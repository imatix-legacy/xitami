/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflini.c
    Title:      Initialisation file access functions
    Package:    Standard Function Library (SFL)

    Written:    94/01/18  iMatix SFL project team <sfl@imatix.com>
    Revised:    98/12/10

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
#include "sflsymb.h"                    /*  Symbol table functions           */
#include "sflenv.h"                     /*  Environment access functions     */
#include "sfltok.h"                     /*  Token-handling functions         */
#include "sfldate.h"                    /*  Date and time functions          */
#include "sfltron.h"                    /*  Trace functions                  */
#include "sflini.h"                     /*  Prototypes for functions         */


/*  Static variables used globally in this source file only                  */

static char
    iniline     [LINE_MAX + 1],         /*  Line from ini file               */
    ini_section [LINE_MAX + 1],         /*  Match [section name]             */
    ini_keyword [LINE_MAX + 1],         /*  Match keyword =                  */
    ini_value   [LINE_MAX + 1];         /*  Match = value                    */


/*  ---------------------------------------------------------------------[<]-
    Function: ini_find_section

    Synopsis:
    Finds a specific section in the ini file.  An ini file contains lines
    as shown below.  The section name can be any mix of upper or lowercase.
    You should open the ini file using file_open before you call this
    function.  If the 'top' argument is TRUE, repositions to the start
    of the file before reading, else reads from the current file offset.
    Returns TRUE if the section was found, and positions on the line that
    follows the section.  Returns FALSE if the section was not found, and
    positions at the end of the file.

    Examples:
    ;   comments like this, or
    #   comments like this if you prefer
    !   Text is echoed to console using trace()
    [Section]
        keyword = key_value; comments
        keyword = "key_value"; comments
        keyword = 'key_value'; comments
        ...
    [Section]
        keyword = key_value; comments
        ...
    ---------------------------------------------------------------------[>]-*/

Bool
ini_find_section (
    FILE *inifile,
    char *section,
    Bool top)
{
    char
        *first;

    ASSERT (inifile != NULL);
    ASSERT (section != NULL);

    if (top)                            /*  Reposition at top if wanted      */
        fseek (inifile, 0, SEEK_SET);

    /*  Read through file until we find what we are looking for              */
    while (file_read (inifile, iniline))
      {
        first = strskp (iniline);       /*  Skip leading spaces              */
        if (*first == ';' || *first == '#' || *first == 0)
            continue;                   /*  Comment line                     */
        else
        if (*first == '!')
          {
            first = strskp (first + 1);
            trace (first);
          }
        else
        if (sscanf (first, "[%[^]]", ini_section) == 1
        &&  lexcmp (ini_section, section) == 0)
            return (TRUE);
      }
    return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ini_scan_section

    Synopsis:
    Scans the current section of the ini file, and returns a keyword and
    value if such was found.  Returns the address of these values in the
    supplied arguments.  The addresses point to static values that are
    overwritten with each call.  Returns TRUE when a keyword/value pair
    is found.  Returns FALSE if a new section name or end of file is found.
    In the first case, sets the keyword to the section name; in the second
    case sets the keyword to NULL.  Ignores blank and comment lines, and
    lines that look like junk.  Keyword and section names are returned as
    lower-case; values are returned exactly as specified in the ini file.
    ---------------------------------------------------------------------[>]-*/

Bool
ini_scan_section (
    FILE *inifile,
    char **keyword,
    char **value)
{
    char
        *first;

    /*  Read through file until we find what we are looking for              */
    while (file_read (inifile, iniline))
      {
        first = strskp (iniline);       /*  Skip leading spaces              */
        if (*first == ';' || *first == '#' || *first == 0)
            continue;                   /*  Comment line                     */
        else
        if (*first == '!')
          {
            first = strskp (first + 1);
            trace (first);
          }
        else
        if (sscanf (first, "[%[^]]", ini_section) == 1)
          {
            *keyword = strlwc (ini_section);
            *value   = NULL;
            return (FALSE);             /*  New section name                 */
          }
        else
        if (streq (first, "[]"))        /*  Allow empty section names        */
          {
            strcpy (ini_section, "");
            *keyword = ini_section;
            *value   = NULL;
            return (FALSE);             /*  New section name                 */
          }
        else
        if (sscanf (first, "%[^=] = \"%[^\"]\"", ini_keyword, ini_value) == 2
        ||  sscanf (first, "%[^=] = '%[^\']'",   ini_keyword, ini_value) == 2
        ||  sscanf (first, "%[^=] = %[^;#]",     ini_keyword, ini_value) == 2)
          {
            strcrop (strlwc (ini_keyword));
            strcrop (ini_value);
            /*  sscanf can't handle "" or '' as an empty value, so we do this
             *  ourselves.  Note that this breaks '""' and "''".  :-(
             */
            if (streq (ini_value, "\"\"")
            ||  streq (ini_value, "''"))
                strclr (ini_value);

            *keyword = ini_keyword;
            *value   = ini_value;
            return (TRUE);              /*  Found keyword = value            */
          }
      }
    *keyword = NULL;
    return (FALSE);                     /*  End of file                      */
}


/*  ---------------------------------------------------------------------[<]-
    Function: ini_dyn_load

    Synopsis: Loads the contents of an .ini file into a symbol table.  If
    no symbol table is specified, creates a new symbol table.  The ini file
    data is loaded as a set of symbols and values, where the symbol name is
    built from the section name and keyword like this: "section:keyword".
    The symbol name is always stored in lowercase, with no trailing spaces.
    If the same keyword occurs several times in a section, earlier symbols
    are overwritten.  Ignores all comments and blank lines.  Returns NULL
    if there is not enough memory.  Stores these control variables in the
    symbol table if the table was freshly created or the file was loaded:
    <TABLE>
    filename        Name of input file
    filetime        Time of input file, as 8-digit string "HHMMSSCC"
    filedate        Date of input file, as 8-digit string "YYYYMMDD"
    </TABLE>
    Also creates a symbol for each section, with name equal to the section
    name, and value equal to an empty string.  Looks for the .ini file on
    the current PATH.  The table is sorted after loading.
    ---------------------------------------------------------------------[>]-*/

SYMTAB *
ini_dyn_load (
    SYMTAB *load_symtab,
    const char *filename)
{
    FILE
        *inifile;
    SYMTAB
        *symtab,                        /*  Symbol table to populate         */
        *envtab;                        /*  Environment, as symbol table     */
    char
        *section = NULL,                /*  Filled as we scan through        */
        *keyword = NULL,                /*    the ini file                   */
        *value   = NULL,
        *section_end;                   /*  Null byte at end of section      */

    ASSERT (filename);
    inifile = file_locate ("PATH", filename, NULL);

    if (load_symtab)                    /*  Use specified symbol table       */
        symtab = load_symtab;           /*    or create a new one            */
    else
      {
        symtab = sym_create_table ();
        if (symtab == NULL)
            return (NULL);              /*  Quit if insufficient memory      */
      }
    /*  Store control variables in symbol table                              */
    if (inifile || load_symtab == NULL)
      {
        sym_assume_symbol (symtab, "filename", filename);
        sprintf (iniline, "%ld", timer_to_date (get_file_time (filename)));
        sym_assume_symbol (symtab, "filedate", iniline);
        sprintf (iniline, "%ld", timer_to_time (get_file_time (filename)));
        sym_assume_symbol (symtab, "filetime", iniline);
      }
    if (!inifile)
        return (symtab);                /*  File not found; empty table      */

    /*  Now load the ini file, starting from the beginning                   */
    envtab = env2symb ();
    fseek (inifile, 0, SEEK_SET);
    FOREVER
      {
        if (ini_scan_section (inifile, &keyword, &value))
          {
            if (section)
              {
                section_end = strchr (section, '\0');
                ASSERT (section_end);
                xstrcat (section, ":", keyword, NULL);
                value = tok_subst (value, envtab);
                sym_assume_symbol (symtab, section, value);
                mem_strfree (&value);
                *section_end = '\0';
              }
          }
        else
        if (keyword)                    /*  Found new section                */
          {
            section = keyword;
            sym_assume_symbol (symtab, section, "");
          }
        else
            break;
      }
    file_close (inifile);
    sym_delete_table (envtab);
    sym_sort_table (symtab, NULL);      /*  Sort table by symbol name        */
    return (symtab);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ini_dyn_loade

    Synopsis: Loads the contents of an .ini file into a symbol table, as
    for ini_dyn_load(), but requires that the .ini file exists.  Returns
    a loaded symbol table if the file was present, and NULL otherwise.
    ---------------------------------------------------------------------[>]-*/

SYMTAB *
ini_dyn_loade (
    SYMTAB *load_symtab,
    const char *filename)
{
    ASSERT (filename);
    if (file_locate ("PATH", filename, NULL))
        return (ini_dyn_load (load_symtab, filename));
    else
        return (NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ini_dyn_save

    Synopsis: Saves a symbol table to the specified file.  The symbol table
    entries must be formatted as "section:name=value" - see ini_dyn_load().
    Scans the ini file for a line containing only "#*END", then writes the
    symbol data to the file from that point.  Returns the number of symbols
    saved, or -1 if there was an error.  As a side-effect, sorts the table
    on the symbol name.
    ---------------------------------------------------------------------[>]-*/

int
ini_dyn_save (
    SYMTAB *symtab,
    const char *filename)
{
    FILE
        *inifile,
        *wrkfile;
    SYMBOL
        *symbol;                        /*  Next symbol in table             */
    Bool
        header_found;                   /*  Did we find a file header?       */
    int
        count;                          /*  How many symbols did we save?    */
    char
        *colon;                         /*  Points to ':' in symbol name     */

    ASSERT (filename);
    ASSERT (symtab);

    /*  Copy ini file header to temporary file                               */
    wrkfile = tmpfile ();
    header_found = FALSE;
    if ((inifile = file_open (filename, 'r')) != NULL)
      {
        while (file_read (inifile, iniline))
          {
            if (streq (iniline, "#*END"))
              {
                header_found = TRUE;
                break;
              }
            file_write (wrkfile, iniline);
          }
        file_close (inifile);
      }
    /*  Now rewrite ini file                                                 */
    if ((inifile = file_open (filename, 'w')) == NULL)
      {
        fclose (wrkfile);
        return (-1);                    /*  No permission to write file      */
      }
    if (header_found)
      {
        fseek (wrkfile, 0, SEEK_SET);
        while (file_read (wrkfile, iniline))
            file_write (inifile, iniline);
      }
    file_close (wrkfile);               /*  Finished with temporary file     */

    /*  Output ini file values                                               */
    file_write (inifile, "#*END");
    strclr (ini_section);               /*  Current section                  */
    count = 0;

    sym_sort_table (symtab, NULL);      /*  Sort table by symbol name        */
    for (symbol = symtab-> symbols; symbol; symbol = symbol-> next)
      {
        /*  Output symbols formatted as key:name                             */
        colon = strrchr (symbol-> name, ':');
        if (colon)
          {
            memcpy (ini_value, symbol-> name, colon - symbol-> name);
            ini_value [colon - symbol-> name] = '\0';
            strcpy (ini_keyword, colon + 1);

            /*  If we start a new section, output the section header         */
            *ini_value   = toupper (*ini_value);
            *ini_keyword = toupper (*ini_keyword);
            if (strneq (ini_section, ini_value))
              {
                strcpy (ini_section, ini_value);
                sprintf (iniline, "[%s]", ini_section);
                file_write (inifile, "");
                file_write (inifile, iniline);
              }
            if (strnull (symbol-> value))
                sprintf (iniline, "    %s=\"\"", ini_keyword);
            else
            if (strpbrk (symbol-> value, ";#="))
                sprintf (iniline, "    %s=\"%s\"", ini_keyword, symbol-> value);
            else
                sprintf (iniline, "    %s=%s", ini_keyword, symbol-> value);
            file_write (inifile, iniline);
          }
      }
    file_close (inifile);
    return (count);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ini_dyn_changed

    Synopsis: Returns TRUE if the ini file loaded into the specified table
    has in the meantime been changed.  Returns FALSE if not.
    ---------------------------------------------------------------------[>]-*/

Bool
ini_dyn_changed (
    SYMTAB *symtab)
{
    char
        *filename;

    ASSERT (symtab);

    /*  Date, time, and name of original ini file are in the table           */
    filename = sym_get_value (symtab, "filename", NULL);
    if (filename
    &&  file_has_changed (filename,
                          sym_get_number (symtab, "filedate", 0),
                          sym_get_number (symtab, "filetime", 0)))
        return (TRUE);
    else
        return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ini_dyn_refresh

    Synopsis: Refreshes a symbol table created by ini_dyn_load().  If the
    original file (as specified by the 'filename' symbol) has been modified,
    reloads the whole ini file.  You would typically call this function at
    regular intervals to permit automatic reloading of an ini file in an
    application.  Returns TRUE if the ini file was actually reloaded, or
    FALSE if the file had not changed or could not be accessed, or if the
    symbol table was incorrectly created.  If the symbol table is reloaded
    from the ini file, all previous symbols are deleted.
    ---------------------------------------------------------------------[>]-*/

Bool
ini_dyn_refresh (
    SYMTAB *symtab)
{
    char
        *filename;

    ASSERT (symtab);
    if (ini_dyn_changed (symtab))
      {
        filename = mem_strdup (sym_get_value (symtab, "filename", NULL));
        sym_empty_table (symtab);       /*  Delete previous table contents   */
        ini_dyn_load (symtab, filename);
        mem_free (filename);
        return (TRUE);
      }
    return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ini_dyn_value

    Synopsis: Finds a section:keyword in the symbol table and returns a
    pointer to its value.  Returns the default value if the symbol is not
    defined in the table.  The default value may be NULL.  The specified
    section and keyword can be in any case; they are converted internally
    to lowercase to match the symbol table.  If the keyword is empty or
    NULL, no ':keyword' is appended to the section name.
    ---------------------------------------------------------------------[>]-*/

char *
ini_dyn_value (
    SYMTAB *symtab,
    const char *section,
    const char *keyword,
    const char *default_value)
{
    ASSERT (section);
    if (keyword && *keyword)
        sprintf (ini_keyword, "%s:%s", section, keyword);
    else
        strcpy  (ini_keyword, section);

    strlwc (ini_keyword);
    return (sym_get_value (symtab, ini_keyword, default_value));
}


/*  ---------------------------------------------------------------------[<]-
    Function: ini_dyn_values

    Synopsis: Finds a section:keyword in the symbol table and returns a
    pointer to a string table containing the values, delimited by commas.
    When finished with the string table you should call tok_free() to free
    the memory allocated for it.  The default value may not be NULL.
    Returns a pointer to a table of string tokens (see tok_split()), or
    NULL if there was insufficient memory.  The specified section and keyword
    can be in any case; they are converted internally to lowercase to match
    the symbol table.  If the keyword is empty or NULL, no ':keyword' is
    appended to the section name.
    ---------------------------------------------------------------------[>]-*/

char **
ini_dyn_values (
    SYMTAB *symtab,
    const char *section,
    const char *keyword,
    const char *default_value)
{
    ASSERT (section);
    ASSERT (default_value);

    if (keyword && *keyword)
        sprintf (ini_keyword, "%s:%s", section, keyword);
    else
        strcpy  (ini_keyword, section);

    strlwc (ini_keyword);
    strcpy (iniline, sym_get_value (symtab, ini_keyword, default_value));
    strconvch (iniline, ',', ' ');
    return (tok_split (iniline));
}
