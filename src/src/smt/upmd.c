/*  ----------------------------------------------------------------<Prolog>-
    Name:       upmd.c
    Title:      SMT UPM server
    Package:    Libero/SMT Kernel 2.x

    Written:    96/09/06  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Handles the UPM protocol on port 5050.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smtupm.h"                     /*  SMT UPM definitions              */

int
main (int argc, char *argv [])
{
#if 0
    enable_trace ();
    set_trace_file ("trace", 'w');
    smtsock_trace (TRUE);               /*  Set socket trace options         */
#endif
    smt_init ();                        /*  Initialise SMT kernel            */
    smtupmd_init ("upm", SMT_UPM_PORT); /*  Initialise UPM server agent      */
    smt_exec_full ();                   /*  Run until completed              */
    smt_term ();                        /*  Shut-down SMT kernel             */

    mem_assert ();
    return (0);
}
