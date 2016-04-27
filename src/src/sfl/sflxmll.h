/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflxmll.h
    Title:      XML serialisation functions
    Package:    Standard Function Library (SFL)

    Written:    96/06/08  iMatix SFL project team <sfl@imatix.com>
    Revised:    99/01/01

    Synopsis:   Provides functions to load and save XML files.  An XML file
                is held in memory as a tree of nodes, of type XML_ITEM.  The
                XML functions do not currently accept DTDs in the XML data.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef SLFXMLL_INCLUDED               /*  Allow multiple inclusions        */
#define SLFXMLL_INCLUDED

/*- Function prototypes ---------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

XML_ITEM *xml_load  (const char *path, const char *filename);
int       xml_save  (XML_ITEM   *item, const char *filename);
char     *xml_error (void);

#ifdef __cplusplus
}
#endif

#endif                                  /*  Included                         */
