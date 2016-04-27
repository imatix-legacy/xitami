/*---------------------------------------------------------------------------
 * xixlogm.c - Xixlog messages.
 *
 * Generated on 1999/03/08, 21:30:31 from xixlogm.msg by exdrgen
 * DO NOT MODIFY THIS FILE.
 *
 * For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#include "sfl.h"                        /*  SFL header file                  */
#include "smtlib.h"                     /*  SMT header file                  */
#include "xixlogm.h"                    /*  Definitions & prototypes         */

/*---------------------------------------------------------------------------
 *  Message functions for xixlog - Xitami Extended Logging Agent.
 *---------------------------------------------------------------------------*/

int  get_xixlog_set_rdns (
         byte *_buffer,
         /* struct_xixlog_set_rdns */ void **params)
{
    *params = mem_alloc (sizeof (struct_xixlog_set_rdns));
    if (*params)
      {
        ((struct_xixlog_set_rdns *) *params)-> primary = NULL;
        ((struct_xixlog_set_rdns *) *params)-> secondary = NULL;
        return (exdr_read (_buffer, XIXLOG_SET_RDNS,
                   & ((struct_xixlog_set_rdns *) *params)-> primary,
                   & ((struct_xixlog_set_rdns *) *params)-> secondary,
                   & ((struct_xixlog_set_rdns *) *params)-> recursive,
                   & ((struct_xixlog_set_rdns *) *params)-> debug));
      }
    else
        return -1;
}

void free_xixlog_set_rdns (
         /* struct_xixlog_set_rdns */ void **params)
{
    mem_free (((struct_xixlog_set_rdns *) *params)-> primary);
    mem_free (((struct_xixlog_set_rdns *) *params)-> secondary);
    mem_free (*params);
    *params = NULL;
}

int  get_xixlog_open (
         byte *_buffer,
         /* struct_xixlog_open */ void **params)
{
    *params = mem_alloc (sizeof (struct_xixlog_open));
    if (*params)
      {
        ((struct_xixlog_open *) *params)-> log_path = NULL;
        ((struct_xixlog_open *) *params)-> log_file = NULL;
        ((struct_xixlog_open *) *params)-> log_format = NULL;
        ((struct_xixlog_open *) *params)-> cycle_when = NULL;
        ((struct_xixlog_open *) *params)-> cycle_how = NULL;
        ((struct_xixlog_open *) *params)-> cycle_time = NULL;
        ((struct_xixlog_open *) *params)-> cycle_date = NULL;
        ((struct_xixlog_open *) *params)-> cycle_size = NULL;
        ((struct_xixlog_open *) *params)-> cycle_lines = NULL;
        ((struct_xixlog_open *) *params)-> cycle_argument = NULL;
        return (exdr_read (_buffer, XIXLOG_OPEN,
                   & ((struct_xixlog_open *) *params)-> log_path,
                   & ((struct_xixlog_open *) *params)-> log_file,
                   & ((struct_xixlog_open *) *params)-> log_format,
                   & ((struct_xixlog_open *) *params)-> cycle_when,
                   & ((struct_xixlog_open *) *params)-> cycle_how,
                   & ((struct_xixlog_open *) *params)-> cycle_time,
                   & ((struct_xixlog_open *) *params)-> cycle_date,
                   & ((struct_xixlog_open *) *params)-> cycle_size,
                   & ((struct_xixlog_open *) *params)-> cycle_lines,
                   & ((struct_xixlog_open *) *params)-> cycle_argument,
                   & ((struct_xixlog_open *) *params)-> translate));
      }
    else
        return -1;
}

void free_xixlog_open (
         /* struct_xixlog_open */ void **params)
{
    mem_free (((struct_xixlog_open *) *params)-> log_path);
    mem_free (((struct_xixlog_open *) *params)-> log_file);
    mem_free (((struct_xixlog_open *) *params)-> log_format);
    mem_free (((struct_xixlog_open *) *params)-> cycle_when);
    mem_free (((struct_xixlog_open *) *params)-> cycle_how);
    mem_free (((struct_xixlog_open *) *params)-> cycle_time);
    mem_free (((struct_xixlog_open *) *params)-> cycle_date);
    mem_free (((struct_xixlog_open *) *params)-> cycle_size);
    mem_free (((struct_xixlog_open *) *params)-> cycle_lines);
    mem_free (((struct_xixlog_open *) *params)-> cycle_argument);
    mem_free (*params);
    *params = NULL;
}

int  get_xixlog_log (
         byte *_buffer,
         /* struct_xixlog_log */ void **params)
{
    *params = mem_alloc (sizeof (struct_xixlog_log));
    if (*params)
      {
        ((struct_xixlog_log *) *params)-> ip_client = NULL;
        ((struct_xixlog_log *) *params)-> ip_server = NULL;
        ((struct_xixlog_log *) *params)-> user_name = NULL;
        ((struct_xixlog_log *) *params)-> service = NULL;
        ((struct_xixlog_log *) *params)-> request = NULL;
        ((struct_xixlog_log *) *params)-> query = NULL;
        ((struct_xixlog_log *) *params)-> method = NULL;
        ((struct_xixlog_log *) *params)-> response = NULL;
        ((struct_xixlog_log *) *params)-> referer = NULL;
        ((struct_xixlog_log *) *params)-> agent = NULL;
        ((struct_xixlog_log *) *params)-> file_name = NULL;
        ((struct_xixlog_log *) *params)-> vhost_name = NULL;
        return (exdr_read (_buffer, XIXLOG_LOG,
                   & ((struct_xixlog_log *) *params)-> ip_client,
                   & ((struct_xixlog_log *) *params)-> ip_server,
                   & ((struct_xixlog_log *) *params)-> user_name,
                   & ((struct_xixlog_log *) *params)-> service,
                   & ((struct_xixlog_log *) *params)-> request,
                   & ((struct_xixlog_log *) *params)-> query,
                   & ((struct_xixlog_log *) *params)-> method,
                   & ((struct_xixlog_log *) *params)-> response,
                   & ((struct_xixlog_log *) *params)-> size_recd,
                   & ((struct_xixlog_log *) *params)-> size_sent,
                   & ((struct_xixlog_log *) *params)-> time_ms,
                   & ((struct_xixlog_log *) *params)-> referer,
                   & ((struct_xixlog_log *) *params)-> agent,
                   & ((struct_xixlog_log *) *params)-> file_name,
                   & ((struct_xixlog_log *) *params)-> vhost_name));
      }
    else
        return -1;
}

void free_xixlog_log (
         /* struct_xixlog_log */ void **params)
{
    mem_free (((struct_xixlog_log *) *params)-> ip_client);
    mem_free (((struct_xixlog_log *) *params)-> ip_server);
    mem_free (((struct_xixlog_log *) *params)-> user_name);
    mem_free (((struct_xixlog_log *) *params)-> service);
    mem_free (((struct_xixlog_log *) *params)-> request);
    mem_free (((struct_xixlog_log *) *params)-> query);
    mem_free (((struct_xixlog_log *) *params)-> method);
    mem_free (((struct_xixlog_log *) *params)-> response);
    mem_free (((struct_xixlog_log *) *params)-> referer);
    mem_free (((struct_xixlog_log *) *params)-> agent);
    mem_free (((struct_xixlog_log *) *params)-> file_name);
    mem_free (((struct_xixlog_log *) *params)-> vhost_name);
    mem_free (*params);
    *params = NULL;
}

int  get_xixlog_put (
         byte *_buffer,
         /* struct_xixlog_put */ void **params)
{
    *params = mem_alloc (sizeof (struct_xixlog_put));
    if (*params)
      {
        ((struct_xixlog_put *) *params)-> message = NULL;
        return (exdr_read (_buffer, XIXLOG_PUT,
                   & ((struct_xixlog_put *) *params)-> message));
      }
    else
        return -1;
}

void free_xixlog_put (
         /* struct_xixlog_put */ void **params)
{
    mem_free (((struct_xixlog_put *) *params)-> message);
    mem_free (*params);
    *params = NULL;
}

int put_xixlog_set_rdns (
        byte **_buffer,
        struct_xixlog_set_rdns *params)
{
    int _size;

    _size = exdr_write (NULL, XIXLOG_SET_RDNS,
                        params-> primary,
                        params-> secondary,
                        params-> recursive,
                        params-> debug);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, XIXLOG_SET_RDNS,
                    params-> primary,
                    params-> secondary,
                    params-> recursive,
                    params-> debug);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Initialise RDNS interface                                   */

int lsend_set_rdns (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *primary,                  /*  Primary DNS server               */
        char *secondary,                /*  Secondary DNS server             */
        Bool  recursive,                /*  Do recursive lookups?            */
        Bool  debug)                    /*  Debug DNS queries?               */
{
    byte *_body;
    int   _size,
          _rc;
    struct_xixlog_set_rdns
          _params;

    _params.primary                     = primary;
    _params.secondary                   = secondary;
    _params.recursive                   = recursive;
    _params.debug                       = debug;

    _size = put_xixlog_set_rdns (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SET_RDNS",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_xixlog_open (
        byte **_buffer,
        struct_xixlog_open *params)
{
    int _size;

    _size = exdr_write (NULL, XIXLOG_OPEN,
                        params-> log_path,
                        params-> log_file,
                        params-> log_format,
                        params-> cycle_when,
                        params-> cycle_how,
                        params-> cycle_time,
                        params-> cycle_date,
                        params-> cycle_size,
                        params-> cycle_lines,
                        params-> cycle_argument,
                        params-> translate);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, XIXLOG_OPEN,
                    params-> log_path,
                    params-> log_file,
                    params-> log_format,
                    params-> cycle_when,
                    params-> cycle_how,
                    params-> cycle_time,
                    params-> cycle_date,
                    params-> cycle_size,
                    params-> cycle_lines,
                    params-> cycle_argument,
                    params-> translate);
    else
        _size = 0;

    return (_size);
}

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
        Bool  translate)                /*  Do reverse-DNS translation?      */
{
    byte *_body;
    int   _size,
          _rc;
    struct_xixlog_open
          _params;

    _params.log_path                    = log_path;
    _params.log_file                    = log_file;
    _params.log_format                  = log_format;
    _params.cycle_when                  = cycle_when;
    _params.cycle_how                   = cycle_how;
    _params.cycle_time                  = cycle_time;
    _params.cycle_date                  = cycle_date;
    _params.cycle_size                  = cycle_size;
    _params.cycle_lines                 = cycle_lines;
    _params.cycle_argument              = cycle_argument;
    _params.translate                   = translate;

    _size = put_xixlog_open (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "OPEN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_xixlog_log (
        byte **_buffer,
        struct_xixlog_log *params)
{
    int _size;

    _size = exdr_write (NULL, XIXLOG_LOG,
                        params-> ip_client,
                        params-> ip_server,
                        params-> user_name,
                        params-> service,
                        params-> request,
                        params-> query,
                        params-> method,
                        params-> response,
                        params-> size_recd,
                        params-> size_sent,
                        params-> time_ms,
                        params-> referer,
                        params-> agent,
                        params-> file_name,
                        params-> vhost_name);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, XIXLOG_LOG,
                    params-> ip_client,
                    params-> ip_server,
                    params-> user_name,
                    params-> service,
                    params-> request,
                    params-> query,
                    params-> method,
                    params-> response,
                    params-> size_recd,
                    params-> size_sent,
                    params-> time_ms,
                    params-> referer,
                    params-> agent,
                    params-> file_name,
                    params-> vhost_name);
    else
        _size = 0;

    return (_size);
}

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
        char *vhost_name)               /*  Virtual host used for request    */
{
    byte *_body;
    int   _size,
          _rc;
    struct_xixlog_log
          _params;

    _params.ip_client                   = ip_client;
    _params.ip_server                   = ip_server;
    _params.user_name                   = user_name;
    _params.service                     = service;
    _params.request                     = request;
    _params.query                       = query;
    _params.method                      = method;
    _params.response                    = response;
    _params.size_recd                   = size_recd;
    _params.size_sent                   = size_sent;
    _params.time_ms                     = time_ms;
    _params.referer                     = referer;
    _params.agent                       = agent;
    _params.file_name                   = file_name;
    _params.vhost_name                  = vhost_name;

    _size = put_xixlog_log (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "LOG",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_xixlog_put (
        byte **_buffer,
        struct_xixlog_put *params)
{
    int _size;

    _size = exdr_write (NULL, XIXLOG_PUT,
                        params-> message);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, XIXLOG_PUT,
                    params-> message);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Log plain text request                                      */

int lsend_put (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *message)                  /*  Line of text to log              */
{
    byte *_body;
    int   _size,
          _rc;
    struct_xixlog_put
          _params;

    _params.message                     = message;

    _size = put_xixlog_put (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "PUT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

