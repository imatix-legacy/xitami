!----------------------------------------------------------------------------
!   Name:       smthttp.l
!   Title:      Dialog for SMT HTTP server
!   Package:    Libero SMT 2.x
!
!   Written:    96/04/22  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    99/05/16  for 2.4d1
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c

After-Init:
    (--) Master                             -> Master-Input
          + Open-Server-Log-File
          + Load-Virtual-Hosts
          + Check-Rootdir-Exists
          + Open-Ssl-Socket-If-Needed
          + Open-Master-Socket
          + Set-Server-Process-State
          + Wait-For-Socket-Input
    (--) Sock-Retry                         -> Master-Input
          + Open-Master-Socket
          + Set-Server-Process-State
          + Wait-For-Socket-Input
    (--) Client                             -> Client-Input
          + Prepare-Client-Thread
          + Prepare-To-Read-Request
          + Read-Input-From-Socket

Master-Input:
    (--) Ok                                 ->
          + Accept-Client-Connection
          + Wait-For-Socket-Input
    (--) New-Ssl-Client                     ->
          + Create-Ssl-Child-Thread
    (--) Timer                              ->
          + Reload-Config-If-Needed
    (--) Restart                            -> Master-Restart
          + Free-All-Server-Resources
          + Kill-All-Active-Connections
          + Wait-For-Connections-To-Close
    (--) Sock-Retry                         ->
          + Open-Master-Socket
          + Wait-For-Socket-Input
    (--) Sock-Closed                        -> End-Thread
          + Signal-Socket-Closed
          + Check-Socket-Type
    (--) Cancel                             ->
          +
    (--) Wsx-Install                        ->
          + Install-Wsx-Alias
    (--) Wsx-Cancel                         ->
          + Cancel-Wsx-Alias

Master-Restart: <Master-Input>
    (--) Timer                              -> Master-Input
          + Open-Server-Log-File
          + Load-Virtual-Hosts
          + Check-Rootdir-Exists
          + Restart-Ftp-Server-If-Reqd
          + Restart-Ssl-Agent-If-Reqd
          + Open-Ssl-Socket-If-Needed
          + Wait-For-Socket-Input
!   We reject any connection requests that come in now
    (--) Ok                                 ->
          + Reject-Client-Connection
          + Wait-For-Socket-Input

!   Superstate defines error-handling for client threads.
!   This makes error handling a little faster in all child
!   threads; in any case the Defaults handling is secure too.

Client:
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Terminate-The-Thread
    (--) Sock-Timeout                       ->
          + Terminate-The-Thread
    (--) Sock-Retry                         ->
          + Terminate-The-Thread
    (--) Error                              ->
          + Write-Http-Header
          + Terminate-The-Thread
    (--) Ssl-Error                          ->
          + Terminate-The-Thread
    (--) Bad-Request                        ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Unauthorized                       ->
          + Signal-Url-Unauthorized
          + Terminate-The-Thread
    (--) Forbidden                          ->
          + Signal-Url-Forbidden
          + Terminate-The-Thread
    (--) Not-Found                          ->
          + Signal-Url-Not-Found
          + Terminate-The-Thread
    (--) Too-Large                          ->
          + Signal-Too-Large
          + Terminate-The-Thread
    (--) Internal-Error                     ->
          + Signal-Internal-Error
          + Terminate-The-Thread
    (--) Not-Implemented                    ->
          + Signal-Not-Implemented
          + Terminate-The-Thread
    (--) Overloaded                         ->
          + Signal-Overloaded
          + Terminate-The-Thread

Client-Input: <Client>
    (--) Ok                                 -> Have-Client-Request
          + Read-Http-Request-Next
          + Check-If-Request-Complete
    (--) Sock-Retry                         -> Client-Input
          + Read-Input-From-Socket

Have-Client-Request: <Client>
    (--) More                               -> Client-Input
          + Read-Input-From-Socket
    (--) Post                               -> Have-Client-Post
          + Check-If-Post-Data-Complete
    (--) Finished                           -> Execute-Http-Request
          + Parse-Http-Request
          + Resolve-Virtual-Hostname
          + Check-Client-Ip-Allowed

Client-Input-Post: <Client>
    (--) Ok                                 -> Have-Client-Post
          + Read-Http-Posted-Data
          + Check-If-Post-Data-Complete
    (--) Sock-Retry                         -> Client-Input-Post
          + Read-Input-From-Socket

Have-Client-Post: <Client>
    (--) More                               -> Client-Input-Post
          + Read-Input-From-Socket
    (--) Finished                           -> Execute-Http-Request
          + Parse-Http-Request
          + Resolve-Virtual-Hostname
          + Check-Client-Ip-Allowed

Execute-Http-Request: <Client>
    (--) Get-Request                        -> Process-Http-Get
          + Get-Url-Type
    (--) Post-Request                       -> Process-Http-Post
          + Get-Url-Type
    (--) Update-Request                     -> Process-Http-Update
          + Get-Url-Type

Process-Http-Get: <Client>
    (--) Html                               -> Have-Type-Of-Get
          + Check-File-Or-Directory
    (--) Imap                               -> Request-Finished
          + Get-Url-From-Map
          + Write-Http-Header
          + Check-If-Keep-Alive
    (--) Cgi                                -> Have-Type-Of-Cgi
          + Check-File-Or-Directory
    (--) Filter                             -> Have-Type-Of-Filter
          + Check-File-Or-Directory
    (--) Wsx                                -> Trying-To-Get-Wsx
          + Check-If-Protected

Have-Type-Of-Get: <Client>
    (--) File                               -> Trying-To-Get-File
          + Check-If-Protected
    (--) Executable                         -> Trying-To-Get-File
          + Check-If-Protected
    (--) Directory                          -> Trying-To-Get-Dir
          + Check-If-Protected

Trying-To-Get-File: <Client>
    (--) Ok                                 -> After-Sending-File
          + Check-If-Send-File
          + Write-Http-Header
          + Send-File-To-Browser
    (--) Send-Header                        -> Request-Finished
          + Write-Http-Header
          + Check-If-Keep-Alive

Process-Http-Post: <Client>
    (--) Html                               ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Imap                               ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Cgi                                -> Have-Type-Of-Cgi
          + Check-File-Or-Directory
    (--) Filter                             -> Have-Type-Of-Filter
          + Check-File-Or-Directory
    (--) Wsx                                -> Trying-To-Get-Wsx
          + Check-If-Protected

Process-Http-Update: <Client>
    (--) Html                               -> Have-Type-Of-Update
          + Check-File-Or-Directory
    (--) Imap                               ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Cgi                                ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Wsx                                ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Filter                             ->
          + Signal-Bad-Request
          + Terminate-The-Thread

Have-Type-Of-Update: <Client>
    (--) File                               -> Trying-To-Update
          + Check-If-Protected
    (--) Not-Found                          -> Trying-To-Update
          + Check-If-Protected
    (--) Executable                         ->
          + Signal-Url-Forbidden
          + Terminate-The-Thread
    (--) Directory                          ->
          + Signal-Url-Forbidden
          + Terminate-The-Thread

Trying-To-Update: <Client>
    (--) Ok                                 -> Request-Finished
          + Update-Resource-From-Request
          + Write-Http-Header
          + Check-If-Keep-Alive

After-Sending-File: <Client>
    (--) Finished                           -> Request-Finished
          + Check-If-Keep-Alive

Trying-To-Get-Dir: <Client>
    (--) Ok                                 -> Have-Default
          + Get-Default-Web-Page

Have-Default: <Client>
    (--) File                               -> Process-Http-Get
          + Get-Url-Type
    (--) Send-Header                        -> Request-Finished
          + Write-Http-Header
          + Check-If-Keep-Alive
    (--) Not-Found                          -> After-Sending-File
          + Make-Directory-Listing
          + Write-Http-Header
          + Send-File-To-Browser

Have-Type-Of-Cgi: <Client>
!   If /cgi-bin contains non-executable file (e.g. image) we just send it
    (--) File                               -> Trying-To-Get-File
          + Check-If-Protected
    (--) Executable                         -> Before-Running-Cgi
          + Check-If-Protected
    (--) Directory                          -> Trying-To-Get-Dir
          + Check-If-Protected

Before-Running-Cgi: <Client>
    (--) Ok                                 -> Wait-For-Cgi
          + Create-Cgi-Process
          + Wait-Process-End

Wait-For-Cgi: <Client>
    (--) Timer                              -> Wait-For-Cgi
          + Wait-Process-End
    (--) Finished                           -> After-Sending-File
          + Close-Child-Process
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser
    (--) Redirect                           -> Process-Http-Get
          + Get-Url-Type
    (--) Error                              ->
          + Close-Child-Process
          + Write-Http-Header
          + Terminate-The-Thread

Have-Type-Of-Filter: <Client>
    (--) File                               -> Trying-To-Get-Filter
          + Check-If-Protected
    (--) Executable                         -> Trying-To-Get-Filter
          + Check-If-Protected
    (--) Directory                          -> Trying-To-Get-Dir
          + Check-If-Protected

Trying-To-Get-Filter: <Client>
    (--) Ok                                 -> Wait-For-Filter
          + Create-Filter-Process
          + Wait-Process-End

Wait-For-Filter: <Client>
    (--) Timer                              -> Wait-For-Filter
          + Wait-Process-End
    (--) Finished                           -> After-Sending-File
          + Close-Child-Process
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser
    (--) Redirect                           -> Process-Http-Get
          + Get-Url-Type
    (--) Error                              ->
          + Close-Child-Process
          + Write-Http-Header
          + Terminate-The-Thread

Trying-To-Get-Wsx: <Client>
    (--) Ok                                 -> Wait-For-Wsx
          + Pass-Request-To-Wsx-Agent

Wait-For-Wsx: <Client>
    (--) Ok                                 -> Process-Wsx-Done
          + Get-Wsx-Return-Fields
    (--) Multi                              -> Process-Wsx-Multipart
          + Get-Wsx-Return-Fields
    (--) Binary                             -> Process-Wsx-Done
          + Get-Wsx-Bin-Return-Fields
    (--) Multibin                           -> Process-Wsx-Multipart
          + Get-Wsx-Bin-Return-Fields
    (--) Error                              ->
          + Get-Wsx-Error-Fields
          + Write-Http-Header
          + Terminate-The-Thread
    (--) Redirect                           ->
          + Get-Wsx-Redirect-Fields
          + Write-Http-Header
          + Terminate-The-Thread
    (--) Restart                            -> Process-Wsx-Restart
          + Get-Wsx-Return-Fields
    (--) Kill                               -> Process-Wsx-Kill
          + Get-Wsx-Return-Fields

Process-Wsx-Done:
!   Normally the WSX response data is in the event body
    (--) Ok                                 -> Request-Finished
          + Reparse-Http-Body
          + Write-Http-Header
          + Write-Http-Body
          + Check-If-Keep-Alive
!   But it might be redirected to a file
    (--) Redirect                           -> After-Sending-File
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser

Process-Wsx-Multipart:
    (--) Ok                                 -> Wait-For-Wsx
          + Reparse-Http-Body
          + Write-Http-Header
          + Write-Http-Body
    (--) Redirect                           -> Wait-For-Wsx
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser

Process-Wsx-Restart:
    (--) Ok                                 ->
          + Reparse-Http-Body
          + Write-Http-Header
          + Write-Http-Body
          + Send-Master-Thread-Restart
          + Terminate-The-Thread
    (--) Redirect                           ->
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser
          + Send-Master-Thread-Restart
          + Terminate-The-Thread

Process-Wsx-Kill:
    (--) Ok                                 ->
          + Reparse-Http-Body
          + Write-Http-Header
          + Write-Http-Body
          + Send-Master-Thread-Shutdown
          + Terminate-The-Thread
    (--) Redirect                           ->
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser
          + Send-Master-Thread-Shutdown
          + Terminate-The-Thread

Request-Finished: <Client>
    (--) Ok                                 -> Client-Input
          + Partial-Clear-Http-Context
          + Read-Input-From-Socket
    (--) Close                              ->
          + Terminate-The-Thread

Defaults:
    (--) Exception                          -> End-Thread
          + Check-Socket-Type
    (--) Shutdown                           -> End-Thread
          + Check-Socket-Type
    (--) Cancel                             -> End-Thread
          + Check-Socket-Type
    (--) Fatal                              ->
          + Signal-Closing-Server
          + Free-All-Server-Resources
          + Shutdown-The-Application
          + Terminate-The-Thread
    (--) Sock-Error                         -> End-Thread
          + Signal-Socket-Error
          + Check-Socket-Type
    (--) Sock-Closed                        -> End-Thread
          + Check-Socket-Type
    (--) Sock-Timeout                       -> End-Thread
          + Check-Socket-Type
    (--) Sock-Retry                         -> End-Thread
          + Check-Socket-Type
    (--) $other                             ->
          +

End-Thread:
    (--) Master                             ->
          + Signal-Closing-Server
          + Free-All-Server-Resources
          + Shutdown-The-Application
          + Terminate-The-Thread
    (--) Client                             ->
          + Flush-Socket-Requests
          + Terminate-The-Thread
