/*  ----------------------------------------------------------------<Prolog>-
    Name:       tsttime.c
    Title:      SMT timer test program
    Package:    Libero/SMT Kernel 2.x

    Written:    96/07/03  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Tests the timer functions, using the smttst1 agent.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"                        /*  SFL library header file          */
#include "smtlib.h"                     /*  SMT kernel functions             */

int  smttst1_init    (void);            /*  Test agent                       */

int
main (int argc, char *argv [])
{
    AGENT *test_agent;

    smt_init ();                        /*  Initialise SMT kernel            */
    smttst1_init ();                    /*  Initialise agent                 */
    test_agent = agent_lookup ("smttst1");
    while (test_agent-> cur_threads > 0)
        smt_exec_full ();               /*  Run until completed              */

    smt_term ();                        /*  Shut-down SMT kernel             */
    printf ("Allocs=%ld frees=%ld\n", mem_allocs (), mem_frees ());
    mem_assert ();
    return (0);
}
