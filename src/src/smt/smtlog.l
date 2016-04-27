!----------------------------------------------------------------------------
!   Name:       smtlog.l
!   Title:      Dialog for SMT logging agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/06/15  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    99/01/06
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c

After-Init:
    (--) Ok                                 -> Before-Opening
          +
    (--) Error                              ->
          + Terminate-The-Thread

Before-Opening:
    (--) Cycle                              -> Before-Opening
          + Cycle-Logfile-If-Exists
    (--) Open                               -> Logfile-Open
          + Open-Thread-Logfile
    (--) Append                             -> Logfile-Open
          + Append-Thread-Logfile
    (--) Plain                              -> Before-Opening
          + Log-File-Output-Is-Plain

Logfile-Open:
    (--) Cycle                              -> Logfile-Open
          + Close-Thread-Logfile
          + Cycle-Logfile-If-Exists
          + Open-Thread-Logfile
    (--) Put                                -> Logfile-Open
          + Write-Text-To-Logfile
    (--) Plain                              -> Logfile-Open
          + Log-File-Output-Is-Plain
    (--) Stamp                              -> Logfile-Open
          + Log-File-Output-Is-Timed
    (--) Close                              -> Before-Opening
          + Close-Thread-Logfile

Defaults:
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          +
    (--) $other                             ->
          +
