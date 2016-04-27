!----------------------------------------------------------------------------
!   Name:       smtoper.l
!   Title:      Dialog for SMT operator agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/06/16  iMatix SMT kernel team <smt@imatix.com>
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
          + Enable-Console-Messages
    (--) Error                              ->
          + Terminate-The-Thread

Expect-Event:
    (--) Log                                -> Expect-Event
          + Use-Specified-Log-Queue
    (--) Error                              -> Expect-Event
          + Signal-Error-Message
    (--) Warning                            -> Expect-Event
          + Signal-Warning-Message
    (--) Info                               -> Expect-Event
          + Signal-Info-Message
    (--) Enable                             -> Expect-Event
          + Enable-Console-Messages
    (--) Disable                            -> Expect-Event
          + Disable-Console-Messages

Defaults:
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Signal-Shutdown-In-Progress
    (--) $other                             ->
          +
