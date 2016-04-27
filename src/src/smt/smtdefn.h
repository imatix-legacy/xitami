/*  ----------------------------------------------------------------<Prolog>-
    Name:       smtdefn.h
    Title:      The Standard SMT Agents
    Package:    Libero SMT 2.x

    Written:    96/05/27  iMatix SMT kernel team <smt@imatix.com>
    Revised:    98/06/10

    Synopsis:   Defines the standard agent prototypes and methods.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SMTDEFN_INCLUDED               /*  Allow multiple inclusions        */
#define _SMTDEFN_INCLUDED

#include "sfl.h"                        /*  SFL functions & definitions      */
#include "smtlib.h"                     /*  SMT functions & definitions      */
#include "smtmsg.h"                     /*  SMT message definitions          */


/*---------------------------------------------------------------------------
 *  Standard SMT agents
 */

/*  Prototypes                                                               */

#ifdef __cplusplus
extern "C" {
#endif

int  smtauth_init    (void);            /*  Authorisation agent              */
int  smtecho_init    (void);            /*  TCP/IP echo agent                */
int  smthttp_init    (char *rootdir, char *cgidir);
                                        /*  HTTP agent                       */
int  smtlog_init     (void);            /*  Logging agent                    */
int  smtoper_init    (void);            /*  Operator agent                   */
int  smtslot_init    (void);            /*  Time slot agent                  */
int  smtsock_init    (void);            /*  Socket i/o agent                 */
void smtsock_trace   (Bool trace);      /*  Socket i/o agent trace on/off    */
int  smttime_init    (void);            /*  Timer agent                      */
int  smttran_init    (void);            /*  TCP/IP transfer agent            */
int  smtftpc_init    (char *root);      /*  FTP control agent                */
int  smtftpd_init    (void);            /*  FTP data agent                   */
int  smtrdns_init    (void);            /*  Reverse DNS agent                */
int  smtssl_init     (void);            /*  SSL agent                        */

#ifdef __cplusplus
}
#endif


/*---------------------------------------------------------------------------
 *  SMTLOG - Logging Agent
 *      One thread per log file; create thread with log file name, or supply
 *      log file name in CYCLE, OPEN, APPEND events.  Filename "" or "NULL"
 *      means discard all log file output.  Errors are sent to SMTOPER.
 *
 *  Method:                         Body:           Replies:
 *  CYCLE    Cycle log file         [file name]     -
 *  OPEN     Open new log file      [file name]     -
 *  APPEND   Append to existing     [file name]     -
 *  PUT      Write line to log      Line of text    -
 *  PLAIN    Do not timestamp log   -               -
 *  STAMP    Timestamp each line    -               -
 *  CLOSE    Close log file         -               -
 */

#define SMT_LOGGING     "smtlog"        /*  Name of logging agent            */


/*---------------------------------------------------------------------------
 *  SMTOPER - Operator Console Agent
 *      Single unnamed thread created automatically when agent initialises.
 *      Send messages to console device or log file if specified.
 *
 *  Method:                         Body:             Replies:
 *  ERROR    Error message          Message           -
 *  WARNING  Warning message        Message           -
 *  INFO     Information message    Message           -
 *  LOG      Redirect to log file   SMTLOG thread name  -
 */

#define SMT_OPERATOR    "smtoper"       /*  Name of operator agent           */


/*---------------------------------------------------------------------------
 *  SMTSLOT - Time Slot Agent
 *      One thread per application; create thread with application name.
 *      Send SPECIFY events, then ON or OFF to set timer initial state.
 *      Specification is "name values..."; name is "mon" to "sun", or date
 *      in MM/DD, YY/MM/DD, or YYYY/MM/DD format.  Values are hh:mm[-hh:mm]
 *      in 24-hour clock format, delimited by spaces.
 *
 *  Method:                         Body:             Replies:
 *  SPECIFY  Specify time slot      Specification     SLOT_ERROR, if error
 *  ON       Error message          -                 SWITCH_ON, SWITCH_OFF
 *  OFF      Error message          -                 SWITCH_ON, SWITCH_OFF
 */

#define SMT_SLOT        "smtslot"       /*  Name of time slot agent          */


/*---------------------------------------------------------------------------
 *  SMTSOCK - Socket I/O Agent
 *      Single unnamed thread created automatically when agent initialises.
 *      Multiple writes are processed in order; multiple reads are collapsed.
 *
 *  Method:                         Body:             Replies:
 *  READ     Read socket data       SMT_SOCK_READ     SOCK_READ_OK, ...
 *  READR    Read, repeat for ever  SMT_SOCK_READ     SOCK_READ_OK, ...
 *  WRITE    Write socket data      SMT_SOCK_WRITE    SOCK_WRITE_OK, ...
 *  INPUT    Wait for input         SMT_SOCK_INPUT    SOCK_INPUT_OK, ...
 *  INPUTR   Wait input, repeat     SMT_SOCK_INPUT    SOCK_INPUT_OK, ...
 *  OUTPUT   Wait for output        SMT_SOCK_OUTPUT   SOCK_OUTPUT_OK, ...
 *  CONNECT  Connect to host        SMT_SOCK_CONNECT  SOCK_WRITE_OK, ...
 *  FLUSH    Flush requests         SMT_SOCK_FLUSH    -
 *
 *  Replies:                                    Body:
 *  SOCK_READ_OK    Data read okay              SMT_SOCK_READ_OK
 *  SOCK_WRITE_OK   Data written okay           SMT_SOCK_OK
 *  SOCK_INPUT_OK   Socket has input ready      SMT_SOCK_OK
 *  SOCK_OUTPUT_OK  Socket ready for output     SMT_SOCK_OK
 *  SOCK_CLOSED     Socket was closed           SMT_SOCK_READ_OK
 *  SOCK_TIMEOUT    Request timed-out           SMT_SOCK_READ_OK
 *  SOCK_ERROR      Socket error during read    SMT_SOCK_ERROR
 */

#define SMT_SOCKET      "smtsock"       /*  Name of socket i/o agent         */


/*---------------------------------------------------------------------------
 *  SMTTIME - Timer Agent
 *      Single unnamed thread created automatically when agent initialises.
 *      Accurate to 1/100th second.
 *
 *  Method:                         Body:             Replies:
 *  ALARM    Alarm after delay      SMT_TIME_ALARM    TIME_ALARM, TIME_ERROR
 *  WAKEUP   Alarm at some time     SMT_TIME_ALARM    TIME_ALARM, TIME_ERROR
 *  CLOCK    Alarm at intervals     SMT_TIME_CLOCK    TIME_ALARM, TIME_ERROR
 *
 *  Replies:                                    Body:
 *  TIME_ALARM      Alarm went off              SMT_TIME_REPLY
 *  TIME_ERROR      Insufficient memory         Error message
 */

#define SMT_TIMER       "smttime"       /*  Name of timer agent              */


/*---------------------------------------------------------------------------
 *  SMTTRAN - Transfer Agent
 *      Single unnamed thread created automatically when agent initialises.
 *      Transfers fixed-size blocks or complete files.
 *
 *  Method:                         Body:             Replies:
 *  PUT_BLOCK   Write block         SMT_TRAN_PUTB     TRAN_PUTB_OK, ...
 *  GET_BLOCK   Read block          SMT_TRAN_GETB     TRAN_GETB_OK, ...
 *  PUT_FILE    Write file          SMT_TRAN_PUTF     TRAN_PUTF_OK, ...
 *  GET_FILE    Read file           SMT_TRAN_GETF     TRAN_GETF_OK, ...
 *  PUT_TEXT    Write text file     SMT_TRAN_PUTT     TRAN_PUTF_OK, ...
 *  GET_TEXT    Read text file      SMT_TRAN_GETT     TRAN_GETF_OK, ...
 *  PUT_SLICE   Write file slice    SMT_TRAN_PUTS     TRAN_PUTF_OK, ...
 *  GET_SLICE   Read file slice     SMT_TRAN_GETS     TRAN_GETF_OK, ...
 *  COMMIT      Finish transfers    -                 -
 */

#define SMT_TRANSFER    "smttran"       /*  Name of transfer agent           */


/*---------------------------------------------------------------------------
 *  SMTFTPD - FTP data Agent
 *      Single unnamed thread created automatically when agent initialises.
 *      Send or receive files with FTP data connection.
 *      Implement Active and passive mode (connect to client or listen)
 *
 *  Method:                         Body:              Replies:
 *  PUT_FILE    Write file          SMT_FTPD_PUTF      FTPD_PUTF_OK, ...
 *  GET_FILE    Read file           SMT_FTPD_GETF      FTPD_GETF_OK, ...
 *  PASSIVE     Passive mode        SMT_FTPD_PASS      FTPD_PASS_OK, ...
 *  ABORT       Abort transfert     SMT_FTPD_ABORT     FTPD_ABORT_OK, ...
 *  CLOSECTRL   Close control       SMT_FTPD_CLOSECTRL
 */

#define SMT_FTPD        "smtftpd"       /*  Name of FTP server data agent    */


/*---------------------------------------------------------------------------
 *  SMTRDNS - Reverse DNS Agent
 *      One thread per request.  A main thread creates child threads with
 *      the type of request.
 *
 *  Method:                         Body:             Replies:
 *  GET_HOST Get host name          SMT_GET_HOST_NAME RDNS_OK,...
 *
 *  Replies:
 *  HOST_NAME  Host name
 *  HOST_IP    Host IP address
 */

#define SMT_RDNS        "smtrdns"       /*  Name of reverse dns agent        */


/*  Other Agents                                                             */

#define SMT_ECHO        "smtecho"       /*  Name of TCP/IP echo agent        */
#define SMT_HTTP        "smthttp"       /*  Name of HTTP server agent        */
#define SMT_FTPC        "smtftpc"       /*  Name of FTP server control agent */
#define SMT_SSL         "smtssl"        /*  Name of SSL server agent         */
#define SMT_ECHO_PORT   "7"             /*  Port for echo agent              */
#define SMT_FTP_PORT    "21"            /*  Port for FTP agent               */
#define SMT_HTTP_PORT   "80"            /*  Port for HTTP agent              */
#define SMT_SHTTP_PORT  "443"           /*  Port for SHTTP agent             */


#endif                                  /*  Include smtdefn.h                */
