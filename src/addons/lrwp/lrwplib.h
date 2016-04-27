/************************************************************************
               Copyright (c) 1997 by Total Control Software
                         All Rights Reserved
------------------------------------------------------------------------

Module Name:    lrwplib.h

Description:    Small library of routines to assist with the creation
                of LRWP Peer applications.


Creation Date:  1/5/98 9:47:17PM

# License:      This is free software.  You may use this software for any
#               purpose including modification/redistribution, so long as
#               this header remains intact and that you do not claim any
#               rights of ownership or authorship of this software.  This
#               software has been tested, but no warranty is expressed or
#               implied.

************************************************************************/

#ifndef __LRWPLIB_H__
#define __LRWPLIB_H__

#include "sfl.h"

//---------------------------------------------------------------------------


typedef struct _LRWP {
    sock_t  sock;
    SYMTAB* cgi;
    char*   post_data;

    char*   outbuf;
    size_t  size;
    size_t  allocated;

} LRWP;


#ifdef __cplusplus
extern "C" {
#endif

char* lrwp_connect          (LRWP* lrwp, char* appname, char* host,
                             char* port, char* vhost);
int  lrwp_accept_request    (LRWP* lrwp);
int  lrwp_send_string       (LRWP* lrwp, char* st);
int  lrwp_send_data         (LRWP* lrwp, void* data, size_t len);
int  lrwp_finish_request    (LRWP* lrwp);
int  lrwp_close             (LRWP* lrwp);
void lrwp_cleanup           (LRWP* lrwp);

#ifdef __cplusplus
}
#endif



//---------------------------------------------------------------------------
#endif

