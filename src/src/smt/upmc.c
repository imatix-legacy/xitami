/*  ----------------------------------------------------------------<Prolog>-
    Name:       upmc.c
    Title:      UPM client main program
    Package:    Libero/SMT Kernel 2.x

    Written:    96/09/06  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Provides a client interface to the UPM server.

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
    int
        argn;
    static char
        args [LINE_MAX];

    strclr (args);
    for (argn = 1; argn < argc; argn++)
      {
        strcat (args, " ");
        strcat (args, argv [argn]);
      }

    smt_init ();                        /*  Initialise SMT kernel            */
    smtupmc_init (args, SMT_UPM_PORT);  /*  Initialise UPM client agent      */
    smt_exec_full ();                   /*  Run until completed              */
    smt_term ();                        /*  Shut-down SMT kernel             */
    mem_assert ();                      /*  Assert memory is clean           */
    return (0);
}
