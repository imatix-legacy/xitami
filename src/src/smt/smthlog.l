!----------------------------------------------------------------------------
!   Name:       smthlog.l
!   Title:      Dialog for SMT Log file host resolver
!   Package:    Libero SMT 2.x
!
!   Written:    97/12/05  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    98/09/09
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c
-idle

After-Init:
    (--) Master                             -> Process-Argument
          + Initialise-Dns-Library
          + Get-Next-Argument
    (--) Error                              -> End-Thread
          + Check-Thread-Type
    (--) Request                            -> Resolver-Feedback
          + Send-Request-To-Resolver

Process-Argument:
    (--) Server-Ip                          -> Process-Argument
          + Set-Server-Ip-Value
          + Get-Next-Argument
    (--) Debug-Mode                         -> Process-Argument
          + Set-Debug-Mode
          + Get-Next-Argument
    (--) Verbose-Mode                       -> Process-Argument
          + Set-Verbose-Mode
          + Get-Next-Argument
    (--) Recursive-Mode                     -> Process-Argument
          + Set-Recursive-Mode
          + Get-Next-Argument
    (--) Log-File                           -> After-Open-File
          + Check-Dns-Config
          + Open-Log-File
    (--) End                                -> End-Thread
          + Check-Thread-Type
    (--) Help                               -> End-Thread
          + Show-Help
          + Check-Thread-Type

After-Open-File:
    (--) Ok                                 -> After-Request-Creation
          + Read-Next-Line
          + Create-Request
    (--) Error                              -> Process-Argument
          + Partial-Initialisation
          + Get-Next-Argument

After-Request-Creation:
    (--) Ok                                 -> Stack-Level
          + Create-Request-Thread
          + Check-Stack-Level
    (--) Error                              -> After-Request-Creation
          + Write-Current-Line-To-Output
          + Read-Next-Line
          + Create-Request
    (--) End-Of-File                        -> Master-Input
          + Show-Processing-Statistics
          + Set-End-File-Flag

Stack-Level:
    (--) Full                               -> Master-Input
          +
    (--) Not-Full                           -> After-Request-Creation
          + Read-Next-Line
          + Create-Request
    (--) Empty                              -> Process-Argument
          + Partial-Initialisation
          + Get-Next-Argument

Master-Input:
    (--) Request-Complete                   -> After-Request-Complete
          + Check-If-First-Request-Complete
    (--) End-Of-File                        -> Process-Argument
          + Partial-Initialisation
          + Get-Next-Argument

After-Request-Complete:
    (--) First-Request                      -> After-Request-Complete
          + Store-Line-To-Output
          + Remove-Request-Form-Stack
          + Check-If-First-Request-Complete
    (--) Not-First                          -> Stack-Level
          + Check-Stack-Level
    (--) Empty-Stack                        -> After-Request-Creation
          + Read-Next-Line
          + Create-Request
    (--) End-Of-File                        -> Process-Argument
          + Partial-Initialisation
          + Get-Next-Argument

Resolver-Feedback:
    (--) Host                               -> End-Thread
          + Store-Host-Name
          + Check-Thread-Type
    (--) Ip                                 -> End-Thread
          + Set-Feedback-To-Error
          + Check-Thread-Type
    (--) Error                              -> End-Thread
          + Set-Feedback-To-Error
          + Check-Thread-Type
    (--) End                                -> End-Thread
          + Set-Feedback-To-Not-Found
          + Check-Thread-Type
    (--) Timeout                            -> End-Thread
          + Set-Feedback-To-Timeout
          + Check-Thread-Type

Defaults:
    (--) Exception                          -> End-Thread
          + Check-Thread-Type
    (--) Shutdown                           -> End-Thread
          + Check-Thread-Type
    (--) Fatal                              -> End-Thread
          + Check-Thread-Type

End-Thread:
    (--) Master                             ->
          + Terminate-The-Thread
          + Shutdown-Application
    (--) Request                            ->
          + Display-Result-To-Console
          + Send-Request-Complete
          + Terminate-The-Thread
