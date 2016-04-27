/*  ----------------------------------------------------------------<Prolog>-
    Name:       echocli.c
    Title:      ECHO client (socket test program)
    Package:    Libero/SMT Kernel 2.x

    Written:    96/06/16  iMatix SMT kernel team <smt@imatix.com>
    Revised:    97/09/08

    Synopsis:   Sends messages to port 5001 and echoes the returned result.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"                        /*  SFL library header file          */

static sock_t handle;

void handle_signal (int the_signal)
{
    close (handle);
    exit (1);
}

int main (int argc, char *argv [])
{
#   define BUFFER_SIZE  512
    char buffer [BUFFER_SIZE + 1];
    int  count, length;
    char *socket_number;

    signal (SIGINT,  handle_signal);
    signal (SIGSEGV, handle_signal);
    signal (SIGTERM, handle_signal);

    sock_init ();
    if (argc > 1)
        socket_number = argv [1];
    else
        socket_number = "5001";

    handle = connect_TCP ("", socket_number);
    if (handle == INVALID_SOCKET)
      {
        printf ("Echocli error : %s\n", sockmsg ());
        exit (EXIT_FAILURE);
      }
    printf ("=>");
    fflush (stdout);
    while (fgets (buffer, BUFFER_SIZE, stdin))
      {
        buffer [BUFFER_SIZE] = '\0';
        length = strlen (buffer);
        write_TCP (handle, buffer, length);
        printf ("--");
        fflush (stdout);
        while (length > 0)
          {
            count = read_TCP (handle, buffer, BUFFER_SIZE);
            if (count == 0)
                break;
            if (count == -1)
              {
                if (sockerrno == EAGAIN || sockerrno == EWOULDBLOCK)
                    continue;
                printf ("Echocli error : %s\n", sockmsg ());
                return (EXIT_FAILURE);
              }
            buffer [count] = '\0';
            printf (buffer);
            length -= count;
          }
        printf ("=>");
        fflush (stdout);
      }
    close_socket (handle);
    sock_term ();
    return (EXIT_SUCCESS);
}
