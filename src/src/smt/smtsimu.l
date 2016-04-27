!----------------------------------------------------------------------------
!   Name:       smtsimu.l
!   Title:      Dialog for SMT network delay simulator
!   Package:    Libero SMT 2.x
!
!   Written:    96/11/28  iMatix SMT kernel team <smt@imatix.com>
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
    (--) Ok                                 -> Getting-Event
          +
    (--) Error                              ->
          + Terminate-The-Thread

Getting-Event:
    (--) Alarm                              -> Getting-Event
          + Make-Socket-Call
          + Get-Next-Event-From-Queue

Defaults:
    (--) Shutdown                           ->
          + Terminate-The-Thread
