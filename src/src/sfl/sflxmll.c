/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflxmll.c
    Title:      XML serialisation functions
    Package:    Standard Function Library (SFL)

    Written:    96/06/08  iMatix SFL project team <sfl@imatix.com>
    Revised:    99/01/01

    Synopsis:   Loads XML file into memory, to/from disk files.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "prelude.h"                    /*  Universal include file           */
#include "sfldate.h"                    /*  Date and time functions          */
#include "sflfile.h"                    /*  File access functions            */
#include "sfllist.h"                    /*  List access functions            */
#include "sflmem.h"                     /*  Memory allocation functions      */
#include "sflstr.h"                     /*  String access functions          */
#include "sflxml.h"                     /*  XML definitions                  */
#include "sflsymb.h"
#include "sflhttp.h"                    /*  Meta-char encoding/decoding      */
#include "sflxmll.d"                    /*  Include dialog data              */

/*  Function prototypes                                                      */

static int     xml_save_item           (FILE *xmlfile, XML_ITEM *item,
                                        int level);
static void    init_charmaps           (void);
static void    build_charmap           (byte flag, char *chars);
static void    expect_token            (char *expect);
static char    get_next_non_space_char (void);
static Bool    xml_read                (void);
static int     collect_name            (void);
static char   *collect_literal         (char *prefix, char terminator);
static void    error_exception         (char *format, ...);


/*- Global variables used in this source file only --------------------------*/

static int
    char_nbr,                           /*  Current read position in line    */
    line_nbr;                           /*  Input line nbr from file         */

static const char
    *ppath,                             /*  XML file path as specified       */
    *pname;                             /*  XML file name as specified       */

static char
    *fname,                             /*  Full file name of XML file       */
    *literal,                           /*  String of any length             */
    token         [LINE_MAX + 1],       /*  Token from input stream          */
    srcline       [LINE_MAX + 1],       /*  Current source line              */
    name          [LINE_MAX + 1],       /*  Saved name                       */
    error_message [LINE_MAX + 1];       /*  Saved name                       */

static FILE
    *xmlfile;

static XML_ITEM
    *feedback,                          /*  Feedback for calling program     */
    *item,                              /*  Current XML item                 */
    *root;                              /*  Root XML item                    */


/*  Character classification tables and macros                               */

static byte
    cmap [256];                         /*  Character classification tables  */

#define CMAP_NAME        1              /*  Normal name character            */
#define CMAP_NAME_OPEN   2              /*  Valid character to start name    */
#define CMAP_QUOTE       4              /*  Possible string delimiters       */
#define CMAP_PRINTABLE   8              /*  Valid characters in literal      */
#define CMAP_DECIMAL    16              /*  Decimal digits                   */
#define CMAP_HEX        32              /*  Hexadecimal digits               */

                                        /*  Macros for character mapping:    */
#define is_name(ch)      (cmap [(byte) (ch)] & CMAP_NAME)
#define is_name_open(ch) (cmap [(byte) (ch)] & CMAP_NAME_OPEN)
#define is_quote(ch)     (cmap [(byte) (ch)] & CMAP_QUOTE)
#define is_printable(ch) (cmap [(byte) (ch)] & CMAP_PRINTABLE)
#define is_decimal(ch)   (cmap [(byte) (ch)] & CMAP_DECIMAL)
#define is_hex(ch)       (cmap [(byte) (ch)] & CMAP_HEX)


/*  ---------------------------------------------------------------------[<]-
    Function: xml_save

    Synopsis: Saves an XML tree to the specified file.  Returns the number
    of items saved, or -1 if there was an error.
    ---------------------------------------------------------------------[>]-*/

int
xml_save (
    XML_ITEM   *item,
    const char *filename)
{
    FILE
        *xmlfile;                       /*  XML output stream                */
    XML_ITEM
        *child;
    int
        count;                          /*  How many symbols did we save?    */

    ASSERT (item);
    ASSERT (filename);
    init_charmaps ();                   /*  Initialise character maps        */

    if ((xmlfile = file_open (filename, 'w')) == NULL)
        return (-1);                    /*  No permission to write file      */

    /*  Write XML file header                                                */
    fprintf (xmlfile, "<?XML VERSION=\"1.0\"?>\n");

    /*  Output children of XML root                                          */
    count = 0;
    FORCHILDREN (child, item)
        count += xml_save_item (xmlfile, child, 1);

    file_close (xmlfile);
    return (count);
}


/*  -------------------------------------------------------------------------
 *  init_charmaps
 *
 *  Initialise character map bit tables.  These are used to speed-up
 *  token recognition and collection.
 */

static void
init_charmaps (void)
{
    memset (cmap, 0, sizeof (cmap));    /*  Clear all bitmaps                */

    /*  Name     ::= (Letter | '_' | ':') (NameChar)*                        */
    /*  NameChar ::= Letter | Digit | MiscName                               */

    /*  Map fixed character sets to various bitmaps                          */
    build_charmap (CMAP_NAME, "abcdefghijklmnopqrstuvwxyz");
    build_charmap (CMAP_NAME, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    build_charmap (CMAP_NAME, "0123456789");
    build_charmap (CMAP_NAME, "_:.-");

    build_charmap (CMAP_NAME_OPEN, "abcdefghijklmnopqrstuvwxyz");
    build_charmap (CMAP_NAME_OPEN, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    build_charmap (CMAP_NAME_OPEN, "_:");

    build_charmap (CMAP_QUOTE, "\"'");

    /*  Printable characters.  ???                                           */
    build_charmap (CMAP_PRINTABLE, "abcdefghijklmnopqrstuvwxyz");
    build_charmap (CMAP_PRINTABLE, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    build_charmap (CMAP_PRINTABLE, "0123456789");
    build_charmap (CMAP_PRINTABLE, "!@#$%^&*()-_=+[]{}\\|;:'\"<>,./?`~ ");

    build_charmap (CMAP_DECIMAL, "0123456789");

    build_charmap (CMAP_HEX, "abcdefghijklmnopqrstuvwxyz");
    build_charmap (CMAP_HEX, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    build_charmap (CMAP_HEX, "0123456789");
}


/*  -------------------------------------------------------------------------
 *  build_charmap
 *
 *  Encode character string and flag into character map table.  Flag should
 *  be a 1-bit value from 1 to 128 (character map is 8 bits wide).
 */

static void
build_charmap (byte flag, char *string)
{
    for (; *string; string++)
        cmap [(byte) *string] |= flag;
}


static int
xml_save_item (FILE *xmlfile, XML_ITEM *item, int level)
{
    int
        count = 1;                      /*  Count 1 for current item         */
    XML_ITEM
        *child = NULL;
    XML_ATTR
        *attr;
    char
        *item_name,
        *item_value,
        *attr_name,
        *attr_value;

    /*  First output item name and attributes                                */
    item_name  = xml_item_name  (item);
    item_value = xml_item_value (item);
/*     fprintf (xmlfile, "<%*s%s", (level - 1) * 4, "", item_name); */
    fprintf (xmlfile, "<%s", item_name);
    FORATTRIBUTES (attr, item)
      {
        attr_name  = xml_attr_name  (attr);
        attr_value = xml_attr_value (attr);
/*         fprintf (xmlfile, "\n%*s%s=", level * 4, "", attr_name); */
        fprintf (xmlfile, "\n%s=", attr_name);
        http_encode_meta (srcline, attr_value, LINE_MAX);
        fprintf (xmlfile, "\"%s\"", srcline);
      }

    /*  If value or children exist, use long form, otherwise short form      */
    if ((xml_first_child (item)) || (item_value))
      {
        fprintf (xmlfile, ">\n");
        if (item_value)
            fprintf (xmlfile, "%s\n", item_value);

        FORCHILDREN (child, item)
            count += xml_save_item (xmlfile, child, level + 1);

/*         fprintf (xmlfile, "<%*s/%s>\n", (level - 1) * 4, "", item_name); */
        fprintf (xmlfile, "</%s>\n", item_name);
      }
    else
        fprintf (xmlfile, "/>\n");

    return (count);
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_error

    Synopsis: Returns the last error message generated by xml_load.
    ---------------------------------------------------------------------[>]-*/

char *
xml_error (void)
{
    return error_message;
}


/*  ---------------------------------------------------------------------[<]-
    Function: xml_load

    Synopsis: Loads the contents of an XML file into a new XML tree.  The XML
    data is not checked against a DTD.  Returns NULL if there was insufficient
    memory, or the XML file could not be read.  The XML tree always starts with
    a top-level item called 'XML' with these attributes:
    <TABLE>
    filename        Name of the XML input file
    filetime        Modification time of the file, "HHMMSSCC"
    filedate        Modification date of input file, "YYYYMMDD"
    </TABLE>
    Looks for the XML file on the specified path symbol, or in the current
    directory if the path argument is null.  Adds the specified extension
    to the file name if there is none already included.
    ---------------------------------------------------------------------[>]-*/

XML_ITEM *
xml_load (const char *path,
          const char *filename)
{
    feedback = NULL;                    /*  Reset return feedback            */

    ASSERT (filename);
    pname = filename;
    ppath = path;

#   include "sflxmll.i"                 /*  Include dialog interpreter       */
}


/*************************   INITIALISE THE PROGRAM   ************************/

MODULE initialise_the_program (void)
{
    root     = NULL;                    /*  No files open yet                */
    xmlfile  = NULL;                    /*  No files open yet                */
    line_nbr = 0;                       /*  Nothing read from file yet       */

    init_charmaps ();                   /*  Initialise character maps        */

    the_next_event = ok_event;
}


/*****************************   OPEN XML FILE   *****************************/

MODULE open_xml_file (void)
{
    fname = file_where ('r', ppath, pname, "xml");
    if (!fname)
      {
        error_exception ("Could not find XML file: %s", pname);
        return;
      }
    if ((xmlfile = file_open (fname, 'r')) == NULL)
      {
        error_exception ("Could not open XML file: %s", pname);
        return;
      }

    char_nbr    = 0;                    /*  Clear input line                 */
    srcline [0] = 0;
}


/**************************   INITIALISE XML TREE   **************************/

MODULE initialise_xml_tree (void)
{
    char
        buffer [LINE_MAX + 1];

    root = xml_new (NULL, "root", "");
    ASSERT (root);

    item = root;

    xml_put_attr (root, "filename", fname);
    sprintf (buffer, "%ld", timer_to_date (get_file_time (fname)));
    xml_put_attr (root, "filedate", buffer);
    sprintf (buffer, "%ld", timer_to_time (get_file_time (fname)));
    xml_put_attr (root, "filetime", buffer);
}


/*****************************   GET NEXT CHAR   *****************************/

MODULE get_next_char (void)
{
    char thisch;                        /*  Next char in token               */

    FOREVER
      {
        if (srcline [char_nbr] == 0)    /*  If we need input, read a line    */
            if (!xml_read ())
                return;

        thisch = srcline [char_nbr];
        if (thisch != 0)                /*  Unless we need input, stop       */
            break;
      }

    if (thisch == '<')
      {
        char_nbr++;
        the_next_event = open_event;
      }
    else
        the_next_event = char_event;
}


static Bool
xml_read (void)
{
    if (file_read (xmlfile, srcline))
      {
        char_nbr = 0;
        line_nbr++;
        return TRUE;
      }
    else
      {
        the_next_event = end_of_file_event;
        return FALSE;
      }
}


/*****************************   GET NEXT TOKEN   ****************************/

MODULE get_next_token (void)
{
    char thisch;                        /*  Next char in token               */

    thisch = get_next_non_space_char ();

    if (!thisch)
        return;

    if (thisch == '<')
      {
        char_nbr++;
        the_next_event = open_event;
      }
    else
    if (thisch == '/')
      {
        char_nbr++;
        the_next_event = slash_event;
      }
    else
    if (thisch == '>')
      {
        char_nbr++;
        the_next_event = close_event;
      }
    else
    if (thisch == '?')
      {
        char_nbr++;
        the_next_event = header_event;
      }
    else
    if ((                thisch == '!')
    &&  (srcline [char_nbr + 1] == '-')
    &&  (srcline [char_nbr + 2] == '-'))
      {
        char_nbr += 3;
        the_next_event = comment_event;
      }
    else
    if (collect_name ())
      {
        strcpy (name, token);
        the_next_event = name_event;
      }
    else
        error_exception ("Unrecognised token: %c", srcline [char_nbr]);
}


static char
get_next_non_space_char (void)
{
    char thisch;                        /*  Next char in token               */

    FOREVER
      {
        if (srcline [char_nbr] == 0)    /*  If we need input, read a line    */
            if (!xml_read ())
                return 0;

        /*  Skip spaces before token                                         */
        while (srcline [char_nbr] == ' ')
            char_nbr++;

        thisch = srcline [char_nbr];
        if (thisch != 0)                /*  Unless we need input, stop       */
            break;
      }

    return thisch;
}


static int
collect_name (void)
{
    int  size;                          /*  Size of token                    */
    char thisch;                        /*  Next char                        */

    /*  Name ::= (Letter | '_' | ':') (NameChar)*                            */

    size = 0;
    if (is_name_open (srcline [char_nbr]))
        while (is_name (thisch = srcline [char_nbr]))
          {
            char_nbr++;
            token [size++] = thisch;
          }

    token [size] = 0;                   /*  Terminate token string           */
    return size;
}


/***************************   CONFIRM ITEM OPEN   ***************************/

MODULE confirm_item_open (void)
{
    if (item == root)
      {
        error_exception ("Value belongs to no item.");
        raise_exception (error_event);
      }
}


/***************************   COLLECT ITEM VALUE   **************************/

MODULE collect_item_value (void)
{
    char
        *value;

    value = collect_literal (xml_item_value (item), '<');

    xml_modify_value (item, value);
    mem_free (value);
}


static char *
collect_literal (char *prefix, char terminator)
{
    char
        thisch,                         /*  Next character                   */
        *literal = NULL;                /*  The result                       */
    int
        start,                          /*  Start index in source line       */
        length,                         /*  Length of literal                */
        snippet;                        /*  Length of line in literal        */

    if (prefix)
        length = strlen (prefix);
    else
        length = 0;

    FOREVER
      {
        start  = char_nbr;

        thisch = srcline [char_nbr];
        while ((thisch != 0) && (thisch != terminator))
            thisch = srcline [++char_nbr];
        
        srcline [char_nbr] = 0;
        snippet = http_decode_meta (& srcline [start],
                                    & srcline [start],
                                    LINE_MAX - start);
        srcline [char_nbr] = thisch;

        if (literal)
          {
            literal = mem_realloc (literal, length + snippet + 1);
            ASSERT (literal);
            memcpy (&literal [length], & srcline [start], snippet);
          }         
        else
          {
            literal = mem_alloc   (length + snippet + 1);
            ASSERT (literal);
            memcpy (literal, prefix, length);
            memcpy (&literal [length], & srcline [start], snippet);
          }
        length += snippet;
        literal [length] = '\0';

        if (thisch == terminator)
            break;

        if (thisch == terminator)
          {
            literal [length] = '\0';
            break;
          }

        if (!xml_read ())
          {
            error_exception ("File end inside literal.");
            mem_free (literal);
            return prefix;
          }
      }
    return literal;
}


/****************************   ATTACH NEW ITEM   ****************************/

MODULE attach_new_item (void)
{
    item = xml_new (item, name, NULL);
    ASSERT (item);
}


/******************************   EXPECT NAME   ******************************/

MODULE expect_name (void)
{
    if (get_next_non_space_char ())
        if (collect_name ())
            strcpy (name, token);
        else
            error_exception ("Did not find a name.");
}


/***************************   CONFIRM ITEM NAME   ***************************/

MODULE confirm_item_name (void)
{
    if (lexcmp (name, xml_item_name (item)) != 0)
        error_exception ("Incorrect closing tag name: %s", name);
}


/*****************************   CLOSE THE ITEM   ****************************/

MODULE close_the_item (void)
{
    item = xml_parent (item);
    if (!item)
        error_exception ("Incorrect closing tag name: %s", name);
}


/******************************   EXPECT CLOSE   *****************************/

MODULE expect_close (void)
{
    expect_token (">");
}


static void
expect_token (char *expect)
{
    int  pos;                           /*  Offset in token                  */
    char thisch;                        /*  Next char in token               */

    thisch = get_next_non_space_char ();
    if (thisch == 0)                    /*  If end of file was reached       */
        return;

    pos = 0;
    while ((thisch = srcline [char_nbr]) == expect[pos])
      {
        if (thisch == 0)
            break;

        char_nbr++;
        pos++;
      }

    if (expect[pos] != 0)
        error_exception ("Unexpected token: %c", thisch);
}


/**************************   SKIP REST OF COMMENT   *************************/

MODULE skip_rest_of_comment (void)
{
    char thisch;                        /*  Next char in comment             */

    FOREVER
      {
        thisch = get_next_non_space_char ();
        if (thisch == 0)
            return;

        FOREVER
          {
            while ((thisch = srcline [char_nbr]) != 0)
              {
                char_nbr++;
                if ((            thisch == '-')
                &&  (srcline [char_nbr] == '-'))
                  {
                    char_nbr++;
                    return;
                  }
              }
            if (!xml_read ())
              {
                error_exception ("File end inside comment.");
                return;
              }
          }
      }
}


/**************************   SKIP REST OF HEADER   **************************/

MODULE skip_rest_of_header (void)
{
    char thisch;                        /*  Next char in comment             */

    FOREVER
      {
        thisch = get_next_non_space_char ();
        if (thisch == 0)
            return;

        FOREVER
          {
            while ((thisch = srcline [char_nbr]) != 0)
              {
                char_nbr++;
                if (thisch == '?')
                    return;
              }
            if (!xml_read ())
              {
                error_exception ("File end inside header.");
                return;
              }
          }
      }
}


/************************   CONFIRM ALL ITEMS CLOSED   ***********************/

MODULE confirm_all_items_closed (void)
{
    if (xml_parent (item) != NULL)
        error_exception ("Missing end tag.");
}


/*****************************   CLOSE XML FILE   ****************************/

MODULE close_xml_file (void)
{
    if (xmlfile)
        if (file_close (xmlfile))
            error_exception ("Error closing file.");
}


/************************   RETURN SUCCESS FEEDBACK   ************************/

MODULE return_success_feedback (void)
{
    feedback = root;
}


/**************************   EXPECT EQUALS TOKEN   **************************/

MODULE expect_equals_token (void)
{
    expect_token ("=");
}


/*****************************   EXPECT LITERAL   ****************************/

MODULE expect_literal (void)
{
    char thisch;

    thisch = get_next_non_space_char ();
    if (thisch == 0)                    /* End-of-file was reached           */
        return;

    if (!is_quote (thisch))
      {
        error_exception ("Invalid literal opening quote: %c",
                         thisch);
        return;
      }

    char_nbr++;                          /*  Skip opening quote              */
    literal = collect_literal (NULL, thisch);
    char_nbr++;                          /*  Skip closing quote              */
}


/**************************   ATTACH NEW ATTRIBUTE   *************************/

MODULE attach_new_attribute (void)
{
    if (xml_put_attr (item, name, literal) != 1)
        error_exception ("Duplicate attribute name: %s", name);
}


/******************************   FREE LITERAL   *****************************/

MODULE free_literal (void)
{
    mem_strfree (&literal);
}


/**************************   PROCESS OPTION VALUE   *************************/

MODULE process_option_value (void)
{
}


/*************************   FREE PARTIAL XML TREE   *************************/

MODULE free_partial_xml_tree (void)
{
    if (root)
        xml_free (root);
}


/*************************   RETURN ERROR FEEDBACK   *************************/

MODULE return_error_feedback (void)
{
    feedback = NULL;
}


/*************************   ERROR UNEXPECTED TOKEN   ************************/

MODULE unexpected_token_error (void)
{
    error_exception ("Unexpected character: %c", srcline [char_nbr - 1]);
}


/***************************   GET EXTERNAL EVENT   **************************/

MODULE get_external_event (void)
{
}


/*************************   TERMINATE THE PROGRAM    ************************/

MODULE terminate_the_program (void)
{
    the_next_event = terminate_event;
}


/*****************************************************************************/

local
error_exception (char *format, ...)
{
char
    *mess_ptr;
int
    offset;
va_list
    argptr;

    mess_ptr = error_message;
    if (line_nbr > 0)
      {
        offset = sprintf (mess_ptr, "%s %d: %s\n", pname, line_nbr, srcline);
        mess_ptr += offset;
      }

    va_start (argptr, format);          /*  Start variable arguments list    */
    offset = vsprintf (mess_ptr, format, argptr);
    va_end   (argptr);                  /*  End variable arguments list      */
    mess_ptr += offset;

    sprintf (mess_ptr, "\n");
    raise_exception (error_event);
}
