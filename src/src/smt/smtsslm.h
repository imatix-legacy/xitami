/*---------------------------------------------------------------------------
 * smtsslm.h - Smtssl messages.
 *
 * Generated on 1999/01/23, 19:42:07 from smtsslm.msg by exdrgen
 * DO NOT MODIFY THIS FILE.
 *
 * For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#ifndef INCLUDE_SMTSSLM
#define INCLUDE_SMTSSLM

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smtssl - SMT SSL agent.
 *---------------------------------------------------------------------------*/

#define SSL_ACCEPTED "qssd"

typedef struct {
    qbyte socket;                       /*  Socket handle for ssl connection */
    char *user;                         /*  User name                        */
    char *cipher;                       /*  Cipher used                      */
    dbyte verify;                       /*  Level of user verification       */
} struct_ssl_accepted;

int  get_ssl_accepted (
         byte *_buffer,
         /* struct_ssl_accepted */ void **params);

void free_ssl_accepted (
         /* struct_ssl_accepted */ void **params);

#define declare_ssl_accept(_event, _priority)                                \
    method_declare (agent, "SSL_ACCEPT", _event, _priority)

#define SSL_OPEN "s"

typedef struct {
    char *config;                       /*  Configuration file to use        */
} struct_ssl_open;

int  get_ssl_open (
         byte *_buffer,
         /* struct_ssl_open */ void **params);

void free_ssl_open (
         /* struct_ssl_open */ void **params);

#define declare_ssl_open(_event, _priority)                                  \
    method_declare (agent, "SSL_OPEN", _event, _priority)

#define SSL_READ_REQUEST "q"

typedef struct {
    qbyte size;                         /*  Maximum size to read             */
} struct_ssl_read_request;

int  get_ssl_read_request (
         byte *_buffer,
         /* struct_ssl_read_request */ void **params);

void free_ssl_read_request (
         /* struct_ssl_read_request */ void **params);

#define declare_ssl_read_request(_event, _priority)                          \
    method_declare (agent, "SSL_READ_REQUEST", _event, _priority)

#define SSL_WRITE_REQUEST "dqmMq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    qbyte socket;                       /*  Socket to write to               */
    word  size;                         /*  Amount of data to write          */
    byte *data;                         /*  Block of data to write           */
    qbyte tag;                          /*  User-defined request tag         */
} struct_ssl_write_request;

int  get_ssl_write_request (
         byte *_buffer,
         /* struct_ssl_write_request */ void **params);

void free_ssl_write_request (
         /* struct_ssl_write_request */ void **params);

#define declare_ssl_write_request(_event, _priority)                         \
    method_declare (agent, "SSL_WRITE_REQUEST", _event, _priority)

#define SSL_PUTS "qsqq"

typedef struct {
    qbyte socket;                       /*  Socket for output                */
    char *filename;                     /*  Name of file to send             */
    qbyte start;                        /*  Starting offset; 0 = start       */
    qbyte end;                          /*  Ending offset; 0 = end           */
} struct_ssl_puts;

int  get_ssl_puts (
         byte *_buffer,
         /* struct_ssl_puts */ void **params);

void free_ssl_puts (
         /* struct_ssl_puts */ void **params);

#define declare_ssl_put_slice(_event, _priority)                             \
    method_declare (agent, "SSL_PUT_SLICE", _event, _priority)

#define SSL_ERROR "q"

typedef struct {
    qbyte code;                         /*  Error code                       */
} struct_ssl_error;

int put_ssl_error (
        byte **_buffer,
        struct_ssl_error *params);

/*  Send event - Signal SSL error                                            */

int lsend_ssl_error (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte code);                    /*  Error code                       */

#define send_ssl_error(_to,                                                  \
                       code)                                                 \
       lsend_ssl_error(_to,                                                  \
                       &thread-> queue-> qid,                                \
                       NULL, NULL, NULL, 0,                                  \
                       code)

#define SSL_WRITE_OK "qq"

typedef struct {
    qbyte socket;                       /*  Socket used for i/o, or new socket */
    qbyte tag;                          /*  User-defined request tag         */
} struct_ssl_write_ok;

int put_ssl_write_ok (
        byte **_buffer,
        struct_ssl_write_ok *params);

/*  Send event - Write OK reply                                              */

int lsend_ssl_write_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket */
        qbyte tag);                     /*  User-defined request tag         */

#define send_ssl_write_ok(_to,                                               \
                          socket,                                            \
                          tag)                                               \
       lsend_ssl_write_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          socket,                                            \
                          tag)

#define SSL_READ_OK "mM"

typedef struct {
    word  size;                         /*  Size of result                   */
    byte *data;                         /*  Read data                        */
} struct_ssl_read_ok;

int put_ssl_read_ok (
        byte **_buffer,
        struct_ssl_read_ok *params);

/*  Send event - Read result data                                            */

int lsend_ssl_read_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        word  size,                     /*  Size of result                   */
        byte *data);                    /*  Read data                        */

#define send_ssl_read_ok(_to,                                                \
                         size,                                               \
                         data)                                               \
       lsend_ssl_read_ok(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         size,                                               \
                         data)

#define SSL_PUTF_OK "q"

typedef struct {
    qbyte size;                         /*  Amount of transmitted data       */
} struct_ssl_putf_ok;

int put_ssl_putf_ok (
        byte **_buffer,
        struct_ssl_putf_ok *params);

/*  Send event - File written okay                                           */

int lsend_ssl_putf_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size);                    /*  Amount of transmitted data       */

#define send_ssl_putf_ok(_to,                                                \
                         size)                                               \
       lsend_ssl_putf_ok(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         size)


int put_ssl_accepted (
        byte **_buffer,
        struct_ssl_accepted *params);

/*  Send event - Accept SSL connection                                       */

int lsend_ssl_accept (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket handle for ssl connection */
        char *user,                     /*  User name                        */
        char *cipher,                   /*  Cipher used                      */
        dbyte verify);                  /*  Level of user verification       */

#define send_ssl_accept(_to,                                                 \
                        socket,                                              \
                        user,                                                \
                        cipher,                                              \
                        verify)                                              \
       lsend_ssl_accept(_to,                                                 \
                        &thread-> queue-> qid,                               \
                        NULL, NULL, NULL, 0,                                 \
                        socket,                                              \
                        user,                                                \
                        cipher,                                              \
                        verify)

int put_ssl_open (
        byte **_buffer,
        struct_ssl_open *params);

/*  Send event - Open ssl port                                               */

int lsend_ssl_open (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *config);                  /*  Configuration file to use        */

#define send_ssl_open(_to,                                                   \
                      config)                                                \
       lsend_ssl_open(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      config)

int put_ssl_read_request (
        byte **_buffer,
        struct_ssl_read_request *params);

/*  Send event - Request read                                                */

int lsend_ssl_read_request (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size);                    /*  Maximum size to read             */

#define send_ssl_read_request(_to,                                           \
                              size)                                          \
       lsend_ssl_read_request(_to,                                           \
                              &thread-> queue-> qid,                         \
                              NULL, NULL, NULL, 0,                           \
                              size)

int put_ssl_write_request (
        byte **_buffer,
        struct_ssl_write_request *params);

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
        qbyte tag);                     /*  User-defined request tag         */

#define send_ssl_write_request(_to,                                          \
                               timeout,                                      \
                               socket,                                       \
                               size,                                         \
                               data,                                         \
                               tag)                                          \
       lsend_ssl_write_request(_to,                                          \
                               &thread-> queue-> qid,                        \
                               NULL, NULL, NULL, 0,                          \
                               timeout,                                      \
                               socket,                                       \
                               size,                                         \
                               data,                                         \
                               tag)

int put_ssl_puts (
        byte **_buffer,
        struct_ssl_puts *params);

/*  Send event - Write file slice to SSL socket                              */

int lsend_ssl_put_slice (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        char *filename,                 /*  Name of file to send             */
        qbyte start,                    /*  Starting offset; 0 = start       */
        qbyte end);                     /*  Ending offset; 0 = end           */

#define send_ssl_put_slice(_to,                                              \
                           socket,                                           \
                           filename,                                         \
                           start,                                            \
                           end)                                              \
       lsend_ssl_put_slice(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           socket,                                           \
                           filename,                                         \
                           start,                                            \
                           end)

int get_ssl_error (
        byte *_buffer,
        /* struct_ssl_error */ void **params);

void free_ssl_error (
        /* struct_ssl_error */ void **params);

#define declare_ssl_error(_event, _priority)                                 \
    method_declare (agent, "SSL_ERROR", _event, _priority)

int get_ssl_write_ok (
        byte *_buffer,
        /* struct_ssl_write_ok */ void **params);

void free_ssl_write_ok (
        /* struct_ssl_write_ok */ void **params);

#define declare_ssl_write_ok(_event, _priority)                              \
    method_declare (agent, "SSL_WRITE_OK", _event, _priority)

int get_ssl_read_ok (
        byte *_buffer,
        /* struct_ssl_read_ok */ void **params);

void free_ssl_read_ok (
        /* struct_ssl_read_ok */ void **params);

#define declare_ssl_read_ok(_event, _priority)                               \
    method_declare (agent, "SSL_READ_OK", _event, _priority)

int get_ssl_putf_ok (
        byte *_buffer,
        /* struct_ssl_putf_ok */ void **params);

void free_ssl_putf_ok (
        /* struct_ssl_putf_ok */ void **params);

#define declare_ssl_putf_ok(_event, _priority)                               \
    method_declare (agent, "SSL_PUTF_OK", _event, _priority)

#endif                                  /*  Included                         */
