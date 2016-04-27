!-------------------------------------------------------------------<Prolog>-
!   Name:       sflxmll.l
!   Title:      Dialog for XML loader function
!   Package:    Standard Function Library (SFL)
!
!   Written:    98/03/15  iMatix SFL project team <sfl@imatix.com>
!   Revised:    98/12/04
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SFL License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!------------------------------------------------------------------</Prolog>-*/

-source=sflxmll

After-Init:
    (--) Ok                                 -> Getting-Item
          + Open-XML-File
          + Initialise-XML-Tree
          + Get-Next-Char

Getting-Item:
    (--) Open                               -> Getting-Tag
          + Get-Next-Token
    (--) Char                               -> Getting-Item
          + Confirm-Item-Open
          + Collect-Item-Value
          + Get-Next-Char
    (--) End-Of-File                        ->
          + Confirm-All-Items-Closed
          + Close-XML-File
          + Return-Success-Feedback
          + Terminate-The-Program

Getting-Tag:
    (--) Name                               -> Getting-Attr
          + Attach-New-Item
          + Get-Next-Token
    (--) Slash                              -> Getting-Item
          + Expect-Name
          + Confirm-Item-Name
          + Close-The-Item
          + Expect-Close
          + Get-Next-Char
    (--) Comment                            -> Getting-Item
          + Skip-Rest-Of-Comment
          + Expect-Close
          + Get-Next-Char
    (--) Header                             -> Getting-Item
          + Skip-Rest-Of-Header
          + Expect-Close
          + Get-Next-Char

Getting-Attr:
    (--) Name                               -> Getting-Attr
          + Expect-Equals-Token
          + Expect-Literal
          + Attach-New-Attribute
          + Free-Literal
          + Get-Next-Token
    (--) Close                              -> Getting-Item
          + Get-Next-Char
    (--) Slash                              -> Getting-Item
          + Expect-Close
          + Close-The-Item
          + Get-Next-Char

Defaults:
    (--) Option                             ->
          + Process-Option-Value
          + Get-Next-Token
    (--) Error                              ->
          + Close-XML-File
          + Free-Partial-XML-Tree
          + Return-Error-Feedback
          + Terminate-The-Program
    (--) $other                             ->
          + Unexpected-Token-Error
