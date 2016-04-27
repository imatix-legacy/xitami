!----------------------------------------------------------------------------
!   Name:       smttran.l
!   Title:      Dialog for SMT transfer agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/09/05  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    99/02/13
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c

After-Init:
    (--) Master                             -> Getting-Event
          +
    (--) Put-File                           -> File-Buffer-Out
          + Open-File-For-Input
          + Read-File-Data-Buffer
          + Convert-Ascii-To-Net-If-Reqd
          + Put-Buffer-To-Socket
    (--) Get-File                           -> File-Buffer-In
          + Open-File-For-Output
          + Get-Buffer-From-Socket

Getting-Event:
    (--) Put-Block                          -> Getting-Event
          + Create-Put-Block-Request
          + Process-Transfer-Requests
          + Get-Next-Event-From-Queue
    (--) Get-Block                          -> Getting-Event
          + Create-Get-Block-Request
          + Process-Transfer-Requests
          + Get-Next-Event-From-Queue
    (--) Put-Huge                           -> Getting-Event
          + Create-Put-Huge-Request
          + Process-Transfer-Requests
          + Get-Next-Event-From-Queue
    (--) Get-Huge                           -> Getting-Event
          + Create-Get-Huge-Request
          + Process-Transfer-Requests
          + Get-Next-Event-From-Queue
    (--) Put-File                           -> Getting-Event
          + Create-Put-File-Thread
          + Process-Transfer-Requests
          + Get-Next-Event-From-Queue
    (--) Get-File                           -> Getting-Event
          + Create-Get-File-Thread
          + Process-Transfer-Requests
          + Get-Next-Event-From-Queue
    (--) Commit                             -> Getting-Event
          + Okay-If-No-Requests-Left
          + Get-Next-Event-From-Queue
    (--) Empty                              -> Getting-Event
!    We wait for an incoming event
          + Process-Transfer-Requests
    (--) Write-Ok                           -> Getting-Event
          + Update-Request-After-Write
          + Process-Transfer-Requests
    (--) Read-Ok                            -> Getting-Event
          + Update-Request-After-Read
          + Process-Transfer-Requests
    (--) Writeh-Ok                          -> Getting-Event
          + Update-Request-After-Writeh
          + Process-Transfer-Requests
    (--) Readh-Ok                           -> Getting-Event
          + Update-Request-After-Readh
          + Process-Transfer-Requests
    (--) Sock-Closed                        -> Getting-Event
          + Update-Request-After-Closed
          + Process-Transfer-Requests
    (--) Sock-Error                         -> Getting-Event
          + Update-Request-After-Error
          + Process-Transfer-Requests

File-Buffer-Out:
    (--) Write-Ok                           -> File-Buffer-Out
          + Read-File-Data-Buffer
          + Convert-Ascii-To-Net-If-Reqd
          + Put-Buffer-To-Socket
    (--) Incomplete                         -> File-Buffer-Out
          + Put-Buffer-To-Socket
    (--) Sock-Closed                        ->
          + Signal-Socket-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Terminate-The-Thread

File-Buffer-In:
    (--) Read-Ok                            -> File-Buffer-In
          + Convert-Net-To-Ascii-If-Reqd
          + Write-File-Data-Buffer
          + Get-Buffer-From-Socket
    (--) Sock-Closed                        ->
          + Signal-Get-File-Okay
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Terminate-The-Thread

Defaults:
    (--) Shutdown                           -> End-Thread
          + Check-Thread-Type
    (--) Exception                          -> End-Thread
          + Check-Thread-Type
    (--) End-Of-File                        ->
          + Signal-Put-File-Okay
          + Terminate-The-Thread
    (--) Error                              ->
          + Terminate-The-Thread
    (--) Ok                                 ->
          +

End-Thread:
    (--) Master                             ->
          + Destroy-All-Requests
          + Terminate-The-Thread
    (--) Put-File                           ->
          + Terminate-The-Thread
    (--) Get-File                           ->
          + Terminate-The-Thread

