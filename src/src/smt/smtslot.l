!----------------------------------------------------------------------------
!   Name:       smtslot.l
!   Title:      Dialog for SMT time slot agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/09/30  iMatix SMT kernel team <smt@imatix.com>
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
    (--) Ok                                 -> Expect-Specify
          +
    (--) Error                              ->
          + Terminate-The-Thread

Expect-Specify:
    (--) Specify                            -> Expect-Specify
          + Store-Time-Slot-Specification
    (--) On                                 -> Switched-On
          + Rebuild-Time-Slots-If-New-Day
          + Wait-For-Timer-Tick
    (--) Off                                -> Switched-Off
          + Rebuild-Time-Slots-If-New-Day
          + Wait-For-Timer-Tick

Switched-On:
    (--) Tick                               -> Switched-On
          + Rebuild-Time-Slots-If-New-Day
          + Check-If-Time-To-Switch-Off
          + Wait-For-Timer-Tick

Switched-Off:
    (--) Tick                               -> Switched-Off
          + Rebuild-Time-Slots-If-New-Day
          + Check-If-Time-To-Switch-On
          + Wait-For-Timer-Tick

Defaults:
    (--) Reset                              ->
          + Reset-All-Time-Slots
    (--) Specify                            -> Expect-Specify
          + Store-Time-Slot-Specification
    (--) Off                                -> Switched-Off
          + Signal-Switch-Off-Now
          + Wait-For-Timer-Tick
    (--) On                                 -> Switched-On
          + Signal-Switch-On-Now
          + Wait-For-Timer-Tick
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread
    (--) Finish                             ->
          + Terminate-The-Thread
