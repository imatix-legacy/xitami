!----------------------------------------------------------------------------
!   Name:       xierror.l
!   Title:      Dialog for Xitami error simulation WSX agent
!   Package:    Xitami
!
!   Written:    97/11/30  Pieter Hintjens <ph@imatix.com>
!   Revised:    97/12/01  Pieter Hintjens <ph@imatix.com>
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c

After-Init:
    (--) Ok                                 -> Expect-Request
          +

Expect-Request:
    (--) Request                            -> Have-Request
          + Decode-Wsx-Request

Have-Request:
    (--) Ok                                 -> Expect-Request
          + Reply-To-Wsx-Request

Defaults:
    (--) Exception                          -> Expect-Request
          +
    (--) Shutdown                           ->
          + Terminate-The-Thread
