/************************************************************************
               Copyright (c) 1997 by Total Control Software
                         All Rights Reserved
------------------------------------------------------------------------

Module Name:    testlrwp.c

Description:    Simple example of an LRWP Peer application.

Creation Date:  1/5/98 9:47:50PM

# License:      This is free software.  You may use this software for any
#               purpose including modification/redistribution, so long as
#               this header remains intact and that you do not claim any
#               rights of ownership or authorship of this software.  This
#               software has been tested, but no warranty is expressed or
#               implied.

************************************************************************/


#include "lrwplib.h"

#include <stdio.h>

//---------------------------------------------------------------------------

void usage(void)
{
    printf("Usage:\n\ttestlrwp appname host port [vhost]\n");
}

//---------------------------------------------------------------------------

void main(int argc, char* argv[])
{
    LRWP    lrwp;
    int     count = 0;
    int     err;
    char*   errMsg;
    char*   appname;
    char*   host;
    char*   port;
    char*   vhost = NULL;
    char    buf[1024];
    SYMBOL* symbol;

    if (argc < 4) {
        usage();
        exit(1);
    }

    appname = argv[1];
    host    = argv[2];
    port    = argv[3];
    if (argc > 4)
        vhost = argv[4];

    sock_init();

    errMsg = lrwp_connect(&lrwp, appname, host, port, vhost);
    if (errMsg) {
        fprintf(stderr, "%s\n", errMsg);
        exit(1);
    }

    printf("Waiting for requests from %s:%s\n", host, port);
    printf("Try hitting http://%s/%s with your browser...\n",
           vhost ? vhost : host, appname);

        /* only handle 5 reqests, then exit */
    while (count < 5 && lrwp_accept_request(&lrwp) != -1) {
        count += 1;

        err = lrwp_send_string(&lrwp, "Content-type: text/html\r\n\r\n");
        sprintf(buf, "<HTML><HEAD><TITLE>LRWP TestApp (%s)</TITLE></HEAD>\n<BODY>\n",
                appname);
        err = lrwp_send_string(&lrwp, buf);

        sprintf(buf, "<H2>LRWP test app (%s)</H2><P>", appname);
        err = lrwp_send_string(&lrwp, buf);

        sprintf(buf, "<b>request count</b> = %d<br>", count);
        err = lrwp_send_string(&lrwp, buf);

        err = lrwp_send_string(&lrwp, "<br><b>post data:</b> ");
        if (strlen(lrwp.post_data)) {
            err = lrwp_send_string(&lrwp, "<pre>");
            err = lrwp_send_string(&lrwp, lrwp.post_data);
            err = lrwp_send_string(&lrwp, "</pre><br>");
        }

        err = lrwp_send_string(&lrwp, "<P><HR><P><pre>");
        for (symbol=lrwp.cgi->symbols; symbol; symbol=symbol->next) {
            sprintf(buf, "<b>%-20s :</b>  %s\n", symbol->name, symbol->value);
            err = lrwp_send_string(&lrwp, buf);
        }

        err = lrwp_send_string(&lrwp, "\n</pre><P><HR>\n</BODY></HTML>\n");
        err = lrwp_finish_request(&lrwp);
    }

    err = lrwp_close(&lrwp);
    sock_term();
}

//---------------------------------------------------------------------------



