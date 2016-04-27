/*  ----------------------------------------------------------------<Prolog>-
    Name:       smttran.c
    Title:      SMT transfer agent
    Package:    Libero/SMT Kernel 2.x

    Written:    96/09/05  iMatix SMT kernel team <smt@imatix.com>
    Revised:    99/08/31

    Synopsis:   Transfers blocks or files via an opened TCP/IP socket.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME   SMT_TRANSFER       /*  Our public name                  */
#define BUFFER_SIZE  32000L             /*  Buffer for file transmission     */

#define FILETYPE_BINARY   0
#define FILETYPE_ASCII    1

typedef struct {                        /*  Thread context block:            */
    event_t thread_type;                /*    Thread type indicator          */
    QID     reply_to;                   /*    Queue to reply to              */
    sock_t  handle;                     /*    Socket i/o handle              */
    char   *filename;                   /*    Filename, if used              */
    qbyte   filesize;                   /*    Total file size                */
    int     stream;                     /*    File i/o handle, if used       */
    qbyte   read_size;                  /*    Read size, 0 = GET             */
    qbyte   write_size;                 /*    Write size, 0 = GET            */
    qbyte   block_size;                 /*    Block size, 0 = GET            */
    char   *block_data;                 /*    Block data, or NULL            */
    char   *block_text;                 /*    Block text data, or NULL       */
    long    start_slice;                /*    Start of slice, if any         */
    long    end_slice;                  /*    End slice, if any              */
    dbyte   filetype;                   /*    Type of file (binary, ascii)   */
    Bool    send_text;                  /*    Do we send block data or text  */
    Bool    append;                     /*    Open for output or append?     */
} TCB;

typedef struct _TRANREQ {               /*  Request descriptor               */
    struct _TRANREQ                     /*                                   */
           *next, *prev;                /*    Doubly-linked list             */
    QID     reply_to;                   /*    Who sent the request event     */
    Bool    sending;                    /*    True=PUT, false=GET            */
    sock_t  handle;                     /*    Socket for output              */
    qbyte   block_size;                 /*    Block size, 0 = GET            */
    char   *block_data;                 /*    Block data, or NULL            */
    Bool    in_header;                  /*    True when doing header         */
    Bool    in_progress;                /*    Are we processing request?     */
    Bool    huge_block;                 /*    Are we using huge blocks?      */
    qbyte   reqid;                      /*    Unique request ID              */
} TRANREQ;


/*- Local function prototypes -----------------------------------------------*/

static TRANREQ *request_create      (THREAD *thread, sock_t handle);
static TRANREQ *request_lookup      (qbyte reqid);
static void     request_destroy     (TRANREQ *request);
static void     signal_fatal_error  (void);
static void     put_request_header  (THREAD *thread, TRANREQ *request);
static void     put_request_body    (THREAD *thread, TRANREQ *request);
static void     get_request_header  (THREAD *thread, TRANREQ *request);
static void     get_request_body    (THREAD *thread, TRANREQ *request);
static void     open_transfer_file  (THREAD *thread, char mode);


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    operq,                              /*  Operator console event queue     */
    timeq,                              /*  Timer agent event queue          */
    sockq;                              /*  Socket agent event queue         */
static NODE
    requests;                           /*  Request list header              */
static int
    fileio_threads = 0;                 /*  Number of child fileio threads   */


#include "smttran.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/


/*  ---------------------------------------------------------------------[<]-
    Function: smttran_init

    Synopsis: Initialises the SMT transfer agent.  Returns 0 if initialised
    okay, -1 if there was an error.  The transfer agent reads and writes
    blocks of data, or complete files, through an open TCP/IP socket.  A
    block of data is sent/received as a two-byte length header followed
    by the data block.  Creates an unnamed thread automatically.  Supports
    these public methods:
    <Table>
    PUT_BLOCK   Write a length-specified block to a socket (< 64k)
    GET_BLOCK   Read a length-specified block from a socket (< 64k)
    PUT_HUGE    Write a length-specified block to a socket (< 2Gb)
    GET_HUGE    Read a length-specified block from a socket (< 2Gb)
    PUT_FILE    Write part or all of a file to a socket
    GET_FILE    Read part or all of a file from a socket
    COMMIT      Wait until all transfer requests are finished
    </Table>
    Sends errors to the SMTOPER agent; see the doc for reply events.
    ---------------------------------------------------------------------[>]-*/

int
smttran_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to various threads        */
#   include "smttran.i"                 /*  Include dialog interpreter       */

    /*                      Method name      Event value      Priority        */
    /*  Shutdown event comes from Kernel                                      */
    method_declare (agent, "SHUTDOWN",       shutdown_event,  SMT_PRIORITY_MAX);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",  ok_event,          0);
    method_declare (agent, "SOCK_OUTPUT_OK", ok_event,          0);
    method_declare (agent, "SOCK_READ_OK",   read_ok_event,     0);
    method_declare (agent, "SOCK_WRITE_OK",  write_ok_event,    0);
    method_declare (agent, "SOCK_READH_OK",  readh_ok_event,    0);
    method_declare (agent, "SOCK_WRITEH_OK", writeh_ok_event,   0);
    method_declare (agent, "SOCK_CLOSED",    sock_closed_event, 0);
    method_declare (agent, "SOCK_ERROR",     sock_error_event,  0);
    method_declare (agent, "SOCK_TIMEOUT",   sock_error_event,  0);

    /*  Reply events from timer agent                                        */
    method_declare (agent, "TIME_ALARM",     commit_event,      0);
    method_declare (agent, "TIME_ERROR",     error_event,       0);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "PUT_BLOCK",  put_block_event,  SMT_PRIORITY_MIN);
    method_declare (agent, "GET_BLOCK",  get_block_event,  SMT_PRIORITY_MIN);
    method_declare (agent, "PUT_HUGE",   put_huge_event,   SMT_PRIORITY_MIN);
    method_declare (agent, "GET_HUGE",   get_huge_event,   SMT_PRIORITY_MIN);
    method_declare (agent, "PUT_FILE",   put_file_event,   0);
    method_declare (agent, "GET_FILE",   get_file_event,   0);
    method_declare (agent, "COMMIT",     commit_event,     SMT_PRIORITY_MIN);

    /*  Private method used to pass initial thread events                    */
    method_declare (agent, "_MASTER",   master_event,    0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that socket agent is running, else start it up                */
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

    /*  Create initial thread to manage master thread                        */
    if ((thread = thread_create (AGENT_NAME, "")) != NULL)
      {
        SEND (&thread-> queue-> qid, "_MASTER", "");
        ((TCB *) thread-> tcb)-> thread_type = master_event;
        ((TCB *) thread-> tcb)-> filename    = NULL;
      }
    else
        return (-1);

    /*  Clear & prepare request queue                                        */
    node_reset (&requests);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    /*  We don't set the_next_event because we expect an argument event      */
    /*  to supply these.                                                     */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> stream     = 0;
    tcb-> block_data = NULL;
    tcb-> block_text = NULL;
    tcb-> send_text  = FALSE;
}


/***********************   GET NEXT EVENT FROM QUEUE   ***********************/

MODULE get_next_event_from_queue (THREAD *thread)
{
    AGENT   *agent;                     /*  This agent                       */
    QUEUE   *queue;                     /*  Thread's event queue             */
    EVENT   *event;                     /*  Event information block          */
    METHOD  *method;                    /*  Method information block         */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get next event off queue                                             */
    queue = thread-> queue;
    agent = queue-> agent;
    event = event_iterate (queue, NULL);
    if (event)
      {
        method = method_lookup (agent, event-> name);
        if (method == NULL)             /*  Not a method we accept           */
            event_reject (queue, event);
        else
          {
            if (thread-> event)         /*  If thread was sitting on an      */
              {                         /*    event, release it              */
                event_destroy (thread-> event);
                thread-> event = NULL;
              }
            /*  Get event off queue; it now belongs to the thread            */
            thread-> event = event_accept (queue, event);
            the_next_event = method-> event_number;
          }
      }
    else
        the_next_event = empty_event;
}


/************************   CREATE PUT BLOCK REQUEST   ***********************/

MODULE create_put_block_request (THREAD *thread)
{
    dbyte
        block_size;                     /*  Size of data block to write      */
    char
        *block_data = NULL;             /*  Block of data to write           */
    sock_t
        handle;                         /*  Socket for output                */
    TRANREQ
        *request;                       /*  Newly-created request            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_TRAN_PUTB,
               &handle, &block_size, &block_data);

    if ((request = request_create (thread, handle)) != NULL)
      {
        request-> block_size = block_size;
        request-> block_data = block_data;
        request-> sending    = TRUE;
      }
}


/*  -------------------------------------------------------------------------
 *  request_create
 *
 *  Creates a new request, and initialises it to empty.
 */

static TRANREQ *
request_create (THREAD *thread, sock_t handle)
{
    static qbyte
        reqid = 0;                      /*  Cyclic request id                */
    TRANREQ
        *request;                       /*  Request we create                */

    request = node_create (requests.prev, sizeof (TRANREQ));
    if (request)
      {
        /*  Initialise the request with default values                       */
        request-> reply_to    = thread-> event-> sender;
        request-> handle      = handle;
        request-> block_size  = 0;
        request-> block_data  = NULL;
        request-> in_header   = TRUE;
        request-> in_progress = FALSE;
        request-> reqid       = reqid++;
        request-> huge_block  = FALSE;
      }
    return (request);
}


/************************   CREATE GET BLOCK REQUEST   ***********************/

MODULE create_get_block_request (THREAD *thread)
{
    sock_t
        handle;                         /*  Socket for output                */
    TRANREQ
        *request;                       /*  Newly-created request            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_TRAN_GETB, &handle);
    if ((request = request_create (thread, handle)) != NULL)
        request-> sending = FALSE;
}


/************************   CREATE PUT HUGE REQUEST   ************************/

MODULE create_put_huge_request (THREAD *thread)
{
    qbyte
        block_size;                     /*  Size of data block to write      */
    char
        *block_data = NULL;             /*  Block of data to write           */
    sock_t
        handle;                         /*  Socket for output                */
    TRANREQ
        *request;                       /*  Newly-created request            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_TRAN_PUTH,
               &handle, &block_size, &block_data);

    if ((request = request_create (thread, handle)) != NULL)
      {
        request-> block_size = block_size;
        request-> block_data = block_data;
        request-> sending    = TRUE;
        request-> huge_block = TRUE;
      }
}


/************************   CREATE GET HUGE REQUEST   ************************/

MODULE create_get_huge_request (THREAD *thread)
{
    sock_t
        handle;                         /*  Socket for output                */
    TRANREQ
        *request;                       /*  Newly-created request            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_TRAN_GETH, &handle);
    if ((request = request_create (thread, handle)) != NULL)
      {
        request-> sending    = FALSE;
        request-> huge_block = TRUE;
      }
}


/***********************   PROCESS TRANSFER REQUESTS   ***********************/

MODULE process_transfer_requests (THREAD *thread)
{
    TRANREQ
        *request;                       /*  Request we process               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    for (request  = requests.next;
         request != (TRANREQ *) &requests;
         request  = request-> next)
      {
        if (request-> in_progress)
            continue;                   /*  Ignore requests in progress      */

        /*  Start processing the request                                     */
        request-> in_progress = TRUE;

        if (request-> sending)
          {
            /*  Send header and body one after the other                     */
            put_request_header (thread, request);
            put_request_body   (thread, request);
          }
        else                            /*  Otherwise we want GET            */
            if (request-> in_header)
                get_request_header (thread, request);
            else
                get_request_body   (thread, request);
      }
}


static void
put_request_header (THREAD *thread, TRANREQ *request)
{
    dbyte
        dsize;                          /*  Block size in network order      */
    qbyte
        qsize;                          /*  Huge size in network order       */

    /*  Write 2/4-byte block header in network format                        */
    if (request-> huge_block)
      {
        qsize = htonl (request-> block_size);
        send_writeh (&sockq, 0, request-> handle, 4,
                    (byte *) &qsize, request-> reqid);
      }
    else
      {
        dsize = htons ((dbyte) request-> block_size);
        send_write (&sockq, 0, request-> handle, 2,
                   (byte *) &dsize, request-> reqid);
      }
}


static void
put_request_body (THREAD *thread, TRANREQ *request)
{
    if (request-> huge_block)
        send_writeh (
            &sockq,                         /*  Socket agent queue           */
            0,                              /*  Timeout for transmission     */
            request-> handle,               /*  Socket to send to            */
            request-> block_size,           /*  Amount of data to send       */
            (byte *) request-> block_data,  /*  Address of data to send      */
            request-> reqid);               /*  Request tag                  */
    else
        send_write (
            &sockq,
            0,
            request-> handle,
            (dbyte)  request-> block_size,
            (byte *) request-> block_data,
            request-> reqid);
}


static void
get_request_header (THREAD *thread, TRANREQ *request)
{
    if (request-> huge_block)
        send_readh (
            &sockq,                     /*  Socket agent queue               */
            0,                          /*  Timeout for transmission         */
            request-> handle,           /*  Socket to read from              */
            4,                          /*  Max amount of data to read       */
            4,                          /*  Min amount of data to read       */
            request-> reqid);           /*  Request tag                      */
    else
        send_read (
            &sockq,                     /*  Socket agent queue               */
            0,                          /*  Timeout for transmission         */
            request-> handle,           /*  Socket to read from              */
            2,                          /*  Max amount of data to read       */
            2,                          /*  Min amount of data to read       */
            request-> reqid);           /*  Request tag                      */
}


static void
get_request_body (THREAD *thread, TRANREQ *request)
{
    if (request-> huge_block)
        send_readh (
            &sockq,                     /*  Socket agent queue               */
            0,                          /*  Timeout for transmission         */
            request-> handle,           /*  Socket to read from              */
            request-> block_size,       /*  Max amount of data to read       */
            request-> block_size,       /*  Min amount of data to read       */
            request-> reqid);           /*  Request tag                      */
    else
        send_read (
            &sockq,
            0,
            request-> handle,
            (dbyte) request-> block_size,
            (dbyte) request-> block_size,
            request-> reqid);
}


/***********************   UPDATE REQUEST AFTER READ   ***********************/

MODULE update_request_after_read (THREAD *thread)
{
    dbyte
        netsize,                        /*  Block size in network order      */
        *netsize_addr = &netsize;
    qbyte
        reqid;                          /*  Request ID back from SMTSOCK     */
    TRANREQ
        *request;                       /*  Request we process               */
    byte
        *body = NULL;                   /*  Received message body            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up reqid from event body, encoded as SMT_SOCK_READ_OK           */
    exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
               NULL, NULL, NULL, NULL, &reqid);
    if ((request = request_lookup (reqid)) == NULL)
         return;                        /*  Something garbage - ignore it    */

    /*  We either just received the header or the body                       */
    if (request-> in_header)
      {
        /*  Pick up block size from event body encoded as SMT_SOCK_READ_OK   */
        exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
                   NULL, NULL, NULL, &netsize_addr, NULL);
        request-> block_size  = ntohs (netsize);
        request-> in_header   = FALSE;
        request-> in_progress = FALSE;
      }
    else
      {
        /*  Get data from socket agent reply message                         */
        exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
                   NULL, NULL, &request-> block_size, &body, NULL);

        /*  Send it back to the calling program                              */
        send_tran_getb_ok (&request-> reply_to,
                          (dbyte) request-> block_size, body);

        request_destroy (request);
        mem_free (body);
      }
}


/*  Returns in-progress request for handle, or NULL if none found            */

static TRANREQ
*request_lookup (qbyte reqid)
{
    TRANREQ
        *request;                       /*  Request we process               */

    for (request  = requests.next;
         request != (TRANREQ *) &requests;
         request  = request-> next)
      {
        if (request-> reqid == reqid)
            return (request);           /*  We found the request             */
      }
    return (NULL);
}

static void
request_destroy (TRANREQ *request)
{
    mem_free (request-> block_data);
    node_destroy (request);
}


/***********************   UPDATE REQUEST AFTER READH   **********************/

MODULE update_request_after_readh (THREAD *thread)
{
    qbyte
        netsize,                        /*  Block size in network order      */
        *netsize_addr = &netsize,
        reqid;                          /*  Request ID back from SMTSOCK     */
    TRANREQ
        *request;                       /*  Request we process               */
    byte
        *body = NULL;                   /*  Received message body            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up reqid from event body, encoded as SMT_SOCK_READH_OK          */
    exdr_read (thread-> event-> body, SMT_SOCK_READH_OK,
               NULL, NULL, NULL, NULL, &reqid);
    if ((request = request_lookup (reqid)) == NULL)
         return;                        /*  Something garbage - ignore it    */

    /*  We either just received the header or the body                       */
    if (request-> in_header)
      {
        /*  Pick up block size from event body encoded as SMT_SOCK_READH_OK  */
        exdr_read (thread-> event-> body, SMT_SOCK_READH_OK,
                   NULL, NULL, NULL, &netsize_addr, NULL);
        request-> block_size  = ntohl (netsize);
        request-> in_header   = FALSE;
        request-> in_progress = FALSE;
      }
    else
      {
        /*  Get data from socket agent reply message                         */
        exdr_read (thread-> event-> body, SMT_SOCK_READH_OK,
                   NULL, NULL, &request-> block_size, &body, NULL);

        /*  Send it back to the calling program                              */
        send_tran_geth_ok (&request-> reply_to, request-> block_size, body);

        request_destroy (request);
        mem_free (body);
      }
}


/***********************   UPDATE REQUEST AFTER WRITE   **********************/

MODULE update_request_after_write (THREAD *thread)
{
    qbyte
        reqid;                          /*  Request ID back from SMTSOCK     */
    TRANREQ
        *request;                       /*  Request we process               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up reqid from event body, encoded as SMT_SOCK_OK                */
    exdr_read (thread-> event-> body, SMT_SOCK_OK, NULL, &reqid);
    if ((request = request_lookup (reqid)) == NULL)
         return;                        /*  Something garbage - ignore it    */

    /*  We either just sent the header or the body                           */
    if (request-> in_header)
        request-> in_header = FALSE;
    else
      {
        /*  Send confirmation back to the calling program                    */
        send_tran_putb_ok (&request-> reply_to,
                          (dbyte) request-> block_size);
        request_destroy (request);
      }
}


/**********************   UPDATE REQUEST AFTER WRITEH   **********************/

MODULE update_request_after_writeh (THREAD *thread)
{
    qbyte
        reqid;                          /*  Request ID back from SMTSOCK     */
    TRANREQ
        *request;                       /*  Request we process               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up reqid from event body, encoded as SMT_SOCK_OK                */
    exdr_read (thread-> event-> body, SMT_SOCK_OK, NULL, &reqid);
    if ((request = request_lookup (reqid)) == NULL)
         return;                        /*  Something garbage - ignore it    */

    /*  We either just sent the header or the body                           */
    if (request-> in_header)
        request-> in_header = FALSE;
    else
      {
        /*  Send confirmation back to the calling program                    */
        send_tran_puth_ok (&request-> reply_to, request-> block_size);
        request_destroy (request);
      }
}


/**********************   UPDATE REQUEST AFTER CLOSED   **********************/

MODULE update_request_after_closed (THREAD *thread)
{
    sock_t
        handle;                         /*  Socket closed                    */
    qbyte
        reqid;                          /*  Request ID back from SMTSOCK     */
    TRANREQ
        *request;                       /*  Request we process               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up reqid from event body encoded as SMT_SOCK_READ_OK            */
    exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
               NULL, &handle, NULL, NULL, &reqid);
    if ((request = request_lookup (reqid)) == NULL)
         return;                        /*  Something garbage - ignore it    */

    SEND (&request-> reply_to, "TRAN_CLOSED", "");

    for (request  = requests.next;
         request != (TRANREQ *) &requests;
         request  = request-> next)
      {
        /*  Destroy all requests that refer to this (closed) socket          */
        if (request-> handle == handle)
          {
            request = request-> prev;
            request_destroy (request-> next);
          }
      }
}


/***********************   UPDATE REQUEST AFTER ERROR   **********************/

MODULE update_request_after_error (THREAD *thread)
{
    qbyte
        reqid;                          /*  Request ID back from SMTSOCK     */
    TRANREQ
        *request;                       /*  Request we process               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up reqid from event body, encoded as SMT_SOCK_ERROR             */
    exdr_read (thread-> event-> body, SMT_SOCK_ERROR, NULL, NULL, &reqid);
    if ((request = request_lookup (reqid)) == NULL)
         return;                        /*  Something garbage - ignore it    */

    SEND (&request-> reply_to, "TRAN_ERROR", (char *) thread-> event-> body);
    request_destroy (request);
}


/*************************   CREATE PUT FILE THREAD   ************************/

MODULE create_put_file_thread (THREAD *thread)
{
    struct_smt_tran_putf
        *params;
    THREAD
        *child;                         /*  Handle to child thread           */
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    child = thread_create (AGENT_NAME, "");
    ASSERT (child);

    tcb = child-> tcb;
    get_smt_tran_putf (thread-> event-> body, (void **) &params);

    tcb-> thread_type = put_file_event;
    tcb-> filename    = mem_strdup (clean_path (params-> filename));
    tcb-> start_slice = params-> start;
    tcb-> end_slice   = params-> end;
    tcb-> filetype    = params-> filetype;
    tcb-> handle      = params-> socket;
    tcb-> append      = FALSE;
    tcb-> reply_to    = thread-> event-> sender;

#if (defined (MSDOS_FILESYSTEM))
    /*  On DOS-based file systems, text files already contain CRLFs, and
     *  can thus be handled as binary files.
     */   
    tcb-> filetype = FILETYPE_BINARY;
#endif

    event_send (
        &child-> queue-> qid,           /*  Send to child thread queue       */
        &thread-> event-> sender,       /*  Queue for reply                  */
        "PUT_FILE",                     /*  Name of event to send            */
        NULL, 0,                        /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */

    fileio_threads++;
    free_smt_tran_putf ((void **) &params);
}


/*************************   CREATE GET FILE THREAD   ************************/

MODULE create_get_file_thread (THREAD *thread)
{
    struct_smt_tran_getf
        *params;
    THREAD
        *child;                         /*  Handle to child thread           */
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    child = thread_create (AGENT_NAME, "");
    ASSERT (child);

    tcb = child-> tcb;
    get_smt_tran_getf (thread-> event-> body, (void **) &params);

    tcb-> thread_type = get_file_event;
    tcb-> filename    = mem_strdup (clean_path (params-> filename));
    tcb-> start_slice = params-> start;
    tcb-> end_slice   = params-> end;
    tcb-> filetype    = params-> filetype;
    tcb-> handle      = params-> socket;
    tcb-> append      = params-> append;
    tcb-> reply_to    = thread-> event-> sender;

    event_send (
        &child-> queue-> qid,           /*  Send to child thread queue       */
        &thread-> event-> sender,       /*  Queue for reply                  */
        "GET_FILE",                     /*  Name of event to send            */
        NULL, 0,                        /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */

    fileio_threads++;
    free_smt_tran_getf ((void **) &params);
}


/**************************   OPEN FILE FOR OUTPUT   *************************/

MODULE open_file_for_output (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> append)
        open_transfer_file (thread, 'a');
    else
        open_transfer_file (thread, 'o');
}

static void
open_transfer_file (THREAD *thread, char mode)
{
    int
        open_mode;
    
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    if (mode == 'i')                    /*  Input                            */
        open_mode = O_RDONLY;
    else
    if (mode == 'o')                    /*  Output                           */
        open_mode = O_WRONLY | O_CREAT | O_TRUNC;
    else
    if (mode == 'a')                    /*  Append                           */
        open_mode = O_WRONLY | O_CREAT | O_APPEND;
    else
        return;                         /*  Error                            */
        
    tcb-> filesize = 0;
    tcb-> stream   = lazy_open (tcb-> filename, open_mode);
    if (io_completed)
      {
        if (tcb-> stream < 0)           /*  If the open failed, send error   */
          {                             /*    to console, and terminate      */
            sendfmt (&operq, "ERROR",
                "smttran: cannot open '%s' for '%c'", tcb-> filename, mode);
            signal_fatal_error ();
          }
        else
        if (tcb-> start_slice > 0)      /*  Position at start of slice?      */
            lseek (tcb-> stream, tcb-> start_slice, SEEK_SET);
      }
}

local
signal_fatal_error (void)
{
    senderr (&operq);
    raise_exception (exception_event);
    SEND (&tcb-> reply_to, "TRAN_ERROR", strerror (errno));
}


/**************************   OPEN FILE FOR INPUT   **************************/

MODULE open_file_for_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    open_transfer_file (thread, 'i');
}


/*************************   READ FILE DATA BUFFER   *************************/

MODULE read_file_data_buffer (THREAD *thread)
{
    long
        read_size;                      /*  Amount of data read/to read      */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> end_slice > 0)            /*  End of slice defined?            */
      {
        read_size = tcb-> end_slice - tcb-> filesize + 1;
        if (read_size < 0)
            read_size = 0;
        else
        if (read_size > BUFFER_SIZE)
            read_size = BUFFER_SIZE;
      }
    else
        read_size = BUFFER_SIZE;

    mem_strfree (&tcb-> block_data);
    tcb-> block_size = read_size;
    tcb-> block_data = mem_alloc ((dbyte) read_size);

    read_size = lazy_read (tcb-> stream, tcb-> block_data, (int) read_size);
    if (io_completed)
      {
        if (read_size == 0)
            raise_exception (end_of_file_event);
        else
        if (read_size == -1)            /*  If the read failed, send error   */
          {                             /*    to console, and terminate      */
            sendfmt (&operq, "ERROR",
                     "smttran: could not read from %s", tcb-> filename);
            signal_fatal_error ();
          }
        else
            tcb-> read_size = read_size;
      }
}


/**********************   CONVERT ASCII TO NET IF REQD   *********************/

MODULE convert_ascii_to_net_if_reqd (THREAD *thread)
{
    qbyte
        text_size;                      /*  Size of text block               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> filetype == FILETYPE_BINARY)
      {
        tcb-> write_size = tcb-> read_size;
        tcb-> send_text  = FALSE;
      }
    else
      {
        /*  Allocate text block, in the worst case = all LFs -> CRLFs        */
        mem_strfree (&tcb-> block_text);
        text_size = tcb-> read_size * 2;    
        tcb-> block_text = mem_alloc ((size_t) text_size);
        if (tcb-> block_text)
          {
            /*  Convert data to 'text'                                       */
            tcb-> write_size = file_set_eoln (tcb-> block_text,
                                              tcb-> block_data,
                                              (dbyte) tcb-> read_size, TRUE);
            tcb-> send_text = TRUE;
           }
        else
          {
            sendfmt (&operq, "ERROR",
                     "smttran: could not allocate text buffer (%ld bytes)",
                     text_size);
            signal_fatal_error ();
          }
      }
}


/**************************   PUT BUFFER TO SOCKET   *************************/

MODULE put_buffer_to_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> filesize += tcb-> write_size;
    send_write (&sockq, 0, tcb-> handle, (word) tcb-> write_size,
               (byte *) (tcb-> send_text?
                         tcb-> block_text: tcb-> block_data), 0);
}


/*************************   GET BUFFER FROM SOCKET   ************************/

MODULE get_buffer_from_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Read buffer from socket, we expect up to BUFFER_MAX bytes, but       */
    /*  anything will do.                                                    */
    send_read (&sockq, 0, tcb-> handle, BUFFER_SIZE, 1, 0);
}


/**********************   CONVERT NET TO ASCII IF REQD   *********************/

MODULE convert_net_to_ascii_if_reqd (THREAD *thread)
{
    dbyte
        read_size;
    
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> filetype == FILETYPE_BINARY)
      {
        mem_strfree (&tcb-> block_data);
        exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
                   NULL, NULL, &read_size, &tcb-> block_data, NULL);
        tcb-> write_size = read_size;
      }
    else
      {
        mem_strfree (&tcb-> block_text);
        exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
                   NULL, NULL, &read_size, &tcb-> block_text, NULL);

        mem_strfree (&tcb-> block_data);
        tcb-> block_data = mem_alloc (read_size);
        if (tcb-> block_text)
            tcb-> write_size = file_set_eoln (tcb-> block_data,
                                              tcb-> block_text,
                                              read_size, FALSE);
        else
          {
            sendfmt (&operq, "ERROR",
                     "smttran: could not allocate text buffer (%ld bytes)",
                     read_size);
            signal_fatal_error ();
          }
      }
}


/*************************   WRITE FILE DATA BUFFER   ************************/

MODULE write_file_data_buffer (THREAD *thread)
{
    int
        rc;                             /*  Return code from write           */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> filesize += tcb-> write_size;
    rc = lazy_write (tcb-> stream, tcb-> block_data,
                    (size_t) tcb-> write_size);
    if (io_completed)
      {
        if (rc < 0)                     /*  If the read failed, send error   */
          {                             /*    to console, and terminate      */
            sendfmt (&operq, "ERROR",
                     "smttran: could not write to %s", tcb-> filename);
            signal_fatal_error ();
          }
      }
}


/**************************   SIGNAL PUT FILE OKAY   *************************/

MODULE signal_put_file_okay (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_tran_putf_ok (&tcb-> reply_to, tcb-> filesize);
    fileio_threads--;                   /*  Request is finished              */
}


/**************************   SIGNAL GET FILE OKAY   *************************/

MODULE signal_get_file_okay (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_tran_getf_ok (&tcb-> reply_to, tcb-> filesize);
    fileio_threads--;                   /*  Request is finished              */
}


/**************************   SIGNAL SOCKET CLOSED   *************************/

MODULE signal_socket_closed (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&tcb-> reply_to, "TRAN_CLOSED", "");
    fileio_threads--;                   /*  Request is finished              */
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&tcb-> reply_to, "TRAN_ERROR", (char *) thread-> event-> body);
    fileio_threads--;                  /*  Request is finished              */
}


/************************   OKAY IF NO REQUESTS LEFT   ***********************/

MODULE okay_if_no_requests_left (THREAD *thread)
{
    static QID
        commit_requestor = { 0, 0 };

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Since commit events come from various places, we will store the QID  */
    /*  of the first one to come in, and use that for reply events.  When    */
    /*  we send an ok event, we'll reset the requestor queue id.  This is    */
    /*  not the best solution, but will have to do for now.                  */

    if (commit_requestor.ident == 0)
        commit_requestor = thread-> event-> sender;

    /*  If no requests left, signal all closed to sender, else send a        */
    /*  timer alarm event to ourselves to cause the dialog to loop.          */
    if (requests.next  == &requests
    &&  fileio_threads == 0)
      {
        SEND (&commit_requestor, "TRAN_CLOSED", "");
        commit_requestor.ident = 0;
      }
    else
        /*  Ask timer to send us an event after one second                   */
        send_alarm (&timeq, 0, 100, 0, NULL);
}


/***************************   CHECK THREAD TYPE   ***************************/

MODULE check_thread_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = tcb-> thread_type;
}


/**************************   DESTROY ALL REQUESTS   *************************/

MODULE destroy_all_requests (THREAD *thread)
{
    while (requests.next != &requests)
        request_destroy (requests.next);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> stream)
        close (tcb-> stream);

    mem_strfree (&tcb-> filename);
    mem_strfree (&tcb-> block_data);
    mem_strfree (&tcb-> block_text);
    the_next_event = terminate_event;
}

