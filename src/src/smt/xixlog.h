/*  ----------------------------------------------------------------<Prolog>-
    Name:       xixlog.h
    Title:      Xitami extended logging agent - definitions
    Package:    Libero SMT 2.x

    Written:    98/05/31  iMatix SMT kernel team <smt@imatix.com>
    Revised:    98/11/23

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _XIXLOG_INCLUDED                /*  Allow multiple inclusions        */
#define _XIXLOG_INCLUDED

#include "xixlogm.h"                    /*  Xixlog message definitions       */


/*- Constants ---------------------------------------------------------------*/

#define XIXLOG_AGENT     "xixlog"       /*  Xixlog agent name                */

/*  Common log file format (NCSA standard)                                   */
#define LOG_FORMAT_CLF   "$(client) - $(user) [$(datetime)] \"$(request)\" "\
                         "$(status) $(sent)"

/*  Extended common log file format (Apache standard)                        */
#define LOG_FORMAT_CLFX  "$(client) - $(user) [$(datetime)] \"$(request)\" "\
                         "$(status) $(sent) \"$(referer)\" \"$(agent)\""

/*  Microsoft log file format (IIS, PWS format)                              */
#define LOG_FORMAT_MS    "$(client), $(user), $(mon)/$(day)/$(year), " \
                         "$(hh):$(mm):$(ss), $(service), Xitami, $(ipsrv), "\
                         "$(stime), $(recd), $(sent), $(status), 0, " \
                         "$(method), $(file)"

/*  Log file markup language format (specific to Xitami)                     */
#define LOG_FORMAT_LML   "<LOG"                      \
                         " DATE=\"$(datetime)\""     \
                         " CLIENT=\"$(client)\""     \
                         " REQUEST=\"$(request)\""   \
                         " METHOD=\"$(method)\""     \
                         " STATUS=\"$(status)\""     \
                         " SENT=\"$(sent)\""         \
                         " FILENAME=\"$(file)\""     \
                         " USERNAME=\"$(user)\""     \
                         " SERVICE=\"$(service)\""   \
                         "/>"

/*  Extended log file markup language format (specific to Xitami)           */
#define LOG_FORMAT_XLML  "<LOG"                      \
                         " DATE=\"$(datetime)\""     \
                         " CLIENT=\"$(client)\""     \
                         " CLIENTIP=\"$(ipcli)\""    \
                         " SERVERIP=\"$(ipsrv)\""    \
                         " REQUEST=\"$(request)\""   \
                         " METHOD=\"$(method)\""     \
                         " STATUS=\"$(status)\""     \
                         " RECEIVED=\"$(recd)\""     \
                         " SENT=\"$(sent)\""         \
                         " DURATION=\"$(time_ms)\""  \
                         " FILENAME=\"$(file)\""     \
                         " USERAGENT=\"$(agent)\""   \
                         " REFERER=\"$(referer)\""   \
                         " USERNAME=\"$(user)\""     \
                         " SERVICE=\"$(service)\""   \
                         " VHOST=\"$(vhost)\""       \
                         "/>"

/*  When to cycle the log file                                               */

#define XI_CYCLE_STARTUP  "startup"     /*  Cycle when starting the server   */
#define XI_CYCLE_HOURLY   "hourly"      /*  Cycle every hour at X minutes    */
#define XI_CYCLE_DAILY    "daily"       /*  Cycle every day at hh:mm         */
#define XI_CYCLE_WEEKLY   "weekly"      /*  Cycle every week at dd:hh:mm     */
#define XI_CYCLE_MONTHLY  "monthly"     /*  Cycle every month at dd:hh:mm    */
#define XI_CYCLE_SIZE     "size"        /*  Cycle when exceeds X Kb          */
#define XI_CYCLE_LINES    "lines"       /*  Cycle when exceeds X lines       */
#define XI_CYCLE_MANUAL   "manual"      /*  Do not cycle the log file        */

/*  How to cycle the log file                                                */

#define XI_CYCLE_RENAME   "rename"      /*  Rename old file                  */
#define XI_CYCLE_DELETE   "delete"      /*  Delete old file                  */
#define XI_CYCLE_MOVE     "move"        /*  Move old file to another path    */
#define XI_CYCLE_CONCAT   "concat"      /*  Concat old data to file          */
#define XI_CYCLE_PROCESS  "process"     /*  Execute some command on file     */


/*- Function prototypes -----------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int xixlog_init (void);

#ifdef __cplusplus
}

#endif

#endif
