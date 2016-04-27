!----------------------------------------------------------------------------
!   Name:       smttst2.l
!   Title:      Test program 2 - tests time slot functions
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
-anim

After-Init:
    (--) Ok                                 -> Getting-Event
          + Send-Time-Slot-Specifiers
          + Send-Time-Switched-Off
    (--) Error                              ->
          + Terminate-The-Thread

Getting-Event:
    (--) Switch-On                          -> Getting-Event
          + Signal-Switched-On
    (--) Switch-Off                         -> Getting-Event
          + Signal-Switched-Off

Defaults:
    (--) Shutdown                           ->
          + Terminate-The-Thread
