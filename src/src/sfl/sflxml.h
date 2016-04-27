/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflxml.h
    Title:      XML (Extensible Markup Language) access functions
    Package:    Standard Function Library (SFL)

    Written:    98/02/25  iMatix SFL project team <sfl@imatix.com>
    Revised:    98/09/30

    Synopsis:   Provides functions to read and write XML files, and manipulate
                XML data in memory as list structures.  XML is the Extensible
                Markup Language.  Accepts this XML syntax:
                <item [attr=["]value["]]...>value [child]</item>

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef SLFXML_INCLUDED                /*  Allow multiple inclusions        */
#define SLFXML_INCLUDED

/* -------------------------------------------------------------------------
    An XML tree is built as the following recursive structure:

                   .---------.    .----------.
                 .-:  Attr   :<-->:   0..n   :  Attributes are not sorted.
    .----------. : :  Head   :    :   attrs  :
    :   Item   :-' `---------'    `----------'
    :   node   :-. .---------.    .----------.
    `----------' : :  Child  :<-->:   0..n   :  Each child node is the root
                 `-:  Head   :    : children :  of its own tree of nodes.
                   `---------'    `----------'
   ------------------------------------------------------------------------- */


/*- Structure definitions -------------------------------------------------- */

typedef struct _XML_ITEM XML_ITEM;
typedef struct _XML_ATTR XML_ATTR;


/*- Function prototypes ---------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/*  XML item functions */
XML_ITEM *xml_new          (XML_ITEM *parent,
                            const char *name, const char *value);
void      xml_modify_value (XML_ITEM *item, const char *value);
char     *xml_item_name    (XML_ITEM *item);
char     *xml_item_value   (XML_ITEM *item);
void      xml_free         (XML_ITEM *item);

/*  XML tree mainipulation  */
void      xml_attach       (XML_ITEM *parent, XML_ITEM *item);
void      xml_detach       (XML_ITEM *item);

/*  XML family navigation  */
XML_ITEM *xml_first_child  (XML_ITEM *item);
XML_ITEM *xml_next_sibling (XML_ITEM *item);
XML_ITEM *xml_parent       (XML_ITEM *item);

/*  XML attribute functions  */
int       xml_put_attr     (XML_ITEM *item,
                            const char *name, const char *value);
XML_ATTR *xml_attr         (XML_ITEM *item, const char *name);
char     *xml_attr_name    (XML_ATTR *item);
char     *xml_attr_value   (XML_ATTR *item);
char     *xml_get_attr     (XML_ITEM *item,
                            const char *name, const char *deflt);
void      xml_free_attr    (XML_ATTR *attr);

/*  XML attribute navigation  */
XML_ATTR *xml_first_attr   (XML_ITEM *item);
XML_ATTR *xml_next_attr    (XML_ATTR *attr);

/*  XML housekeeping functions  */
Bool     xml_changed       (XML_ITEM *item);
Bool     xml_refresh       (XML_ITEM *item);


/*  Macros to treat all children and all attributes                          */

#define FORCHILDREN(child,item)    for (child  = xml_first_child (item);      \
                                        child != NULL;                        \
                                        child  = xml_next_sibling (child))

#define FORATTRIBUTES(attr,item)   for (attr  = xml_first_attr (item);        \
                                        attr != NULL;                         \
                                        attr  = xml_next_attr (attr))


#ifdef __cplusplus
}
#endif


#endif
