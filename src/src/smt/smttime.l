!----------------------------------------------------------------------------
!   Name:       smttime.l
!   Title:      Dialog for SMT timer agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/06/23  iMatix SMT kernel team <smt@imatix.com>
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
    (--) Ok                                 -> Expect-Event
          +
    (--) Error                              ->
          + Terminate-The-Thread

Expect-Event:
    (--) Alarm                              -> Expect-Event
          + Flush-Requests-For-Client
          + Create-Single-Alarm-Request
          + Generate-Response-Events
    (--) Wakeup                             -> Expect-Event
          + Flush-Requests-For-Client
          + Create-Single-Wakeup-Request
          + Generate-Response-Events
    (--) Clock                              -> Expect-Event
          + Flush-Requests-For-Client
          + Create-Cycled-Clock-Request
          + Generate-Response-Events
    (--) Flush                              -> Expect-Event
          + Flush-Requests-For-Client
          + Generate-Response-Events
    (--) Timer                              -> Expect-Event
          + Generate-Response-Events

Defaults:
    (--) Exception                          ->
          + Destroy-All-Requests
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Destroy-All-Requests
          + Terminate-The-Thread
    (--) $other                             ->
          +
