/*---------------------------------------------------------------------------
 * xixlogm.h - Xixlog messages.
 *
 * Generated on 1999/03/08, 21:30:31 from xixlogm.msg by exdrgen
 * DO NOT MODIFY THIS FILE.
 *
 * For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#ifndef INCLUDE_XIXLOGM
#define INCLUDE_XIXLOGM

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for xixlog - Xitami Extended Logging Agent.
 *---------------------------------------------------------------------------*/

#define XIXLOG_SET_RDNS "ssBB"

typedef struct {
    char *primary;                      /*  Primary DNS server               */
    char *secondary;                    /*  Secondary DNS server             */
    Bool  recursive;                    /*  Do recursive lookups?            */
    Bool  debug;                        /*  Debug DNS queries?               */
} struct_xixlog_set_rdns;

int  get_xixlog_set_rdns (
         byte *_buffer,
         /* struct_xixlog_set_rdns */ void **params);

void free_xixlog_set_rdns (
         /* struct_xixlog_set_rdns */ void **params);

#define declare_set_rdns(_event, _priority)                                  \
    method_declare (agent, "SET_RDNS", _event, _priority)

#define XIXLOG_OPEN "ssssssssssB"

typedef struct {
    char *log_path;                     /*  Path for logfiles, or empty      */
    char *log_file;                     /*  Name of logfile                  */
    char *log_format;                   /*  Desired logging format           */
    char *cycle_when;                   /*  When to cycle logfile            */
    char *cycle_how;                    /*  How to cycle logfile             */
    char *cycle_time;                   /*  For time-based cycling           */
    char *cycle_date;                   /*  For date-based cycling           */
    char *cycle_size;                   /*  For size-based cycling           */
    char *cycle_lines;                  /*  For size-based cycling           */
    char *cycle_argument;               /*  For other cycle methods          */
    Bool  translate;                    /*  Do reverse-DNS translation?      */
} struct_xixlog_open;

int  get_xixlog_open (
         byte *_buffer,
         /* struct_xixlog_open */ void **params);

void free_xixlog_open (
         /* struct_xixlog_open */ void **params);

#define declare_open(_event, _priority)                                      \
    method_declare (agent, "OPEN", _event, _priority)

#define XIXLOG_LOG "ssssssssqqqssss"

typedef struct {
    char *ip_client;                    /*  IP address of client             */
    char *ip_server;                    /*  IP address of server             */
    char *user_name;                    /*  User name, if known              */
    char *service;                      /*  HTTP or FTP                      */
    char *request;                      /*  Request line (HTTP)              */
    char *query;                        /*  Query string (HTTP)              */
    char *method;                       /*  HTTP method or FTP operation     */
    char *response;                     /*  Response code, 3 digits          */
    qbyte size_recd;                    /*  Request size in bytes            */
    qbyte size_sent;                    /*  Response size in bytes           */
    qbyte time_ms;                      /*  Processing time, in msecs        */
    char *referer;                      /*  HTTP Referer field               */
    char *agent;                        /*  HTTP User-Agent field            */
    char *file_name;                    /*  Filename used for request        */
    char *vhost_name;                   /*  Virtual host used for request    */
} struct_xixlog_log;

int  get_xixlog_log (
         byte *_buffer,
         /* struct_xixlog_log */ void **params);

void free_xixlog_log (
         /* struct_xixlog_log */ void **params);

#define declare_log(_event, _priority)                                       \
    method_declare (agent, "LOG", _event, _priority)

#define XIXLOG_PUT "s"

typedef struct {
    char *message;                      /*  Line of text to log              */
} struct_xixlog_put;

int  get_xixlog_put (
         byte *_buffer,
         /* struct_xixlog_put */ void **params);

void free_xixlog_put (
         /* struct_xixlog_put */ void **params);

#define declare_put(_event, _priority)                                       \
    method_declare (agent, "PUT", _event, _priority)


int put_xixlog_set_rdns (
        byte **_buffer,
        struct_xixlog_set_rdns *params);

/*  Send event - Initialise RDNS interface                                   */

int lsend_set_rdns (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *primary,                  /*  Primary DNS server               */
        char *secondary,                /*  Secondary DNS server             */
        Bool  recursive,                /*  Do recursive lookups?            */
        Bool  debug);                   /*  Debug DNS queries?               */

#define send_set_rdns(_to,                                                   \
                      primary,                                               \
                      secondary,                                             \
                      recursive,                                             \
                      debug)                                                 \
       lsend_set_rdns(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      primary,                                               \
                      secondary,                                             \
                      recursive,                                             \
                      debug)

int put_xixlog_open (
        byte **_buffer,
        struct_xixlog_open *params);

/*  Send event - Open log file                                               */

int lsend_open (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *log_path,                 /*  Path for logfiles, or empty      */
        char *log_file,                 /*  Name of logfile                  */
        char *log_format,               /*  Desired logging format           */
        char *cycle_when,               /*  When to cycle logfile            */
        char *cycle_how,                /*  How to cycle logfile             */
        char *cycle_time,               /*  For time-based cycling           */
        char *cycle_date,               /*  For date-based cycling           */
        char *cycle_size,               /*  For size-based cycling           */
        char *cycle_lines,              /*  For size-based cycling           */
        char *cycle_argument,           /*  For other cycle methods          */
        Bool  translate);               /*  Do reverse-DNS translation?      */

#define send_open(_to,                                                       \
                  log_path,                                                  \
                  log_file,                                                  \
                  log_format,                                                \
                  cycle_when,                                                \
                  cycle_how,                                                 \
                  cycle_time,                                                \
                  cycle_date,                                                \
                  cycle_size,                                                \
                  cycle_lines,                                               \
                  cycle_argument,                                            \
                  translate)                                                 \
       lsend_open(_to,                                                       \
                  &thread-> queue-> qid,                                     \
                  NULL, NULL, NULL, 0,                                       \
                  log_path,                                                  \
                  log_file,                                                  \
                  log_format,                                                \
                  cycle_when,                                                \
                  cycle_how,                                                 \
                  cycle_time,                                                \
                  cycle_date,                                                \
                  cycle_size,                                                \
                  cycle_lines,                                               \
                  cycle_argument,                                            \
                  translate)

int put_xixlog_log (
        byte **_buffer,
        struct_xixlog_log *params);

/*  Send event - Log normal request                                          */

int lsend_log (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *ip_client,                /*  IP address of client             */
        char *ip_server,                /*  IP address of server             */
        char *user_name,                /*  User name, if known              */
        char *service,                  /*  HTTP or FTP                      */
        char *request,                  /*  Request line (HTTP)              */
        char *query,                    /*  Query string (HTTP)              */
        char *method,                   /*  HTTP method or FTP operation     */
        char *response,                 /*  Response code, 3 digits          */
        qbyte size_recd,                /*  Request size in bytes            */
        qbyte size_sent,                /*  Response size in bytes           */
        qbyte time_ms,                  /*  Processing time, in msecs        */
        char *referer,                  /*  HTTP Referer field               */
        char *agent,                    /*  HTTP User-Agent field            */
        char *file_name,                /*  Filename used for request        */
        char *vhost_name);              /*  Virtual host used for request    */

#define send_log(_to,                                                        \
                 ip_client,                                                  \
                 ip_server,                                                  \
                 user_name,                                                  \
                 service,                                                    \
                 request,                                                    \
                 query,                                                      \
                 method,                                                     \
                 response,                                                   \
                 size_recd,                                                  \
                 size_sent,                                                  \
                 time_ms,                                                    \
                 referer,                                                    \
                 agent,                                                      \
                 file_name,                                                  \
                 vhost_name)                                                 \
       lsend_log(_to,                                                        \
                 &thread-> queue-> qid,                                      \
                 NULL, NULL, NULL, 0,                                        \
                 ip_client,                                                  \
                 ip_server,                                                  \
                 user_name,                                                  \
                 service,                                                    \
                 request,                                                    \
                 query,                                                      \
                 method,                                                     \
                 response,                                                   \
                 size_recd,                                                  \
                 size_sent,                                                  \
                 time_ms,                                                    \
                 referer,                                                    \
                 agent,                                                      \
                 file_name,                                                  \
                 vhost_name)

int put_xixlog_put (
        byte **_buffer,
        struct_xixlog_put *params);

/*  Send event - Log plain text request                                      */

int lsend_put (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *message);                 /*  Line of text to log              */

#define send_put(_to,                                                        \
                 message)                                                    \
       lsend_put(_to,                                                        \
                 &thread-> queue-> qid,                                      \
                 NULL, NULL, NULL, 0,                                        \
                 message)

#endif                                  /*  Included                         */
