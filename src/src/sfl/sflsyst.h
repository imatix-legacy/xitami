/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflsyst.h
    Title:      System-level functions (assertions,...)
    Package:    Standard Function Library (SFL)

    Written:    97/04/13  iMatix SFL project team <sfl@imatix.com>
    Revised:    98/12/22

    Synopsis:   Provides miscellaneous system-level functions.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef SFLSYST_INCLUDED               /*  Allow multiple inclusions        */
#define SFLSYST_INCLUDED


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

void  sys_assert  (const char *filename, unsigned line_number);
char *sys_name    (void);

#ifdef __cplusplus
}
#endif

#endif
