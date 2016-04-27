!----------------------------------------------------------------------------
!   Name:       smtsock.l
!   Title:      Dialog for SMT socket i/o agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/06/16  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    97/12/28
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c

After-Init:
    (--) Ok                                 -> Getting-Event
          +
    (--) Error                              ->
          + Terminate-The-Thread

Getting-Event:
    (--) Read                               -> Getting-Event
          + Create-Read-Request
          + Get-Next-Event-From-Queue
    (--) Readh                              -> Getting-Event
          + Create-Huge-Read-Request
          + Get-Next-Event-From-Queue
    (--) Readr                              -> Getting-Event
          + Create-Read-Repeat-Request
          + Get-Next-Event-From-Queue
    (--) Readrh                             -> Getting-Event
          + Create-Huge-Read-Repeat-Request
          + Get-Next-Event-From-Queue
    (--) Write                              -> Getting-Event
          + Create-Write-Request
          + Get-Next-Event-From-Queue
    (--) Writeh                             -> Getting-Event
          + Create-Huge-Write-Request
          + Get-Next-Event-From-Queue
    (--) Input                              -> Getting-Event
          + Create-Input-Request
          + Get-Next-Event-From-Queue
    (--) Inputr                             -> Getting-Event
          + Create-Input-Repeat-Request
          + Get-Next-Event-From-Queue
    (--) Output                             -> Getting-Event
          + Create-Output-Request
          + Get-Next-Event-From-Queue
    (--) Connect                            -> Getting-Event
          + Create-Connect-Request
          + Get-Next-Event-From-Queue
    (--) Flush                              -> Getting-Event
          + Flush-Socket-Requests
          + Get-Next-Event-From-Queue
    (--) Timeout                            -> Getting-Event
          + Get-Next-Event-From-Queue
    (--) Invalid                            -> Getting-Event
          + Get-Next-Event-From-Queue
    (--) Empty                              -> Socket-Activity
          + Check-For-Expired-Requests
          + Wait-For-Socket-Activity
          + Check-First-Socket-Activity
    (--) No-Requests                        -> Getting-Event
          + Send-Timeout-Event-To-Self
    (--) No-Activity                        -> Getting-Event
          + Send-Timeout-Event-To-Self

Socket-Activity:
    (--) Read                               -> After-Reading
          + Read-Data-From-Socket
    (--) Write                              -> After-Writing
          + Write-Data-To-Socket
    (--) Input                              -> Socket-Activity
          + Signal-Socket-Ready-For-Input
          + Check-Next-Socket-Activity
    (--) Output                             -> Socket-Activity
          + Signal-Socket-Ready-For-Output
          + Check-Next-Socket-Activity
    (--) Error                              -> Socket-Activity
          + Signal-Socket-Error
          + Check-Next-Socket-Activity
    (--) Finished                           -> Getting-Event
          + Send-Timeout-Event-To-Self

After-Reading:
    (--) Incomplete                         -> Socket-Activity
          + Check-Next-Socket-Activity
    (--) Finished                           -> Socket-Activity
          + Signal-Read-Complete
          + Check-Next-Socket-Activity
    (--) Closed                             -> Socket-Activity
          + Signal-Read-Closed
          + Check-Next-Socket-Activity
    (--) Error                              -> Socket-Activity
          + Signal-Socket-Error
          + Check-Next-Socket-Activity

After-Writing:
    (--) Incomplete                         -> Socket-Activity
          + Check-Next-Socket-Activity
    (--) Finished                           -> Socket-Activity
          + Signal-Write-Complete
          + Check-Next-Socket-Activity
    (--) Closed                             -> Socket-Activity
          + Signal-Write-Closed
          + Check-Next-Socket-Activity
    (--) Error                              -> Socket-Activity
          + Signal-Socket-Error
          + Check-Next-Socket-Activity

Defaults:
    (--) Exception                          ->
          + Destroy-All-Requests
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Destroy-All-Requests
          + Terminate-The-Thread
    (--) $other                             ->
          +
