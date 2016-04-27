/*  ----------------------------------------------------------------<Prolog>-
    Name:       smttst2.c                                                    *
    Title:      Tests time slot functions
    Package:    Libero/SMT Kernel 2.x

    Written:    96/09/30  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Tests the SMTSLOT agent.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME      "smttst2"       /*  Our public name                  */
#define SINGLE_THREADED TRUE


/*- Function prototypes -----------------------------------------------------*/

static char *time_str         (void);


/*- Global variables used in this source file only --------------------------*/

static QID
    slotq;                              /*  Operator console event queue     */

static byte
    msg_body [LINE_MAX];                /*  Message sent to timer agent      */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_writed       */
    msg = { LINE_MAX, msg_body };


#include "smttst2.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int smttst2_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "smttst2.i"                 /*  Include dialog interpreter       */

    /*  Declare all methods here, with corresponding internal events         */
    /*                      Method name  Event value        Priority         */
    method_declare (agent, "SHUTDOWN",   shutdown_event,    SMT_PRIORITY_MAX);
    method_declare (agent, "SWITCH_ON",  switch_on_event,   0);
    method_declare (agent, "SWITCH_OFF", switch_off_event,  0);

    /*  Create initial thread - all threads are unnamed                      */
    thread_create (AGENT_NAME, "");

    /*  Ensure that slot agent is running, else start it up                  */
    smtslot_init ();
    thread = thread_create (SMT_SLOT, "");
    slotq  = thread-> queue-> qid;

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    the_next_event = ok_event;
}


/***********************   SEND TIME SLOT SPECIFIERS   ***********************/

MODULE send_time_slot_specifiers (THREAD *thread)
{
    msg_size = exdr_writed (&msg, SMT_SLOT_SPEC, "Tue 22:10-23");
    event_send (&slotq, &thread-> queue-> qid, "SPECIFY", msg_body, msg_size,
                NULL, NULL, NULL, 0);

    msg_size = exdr_writed (&msg, SMT_SLOT_SPEC, "Mon 6:50-9 12:00-15");
    event_send (&slotq, &thread-> queue-> qid, "SPECIFY", msg_body, msg_size,
                NULL, NULL, NULL, 0);

    msg_size = exdr_writed (&msg, SMT_SLOT_SPEC, "Thu 12:30-20:00");
    event_send (&slotq, &thread-> queue-> qid, "SPECIFY", msg_body, msg_size,
                NULL, NULL, NULL, 0);
}


/*************************   SEND TIME SWITCHED OFF   ************************/

MODULE send_time_switched_off (THREAD *thread)
{
    SEND (&slotq, "OFF", "");
}


/***************************   SIGNAL SWITCHED ON   **************************/

MODULE signal_switched_on (THREAD *thread)
{
    printf ("%s: +++ ON\n", time_str ());
}


/*  -------------------------------------------------------------------------
 *  time_str
 *
 *  Returns the current date and time formatted as: "yy/mm/dd hh:mm:ss".
 *  The formatted time is in a static string that each call overwrites.
 */

static char *
time_str (void)
{
    static char
        formatted_time [18];
    time_t
        time_secs;
    struct tm
        *time_struct;

    time_secs   = time (NULL);
    time_struct = localtime (&time_secs);

    sprintf (formatted_time, "%2d/%02d/%02d %2d:%02d:%02d",
                              time_struct-> tm_year % 100,
                              time_struct-> tm_mon + 1,
                              time_struct-> tm_mday,
                              time_struct-> tm_hour,
                              time_struct-> tm_min,
                              time_struct-> tm_sec);
    return (formatted_time);
}


/**************************   SIGNAL SWITCHED OFF   **************************/

MODULE signal_switched_off (THREAD *thread)
{
    printf ("%s: --- OFF\n", time_str ());
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    the_next_event = terminate_event;
}
