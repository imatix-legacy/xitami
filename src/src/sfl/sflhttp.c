/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflhttp.c
    Title:      HTTP and CGI Support functions
    Package:    Standard Function Library (SFL)

    Written:    96/05/31  iMatix SFL project team <sfl@imatix.com>
    Revised:    99/07/15

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "prelude.h"                    /*  Universal header file            */
#include "sflstr.h"                     /*  String functions                 */
#include "sflsymb.h"                    /*  Symbol functions                 */
#include "sflconv.h"                    /*  Convertion functions             */
#include "sfllist.h"                    /*  Linked-list functions            */
#include "sflmem.h"                     /*  Memory functions                 */
#include "sflfind.h"                    /*  Find text functions              */
#include "sflfile.h"                    /*  Files functions                  */
#include "sfldate.h"                    /*  Date/time functions              */
#include "sflhttp.h"                    /*  Prototypes for functions         */


/*  Constants -------------------------------------------------------------- */

/*  This is the maximum size of a stream of HTTP query data coming from a
 *  file.  Used by cgi_parse_file_vars ().
 */

#define CGI_QUERY_FILE_MAX      65535U
#define MULTI_BUFFER_SIZE       16384


/*- Local functions ---------------------------------------------------------*/

static void   save_multipart_header   (SYMTAB *table, SYMTAB *header,
                                       char *data, char *tmp_name,
                                       const char *local_format);
static void   multipart_decode_header (char *header, SYMTAB *table);
static DESCR *http_multipart2url      (const SYMTAB *symtab);


/*  ---------------------------------------------------------------------[<]-
    Function: http_escape

    Synopsis: Performs HTTP escaping on a string.  This works as follows:
    all characters except alphanumerics and spaces are converted into the
    3-byte sequence "%xx" where xx is the character's hexadecimal value;
    spaces are replaced by '+'.  Line breaks are stored as "%0D%0A", where
    a 'line break' is any one of: "\n", "\r", "\n\r", or "\r\n".  If the
    result buffer is NULL, calculates the required size, allocates a block
    of memory, and returns that.  Otherwise, returns result, which must be
    large enough for the escaping operation (see http_escape_size()).
    When you all http_escape() with a null target block, you must free the
    returned block using mem_free().  Returns NULL if it could not allocate
    a target block as required.
    ---------------------------------------------------------------------[>]-*/

char *
http_escape (
    const char *string,
    char *result)
{
    static char
        hex_char [] = "0123456789ABCDEF";
    char
        *target;                        /*  Where we store the result        */

    ASSERT (string);
    if (result == NULL)
        if ((result = mem_alloc (http_escape_size (string))) == NULL)
            return (NULL);              /*  Could not allocate a block       */

    target = result;
    while (*string)
      {
        if (isalnum (*string))          /*  Don't escape letters or digits   */
            *target++ = *string;
        else
        if (*string == ' ')             /*  Spaces are replaced by '+'       */
            *target++ = '+';
        else
        if (*string == '\n' || *string == '\r')
          {
            if ((string [1] == '\n' || string [1] == '\r')
            &&  (string [1] != *string))
                string++;
            *target++ = '%';            /*  New line becomes %0A%0D          */
            *target++ = '0';
            *target++ = 'A';
            *target++ = '%';
            *target++ = '0';
            *target++ = 'D';
          }
        else
          {
            *target++ = '%';            /*  Some other escaped character     */
            *target++ = hex_char [(byte) *string >> 4];
            *target++ = hex_char [(byte) *string & 15];
          }
        string++;
      }
    *target = '\0';                     /*  Terminate target string          */
    return (result);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_escape_size

    Synopsis: Returns the size of a string after HTTP escaping.  See the
    http_escape() function for details of the escaping algorithm.  Includes
    the null terminator in the returned size.
    ---------------------------------------------------------------------[>]-*/

size_t
http_escape_size (
    const char *string)
{
    size_t
        result_size = 1;                /*  Allow for null terminator        */

    ASSERT (string);
    while (*string)
      {
        if (isalnum (*string))          /*  Don't escape letters or digits   */
            result_size++;
        else
        if (*string == ' ')             /*  Spaces are replaced by '+'       */
            result_size++;
        else
        if (*string == '\n' || *string == '\r')
          {
            if ((string [1] == '\n' || string [1] == '\r')
            &&  (string [1] != *string))
                string++;
            result_size += 6;           /*  Line ending becomes %0D%0A       */
          }
        else
            result_size += 3;           /*  Some other escaped character     */

        string++;
      }
    return (result_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_unescape

    Synopsis: Removes HTTP escaping from a string.  See http_escape() for
    details of the escaping algorithm.  If the result string is NULL,
    modifies the source string in place, else fills-in the result string.
    Returns the resulting string.  End-of-line sequences (%0A%0D) are
    stored as a single new-line character, i.e. carriage-returns (%0D) are
    not stored.
    ---------------------------------------------------------------------[>]-*/

char *
http_unescape (
    char *string,
    char *result)
{
    /*  This lookup table gives us a quick way to convert a hex digit        */
    /*  into a binary value.  Note that the index must be [0..127].          */
    static char
        hex_to_bin [128] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*            */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*            */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*            */
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,    /*   0..9     */
            0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*   A..F     */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*            */
            0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*   a..f     */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };  /*            */
    char
        *target;                        /*  Where we store the result        */

    ASSERT (string);
    if (!result)                        /*  If result string is null,        */
        result = string;                /*    modify in place                */
    target = result;

    while (*string)
      {
        if (*string == '%'              /*  Unescape %xx sequence            */
        &&   string [1] && string [2])
          {
            *target = hex_to_bin [string [1] & 127] * 16
                    + hex_to_bin [string [2] & 127];
            string += 2;                /*  Bump past two hex digits         */
            if (*target != '\r')
                target++;               /*  We do not store CRs              */
          }
        else
        if (*string == '+')             /*  Spaces are escaped as '+'        */
            *target++ = ' ';
        else
            *target++ = *string;        /*  Otherwise just copy              */

        string++;
      }
    *target = '\0';                     /*  Terminate target string          */
    return (result);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_unescape_hex

    Synopsis: Removes HTTP hex escaping from a URL string, by expanding any
    sequences of characters %xx.
    ---------------------------------------------------------------------[>]-*/

char *
http_unescape_hex (
    char *string,
    char *result)
{
    /*  This lookup table gives us a quick way to convert a hex digit        */
    /*  into a binary value.  Note that the index must be [0..127].          */
    static char
        hex_to_bin [128] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*            */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*            */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*            */
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,    /*   0..9     */
            0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*   A..F     */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*            */
            0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /*   a..f     */
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };  /*            */
    char
        *target;                        /*  Where we store the result        */

    ASSERT (string);
    if (!result)                        /*  If result string is null,        */
        result = string;                /*    modify in place                */
    target = result;

    while (*string)
      {
        if (*string == '%'              /*  Unescape %xx sequence            */
        &&   string [1] && string [2])
          {
            *target = hex_to_bin [string [1] & 127] * 16
                    + hex_to_bin [string [2] & 127];
            string += 2;                /*  Bump past two hex digits         */
            target++;             
          }
        else
            *target++ = *string;        /*  Otherwise just copy              */

        string++;
      }
    *target = '\0';                     /*  Terminate target string          */
    return (result);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_query2strt

    Synopsis: Parses a HTTP query string, building an array of strings of
    the format "name=value".  The query string is assumed to be in escaped
    format, so http_unescape() is always applied to the query string.
    Within the query string, field=value pairs are delimited by & or ;.
    Returns a pointer to the array.  The array is allocated dynamically.
    The array ends with a NULL string.  To free the table, call strtfree().
    If there was not enough memory to allocate the table, returns NULL.
    ---------------------------------------------------------------------[>]-*/

char **
http_query2strt (
    const char *original_query)
{
    char
        *query,                         /*  Local copy of query string       */
        *query_ptr,                     /*  Pointer into query string        */
        *query_next,                    /*  Pointer to next query chunk      */
        **strings;                      /*  Returned string array            */
    int
        char_nbr,                       /*  Index into query string          */
        string_count,                   /*  Size of string table             */
        string_nbr;                     /*  Index into string table          */

    ASSERT (original_query);

    if (*original_query == '&')         /*  Skip leading & if present        */
        original_query++;

    if ((query = mem_strdup (original_query)) == NULL)
        return (NULL);                  /*  Could not allocate memory        */

    /*  Break query string at & and ; delimiters and count strt size         */
    string_count = 1;                   /*  Last string has no delimiter     */
    for (char_nbr = 0; original_query [char_nbr]; char_nbr++)
        if (query [char_nbr] == '&' || query [char_nbr] == ';')
          {
            query [char_nbr] = '\0';
            string_count++;
          }

    /*  Allocate the array of pointers with one slot for the final NULL      */
    if ((strings = mem_alloc (sizeof (char *) * (string_count + 1))) == NULL)
      {
        mem_free (query);
        return (NULL);                  /*  Could not allocate memory        */
      }

    /*  Query string now consists of a series of substrings, each ending in
     *  a null character.  We have to unescape each substring, which we do
     *  in-place: the unescaped string is never larger than the original
     *  string.
     */
    query_ptr = query;
    for (string_nbr = 0; string_nbr < string_count; string_nbr++)
      {
        /*  Unescape next query string component                             */
        query_next = query_ptr + strlen (query_ptr) + 1;
        http_unescape (query_ptr, NULL);

        /*  Allocate space for "name=value" plus final null char             */
        strings [string_nbr] = mem_strdup (query_ptr);
        query_ptr = query_next;
      }
    strings [string_nbr] = NULL;        /*  Store final null pointer         */
    mem_free (query);                   /*  Release temporary memory         */
    return (strings);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_query2symb

    Synopsis: Parses a HTTP query string, and populates a symbol table with
    the resulting field values.  The query string is assumed to be escaped,
    so http_unescape() is always applied to the query string.  Within the
    query string, field=value pairs are delimited by & or ;.  Returns a
    SYMTAB pointer to the new table.  If there was not enough memory to
    allocate the table, returns NULL.
    ---------------------------------------------------------------------[>]-*/

SYMTAB *
http_query2symb (
    const char *query)
{
    char
        **strings;                      /*  Formatted string array           */
    SYMTAB
        *symtab;                        /*  Returned symbol table            */

    strings = http_query2strt (query);
    if (strings)
      {
        symtab = strt2symb (strings);
        strtfree (strings);
        return (symtab);
      }
    else
        return (NULL);                  /*  Couldn't create string table     */
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_query2descr

    Synopsis: Parses a HTTP query string, and returns the values as a DESCR
    block, composed of null-delimited strings with an empty string at the
    end.  See strt2descr() and http_query2symb() for more details.  Returns
    the address of the allocated descriptor, or NULL if there was not
    enough memory.
    ---------------------------------------------------------------------[>]-*/

DESCR *
http_query2descr (
    const char *query)
{
    char
        **strings;                      /*  Formatted string array           */
    DESCR
        *descr;                         /*  Returned descriptor              */

    strings = http_query2strt (query);
    if (strings)
      {
        descr = strt2descr (strings);
        strtfree (strings);
        return (descr);
      }
    else
        return (NULL);                  /*  Couldn't create string table     */
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_encode_meta

    Synopsis: Translates special characters into HTML/SGML metacharacters.
    The input buffer is not modified; you supply an output buffer and specify
    the maximum size of this buffer.  The input buffer must end in a null.
    Returns the final size of the translated data excluding the final null
    byte.  If the resulting data is too long, it is brutally truncated.
    ---------------------------------------------------------------------[>]-*/

size_t
http_encode_meta (
    char       *output,
    const char *input,
    size_t      outmax)
{
    size_t
        space_left,                     /*  Space left in destination        */
        length;
    const char
        *source;                        /*  Pointer to source string         */
    char
        *dest;                          /*  Pointer to result string         */

    ASSERT (input);
    ASSERT (output);

    if (outmax == 0)                    /*  Special case for zero space      */
        return (0);

    space_left = outmax - 1;            /*  Allow for final null byte        */
    dest = output;
    for (source = input; *source; source++)
      {
        length = encode_meta_char (dest, *source, space_left);
        space_left -= length;
        dest += length;
      }
    *dest = '\0';
    return ((size_t) (dest - output));
}


/*  ---------------------------------------------------------------------[<]-
    Function: encode_meta_char

    Synopsis: Translates one character into HTML/SGML metacharacters.  You
    supply an output buffer and specify the maximum size of this buffer.
    Returns the final size of the translated data excluding the final null
    byte.  If the resulting data is too long, it is brutally truncated.
    ---------------------------------------------------------------------[>]-*/

size_t
encode_meta_char (
    char *output,
    char code,
    size_t outmax)
{
    /*  This lookup table provides a translation string for each byte
     *  in the character set.  We assume 8-bit characters.  When the
     *  string is NULL, the character is copied without translation.
     */
    static char
        *meta [256];                    /*  Metacharacter translation table  */
    static Bool
        first_time = TRUE;              /*  First time flag                  */
    int
        char_index;                     /*  Index into translation table     */
    size_t
        space_left;                     /*  Space left in destination        */
    char
        *dest,                          /*  Pointer to result string         */
        *meta_char,                     /*  Pointer through metachar string  */
        buffer [6];                     /*  Buffer for numeric conversions   */

#   define OUTPUT(c)  if (!space_left) ; else { *dest++ = (c); space_left--; }
#   define FIRST_PRINTABLE 32

    space_left = outmax - 1;            /*  Allow for final null byte        */
    dest = output;

    /*  Initialise translation table first time through                      */
    if (first_time)
      {
        first_time = FALSE;
        for (char_index = 0; char_index < 256; char_index++)
            meta [char_index] = NULL;

        /*  The four standard meta-characters plus CR  */
        meta ['\n'] = "cr";
        meta ['&']  = "amp";
        meta ['<']  = "lt";
        meta ['>']  = "gt";
        meta ['"']  = "quot";

#if (defined (__UNIX__) || defined (__WINDOWS__))
        /*  UNIX and Windows generally use ISO-8859-1 (Latin-1)              */
        meta [0xC4] = "Auml";
        meta [0xC5] = "Aring";
        meta [0xC6] = "AElig";
        meta [0xD6] = "Ouml";
        meta [0xDC] = "Uuml";
        meta [0xE0] = "agrave";
        meta [0xE1] = "aacute";
        meta [0xE2] = "acirc";
        meta [0xE4] = "auml";
        meta [0xE5] = "aring";
        meta [0xE6] = "aelig";
        meta [0xE7] = "ccedil";
        meta [0xE8] = "egrave";
        meta [0xE9] = "eacute";
        meta [0xEA] = "ecirc";
        meta [0xEB] = "euml";
        meta [0xEC] = "igrave";
        meta [0xED] = "iacute";
        meta [0xEE] = "icirc";
        meta [0xEF] = "iuml";
        meta [0xF2] = "ograve";
        meta [0xF3] = "oacute";
        meta [0xF4] = "ocirc";
        meta [0xF6] = "ouml";
        meta [0xF9] = "ugrave";
        meta [0xFA] = "uacute";
        meta [0xFB] = "ucirc";
        meta [0xFC] = "uuml";
        meta [0xFD] = "yuml";

#elif (defined (__MSDOS__))
        /*  DOS generally uses the PC-1 alphabet                             */
        meta [0x80] = "uuml";
        meta [0x82] = "eacute";
        meta [0x83] = "acirc";
        meta [0x84] = "auml";
        meta [0x85] = "agrave";
        meta [0x86] = "aring";
        meta [0x87] = "ccedil";
        meta [0x88] = "ecirc";
        meta [0x89] = "euml";
        meta [0x8A] = "egrave";
        meta [0x8B] = "iuml";
        meta [0x8C] = "icirc";
        meta [0x8D] = "igrave";
        meta [0x8E] = "Auml";
        meta [0x2F] = "Aring";
        meta [0x91] = "aelig";
        meta [0x92] = "AElig";
        meta [0x93] = "ocirc";
        meta [0x94] = "ouml";
        meta [0x95] = "ograve";
        meta [0x96] = "ucirc";
        meta [0x97] = "ugrave";
        meta [0x98] = "yuml";
        meta [0x99] = "Ouml";
        meta [0x9A] = "Uuml";
        meta [0xA0] = "aacute";
        meta [0xA1] = "iacute";
        meta [0xA2] = "oacute";
        meta [0xA3] = "uacute";
#endif
      }
    
    meta_char = meta [(int) code & 255];
    if ((!meta_char) && (code < FIRST_PRINTABLE))
      {
        sprintf (buffer, "#%u;", (byte) code);
        meta_char = buffer;
      }
    
    if (meta_char)
      {
        OUTPUT ('&');
        while (*meta_char)
          {
            OUTPUT (*meta_char);
            meta_char++;
          }
        OUTPUT (';');
      }
    else
        OUTPUT (code);

    *dest = '\0';
    return ((size_t) (dest - output));
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_decode_meta

    Synopsis: Translates special characters from HTML/SGML metacharacters.
    The input buffer is not modified; you supply an output buffer and specify
    the maximum size of this buffer.  The input buffer must end in a null.
    Returns the final size of the translated data excluding the final null
    byte.  If the resulting data is too long, it is brutally truncated.
    Invalid meta-characters are left as-is.
    ---------------------------------------------------------------------[>]-*/

size_t
http_decode_meta (
    char       *output,
    const char *input,
    size_t      outmax)
{
    const char
        *source;                        /*  Pointer to source string         */
    char
        *dest,                          /*  Pointer to result string         */
        *end,                           /*  Next character after meta-char   */
        code;                           /*  Decoded metachar string          */
    size_t
        space_left;                     /*  Space left in destination        */

    ASSERT (input);
    ASSERT (output);

    if (outmax == 0)                    /*  Special case for zero space      */
        return (0);

    space_left = outmax - 1;            /*  Allow for final null byte        */
    dest = output;
    for (source = input; *source; source++)
      {
        if (*source == '&')
          {
            end = strchr (source, ';');
            if (end)
              {
                code = decode_meta_charn (source + 1, end - source - 1);
                if (code)
                  {
                    OUTPUT (code);
                    source = end;
                  }
                else
                    OUTPUT (*source);
              }
            else
                OUTPUT (*source);
          }
        else
          OUTPUT (*source);
      }
    *dest = '\0';
    return ((size_t) (dest - output));
}


/*  ---------------------------------------------------------------------[<]-
    Function: decode_meta_charn

    Synopsis: Decodes a single meta-character (the piece from the character
    after the '&' up to but not including the ';'.  If the meta-character
    is valid, returns the character; otherwise returns zero.  Decodes both
    named and numeric meta-characters.  Use the macro decode_meta_char if
    the input has a terminating zero.
    ---------------------------------------------------------------------[>]-*/

char
decode_meta_charn (const char *input, size_t length)
{
#define META_COUNT 34
    static char
        *meta [META_COUNT];             /*  Metacharacter translation tables */
    static byte
        code [META_COUNT];
    static Bool
        first_time = TRUE;              /*  First time flag                  */
    int
        char_index,                     /*  Index into translation table     */
        min,                            /*  Pointers for binary chop         */
        max,
        cmp,
        num;

    /*  Initialise translation table first time through                      */
    if (first_time)
      {
        first_time = FALSE;

        /*  The meta-characters must be in alphabetical order so we can use  */
        /*  a binary chop.                                                   */
#if (defined (__UNIX__) || defined (__WINDOWS__))
        /*  UNIX and Windows generally use ISO-8859-1 (Latin-1)              */
        code [ 0] = 0xC6;  meta [ 0] = "AElig";
        code [ 1] = 0xC5;  meta [ 1] = "Aring";
        code [ 2] = 0xC4;  meta [ 2] = "Auml";
        code [ 3] = 0xD6;  meta [ 3] = "Ouml";
        code [ 4] = 0xDC;  meta [ 4] = "Uuml";
        code [ 5] = '&';   meta [ 5] = "amp";
        code [ 6] = 0xE1;  meta [ 6] = "aacute";
        code [ 7] = 0xE2;  meta [ 7] = "acirc";
        code [ 8] = 0xE6;  meta [ 8] = "aelig";
        code [ 9] = 0xE0;  meta [ 9] = "agrave";
        code [10] = 0xE5;  meta [10] = "aring";
        code [11] = 0xE4;  meta [11] = "auml";
        code [12] = 0xE7;  meta [12] = "ccedil";
        code [13] = '\n';  meta [13] = "cr";
        code [14] = 0xE9;  meta [14] = "eacute";
        code [15] = 0xEA;  meta [15] = "ecirc";
        code [16] = 0xE8;  meta [16] = "egrave";
        code [17] = 0xEB;  meta [17] = "euml";
        code [18] = '>';   meta [18] = "gt";
        code [19] = 0xED;  meta [19] = "iacute";
        code [20] = 0xEE;  meta [20] = "icirc";
        code [21] = 0xEC;  meta [21] = "igrave";
        code [22] = 0xEF;  meta [22] = "iuml";
        code [23] = '<';   meta [23] = "lt";
        code [24] = 0xF3;  meta [24] = "oacute";
        code [25] = 0xF4;  meta [25] = "ocirc";
        code [26] = 0xF2;  meta [26] = "ograve";
        code [27] = 0xF6;  meta [27] = "ouml";
        code [28] = '"';   meta [28] = "quot";
        code [29] = 0xFA;  meta [29] = "uacute";
        code [30] = 0xFB;  meta [30] = "ucirc";
        code [31] = 0xF9;  meta [31] = "ugrave";
        code [32] = 0xFC;  meta [32] = "uuml";
        code [33] = 0xFD;  meta [33] = "yuml";
#elif (defined (__MSDOS__))
        code [ 0] = 0x92;  meta [ 0] = "AElig";
        code [ 1] = 0x2F;  meta [ 1] = "Aring";
        code [ 2] = 0x8E;  meta [ 2] = "Auml";
        code [ 3] = 0x99;  meta [ 3] = "Ouml";
        code [ 4] = 0x9A;  meta [ 4] = "Uuml";
        code [ 5] = 0xA0;  meta [ 5] = "aacute";
        code [ 6] = 0x8E;  meta [ 6] = "acirc";
        code [ 7] = 0x91;  meta [ 7] = "aelig";
        code [ 8] = 0x85;  meta [ 8] = "agrave";
        code [ 9] = '&';   meta [ 9] = "amp";
        code [10] = 0x86;  meta [10] = "aring";
        code [11] = 0x84;  meta [11] = "auml";
        code [12] = 0x87;  meta [12] = "ccedil";
        code [13] = '\n';  meta [13] = "cr";
        code [14] = 0x82;  meta [14] = "eacute";
        code [15] = 0x88;  meta [15] = "ecirc";
        code [16] = 0x8A;  meta [16] = "egrave";
        code [17] = 0x89;  meta [17] = "euml";
        code [18] = '>';   meta [18] = "gt";
        code [19] = 0xA1;  meta [19] = "iacute";
        code [20] = 0x8C;  meta [20] = "icirc";
        code [21] = 0x8D;  meta [21] = "igrave";
        code [22] = 0x8B;  meta [22] = "iuml";
        code [23] = '<';   meta [23] = "lt";
        code [24] = 0xA2;  meta [24] = "oacute";
        code [25] = 0x93;  meta [25] = "ocirc";
        code [26] = 0x95;  meta [26] = "ograve";
        code [27] = 0x94;  meta [27] = "ouml";
        code [28] = '"';   meta [28] = "quot";
        code [29] = 0xA3;  meta [29] = "uacute";
        code [30] = 0x96;  meta [30] = "ucirc";
        code [31] = 0x97;  meta [31] = "ugrave";
        code [32] = 0x80;  meta [32] = "uuml";
        code [33] = 0x98;  meta [33] = "yuml";
#endif
      }

    if (*input == '#')    /*  Numeric translation  */
      {
        input++;
        num = 0;
        if (*input == 'x')  /*  Hex  */
          {
            input++;
            FOREVER
              {
                if ((*input >= '0') && (*input <= '9'))
                    num = (num * 16) + *input - '0';
                else if ((*input >= 'a') && (*input <= 'f'))
                    num = (num * 16) + *input - 'a' + 10;
                else
                    break;

                input++;
              }
          }
        else
            FOREVER
              {
                if ((*input >= '0') && (*input <= '9'))
                    num = (num * 10) + *input - '0';
                else
                    break;

                input++;
              }

        if (*input != ';')
            num = 0;

        return num;
      }
    else  /*  Lookup meta-character  */
      {
        min = 0;
        max = META_COUNT;
        while (max > min)
          {
            char_index = (max + min) / 2;
            cmp = strncmp (input, meta [char_index], length);
            if (cmp == 0)
                return code [char_index];

            if (cmp > 0)
                min = char_index + 1;
            else
                max = char_index;
          }

        return 0;
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: cgi_parse_query_vars

    Synopsis: Parses a CGI query string and loads the resulting variables
    into an existing symbol table, optionally prefixing each name with a
    string.  Returns the number of variables loaded.  The prefix can be
    NULL or empty if not required.
    ---------------------------------------------------------------------[>]-*/

int
cgi_parse_query_vars (
    SYMTAB *symtab,
    const char *query,
    const char *prefix)
{
    char
        *query_var,                     /*  Query variable name              */
        **query_vars,                   /*  Query as string table            */
        *equals;                        /*  Equal sign in variable           */
    int
        string_nbr,                     /*  Index into string table          */
        variables = 0;                  /*  Number of variables loaded       */

    ASSERT (symtab);
    if ((query_vars = http_query2strt (query)) == NULL)
        return (0);                     /*  Not enough memory                */

    for (string_nbr = 0; query_vars [string_nbr]; string_nbr++)
      {
        equals = strchr (query_vars [string_nbr], '=');
        if (equals)
          {
            *equals = '\0';             /*  Cut into two strings             */
            if (prefix == NULL)
                prefix = "";            /*  Make safe for xstrcpy()          */
            query_var = xstrcpy (NULL, prefix, query_vars [string_nbr], NULL);
            sym_assume_symbol (symtab, query_var, equals + 1);
            mem_strfree (&query_var);
            *equals = '=';              /*  Restore previous state           */
            variables++;                /*  Count this variable              */
          }
      }
    strtfree (query_vars);
    return (variables);
}


/*  ---------------------------------------------------------------------[<]-
    Function: cgi_parse_file_vars

    Synopsis: Parses a CGI query string stored in a file, and loads the
    resulting variables into an existing symbol table, optionally
    prefixing each name with a string.  Returns the number of variables
    loaded.  The prefix can be NULL or empty if not required.  The
    file data is assumed to be escaped (see http_escape()); the data
    should not contain line breaks, spaces, or other unescaped chars.
    The file should already have been opened: a typical use for this
    function is to parse the values supplied in stdin.  The maximum size
    for the file is CGI_QUERY_FILE_MAX characters.
    ---------------------------------------------------------------------[>]-*/

int
cgi_parse_file_vars (
    SYMTAB *symtab,
    FILE   *file,
    const char *prefix,
    size_t size)
{
    char
        *query;                         /*  Data loaded from file            */
    size_t
        read_size;                      /*  Amount of data read from file    */
    int
        variables = 0;                  /*  Number of variables loaded       */

    ASSERT (file);
    ASSERT (symtab);
    ASSERT (size <= CGI_QUERY_FILE_MAX);

    if ((query = mem_alloc (size + 1)) == NULL)
        return (0);

    read_size = fread (query, 1, size, file);
    query [read_size] = '\0';
    variables = cgi_parse_query_vars (symtab, query, prefix);
    mem_free (query);
    return (variables);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_multipart_decode

    Synopsis: Parses a multipart-encoded file (as received by a web server as
    POST data) and returns a HTTP-encoded string containing the field data,
    in the format: "name=value&name=value&name=value...".  For each field that
    refers to an uploaded file (INPUT field with type FILE), creates a
    temporary file holding the data.  The name of this temporary file is put
    into a generated variable, whose name is built by using the local format
    string (ex: '%s_tmp').  The actual uploaded file is stored in
    a temporary file whose name is generated by the SFL get_tmp_file_name()
    function.  So, data for a file upload field called "doc" will be stored in
    a temporary file called (eg) "temp1234.tmp", and a field "doc_tmp" will be
    added, with the value "temp1234.tmp".  The HTTP-encoded string is returned
    as a DESCR block, which you can decode using http_query2strt(), passing the
    descriptor data.  You must free the descriptor using mem_free() when you're
    finished with it.
    ---------------------------------------------------------------------[>]-*/

DESCR *
http_multipart_decode (const char *mime_file, const char *store_path,
                       const char *local_format)
{
    FILE
        *f_source,
        *f_tmp = NULL;
    char
        *tmp_name = NULL,
        *p_head,
        *p_data,
        *p_next,
        *buffer;
    int
        offset,
        read_size;
    static char
        separator [80 + 1];
    static int
        sep_size;
    SYMTAB
        *table,
        *header_tab;
    qbyte
        tmp_index = 1;
    DESCR
        *descr = NULL;

    ASSERT (local_format);

    if (strstr (local_format, "%s") == NULL)
        return (NULL);

    buffer = mem_alloc (MULTI_BUFFER_SIZE + 1);
    if (buffer == NULL)
        return (NULL);

    table = sym_create_table ();
    if (table == NULL)
      {
        mem_free (buffer);
        return (NULL);
      }

    header_tab = sym_create_table ();
    if (header_tab == NULL)
      {
        mem_free (buffer);
        sym_delete_table (table);
        return (NULL);
      }

    f_source = fopen (mime_file, "rb");
    if (f_source == NULL)
      {
        mem_free (buffer);
        sym_delete_table (table);
        sym_delete_table (header_tab);
        return (NULL);
      }

    memset (separator, 0, sizeof (separator));
    separator [0] = 0x0D;
    separator [1] = 0x0A;
    fgets (&separator [2], 78, f_source);
    strconvch (&separator [2] , '\r', '\0');
    strconvch (&separator [2] , '\n', '\0');
    sep_size  = strlen (separator);

    read_size = fread (buffer, 1, MULTI_BUFFER_SIZE, f_source);
    p_next = buffer;
    while (read_size > 0)
      {
        sym_empty_table (header_tab);
        p_head = p_next;
        p_data = (char *) memfind ((byte *) p_head,
                          MULTI_BUFFER_SIZE - (p_head - buffer),
                          (byte *) "\r\n\r\n", 4, FALSE);
        if (p_data)
          {
            *p_data = '\0';
            p_data += 4;
          }
        if (p_head)
          {
            multipart_decode_header (p_head, header_tab);
            if (sym_lookup_symbol (header_tab, "filename") != NULL)
              {
                if (f_tmp != NULL)
                  {
                    ASSERT (tmp_name != NULL);
                    fclose (f_tmp);
                    f_tmp = NULL;
                    if (get_file_size (tmp_name) == 0)
                        file_delete (tmp_name);
                  }
                tmp_name = get_tmp_file_name (store_path, &tmp_index, "tmp");
                f_tmp = fopen (tmp_name, "wb");
              }
          }
        p_next = (char *) memfind ((byte *) p_data,
                          read_size - (p_data - buffer),
                          (byte *) separator, sep_size, FALSE);
        if (p_next != NULL)
          {
            *p_next = '\0';
            save_multipart_header (table, header_tab, p_data, tmp_name,
                                   local_format);
            if (f_tmp)
              {
                fwrite (p_data, p_next - p_data, 1, f_tmp);
                fclose (f_tmp);
                f_tmp = NULL;
                if (get_file_size (tmp_name) == 0)
                    file_delete (tmp_name);
              }
            p_next += sep_size;

            /*  Found end of file marker                                     */
            if (*p_next == '-' && *(p_next + 1) == '-')
              {
                if (f_tmp)
                  {
                    fclose (f_tmp);
                    f_tmp = NULL;
                    if (get_file_size (tmp_name) == 0)
                        file_delete (tmp_name);
                  }
                break;
              }
            else
                while (*p_next == '\r' || *p_next == '\n')
                    p_next++;
          }
        else
          {
            if (f_tmp)
                fwrite (p_data, &buffer [read_size - sep_size ] - p_data,
                        1, f_tmp);
            offset = 0;
            while (read_size > 0 && p_next == NULL)
              {
                memmove (buffer, &buffer [read_size - sep_size + offset ],
                                 sep_size);
                read_size = fread (&buffer [sep_size], 1,
                                   MULTI_BUFFER_SIZE - sep_size, f_source);
                p_next = (char *) memfind ((byte *) buffer,
                                  read_size + sep_size,
                                  (byte *) separator, sep_size, FALSE);
                if (p_next != NULL)
                  {
                    *p_next = '\0';
                    save_multipart_header (table, header_tab,
                                           p_data, tmp_name, local_format);
                    if (f_tmp)
                      {
                        fwrite (buffer, p_next - buffer, 1, f_tmp);
                        fclose (f_tmp);
                        f_tmp = NULL;
                        if (get_file_size (tmp_name) == 0)
                            file_delete (tmp_name);
                      }
                    p_next += sep_size;

                   /*  Found end of file marker                              */
                   if (*p_next == '-' && *(p_next + 1) == '-')
                     {
                       read_size = 0;
                       break;
                     }
                   else
                       while (*p_next == '\r' || *p_next == '\n')
                           p_next++;
                   read_size += sep_size;
                  }
                else
                  {
                    if (f_tmp)
                        fwrite (buffer, read_size, 1, f_tmp);
                    offset = sep_size;
                  }

              }
          }
      }
    if (f_tmp)
      {
        fclose (f_tmp);
        if (get_file_size (tmp_name) == 0)
            file_delete (tmp_name);
      }
    sym_delete_table (header_tab);
    fclose (f_source);
    mem_free (buffer);

    descr = http_multipart2url (table);
    sym_delete_table (table);

    return (descr);
}


/*  -------------------------------------------------------------------------
    Function: http_multipart2url

    Synopsis: Convert a symbol table to a string in format :
              name=value&name=value&name=value ....
    -------------------------------------------------------------------------*/

static DESCR *
http_multipart2url  (const SYMTAB *symtab)
{
    DESCR
        *descr;                         /*  Formatted descriptor             */
    SYMBOL
        *symbol;                        /*  Pointer to symbol                */
    char
        *p_char,
        *p_val;
    qbyte
        buffer_length = 0;

    if (!symtab)
        return (NULL);                  /*  Return NULL if argument is null  */

    /*  Calculate length of buffer                                           */
    for (symbol = symtab-> symbols; symbol; symbol = symbol-> next)
        buffer_length += strlen (symbol-> name) + strlen (symbol-> value) + 2;

    if (buffer_length > UINT_MAX)
        return (NULL);                  /*  Too large for memory model       */
    else
      {
        descr = mem_descr (NULL, (size_t) buffer_length + 1);
        if (descr == NULL)
            return (NULL);
      }
    p_char = (char *) descr-> data;
    for (symbol = symtab-> symbols; symbol; symbol = symbol-> next)
      {
        if (symbol != symtab-> symbols)
            *p_char++ = '&';
        p_val = symbol-> name;
        while (*p_val)
            *p_char++ = *p_val++;
        *p_char++ = '=';
        p_val = symbol-> value;
        while (*p_val)
            *p_char++ = *p_val++;
      }
    *p_char = '\0';

    return (descr);
}


/*  -------------------------------------------------------------------------
    Function: save_multipart_header

    Synopsis: Store field name and value in symbol table.
    -------------------------------------------------------------------------*/

static void
save_multipart_header (SYMTAB *table, SYMTAB *header, char *data,
                       char *tmp_name, const char *local_format)
{
    SYMBOL
        *sym_filename,
        *symbol;
    static char
        tmp_val [LINE_MAX + 1];
    char
        *value;

    /* Check if is a file uploaded or form field                             */
    if ((sym_filename = sym_lookup_symbol (header, "filename")) != NULL)
      {
        symbol = sym_lookup_symbol (header, "name");
        if (symbol)
          {
            value = http_escape (sym_filename-> value, NULL);
            if (value)
              {
                sym_assume_symbol (table, symbol-> value, value);
                mem_free (value);
              }
            sprintf (tmp_val, local_format, symbol-> value);

            value = http_escape (tmp_name, NULL);
            if (value)
              {
                sym_assume_symbol (table, tmp_val, value);
                mem_free (value);
              }
          }
      }
    else
      {
        symbol = sym_lookup_symbol (header, "name");
        if (symbol)
          {
            value = http_escape (data, NULL);
            if (value)
              {
                sym_assume_symbol (table, symbol-> value, value);
                mem_free (value);
              }
          }
      }
}


/*  -------------------------------------------------------------------------
    Function: multipart_decode_header

    Synopsis: Decode mime header of a part.
    -------------------------------------------------------------------------*/

static void
multipart_decode_header (char *header, SYMTAB *table)
{
    char
        *p,
        *variable,
        *value = "";

    ASSERT (header);
    ASSERT (table);

    p        = header;
    variable = header;
    while (*p)
      {
        if ((*p == ':' && *(p + 1) == ' ')
        ||   *p == '=')
          {
            *p++ = '\0';
            if (*p == ' ' || *p == '"')
                p++;
            value = p;
          }
        else
        if (*p == ';' || *p == '\r'||  *p == '\n')
          {
            if (*(p - 1) == '"')
                *(p - 1) = '\0';
            else
                *p = '\0';
            http_unescape (value, NULL);
            sym_assume_symbol (table, variable, value);
            p++;
            while (*p == ' ' || *p == '\r' || *p == '\n')
                p++;
            variable = p;
          }
        p++;
      }
    if (p != header && *(p - 1) == '"')
        *(p - 1) = '\0';
    http_unescape (value, NULL);
    sym_assume_symbol (table, variable, value);
}


/*  ---------------------------------------------------------------------[<]-
    Function: is_full_url

    Synopsis: If the specified URI string starts with a URL scheme, returns
    TRUE, else returns FALSE.  A schema is one or more of [A-Za-z0-9+-.]
    followed by a ':'.
    ---------------------------------------------------------------------[>]-*/

Bool
is_full_url (const char *string)
{
    Bool
        scheme_size = 0;

    ASSERT (string);
    while (*string)
      {
        if (isalpha (*string)
        ||  isdigit (*string)
        ||  *string == '+'
        ||  *string == '-'
        ||  *string == '.')
            scheme_size++;              /*  So far, a valid scheme name      */
        else
        if (*string == ':')
            return (scheme_size > 0);   /*  Okay if ':' was not first char   */
        else
            return (FALSE);             /*  No scheme name found             */
        string++;
      }
    return (FALSE);                     /*  End of string but no scheme      */
}


/*  ---------------------------------------------------------------------[<]-
    Function: build_full_url

    Synopsis: If the specified URI string does not start with a URL schema
    or a directory delimiter, we add the path of the base URI, and return
    the resulting full URI.  This is provided as a freshly-allocated string
    which the caller must free using mem_free() when finished.  If the
    specified URI is already a full URI, returns a fresh copy of that URI.
    ---------------------------------------------------------------------[>]-*/

char *
build_full_url (const char *uri, const char *base_uri)
{
    char
        *full_uri,                      /*  Formatted full URI               */
        *slash;                         /*  Find delimiter in path           */
    int
        base_len;                       /*  Length of base part of URI       */

    if (is_full_url (uri) || uri [0] == '/')
        return (mem_strdup (uri));
    else
      {
        /*  Find last slash in base URI                                      */
        slash = strrchr (base_uri, '/');
        if (slash)
          {
            base_len = ++slash - base_uri;
            full_uri = mem_alloc (base_len + strlen (uri) + 1);
            memcpy (full_uri, base_uri, base_len);
            strcpy (full_uri + base_len, uri);
          }
        else
            full_uri = xstrcpy (NULL, "/", uri, NULL);

        return (full_uri);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_time_string

    Synopsis: Returns the current date and time formatted using the HTTP
    standard format for log files: "DD/Mon/YYYY:hh:mm:ss".  The formatted
    time is in a static string that each call overwrites.
    ---------------------------------------------------------------------[>]-*/

char *
http_time_str (void)
{
    static char
        formatted_time [30],
        *months = "Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec";
    time_t
        time_secs;
    struct tm
        *time_struct;

    time_secs   = time (NULL);
    time_struct = localtime (&time_secs);

    sprintf (formatted_time, "%02d/%s/%04d:%02d:%02d:%02d %s",
                              time_struct-> tm_mday,
                              months + time_struct-> tm_mon * 4,
                              time_struct-> tm_year + 1900,
                              time_struct-> tm_hour,
                              time_struct-> tm_min,
                              time_struct-> tm_sec,
                              timezone_string ());
    return (formatted_time);
}


/*  ---------------------------------------------------------------------[<]-
    Function: cgi_get_input

    Synopsis: Gets CGI data input from stdin or the enviorment vairable
    QUERY_STRING,  to form a stream to be used by cgi_fld_by_name,
    cgi_fld_by_index and cgi_fld_len_by_index functions.  After you
    have finshed with the input stream from this function you should call,
    cgi_free_input to free it up.

    Submitted by Scott Beasley <jscottb@infoave.com>
    ---------------------------------------------------------------------[>]-*/

char *
cgi_get_input (
    int iMethod)
{
    int iStdinLen = 0, iMethodWas = 0;
    char *strHead, *strRetBuf;

    if (iMethod == CGIPOST
    ||  iMethod == CGIETHER)
      {
        if (getenv ("CONTENT_LENGTH"))
          {
            iStdinLen = atoi (getenv ("CONTENT_LENGTH"));
            iMethodWas = 1;
          }
      }
    if (iMethod == CGIGET
    || (iMethod == CGIETHER && !iStdinLen))
      {
        if (getenv ("QUERY_STRING"))
          {
            iStdinLen = strlen (getenv ("QUERY_STRING"));
            iMethodWas = 0;
          }
      }
    if (!iStdinLen)
        return (NULL);

    strHead = strRetBuf = (char *) malloc (sizeof (char) *
                                           iStdinLen + 1);
    if (strHead == NULL)
        return (NULL);

    memset (strRetBuf, 0, iStdinLen + 1);
    if (iMethodWas == CGIPOST)
        fread (strRetBuf, sizeof (char), iStdinLen, stdin);
    else
        strcpy (strRetBuf, getenv ("QUERY_STRING"));

    return (*strHead? strHead: NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: cgi_fld_by_name

    Synopsis: Gets field data from a CGI input stream based off a HTML
    form field name.  This function returns the value of the form field.

    example:

      Form snippet:
         Product <INPUT TYPE="text" NAME="SENDERID" SIZE=80 VALUE="mailto">
         Version <INPUT TYPE="text" NAME="VERSION" SIZE=80 VALUE="v1.4">
         E-mail  <INPUT TYPE="text" NAME="Email" SIZE=80>

      CGI code to get form field:
         cgi_fld_by_name ("VERSION", strStdin, strVersion);

      On return from the call:
         strVersion would = "VERSION"

    Submitted by Scott Beasley <jscottb@infoave.com>
    ---------------------------------------------------------------------[>]-*/

char *
cgi_fld_by_name (
    char *strFld,
    char *strIn,
    char *strRetBuf)
{
    int iCnt = 0, iLen;
    char *strTmp;

    ASSERT (strFld);
    ASSERT (strIn);

    trim (strFld);
    *strRetBuf = (char) NULL;
    FOREVER
      {
        iLen = getstrfldlen (strIn, iCnt, 0, "&");
        if (!iLen)
            break;

        strTmp = (char *) malloc (sizeof (char) * iLen + 1);
        getstrfld (strIn, iCnt++, 0, "&", strTmp);
        if (!lexncmp (strFld, strTmp, strlen (strFld)))
          {
            getequval (strTmp, strRetBuf);
            http_unescape (strRetBuf, NULL);
          }
        if (strTmp)
            free (strTmp);
        strTmp = NULL;
      }
    return strRetBuf;
}

/*  ---------------------------------------------------------------------[<]-
    Function: cgi_fld_by_index

    Synopsis: Gets field data from a CGI input stream based off a field
    index.  The index is from 0 to n.  Where 0 would be the first field
    in the stream, and n would be the last.  This function returns the
    HTML form field name and the value of the field.

    example:

      Form snippet:
         Product <INPUT TYPE="text" NAME="SENDERID" SIZE=80 VALUE="mailto">
         Version <INPUT TYPE="text" NAME="VERSION" SIZE=80 VALUE="v1.4">
         E-mail  <INPUT TYPE="text" NAME="Email" SIZE=80>

      CGI code to get form field:
         cgi_fld_by_index (1, strStdin, strFldValue, strFldName);

      On return from the call:
         strFldValue would = "v1.4"
         and would strFldName be = "VERSION"

    Submitted by Scott Beasley <jscottb@infoave.com>
    ---------------------------------------------------------------------[>]-*/

char *
cgi_fld_by_index (
    int iPos,
    char *strIn,
    char *strRetBuf,
    char *strFldName)
{
    int iLen;
    char *strTmp;

    ASSERT (strIn);

    *strRetBuf = (char) NULL;
    iLen = getstrfldlen (strIn, iPos, 0, "&");
    if (iLen)
      {
        strTmp = (char *) malloc (sizeof (char) * iLen + 1);

        getstrfld (strIn, iPos, 0, "&", strTmp);
        getequval (strTmp, strRetBuf);
        http_unescape (strRetBuf, NULL);
        if (strFldName)
            getstrfld (strTmp, 0, 0, "=", strFldName);

        free (strTmp);
      }
    return strRetBuf;
}

/*  ---------------------------------------------------------------------[<]-
    Function: cgi_fld_len_by_index

    Synopsis: Gets the length of the field data from a CGI input stream
    based off a field index.  The index is from 0 to n.  Where 0 would
    be the first field in the stream, and n would be the last.

    example:

      Form snippet:
         Product <INPUT TYPE="text" NAME="SENDERID" SIZE=80 VALUE="mailto">
         Version <INPUT TYPE="text" NAME="VERSION" SIZE=80 VALUE="v1.4">
         E-mail  <INPUT TYPE="text" NAME="Email" SIZE=80>

      CGI code to get form field:
         cgi_fld_len_by_index (1, strStdin, &iDataLen, &iNameLen);

      On return from the call:
         iDataLen would = 4
         and iNameLen would be = 7

    Submitted by Scott Beasley <jscottb@infoave.com>
    ---------------------------------------------------------------------[>]-*/

int
cgi_fld_len_by_index (
    int iPos,
    char *strIn,
    int *iDataLen,
    int *iNameLen)
{
    int iLen;
    char *strTmp;

    ASSERT (strIn);

    iLen = getstrfldlen (strIn, iPos, 0, "&");

    if (iLen)
      {
        strTmp = (char *) malloc (sizeof (char) * iLen + 1);

        getstrfld (strIn, iPos, 0, "&", strTmp);
        http_unescape (strTmp, NULL);
        iLen = getstrfldlen (strTmp, 1, 0, "=");
        if (iDataLen)
            *iDataLen = iLen;

        if (iNameLen)
            *iNameLen = getstrfldlen (strTmp, 0, 0, "=");

        free (strTmp);
      }

    return iLen;
}

/*  ---------------------------------------------------------------------[<]-
    Function: displayform

    Synopsis: Writes a HTML file out to the web browser or another file.
    Gives the option to have replaceable parameters in your HTML.

    Form snippet:
       Product <INPUT TYPE="text" NAME="SENDERID" SIZE=80 VALUE="%PRONAME%">
       Version <INPUT TYPE="text" NAME="TOIDS" SIZE=80 VALUE="%PROVER%">
       E-mail  <INPUT TYPE="text" NAME="Email" SIZE=80>

    This would/could be a string you build at runtime:
      char *strformparms = "%PRONAME%|mailto,%PROVER%|v1.4";
      char *strfilename = The full path to the HTML file to display.

    This will read the file and do any string replaces it needs to
    and then send it out to the browser, or file with the changes.
      displayform (strfilename, strformparms);

    Submitted by Scott Beasley <jscottb@infoave.com>
    ---------------------------------------------------------------------[>]-*/

int
displayform (
    char *strformfile,
    char *strvalues)
{
    FILE *fp;
    char strline[1025];

    ASSERT (strformfile);

    fp = fopen (strformfile, "r");
    if (!fp)
        return 1;

    while (!feof (fp))
      {
        fgets (strline, 1024, fp);
        strcrop (strline);
        if (*strvalues)
            stringreplace (strline, strvalues);
        puts (strline);
      }

    fclose (fp);
    return 0;
}

