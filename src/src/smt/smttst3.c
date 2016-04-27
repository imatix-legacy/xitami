/*  ----------------------------------------------------------------<Prolog>-
    Name:       smttst3.c
    Title:      SMT Test Reverse DNS agent
    Package:    Libero SMT 2.x

    Written:    96/10/12  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/12/16

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smtrdnsl.h"

/*- Definitions -------------------------------------------------------------*/

#ifdef AGENT_NAME
#undef AGENT_NAME
#endif


#define AGENT_NAME   "smttst3"          /*  Our public name                  */
#define BUFFER_SIZE  2048

typedef struct                          /*  Thread context block:            */
{
  int
     arg_index,                         /*  Current argument index           */
     argc;                              /*  Number of argument               */
  char
     **argv;                            /*  Argument list value              */
} TCB;


/*- Function prototypes -----------------------------------------------------*/


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread contect block     */
static QID
    operq,                              /*  Operator console event queue     */
    rdnsq;                              /*  Reverse DNS agent event queue    */

extern SYMTAB
    *config;                            /*  Global config file               */
static struct in_addr
    inaddr;                             /*  Used to format IP address        */

#define MSG_MAX BUFFER_SIZE + 64

static byte
    msg_body [MSG_MAX];                 /*  Messages sent to other agents    */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_writed()     */
    msg = { MSG_MAX,  msg_body };
static char
    buffer [BUFFER_SIZE];               /*  General-use string buffer        */

#include "smttst3.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int smttst3_init (int argc, char *argv [])
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread;                     /*  Handle to various threads        */

#   include "smttst3.i"                 /*  Include dialog interpreter       */

    /*                      Method name      Event value     Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",       shutdown_event,
                                             SMT_PRIORITY_MAX);

    /*  Reply events from reverse DNS agent                                  */
    method_declare (agent, "HOST_NAME",       host_event,       0);
    method_declare (agent, "HOST_IP",         ip_event,         0);
    method_declare (agent, "HOST_ERROR",      error_event,      0);
    method_declare (agent, "HOST_END",        end_event,        0);
    method_declare (agent, "HOST_TIMEOUT",    timeout_event,    0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that socket i/o agent is running, else start it up            */
    smtrdns_init ();
    if ((thread = thread_lookup ("smtrdns", "main")) != NULL)
        rdnsq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create initial, unnamed thread                                       */
    if ((thread = thread_create (AGENT_NAME, "")) != NULL)
      {
        ((TCB *) thread-> tcb)-> argc = argc;
        ((TCB *) thread-> tcb)-> argv = argv;
      }
    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> arg_index = 1;
    the_next_event = ok_event;
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = terminate_event;
    smt_shutdown ();
}


/**************************   DISPLAY ERROR VALUE   **************************/

MODULE display_error_value (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    puts ("Error in request execution");
    the_next_event = ok_event;
}


/***************************   DISPLAY HOST NAME   ***************************/

MODULE display_host_name (THREAD *thread)
{
    char
        *host = buffer;
    qbyte
        ip;
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    exdr_read (thread-> event-> body, SMT_HOST_NAME, &ip, &host);
    inaddr.s_addr = ip;
    printf ("%s -> %s\n", inet_ntoa (inaddr), host);
    the_next_event = ok_event;
}


/***************************   REQUEST HOST NAME   ***************************/

MODULE request_host_name (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    msg_size = exdr_writed (&msg, SMT_GET_HOST_NAME, (qbyte) 0, buffer,
                            (qbyte) 0);

    event_send (
        &rdnsq,                         /*  Send to specified queue          */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "GET_HOST_NAME",                /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/*************************   DISPLAY END OF SEARCH   *************************/

MODULE display_end_of_search (THREAD *thread)
{
    coprintf ("%s not found !!!", buffer);
    the_next_event = ok_event;
}


/******************************   DISPLAY HELP   *****************************/

MODULE display_help (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    printf ("Name Server Host query version 1.0\n");
    printf ("NSHOST Copyright (c) 1991-98 iMatix\n\n");
    printf ("Usage: nshost [-debug] [-rec] [-server addr] [-help] [request]\n");
    printf ("Where: help or ?:         Display this message\n");
    printf ("       set debug:         Set debug mode (to nshost.log)\n");
    printf ("       set recursive:     Set recursive query ON\n");
    printf ("       set server %%addr%%: Set default DNS ip address\n");
    printf ("       exit or quit:      Exit the program\n\n");
    printf ("Example: nshost -debug -server 127.0.0.1 www.imatix.com\n\n");
    printf ("Enter an IP address or a host name to resolv this\n\n");
    the_next_event = ok_event;
}


/***************************   DISPLAY IP ADDRESS   **************************/

MODULE display_ip_address (THREAD *thread)
{
    qbyte
        ip;
    char
        *host = buffer;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    exdr_read (thread-> event-> body, SMT_HOST_IP, &ip, &host);
    inaddr.s_addr = ip;
    printf ("%s -> %s\n", host, inet_ntoa (inaddr));

    the_next_event = ok_event;
}


/****************************   DISPLAY TIME OUT   ***************************/

MODULE display_time_out (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    puts ("Request timed out!!!");
    the_next_event = ok_event;
}


/***************************   GET ARGUMENT TYPE   ***************************/

MODULE get_argument_type (THREAD *thread)
{
    int
       index,
       h [4],
       count;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    count = sscanf (buffer, "%d.%d.%d.%d", &h [0], &h[1], &h [2], &h [3]);
    if (count > 0)
      {
        the_next_event = ip_event;
        for (index = 0; index < count; index++)
         {
            if (h [index] < 0 || h [index] > 255)
              {
                the_next_event = host_name_event;
                break;
              }
         }
      }
    else
        the_next_event = host_name_event;
}


/******************************   GET COMMAND   ******************************/

MODULE get_command (THREAD *thread)
{
    char
        *value;
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    strcrop (buffer);
    strlwc  (buffer);
    value = strskp (buffer);
    if (value != buffer)
        strcpy (buffer, value);

    if (strnull (buffer))
        the_next_event = none_event;
    else
    if (streq (buffer, "help"))
        the_next_event = help_event;
    else
    if (strchr (buffer, '?'))
        the_next_event = help_event;
    else
    if (strncmp (buffer, "set server", 10) == 0)
        the_next_event = server_ip_event;
    else
    if (streq (buffer, "set debug"))
        the_next_event = debug_event;
    else
    if (streq (buffer, "set recursive"))
        the_next_event = recursive_event;
    else
    if (streq (buffer, "exit"))
        the_next_event = exit_event;
    else
    if (streq (buffer, "quit"))
        the_next_event = exit_event;
    else
      {
        if (strchr (buffer, ' ') != NULL)
            the_next_event = invalid_event;
        else
            the_next_event = request_event;
      }
}


/***************************   GET NEXT ARGUMENT   ***************************/

MODULE get_next_argument (THREAD *thread)
{
    char
        *value;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    if (++tcb-> arg_index <= tcb-> argc)
      {
        value = tcb-> argv [tcb-> arg_index - 1];
        if (*value == '-')
          {
            value++;
            strcrop (value);
            strlwc  (value);
            value = strskp (value);
            if (streq (value, "debug"))
                strcpy (buffer, "set debug");
            else
            if (streq (value, "rec"))
                strcpy (buffer, "set recursive");
            else
            if (streq (value, "server"))
              {
                if (++tcb-> arg_index <= tcb-> argc)
                    xstrcpy (buffer, "set server ",
                             tcb-> argv [tcb-> arg_index - 1], NULL);
                else
                    strcpy  (buffer, "set server");
              }
            else
                strcpy (buffer, value);
          }
        else
            strcpy (buffer, value);
      }
    else
        buffer [0] = '\0';
}


/***************************   REQUEST IP ADDRESS   **************************/

MODULE request_ip_address (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    msg_size = exdr_writed (&msg, SMT_GET_HOST_IP, buffer, (qbyte) 0);

    event_send (
        &rdnsq,                         /*  Send to specified queue          */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "GET_HOST_IP",                  /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/*****************************   SET DEBUG MODE   ****************************/

MODULE set_debug_mode (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    dns_debug_mode = TRUE;
    console_set_mode (CONSOLE_TIME);
    console_capture  (".\\nshost.log", 'a');
    coprintf ("Debug mode ON, console output logged to file 'nshost.log'");
}


/*******************************   SET PROMPT   ******************************/

MODULE set_prompt (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    memset (buffer, 0, BUFFER_SIZE);
    printf ("Enter a request (? for help) =>");
    memset (buffer, 0, BUFFER_SIZE);
    fgets  (buffer, BUFFER_SIZE, stdin);
}


/**************************   SET SERVER IP VALUE   **************************/

MODULE set_server_ip_value (THREAD *thread)
{
    char
        *ip_value;
    int
        index;
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ip_value = &buffer [10];
    ip_value = strskp (ip_value);
    strconvch (ip_value, '\r', '\0');
    strconvch (ip_value, '\n', '\0');
    strcrop   (ip_value);
    inaddr.s_addr = inet_addr (ip_value);
    if (inaddr.s_addr != 0xFFFFFFFFUL
    &&  inaddr.s_addr != 0)
      {
        if (server_list.ns_count == MAX_NS)
            server_list.ns_count--;
        for (index = server_list.ns_count - 1; index >= 0; index--)
          {
            server_list.ns_addr [index + 1].sin_addr.s_addr =
                server_list.ns_addr [index].sin_addr.s_addr;
            server_list.ns_addr [index + 1].sin_port =
                server_list.ns_addr [index].sin_port;
            server_list.recursive_accept [index + 1] =
                server_list.recursive_accept [index];
          }
        server_list.ns_addr [0].sin_addr.s_addr = inaddr.s_addr;
        server_list.ns_addr [0].sin_port = htons (DNS_PORT);
        server_list.recursive_accept [0] = dns_recursive;
        server_list.ns_count++;
      }
    else
        puts ("Invalid IP address !!!");
}


/***********************   DISPLAY DNS SERVER ADDRESS   **********************/

MODULE display_dns_server_address (THREAD *thread)
{
    int
        index;
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    if (server_list.ns_count > 0)
      {
        puts ("Current DNS configuration:");
        for (index = 0; index < server_list.ns_count; index++)
          {
            inaddr.s_addr = server_list.ns_addr [index].sin_addr.s_addr;
            printf ("  %s\n", inet_ntoa (inaddr));
          }
      }
    else
      {
        puts ("No default DN Server defined");
        puts ("must be use 'set server' command before execution of request");
      }
}


/*************************   INITIALISE DNS LIBRARY   ************************/

MODULE initialise_dns_library (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    rdns_init (&server_list);
}



/***************************   SET RECURSIVE MODE   **************************/

MODULE set_recursive_mode (THREAD *thread)
{
    int
       index;

    dns_recursive = TRUE;
    for (index = 0; index < server_list.ns_count; index++)
        server_list.recursive_accept [index] = TRUE;
}


/************************   DISPLAY INVALID ARGUMENT   ***********************/

MODULE display_invalid_argument (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    coprintf ("%s: ERROR, invalid argument");
}


/************************   DISPLAY INVALID COMMAND   ************************/

MODULE display_invalid_command (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    coprintf ("%s: ERROR, invalid command");
}
