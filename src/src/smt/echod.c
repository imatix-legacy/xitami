/*  ----------------------------------------------------------------<Prolog>-
    Name:       echod.c
    Title:      SMT echo daemon example
    Package:    Libero/SMT Kernel 2.x

    Written:    96/06/19  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Handles the TCP/IP echo protocol on port 7.  You can pass
                an optional numeric argument; this is used as the port base.
                I.e. echod 8000 opens port 8007.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"                        /*  SFL library header file          */
#include "smtlib.h"                     /*  SMT kernel functions             */
#include "smtdefn.h"                    /*  SMT agents                       */

int
main (int argc, char *argv [])
{
    if (argc > 1)                       /*  Use port base if specified       */
        ip_portbase = atoi (argv [1]);

    smt_init ();                        /*  Initialise SMT kernel            */
    smtecho_init ();                    /*  Initialise echo agent            */
    smt_exec_full ();                   /*  Run until completed              */
    smt_term ();                        /*  Shut-down SMT kernel             */

    printf ("Allocs=%ld frees=%ld\n", mem_allocs (), mem_frees ());
    mem_assert ();
    return (0);
}
