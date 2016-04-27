/*  ----------------------------------------------------------------<Prolog>-
    Name:       smtupm.h
    Title:      The Unattended Process Monitor
    Package:    Libero SMT 2.x

    Written:    96/09/10  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Defines constants, messages, and prototypes for the UPM
                (unattended process monitor) agents.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SMTUPM_INCLUDED                /*  Allow multiple inclusions        */
#define _SMTUPM_INCLUDED


/*---------------------------------------------------------------------------
 *  Function prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif

int  smtupmc_init (char *args, char *port);
int  smtupmd_init (char *inifile, char *port);

#ifdef __cplusplus
}
#endif


/*---------------------------------------------------------------------------
 *  Constants
 */

#define SMT_UPMD        "smtupmd"       /*  Name of UPM daemon agent         */
#define SMT_UPMC        "smtupmc"       /*  Name of UPM client agent         */
#define SMT_UPM_PORT    "5050"          /*  Port for UPM connection          */

/*  Messages (EXDR formatted events)                                         */

#define SMT_UPM_MESSAGE  "ds"
/*  d=message identifier                                                     */
/*  s=message string                                                         */

#define UPM_LIST         100            /*  List processes                   */
#define UPM_HALT         101            /*  Halt UPM and processes           */
#define UPM_START        102            /*  Start-up a process               */
#define UPM_STOP         103            /*  Shut-down a process              */
#define UPM_STATUS       104            /*  Enquire process status           */
#define UPM_READY        200            /*  Reply ready for command          */
#define UPM_ERROR        201            /*  Reply fatal error                */
#define UPM_HALTING      202            /*  Reply halting UPM                */
#define UPM_TASK_ID      203            /*  Reply task name                  */
#define UPM_TASK_OK      204            /*  Reply task status                */
#define UPM_TASK_NF      205            /*  Reply unknown task               */
#define UPM_TASK_RUNNING 206            /*  Reply task is running            */
#define UPM_TASK_STOPPED 207            /*  Reply task is not running        */
#define UPM_START_OK     208            /*  Reply task started ok            */
#define UPM_START_ERROR  209            /*  Reply task could not be started  */
#define UPM_STOP_OK      210            /*  Reply task stopped ok            */
#define UPM_STOP_ERROR   211            /*  Reply task could not be stopped  */

#endif                                  /*  Include smtlib.h                 */
