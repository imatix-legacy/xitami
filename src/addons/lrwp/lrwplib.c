/************************************************************************
               Copyright (c) 1997 by Total Control Software
                         All Rights Reserved
------------------------------------------------------------------------

Module Name:    lrwplib.c

Description:    Small library of routines to assist with the creation
                of LRWP Peer applications.

Creation Date:  1/5/98 9:47:27PM

# License:      This is free software.  You may use this software for any
#               purpose including modification/redistribution, so long as
#               this header remains intact and that you do not claim any
#               rights of ownership or authorship of this software.  This
#               software has been tested, but no warranty is expressed or
#               implied.

************************************************************************/

#include "lrwplib.h"

#define SIZELEN     9
#define ALLOC_INCR  1024


static int
read_full_TCP(
    sock_t handle,                      /*  Socket handle                    */
    void *buffer,                       /*  Buffer to receive data           */
    size_t length                       /*  Full amount of data to read      */
    );

/*  ---------------------------------------------------------------------[<]-
    Function: lrwp_connect

    Connects to the LRWP agent running in Xitami on host and port.  Sends
    the given appname to use as the URI alias that will trigger requests to
    be sent to this peer.  If vhost is given, this peer will only be sent
    requests origininating from that virtual host.  This function assumes
    that the LRWP structure is uninitialized and clears it before use.

    Returns NULL on success and a pointer to an error message otherwise.
    ---------------------------------------------------------------------[>]-*/

char* lrwp_connect(LRWP* lrwp,          /* pointer to UNCONNECTED LRWP object */
                   char* appname,       /* Name or alias of Peer app         */
                   char* host,          /* hostname/IP address to connect to */
                   char* port,          /* string containing port number     */
                   char* vhost)         /* optional virtual hostname         */
{
    static char buf[1024];
    int         len;

    /* Initialize LRWP structure.  Assumes this is first use. */
    lrwp->sock      = 0;
    lrwp->cgi       = NULL;
    lrwp->post_data = NULL;
    lrwp->outbuf    = NULL;
    lrwp->size      = 0;
    lrwp->allocated = 0;


    /* Attempt the connection */
    ip_nonblock = FALSE;                /*  Use blocking socket i/o          */
    lrwp->sock = connect_TCP(host, port);
    if (lrwp->sock == INVALID_SOCKET) {
        sprintf(buf, "ERROR: Unable to connect (%s)", sockmsg());
        return buf;
    }

    /* send the startup sting */
    sprintf(buf, "%s\xFF%s\xFF%s", appname, vhost?vhost:"", "");
    if (write_TCP(lrwp->sock, buf, strlen(buf)) == SOCKET_ERROR) {
        sprintf(buf, "ERROR: Unable to send startup string (%s)", sockmsg());
        return buf;
    }

    /* wait for an acknowledgement... */
    len = read_TCP(lrwp->sock, buf, sizeof(buf)-1);
    if (len == SOCKET_ERROR) {
        sprintf(buf, "ERROR: Unable to receive acknowledgement string (%s)", sockmsg());
        return buf;
    }
    buf[len] = 0;

    if (streq(buf, "OK"))
        return NULL;
    else
        return buf;
}

/*  ---------------------------------------------------------------------[<]-
    Function: lrwp_accept_request

    This funation waits for and recieves a request from the LRWP agent, and
    populates the LRWP structure with the request data.

    Returns 0 on success and -1 otherwise.
    ---------------------------------------------------------------------[>]-*/

int  lrwp_accept_request(LRWP* lrwp)    /* pointer to CONNECTED LRWP object  */
{
    char    sizebuf[SIZELEN+1];
    int     len;
    int     size;
    DESCR   descr;
    char*   temp;

    /* read the size of the CGI environment */
    len = read_full_TCP(lrwp->sock, sizebuf, SIZELEN);
    if (len == SOCKET_ERROR || len != SIZELEN)
        return -1;
    sizebuf[len] = 0;
    size = atoi(sizebuf);

    /*  read the CGI environment data */
    temp = mem_alloc(size+1);           /* **** Should be checking this!!! */
    len = read_full_TCP(lrwp->sock, temp, size);
    if (len == SOCKET_ERROR || len != size) {
        mem_free(temp);
        return -1;
    }

    /*  and convert it to a Symbol Table */
    descr.size = size;
    descr.data = temp;
    lrwp->cgi = descr2symb(&descr);
    mem_free(temp);

    /*  now read the size of the post data */
    len = read_full_TCP(lrwp->sock, sizebuf, SIZELEN);
    if (len == SOCKET_ERROR || len != SIZELEN) {
        sym_delete_table(lrwp->cgi);
        lrwp->cgi = NULL;
        return -1;
    }
    sizebuf[len] = 0;
    size = atoi(sizebuf);

    /*  and finally, read the post data, if any */
    if (size) {
        lrwp->post_data = mem_alloc(size+1); /* **** Should be checking this!!! */
        len = read_full_TCP(lrwp->sock, lrwp->post_data, size);
        if (len == SOCKET_ERROR || len != size) {
            sym_delete_table(lrwp->cgi);
            lrwp->cgi = NULL;
            mem_free(lrwp->post_data);
            lrwp->post_data = NULL;
            return -1;
        }
    }
    else
        lrwp->post_data = mem_strdup("");

    return 0;
}

/*  ---------------------------------------------------------------------[<]-
    Function: lrwp_send_string

    This function appends a string to the response buffer.
    lrwp_finish_request() must be called to send the response back to Xitami.

    Returns 0 on success and -1 otherwise.
    ---------------------------------------------------------------------[>]-*/

int  lrwp_send_string(LRWP* lrwp,       /* pointer to CONNECTED LRWP object  */
                      char* st)         /* an ouput string                   */
{
    return lrwp_send_data(lrwp, st, strlen(st));
}

/*  ---------------------------------------------------------------------[<]-
    Function: lrwp_send_data

    Appends a buffer of (possibly binary) data of the specified size to
    the response buffer.  lrwp_finish_request() must be called to send the
    response back to Xitami.

    Returns 0 on success and -1 otherwise.
    ---------------------------------------------------------------------[>]-*/

int  lrwp_send_data(LRWP* lrwp,         /* pointer to CONNECTED LRWP object  */
                    void* data,         /* pointer to a data buffer          */
                    size_t len)         /* size of the data buffer           */
{
    char*   newPtr;
    size_t  newAlloc;

    /* reallocate if necessary */
    if ((lrwp->size + len) > lrwp->allocated) {
        newAlloc = max(lrwp->allocated + len, lrwp->allocated + ALLOC_INCR);
        if (! lrwp->outbuf)
            newPtr = mem_alloc(newAlloc);
        else
            newPtr = mem_realloc(lrwp->outbuf, newAlloc);
        if (!newPtr)
            return -1;
        lrwp->outbuf = newPtr;
        lrwp->allocated = newAlloc;
    }
    memcpy(lrwp->outbuf + lrwp->size, data, len);
    lrwp->size += len;
    return 0;
}

/*  ---------------------------------------------------------------------[<]-
    Function: lrwp_finish_request

    Completes the request by sending the response buffer back to Xitami
    and prepares the lwrp structure to receive another request.

    Returns 0 on success and -1 otherwise.
    ---------------------------------------------------------------------[>]-*/

int  lrwp_finish_request(LRWP* lrwp)    /* pointer to CONNECTED LRWP object  */
{
    char    sizebuf[SIZELEN+1];

    sprintf(sizebuf, "%09ld", lrwp->size);
    if (write_TCP(lrwp->sock, sizebuf, SIZELEN) == SOCKET_ERROR) {
        lrwp_cleanup(lrwp);
        return -1;
    }

    if (write_TCP(lrwp->sock, lrwp->outbuf, lrwp->size) == SOCKET_ERROR) {
        lrwp_cleanup(lrwp);
        return -1;
    }
    lrwp_cleanup(lrwp);
    return 0;
}

/*  ---------------------------------------------------------------------[<]-
    Function: lrwp_close

    Closes the connection to Xitami.

    Returns 0 on success and -1 otherwise.
    ---------------------------------------------------------------------[>]-*/

int  lrwp_close(LRWP* lrwp)             /* pointer to CONNECTED LRWP object  */
{
    close_socket(lrwp->sock);
    lrwp->sock = 0;
    lrwp_cleanup(lrwp);
    return 0;
}

/*  ---------------------------------------------------------------------[<]-
    Function: lrwp_cleanup

    Cleans up the LRWP structure.

    ---------------------------------------------------------------------[>]-*/

void lrwp_cleanup(LRWP* lrwp)
{
    if (lrwp->cgi)
        sym_delete_table(lrwp->cgi);

    if (lrwp->post_data)
        mem_free(lrwp->post_data);

    if (lrwp->outbuf)
        mem_free(lrwp->outbuf);

    lrwp->cgi       = NULL;
    lrwp->post_data = NULL;
    lrwp->outbuf    = NULL;
    lrwp->size      = 0;
    lrwp->allocated = 0;
}


/*  -------------------------------------------------------------------------
    Function: read_full_TCP

    Helper function to read the full number of bytes specified from the socket.

    -------------------------------------------------------------------------*/
static int
read_full_TCP(
    sock_t handle,                      /*  Socket handle                    */
    void *buffer,                       /*  Buffer to receive data           */
    size_t length                       /*  Full amount of data to read      */
    )
{
    size_t  numRead = 0;
    int     chunkLen;

    while (numRead < length) {
        chunkLen = read_TCP(handle, ((char*)buffer)+numRead, length-numRead);
        if (chunkLen == SOCKET_ERROR)
            return SOCKET_ERROR;
        numRead += chunkLen;
    }
    return numRead;
}

