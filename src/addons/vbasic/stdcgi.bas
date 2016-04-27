Attribute VB_Name = "StdCGI_Framework"
'====================================================================
'           CGI WorkerMan for Visual Basic
'====================================================================
' Author : Wei-dun Teng <tiberius@ms28.hinet.net>
' Version: 1.4 Release (November 12, 1998)
' Please report any comments or bugs to my E-Mail box, thanks.
'--------------------------------------------------------------------
' Common routines needed to establish a VB environment for
' Standard CGI programs that run behind the web server.
'--------------------------------------------------------------------
' The Common Gateway Interface (CGI) version 1.1 specifies
' a minial set of data that is made available to the back-
' end application by an HTTP (Web) server. It also specifies
' the details for passing this information to the back-end.
' The latter part of the CGI spec is specific to Unix-like
' environments. The NCSA httpd for Windows does supply the
' data items (and more) specified by CGI/1.1. This module uses
' WinAPIs to parse datas from your server by STDIN/STDOUT.
'--------------------------------------------------------------------
' This module is based on Robert B. Denny's CGI32.BAS
'--------------------------------------------------------------------
' USAGE: Include CGI32.BAS in your VB project. Set the
' project options for "Sub Main" startup. The Main() procedure
' is in this module, and it handles all of the setup of the
' VB CGI environment. Once all of this is done, the Main()
' calls YOUR main procedure which must be called CGI_Main().
' The output file is open, use Send() to write to it. The
' input file is NOT open, notice that. If this module doesn't
' detected any server is running, it will show a message box
' and then quit immediately. If you want to call another
' subroutine when server is not running, just take a look at
' Main() subroutine.
'---------------------------------------------------------------------
' Future plans on this module:
' -> Cookie array/dictionary support
' -> Something works like ASP Session object
'---------------------------------------------------------------------
Option Explicit
Option Compare Text

'=============================
' Standard Input/Output Stuff
'=============================
Const STD_INPUT_HANDLE& = -10
Const STD_OUTPUT_HANDLE& = -11
Declare Function GetStdHandle Lib "kernel32" (ByVal nStdHandle As Long) As Long
Declare Function WriteFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToWrite As Long, lpNumberOfBytesWritten As Long, ByVal lpOverlapped As Long) As Long
Declare Function ReadFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToRead As Long, lpNumberOfBytesRead As Long, ByVal lpOverlapped As Long) As Long

'====================
' Manifest Constants
'====================
Public Const MAX_FORM_TUPLES% = 255
Public Const MAX_FORM_COOKIES% = 255
Public Const DONT_ENCODE$ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-*"

'=======
' Types
'=======
Type Tuple
    Key As String
    Value As String
End Type

'============================
'    CGI Global Variables
'============================
' These values are explained
' in InitializeCGI section.
'----------------------------
Public ServerSoftware$
Public ServerName$
Public ServerPort%
Public RequestProtocol$
Public ServerAdmin$
Public CGIVersion$
Public RequestMethod$
Public VirtualPath$
Public LogicalPath$
Public CGIProgramFile$
Public CGIProgramPath$
Public CGIProgramUrl$
Public QueryString$
Public CookieString$
Public PostString$
Public From$
Public UserAgent$
Public ContentType$
Public ContentLength$
Public AcceptTypes$
Public DocumentRoot$

'================
' POST Form Data
'================
Public FormTuples(MAX_FORM_TUPLES) As Tuple
Public FormCookies(MAX_FORM_COOKIES) As Tuple
Public NumFormTuples As Integer
Public NumFormCookies As Integer

'==================
' System Variables
'==================
Public GMTOffset As Variant
Public STDIN As Long               ' STDIN Handler
Public STDOUT As Long              ' STDOUT Handler
Public rc As Long                  ' WinAPI Return Code
Public ErrorString As String       ' Normal Error Message

'-================-
' STRING CONSTANTS
'-================-
'
' This section contains a lot of useful strings.
'
'-----------------------
' HTTP response headers
'-----------------------
Public Const Status200$ = "HTTP/1.0 200 OK" & vbCrLf
Public Const Status204$ = "HTTP/1.0 204 No Content" & vbCrLf
Public Const Status206$ = "HTTP/1.0 206 Partial Content" & vbCrLf
Public Const Status301$ = "HTTP/1.0 301 Moved Permanently" & vbCrLf
Public Const Status302$ = "HTTP/1.0 302 Found" & vbCrLf
Public Const Status303$ = "HTTP/1.0 303 See Other" & vbCrLf
Public Const Status304$ = "HTTP/1.0 304 Not Modified" & vbCrLf
Public Const Status307$ = "HTTP/1.0 307 Temporary Redirect" & vbCrLf
Public Const Status401$ = "HTTP/1.0 401 Unauthorized" & vbCrLf
Public Const Status403$ = "HTTP/1.0 403 Forbidden" & vbCrLf
Public Const Status404$ = "HTTP/1.0 404 Not Found" & vbCrLf
Public Const Status411$ = "HTTP/1.0 411 Length Required" & vbCrLf
Public Const Status416$ = "HTTP/1.0 416 Request Range Not Satisfiable" & vbCrLf
Public Const Status500$ = "HTTP/1.0 500 Internal Server Error" & vbCrLf
Public Const Status503$ = "HTTP/1.0 503 Service Unavailable" & vbCrLf

'---------------
' Content-Types
'---------------
Public Const ContainHTML$ = "Content-type: text/html" & vbCrLf
Public Const ContainPlainText$ = "Content-type: text/plain" & vbCrLf
Public Const ContainJPEGImage$ = "Content-type: image/jpeg" & vbCrLf
Public Const ContainGIFImage$ = "Content-type: image/gif" & vbCrLf
Public Const ContainOctetStream$ = "Content-type: application/octet-stream" & vbCrLf

'-=============================-
' DATA PROCESSING FUNCTIONS 1.5
'-=============================-
'
'---------------------------------------------------------
' Send - Write a string to output (without CR/LF suffix!)
'---------------------------------------------------------
Sub Send(sInput As String)
    Dim bOutput() As Byte, lStrPos&, lWritten&
    ReDim bOutput(1 To Len(sInput))
    For lStrPos = 1 To Len(sInput)
        bOutput(lStrPos) = Asc(Mid(sInput, lStrPos, 1))
    Next lStrPos
    rc = WriteFile(STDOUT, bOutput(1), UBound(bOutput) - LBound(bOutput) + 1, lWritten, 0)
End Sub

'----------------------------------------
' Param - Get the value of a form field.
'----------------------------------------
Function Param(sKey As String) As String
    Param = TupleValue(sKey, FormTuples)
End Function

'-------------------------------------------------
' ParamExist - Return True/False depending on
'                whether a form field is exist.
'-------------------------------------------------
' Typically used to detect if a checkbox in a form
' is checked or not. Unchecked checkboxes are
' omitted from the form content.
'-------------------------------------------------
Function ParamExist(sKey As String) As Integer
    ParamExist = TupleExist(sKey, FormTuples)
End Function

'-------------------------------------------------------------------------------------------
' SetCookie - Return a cookie header, you MUST send it in header not content area!
'-------------------------------------------------------------------------------------------
' Usage: Send generated cookie header like this: Call Send(SetCookie(.......))
'-------------------------------------------------------------------------------------------
'   sKey:       Name for this cookie.
'   sValue:     Value for this cookie.
'       You can use Cookie() to read a cookie's value,
'       and use CookieExist() to check whether a cookie is exist (with or without a value).
'   sPath:      Path for which this cookie is valid.
'       CGI programs can't read your cookie outside this path.
'       You can save cookie in the same name but in different path,
'       they will not confilict.
'   sDomain:    Internet domain for which this cookie is valid.
'       The rule for this argument is same as sPath.
'   vExpires:   Expiry date in any valid date format (string, etc.)
'       After this date/time the cookie will automatically deleted
'       If omitted, cookie will deleted when browser closed.
'       It will pre-processed by WebDate() automatically.
'       You can use DateAdd() to calcuate expiry dates.
'   bSecure:    If set to TRUE, cookies only pass through secure
'               channel.
'-------------------------------------------------------------------------------------------
Function SetCookie(sKey As String, Optional sValue As String, Optional sPath As String, Optional sDomain As String, Optional sExpires As String, Optional bSecure As Boolean) As String
    Dim sTemp$, sPair$
    If sPath = "" Then sPath = CGIProgramFile
    If sDomain = "" Then sDomain = ServerName
    If sExpires <> "" Then sExpires = WebDate(CVar(sExpires))
    If sValue = "" Then
        sPair = Encode(sKey)
    Else
        sPair = Encode(sKey) & "=" & Encode(sValue)
    End If
    sTemp = "Set-cookie: " & sPair & "; "
    sTemp = sTemp & "path=" & sPath & "; "
    sTemp = sTemp & "domain=" & sDomain & ";"
    If sExpires <> "" Then sTemp = sTemp & " expires=" & sExpires & ";"
    If bSecure Then sTemp = sTemp & " secure;"
    SetCookie = sTemp
End Function

'------------------------------------------
' Cookie - Get the value of a HTTP cookie.
'------------------------------------------
Function Cookie(sKey As String) As String
    Cookie = TupleValue(sKey, FormCookies)
End Function

'-------------------------------------------------
' CookieExist - Return True/False depending on
'                whether a cookie is exist.
'-------------------------------------------------
Function CookieExist(sKey As String) As Integer
    CookieExist = TupleExist(sKey, FormCookies)
End Function

'----------------------------------------------------
' MapPath - Convert virtual path to logical path
'----------------------------------------------------
' Inputs:  Virtual Path (like "/cgi-bin")
' Returns: Converted Path ("D:\Inetpub\WWW\cgi-bin")
'----------------------------------------------------
' You *MUST* include drive letter and full path in
' your server's "Document Root" configuration,
' or you will get an error result.
'----------------------------------------------------
Function MapPath(sPath As String) As String
    Dim lStrPos&
    For lStrPos = 1 To Len(sPath)   ' Convert "/" to "\" in virtual path string
        If Mid$(sPath, lStrPos, 1) = "/" Then Mid$(sPath, lStrPos, 1) = "\"
    Next lStrPos
    If Left$(sPath, 1) = "\" Then
        MapPath = DocumentRoot & sPath
    Else
        MapPath = CGIProgramPath & "\" & sPath
    End If
End Function

'--------------------------------------------------------------
' URLEncode - Convert a string to URL encoded
'--------------------------------------------------------------
' Inputs:  String you want to encode (such as form URL creating
' Returns: Encoded text.
'--------------------------------------------------------------
Function URLEncode(sInput As String)
    URLEncode = Encode(sInput)
End Function

'---------------------------------------------------
' URLDecode - Decode a HTTP-encoded string
'---------------------------------------------------
' Inputs:  String you want to decode
'          (normally this module will automatically
'           decode any needed data.)
' Returns: Decoded text.
'---------------------------------------------------
Function URLDecode(sInput As String)
    URLDecode = Decode(sInput)
End Function

'------------------------------------------------------------------
' WebDate - Return an HTTP/1.0 compliant date/time string
'------------------------------------------------------------------
' Inputs:   Any valid date in string or varient (returned by Now())
' Returns:  Properly formatted HTTP/1.0 date/time in GMT
'------------------------------------------------------------------
Function WebDate(vInput As Variant) As String
    Dim vOutput As Variant
    vInput = CDate(vInput)
    vOutput = CVDate(vInput - CVDate(Val(GMTOffset) / 86400#))
    WebDate = Format$(vOutput, "ddd dd mmm yyyy hh:mm:ss") & " GMT"
End Function

'-================-
' MODULE CORE v1.2
'-================-
'
'-------------------------------------------------
' Main - CGI script back-end main procedure
'-------------------------------------------------
' If it detected it's not running under a HTTP
' server, it will show a message box and exit.
' If you want a user interface such as
' configuration program, simply comment the
' MsgBox call and remove the next line's comment,
' then write your code in Inter_Main() subroutine.
'-------------------------------------------------
Sub Main()
    Dim lSection&, lLastSect&, lLoop&, bTemp() As Byte
    On Error GoTo ErrorHandler
    If Trim$(Environ("REQUEST_METHOD")) = "" Then       ' Looks like it's not running under a server
        Call MsgBox("This CGI program doesn't have user interface in this mode," & vbCrLf & "Please install it under HTTP server, and run it by your browser.", vbOKOnly, "CGI Workerman Module 1.1c")
'       Inter_Main      ' If it's not running under a HTTP server, then go to GUI mode.
        End
    End If
    InitializeCGI
    CGI_Main
    End
ErrorHandler:
    ErrorString = Err.Description
    ErrorString = ErrorString & " (error #" & Err.Number & ")"
    On Error GoTo 0
    Call ErrorHandler
End Sub

'---------------------------------------------------------
' InitializeCGI - Fill in all of the CGI variables, etc.
'---------------------------------------------------------
' NOTE: Check the environments, and modify it to fit
' the server you used. Current config is setted to run in
' Xitami Web Server v2.3b or later.
' PLEASE ENSURE THE I/O FILE ENVIRONMENTS ARE RIGHT FIRST!
'---------------------------------------------------------
Private Sub InitializeCGI()
    Dim lStrPos&, bPostData() As Byte, lReaded&, lCharPos&
    ServerSoftware = Environ("SERVER_SOFTWARE")   ' Server Software's name
    ServerName = Environ("SERVER_NAME")           ' Server's Host Name
    RequestProtocol = Environ("SERVER_PROTOCOL")  ' Used connection protocol
'   ServerAdmin = Environ("SERVER_ADMIN")         ' Server Administrator's e-mail
    ServerAdmin = "tiberius@ms28.hinet.net"       ' If the server doesn't provided it, then please set manually yourself.
    CGIVersion = Environ("GATEWAY_INTERFACE")     ' CGI Version Number
    RequestMethod = Environ("REQUEST_METHOD")     ' Used Request Method
    VirtualPath = Environ("PATH_INFO")            ' Path info after request URL
    LogicalPath = Environ("PATH_TRANSLATED")      ' Decoded Path Info
    CGIProgramFile = Environ("SCRIPT_NAME")       ' Running Script's Filename
    CGIProgramPath = Environ("SCRIPT_PATH")       ' The folder contains current running script
    CGIProgramUrl = Environ("CGI_URL")            ' CGI Directory's URL
    QueryString = Environ("QUERY_STRING")         ' This environment contains GET data
    CookieString = Environ("HTTP_COOKIE")         ' This environment contains HTTP cookie data
    ContentType = Environ("CONTENT_TYPE")         ' POSTed Data's Content Type
    ContentLength = Environ("CONTENT_LENGTH")     ' POSTed Data's Length
    ServerPort = Environ("SERVER_PORT")           ' Server's Port
'   GMTOffset = Environ("GMT_OFFSET")             ' GMT offset (in seconds!) Used to generate GMT times
    GMTOffset = 28800                             ' Xitami doesn't provided it, so I set it manually (GMT +8 Hour, equal 28800 seconds)
    AcceptTypes = Environ("HTTP_ACCEPT")          ' MIME Types that client can handle
    DocumentRoot = Environ("DOCUMENT_ROOT")       ' Web page root
    For lStrPos = 1 To Len(DocumentRoot)          ' Convert "/" to "\" in Document Root variable
        If Mid$(DocumentRoot, lStrPos, 1) = "/" Then Mid$(DocumentRoot, lStrPos, 1) = "\"
    Next lStrPos
    For lStrPos = 1 To Len(CGIProgramPath)        ' Convert "/" to "\" in CGI Program's Pathname
        If Mid$(CGIProgramPath, lStrPos, 1) = "/" Then Mid$(CGIProgramPath, lStrPos, 1) = "\"
    Next lStrPos
    For lStrPos = 1 To Len(LogicalPath)           ' Convert "/" to "\" in CGI Program's Pathname
        If Mid$(LogicalPath, lStrPos, 1) = "/" Then Mid$(LogicalPath, lStrPos, 1) = "\"
    Next lStrPos
    If Right$(DocumentRoot, 1) = "\" Then DocumentRoot = Left$(DocumentRoot, Len(DocumentRoot) - 1)
    STDOUT = GetStdHandle(STD_OUTPUT_HANDLE)
    If RequestMethod = "POST" Then
        ReDim bPostData(1 To Val(ContentLength))
        STDIN = GetStdHandle(STD_INPUT_HANDLE)
        Call ReadFile(STDIN, bPostData(1), Val(ContentLength), lReaded, 0)
        For lCharPos = 1 To Val(ContentLength)
            PostString = PostString & Chr(bPostData(lCharPos))
        Next lCharPos
        Call SplitTuples(PostString, FormTuples, "&", "=", 1, NumFormTuples, MAX_FORM_TUPLES)
        Close #STDIN
    End If
    Call SplitTuples(QueryString, FormTuples, "&", "=", 1, NumFormTuples, MAX_FORM_TUPLES)
    Call SplitTuples(CookieString, FormCookies, ";", "=", 2, NumFormCookies, MAX_FORM_COOKIES)
End Sub

'------------------------------------------------
' ErrorHandler - Global error handler
'------------------------------------------------
' If a VB runtime error occurs dusing execution
' of the program, this procedure generates an
' HTTP/1.0 HTML-formatted error message into the
' output file, then exits the program.
'------------------------------------------------
Private Sub ErrorHandler()
    Dim sTemp$, bTemp() As Byte, lCharPos&, lNumWritten&
    sTemp = sTemp & "<HTML><HEAD>" & vbCrLf
    sTemp = sTemp & "<TITLE>Error in " + CGIProgramFile + "</TITLE>" & vbCrLf
    sTemp = sTemp & "</HEAD><BODY>" & vbCrLf
    sTemp = sTemp & "<H1>Error in " + CGIProgramFile + "</H1>" & vbCrLf
    sTemp = sTemp & "An internal Visual Basic error has occurred in " + CGIProgramFile + "." & vbCrLf
    sTemp = sTemp & "<PRE>" + ErrorString + "</PRE>" & vbCrLf
    sTemp = sTemp & "<I>Please</I> note what you were doing when this problem occurred," & vbCrLf
    sTemp = sTemp & "so we can identify and correct it. Write down the Web page you were using," & vbCrLf
    sTemp = sTemp & "any data you may have entered into a form or search box, and" & vbCrLf
    sTemp = sTemp & "anything else that may help us duplicate the problem. Then contact the" & vbCrLf
    sTemp = sTemp & "administrator of this service: " & vbCrLf
    sTemp = sTemp & "<A HREF=""mailto:" & ServerAdmin & """>" & vbCrLf
    sTemp = sTemp & "<ADDRESS>&lt;" + ServerAdmin + "&gt;</ADDRESS>" & vbCrLf
    sTemp = sTemp & "</A></BODY></HTML>"
    ReDim bTemp(1 To Len(sTemp))
    For lCharPos = 1 To Len(sTemp)
        bTemp(lCharPos) = Asc(Mid(sTemp, lCharPos, 1))
    Next lCharPos
    rc = WriteFile(STDOUT, bTemp(1), UBound(bTemp) - LBound(bTemp) + 1, lNumWritten, 0)
    End
End Sub

'-===========================-
' TUPLE UTILITY FUNCTIONS 1.0
'-===========================-
'
' Please read README.HTM for hints to use these functions.
'
'----------------------------------------------------------------
' SplitTuples - General Utility for Tuple data format processing
'----------------------------------------------------------------
Sub SplitTuples(ByVal sSource As String, tDest() As Tuple, sSplit1 As String, sSplit2 As String, iShift As Integer, iCounter As Integer, iMaxCounter As Integer)
    Dim sTemp$(), iOrigCounter%
    Dim lPos&, iLoop%
    ReDim sTemp$(iMaxCounter)
    iOrigCounter = iCounter
    Do While iCounter < iMaxCounter
        lPos = InStr(sSource, sSplit1)
        If lPos = 0 Then
            sTemp(iCounter) = sSource
            iCounter = iCounter + 1
            Exit Do
        End If
        sTemp(iCounter) = Left$(sSource, lPos - 1)
        sSource = Mid$(sSource, lPos + iShift)
        iCounter = iCounter + 1
    Loop
    For iLoop = iOrigCounter To (iCounter - 1)
        lPos = InStr(sTemp(iLoop), sSplit2)
        If lPos = 0 Then
            tDest(iLoop).Key = Decode(sTemp(iLoop))
        Else
            tDest(iLoop).Key = Decode(Left$(sTemp(iLoop), lPos - 1))
            tDest(iLoop).Value = Decode(Mid$(sTemp(iLoop), lPos + 1))
        End If
    Next iLoop
End Sub

'----------------------------------------------
' GetTupleValue - Get the value of a tuple
'----------------------------------------------
' If this function doesn't found any field
' you specified, it will return a zero-length
' string.
'----------------------------------------------
Function TupleValue(sKey As String, tInput() As Tuple) As String
    Dim iIndex As Integer
    For iIndex = 0 To UBound(tInput)
        If tInput(iIndex).Key = sKey Then
            TupleValue = Trim$(tInput(iIndex).Value)
            Exit Function
        End If
    Next iIndex
    TupleValue = ""
End Function

'-------------------------------------------------
' TupleExist - Return True/False depending on
'                whether a tuple field is exist.
'-------------------------------------------------
Function TupleExist(sKey As String, tInput() As Tuple) As Integer
    Dim iIndex As Integer
    TupleExist = False            ' If doesn't found it, will return false
    For iIndex = 0 To UBound(tInput)
        If tInput(iIndex).Key = sKey Then
            TupleExist = True     ' Found it
            Exit Function           ' ** DONE **
        End If
    Next iIndex
End Function

'-================================-
' URL CODING UTILITY FUNCTIONS 1.0
'-================================-
'
' Please read README.HTM for hints to use these functions.
' These functions is modified for better DBCS language
' system support.
'
'-------------------------------------------------------
' Decode - Decode URL escaped string
'-------------------------------------------------------
Private Function Decode(sInput As String)
    Dim iPos As Integer, iLen As Integer
    Dim sChar As String, sTemp As String
    If InStr(sInput, "%") = 0 And InStr(sInput, "+") = 0 Then
        Decode = sInput
        Exit Function
    End If
    iLen = Len(sInput)
    sTemp = ""
    For iPos = 1 To iLen
        sChar = Mid$(sInput, iPos, 1)
        If sChar = "%" Then
            If Mid$(sInput, iPos + 1, 1) = "%" Then
                sChar = "%"
                iPos = iPos + 1
            Else
                If CInt("&H" & Mid$(sInput, iPos + 1, 2)) >= 127 Then
                    If Mid$(sInput, iPos + 3, 1) = "%" Then
                        sChar = Unescape(Mid$(sInput, iPos + 1, 2) & Mid$(sInput, iPos + 4, 2))
                        iPos = iPos + 5
                    Else
                        sChar = Unescape(Mid$(sInput, iPos + 1, 2) & Hex(Asc(Mid$(sInput, iPos + 3, 1))))
                        iPos = iPos + 3
                    End If
                Else
                    sChar = Unescape(Mid$(sInput, iPos + 1, 2))
                    iPos = iPos + 2
                End If
            End If
        End If
        If sChar = "+" Then
            sChar = " "
        End If
        sTemp = sTemp & sChar
    Next iPos
    Decode = sTemp
End Function

'------------------------------------------
' Encode - Convert a string to URL Encoded
'------------------------------------------
Private Function Encode(ByVal sInput As String) As String
    Dim sHex As String, sOutput As String, sChar As String
    Dim lLoop As Long
    For lLoop = 1 To Len(sInput)
        sChar = Mid$(sInput, lLoop, 1)
        If InStr(DONT_ENCODE, sChar) = 0 Then
            If sChar = " " Then
                sOutput = sOutput & "+"
            Else
                sHex = Hex$(Asc(sChar))
                If Len(sHex) = 4 Then
                    sOutput = sOutput & "%" & Left$(sHex, 2)
                    sOutput = sOutput & "%" & Right$(sHex, 2)
                Else
                    sOutput = sOutput & "%" & sHex
                End If
            End If
        Else
            sOutput = sOutput & sChar
        End If
    Next lLoop
    Encode = sOutput
End Function

'----------------------------------------------
' UnEscape - Convert Hex Encoded Char to ASCII
'----------------------------------------------
Private Function Unescape(sInput As String) As String
    Dim sHexCode As String
    sHexCode = "&H" & sInput
    Unescape = Chr$(CInt(sHexCode))
End Function
