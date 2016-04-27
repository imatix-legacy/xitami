/*  ----------------------------------------------------------------<Prolog>-
    Name:       testxml.c
    Title:      Test program for bitstring functions
    Package:    Standard Function Library (SFL)

    Written:    98/03/23  iMatix SFL project team <sfl@imatix.com>
    Revised:    97/04/01

    Synopsis:   Test XML loading and saving.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"
#include "sflxml.h"
#include "sflxmll.h"

int main (int argc, char *argv [])
{

XML_ITEM
    *root;

    root = xml_load (".", argv[1]);
    if (root)
      {
        xml_save (root, "testxml.txt");
        xml_free (root);
      }
    else
        printf ("Load error\n");

    mem_assert ();
    return (EXIT_SUCCESS);
}










