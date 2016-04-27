/*  ----------------------------------------------------------------<Prolog>-
    Name:       smtftpd.c
    Title:      SMT FTP data agent
    Package:    Libero SMT 2.x

    Written:    96/07/22  iMatix SMT kernel team <smt@imatix.com>
    Revised:    99/04/23

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smtftpl.h"                    /*  SMT FTP  declaration             */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME     "smtftpd"        /*  Our public name                  */

#define PUT_FILE_MODE     1
#define GET_FILE_MODE     2
#define APPEND_FILE_MODE  3
#define PASSIVE_MODE      4


typedef struct                          /*  Thread context block:            */
{
    sock_t
        handle;                         /*    Handle for i/o                 */
    int
        transfer_type;                  /*    Type of transfer (PUT, GET ... */
    event_t
        thread_type;                    /*    Thread type indicator          */
    QID
        reply_to;                       /*    Message Queue to reply         */
    FTP_DATA_CTX
        ftp_data;                       /*    FTP data context               */
} TCB;


/*- Function prototypes -----------------------------------------------------*/

local create_child (THREAD *thread, char *event_name, event_t type);


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread contect block     */
static QID
    operq,                              /*  Operator console event queue     */
    sockq,                              /*  Socket agent event queue         */
    timeq,                              /*  Timer agent event queue          */
    tranq;                              /*  Transfer agent event queue       */
static SYMTAB
    *pasv_port;                         /*  Table of passive ports used      */


#include "smtftpd.d"                    /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

/*  ---------------------------------------------------------------------[<]-
    Function: smtftpd_init

    Synopsis: Initialises the FTP data agent.  Returns 0 if initialised
    okay, -1 if there was an error.
    ---------------------------------------------------------------------[>]-*/

int smtftpd_init (void)
{
    AGENT
        *agent;                         /*  Handle for our agent             */
    THREAD
        *thread;                        /*  Handle to various threads        */
#   include "smtftpd.i"                 /*  Include dialog interpreter       */

    /*                      Method name      Event value     Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN", shutdown_event, SMT_PRIORITY_MAX);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",    ok_event,           0);
    method_declare (agent, "SOCK_OUTPUT_OK",   ok_event,           0);
    method_declare (agent, "SOCK_READ_OK",     ok_event,           0);
    method_declare (agent, "SOCK_WRITE_OK",    ok_event,           0);
    method_declare (agent, "SOCK_CLOSED",      sock_closed_event,  0);
    method_declare (agent, "SOCK_ERROR",       sock_error_event,   0);
    method_declare (agent, "SOCK_TIMEOUT",     sock_timeout_event, 0);

    /*  Reply events from transfer agent                                     */
    method_declare (agent, "TRAN_PUTF_OK",     finished_event,
                                               SMT_PRIORITY_HIGH);
    method_declare (agent, "TRAN_GETF_OK",     finished_event,
                                               SMT_PRIORITY_HIGH);
    method_declare (agent, "TRAN_CLOSED",      sock_closed_event,
                                               SMT_PRIORITY_HIGH);
    method_declare (agent, "TRAN_ERROR",       sock_error_event,
                                               SMT_PRIORITY_HIGH);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "FTPD_PASSIVE",     passive_event,
                                               SMT_PRIORITY_LOW);
    method_declare (agent, "FTPD_PUT_FILE",    put_file_event,
                                               SMT_PRIORITY_NORMAL);
    method_declare (agent, "FTPD_GET_FILE",    get_file_event,
                                               SMT_PRIORITY_NORMAL);
    method_declare (agent, "FTPD_APPEND_FILE", append_file_event,
                                               SMT_PRIORITY_NORMAL);
    method_declare (agent, "FTPD_ABORT",       abort_event,
                                               SMT_PRIORITY_HIGH);
    method_declare (agent, "FTPD_CLOSECTRL",   close_control_event,
                                               SMT_PRIORITY_HIGH);

    /*  Private method used to pass initial thread events                    */
    method_declare (agent, "_MASTER",          master_event, 0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that socket i/o agent is running, else start it up            */
    smtsock_init ();
    if ((thread = thread_lookup (SMT_SOCKET, "")) != NULL)
        sockq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that transfer agent is running, else start it up              */
    smttran_init ();
    if ((thread = thread_lookup (SMT_TRANSFER, "")) != NULL)
        tranq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create initial thread to manage master port                          */
    if ((thread = thread_create (AGENT_NAME, "")) != NULL)
      {
        SEND (&thread-> queue-> qid, "_MASTER", "");
        ((TCB *) thread-> tcb)-> thread_type = master_event;
      }
    else
        return (-1);

    pasv_port = sym_create_table ();

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    if (tcb-> thread_type == master_event)
      {
        tcb-> transfer_type = 0;
        ftpd_init (&tcb-> ftp_data);
      }
    tcb-> handle = 0;
}


/**************************   ABORT FILE TRANSFER   **************************/

MODULE abort_file_transfer (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
}


/************************   ACCEPT CLIENT CONNECTION   ***********************/

MODULE accept_client_connection (THREAD *thread)
{
    sock_t
        slave_socket;                   /*  Connected socket                 */

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    slave_socket = accept_socket (tcb-> handle);
    if (slave_socket != INVALID_SOCKET)
      {
        close_socket (tcb-> handle);
        tcb-> handle = slave_socket;
      }
    else
    if (sockerrno != EAGAIN)
        raise_exception (exception_event);
}


/*************************   CHECK CONNECTION TYPE   *************************/

MODULE check_connection_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    the_next_event = (tcb-> ftp_data.passive)? passive_event:
                                               active_event;
}


/***************************   CONNECT TO CLIENT   ***************************/

MODULE connect_to_client (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_connect (
        &sockq,                         /*  Send to specified queue          */
        0,                              /*  Timeout for connect              */
        "TCP",                          /*  Protocol type                    */
        NULL, NULL,                     /*  Host and service by name         */
        tcb-> ftp_data.data_port,       /*  Port value                       */
        tcb-> ftp_data.data_host,       /*  Host address value               */
        0);                             /*  Connection tag, not used         */
}


/***************************   OPEN LISTEN SOCKET   **************************/

MODULE open_listen_socket (THREAD *thread)
{
    static char
        port [10];
    Bool
        next_port = FALSE;
    int
        index = 0;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> transfer_type = 0;
    if (tcb-> ftp_data.data_port > ip_portbase)
        tcb-> ftp_data.data_port -= ip_portbase;

    sprintf (port, "%d", tcb-> ftp_data.data_port);
    if (sym_lookup_symbol (pasv_port, port) == NULL)
      {
        next_port = FALSE;
        tcb-> handle = passive_TCP (port, 5);
        index++;
      }
    else
        next_port = TRUE;

    while (index < 200
    &&    (next_port == TRUE || connect_error () == IP_BINDERROR))
      {
        tcb-> ftp_data.data_port++;     /*  Port in use - try next one       */
        sprintf (port, "%d", tcb-> ftp_data.data_port);
        if (sym_lookup_symbol (pasv_port, port) == NULL)
          {
            next_port = FALSE;
            tcb-> handle = passive_TCP (port, 5);
            index++;
          }
        else
            next_port = TRUE;
      }

    if (tcb-> handle == INVALID_SOCKET || index >= 200)
        tcb-> handle = 0;               /*  0 means 'not open'               */
    else
      {
        tcb-> ftp_data.data_port += ip_portbase;
        sym_assume_symbol (pasv_port, port, port);
      }
    the_next_event  = tcb-> handle? ok_event: error_event;
}


/***************************   SET TRANSFER MODE   ***************************/

MODULE set_transfer_mode (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> transfer_type == PUT_FILE_MODE)
        the_next_event = put_file_mode_event;
    else
    if (tcb-> transfer_type == GET_FILE_MODE)
        the_next_event = get_file_mode_event;
    else
    if (tcb-> transfer_type == APPEND_FILE_MODE)
        the_next_event = append_file_mode_event;
}


/**********************   SIGNAL CONNECTION TO CONTROL   *********************/

MODULE signal_connection_to_control (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&tcb-> reply_to, "FTPD_CONNECTED", "");
}


/************************   SIGNAL END OF TRANSFER   *************************/

MODULE signal_end_of_transfer (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&tcb-> reply_to, "FTPD_END", "");
}


/***********************   SIGNAL ERROR IN TRANSFER   ************************/

MODULE signal_error_in_transfer (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&tcb-> reply_to, "FTPD_ERROR", "");
}


/************************   SIGNAL CONNECTION FAILED   ***********************/

MODULE signal_connection_failed (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&operq, "ERROR", "smtftpd: could not connect to %s:%d",
        sock_ntoa (htonl (tcb-> ftp_data.data_host)),
                          tcb-> ftp_data.data_port);

    SEND (&tcb-> reply_to, "FTPD_ERROR", "");
}


/*************************   WAIT FOR SOCKET INPUT   *************************/

MODULE wait_for_socket_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_input (&sockq, 0, tcb-> handle, 0);
}


/**************************   CREATE CHILD THREAD   **************************/

MODULE create_child_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> transfer_type == PUT_FILE_MODE)
        create_child (thread, "FTPD_PUT_FILE", put_file_event);
    else
    if (tcb-> transfer_type == PASSIVE_MODE)
        create_child (thread, "FTPD_PASSIVE",  passive_event);
    else
    if (tcb-> transfer_type == GET_FILE_MODE)
        create_child (thread, "FTPD_GET_FILE", get_file_event);
    else
    if (tcb-> transfer_type == APPEND_FILE_MODE)
        create_child (thread, "FTPD_APPEND_FILE", append_file_event);
    else
        SEND (&tcb-> reply_to, "FTPD_ERROR", "");
}


local
create_child (
    THREAD  *thread,
    char    *event_name,
    event_t type)
{
    THREAD
        *child;                         /*  Handle to child thread           */
    FTP_DATA_CTX
        *ctx_parent,
        *ctx_child;
    static char
        child_name [20];

    ctx_parent = &((TCB *) thread-> tcb)-> ftp_data;
    sprintf (child_name, "%ld", ctx_parent-> id);

    if ((child = thread_create (AGENT_NAME, child_name)) != NULL)
      {
        event_send (
            &child-> queue-> qid,       /*  Send to child thread queue       */
            &thread-> event-> sender,   /*  Queue for reply                  */
            event_name,                 /*  Name of event to send            */
            thread-> event-> body,      /*  Event body                       */
            thread-> event-> body_size, /*    and size                       */
            NULL, NULL, NULL,           /*  No response events               */
            0);                         /*  No timeout                       */
        ((TCB *) child-> tcb)-> thread_type = type;
        ((TCB *) child-> tcb)-> reply_to = tcb-> reply_to;
        ctx_child = &((TCB *) child-> tcb)-> ftp_data;

        memcpy (ctx_child, ctx_parent, sizeof (FTP_DATA_CTX));
        if (ctx_parent-> file_name)
          {
            ctx_child-> file_name = mem_strdup (ctx_parent-> file_name);
            mem_strfree (&ctx_parent-> file_name);
          }
      }
    else
        SEND (&tcb-> reply_to, "FTPD_ERROR", "");
}


/********************************   GET FILE   *******************************/

MODULE get_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_get_file (&tranq,
                   tcb-> handle,
                   tcb-> ftp_data.file_name,
                   (dbyte) (tcb-> ftp_data.file_type == FTP_TYPE_ASCII? 1: 0),
                   tcb-> ftp_data.file_offset, 0,
                   FALSE);
}


/******************************   APPEND FILE   ******************************/

MODULE append_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_get_file (&tranq,
                   tcb-> handle,
                   tcb-> ftp_data.file_name,
                   (dbyte) (tcb-> ftp_data.file_type == FTP_TYPE_ASCII? 1: 0),
                   tcb-> ftp_data.file_offset, 0,
                   TRUE);
}


/********************************   PUT FILE   *******************************/

MODULE put_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_put_file (&tranq,
                   tcb-> handle,
                   tcb-> ftp_data.file_name,
                   (dbyte) (tcb-> ftp_data.file_type == FTP_TYPE_ASCII? 1: 0),
                   tcb-> ftp_data.file_offset, 0);
}


/***********************   SEND EVENT TO CHILD THREAD   **********************/

MODULE send_event_to_child_thread (THREAD *thread)
{
    long
        id;
    THREAD
        *child;                         /*  Handle to child thread           */
    static char
        child_name [20];

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    exdr_read (thread-> event-> body, "q", &id);
    sprintf (child_name, "%ld", id);
    child = thread_lookup (AGENT_NAME, child_name);
    if (child)
        event_send (
            &child-> queue-> qid,       /*  Send to specified queue          */
            &tcb-> reply_to,            /*  Queue for reply                  */
            thread-> event-> name,      /*  Name of event to send            */
            thread-> event-> body,      /*  Event body and size              */
            thread-> event-> body_size,
            NULL, NULL, NULL,           /*  No response events               */
            0);                         /*  No timeout                       */
}


/***************************   GET MESSAGE ABORT   ***************************/

MODULE get_message_abort (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    exdr_read (thread-> event-> body, SMT_FTPD_ABORT, &tcb-> ftp_data.id);
    tcb-> reply_to = thread-> event-> sender;
}


/**************************   GET MESSAGE GET FILE   *************************/

MODULE get_message_get_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    mem_strfree (&tcb-> ftp_data.file_name);
    exdr_read (thread-> event-> body, SMT_FTPD_GETF,
               &tcb-> ftp_data.id,
               &tcb-> ftp_data.passive,
               &tcb-> ftp_data.file_type,
               &tcb-> ftp_data.file_name,
               &tcb-> ftp_data.file_offset,
               &tcb-> ftp_data.data_host,
               &tcb-> ftp_data.data_port
              );
    if (tcb-> thread_type != passive_event)
        tcb-> reply_to = thread-> event-> sender;
    tcb-> transfer_type = GET_FILE_MODE;
}


/**************************   GET MESSAGE PASSIVE   **************************/

MODULE get_message_passive (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    mem_strfree (&tcb-> ftp_data.file_name);
    exdr_read (thread-> event-> body, SMT_FTPD_PASSIVE, &tcb-> ftp_data.id,
               &tcb-> ftp_data.data_port, &tcb-> ftp_data.data_host);

    tcb-> reply_to         = thread-> event-> sender;
    tcb-> transfer_type    = PASSIVE_MODE;
    tcb-> ftp_data.passive = TRUE;
}


/**************************   GET MESSAGE PUT FILE   *************************/

MODULE get_message_put_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    mem_strfree (&tcb-> ftp_data.file_name);
    exdr_read (thread-> event-> body, SMT_FTPD_PUTF,
               &tcb-> ftp_data.id,
               &tcb-> ftp_data.passive,
               &tcb-> ftp_data.file_type,
               &tcb-> ftp_data.file_name,
               &tcb-> ftp_data.file_offset,
               &tcb-> ftp_data.data_host,
               &tcb-> ftp_data.data_port
              );
    if (tcb-> thread_type != passive_event)
        tcb-> reply_to = thread-> event-> sender;
    tcb-> transfer_type = PUT_FILE_MODE;
}


/************************   GET MESSAGE APPEND FILE   ************************/

MODULE get_message_append_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    mem_strfree (&tcb-> ftp_data.file_name);
    exdr_read (thread-> event-> body, SMT_FTPD_APPEND,
               &tcb-> ftp_data.id,
               &tcb-> ftp_data.passive,
               &tcb-> ftp_data.file_type,
               &tcb-> ftp_data.file_name,
               &tcb-> ftp_data.data_host,
               &tcb-> ftp_data.data_port
              );
    if (tcb-> thread_type != passive_event)
        tcb-> reply_to = thread-> event-> sender;
    tcb-> transfer_type = APPEND_FILE_MODE;
}


/*************************   GET CONNECTION HANDLE   *************************/

MODULE get_connection_handle (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    exdr_read (thread-> event-> body, SMT_SOCK_OK, &tcb-> handle, NULL);
}


/******************************   SIGNAL ERROR   *****************************/

MODULE signal_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&tcb-> reply_to, "FTPD_ERROR", "");
}


/**************************   SIGNAL PASSIVE OPEN   **************************/

MODULE signal_passive_open (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_ftpd_pass_ok (&tcb-> reply_to,
                        tcb-> ftp_data.data_host,
                        tcb-> ftp_data.data_port);
}


/************************   SIGNAL ABORT TO CONTROL   ************************/

MODULE signal_abort_to_control (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&tcb-> reply_to, "FTPD_ABORTED", "");
}


/*************************   CLOSE DATA CONNECTION   *************************/

MODULE close_data_connection (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> handle)
      {
        close_socket (tcb-> handle);
        tcb-> handle = 0;
      }
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    SYMBOL
        *symb_port;
    static char
        port_name [10];

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> handle)
      {
        close_socket (tcb-> handle);
        tcb-> handle = 0;
      }
    ftpd_free (&tcb-> ftp_data);

    if (tcb-> thread_type == master_event)
        sym_delete_table (pasv_port);
    else
    if (tcb-> ftp_data.passive)
      {
        tcb-> ftp_data.data_port -= ip_portbase;
        sprintf (port_name, "%d", tcb-> ftp_data.data_port);
        symb_port = sym_lookup_symbol (pasv_port, port_name);
        if (symb_port)
            sym_delete_symbol (pasv_port, symb_port);
      }
    the_next_event = terminate_event;
}
