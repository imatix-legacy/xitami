/*  ----------------------------------------------------------------<Prolog>-
    Name:       smttst1.c                                                    *
    Title:      Tests timer functions
    Package:    Libero/SMT Kernel 2.x

    Written:    96/07/23  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Sets a clock ticking every second.  To see the return
                messages, compile this program with animation.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME   "smttst1"          /*  Our public name                  */

typedef struct                          /*  Thread context block:            */
{
    qbyte delay;                        /*    Delay for this thread          */
} TCB;


/*- Function prototypes -----------------------------------------------------*/


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    console,                            /*  Operator console event queue     */
    timer;                              /*  Timer event queue                */

static byte
    msg_body [LINE_MAX];                /*  Message sent to timer agent      */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_writed       */
    msg = { LINE_MAX, msg_body };


#include "smttst1.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int smttst1_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "smttst1.i"                 /*  Include dialog interpreter       */

    /*  Declare all methods here, with corresponding internal events         */
    /*                      Method name  Event value      Priority           */
    method_declare (agent, "SHUTDOWN",   shutdown_event,  SMT_PRIORITY_MAX);
    method_declare (agent, "TIME_ALARM", alarm_event,     0);
    method_declare (agent, "TIME_ERROR", error_event,     0);

    /*  Create initial thread - all threads are unnamed                      */
    thread_create (AGENT_NAME, "");

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        console = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that timer is running, else start it up                       */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timer = thread-> queue-> qid;
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = ok_event;
}


/***************************   SET CLOCK TICKING   ***************************/

MODULE set_clock_ticking (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Request clock messages with 1 second delay                           */
    tcb-> delay = 100;                  /*  Measured in centiseconds         */
    msg_size = exdr_writed (&msg, SMT_TIME_CLOCK,
                           (qbyte) 0, tcb-> delay, (word) 0, (word) 5, "TOKEN");
    event_send (
        &timer,                         /*  Send to specified queue          */
        &thread-> queue-> qid,          /*  No queue for reply               */
        "CLOCK",                        /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = terminate_event;
}
