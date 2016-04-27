/*  ----------------------------------------------------------------<Prolog>-
    Name:       tstrdns.c
    Title:      Get Host name from a DNS server
    Package:    Libero SMT 2.x

    Written:    97/10/12  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/12/23

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"                        /*  SFL library header file          */
#include "smtlib.h"                     /*  SMT kernel functions             */
#include "smtdefn.h"                    /*  SMT agents                       */

int smttst3_init (int argc, char *argv []);

int    argc;
char **argv;

int
main (int p_argc, char *p_argv [])
{
    argc = p_argc;
    argv = p_argv;

    smt_init ();                        /*  Initialise SMT kernel            */
    smttst3_init (argc, argv);           /*  Initialise test DNS agent        */
    smt_exec_full ();                   /*  Run until completed              */
    smt_term ();                        /*  Shut-down SMT kernel             */

    mem_assert ();
    return (0);
}
