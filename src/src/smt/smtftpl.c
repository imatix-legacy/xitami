/*  ----------------------------------------------------------------<Prolog>-
    Name:       smtftpl.c
    Title:      File Transfer Protocol functions
    Package:    Libero SMT 2.x

    Written:    96/08/20  iMatix SMT kernel team <smt@imatix.com>
    Revised:    99/06/23

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"                        /*  SFL library header file          */
#include "smthttpl.h"

#define  DEFINE_FTP_TABLES
#include "smtftpl.h"

/*  These limits are a rough way of ensuring that user-defined messages      */
/*  do not exceed the size of the header buffer (4096).  Anyhow, any         */
/*  message should not be more than a screenful of text.                     */

#define MESSAGE_MAX      2000           /*  Max. size of message text        */
#define USERNAME_MAX     50             /*  Max. size of a user name         */

#define FTPCONFIG(s)     http_config   (p_ftpc-> config, (s))
#define USRCONFIG(s,d)   ini_dyn_value (p_ftpc-> users, p_ftpc-> user,(s),(d))


static dbyte
    access_table [256];
#define BUFFER_SIZE      1024
static char
    work_buffer [BUFFER_SIZE + 1];      /*  For various short strings        */


/*  Internal functions ----------------------------------------------------- */

static void  format_welcome_text   (FTP_CONTROL_CTX *p_ftpc, char *buffer,
                                    char *option, char *last_line);
static void  check_quotas          (FTP_CONTROL_CTX *p_ftpc, char *buffer);
static qbyte quota_value           (FTP_CONTROL_CTX *p_ftpc, char *key);
static void  format_dir_for_alias  (FTP_CONTROL_CTX *p_ftpc, NODE *file_list,
                                    char *alias, char *mask);
static Bool  ftp_path_protected    (SYMTAB *passwd, char *file, char *user);


/*  ---------------------------------------------------------------------[<]-
    Function: ftp_initialise

    Synopsis: Initialises the FTP library.
    ---------------------------------------------------------------------[>]-*/

void
ftp_initialise (void)
{
    memset (access_table, 0, sizeof (access_table));
    access_table ['G'] = FTP_AUTH_GET;
    access_table ['g'] = FTP_AUTH_GET;
    access_table ['P'] = FTP_AUTH_PUT;
    access_table ['p'] = FTP_AUTH_PUT;
    access_table ['S'] = FTP_AUTH_PUT;  /*  Used to be 'STORE'               */
    access_table ['s'] = FTP_AUTH_PUT;
    access_table ['D'] = FTP_AUTH_DELETE;
    access_table ['d'] = FTP_AUTH_DELETE;
    access_table ['M'] = FTP_AUTH_MKDIR;
    access_table ['m'] = FTP_AUTH_MKDIR;
    access_table ['R'] = FTP_AUTH_RMDIR;
    access_table ['r'] = FTP_AUTH_RMDIR;
    access_table ['U'] = FTP_AUTH_UPLOAD;
    access_table ['u'] = FTP_AUTH_UPLOAD;
    access_table ['*'] = FTP_AUTH_ALL;
}


/*###########################################################################
  #                                                                         #
  #                           FTP CONTROL FUNCTIONS                         #
  #                                                                         #
  ###########################################################################*/

/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_init_connection

    Synopsis: Initialises the FTP connection.
    ---------------------------------------------------------------------[>]-*/

void
ftpc_init_connection (FTP_CONTROL_CTX *p_ftpc, sock_t handle)
{
    p_ftpc-> user        = NULL;
    p_ftpc-> password    = NULL;
    p_ftpc-> guestname   = NULL;
    p_ftpc-> user_root   = NULL;
    p_ftpc-> real_root   = NULL;
    p_ftpc-> cur_dir     = NULL;
    p_ftpc-> last_file   = NULL;
    p_ftpc-> file_name   = NULL;
    p_ftpc-> parameters  = NULL;
    p_ftpc-> aliases     = FALSE;
    p_ftpc-> login       = FALSE;
    p_ftpc-> passive     = FALSE;
    p_ftpc-> temp_file   = FALSE;
    p_ftpc-> use_quotas  = FALSE;
    p_ftpc-> cur_usage   = 0;
    p_ftpc-> soft_quota  = 0;
    p_ftpc-> hard_quota  = 0;
    p_ftpc-> file_type   = FTP_TYPE_ASCII;
    p_ftpc-> file_size   = 0;
    p_ftpc-> file_offset = 0;
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_free_connection

    Synopsis: Free memory allocated for ftp control context
    ---------------------------------------------------------------------[>]-*/

void
ftpc_free_connection (FTP_CONTROL_CTX *p_ftpc)
{
    mem_strfree (&p_ftpc-> file_name);
    mem_strfree (&p_ftpc-> cur_dir);
    mem_strfree (&p_ftpc-> real_root);
    mem_strfree (&p_ftpc-> user_root);
    mem_strfree (&p_ftpc-> user);
    mem_strfree (&p_ftpc-> password);
    mem_strfree (&p_ftpc-> guestname);
    mem_strfree (&p_ftpc-> last_file);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_get_user

    Synopsis: Stores user name in p_ftpc-> user string.  Returns FALSE if
    there was a fatal error.  We don't care whether the user name is in the
    authorisation file or not, since that's checked when we receive the
    password.  User name is limited and truncated to USERNAME_MAX characters
    and always stored in lowercase.
    ---------------------------------------------------------------------[>]-*/

Bool
ftpc_get_user (FTP_CONTROL_CTX *p_ftpc)
{
    if (p_ftpc-> parameters && p_ftpc-> users)
      {
        /*  Protect against over-long parameters                             */
        if (strlen (p_ftpc-> parameters) > USERNAME_MAX)
            p_ftpc-> parameters [USERNAME_MAX] = '\0';

        strlwc (p_ftpc-> parameters);
        mem_strfree (&p_ftpc-> user);
        p_ftpc-> user = mem_strdup (p_ftpc-> parameters);
        p_ftpc-> return_code = FTP_RC_USER_NAME_OK;
        return (TRUE);
      }
    else                                /*  Information is missing           */
      {
        p_ftpc-> return_code = FTP_RC_SYNTAX_ERROR_PARAM;
        return (FALSE);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_get_password

    Synopsis: Get password from user configuration file, which is "-" by
    default.  Sets p_ftpc-> password to point to the password.  Returns
    FALSE if no user is logged-in.
    ---------------------------------------------------------------------[>]-*/

Bool
ftpc_get_password (FTP_CONTROL_CTX *p_ftpc)
{
    if (p_ftpc-> user)
      {
        mem_strfree (&p_ftpc-> password);
        p_ftpc-> password = mem_strdup (USRCONFIG ("password", "-"));
        return (TRUE);
      }
    else
        return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_verify_password

    Synopsis: Verifies the user password.  If it is "-", the login is always
    rejected.  If it's "*" the login is accepted (the password must be a
    valid email address if ftp:check_email is set).  Otherwise the password
    must match.
    ---------------------------------------------------------------------[>]-*/

Bool
ftpc_verify_password (FTP_CONTROL_CTX *p_ftpc)
{
    char
        *challenge,                     /*  Required password                */
        *response;                      /*  What the user supplied           */

    challenge = p_ftpc-> password;
    response  = p_ftpc-> parameters;

    if (challenge && response)
      {
        /*  Challenge should not be empty, but we'll treat that as "-"       */
        if (streq (challenge, "-") || strnull (challenge))
            p_ftpc-> login = FALSE;
        else
        if (streq (challenge, "*"))
          {
            if (*FTPCONFIG ("ftp:check-email") == '0'
            || strchr (response, '@'))
              {
                p_ftpc-> login     = TRUE;
                p_ftpc-> guestname = mem_strdup (response);
              }
          }
        else
          {
            /*  If password case not sensitive, compare as lower-case        */
            if (*(FTPCONFIG ("ftp:password-case")) == '0')
                strlwc (response);
            p_ftpc-> login = streq (challenge, response);
          }
      }
    else
        p_ftpc-> login = FALSE;

    if (p_ftpc-> login)
        p_ftpc-> return_code = FTP_RC_USER_LOGGED;
    else
        p_ftpc-> return_code = FTP_RC_LOGIN_FAILED;

    return (p_ftpc-> login);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_get_rootdir

    Synopsis: Get the root directory for the user.  This comes from the user
    definition file.  The default root is "".  The user's root directory may
    be an absolute directory or relative to the FTP root directory.
    The user's current directory is set to "/" (the user's initial root).
    The aliases flag is set according to the users aliases option.
    ---------------------------------------------------------------------[>]-*/

void
ftpc_get_rootdir (FTP_CONTROL_CTX *p_ftpc, char *rootdir)
{
    char
        *def_aliases,
        *cur_root;

    cur_root = USRCONFIG ("root", "");

    /*  Store physical root directory                                        */
    mem_strfree (&p_ftpc-> real_root);
    p_ftpc-> real_root = mem_strdup (locate_path (rootdir, cur_root));

    /*  Store user's root directory, within the FTP root directory           */
    mem_strfree (&p_ftpc-> user_root);
    p_ftpc-> user_root = mem_strdup (cur_root);

    /*  Check whether user can see root aliases                              */
    def_aliases = strnull (p_ftpc-> user_root)? "1": "0";
    p_ftpc-> aliases = *USRCONFIG ("aliases", def_aliases) == '1';

    /*  Initialise the current directory to be "/"                           */
    mem_strfree (&p_ftpc-> cur_dir);
    p_ftpc-> cur_dir = mem_strdup ("/");
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_get_quotas

    Synopsis: Gets the user's specified quotas.  If quotas are enabled for
    the user, calculates the actual disk space used at the moment of login.
    This is updated on the fly when files are uploaded or deleted.  The
    quota applies to the user's login directory and all child directories.
    ---------------------------------------------------------------------[>]-*/

void
ftpc_get_quotas (FTP_CONTROL_CTX *p_ftpc)
{
    p_ftpc-> use_quotas = *USRCONFIG ("use-quotas", "0") == '1';
    if (p_ftpc-> use_quotas)
      {
        /*  Get quotas as number of bytes                                    */
        p_ftpc-> soft_quota = quota_value (p_ftpc, "soft-quota");
        p_ftpc-> hard_quota = quota_value (p_ftpc, "hard-quota");
        
        /*  Hard quota must be at least as high as soft quota                */
        if (p_ftpc-> hard_quota < p_ftpc-> soft_quota)
            p_ftpc-> hard_quota = p_ftpc-> soft_quota;

        p_ftpc-> cur_usage = dir_usage (p_ftpc-> real_root, TRUE);
      }        
}


static qbyte
quota_value (FTP_CONTROL_CTX *p_ftpc, char *key)
{
    double
        quota_mbytes;
        
    quota_mbytes = atof (USRCONFIG (key, "0"));
    return ((qbyte) (quota_mbytes * 1048576));
}

        
/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_get_permissions

    Synopsis: Return access rights for the current user and filename.  Looks
    first for an entry in the direct table, for the current directory, then
    for a general entry for the user.  The filename should be relative to the
    user's root directory, if full is false, and include the root directory,
    if full is true.
    ---------------------------------------------------------------------[>]-*/

dbyte
ftpc_permissions (FTP_CONTROL_CTX *p_ftpc, char *filename, Bool full)
{
    char
        *resource,
        *resource_path,
        *permission_string = NULL;

    ASSERT (p_ftpc-> user);
    ASSERT (filename);

    /*  If filename starts with real root, remove it                         */
    if (full && strprefixed (filename, p_ftpc-> real_root))
        filename += strlen (p_ftpc-> real_root);

    /*  First look for an entry in the directory authorisation table         */
    if (*filename == '/')
        filename++;

    /*  Build filename from user_root plus / plus filename                   */
    if (strnull (p_ftpc-> user_root))
      {
        xstrcpy_debug ();
        resource = xstrcpy (NULL, filename, NULL);
      }
    else
    if (strnull (filename))
      {
        xstrcpy_debug ();
        resource = xstrcpy (NULL, p_ftpc-> user_root, NULL);
      }
    else
    if (strlast (p_ftpc-> user_root) == '/')
      {
        xstrcpy_debug ();
        resource = xstrcpy (NULL, p_ftpc-> user_root, filename, NULL);
      }
    else
      {
        xstrcpy_debug ();
        resource = xstrcpy (NULL, p_ftpc-> user_root, "/", filename, NULL);
      }
    resource_path = resolve_path (resource);
    mem_free (resource);

    /*  If we have the same filename as last time, use cached permissions    */
    if (p_ftpc-> last_file && streq (p_ftpc-> last_file, resource_path))
        return (p_ftpc-> last_permissions);
    else
      {
        mem_strfree (&p_ftpc-> last_file);
        p_ftpc-> last_file = mem_strdup (resource_path);
      }

    if (ftp_path_protected (p_ftpc-> direct, resource_path, p_ftpc-> user))
        permission_string = ini_dyn_value (p_ftpc-> direct, resource_path,
                                           p_ftpc-> user, NULL);

    /*  If not found, look for general permissions for the user              */
    if (!permission_string)
        permission_string = USRCONFIG ("access", "");

    trace ("FTP access: user=%s resource=%s permissions=%s",
            p_ftpc-> user, resource_path, permission_string);

    p_ftpc-> last_permissions = ftpc_access_bits (permission_string);
    return (p_ftpc-> last_permissions);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_access_bits

    Synopsis: Translates an access string into a value holding the
    FTP_AUTH_... access bits.
    ---------------------------------------------------------------------[>]-*/

dbyte
ftpc_access_bits (char *access)
{
    dbyte
        permissions = 0;

    while (*access)
        permissions |= access_table [(int) *access++];

    return (permissions);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftp_path_protected

    Synopsis: Looks for the path in the authorisation table.  The
    authorisation table always specifies a full path.  Searches for the most
    specific path first, by successively removing path segments from the
    right-hand side.  If asked to look for "/pub/mypages/file", will look
    for entries in this order:

        [/pub/mypages/file]
        [/pub/mypages]
        [/pub]
        [/]

    If asked to look for "pub/mypages/file", will look for entries in this
    order:

        [pub/mypages/file]
        [pub/mypages]
        [pub]
        []

    Returns TRUE if the path is defined in the authorisation table, and
    modifies the supplied path to match the entry keyword.  Only matches
    sections which define access for the specified user.
    ---------------------------------------------------------------------[>]-*/

static Bool
ftp_path_protected (SYMTAB *passwd, char *path, char *user)
{
    char
        *slash;                         /*  Position of last '/' in name     */

    ASSERT (passwd);
    ASSERT (path);

    strlwc (path);                      /*  All searches in lowercase        */
#if (defined (MSDOS_FILESYSTEM))
    strconvch (path, '\\', '/');        /*  Use only '/' in comparisons      */
#endif

    FOREVER
      {
        if (ini_dyn_value (passwd, path, user, NULL))
            return (TRUE);
        else
        if (streq (path, "/") || streq (path, ""))
            return (FALSE);             /*  Not found, finally               */

        /*  Cut at slash, if any                                             */
        slash = strrchr (path, '/');
        if (slash)
          {
            if (slash == path)          /*  Leave initial slash if any       */
                slash++;
            *slash = '\0';
          }
        else
            strcpy (path, "");
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_return_message

    Synopsis: Write FTP return code message
    ---------------------------------------------------------------------[>]-*/

void
ftpc_return_message (FTP_CONTROL_CTX *p_ftpc, char *buffer)
{
#   define TRACE_SIZE 100
    static char
        trace_line [TRACE_SIZE + 1];
    char
        *user_message;
    char
        *params;                        /*  Command parameters, if any       */

    ASSERT (buffer);

    /*  Protect against buffer-overflow attacks; we use the parameters in    */
    /*  various error messages, but this string is supplied by the client.   */
    params = p_ftpc-> parameters;
    if (params)
      {
        if (strlen (params) > 40)
            params [40] = '\0';
      }
    else
        params = "(none)";

    /*  Return message always starts with 3-digit code and a space           */
    sprintf (buffer, "%s ", ftp_response [p_ftpc-> return_code].code);
    switch (p_ftpc-> return_code)
      {
        case FTP_RC_SERVICE_READY:      /*  FTP server is ready for login    */
            format_welcome_text (p_ftpc, buffer, "ftp:welcome", FTP_VERSION);
            break;

        case FTP_RC_USER_LOGGED:        /*  Logged-in                        */
            xstrcpy_debug ();
            user_message = xstrcpy (NULL, "User ", p_ftpc-> user,
                                          " logged-in", NULL);
            format_welcome_text (
                p_ftpc, buffer, "ftp:login-text", user_message);
            check_quotas (p_ftpc, buffer); 
            mem_free (user_message);
            break;

        case FTP_RC_SERVICE_CLOSING:    /*  FTP connection is ending         */
            xstrcpy_debug ();
            user_message = xstrcpy (NULL, "User ", p_ftpc-> user,
                                          " signed-off", NULL);
            format_welcome_text (
                p_ftpc, buffer, "ftp:signoff", user_message);
            check_quotas (p_ftpc, buffer);
            mem_free (user_message);
            break;

        case FTP_RC_PATHNAME_CREATED:   /*  Current Directory name           */
            sprintf (buffer + 4,
                "\"%s\" is the current directory\r\n", p_ftpc-> cur_dir);
            check_quotas (p_ftpc, buffer);
            break;

        case FTP_RC_USER_NAME_OK:       /*  User name ok                     */
            if (streq (p_ftpc-> password, "*"))
                sprintf (buffer + 4,
                    "Anonymous access ok: give e-mail address as password\r\n");
            else
                sprintf (buffer + 4,
                    "Password required for user %s\r\n", p_ftpc-> user);
            break;

        case FTP_RC_LOGIN_FAILED:       /*  Could not login                  */
            sprintf (buffer + 4, "User %s cannot login\r\n", p_ftpc-> user);
            break;

        case FTP_RC_SYSTEM_NAME:        /*  Operating System Name            */
            sprintf (buffer + 4, "%s\r\n", sys_name ());
            break;

        case FTP_RC_FILE_OK:            /*  Ready to transfer file           */
            sprintf (buffer + 4, "Preparing to transfer %s file\r\n",
                p_ftpc-> file_type == FTP_TYPE_ASCII? "ASCII": "binary");
            break;

        case FTP_RC_PASSIVE_MODE:       /*  Host/port for data connection    */
            sprintf (buffer + 4,
                "Entering Passive Mode (%u,%u,%u,%u,%u,%u)\r\n",
                (unsigned int) (p_ftpc-> data_host >> 24) & 0xFF,
                (unsigned int) (p_ftpc-> data_host >> 16) & 0xFF,
                (unsigned int) (p_ftpc-> data_host >>  8) & 0xFF,
                (unsigned int) (p_ftpc-> data_host      ) & 0xFF,
                (unsigned int) (p_ftpc-> data_port >>  8) & 0xFF,
                (unsigned int) (p_ftpc-> data_port      ) & 0xFF);
            break;

        case FTP_RC_FILE_STATUS:
            sprintf (buffer + 4, "%ld\r\n", p_ftpc-> file_size);
            break;

        case FTP_RC_FILE_ACTION_PENDING:
            sprintf (buffer + 4, "Restarting from %ld\r\n",
                     p_ftpc-> file_offset);
            break;

        case FTP_RC_HELP_MESSAGE:
            strcpy (buffer, FTP_HELP_MESSAGE);
            break;

        case FTP_RC_SYNTAX_ERROR:       /*  Syntax error in command          */
            sprintf (buffer + 4, "'%s' is not a valid command\r\n",
                     params);
            break;

        case FTP_RC_COMMAND_NOT_IMPLEMENTED:
            sprintf (buffer + 4, "'%s' not implemented\r\n",
                     p_ftpc-> command);
            break;

        case FTP_RC_BAD_SEQUENCE:
            if (p_ftpc-> login)
                sprintf (buffer + 4, "'%s' not valid at this time\r\n",
                         p_ftpc-> command);
            else
                sprintf (buffer + 4, "Log-in with 'USER' first\r\n");
            break;

        case FTP_RC_FILE_NOT_FOUND:
            sprintf (buffer + 4, "%s: No such file or directory\r\n",
                     params);
            break;

        case FTP_RC_PERMISSION_DENIED:
            sprintf (buffer + 4, "%s: Permission denied\r\n",
                     params);
            break;

        case FTP_RC_COMMAND_OK:
        case FTP_RC_FILE_ACTION_OK:
            check_quotas (p_ftpc, buffer); 
            sprintf (buffer + 4, "%s\r\n",
                     ftp_response [p_ftpc-> return_code].name);
            break;

        default:
            sprintf (buffer + 4, "%s\r\n",
                     ftp_response [p_ftpc-> return_code].name);
      }
    strncpy (trace_line, buffer, TRACE_SIZE);
    trace_line [TRACE_SIZE] = '\0';
    if (strchr (trace_line, '\r'))
        *strchr (trace_line, '\r') = '\0';
    trace ("FTP reply: %s", trace_line);
}


/*  format_welcome_text -- local
 *
 *  Formats a multiline reply text.  The formatting for this reply is done
 *  to work best with web browsers.  The first line starts: "XXX- " and the
 *  following lines start: " ".  (XXX is the code is being sent, e.g. 230.)
 */

local
format_welcome_text (
    FTP_CONTROL_CTX *p_ftpc,            /*  FTP control block                */
    char *buffer,                       /*  Buffer to receive data           */
    char *option,                       /*  Config option for message        */
    char *last_line)                    /*  Appended to end of message       */
{
    int
        message_size;                   /*  Total size of message text       */
    FILE
        *message_file = NULL;           /*  Welcome message file             */
    char
        *local_filename,                /*  Message file in local dir        */
        *welcome = NULL,                /*  Welcome message option           */
        *return_code,                   /*  3-digit return code              */
        prefix [6];                     /*  Prefix for each line             */

    /*  Show custom welcome message (literal string or file)                 */
    welcome = FTPCONFIG (option);
    ASSERT (welcome);

    strclr  (buffer);
    return_code = ftp_response [p_ftpc-> return_code].code;
    sprintf (prefix, "%s- ", return_code);

    if (welcome [0] == '@')
      {
        /*  First look for file in login (current user) directory            */
        if (p_ftpc-> login)
          {
            sprintf (work_buffer, "/%s", welcome + 1);
            local_filename = ftpc_map_name (p_ftpc, work_buffer);
            if (file_exists (local_filename))
                message_file = file_open (local_filename, 'r');
            mem_strfree (&local_filename);
          }
        if (!message_file)
            message_file = file_open (welcome + 1, 'r');

        if (message_file)
          {
            message_size = 0;           /*  We allow up to MESSAGE_MAX       */
            while (file_readn (message_file, work_buffer, BUFFER_SIZE))
              {
                /*  Skip comment lines starting with '#'                     */
                if (*work_buffer == '#')
                    continue;

                xstrcat (buffer, prefix, work_buffer, "\r\n", NULL);
                strcpy (prefix, " ");
                message_size += strlen (work_buffer) + 6;
                if (message_size > MESSAGE_MAX)
                    break;              /*  We don't need to be too exact    */
              }
            file_close (message_file);
          }
      }
    else
    if (strused (welcome))
        xstrcpy (buffer, return_code, "- ", welcome, "\r\n", NULL);

    xstrcat (buffer, return_code, " ", last_line, "\r\n", NULL);
}


/*  check_quotas -- local
 *
 *  If the user is over quota, appends a message to that effect.
 */

static void 
check_quotas (FTP_CONTROL_CTX *p_ftpc, char *buffer)
{
    char
        *return_code;                   /*  3-digit return code              */

    if (p_ftpc-> use_quotas)
      {
        return_code = ftp_response [p_ftpc-> return_code].code;
        if (p_ftpc-> cur_usage > p_ftpc-> soft_quota)
            xstrcat (buffer, return_code, " ", FTP_SOFT_QUOTA, NULL);
        if (p_ftpc-> cur_usage > p_ftpc-> hard_quota)
            xstrcat (buffer, return_code, " ", FTP_HARD_QUOTA, NULL);
      }
}    

/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_set_type

    Synopsis: Set the representation type
    ---------------------------------------------------------------------[>]-*/

void
ftpc_set_type (FTP_CONTROL_CTX *p_ftpc)
{
    static struct {
        char code;
        byte type;
    } ftp_type [] = {
       { 'A', FTP_TYPE_ASCII  },        /*  ASCII type                       */
       { 'E', FTP_TYPE_EBCDIC },        /*  EBCDIC type                      */
       { 'I', FTP_TYPE_IMAGE  },        /*  Image type                       */
       { 'N', FTP_TYPE_NONPRT },        /*  Non print                        */
       { 'T', FTP_TYPE_TELNET },        /*  Telnet format                    */
       { 'C', FTP_TYPE_CAR    },        /*  Carriage control                 */
       { 'L', FTP_TYPE_LOCBYT },        /*  Local byte size                  */
    };
    dbyte
        index;

    if (p_ftpc-> parameters == NULL)
      {
        p_ftpc-> return_code = FTP_RC_SYNTAX_ERROR_PARAM;
        return;
      }
    p_ftpc-> file_type = 0;
    strupc (p_ftpc-> parameters);
    for (index = 0; index < tblsize (ftp_type); index++)
      {
        if (strchr (p_ftpc-> parameters, ftp_type [index].code))
            p_ftpc-> file_type |= ftp_type [index].type;
      }
    if (p_ftpc-> file_type == 0)
        p_ftpc-> return_code = FTP_RC_SYNTAX_ERROR_PARAM;
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_get_port

    Synopsis: Get port and host value
    ---------------------------------------------------------------------[>]-*/

void
ftpc_get_port (FTP_CONTROL_CTX *p_ftpc)
{
    static unsigned long
        h1, h2, h3, h4;
    static int
        p1, p2;

    if (p_ftpc-> parameters == NULL)
      {
        p_ftpc-> return_code = FTP_RC_SYNTAX_ERROR_PARAM;
        return;
      }
    if (sscanf (p_ftpc-> parameters, "%ld,%ld,%ld,%ld,%d,%d", &h1, &h2,
                &h3, &h4, &p1, &p2) == 6)
      {
        p_ftpc-> data_host = (h1 << 24) + (h2 << 16) + (h3 << 8) + h4;
        p_ftpc-> data_port = (p1 << 8) + p2;
      }
    else
        p_ftpc-> return_code = FTP_RC_SYNTAX_ERROR_PARAM;
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_make_listing

    Synopsis: Make directory listing in a temporary file.  Returns TRUE if
    okay, FALSE if the listing could not be made.  Adds aliases to the
    directory if we're working in the ftproot directory.
    ---------------------------------------------------------------------[>]-*/

Bool
ftpc_make_listing (FTP_CONTROL_CTX *p_ftpc, Bool full)
{
    static char
        file_name [15];                 /*  ./lsxxxxxx.ftp                   */
    static dbyte
        file_index = 0;                 /*  Counter for temporary file       */
    char
        *file_mask,                     /*  Files must match this mask       */
        *physical_dir;                  /*  Physical directory name          */
    dbyte
        permissions;                    /*  Access permissions               */
    FILE
        *output;
    NODE
        *file_list;                     /*  Directory list                   */

    FILEINFO
        *file_node;                     /*  Entry in directory list          */
    DIRST
        dirst;                          /*  Directory structure entry        */

    /*  If arguments start with '-', treat as command switches               */
    file_mask = p_ftpc-> parameters;
    if (file_mask && *file_mask == '-')
      {                                 /*  -l anywhere is 'long'            */
        if (strchr (file_mask, 'l'))
            full = TRUE;
        /*  Get what follows -l (or NULL)                                    */
        file_mask = strchr (file_mask, ' ');
      }
    /*  Parameter can be a directory name or a file pattern                  */
    if (ftpc_dir_name (p_ftpc, work_buffer))
        file_mask = NULL;               /*  By default we accept all files   */
    permissions = ftpc_permissions (p_ftpc, work_buffer, FALSE);

    /*  Initialise file list, and load it up                                 */
    file_list = mem_alloc (sizeof (NODE));
    if (!file_list)
        return (0);

    node_reset (file_list);
    physical_dir = ftpc_map_name (p_ftpc, work_buffer);
    trace ("FTP list: directory=%s permissions=%d", physical_dir, permissions);

    if ((permissions & (FTP_AUTH_GET + FTP_AUTH_PUT)) != 0)
      {
        if (open_dir (&dirst, physical_dir))
          {
            do
              {
                if ((!file_mask || file_matches (dirst.file_name, file_mask))
                && (dirst.file_attrs & ATTR_HIDDEN) == 0)
                   add_dir_list (file_list, &dirst);
              }
            while (read_dir (&dirst));
          }
        close_dir (&dirst);
        /*  Add aliases if in user's root dir and aliases flag is set        */
        if (streq (work_buffer, "/") && p_ftpc-> aliases)
          {
            format_dir_for_alias (p_ftpc, file_list, "ftp-alias", file_mask);
            if (*FTPCONFIG ("ftp:http-aliases") == '1')
                format_dir_for_alias (p_ftpc, file_list, "alias", file_mask);
          }
        sort_dir_list (file_list, FTPCONFIG ("ftp:dirsort"));
      }

    /*  Now write it to a temporary file for output to the client            */
    sprintf (file_name, "./ls%06d.ftp", ++file_index);
    mem_strfree (&p_ftpc-> file_name);
    p_ftpc-> file_name = mem_strdup    (
             file_where ('s', FTPCONFIG ("server:temp-dir"), file_name, NULL));
    output = file_open (p_ftpc-> file_name, 'w');

    if (output)
      {
        for (file_node  = file_list-> next;
             file_node != (FILEINFO *) file_list;
             file_node  = file_node-> next)
          {
            if (full)
                fprintf (output,"%s\r\n", format_dir (&file_node-> dir, FALSE));
            else
                fprintf (output,"%s\r\n", file_node-> dir.file_name);
          }
        fclose (output);
        p_ftpc-> file_size = get_file_size (file_name);
        p_ftpc-> temp_file = TRUE;
      }
    free_dir_list (file_list);
    mem_strfree (&physical_dir);
    return (TRUE);
}


local
format_dir_for_alias (
    FTP_CONTROL_CTX *p_ftpc,
    NODE            *file_list,
    char            *alias,
    char            *mask)
{
    SYMBOL
        *symbol;                        /*  Symbol in config table           */
    DIRST
        dirst;                          /*  Directory structure entry        */
    char
        *alias_name;

    symbol = sym_lookup_symbol (p_ftpc-> config, alias);
    if (symbol)
        symbol = symbol-> next;         /*  Skip directory entry itself      */

    while (symbol && strprefixed (symbol-> name, alias))
      {
        alias_name = symbol-> name + strlen (alias) + 1;
        if (*alias_name == '/')
            alias_name++;               /*  Skip leading '/' in alias        */

        dirst.dir_name   = "";
        dirst.owner      = "xitami";
        dirst.group      = "alias";
        dirst.file_name  = alias_name;
        dirst.file_time  = time (NULL);
        dirst.file_size  = 0;
        dirst.file_mode  = 0777 + S_IFDIR;
        dirst.file_attrs = ATTR_SUBDIR;
        dirst.file_nlink = 1;

        if (!mask || file_matches (dirst.file_name, mask))
            add_dir_list (file_list, &dirst);

        symbol = symbol-> next;
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_dir_name

    Synopsis: Builds an external directory name in the buffer, using the
    user's current working directory, and the command arguments if any.
    The resulting directory name is not validated in any way.  It must be
    translated using ftpc_map_name () to get a physical path.  Returns
    TRUE if the directory name could be translated to a physical path, or
    FALSE if otherwise.  When it returns FALSE, always copies the current
    directory name into the buffer.
    ---------------------------------------------------------------------[>]-*/

Bool
ftpc_dir_name (FTP_CONTROL_CTX *p_ftpc, char *buffer)
{
    Bool
        feedback = TRUE;                /*  Assume it was okay               */
    char
        *new_dir;                       /*  Requested directory              */

    /*  Build a file/directory name in buffer                                */
    ftpc_file_name (p_ftpc, buffer);

    /*  Now check whether the resulting directory name maps correctly        */
    new_dir = ftpc_map_name (p_ftpc, buffer);
    if (strnull (new_dir))              /*  "" means syntax error            */
        feedback = FALSE;
    else
        feedback = file_is_directory (new_dir);

    if (!feedback)
        strcpy (buffer, p_ftpc-> cur_dir);
    mem_strfree (&new_dir);
    return (feedback);
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_file_name

    Synopsis: Builds an external filename in the buffer, using the user's
    current working directory, and the command arguments if any.  The
    resulting filename is not validated in any way.  It must be translated
    using ftpc_map_name() to get a physical path.  If the command has no
    arguments, copies the current directory name into the buffer.
    ---------------------------------------------------------------------[>]-*/

void
ftpc_file_name (FTP_CONTROL_CTX *p_ftpc, char *buffer)
{
    char
        *params;                        /*  Command argument if any          */

    params = p_ftpc-> parameters;
    if (params == NULL)                 /*  No parameters-> use curr dir     */
        strcpy (buffer, p_ftpc-> cur_dir);
    else
      {
        if (*params == '/')             /*  Use absolute directory           */
            strncpy (buffer, params, BUFFER_SIZE);
        else                            /*  Use relative directory           */
          {
            strcpy (buffer, p_ftpc-> cur_dir);
            if (strlast (buffer) != '/')
                strcat (buffer, "/");
            strncat (buffer, params, BUFFER_SIZE - strlen (buffer));
          }
        strcpy (buffer, resolve_path (buffer));
        /*  Remove trailing / if any (except first slash)                    */
        if (strlast (buffer) == '/')
            strlast (buffer) = '\0';
        if (strnull (buffer))           /*  And use "/" if finally empty     */
            strcpy (buffer, "/");
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_mkdir

    Synopsis: Make a new directory
    ---------------------------------------------------------------------[>]-*/

void
ftpc_mkdir (FTP_CONTROL_CTX *p_ftpc)
{
    char
        *physical_dir;

    p_ftpc-> return_code = FTP_RC_PERMISSION_DENIED;
    if (p_ftpc-> parameters)
      {
        ftpc_file_name (p_ftpc, work_buffer);
        if ((ftpc_permissions (p_ftpc, work_buffer, FALSE)
        &    FTP_AUTH_MKDIR) > 0)
          {
            physical_dir = ftpc_map_name (p_ftpc, work_buffer);
            if (make_dir (physical_dir) == 0)
                p_ftpc-> return_code = FTP_RC_FILE_ACTION_OK;
            mem_strfree (&physical_dir);
          }
      }
    else
        p_ftpc-> return_code = FTP_RC_SYNTAX_ERROR_PARAM;
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_rmdir

    Synopsis: Remove a empty directory.
    ---------------------------------------------------------------------[>]-*/

void
ftpc_rmdir (FTP_CONTROL_CTX *p_ftpc)
{
    char
        *physical_dir;

    p_ftpc-> return_code = FTP_RC_PERMISSION_DENIED;
    if (p_ftpc-> parameters)
      {
        if (!ftpc_dir_name (p_ftpc, work_buffer))
          {
            p_ftpc-> return_code = FTP_RC_FILE_NOT_FOUND;
            return;                     /*  Could not build a dir name       */
          }
      }
    else
        strcpy (work_buffer, p_ftpc-> cur_dir);

    if ((ftpc_permissions (p_ftpc, work_buffer, FALSE)
    &    FTP_AUTH_RMDIR) > 0)
      {
        physical_dir = ftpc_map_name (p_ftpc, work_buffer);
        if (remove_dir (physical_dir) == 0)
            p_ftpc-> return_code = FTP_RC_FILE_ACTION_OK;
        mem_strfree (&physical_dir);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_chdir

    Synopsis: Change to the specified directory if possible.
    ---------------------------------------------------------------------[>]-*/

void
ftpc_chdir (FTP_CONTROL_CTX *p_ftpc)
{
    if (p_ftpc-> parameters)
      {
        /*  Try to change directory                                          */
        if (!ftpc_dir_name (p_ftpc, work_buffer))
            p_ftpc-> return_code = FTP_RC_FILE_NOT_FOUND;
        else
        if ((ftpc_permissions (p_ftpc, work_buffer, FALSE)
        &   (FTP_AUTH_GET + FTP_AUTH_PUT)) != 0)
          {
            mem_strfree (&p_ftpc-> cur_dir);
            p_ftpc-> cur_dir = mem_strdup (work_buffer);
            p_ftpc-> return_code = FTP_RC_FILE_ACTION_OK;
          }
        else
            p_ftpc-> return_code = FTP_RC_PERMISSION_DENIED;
      }
    else
        /*  No parameters means stay where we are...                         */
        p_ftpc-> return_code = FTP_RC_FILE_ACTION_OK;
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_cdup

    Synopsis: Move up to parent directory by removing last component of
    the current directory if there is anything after the '/'.
    ---------------------------------------------------------------------[>]-*/

void
ftpc_cdup (FTP_CONTROL_CTX *p_ftpc)
{
    char
        *slash;

    strcpy (work_buffer, p_ftpc-> cur_dir);
    slash = strrchr (work_buffer + 1, '/');
    if (slash)
        *slash = '\0';                  /*  Cut at slash, if there           */
    else
    if (work_buffer [0])                /*  Otherwise cut after first /      */
        work_buffer [1] = '\0';

    /*  Try to change directory                                              */
    if ((ftpc_permissions (p_ftpc, work_buffer, FALSE)
    &   (FTP_AUTH_GET + FTP_AUTH_PUT)) != 0)
      {
        /*  Copy new name, which is always at least shorter                  */
        strcpy (p_ftpc-> cur_dir, work_buffer);
        p_ftpc-> return_code = FTP_RC_FILE_ACTION_OK;
      }
    else
        p_ftpc-> return_code = FTP_RC_PERMISSION_DENIED;
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpc_map_name

    Synopsis: Maps an external filename into an internal physical name with
    full path information.  Returns a pointer to a fresh buffer containing
    the name, or NULL if there was a problem.  The mapping works as follows:

    1.  Any single-word alias at the start of the name is replaced by the
        value of the alias.  We limit aliases to single words to make the
        lookup process faster (no scanning is involved).  Aliases are not
        case-dependent.  HTTP aliases are used iff ftp:http_aliases is 1.
        Aliases are only allowed for root users.

    2.  Otherwise we prefix the user's root directory.
    ---------------------------------------------------------------------[>]-*/

char *
ftpc_map_name (FTP_CONTROL_CTX *p_ftpc, char *external)
{
    char
        *uri_base,                      /*  URI following alias, if any      */
        *local_root,
        *full_name,                     /*  Final full name                  */
        *slash;                         /*  We may need a / delimiter        */
    SYMBOL
        *alias = NULL;                  /*  Alias symbol pointer             */

    ASSERT (external);

    if (p_ftpc-> aliases)
      {
        /*  Resolve any aliases used in the URI.  The current implementation
         *  only allows single-word aliases at the start of the URI.  So, we
         *  take the first URI path component and see if it is a known alias.
         *  If so, we replace that by the alias value. Aliases are lowercase.
         */
        /*  We look for FTP aliases first; these take precedence             */
        alias = http_match_alias (config, external, "ftp-alias", &uri_base);

        /*  If that did not find anything, try an ordinary HTTP alias        */
        if (alias == NULL && *FTPCONFIG ("ftp:http-aliases") == '1')
            alias = http_match_alias (config, external, "alias", &uri_base);
      }
    if (alias)                          /*  Get alias path                   */
        local_root = alias-> value;     /*    uri_base is set                */
    else
      {                                 /*  No alias: use normal rootdir     */
        /*  Get the server FTP root and add the user's root                  */
        local_root = p_ftpc-> real_root;
        uri_base = external;
      }
#if (defined (MSDOS_FILESYSTEM))
    /*  Simplify the code by using / as path delimiter                       */
    strconvch (local_root, '\\', '/');
#endif
    local_root = resolve_path (local_root);
    if (strlast (local_root) == '/')    /*  If root ends in / we do not      */
        slash = "";                     /*    need to add one                */
    else
        slash = "/";

    if (*uri_base == '/')               /*  In any case, skip / at start     */
        uri_base++;                     /*    of URI name                    */

    xstrcpy_debug ();
    full_name = xstrcpy (NULL, local_root, slash, uri_base, NULL);
    return (full_name);
}


/*###########################################################################
  #                                                                         #
  #                           FTP DATA FUNCTIONS                            #
  #                                                                         #
  ###########################################################################*/

/*  ---------------------------------------------------------------------[<]-
    Function: ftpd_init

    Synopsis: Initialises the FTP data context.
    ---------------------------------------------------------------------[>]-*/

void
ftpd_init (FTP_DATA_CTX *p_ftpd)
{
    memset (p_ftpd, 0, sizeof (FTP_DATA_CTX));
}


/*  ---------------------------------------------------------------------[<]-
    Function: ftpd_free

    Synopsis: Free all allocate memory of ftp data context
    ---------------------------------------------------------------------[>]-*/

void
ftpd_free (FTP_DATA_CTX *p_ftpd)
{
    mem_strfree (&p_ftpd-> file_name);
}
