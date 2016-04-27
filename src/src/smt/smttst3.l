!----------------------------------------------------------------------------
!   Name:       smttst3.l
!   Title:      Dialog for SMT DNS test agent
!   Package:    Libero SMT 2.x
!
!   Written:    97/10/12  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    97/12/23
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
    (--) Ok                                 -> Process-Argument
          + Initialise-Dns-Library
          + Display-Dns-Server-Address
          + Get-Next-Argument
          + Get-Command
    (--) Error                              ->
          + Terminate-The-Thread

Process-Argument:
    (--) Help                               -> Process-Argument
          + Display-Help
          + Get-Next-Argument
          + Get-Command
    (--) Debug                              -> Process-Argument
          + Set-Debug-Mode
          + Get-Next-Argument
          + Get-Command
    (--) Recursive                          -> Process-Argument
          + Set-Recursive-Mode
          + Get-Next-Argument
          + Get-Command
    (--) Server-Ip                          -> Process-Argument
          + Set-Server-Ip-Value
          + Display-Dns-Server-Address
          + Get-Next-Argument
          + Get-Command
    (--) Request                            -> Send-Request
          + Get-Argument-Type
    (--) Invalid                            -> Process-Argument
          + Display-Invalid-Argument
          + Get-Next-Argument
          + Get-Command
    (--) None                               -> Process-Command
          + Set-Prompt
          + Get-Command

Process-Command:
    (--) Ok                                 -> Process-Command
          + Set-Prompt
          + Get-Command
    (--) None                               -> Process-Command
          + Set-Prompt
          + Get-Command
    (--) Exit                               ->
          + Terminate-The-Thread
    (--) Help                               -> Process-Command
          + Display-Help
          + Set-Prompt
          + Get-Command
    (--) Debug                              -> Process-Command
          + Set-Debug-Mode
          + Set-Prompt
          + Get-Command
    (--) Invalid                            -> Process-Command
          + Display-Invalid-Command
          + Set-Prompt
          + Get-Command
    (--) Recursive                          -> Process-Command
          + Set-Recursive-Mode
          + Set-Prompt
          + Get-Command
    (--) Server-Ip                          -> Process-Command
          + Set-Server-Ip-Value
          + Display-Dns-Server-Address
          + Set-Prompt
          + Get-Command
    (--) Request                            -> Send-Request
          + Get-Argument-Type

Send-Request:
    (--) Ip                                 -> After-Request
          + Request-Host-Name
    (--) Host-Name                          -> After-Request
          + Request-Ip-Address
    (--) Error                              -> Process-Command
          + Display-Error-Value
          + Set-Prompt
          + Get-Command

After-Request:
    (--) Host                               -> Process-Command
          + Display-Host-Name
    (--) Ip                                 -> Process-Command
          + Display-Ip-Address
    (--) Error                              -> Process-Command
          + Display-Error-Value
    (--) End                                -> Process-Command
          + Display-End-Of-Search
    (--) Timeout                            -> Process-Command
          + Display-Time-Out

Defaults:
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread
    (--) Fatal                              ->
          + Terminate-The-Thread
