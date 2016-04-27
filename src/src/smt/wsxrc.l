!=============================================================================
!
!   wsxrc.l     WSX resource compiler
!
!   Written:    98/08/14  Xitami Team <xitami@imatix.com>
!   Revised:    98/08/14  Xitami Team <xitami@imatix.com>
!
!   Copyright:  Copyright (c) 1998-99 iMatix Corporation
!
!   This software is copyright (c) 1996-98 iMatix.  All rights reserved.
!   Use and distribution of this software, documentation, executables,
!   source files, and object files is only permitted in the context of a
!   current License Agreement between the user and iMatix.
!=============================================================================
-schema=lrschema.pl
-idle

After-Init:
    (--) Ok                                 -> Have-Input
          + Initialise-Program-Data
          + Load-Xitami-Mime-Types
          + Parse-Argument-Values
          + Open-Output-File
          + Generate-Output-Header
          + Get-Next-Input-File
    (--) Error                              ->
          + Terminate-The-Program

Have-Input:
    (--) Ok                                 -> Have-Input
          + Load-Input-File-Data
          + Generate-Resource-Item
          + Get-Next-Input-File
    (--) Finished                           ->
          + Generate-Output-Footer
          + Close-Output-File
          + Terminate-The-Program

Defaults:
    (--) Exception                          ->
          + Terminate-The-Program
