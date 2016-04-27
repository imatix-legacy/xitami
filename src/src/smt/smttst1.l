!----------------------------------------------------------------------------
!   Name:       smttst1.l
!   Title:      Test program 1 - tests timer functions
!   Package:    Libero SMT 2.x
!
!   Written:    96/07/03  iMatix SMT kernel team <smt@imatix.com>
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
    (--) Ok                                 -> Waiting-Tick
          + Set-Clock-Ticking
    (--) Error                              ->
          + Terminate-The-Thread

Waiting-Tick:
    (--) Alarm                              -> Waiting-Tick
          +

Defaults:
    (--) Error                              ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread
