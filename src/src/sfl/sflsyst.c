/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflsyst.c
    Title:      System-level functions
    Package:    Standard Function Library (SFL)

    Written:    97/04/13  iMatix SFL project team <sfl@imatix.com>
    Revised:    98/12/22

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "prelude.h"                    /*  Universal header file            */
#include "sflsyst.h"                    /*  Symbol-table functions           */


/*  ---------------------------------------------------------------------[<]-
    Function: sys_assert

    Synopsis: Displays an 'assertion failed' message and aborts the program.
    This function is required by prelude.h if you compile with the DEBUG
    symbol.
    ---------------------------------------------------------------------[>]-*/

void
sys_assert (const char *File, unsigned Line)
{
#if (defined (__WINDOWS__))
    static char
        buffer [LINE_MAX];              /*  Formatted error message          */
    MSG
        msg;
    Bool
        quit;
    int
        rc;                             /*  MessageBox return code           */

    sprintf (buffer, "Module %s, line %u", File, Line);
    /*  If WM_QUIT is in the queue the message box won't show                */
    quit = PeekMessage (&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
    rc   = MessageBox  (NULL, buffer, "Assertion failed!",
                        MB_TASKMODAL | MB_ICONHAND | MB_ABORTRETRYIGNORE);
    if (quit)
        PostQuitMessage (msg.wParam);
    if (rc != IDABORT)
        return;
#else
    fflush  (stdout);
    fprintf (stderr, "\nAssertion failed: %s, line %u\n", File, Line);
    fflush  (stderr);
#endif
    abort   ();
}


/*  ---------------------------------------------------------------------[<]-
    Function: sys_name

    Synopsis: Returns a static buffer with the type or name of OS.
    ---------------------------------------------------------------------[>]-*/

char *
sys_name (void)
{
#if (defined (__WINDOWS__))
#   if (defined (WIN32))
    static char
        name [30];

    OSVERSIONINFO
        version_info;

    version_info.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    if (GetVersionEx (&version_info))
      {
        if (version_info.dwPlatformId == VER_PLATFORM_WIN32_NT)
            sprintf (name, "Windows NT %ld.%ld",
                            version_info.dwMajorVersion,
                            version_info.dwMinorVersion);
        else
        if (version_info.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
            sprintf (name, "Windows 95 %ld.%ld",
                            version_info.dwMajorVersion,
                            version_info.dwMinorVersion);
        else
            sprintf (name, "Windows %ld.%ld with win32s",
                            version_info.dwMajorVersion,
                            version_info.dwMinorVersion);
      }
    return (name);
#   else
        return ("Windows 3.x");
#   endif
#elif (defined (__UNIX__))
#   if (defined (__UTYPE_AUX))
        return ("UNIX Type: Apple AUX");
#   elif (defined (__UTYPE_DECALPHA))
        return ("UNIX Type: Digital UNIX (Alpha)");
#   elif (defined (__UTYPE_IBMAIX))
        return ("UNIX Type: IBM RS/6000 AIX");
#   elif (defined (__UTYPE_HPUX))
        return ("UNIX Type: HP/UX");
#   elif (defined (__UTYPE_LINUX))
        return ("UNIX Type: Linux");
#   elif (defined (__UTYPE_MIPS))
        return ("UNIX Type: MIPS");
#   elif (defined (__UTYPE_NETBSD))
        return ("UNIX Type: NetBSD");
#   elif (defined (__UTYPE_NEXT))
        return ("UNIX Type: NeXT");
#   elif (defined (__UTYPE_SCO))
        return ("UNIX Type: SCO UNIX");
#   elif (defined (__UTYPE_IRIX))
        return ("UNIX Type: Silicon Graphics IRIX");
#   elif (defined (__UTYPE_SUNOS))
        return ("UNIX Type: SunOS");
#   elif (defined (__UTYPE_SUNSOLARIS))
        return ("UNIX Type: Sun Solaris");
#   elif (defined (__UTYPE_UNIXWARE))
        return ("UNIX Type: SCO UNIXWare");
#   else
        return ("UNIX Type: Generic");
#   endif
#elif (defined (__VMS__))
    return ("UNIX Type: Digital OpenVMS");
#elif (defined (__OS2__))
    return ("UNIX Type: IBM OS/2");
#elif (defined (__MSDOS__))
    return ("MS-DOS");
#else
    return ("Unknown");
#endif
}

