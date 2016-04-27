/* ----------------------------------------------------------------<Prolog>-
    Name:       xierror.c
    Title:      Xitami error simulation agent (uses WSX protocol)
    Package:    Xitami

    Written:    97/12/01  Pieter Hintjens <ph@imatix.com>
    Revised:    98/12/22

    Synopsis:   Installs itself as a WSX agent on the '/error' alias.  URLs
                in the format /error?xxx return a HTTP error code xxx.  The
                URL /error?302:yyyy is handled as a redirection to the URL
                specified as yyyy.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMT HTTP definitions             */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME        "xierror"     /*  Our public name                  */
#define SINGLE_THREADED   TRUE          /*  Single-threaded agent            */


/*- Global variables used in this source file only --------------------------*/

static struct_smt_wsx_request
    *request = NULL;                    /*  Incoming smt_wsx request         */

#include "xierror.d"                    /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int xierror_init (void)
{
    AGENT  *agent;                      /*  Handle for our agent             */
#   include "xierror.i"                 /*  Include dialog interpreter       */

    /*                      Method name   Event value     Priority          */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",    shutdown_event, SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "WSX_REQUEST", request_event,  0);

    /*  Create master thread to manage WSX requests                          */
    thread_create (AGENT_NAME, "main");

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    THREAD
        *http_thread;

    the_next_event = ok_event;

    /*  Just as an example, we'll define a dynamic WSX alias                 */
    /*  Find 'main' thread in SMTHTTP agent                                  */
    http_thread = thread_lookup (SMT_HTTP, "main");
    ASSERT (http_thread);
    send_wsx_install (&http_thread-> queue-> qid,
                       NULL, "error-test", AGENT_NAME);
}


/***************************   DECODE WSX REQUEST   **************************/

MODULE decode_wsx_request (THREAD *thread)
{
    ASSERT (request == NULL);

    /*  Decode the WSX request using this standard function call             */
    get_smt_wsx_request (thread-> event-> body, (void **) &request);

    if (request)
        the_next_event = ok_event;
    else
      {
        /*  The request can only be null if there is no memory left          */
        send_wsx_error (&thread-> event-> sender, HTTP_RESPONSE_OVERLOADED);
        the_next_event = exception_event;
      }
}


/**************************   REPLY TO WSX REQUEST   *************************/

MODULE reply_to_wsx_request (THREAD *thread)
{
    dbyte
        response;                       /*  HTTP response to return          */
    int
        index;                          /*  Index into response table        */
    char
        *args_url;                      /*  We can get 302:xxxx in args      */

    /*  If arguments contain ':', point args_url to string following that    */
    args_url = strchr (request-> arguments, ':');
    if (args_url)
        *args_url++ = '\0';
    else
        args_url = "";

    /*  Look for HTTP response code in table                                 */
    response = HTTP_RESPONSE_BADREQUEST;
    for (index = 0; http_response [index].code; index++)
        if (streq (request-> arguments, http_response [index].code))
          {
            response = index;           /*  We found the code we wanted      */
            break;
          }
    /*  Send reply back to HTTP agent                                        */
    if (response == HTTP_RESPONSE_FOUND)
        send_wsx_redirect (&thread-> event-> sender, args_url);
    else
        send_wsx_error    (&thread-> event-> sender, response);

    /*  We're finished with the request structure - deallocate it            */
    free_smt_wsx_request ((void **) &request);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    /*  If we were interrupted during processing the request, free it.
     *  This avoids potential memory leaks.
     */
    if (request)
        free_smt_wsx_request ((void **) &request);

    the_next_event = terminate_event;
}
