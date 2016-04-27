/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflxml.c
    Title:      XML (Extensible Markup Language) access functions
    Package:    Standard Function Library (SFL)

    Written:    98/02/25  iMatix SFL project team <sfl@imatix.com>
    Revised:    98/09/30

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "prelude.h"                    /*  Universal header file            */
#include "sflstr.h"                     /*  String functions                 */
#include "sfllist.h"                    /*  List access functions            */
#include "sflmem.h"                     /*  Memory access functions          */
#include "sflfile.h"                    /*  File access functions            */
#include "sfldate.h"                    /*  Date and time functions          */
#include "sflxml.h"                     /*  Prototypes for functions         */
#include "sflxmll.h"                    /*  Loading & saving functions       */


/*  Implementation-dependent type definitions                                */

struct _XML_ITEM {                      /*  Item node definition             */
    struct _XML_ITEM
        *next,                          /*  Next item in list                */
        *prev,                          /*  Previous item in list            */
        *parent;                        /*  Parent if this is a child        */
    LIST
        attrs,                          /*  List of attributes, 0 or more    */
        children;                       /*  List of children, 0 or more      */
    char
        *name,                          /*  Item name, allocated string      */
        *value;                         /*  Item value, allocated string     */
};

struct _XML_ATTR {                      /*  Attribute node definition        */
    struct _XML_ATTR
        *next,                          /*  Next attr in list                */
        *prev;                          /*  Previous attr in list            */
    struct _XML_ITEM
        *parent;                        /*  Parent item if this attribute    */
    char
        *name,                          /*  Attribute name                   */
        *value;                         /*  Attribute value, may be null     */
};


/*  ---------------------------------------------------------------------[<]-
    Function: xml_new

    Synopsis: Creates and initialises a new XML_ITEM item.  The item is set
    to link to itself, and its sublists are initialised to be empty.
    Returns the address of the created XML_ITEM item or NULL if there was
    not enough memory.  Sets the new item's (lower-case) name and value as
    specified; either of these arguments may be null.  If the parent argument 
    is not null, attaches the new item to the end of the parent item list.
    ---------------------------------------------------------------------[>]-*/

XML_ITEM *
xml_new (
    XML_ITEM   *parent,
    const char *name,
    const char *value)
{
    XML_ITEM
        *item;

    list_create (item, sizeof (XML_ITEM));
    if (item)
      {
        list_reset (&item-> attrs);
        list_reset (&item-> children);
        item-> parent = parent;
        item-> name   = strlwc (mem_strdup (name));
        item-> value  = mem_strdup (value);
        if (parent)
            list_relink_before (item, &parent-> children);

        return (item);
      }
    else
        return (NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_modify_value

    Synopsis: Modifies an existing XML item's value.
    ---------------------------------------------------------------------[>]-*/

void
xml_modify_value  (XML_ITEM *item, const char *value)
{
    ASSERT (item);

    if (!item-> value)
        item-> value = mem_strdup (value);
    else
    if (!streq (value, item-> value))
      {
        mem_free (item-> value);
        item-> value = mem_strdup (value);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_item_name

    Synopsis: Extracts the name of a specified XML item.  The returned string
    should NOT be modified.  To manipulate it, first make a copy first.
    ---------------------------------------------------------------------[>]-*/

char *
xml_item_name (XML_ITEM *item)
{
    ASSERT (item);

    return item-> name;
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_item_value

    Synopsis: Extracts the value of a specified XML item.  The returned string
    should NOT be modified.  To manipulate it, first make a copy first.
    ---------------------------------------------------------------------[>]-*/

char *
xml_item_value (XML_ITEM *item)
{
    ASSERT (item);

    return item-> value;
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_free

    Synopsis: Frees all memory used by an XML_ITEM item and its children.
    ---------------------------------------------------------------------[>]-*/

void
xml_free (
    XML_ITEM *item)
{
    ASSERT (item);

    /*  Free attribute nodes for the item                                    */
    while (!list_empty (&item-> attrs))
        xml_free_attr (item-> attrs.next);

    /*  Free child nodes for the item                                        */
    while (!list_empty (&item-> children))
        xml_free (item-> children.next);

    /*  Now free this item itself                                            */
    list_unlink (item);                 /*  Unlink from its parent list      */
    mem_free (item-> name);             /*  Free strings, if not null        */
    mem_free (item-> value);
    mem_free (item);                    /*  And free the item itself         */
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_attach

    Synopsis: Attaches an XML item as the child of a given parent.  If the
    item is already attached to a parent, it is first removed.
    ---------------------------------------------------------------------[>]-*/

void
xml_attach (
    XML_ITEM *parent,
    XML_ITEM *item)
{
    if (item-> parent)
        xml_detach (item);

    item-> parent = parent;
    if (parent)
        list_relink_before (item, &parent-> children);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_detach

    Synopsis: Removes an XML item from the tree.
    ---------------------------------------------------------------------[>]-*/

void
xml_detach (
    XML_ITEM *item)
{
    item-> parent = NULL;
    list_unlink (item);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_first_child

    Synopsis: Returns the first child node of the specified item, or NULL
    if there are none.
    ---------------------------------------------------------------------[>]-*/

XML_ITEM *
xml_first_child (XML_ITEM *item)
{
    ASSERT (item);

    if (!list_empty (&item-> children))
        return item-> children. next;
    else
        return NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_next_sibling

    Synopsis: Returns the next sibling of the specified item, or NULL if there
    if are none.
    ---------------------------------------------------------------------[>]-*/

XML_ITEM *
xml_next_sibling (XML_ITEM *item)
{
    ASSERT (item);

    if ((LIST *) item-> next != & item-> parent-> children)
        return item-> next;
    else
        return NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_parent

    Synopsis: Returns the parent of the specified item, or NULL if this is
    the root item.
    ---------------------------------------------------------------------[>]-*/

XML_ITEM *
xml_parent (XML_ITEM *item)
{
    ASSERT (item);

    return (item-> parent);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_put_attr

    Synopsis: Sets, modifies, or deletes an attribute for the specified item.
    The (lower-case) attribute name must be supplied.  If the value is NULL, 
    any attribute with the specified name is deleted.  Otherwise the specified
    attribute is either created or modified accordingly.  Returns the number 
    of attribute nodes created (-1, 0, or 1).
    ---------------------------------------------------------------------[>]-*/

int
xml_put_attr (
    XML_ITEM   *item,
    const char *name,
    const char *value)
{
    int
        feedback = 0;
    XML_ATTR
        *attr;

    ASSERT (item);
    ASSERT (name);

    attr = xml_attr (item, name);
    if (attr)
        if (value)                      /*  Value specified - update attr    */
          {
            mem_free (attr-> value);
            attr-> value = mem_strdup (value);
          }
        else
          {
            xml_free_attr (attr);       /*  No value - delete attribute      */
            feedback = -1;
          }
    else
        if (value)                      /*  Value specified - update attr    */
          {
            list_create (attr, sizeof (XML_ATTR));
            if (attr)
              {
                attr-> name   = strlwc (mem_strdup (name));
                attr-> value  = mem_strdup (value);
                attr-> parent = item;
                list_relink_before (attr, &item-> attrs);
                feedback = 1;
              }
          }
    return (feedback);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_attr

    Synopsis: Searches for the attribute with the specified (lower-case) 
    name; if found, returns the address of the attribute node, otherwise 
    returns NULL.
    ---------------------------------------------------------------------[>]-*/

XML_ATTR *
xml_attr (
    XML_ITEM   *item,
    const char *name)
{
    XML_ATTR
        *attr;

    ASSERT (item);
    ASSERT (name);

    FORLIST (attr, item-> attrs)
        if (lexcmp (attr-> name, name) == 0)
            return (attr);

    return (NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_attr_name

    Synopsis: Extracts the name of a specified XML attr.  The returned string
    should NOT be modified.  To manipulate it, first make a copy first.
    ---------------------------------------------------------------------[>]-*/

char *
xml_attr_name (XML_ATTR *attr)
{
    ASSERT (attr);

    return attr-> name;
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_attr_value

    Synopsis: Extracts the value of a specified XML attr.  The returned string
    should NOT be modified.  To manipulate it, first make a copy first.
    ---------------------------------------------------------------------[>]-*/

char *
xml_attr_value (XML_ATTR *attr)
{
    ASSERT (attr);

    return attr-> value;
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_get_attr

    Synopsis: Returns the value for the specified attribute, if it exists.
    Otherwise returns the default value.
    ---------------------------------------------------------------------[>]-*/

char *
xml_get_attr (
    XML_ITEM   *item,
    const char *name,
    const char *deflt)
{
    XML_ATTR
        *attr;

    ASSERT (item);
    ASSERT (name);

    attr = xml_attr (item, name);
    if (attr)
        return (attr-> value);
    else
        return ((char *) deflt);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_free_attr

    Synopsis: Frees all memory used by an XML_ATTR node.
    ---------------------------------------------------------------------[>]-*/

void
xml_free_attr (
    XML_ATTR *attr)
{
    ASSERT (attr);

    list_unlink (attr);
    mem_free (attr-> name);
    mem_free (attr-> value);
    mem_free (attr);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_first_attr

    Synopsis: Returns the first attribute of a specified XML item, or NULL
    if there are none.
    ---------------------------------------------------------------------[>]-*/

XML_ATTR *
xml_first_attr (XML_ITEM *item)
{
    ASSERT (item);

    if (!list_empty (&item-> attrs))
        return item-> attrs. next;
    else
        return NULL;
}
    

/*  ---------------------------------------------------------------------[<]-
    Function: xml_next_attr

    Synopsis: Returns the next attribute following the specified attribute,
    or NULL if there are none.
    ---------------------------------------------------------------------[>]-*/

XML_ATTR *
xml_next_attr (XML_ATTR *attr)
{
    ASSERT (attr);

    if ((LIST *) attr-> next != & attr-> parent-> attrs)
        return attr-> next;
    else
        return NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_changed

    Synopsis: Returns TRUE if the XML file loaded into the specified list
    has in the meantime been changed.  Returns FALSE if not.
    ---------------------------------------------------------------------[>]-*/

Bool
xml_changed (
    XML_ITEM *item)
{
    char
        *filename;

    ASSERT (item);

    /*  Date, time, and name of original XML file are in the list            */
    filename = xml_get_attr (item, "filename", NULL);
    if (filename
    &&  file_has_changed (filename,
                          atol (xml_get_attr (item, "filedate", "0")),
                          atol (xml_get_attr (item, "filetime", "0"))))
        return (TRUE);
    else
        return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_refresh

    Synopsis: Refreshes an XML tree created by xml_load ().  If the original
    file (as specified by the 'filename' attribute of the root item) has
    been modified, reloads the whole XML file.  Returns TRUE if the XML file
    was actually reloaded, or FALSE if the file had not changed or could not
    be accessed, or if the XML tree was incorrectly created.
    ---------------------------------------------------------------------[>]-*/

Bool
xml_refresh (
    XML_ITEM *item)
{
    char
        *filename,
        *pathsym;

    ASSERT (item);
    if (xml_changed (item))
      {
        pathsym  = mem_strdup (xml_get_attr (item, "pathsym",  NULL));
        filename = mem_strdup (xml_get_attr (item, "filename", NULL));
        xml_free (item);                /*  Delete previous XML tree         */
        xml_load (pathsym, filename);
        mem_free (pathsym);
        mem_free (filename);
        return (TRUE);
      }
    return (FALSE);
}


















