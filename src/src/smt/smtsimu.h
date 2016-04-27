/*  ----------------------------------------------------------------<Prolog>-
    Name:       smtsimu.h
    Title:      The Network Delay Simulator
    Package:    Libero SMT 2.x

    Written:    96/11/28  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/12/15

    Synopsis:   Redefines socket functions to pass via smtsimu.  Include
                smtsimu.h after smtlib.h when you want to simulate network
                delays. You do not need to change your program in any other
                way.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SMTSIMU_INCLUDED               /*  Allow multiple inclusions        */
#define _SMTSIMU_INCLUDED

/*---------------------------------------------------------------------------
 *  Define functions to pass through the fake function.  Only some functions
 *  are redirected in this way.
 */

#define smtsock_init        smtsimu_smtsock_init
#define smtsock_trace       smtsimu_smtsock_trace
#define sock_init           smtsimu_sock_init
#define write_UDP           smtsimu_write_UDP

int  smtsimu_init           (void);
int  smtsimu_smtsock_init   (void);
void smtsimu_smtsock_trace  (Bool trace_value);
int  smtsimu_sock_init      (void);
int  smtsimu_write_UDP      (SOCKET handle, void *buffer,
                             size_t length, struct sockaddr_in *sin);

#endif                                  /*  Include smtsimu.h                */
