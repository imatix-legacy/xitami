/*---------------------------------------------------------------------------
 * smtsslm.c - Smtssl messages.
 *
 * Generated on 1999/01/23, 19:42:07 from smtsslm.msg by exdrgen
 * DO NOT MODIFY THIS FILE.
 *
 * For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#include "sfl.h"                        /*  SFL header file                  */
#include "smtlib.h"                     /*  SMT header file                  */
#include "smtsslm.h"                    /*  Definitions & prototypes         */

/*---------------------------------------------------------------------------
 *  Message functions for smtssl - SMT SSL agent.
 *---------------------------------------------------------------------------*/

int  get_ssl_accepted (
         byte *_buffer,
         /* struct_ssl_accepted */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_accepted));
    if (*params)
      {
        ((struct_ssl_accepted *) *params)-> user = NULL;
        ((struct_ssl_accepted *) *params)-> cipher = NULL;
        return (exdr_read (_buffer, SSL_ACCEPTED,
                   & ((struct_ssl_accepted *) *params)-> socket,
                   & ((struct_ssl_accepted *) *params)-> user,
                   & ((struct_ssl_accepted *) *params)-> cipher,
                   & ((struct_ssl_accepted *) *params)-> verify));
      }
    else
        return -1;
}

void free_ssl_accepted (
         /* struct_ssl_accepted */ void **params)
{
    mem_free (((struct_ssl_accepted *) *params)-> user);
    mem_free (((struct_ssl_accepted *) *params)-> cipher);
    mem_free (*params);
    *params = NULL;
}

int  get_ssl_open (
         byte *_buffer,
         /* struct_ssl_open */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_open));
    if (*params)
      {
        ((struct_ssl_open *) *params)-> config = NULL;
        return (exdr_read (_buffer, SSL_OPEN,
                   & ((struct_ssl_open *) *params)-> config));
      }
    else
        return -1;
}

void free_ssl_open (
         /* struct_ssl_open */ void **params)
{
    mem_free (((struct_ssl_open *) *params)-> config);
    mem_free (*params);
    *params = NULL;
}

int  get_ssl_read_request (
         byte *_buffer,
         /* struct_ssl_read_request */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_read_request));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_READ_REQUEST,
                   & ((struct_ssl_read_request *) *params)-> size));
      }
    else
        return -1;
}

void free_ssl_read_request (
         /* struct_ssl_read_request */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_ssl_write_request (
         byte *_buffer,
         /* struct_ssl_write_request */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_write_request));
    if (*params)
      {
        ((struct_ssl_write_request *) *params)-> data = NULL;
        return (exdr_read (_buffer, SSL_WRITE_REQUEST,
                   & ((struct_ssl_write_request *) *params)-> timeout,
                   & ((struct_ssl_write_request *) *params)-> socket,
                   & ((struct_ssl_write_request *) *params)-> size,
                   & ((struct_ssl_write_request *) *params)-> data,
                   & ((struct_ssl_write_request *) *params)-> tag));
      }
    else
        return -1;
}

void free_ssl_write_request (
         /* struct_ssl_write_request */ void **params)
{
    mem_free (((struct_ssl_write_request *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_ssl_puts (
         byte *_buffer,
         /* struct_ssl_puts */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_puts));
    if (*params)
      {
        ((struct_ssl_puts *) *params)-> filename = NULL;
        return (exdr_read (_buffer, SSL_PUTS,
                   & ((struct_ssl_puts *) *params)-> socket,
                   & ((struct_ssl_puts *) *params)-> filename,
                   & ((struct_ssl_puts *) *params)-> start,
                   & ((struct_ssl_puts *) *params)-> end));
      }
    else
        return -1;
}

void free_ssl_puts (
         /* struct_ssl_puts */ void **params)
{
    mem_free (((struct_ssl_puts *) *params)-> filename);
    mem_free (*params);
    *params = NULL;
}

int put_ssl_error (
        byte **_buffer,
        struct_ssl_error *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_ERROR,
                        params-> code);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_ERROR,
                    params-> code);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Signal SSL error                                            */

int lsend_ssl_error (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte code)                     /*  Error code                       */
{
    byte *_body;
    int   _size,
          _rc;
    struct_ssl_error
          _params;

    _params.code                        = code;

    _size = put_ssl_error (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_ERROR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_ssl_write_ok (
        byte **_buffer,
        struct_ssl_write_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_WRITE_OK,
                        params-> socket,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_WRITE_OK,
                    params-> socket,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write OK reply                                              */

int lsend_ssl_write_ok (QID *_to, QID *_from,
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
    struct_ssl_write_ok
          _params;

    _params.socket                      = socket;
    _params.tag                         = tag;

    _size = put_ssl_write_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_WRITE_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_ssl_read_ok (
        byte **_buffer,
        struct_ssl_read_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_READ_OK,
                        params-> size,
                        params-> data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_READ_OK,
                    params-> size,
                    params-> data);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Read result data                                            */

int lsend_ssl_read_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        word  size,                     /*  Size of result                   */
        byte *data)                     /*  Read data                        */
{
    byte *_body;
    int   _size,
          _rc;
    struct_ssl_read_ok
          _params;

    _params.size                        = size;
    _params.data                        = data;

    _size = put_ssl_read_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_READ_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_ssl_putf_ok (
        byte **_buffer,
        struct_ssl_putf_ok *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_PUTF_OK,
                        params-> size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_PUTF_OK,
                    params-> size);
    else
        _size = 0;

    return (_size);
}

/*  Send event - File written okay                                           */

int lsend_ssl_putf_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size)                     /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;
    struct_ssl_putf_ok
          _params;

    _params.size                        = size;

    _size = put_ssl_putf_ok (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_PUTF_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_ssl_accepted (
        byte **_buffer,
        struct_ssl_accepted *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_ACCEPTED,
                        params-> socket,
                        params-> user,
                        params-> cipher,
                        params-> verify);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_ACCEPTED,
                    params-> socket,
                    params-> user,
                    params-> cipher,
                    params-> verify);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Accept SSL connection                                       */

int lsend_ssl_accept (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket handle for ssl connection */
        char *user,                     /*  User name                        */
        char *cipher,                   /*  Cipher used                      */
        dbyte verify)                   /*  Level of user verification       */
{
    byte *_body;
    int   _size,
          _rc;
    struct_ssl_accepted
          _params;

    _params.socket                      = socket;
    _params.user                        = user;
    _params.cipher                      = cipher;
    _params.verify                      = verify;

    _size = put_ssl_accepted (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_ACCEPT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_ssl_open (
        byte **_buffer,
        struct_ssl_open *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_OPEN,
                        params-> config);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_OPEN,
                    params-> config);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Open ssl port                                               */

int lsend_ssl_open (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *config)                   /*  Configuration file to use        */
{
    byte *_body;
    int   _size,
          _rc;
    struct_ssl_open
          _params;

    _params.config                      = config;

    _size = put_ssl_open (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_OPEN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_ssl_read_request (
        byte **_buffer,
        struct_ssl_read_request *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_READ_REQUEST,
                        params-> size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_READ_REQUEST,
                    params-> size);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Request read                                                */

int lsend_ssl_read_request (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size)                     /*  Maximum size to read             */
{
    byte *_body;
    int   _size,
          _rc;
    struct_ssl_read_request
          _params;

    _params.size                        = size;

    _size = put_ssl_read_request (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_READ_REQUEST",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_ssl_write_request (
        byte **_buffer,
        struct_ssl_write_request *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_WRITE_REQUEST,
                        params-> timeout,
                        params-> socket,
                        params-> size,
                        params-> data,
                        params-> tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_WRITE_REQUEST,
                    params-> timeout,
                    params-> socket,
                    params-> size,
                    params-> data,
                    params-> tag);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write SSL data                                              */

int lsend_ssl_write_request (QID *_to, QID *_from,
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
    struct_ssl_write_request
          _params;

    _params.timeout                     = timeout;
    _params.socket                      = socket;
    _params.size                        = size;
    _params.data                        = data;
    _params.tag                         = tag;

    _size = put_ssl_write_request (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_WRITE_REQUEST",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int put_ssl_puts (
        byte **_buffer,
        struct_ssl_puts *params)
{
    int _size;

    _size = exdr_write (NULL, SSL_PUTS,
                        params-> socket,
                        params-> filename,
                        params-> start,
                        params-> end);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_PUTS,
                    params-> socket,
                    params-> filename,
                    params-> start,
                    params-> end);
    else
        _size = 0;

    return (_size);
}

/*  Send event - Write file slice to SSL socket                              */

int lsend_ssl_put_slice (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        char *filename,                 /*  Name of file to send             */
        qbyte start,                    /*  Starting offset; 0 = start       */
        qbyte end)                      /*  Ending offset; 0 = end           */
{
    byte *_body;
    int   _size,
          _rc;
    struct_ssl_puts
          _params;

    _params.socket                      = socket;
    _params.filename                    = filename;
    _params.start                       = start;
    _params.end                         = end;

    _size = put_ssl_puts (&_body, &_params);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_PUT_SLICE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

int  get_ssl_error (
         byte *_buffer,
         /* struct_ssl_error */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_error));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_ERROR,
                   & ((struct_ssl_error *) *params)-> code));
      }
    else
        return -1;
}

void free_ssl_error (
         /* struct_ssl_error */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_ssl_write_ok (
         byte *_buffer,
         /* struct_ssl_write_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_write_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_WRITE_OK,
                   & ((struct_ssl_write_ok *) *params)-> socket,
                   & ((struct_ssl_write_ok *) *params)-> tag));
      }
    else
        return -1;
}

void free_ssl_write_ok (
         /* struct_ssl_write_ok */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

int  get_ssl_read_ok (
         byte *_buffer,
         /* struct_ssl_read_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_read_ok));
    if (*params)
      {
        ((struct_ssl_read_ok *) *params)-> data = NULL;
        return (exdr_read (_buffer, SSL_READ_OK,
                   & ((struct_ssl_read_ok *) *params)-> size,
                   & ((struct_ssl_read_ok *) *params)-> data));
      }
    else
        return -1;
}

void free_ssl_read_ok (
         /* struct_ssl_read_ok */ void **params)
{
    mem_free (((struct_ssl_read_ok *) *params)-> data);
    mem_free (*params);
    *params = NULL;
}

int  get_ssl_putf_ok (
         byte *_buffer,
         /* struct_ssl_putf_ok */ void **params)
{
    *params = mem_alloc (sizeof (struct_ssl_putf_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_PUTF_OK,
                   & ((struct_ssl_putf_ok *) *params)-> size));
      }
    else
        return -1;
}

void free_ssl_putf_ok (
         /* struct_ssl_putf_ok */ void **params)
{
    mem_free (*params);
    *params = NULL;
}

