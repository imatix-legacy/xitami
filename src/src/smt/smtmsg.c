/*---------------------------------------------------------------------------
 * smtmsg.c - SMT standard messages.
 *
 * Generated on 1999/02/28, 16:29:42 from smtmsg.msg by exdrgen
 * DO NOT MODIFY THIS FILE.
 *
 * For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#include "sfl.h"                        /*  SFL header file                  */
#include "smtlib.h"                     /*  SMT header file                  */
#include "smtmsg.h"                     /*  Definitions & prototypes         */

/*---------------------------------------------------------------------------
 *  Message functions for smtopen - Operator agent.
 *---------------------------------------------------------------------------*/

int  get_smt_oper_log (
         byte *_buffer,
         /* struct_smt_oper_log */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_oper_log));
    if (*params)
      {
        ((struct_smt_oper_log *) *params)-> agent_name = NULL;
        ((struct_smt_oper_log *) *params)-> thread_name = NULL;
        return (exdr_read (_buffer, SMT_OPER_LOG,
                   & ((struct_smt_oper_log *) *params)-> agent_name,
                   & ((struct_smt_oper_log *) *params)-> thread_name));
      }
    else
        return -1;
}

void free_smt_oper_log (
         /* struct_smt_oper_log */ void **params)
{
    mem_free (((struct_smt_oper_log *) *params)-> agent_name);
    mem_free (((struct_smt_oper_log *) *params)-> thread_name);
    mem_free (*params);
    *params = NULL;
}

int put_smt_oper_log (
        byte **_buffer,
        struct_smt_oper_log *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_OPER_LOG,
                        params-> agent_name,
                        params-> thread_name);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_OPER_LOG,
                    params-> agent_name,
                    params-> thread_name);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Specify logging agent                                       */

int lsend_set_log (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *agent_name,               /*  Name of logging agent            */
        char *thread_name)              /*  Name of logging thread           */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_oper_log
          _params;

    _params.agent_name                  = agent_name;
    _params.thread_name                 = thread_name;

    _size = put_smt_oper_log (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SET_LOG",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for smtsock - Socket i/o agent.
 *---------------------------------------------------------------------------*/

int  get_smt_sock_read (
         byte *_buffer,
         /* struct_smt_sock_read */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_read));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_READ,
                   & ((struct_smt_sock_read *) *params)-> timeout,
                   & ((struct_smt_sock_read *) *params)-> socket,
                   & ((struct_smt_sock_read *) *params)-> max_size,
                   & ((struct_smt_sock_read *) *params)-> min_size,
                   & ((struct_smt_sock_read *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_read (
         /* struct_smt_sock_read */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_write (
         byte *_buffer,
         /* struct_smt_sock_write */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_write));
    if (*params)
      {
        ((struct_smt_sock_write *) *params)-> data = NULL;
        return (exdr_read (_buffer, SMT_SOCK_WRITE,
                   & ((struct_smt_sock_write *) *params)-> timeout,
                   & ((struct_smt_sock_write *) *params)-> socket,
                   & ((struct_smt_sock_write *) *params)-> size,
                   & ((struct_smt_sock_write *) *params)-> data,
                   & ((struct_smt_sock_write *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_write (
         /* struct_smt_sock_write */ void **params)
{
    mem_free (((struct_smt_sock_write *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_readh (
         byte *_buffer,
         /* struct_smt_sock_readh */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_readh));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_READH,
                   & ((struct_smt_sock_readh *) *params)-> timeout,
                   & ((struct_smt_sock_readh *) *params)-> socket,
                   & ((struct_smt_sock_readh *) *params)-> max_size,
                   & ((struct_smt_sock_readh *) *params)-> min_size,
                   & ((struct_smt_sock_readh *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_readh (
         /* struct_smt_sock_readh */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_writeh (
         byte *_buffer,
         /* struct_smt_sock_writeh */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_writeh));
    if (*params)
      {
        ((struct_smt_sock_writeh *) *params)-> data = NULL;
        return (exdr_read (_buffer, SMT_SOCK_WRITEH,
                   & ((struct_smt_sock_writeh *) *params)-> timeout,
                   & ((struct_smt_sock_writeh *) *params)-> socket,
                   & ((struct_smt_sock_writeh *) *params)-> size,
                   & ((struct_smt_sock_writeh *) *params)-> data,
                   & ((struct_smt_sock_writeh *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_writeh (
         /* struct_smt_sock_writeh */ void **params)
{
    mem_free (((struct_smt_sock_writeh *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_input (
         byte *_buffer,
         /* struct_smt_sock_input */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_input));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_INPUT,
                   & ((struct_smt_sock_input *) *params)-> timeout,
                   & ((struct_smt_sock_input *) *params)-> socket,
                   & ((struct_smt_sock_input *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_input (
         /* struct_smt_sock_input */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_output (
         byte *_buffer,
         /* struct_smt_sock_output */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_output));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_OUTPUT,
                   & ((struct_smt_sock_output *) *params)-> timeout,
                   & ((struct_smt_sock_output *) *params)-> socket,
                   & ((struct_smt_sock_output *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_output (
         /* struct_smt_sock_output */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_connect (
         byte *_buffer,
         /* struct_smt_sock_connect */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_connect));
    if (*params)
      {
        ((struct_smt_sock_connect *) *params)-> type = NULL;
        ((struct_smt_sock_connect *) *params)-> host = NULL;
        ((struct_smt_sock_connect *) *params)-> service = NULL;
        return (exdr_read (_buffer, SMT_SOCK_CONNECT,
                   & ((struct_smt_sock_connect *) *params)-> timeout,
                   & ((struct_smt_sock_connect *) *params)-> type,
                   & ((struct_smt_sock_connect *) *params)-> host,
                   & ((struct_smt_sock_connect *) *params)-> service,
                   & ((struct_smt_sock_connect *) *params)-> port,
                   & ((struct_smt_sock_connect *) *params)-> address,
                   & ((struct_smt_sock_connect *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_connect (
         /* struct_smt_sock_connect */ void **params)
{
    mem_free (((struct_smt_sock_connect *) *params)-> type);
    mem_free (((struct_smt_sock_connect *) *params)-> host);
    mem_free (((struct_smt_sock_connect *) *params)-> service);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_flush (
         byte *_buffer,
         /* struct_smt_sock_flush */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_flush));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_FLUSH,
                   & ((struct_smt_sock_flush *) *params)-> socket));
      }
    else
        return -1;
}

void free_smt_sock_flush (
         /* struct_smt_sock_flush */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int put_smt_sock_read_ok (
        byte **_buffer,
        struct_smt_sock_read_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_READ_OK,
                        params-> timeout,
                        params-> socket,
                        params-> size,
                        params-> data,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_READ_OK,
                    params-> timeout,
                    params-> socket,
                    params-> size,
                    params-> data,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Read OK reply                                               */

int lsend_sock_read_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout from read request        */
        qbyte socket,                   /*  Socket used for i/o              */
        word  size,                     /*  Amount of data read              */
        byte *data,                     /*  Block of data read               */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_read_ok
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;
    _params.tag                         = tag;

    _size = put_smt_sock_read_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_READ_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  Send event - Closed reply                                                */

int lsend_sock_closed (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout from read request        */
        qbyte socket,                   /*  Socket used for i/o              */
        word  size,                     /*  Amount of data read              */
        byte *data,                     /*  Block of data read               */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_read_ok
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;
    _params.tag                         = tag;

    _size = put_smt_sock_read_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_CLOSED",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  Send event - Timeout reply                                               */

int lsend_sock_timeout (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout from read request        */
        qbyte socket,                   /*  Socket used for i/o              */
        word  size,                     /*  Amount of data read              */
        byte *data,                     /*  Block of data read               */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_read_ok
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;
    _params.tag                         = tag;

    _size = put_smt_sock_read_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_TIMEOUT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_readh_ok (
        byte **_buffer,
        struct_smt_sock_readh_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_READH_OK,
                        params-> timeout,
                        params-> socket,
                        params-> size,
                        params-> data,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_READH_OK,
                    params-> timeout,
                    params-> socket,
                    params-> size,
                    params-> data,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Read OK reply                                               */

int lsend_sock_readh_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout from read request        */
        qbyte socket,                   /*  Socket used for i/o              */
        qbyte size,                     /*  Amount of data read              */
        byte *data,                     /*  Block of data read               */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_readh_ok
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;
    _params.tag                         = tag;

    _size = put_smt_sock_readh_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_READH_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_ok (
        byte **_buffer,
        struct_smt_sock_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_OK,
                        params-> socket,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_OK,
                    params-> socket,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write OK reply                                              */

int lsend_sock_write_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_ok
          _params;

    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_smt_sock_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_WRITE_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  Send event - Write OK reply                                              */

int lsend_sock_writeh_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_ok
          _params;

    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_smt_sock_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_WRITEH_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  Send event - Input OK reply                                              */

int lsend_sock_input_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_ok
          _params;

    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_smt_sock_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_INPUT_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  Send event - Output OK reply                                             */

int lsend_sock_output_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_ok
          _params;

    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_smt_sock_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_OUTPUT_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_error (
        byte **_buffer,
        struct_smt_sock_error *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_ERROR,
                        params-> message,
                        params-> socket,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_ERROR,
                    params-> message,
                    params-> socket,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Error reply                                                 */

int lsend_sock_error (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *message,                  /*  Error message                    */
        qbyte socket,                   /*  Socket for i/o, or new socket    */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_error
          _params;

    _params.message                     = message;
    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_smt_sock_error (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_ERROR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_read (
        byte **_buffer,
        struct_smt_sock_read *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_READ,
                        params-> timeout,
                        params-> socket,
                        params-> max_size,
                        params-> min_size,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_READ,
                    params-> timeout,
                    params-> socket,
                    params-> max_size,
                    params-> min_size,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Read socket data                                            */

int lsend_read (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to read from              */
        dbyte max_size,                 /*  Size of receiving buffer         */
        dbyte min_size,                 /*  Minimum data to read, zero = all */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_read
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.max_size                    = max_size;
    _params.min_size                    = min_size;
    _params.tag                         = tag;

    _size = put_smt_sock_read (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "READ",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  Send event - Read, repeat for ever                                       */

int lsend_readr (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to read from              */
        dbyte max_size,                 /*  Size of receiving buffer         */
        dbyte min_size,                 /*  Minimum data to read, zero = all */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_read
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.max_size                    = max_size;
    _params.min_size                    = min_size;
    _params.tag                         = tag;

    _size = put_smt_sock_read (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "READR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_write (
        byte **_buffer,
        struct_smt_sock_write *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_WRITE,
                        params-> timeout,
                        params-> socket,
                        params-> size,
                        params-> data,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_WRITE,
                    params-> timeout,
                    params-> socket,
                    params-> size,
                    params-> data,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write socket data                                           */

int lsend_write (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to write to               */
        word  size,                     /*  Amount of data to write          */
        byte *data,                     /*  Block of data to write           */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_write
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;
    _params.tag                         = tag;

    _size = put_smt_sock_write (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WRITE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_readh (
        byte **_buffer,
        struct_smt_sock_readh *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_READH,
                        params-> timeout,
                        params-> socket,
                        params-> max_size,
                        params-> min_size,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_READH,
                    params-> timeout,
                    params-> socket,
                    params-> max_size,
                    params-> min_size,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Read huge socket data                                       */

int lsend_readh (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to read from              */
        qbyte max_size,                 /*  Size of receiving buffer         */
        qbyte min_size,                 /*  Minimum data to read, zero = all */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_readh
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.max_size                    = max_size;
    _params.min_size                    = min_size;
    _params.tag                         = tag;

    _size = put_smt_sock_readh (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "READH",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  Send event - Read huge, repeat for ever                                  */

int lsend_readrh (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to read from              */
        qbyte max_size,                 /*  Size of receiving buffer         */
        qbyte min_size,                 /*  Minimum data to read, zero = all */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_readh
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.max_size                    = max_size;
    _params.min_size                    = min_size;
    _params.tag                         = tag;

    _size = put_smt_sock_readh (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "READRH",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_writeh (
        byte **_buffer,
        struct_smt_sock_writeh *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_WRITEH,
                        params-> timeout,
                        params-> socket,
                        params-> size,
                        params-> data,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_WRITEH,
                    params-> timeout,
                    params-> socket,
                    params-> size,
                    params-> data,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write huge socket data                                      */

int lsend_writeh (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to write to               */
        qbyte size,                     /*  Amount of data to write          */
        byte *data,                     /*  Block of data to write           */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_writeh
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;
    _params.tag                         = tag;

    _size = put_smt_sock_writeh (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WRITEH",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_input (
        byte **_buffer,
        struct_smt_sock_input *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_INPUT,
                        params-> timeout,
                        params-> socket,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_INPUT,
                    params-> timeout,
                    params-> socket,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Wait for input                                              */

int lsend_input (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to wait on                */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_input
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_smt_sock_input (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "INPUT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  Send event - Wait input, repeat                                          */

int lsend_inputr (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to wait on                */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_input
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_smt_sock_input (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "INPUTR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_output (
        byte **_buffer,
        struct_smt_sock_output *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_OUTPUT,
                        params-> timeout,
                        params-> socket,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_OUTPUT,
                    params-> timeout,
                    params-> socket,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Wait for output                                             */

int lsend_output (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to wait on                */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_output
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_smt_sock_output (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "OUTPUT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_connect (
        byte **_buffer,
        struct_smt_sock_connect *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_CONNECT,
                        params-> timeout,
                        params-> type,
                        params-> host,
                        params-> service,
                        params-> port,
                        params-> address,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_CONNECT,
                    params-> timeout,
                    params-> type,
                    params-> host,
                    params-> service,
                    params-> port,
                    params-> address,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Connect to host                                             */

int lsend_connect (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        char *type,                     /*  Type, UDP or TCP                 */
        char *host,                     /*  Host, name or dotted address, or NULL */
        char *service,                  /*  Service, as name or port in ASCII, or NULL */
        dbyte port,                     /*  16-bit host port, or 0           */
        qbyte address,                  /*  32-bit host address, or 0        */
        qbyte tag)                      /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_connect
          _params;

    _params.timeout                     = timeout;
    _params.type                        = type;
    _params.host                        = host;
    _params.service                     = service;
    _params.port                        = port;
    _params.address                     = address;
    _params.tag                         = tag;

    _size = put_smt_sock_connect (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "CONNECT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_sock_flush (
        byte **_buffer,
        struct_smt_sock_flush *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_FLUSH,
                        params-> socket);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_FLUSH,
                    params-> socket);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Flush requests                                              */

int lsend_flush (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket)                   /*  Socket to flush requests for     */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_sock_flush
          _params;

    _params.socket                      = socket;

    _size = put_smt_sock_flush (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "FLUSH",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int  get_smt_sock_read_ok (
         byte *_buffer,
         /* struct_smt_sock_read_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_read_ok));
    if (*params)
      {
        ((struct_smt_sock_read_ok *) *params)-> data = NULL;
        return (exdr_read (_buffer, SMT_SOCK_READ_OK,
                   & ((struct_smt_sock_read_ok *) *params)-> timeout,
                   & ((struct_smt_sock_read_ok *) *params)-> socket,
                   & ((struct_smt_sock_read_ok *) *params)-> size,
                   & ((struct_smt_sock_read_ok *) *params)-> data,
                   & ((struct_smt_sock_read_ok *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_read_ok (
         /* struct_smt_sock_read_ok */ void **params)
{
    mem_free (((struct_smt_sock_read_ok *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_readh_ok (
         byte *_buffer,
         /* struct_smt_sock_readh_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_readh_ok));
    if (*params)
      {
        ((struct_smt_sock_readh_ok *) *params)-> data = NULL;
        return (exdr_read (_buffer, SMT_SOCK_READH_OK,
                   & ((struct_smt_sock_readh_ok *) *params)-> timeout,
                   & ((struct_smt_sock_readh_ok *) *params)-> socket,
                   & ((struct_smt_sock_readh_ok *) *params)-> size,
                   & ((struct_smt_sock_readh_ok *) *params)-> data,
                   & ((struct_smt_sock_readh_ok *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_readh_ok (
         /* struct_smt_sock_readh_ok */ void **params)
{
    mem_free (((struct_smt_sock_readh_ok *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_ok (
         byte *_buffer,
         /* struct_smt_sock_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_OK,
                   & ((struct_smt_sock_ok *) *params)-> socket,
                   & ((struct_smt_sock_ok *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_ok (
         /* struct_smt_sock_ok */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_sock_error (
         byte *_buffer,
         /* struct_smt_sock_error */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_error));
    if (*params)
      {
        ((struct_smt_sock_error *) *params)-> message = NULL;
        return (exdr_read (_buffer, SMT_SOCK_ERROR,
                   & ((struct_smt_sock_error *) *params)-> message,
                   & ((struct_smt_sock_error *) *params)-> socket,
                   & ((struct_smt_sock_error *) *params)-> tag));
      }
    else
        return -1;
}

void free_smt_sock_error (
         /* struct_smt_sock_error */ void **params)
{
    mem_free (((struct_smt_sock_error *) *params)-> message);
    mem_free (*params);
    *params = NULL;
}

/*---------------------------------------------------------------------------
 *  Message functions for smttime - Timer agent.
 *---------------------------------------------------------------------------*/

int  get_smt_time_alarm (
         byte *_buffer,
         /* struct_smt_time_alarm */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_time_alarm));
    if (*params)
      {
        ((struct_smt_time_alarm *) *params)-> tag_data = NULL;
        return (exdr_read (_buffer, SMT_TIME_ALARM,
                   & ((struct_smt_time_alarm *) *params)-> days,
                   & ((struct_smt_time_alarm *) *params)-> csecs,
                   & ((struct_smt_time_alarm *) *params)-> tag_size,
                   & ((struct_smt_time_alarm *) *params)-> tag_data));
      }
    else
        return -1;
}

void free_smt_time_alarm (
         /* struct_smt_time_alarm */ void **params)
{
    mem_free (((struct_smt_time_alarm *) *params)-> tag_data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_time_clock (
         byte *_buffer,
         /* struct_smt_time_clock */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_time_clock));
    if (*params)
      {
        ((struct_smt_time_clock *) *params)-> tag_data = NULL;
        return (exdr_read (_buffer, SMT_TIME_CLOCK,
                   & ((struct_smt_time_clock *) *params)-> days,
                   & ((struct_smt_time_clock *) *params)-> csecs,
                   & ((struct_smt_time_clock *) *params)-> cycles,
                   & ((struct_smt_time_clock *) *params)-> tag_size,
                   & ((struct_smt_time_clock *) *params)-> tag_data));
      }
    else
        return -1;
}

void free_smt_time_clock (
         /* struct_smt_time_clock */ void **params)
{
    mem_free (((struct_smt_time_clock *) *params)-> tag_data);
    mem_free (*params);
    *params = NULL;
}

int put_smt_time_reply (
        byte **_buffer,
        struct_smt_time_reply *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TIME_REPLY,
                        params-> tag_size,
                        params-> tag_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TIME_REPLY,
                    params-> tag_size,
                    params-> tag_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Alarm signal                                                */

int lsend_time_reply (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        word  tag_size,                 /*  User-defined data size           */
        byte *tag_data)                 /*  User-defined data block          */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_time_reply
          _params;

    _params.tag_size                    = tag_size;
    _params.tag_data                    = tag_data;

    _size = put_smt_time_reply (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "TIME_REPLY",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_time_alarm (
        byte **_buffer,
        struct_smt_time_alarm *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TIME_ALARM,
                        params-> days,
                        params-> csecs,
                        params-> tag_size,
                        params-> tag_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TIME_ALARM,
                    params-> days,
                    params-> csecs,
                    params-> tag_size,
                    params-> tag_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Ask for single alarm                                        */

int lsend_alarm (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte days,                     /*  Time/delay in days               */
        qbyte csecs,                    /*  Time/delay in 1/100th seconds    */
        word  tag_size,                 /*  User-defined data size           */
        byte *tag_data)                 /*  User-defined data block          */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_time_alarm
          _params;

    _params.days                        = days;
    _params.csecs                       = csecs;
    _params.tag_size                    = tag_size;
    _params.tag_data                    = tag_data;

    _size = put_smt_time_alarm (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "ALARM",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_time_clock (
        byte **_buffer,
        struct_smt_time_clock *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TIME_CLOCK,
                        params-> days,
                        params-> csecs,
                        params-> cycles,
                        params-> tag_size,
                        params-> tag_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TIME_CLOCK,
                    params-> days,
                    params-> csecs,
                    params-> cycles,
                    params-> tag_size,
                    params-> tag_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Ask for repeated alarm                                      */

int lsend_clock (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte days,                     /*  Time/delay in days               */
        qbyte csecs,                    /*  Time/delay in 1/100th seconds    */
        word  cycles,                   /*  Cycle count; zero = forever      */
        word  tag_size,                 /*  User-defined data size           */
        byte *tag_data)                 /*  User-defined data block          */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_time_clock
          _params;

    _params.days                        = days;
    _params.csecs                       = csecs;
    _params.cycles                      = cycles;
    _params.tag_size                    = tag_size;
    _params.tag_data                    = tag_data;

    _size = put_smt_time_clock (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "CLOCK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int  get_smt_time_reply (
         byte *_buffer,
         /* struct_smt_time_reply */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_time_reply));
    if (*params)
      {
        ((struct_smt_time_reply *) *params)-> tag_data = NULL;
        return (exdr_read (_buffer, SMT_TIME_REPLY,
                   & ((struct_smt_time_reply *) *params)-> tag_size,
                   & ((struct_smt_time_reply *) *params)-> tag_data));
      }
    else
        return -1;
}

void free_smt_time_reply (
         /* struct_smt_time_reply */ void **params)
{
    mem_free (((struct_smt_time_reply *) *params)-> tag_data);
    mem_free (*params);
    *params = NULL;
}

/*---------------------------------------------------------------------------
 *  Message functions for smtslot - Time slot agent.
 *---------------------------------------------------------------------------*/

int  get_smt_slot_spec (
         byte *_buffer,
         /* struct_smt_slot_spec */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_slot_spec));
    if (*params)
      {
        ((struct_smt_slot_spec *) *params)-> specification = NULL;
        return (exdr_read (_buffer, SMT_SLOT_SPEC,
                   & ((struct_smt_slot_spec *) *params)-> specification));
      }
    else
        return -1;
}

void free_smt_slot_spec (
         /* struct_smt_slot_spec */ void **params)
{
    mem_free (((struct_smt_slot_spec *) *params)-> specification);
    mem_free (*params);
    *params = NULL;
}

int put_smt_slot_spec (
        byte **_buffer,
        struct_smt_slot_spec *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_SLOT_SPEC,
                        params-> specification);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SLOT_SPEC,
                    params-> specification);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Specify a time slot                                         */

int lsend_specify (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *specification)            /*  Time slot specification          */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_slot_spec
          _params;

    _params.specification               = specification;

    _size = put_smt_slot_spec (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SPECIFY",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for smttran - Transfer agent.
 *---------------------------------------------------------------------------*/

int  get_smt_tran_putb (
         byte *_buffer,
         /* struct_smt_tran_putb */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_putb));
    if (*params)
      {
        ((struct_smt_tran_putb *) *params)-> data = NULL;
        return (exdr_read (_buffer, SMT_TRAN_PUTB,
                   & ((struct_smt_tran_putb *) *params)-> socket,
                   & ((struct_smt_tran_putb *) *params)-> size,
                   & ((struct_smt_tran_putb *) *params)-> data));
      }
    else
        return -1;
}

void free_smt_tran_putb (
         /* struct_smt_tran_putb */ void **params)
{
    mem_free (((struct_smt_tran_putb *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_getb (
         byte *_buffer,
         /* struct_smt_tran_getb */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_getb));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_GETB,
                   & ((struct_smt_tran_getb *) *params)-> socket));
      }
    else
        return -1;
}

void free_smt_tran_getb (
         /* struct_smt_tran_getb */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_puth (
         byte *_buffer,
         /* struct_smt_tran_puth */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_puth));
    if (*params)
      {
        ((struct_smt_tran_puth *) *params)-> data = NULL;
        return (exdr_read (_buffer, SMT_TRAN_PUTH,
                   & ((struct_smt_tran_puth *) *params)-> socket,
                   & ((struct_smt_tran_puth *) *params)-> size,
                   & ((struct_smt_tran_puth *) *params)-> data));
      }
    else
        return -1;
}

void free_smt_tran_puth (
         /* struct_smt_tran_puth */ void **params)
{
    mem_free (((struct_smt_tran_puth *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_geth (
         byte *_buffer,
         /* struct_smt_tran_geth */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_geth));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_GETH,
                   & ((struct_smt_tran_geth *) *params)-> socket));
      }
    else
        return -1;
}

void free_smt_tran_geth (
         /* struct_smt_tran_geth */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_putf (
         byte *_buffer,
         /* struct_smt_tran_putf */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_putf));
    if (*params)
      {
        ((struct_smt_tran_putf *) *params)-> filename = NULL;
        return (exdr_read (_buffer, SMT_TRAN_PUTF,
                   & ((struct_smt_tran_putf *) *params)-> socket,
                   & ((struct_smt_tran_putf *) *params)-> filename,
                   & ((struct_smt_tran_putf *) *params)-> filetype,
                   & ((struct_smt_tran_putf *) *params)-> start,
                   & ((struct_smt_tran_putf *) *params)-> end));
      }
    else
        return -1;
}

void free_smt_tran_putf (
         /* struct_smt_tran_putf */ void **params)
{
    mem_free (((struct_smt_tran_putf *) *params)-> filename);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_getf (
         byte *_buffer,
         /* struct_smt_tran_getf */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_getf));
    if (*params)
      {
        ((struct_smt_tran_getf *) *params)-> filename = NULL;
        return (exdr_read (_buffer, SMT_TRAN_GETF,
                   & ((struct_smt_tran_getf *) *params)-> socket,
                   & ((struct_smt_tran_getf *) *params)-> filename,
                   & ((struct_smt_tran_getf *) *params)-> filetype,
                   & ((struct_smt_tran_getf *) *params)-> start,
                   & ((struct_smt_tran_getf *) *params)-> end,
                   & ((struct_smt_tran_getf *) *params)-> append));
      }
    else
        return -1;
}

void free_smt_tran_getf (
         /* struct_smt_tran_getf */ void **params)
{
    mem_free (((struct_smt_tran_getf *) *params)-> filename);
    mem_free (*params);
    *params = NULL;
}

int put_smt_tran_putb_ok (
        byte **_buffer,
        struct_smt_tran_putb_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTB_OK,
                        params-> size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTB_OK,
                    params-> size);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Block written okay                                          */

int lsend_tran_putb_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte size)                     /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_putb_ok
          _params;

    _params.size                        = size;

    _size = put_smt_tran_putb_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_PUTB_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_getb_ok (
        byte **_buffer,
        struct_smt_tran_getb_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETB_OK,
                        params-> size,
                        params-> data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETB_OK,
                    params-> size,
                    params-> data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Block read okay                                             */

int lsend_tran_getb_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        word  size,                     /*  Amount of data received          */
        byte *data)                     /*  Block of data received           */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_getb_ok
          _params;

    _params.size                        = size;
    _params.data                        = data;

    _size = put_smt_tran_getb_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_GETB_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_puth_ok (
        byte **_buffer,
        struct_smt_tran_puth_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTH_OK,
                        params-> size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTH_OK,
                    params-> size);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Block written okay                                          */

int lsend_tran_puth_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size)                     /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_puth_ok
          _params;

    _params.size                        = size;

    _size = put_smt_tran_puth_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_PUTH_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_geth_ok (
        byte **_buffer,
        struct_smt_tran_geth_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETH_OK,
                        params-> size,
                        params-> data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETH_OK,
                    params-> size,
                    params-> data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Block read okay                                             */

int lsend_tran_geth_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size,                     /*  Amount of data received          */
        byte *data)                     /*  Block of data received           */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_geth_ok
          _params;

    _params.size                        = size;
    _params.data                        = data;

    _size = put_smt_tran_geth_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_GETH_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_putf_ok (
        byte **_buffer,
        struct_smt_tran_putf_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTF_OK,
                        params-> size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTF_OK,
                    params-> size);
    else
        _size = 0;

    return (_size);
}

/*  Send event - File written okay                                           */

int lsend_tran_putf_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size)                     /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_putf_ok
          _params;

    _params.size                        = size;

    _size = put_smt_tran_putf_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_PUTF_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_getf_ok (
        byte **_buffer,
        struct_smt_tran_getf_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETF_OK,
                        params-> size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETF_OK,
                    params-> size);
    else
        _size = 0;

    return (_size);
}

/*  Send event - File received okay                                          */

int lsend_tran_getf_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size)                     /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_getf_ok
          _params;

    _params.size                        = size;

    _size = put_smt_tran_getf_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_GETF_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_putb (
        byte **_buffer,
        struct_smt_tran_putb *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTB,
                        params-> socket,
                        params-> size,
                        params-> data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTB,
                    params-> socket,
                    params-> size,
                    params-> data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write block to socket                                       */

int lsend_put_block (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        word  size,                     /*  Amount of data to send           */
        byte *data)                     /*  Block of data to send            */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_putb
          _params;

    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;

    _size = put_smt_tran_putb (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "PUT_BLOCK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_getb (
        byte **_buffer,
        struct_smt_tran_getb *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETB,
                        params-> socket);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETB,
                    params-> socket);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Read block from socket                                      */

int lsend_get_block (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket)                   /*  Socket for input                 */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_getb
          _params;

    _params.socket                      = socket;

    _size = put_smt_tran_getb (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_BLOCK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_puth (
        byte **_buffer,
        struct_smt_tran_puth *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTH,
                        params-> socket,
                        params-> size,
                        params-> data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTH,
                    params-> socket,
                    params-> size,
                    params-> data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write huge block to socket                                  */

int lsend_put_huge (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        qbyte size,                     /*  Amount of data to send           */
        byte *data)                     /*  Block of data to send            */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_puth
          _params;

    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;

    _size = put_smt_tran_puth (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "PUT_HUGE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_geth (
        byte **_buffer,
        struct_smt_tran_geth *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETH,
                        params-> socket);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETH,
                    params-> socket);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Read huge block from socket                                 */

int lsend_get_huge (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket)                   /*  Socket for input                 */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_geth
          _params;

    _params.socket                      = socket;

    _size = put_smt_tran_geth (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_HUGE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_putf (
        byte **_buffer,
        struct_smt_tran_putf *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTF,
                        params-> socket,
                        params-> filename,
                        params-> filetype,
                        params-> start,
                        params-> end);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTF,
                    params-> socket,
                    params-> filename,
                    params-> filetype,
                    params-> start,
                    params-> end);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write file to socket                                        */

int lsend_put_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        char *filename,                 /*  Name of file to send             */
        dbyte filetype,                 /*  0=binary, 1=ASCII                */
        qbyte start,                    /*  Starting offset; 0 = start       */
        qbyte end)                      /*  Ending offset; 0 = end           */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_putf
          _params;

    _params.socket                      = socket;
    _params.filename                    = filename;
    _params.filetype                    = filetype;
    _params.start                       = start;
    _params.end                         = end;

    _size = put_smt_tran_putf (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "PUT_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_tran_getf (
        byte **_buffer,
        struct_smt_tran_getf *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETF,
                        params-> socket,
                        params-> filename,
                        params-> filetype,
                        params-> start,
                        params-> end,
                        params-> append);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETF,
                    params-> socket,
                    params-> filename,
                    params-> filetype,
                    params-> start,
                    params-> end,
                    params-> append);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Read file from socket                                       */

int lsend_get_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for input                 */
        char *filename,                 /*  Name of file to receive          */
        dbyte filetype,                 /*  0=binary, 1=ASCII                */
        qbyte start,                    /*  Starting offset; 0 = start       */
        qbyte end,                      /*  Ending offset; 0 = end           */
        Bool  append)                   /*  1 = append existing              */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_tran_getf
          _params;

    _params.socket                      = socket;
    _params.filename                    = filename;
    _params.filetype                    = filetype;
    _params.start                       = start;
    _params.end                         = end;
    _params.append                      = append;

    _size = put_smt_tran_getf (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int  get_smt_tran_putb_ok (
         byte *_buffer,
         /* struct_smt_tran_putb_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_putb_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_PUTB_OK,
                   & ((struct_smt_tran_putb_ok *) *params)-> size));
      }
    else
        return -1;
}

void free_smt_tran_putb_ok (
         /* struct_smt_tran_putb_ok */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_getb_ok (
         byte *_buffer,
         /* struct_smt_tran_getb_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_getb_ok));
    if (*params)
      {
        ((struct_smt_tran_getb_ok *) *params)-> data = NULL;
        return (exdr_read (_buffer, SMT_TRAN_GETB_OK,
                   & ((struct_smt_tran_getb_ok *) *params)-> size,
                   & ((struct_smt_tran_getb_ok *) *params)-> data));
      }
    else
        return -1;
}

void free_smt_tran_getb_ok (
         /* struct_smt_tran_getb_ok */ void **params)
{
    mem_free (((struct_smt_tran_getb_ok *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_puth_ok (
         byte *_buffer,
         /* struct_smt_tran_puth_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_puth_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_PUTH_OK,
                   & ((struct_smt_tran_puth_ok *) *params)-> size));
      }
    else
        return -1;
}

void free_smt_tran_puth_ok (
         /* struct_smt_tran_puth_ok */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_geth_ok (
         byte *_buffer,
         /* struct_smt_tran_geth_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_geth_ok));
    if (*params)
      {
        ((struct_smt_tran_geth_ok *) *params)-> data = NULL;
        return (exdr_read (_buffer, SMT_TRAN_GETH_OK,
                   & ((struct_smt_tran_geth_ok *) *params)-> size,
                   & ((struct_smt_tran_geth_ok *) *params)-> data));
      }
    else
        return -1;
}

void free_smt_tran_geth_ok (
         /* struct_smt_tran_geth_ok */ void **params)
{
    mem_free (((struct_smt_tran_geth_ok *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_putf_ok (
         byte *_buffer,
         /* struct_smt_tran_putf_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_putf_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_PUTF_OK,
                   & ((struct_smt_tran_putf_ok *) *params)-> size));
      }
    else
        return -1;
}

void free_smt_tran_putf_ok (
         /* struct_smt_tran_putf_ok */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_tran_getf_ok (
         byte *_buffer,
         /* struct_smt_tran_getf_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_getf_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_GETF_OK,
                   & ((struct_smt_tran_getf_ok *) *params)-> size));
      }
    else
        return -1;
}

void free_smt_tran_getf_ok (
         /* struct_smt_tran_getf_ok */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

/*---------------------------------------------------------------------------
 *  Message functions for smtftpd - FTP data transfer agent.
 *---------------------------------------------------------------------------*/

int  get_smt_ftpd_putf (
         byte *_buffer,
         /* struct_smt_ftpd_putf */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_putf));
    if (*params)
      {
        ((struct_smt_ftpd_putf *) *params)-> filename = NULL;
        return (exdr_read (_buffer, SMT_FTPD_PUTF,
                   & ((struct_smt_ftpd_putf *) *params)-> id,
                   & ((struct_smt_ftpd_putf *) *params)-> passive,
                   & ((struct_smt_ftpd_putf *) *params)-> filetype,
                   & ((struct_smt_ftpd_putf *) *params)-> filename,
                   & ((struct_smt_ftpd_putf *) *params)-> start_position,
                   & ((struct_smt_ftpd_putf *) *params)-> host_address,
                   & ((struct_smt_ftpd_putf *) *params)-> port_number));
      }
    else
        return -1;
}

void free_smt_ftpd_putf (
         /* struct_smt_ftpd_putf */ void **params)
{
    mem_free (((struct_smt_ftpd_putf *) *params)-> filename);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_ftpd_getf (
         byte *_buffer,
         /* struct_smt_ftpd_getf */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_getf));
    if (*params)
      {
        ((struct_smt_ftpd_getf *) *params)-> filename = NULL;
        return (exdr_read (_buffer, SMT_FTPD_GETF,
                   & ((struct_smt_ftpd_getf *) *params)-> id,
                   & ((struct_smt_ftpd_getf *) *params)-> passive,
                   & ((struct_smt_ftpd_getf *) *params)-> filetype,
                   & ((struct_smt_ftpd_getf *) *params)-> filename,
                   & ((struct_smt_ftpd_getf *) *params)-> start_position,
                   & ((struct_smt_ftpd_getf *) *params)-> host_address,
                   & ((struct_smt_ftpd_getf *) *params)-> port_number));
      }
    else
        return -1;
}

void free_smt_ftpd_getf (
         /* struct_smt_ftpd_getf */ void **params)
{
    mem_free (((struct_smt_ftpd_getf *) *params)-> filename);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_ftpd_append (
         byte *_buffer,
         /* struct_smt_ftpd_append */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_append));
    if (*params)
      {
        ((struct_smt_ftpd_append *) *params)-> filename = NULL;
        return (exdr_read (_buffer, SMT_FTPD_APPEND,
                   & ((struct_smt_ftpd_append *) *params)-> id,
                   & ((struct_smt_ftpd_append *) *params)-> passive,
                   & ((struct_smt_ftpd_append *) *params)-> filetype,
                   & ((struct_smt_ftpd_append *) *params)-> filename,
                   & ((struct_smt_ftpd_append *) *params)-> host_address,
                   & ((struct_smt_ftpd_append *) *params)-> port_number));
      }
    else
        return -1;
}

void free_smt_ftpd_append (
         /* struct_smt_ftpd_append */ void **params)
{
    mem_free (((struct_smt_ftpd_append *) *params)-> filename);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_ftpd_passive (
         byte *_buffer,
         /* struct_smt_ftpd_passive */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_passive));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_FTPD_PASSIVE,
                   & ((struct_smt_ftpd_passive *) *params)-> id,
                   & ((struct_smt_ftpd_passive *) *params)-> first_port,
                   & ((struct_smt_ftpd_passive *) *params)-> ip_address));
      }
    else
        return -1;
}

void free_smt_ftpd_passive (
         /* struct_smt_ftpd_passive */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_ftpd_abort (
         byte *_buffer,
         /* struct_smt_ftpd_abort */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_abort));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_FTPD_ABORT,
                   & ((struct_smt_ftpd_abort *) *params)-> id));
      }
    else
        return -1;
}

void free_smt_ftpd_abort (
         /* struct_smt_ftpd_abort */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_ftpd_closectrl (
         byte *_buffer,
         /* struct_smt_ftpd_closectrl */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_closectrl));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_FTPD_CLOSECTRL,
                   & ((struct_smt_ftpd_closectrl *) *params)-> id));
      }
    else
        return -1;
}

void free_smt_ftpd_closectrl (
         /* struct_smt_ftpd_closectrl */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int put_smt_ftpd_pass_ok (
        byte **_buffer,
        struct_smt_ftpd_pass_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_PASS_OK,
                        params-> host_address,
                        params-> port_number);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_PASS_OK,
                    params-> host_address,
                    params-> port_number);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent request handled ok                                    */

int lsend_ftpd_pass_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte host_address,             /*  IP address for host              */
        dbyte port_number)              /*  Port on remote host              */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_ftpd_pass_ok
          _params;

    _params.host_address                = host_address;
    _params.port_number                 = port_number;

    _size = put_smt_ftpd_pass_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_PASS_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_ftpd_putf (
        byte **_buffer,
        struct_smt_ftpd_putf *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_PUTF,
                        params-> id,
                        params-> passive,
                        params-> filetype,
                        params-> filename,
                        params-> start_position,
                        params-> host_address,
                        params-> port_number);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_PUTF,
                    params-> id,
                    params-> passive,
                    params-> filetype,
                    params-> filename,
                    params-> start_position,
                    params-> host_address,
                    params-> port_number);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Send file to host                                           */

int lsend_ftpd_put_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id,                       /*  ID for connection                */
        dbyte passive,                  /*  0/1 = active/passive connection  */
        dbyte filetype,                 /*  Type of file to transfer         */
        char *filename,                 /*  Name of file to transfer         */
        qbyte start_position,           /*  Start offset for file            */
        qbyte host_address,             /*  IP address for host              */
        dbyte port_number)              /*  Port on remote host              */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_ftpd_putf
          _params;

    _params.id                          = id;
    _params.passive                     = passive;
    _params.filetype                    = filetype;
    _params.filename                    = filename;
    _params.start_position              = start_position;
    _params.host_address                = host_address;
    _params.port_number                 = port_number;

    _size = put_smt_ftpd_putf (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_PUT_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_ftpd_getf (
        byte **_buffer,
        struct_smt_ftpd_getf *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_GETF,
                        params-> id,
                        params-> passive,
                        params-> filetype,
                        params-> filename,
                        params-> start_position,
                        params-> host_address,
                        params-> port_number);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_GETF,
                    params-> id,
                    params-> passive,
                    params-> filetype,
                    params-> filename,
                    params-> start_position,
                    params-> host_address,
                    params-> port_number);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Receive file from host                                      */

int lsend_ftpd_get_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id,                       /*  ID for connection                */
        dbyte passive,                  /*  0/1 = passive/active connection  */
        dbyte filetype,                 /*  Type of file to transfer         */
        char *filename,                 /*  Name of file to transfer         */
        qbyte start_position,           /*  Start offset for file            */
        qbyte host_address,             /*  IP address for host              */
        dbyte port_number)              /*  Port on remote host              */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_ftpd_getf
          _params;

    _params.id                          = id;
    _params.passive                     = passive;
    _params.filetype                    = filetype;
    _params.filename                    = filename;
    _params.start_position              = start_position;
    _params.host_address                = host_address;
    _params.port_number                 = port_number;

    _size = put_smt_ftpd_getf (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_GET_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_ftpd_append (
        byte **_buffer,
        struct_smt_ftpd_append *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_APPEND,
                        params-> id,
                        params-> passive,
                        params-> filetype,
                        params-> filename,
                        params-> host_address,
                        params-> port_number);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_APPEND,
                    params-> id,
                    params-> passive,
                    params-> filetype,
                    params-> filename,
                    params-> host_address,
                    params-> port_number);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Append file from host                                       */

int lsend_ftpd_append_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id,                       /*  ID for connection                */
        dbyte passive,                  /*  0/1 = passive/active connection  */
        dbyte filetype,                 /*  Type of file to transfer         */
        char *filename,                 /*  Name of file to transfer         */
        qbyte host_address,             /*  IP address for host              */
        dbyte port_number)              /*  Port on remote host              */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_ftpd_append
          _params;

    _params.id                          = id;
    _params.passive                     = passive;
    _params.filetype                    = filetype;
    _params.filename                    = filename;
    _params.host_address                = host_address;
    _params.port_number                 = port_number;

    _size = put_smt_ftpd_append (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_APPEND_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_ftpd_passive (
        byte **_buffer,
        struct_smt_ftpd_passive *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_PASSIVE,
                        params-> id,
                        params-> first_port,
                        params-> ip_address);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_PASSIVE,
                    params-> id,
                    params-> first_port,
                    params-> ip_address);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Request passive connection                                  */

int lsend_ftpd_passive (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id,                       /*  ID for control connection        */
        dbyte first_port,               /*  First port to listen on          */
        qbyte ip_address)               /*  IP address to listen on          */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_ftpd_passive
          _params;

    _params.id                          = id;
    _params.first_port                  = first_port;
    _params.ip_address                  = ip_address;

    _size = put_smt_ftpd_passive (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_PASSIVE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_ftpd_abort (
        byte **_buffer,
        struct_smt_ftpd_abort *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_ABORT,
                        params-> id);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_ABORT,
                    params-> id);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Abort file transfer                                         */

int lsend_ftpd_abort (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id)                       /*  ID for control connection        */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_ftpd_abort
          _params;

    _params.id                          = id;

    _size = put_smt_ftpd_abort (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_ABORT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_ftpd_closectrl (
        byte **_buffer,
        struct_smt_ftpd_closectrl *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_CLOSECTRL,
                        params-> id);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_CLOSECTRL,
                    params-> id);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Close control connection                                    */

int lsend_ftpd_closectrl (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id)                       /*  ID for control connection        */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_ftpd_closectrl
          _params;

    _params.id                          = id;

    _size = put_smt_ftpd_closectrl (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_CLOSECTRL",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int  get_smt_ftpd_pass_ok (
         byte *_buffer,
         /* struct_smt_ftpd_pass_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_pass_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_FTPD_PASS_OK,
                   & ((struct_smt_ftpd_pass_ok *) *params)-> host_address,
                   & ((struct_smt_ftpd_pass_ok *) *params)-> port_number));
      }
    else
        return -1;
}

void free_smt_ftpd_pass_ok (
         /* struct_smt_ftpd_pass_ok */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

/*---------------------------------------------------------------------------
 *  Message functions for WSX - WSX agent.
 *---------------------------------------------------------------------------*/

int  get_smt_wsx_install (
         byte *_buffer,
         /* struct_smt_wsx_install */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_install));
    if (*params)
      {
        ((struct_smt_wsx_install *) *params)-> virtual_host = NULL;
        ((struct_smt_wsx_install *) *params)-> path = NULL;
        ((struct_smt_wsx_install *) *params)-> agent = NULL;
        return (exdr_read (_buffer, SMT_WSX_INSTALL,
                   & ((struct_smt_wsx_install *) *params)-> virtual_host,
                   & ((struct_smt_wsx_install *) *params)-> path,
                   & ((struct_smt_wsx_install *) *params)-> agent));
      }
    else
        return -1;
}

void free_smt_wsx_install (
         /* struct_smt_wsx_install */ void **params)
{
    mem_free (((struct_smt_wsx_install *) *params)-> virtual_host);
    mem_free (((struct_smt_wsx_install *) *params)-> path);
    mem_free (((struct_smt_wsx_install *) *params)-> agent);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_cancel (
         byte *_buffer,
         /* struct_smt_wsx_cancel */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_cancel));
    if (*params)
      {
        ((struct_smt_wsx_cancel *) *params)-> virtual_host = NULL;
        ((struct_smt_wsx_cancel *) *params)-> path = NULL;
        return (exdr_read (_buffer, SMT_WSX_CANCEL,
                   & ((struct_smt_wsx_cancel *) *params)-> virtual_host,
                   & ((struct_smt_wsx_cancel *) *params)-> path));
      }
    else
        return -1;
}

void free_smt_wsx_cancel (
         /* struct_smt_wsx_cancel */ void **params)
{
    mem_free (((struct_smt_wsx_cancel *) *params)-> virtual_host);
    mem_free (((struct_smt_wsx_cancel *) *params)-> path);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_request (
         byte *_buffer,
         /* struct_smt_wsx_request */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_request));
    if (*params)
      {
        ((struct_smt_wsx_request *) *params)-> request_url = NULL;
        ((struct_smt_wsx_request *) *params)-> arguments = NULL;
        ((struct_smt_wsx_request *) *params)-> virtual_host = NULL;
        ((struct_smt_wsx_request *) *params)-> filename = NULL;
        ((struct_smt_wsx_request *) *params)-> post_data = NULL;
        ((struct_smt_wsx_request *) *params)-> symbols_data = NULL;
        ((struct_smt_wsx_request *) *params)-> config_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_REQUEST,
                   & ((struct_smt_wsx_request *) *params)-> request_url,
                   & ((struct_smt_wsx_request *) *params)-> arguments,
                   & ((struct_smt_wsx_request *) *params)-> virtual_host,
                   & ((struct_smt_wsx_request *) *params)-> filename,
                   & ((struct_smt_wsx_request *) *params)-> post_data,
                   & ((struct_smt_wsx_request *) *params)-> symbols_size,
                   & ((struct_smt_wsx_request *) *params)-> symbols_data,
                   & ((struct_smt_wsx_request *) *params)-> config_size,
                   & ((struct_smt_wsx_request *) *params)-> config_data));
      }
    else
        return -1;
}

void free_smt_wsx_request (
         /* struct_smt_wsx_request */ void **params)
{
    mem_free (((struct_smt_wsx_request *) *params)-> request_url);
    mem_free (((struct_smt_wsx_request *) *params)-> arguments);
    mem_free (((struct_smt_wsx_request *) *params)-> virtual_host);
    mem_free (((struct_smt_wsx_request *) *params)-> filename);
    mem_free (((struct_smt_wsx_request *) *params)-> post_data);
    mem_free (((struct_smt_wsx_request *) *params)-> symbols_data);
    mem_free (((struct_smt_wsx_request *) *params)-> config_data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_reqbin (
         byte *_buffer,
         /* struct_smt_wsx_reqbin */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_reqbin));
    if (*params)
      {
        ((struct_smt_wsx_reqbin *) *params)-> request_url = NULL;
        ((struct_smt_wsx_reqbin *) *params)-> arguments = NULL;
        ((struct_smt_wsx_reqbin *) *params)-> virtual_host = NULL;
        ((struct_smt_wsx_reqbin *) *params)-> filename = NULL;
        ((struct_smt_wsx_reqbin *) *params)-> post_data = NULL;
        ((struct_smt_wsx_reqbin *) *params)-> symbols_data = NULL;
        ((struct_smt_wsx_reqbin *) *params)-> config_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_REQBIN,
                   & ((struct_smt_wsx_reqbin *) *params)-> request_url,
                   & ((struct_smt_wsx_reqbin *) *params)-> arguments,
                   & ((struct_smt_wsx_reqbin *) *params)-> virtual_host,
                   & ((struct_smt_wsx_reqbin *) *params)-> post_size,
                   & ((struct_smt_wsx_reqbin *) *params)-> filename,
                   & ((struct_smt_wsx_reqbin *) *params)-> post_data,
                   & ((struct_smt_wsx_reqbin *) *params)-> symbols_size,
                   & ((struct_smt_wsx_reqbin *) *params)-> symbols_data,
                   & ((struct_smt_wsx_reqbin *) *params)-> config_size,
                   & ((struct_smt_wsx_reqbin *) *params)-> config_data));
      }
    else
        return -1;
}

void free_smt_wsx_reqbin (
         /* struct_smt_wsx_reqbin */ void **params)
{
    mem_free (((struct_smt_wsx_reqbin *) *params)-> request_url);
    mem_free (((struct_smt_wsx_reqbin *) *params)-> arguments);
    mem_free (((struct_smt_wsx_reqbin *) *params)-> virtual_host);
    mem_free (((struct_smt_wsx_reqbin *) *params)-> filename);
    mem_free (((struct_smt_wsx_reqbin *) *params)-> post_data);
    mem_free (((struct_smt_wsx_reqbin *) *params)-> symbols_data);
    mem_free (((struct_smt_wsx_reqbin *) *params)-> config_data);
    mem_free (*params);
    *params = NULL;
}

int put_smt_wsx_ok (
        byte **_buffer,
        struct_smt_wsx_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_OK,
                        params-> html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_OK,
                    params-> html_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent request handled ok                                    */

int lsend_wsx_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *html_data)                /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_ok
          _params;

    _params.html_data                   = html_data;

    _size = put_smt_wsx_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_bin (
        byte **_buffer,
        struct_smt_wsx_bin *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_BIN,
                        params-> html_size,
                        params-> html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_BIN,
                    params-> html_size,
                    params-> html_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent request handled ok                                    */

int lsend_wsx_bin (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte html_size,                /*  HTML response size               */
        byte *html_data)                /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_bin
          _params;

    _params.html_size                   = html_size;
    _params.html_data                   = html_data;

    _size = put_smt_wsx_bin (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_BIN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_multipart (
        byte **_buffer,
        struct_smt_wsx_multipart *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_MULTIPART,
                        params-> html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_MULTIPART,
                    params-> html_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent multipart response                                    */

int lsend_wsx_multipart (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *html_data)                /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_multipart
          _params;

    _params.html_data                   = html_data;

    _size = put_smt_wsx_multipart (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_MULTIPART",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_mbin (
        byte **_buffer,
        struct_smt_wsx_mbin *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_MBIN,
                        params-> html_size,
                        params-> html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_MBIN,
                    params-> html_size,
                    params-> html_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent multipart response                                    */

int lsend_wsx_mbin (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte html_size,                /*  HTML response size               */
        byte *html_data)                /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_mbin
          _params;

    _params.html_size                   = html_size;
    _params.html_data                   = html_data;

    _size = put_smt_wsx_mbin (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_MBIN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_restart (
        byte **_buffer,
        struct_smt_wsx_restart *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_RESTART,
                        params-> html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_RESTART,
                    params-> html_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent requested restart                                     */

int lsend_wsx_restart (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *html_data)                /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_restart
          _params;

    _params.html_data                   = html_data;

    _size = put_smt_wsx_restart (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_RESTART",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_kill (
        byte **_buffer,
        struct_smt_wsx_kill *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_KILL,
                        params-> html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_KILL,
                    params-> html_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent requested shutdown                                    */

int lsend_wsx_kill (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *html_data)                /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_kill
          _params;

    _params.html_data                   = html_data;

    _size = put_smt_wsx_kill (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_KILL",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_error (
        byte **_buffer,
        struct_smt_wsx_error *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_ERROR,
                        params-> error_code);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_ERROR,
                    params-> error_code);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent request failed                                        */

int lsend_wsx_error (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte error_code)               /*  HTTP response code               */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_error
          _params;

    _params.error_code                  = error_code;

    _size = put_smt_wsx_error (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_ERROR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_redirect (
        byte **_buffer,
        struct_smt_wsx_redirect *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_REDIRECT,
                        params-> new_url);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_REDIRECT,
                    params-> new_url);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Agent redirected request                                    */

int lsend_wsx_redirect (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *new_url)                  /*  Redirect location                */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_redirect
          _params;

    _params.new_url                     = new_url;

    _size = put_smt_wsx_redirect (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_REDIRECT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_install (
        byte **_buffer,
        struct_smt_wsx_install *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_INSTALL,
                        params-> virtual_host,
                        params-> path,
                        params-> agent);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_INSTALL,
                    params-> virtual_host,
                    params-> path,
                    params-> agent);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Install SMT_WSX alias                                       */

int lsend_wsx_install (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *virtual_host,             /*  Virtual host name                */
        char *path,                     /*  URL pattern to match             */
        char *agent)                    /*  Name of WSX agent                */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_install
          _params;

    _params.virtual_host                = virtual_host;
    _params.path                        = path;
    _params.agent                       = agent;

    _size = put_smt_wsx_install (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_INSTALL",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_cancel (
        byte **_buffer,
        struct_smt_wsx_cancel *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_CANCEL,
                        params-> virtual_host,
                        params-> path);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_CANCEL,
                    params-> virtual_host,
                    params-> path);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Cancel SMT_WSX alias                                        */

int lsend_wsx_cancel (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *virtual_host,             /*  Virtual host name                */
        char *path)                     /*  URL pattern to match             */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_cancel
          _params;

    _params.virtual_host                = virtual_host;
    _params.path                        = path;

    _size = put_smt_wsx_cancel (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_CANCEL",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_request (
        byte **_buffer,
        struct_smt_wsx_request *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_REQUEST,
                        params-> request_url,
                        params-> arguments,
                        params-> virtual_host,
                        params-> filename,
                        params-> post_data,
                        params-> symbols_size,
                        params-> symbols_data,
                        params-> config_size,
                        params-> config_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_REQUEST,
                    params-> request_url,
                    params-> arguments,
                    params-> virtual_host,
                    params-> filename,
                    params-> post_data,
                    params-> symbols_size,
                    params-> symbols_data,
                    params-> config_size,
                    params-> config_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - SMT_WSX request                                             */

int lsend_wsx_request (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *request_url,              /*  URL for WSX request              */
        char *arguments,                /*  URL arguments, if any            */
        char *virtual_host,             /*  Virtual host, if any             */
        char *filename,                 /*  Physical filename for URL        */
        char *post_data,                /*  POSTed data, if any              */
        word  symbols_size,             /*  HTTP symbol table size           */
        byte *symbols_data,             /*  HTTP symbol table data           */
        word  config_size,              /*  HTTP config table size           */
        byte *config_data)              /*  HTTP config table data           */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_request
          _params;

    _params.request_url                 = request_url;
    _params.arguments                   = arguments;
    _params.virtual_host                = virtual_host;
    _params.filename                    = filename;
    _params.post_data                   = post_data;
    _params.symbols_size                = symbols_size;
    _params.symbols_data                = symbols_data;
    _params.config_size                 = config_size;
    _params.config_data                 = config_data;

    _size = put_smt_wsx_request (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_REQUEST",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_wsx_reqbin (
        byte **_buffer,
        struct_smt_wsx_reqbin *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_REQBIN,
                        params-> request_url,
                        params-> arguments,
                        params-> virtual_host,
                        params-> post_size,
                        params-> filename,
                        params-> post_data,
                        params-> symbols_size,
                        params-> symbols_data,
                        params-> config_size,
                        params-> config_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_REQBIN,
                    params-> request_url,
                    params-> arguments,
                    params-> virtual_host,
                    params-> post_size,
                    params-> filename,
                    params-> post_data,
                    params-> symbols_size,
                    params-> symbols_data,
                    params-> config_size,
                    params-> config_data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - SMT_WSX request                                             */

int lsend_wsx_reqbin (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *request_url,              /*  URL for WSX request              */
        char *arguments,                /*  URL arguments, if any            */
        char *virtual_host,             /*  Virtual host, if any             */
        word  post_size,                /*  POSTed data size                 */
        char *filename,                 /*  Physical filename for URL        */
        byte *post_data,                /*  POSTed data                      */
        word  symbols_size,             /*  HTTP symbol table size           */
        byte *symbols_data,             /*  HTTP symbol table data           */
        word  config_size,              /*  HTTP config table size           */
        byte *config_data)              /*  HTTP config table data           */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_wsx_reqbin
          _params;

    _params.request_url                 = request_url;
    _params.arguments                   = arguments;
    _params.virtual_host                = virtual_host;
    _params.post_size                   = post_size;
    _params.filename                    = filename;
    _params.post_data                   = post_data;
    _params.symbols_size                = symbols_size;
    _params.symbols_data                = symbols_data;
    _params.config_size                 = config_size;
    _params.config_data                 = config_data;

    _size = put_smt_wsx_reqbin (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_REQBIN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int  get_smt_wsx_ok (
         byte *_buffer,
         /* struct_smt_wsx_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_ok));
    if (*params)
      {
        ((struct_smt_wsx_ok *) *params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_OK,
                   & ((struct_smt_wsx_ok *) *params)-> html_data));
      }
    else
        return -1;
}

void free_smt_wsx_ok (
         /* struct_smt_wsx_ok */ void **params)
{
    mem_free (((struct_smt_wsx_ok *) *params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_bin (
         byte *_buffer,
         /* struct_smt_wsx_bin */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_bin));
    if (*params)
      {
        ((struct_smt_wsx_bin *) *params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_BIN,
                   & ((struct_smt_wsx_bin *) *params)-> html_size,
                   & ((struct_smt_wsx_bin *) *params)-> html_data));
      }
    else
        return -1;
}

void free_smt_wsx_bin (
         /* struct_smt_wsx_bin */ void **params)
{
    mem_free (((struct_smt_wsx_bin *) *params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_multipart (
         byte *_buffer,
         /* struct_smt_wsx_multipart */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_multipart));
    if (*params)
      {
        ((struct_smt_wsx_multipart *) *params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_MULTIPART,
                   & ((struct_smt_wsx_multipart *) *params)-> html_data));
      }
    else
        return -1;
}

void free_smt_wsx_multipart (
         /* struct_smt_wsx_multipart */ void **params)
{
    mem_free (((struct_smt_wsx_multipart *) *params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_mbin (
         byte *_buffer,
         /* struct_smt_wsx_mbin */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_mbin));
    if (*params)
      {
        ((struct_smt_wsx_mbin *) *params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_MBIN,
                   & ((struct_smt_wsx_mbin *) *params)-> html_size,
                   & ((struct_smt_wsx_mbin *) *params)-> html_data));
      }
    else
        return -1;
}

void free_smt_wsx_mbin (
         /* struct_smt_wsx_mbin */ void **params)
{
    mem_free (((struct_smt_wsx_mbin *) *params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_restart (
         byte *_buffer,
         /* struct_smt_wsx_restart */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_restart));
    if (*params)
      {
        ((struct_smt_wsx_restart *) *params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_RESTART,
                   & ((struct_smt_wsx_restart *) *params)-> html_data));
      }
    else
        return -1;
}

void free_smt_wsx_restart (
         /* struct_smt_wsx_restart */ void **params)
{
    mem_free (((struct_smt_wsx_restart *) *params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_kill (
         byte *_buffer,
         /* struct_smt_wsx_kill */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_kill));
    if (*params)
      {
        ((struct_smt_wsx_kill *) *params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_KILL,
                   & ((struct_smt_wsx_kill *) *params)-> html_data));
      }
    else
        return -1;
}

void free_smt_wsx_kill (
         /* struct_smt_wsx_kill */ void **params)
{
    mem_free (((struct_smt_wsx_kill *) *params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_error (
         byte *_buffer,
         /* struct_smt_wsx_error */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_error));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_WSX_ERROR,
                   & ((struct_smt_wsx_error *) *params)-> error_code));
      }
    else
        return -1;
}

void free_smt_wsx_error (
         /* struct_smt_wsx_error */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_smt_wsx_redirect (
         byte *_buffer,
         /* struct_smt_wsx_redirect */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_redirect));
    if (*params)
      {
        ((struct_smt_wsx_redirect *) *params)-> new_url = NULL;
        return (exdr_read (_buffer, SMT_WSX_REDIRECT,
                   & ((struct_smt_wsx_redirect *) *params)-> new_url));
      }
    else
        return -1;
}

void free_smt_wsx_redirect (
         /* struct_smt_wsx_redirect */ void **params)
{
    mem_free (((struct_smt_wsx_redirect *) *params)-> new_url);
    mem_free (*params);
    *params = NULL;
}

/*---------------------------------------------------------------------------
 *  Message functions for smtrdns - Reverse DNS agent.
 *---------------------------------------------------------------------------*/

int  get_smt_get_host_name (
         byte *_buffer,
         /* struct_smt_get_host_name */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_get_host_name));
    if (*params)
      {
        ((struct_smt_get_host_name *) *params)-> ip_string = NULL;
        return (exdr_read (_buffer, SMT_GET_HOST_NAME,
                   & ((struct_smt_get_host_name *) *params)-> ip_address,
                   & ((struct_smt_get_host_name *) *params)-> ip_string,
                   & ((struct_smt_get_host_name *) *params)-> request_tag));
      }
    else
        return -1;
}

void free_smt_get_host_name (
         /* struct_smt_get_host_name */ void **params)
{
    mem_free (((struct_smt_get_host_name *) *params)-> ip_string);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_get_host_ip (
         byte *_buffer,
         /* struct_smt_get_host_ip */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_get_host_ip));
    if (*params)
      {
        ((struct_smt_get_host_ip *) *params)-> host_name = NULL;
        return (exdr_read (_buffer, SMT_GET_HOST_IP,
                   & ((struct_smt_get_host_ip *) *params)-> host_name,
                   & ((struct_smt_get_host_ip *) *params)-> request_tag));
      }
    else
        return -1;
}

void free_smt_get_host_ip (
         /* struct_smt_get_host_ip */ void **params)
{
    mem_free (((struct_smt_get_host_ip *) *params)-> host_name);
    mem_free (*params);
    *params = NULL;
}

int put_smt_host_name (
        byte **_buffer,
        struct_smt_host_name *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_HOST_NAME,
                        params-> ip_address,
                        params-> host_name,
                        params-> request_tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_HOST_NAME,
                    params-> ip_address,
                    params-> host_name,
                    params-> request_tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Return host name                                            */

int lsend_host_name (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte ip_address,               /*  IP address in network order      */
        char *host_name,                /*  Host name                        */
        qbyte request_tag)              /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_host_name
          _params;

    _params.ip_address                  = ip_address;
    _params.host_name                   = host_name;
    _params.request_tag                 = request_tag;

    _size = put_smt_host_name (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "HOST_NAME",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_host_ip (
        byte **_buffer,
        struct_smt_host_ip *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_HOST_IP,
                        params-> ip_address,
                        params-> host_name,
                        params-> request_tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_HOST_IP,
                    params-> ip_address,
                    params-> host_name,
                    params-> request_tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Return host IP address                                      */

int lsend_host_ip (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte ip_address,               /*  IP address in network order      */
        char *host_name,                /*  Host name                        */
        qbyte request_tag)              /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_host_ip
          _params;

    _params.ip_address                  = ip_address;
    _params.host_name                   = host_name;
    _params.request_tag                 = request_tag;

    _size = put_smt_host_ip (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "HOST_IP",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_get_host_name (
        byte **_buffer,
        struct_smt_get_host_name *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_GET_HOST_NAME,
                        params-> ip_address,
                        params-> ip_string,
                        params-> request_tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_GET_HOST_NAME,
                    params-> ip_address,
                    params-> ip_string,
                    params-> request_tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Get host name for address                                   */

int lsend_get_host_name (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte ip_address,               /*  IP address in network order      */
        char *ip_string,                /*  Alternative address in string format */
        qbyte request_tag)              /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_get_host_name
          _params;

    _params.ip_address                  = ip_address;
    _params.ip_string                   = ip_string;
    _params.request_tag                 = request_tag;

    _size = put_smt_get_host_name (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_HOST_NAME",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_smt_get_host_ip (
        byte **_buffer,
        struct_smt_get_host_ip *params)
{
    int _size;

    _size = exdr_write (NULL, SMT_GET_HOST_IP,
                        params-> host_name,
                        params-> request_tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_GET_HOST_IP,
                    params-> host_name,
                    params-> request_tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Get host address for name                                   */

int lsend_get_host_ip (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *host_name,                /*  Host name to look-up             */
        qbyte request_tag)              /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;
    struct_smt_get_host_ip
          _params;

    _params.host_name                   = host_name;
    _params.request_tag                 = request_tag;

    _size = put_smt_get_host_ip (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_HOST_IP",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int  get_smt_host_name (
         byte *_buffer,
         /* struct_smt_host_name */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_host_name));
    if (*params)
      {
        ((struct_smt_host_name *) *params)-> host_name = NULL;
        return (exdr_read (_buffer, SMT_HOST_NAME,
                   & ((struct_smt_host_name *) *params)-> ip_address,
                   & ((struct_smt_host_name *) *params)-> host_name,
                   & ((struct_smt_host_name *) *params)-> request_tag));
      }
    else
        return -1;
}

void free_smt_host_name (
         /* struct_smt_host_name */ void **params)
{
    mem_free (((struct_smt_host_name *) *params)-> host_name);
    mem_free (*params);
    *params = NULL;
}

int  get_smt_host_ip (
         byte *_buffer,
         /* struct_smt_host_ip */ void **params)
{
    *params = mem_alloc (sizeof (struct_smt_host_ip));
    if (*params)
      {
        ((struct_smt_host_ip *) *params)-> host_name = NULL;
        return (exdr_read (_buffer, SMT_HOST_IP,
                   & ((struct_smt_host_ip *) *params)-> ip_address,
                   & ((struct_smt_host_ip *) *params)-> host_name,
                   & ((struct_smt_host_ip *) *params)-> request_tag));
      }
    else
        return -1;
}

void free_smt_host_ip (
         /* struct_smt_host_ip */ void **params)
{
    mem_free (((struct_smt_host_ip *) *params)-> host_name);
    mem_free (*params);
    *params = NULL;
}

