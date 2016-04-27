/*  ----------------------------------------------------------------<Prolog>-
    Name:       smtoper.c
    Title:      SMT Operator agent
    Package:    Libero/SMT Kernel 2.x

    Written:    96/06/16  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Sends error or warning messages to the system operator.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME      SMT_OPERATOR    /*  Our public name                  */
#define SINGLE_THREADED TRUE            /*  Single-threaded agent            */


/*- Function prototypes -----------------------------------------------------*/

static void  send_buffer      (void);


/*- Global variables used in this source file only --------------------------*/

static QID
    logq,                               /*  Logging agent event queue        */
    *logq_ptr = NULL;                   /*    and its address, maybe         */

static Bool
    console_enabled = TRUE;             /*  Basic console on/off switch      */

static char
    buffer [LINE_MAX];                  /*  Formatted output line            */


#include "smtoper.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

/*  ---------------------------------------------------------------------[<]-
    Function: smtoper_init

    Synopsis: Initialises the SMT operator agent. Returns 0 if initialised
    okay, -1 if there was an error.  The operator agent writes messages to
    the standard error device.  More sophisticated implementations could
    send messages to consoles.  Creates one unnamed thread automatically.
    Supports these public methods:
    <Table>
    ERROR       Handle event as a serious error message.
    WARNING     Handle event as a warning message.
    INFO        Handle event as an information message.
    LOG         Send output to specified SMTLOG thread.
    DISABLE     Console ignores all messages.
    ENABLE      Console handles messages (default).
    </Table>
    Does not send reply events.
    ---------------------------------------------------------------------[>]-*/

int
smtoper_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle for initial thread        */

#   include "smtoper.i"                 /*  Include dialog interpreter       */

    /*  We give this agent a high priority, so that we get to see messages   */
    /*  and errors as soon as possible.                                      */
    agent-> priority = SMT_PRIORITY_HIGH;

    /*                      Method name     Event value      Priority        */
    /*  Shutdown event comes from Kernel, normal priority so we can show     */
    /*  incoming messages before we shut down.                               */
    method_declare (agent, "SHUTDOWN",      shutdown_event,  0);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "LOG",           log_event,       0);
    method_declare (agent, "ERROR",         error_event,     0);
    method_declare (agent, "WARNING",       warning_event,   0);
    method_declare (agent, "INFO",          info_event,      0);
    method_declare (agent, "DISABLE",       disable_event,   0);
    method_declare (agent, "ENABLE",        enable_event,    0);

    /*  Create initial, unnamed thread                                       */
    thread = thread_create (AGENT_NAME, "");
    smt_set_console (&thread-> queue-> qid);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    /*  Tell sflcons.c that we want date/time prefix on output               */
    console_set_mode (CONSOLE_DATETIME);
    the_next_event = ok_event;
}


/************************   USE SPECIFIED LOG QUEUE   ************************/

MODULE use_specified_log_queue (THREAD *thread)
{
    THREAD
        *log_thread;

    /*  Look for logging thread with specified name; if found, take that
        thread's queue and save it.  All messages will now go there...       */

    log_thread = thread_lookup (SMT_LOGGING, (char *) thread-> event-> body);
    if (log_thread)
      {
        logq = log_thread-> queue-> qid;
        logq_ptr = &logq;
      }
}


/**************************   SIGNAL ERROR MESSAGE   *************************/

MODULE signal_error_message (THREAD *thread)
{
    memcpy (buffer, (char *) thread-> event-> body,
                             thread-> event-> body_size);
    buffer [thread-> event-> body_size] = '\0';
    send_buffer ();
}


static void
send_buffer (void)
{
    if (console_enabled)
      {
        /*  Send to log file if so requested                                 */
        if (logq_ptr)
            SEND (&logq, "PUT", buffer);

        /*  And to console output in any case                                */
        coputs (buffer);
      }
}


/**************************   SIGNAL INFO MESSAGE   **************************/

MODULE signal_info_message (THREAD *thread)
{
    signal_error_message (thread);
}


/*************************   SIGNAL WARNING MESSAGE   ************************/

MODULE signal_warning_message (THREAD *thread)
{
    signal_error_message (thread);
}


/************************   DISABLE CONSOLE MESSAGES   ***********************/

MODULE disable_console_messages (THREAD *thread)
{
    console_enabled = FALSE;            /*  Ignore all messages              */
}


/************************   ENABLE CONSOLE MESSAGES   ************************/

MODULE enable_console_messages (THREAD *thread)
{
    console_enabled = TRUE;             /*  Handle messages                  */
}


/**********************   SIGNAL SHUTDOWN IN PROGRESS   **********************/

MODULE signal_shutdown_in_progress (THREAD *thread)
{
    char
        *message;
    word
        signal_value;                   /*  Signal that caused shutdown      */

    exdr_read ((byte *) thread-> event-> body, SMT_SHUTDOWN, &signal_value);
    switch (signal_value)
      {
        case SMT_SIGNAL_INT:  message = "-- interrupted";        break;
        case SMT_SIGNAL_TERM: message = "-- terminated";         break;
        case SMT_SIGNAL_SEGV: message = "-- segment violation";  break;
        case SMT_SIGNAL_USER: message = NULL;                    break;
        default:              message = "-- unknown signal";     break;
      }
    if (message)
      {
        strcpy (buffer, message);
        send_buffer ();
      }
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    the_next_event = terminate_event;
}
