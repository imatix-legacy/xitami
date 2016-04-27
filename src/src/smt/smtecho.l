!----------------------------------------------------------------------------
!   Name:       smtecho.l
!   Title:      Dialog for SMT TCP/IP echo agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/06/18  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    97/09/08
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
          + Open-Agent-Log-File
          + Open-Master-Socket
          + Wait-For-Socket-Input
    (--) Client                             -> Echoing-Data
          + Read-Socket-Data-Repeatedly

Master-Input:
    (--) Ok                                 -> Master-Input
          + Accept-Client-Connection
          + Wait-For-Socket-Input
    (--) Error                              -> End-Thread
          + Signal-Socket-Error
          + Check-Socket-Type
    (--) Closed                             ->
          + Shutdown-The-Application
          + Terminate-The-Thread

Echoing-Data:
    (--) Read-Ok                            -> Echoing-Data
          + Echo-Socket-Data
    (--) Write-Ok                           -> Echoing-Data
          +
    (--) Closed                             ->
          + Terminate-The-Thread
    (--) Error                              -> End-Thread
          + Signal-Socket-Error
          + Check-Socket-Type

Defaults:
    (--) Exception                          -> End-Thread
          + Check-Socket-Type
    (--) Shutdown                           -> End-Thread
          + Check-Socket-Type
    (--) Fatal                              ->
          + Shutdown-The-Application
          + Terminate-The-Thread

End-Thread:
    (--) Master                             ->
          + Close-Agent-Log-File
          + Terminate-The-Thread
    (--) Client                             ->
          + Terminate-The-Thread
