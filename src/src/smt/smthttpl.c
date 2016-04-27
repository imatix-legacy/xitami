/*  ----------------------------------------------------------------<Prolog>-
    Name:       smthttpl.c
    Title:      Hyper Text Transfer Protocol functions library
    Package:    Libero SMT 2.x

    Written:    96/04/26  iMatix SMT kernel team <smt@imatix.com>
    Revised:    00/03/31  for Xitami 2.4d5

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SMT License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"                        /*  SFL library header file          */
#include "smtlib.h"

#define  DEFINE_HTTP_TABLES
#include "smthttpl.h"                   /*  Function prototypes              */


/*- Global variables used in this source only -------------------------------*/

static char
    server_message_text [LINE_MAX] = "";
static char
    *eoln = "\r\n";                     /*  Standard end-of-line             */
static char
    buffer [HTTP_URL_MAX + 1];          /*  General-use string buffer        */

#define POWERED_BY \
    "<P><I>Powered by <A HREF=\"http://www.imatix.com\">" \
    "the Xitami web server</A></I>"


/*- Global variables --------------------------------------------------------*/

char
    *server_name = "Xitami",
    *server_message = server_message_text;
qbyte
    connect_count = 0,                  /*  Number of connections made       */
    cur_connects  = 0,                  /*  Cur connections made             */
    max_connects  = 0,                  /*  Max connections made             */
    error_count   = 0,                  /*  Number of errors                 */
    transfer_size = 0;                  /*  Amount of data transfered        */
long
    time_started = 0,                   /*  Time that server started         */
    date_started = 0;                   /*  Date that server started         */
SYMTAB
    *config = NULL,                     /*  Global configuration table       */
    *defaults = NULL,                   /*  Defaults for config options      */
    *wsx_aliases = NULL;                /*  WSX aliases table                */
Bool
    server_killed = FALSE,              /*  If ended from control panel      */
    defaults_loaded = FALSE,            /*  Is defaults table accessible?    */
    config_loaded = FALSE;              /*  Did we load the config table?    */


/*- Definitions and constants -----------------------------------------------*/

#define MAP_MAX_POINTS      100         /*  Max. points in one map line      */
#define MAX_DEFAULTS        32          /*  Max. defaults to look for        */
#define URI_MAX_LENGTH      LINE_MAX    /*  Max. allowable length of a URI   */

#define HCONFIG(s)      http_config (p_http-> config, (s))


/*- Internal function prototypes --------------------------------------------*/

static void    load_defaults_table  (void);
static void    http_free_strings    (HTTP_CONTEXT *p_http);
static void    http_close_cgi       (HTTP_CONTEXT *p_http);
static char   *get_map_value        (char *map_file, char *request_point);
static void    point_in_map_element (char *buffer, char *rc_url, int x, int y,
                                     char *url_def);
static char   *http_get_mime_type   (HTTP_CONTEXT *, char *extension);
static char   *http_get_filter      (HTTP_CONTEXT *);
static char   *look_for_alternate   (HTTP_CONTEXT *, char *filename);
static char   *try_alt_name         (char *filename, char *ext, char *lang);
static Bool    set_keep_alive       (HTTP_CONTEXT *);
static void    parse_authorization  (HTTP_CONTEXT *);
static SYMTAB *add_cgi_environment  (HTTP_CONTEXT *, Bool filter);
static void    put_dynamic_headers  (HTTP_CONTEXT *, char *header);
static void    format_error_header  (HTTP_CONTEXT *, char *buffer);
static void    format_full_url      (HTTP_CONTEXT *, char *buffer,
                                     char *url, char *suffix);
static char   *http_hostname        (HTTP_CONTEXT *);
static Bool    parse_cgi_header     (HTTP_CONTEXT *, char *header, char *sep);
static void    http_put_resource    (HTTP_CONTEXT *, char *target_filename);
static void    http_delete_resource (HTTP_CONTEXT *, char *target_filename);
static void    http_move_resource   (HTTP_CONTEXT *, char *target_filename);
static void    http_copy_resource   (HTTP_CONTEXT *, char *target_filename);
static Bool    http_overwrite_ok    (HTTP_CONTEXT *);
static void    set_access_failed    (HTTP_CONTEXT *);


/*  ---------------------------------------------------------------------[<]-
    Function: http_init

    Synopsis: Initialises the HTTP library.
    ---------------------------------------------------------------------[>]-*/

void
http_init (void)
{
    SYMBOL
        *symbol;
        
    /*  Load configuration data into the config table if required            */
    if (config == NULL)
      {
        config = ini_dyn_load (NULL, "xitami.cfg");
        ini_dyn_load (config, CONFIG ("server:defaults"));
        config_loaded = TRUE;
      }
    if (defaults == NULL)
        load_defaults_table ();

    if (wsx_aliases == NULL)
        wsx_aliases = sym_create_table ();

    if (*CONFIG ("server:debug") == '1')
      {
        enable_trace ();
        set_trace_file (file_where ('s', CONFIG ("server:debug-dir"),
                                    "debug.log", NULL), 'a');
      }
    time_started = time_now ();
    date_started = date_now ();
    http_capture_console ();

    /*  Warn if config contains symbols with '_' in the name                 */
    for (symbol = config-> symbols; symbol; symbol = symbol-> next)
        if (strchr (symbol-> name, '_')
        && !strprefixed (symbol-> name, "virtual-hosts:"))
            coprintf ("Warning: '_' in '%s' should probably '-'",
                       symbol-> name);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_term

    Synopsis: Terminates the HTTP library.
    ---------------------------------------------------------------------[>]-*/

void
http_term (void)
{
    defaults_loaded = FALSE;
    if (defaults)
      {
        sym_delete_table (defaults);
        defaults = NULL;
      }
    if (wsx_aliases)
      {
        sym_delete_table (wsx_aliases);
        wsx_aliases = NULL;
      }
    if (config_loaded)
      {
        sym_delete_table (config);
        config_loaded = FALSE;
        config = NULL;
      }
    disable_trace ();
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_config

    Synopsis: Returns config value for specified key.  If the value is not
    defined, returns the default value.  If no default is defined, returns
    an empty string ("").
    ---------------------------------------------------------------------[>]-*/

char *
http_config (SYMTAB *table, const char *key)
{
    /*  Don't go any further if config table is not (yet) loaded             */
    if (table == NULL)
        return ("");
        
    if (defaults == NULL)
        load_defaults_table ();

    return (sym_get_value (table, key,
            sym_get_value (defaults, key, "")));
}


static void
load_defaults_table (void)
{
    static struct {
        char *name;
        char *value;
    } default_list [] = {

    { "server:", NULL                                                        },
    {   "advertize",        "1"                                              },
    {   "autostart",        "0"                                              },
    {   "background",       "0"                                              },
    {   "base-host",        "basehost.cfg"                                   },
    {   "cache-defaults",   "1"                                              },
    {   "cgi-bin",          "cgi-bin"                                        },
    {   "cgi-url",          "/cgi-bin"                                       },
    {   "defaults",         "defaults.cfg"                                   },
    {   "debug",            "0"                                              },
    {   "debug-dir",        "debug"                                          },
    {   "default1",         "index.htm"                                      },
    {   "default2",         "default.htm"                                    },
    {   "dirsort",          "n"                                              },
    {   "error-footer",     "@errors/footer.htm"                             },
    {   "error-header",     "@errors/header.htm"                             },
    {   "ipaddress",        "*"                                              },
    {   "keep-alive",       "1"                                              },
    {   "keep-alive-max",   "50"                                             },
    {   "limit",            "0",                                             },
    {   "log-dir",          "logs",                                          },
    {   "portbase",         "0"                                              },
    {   "priority",         "1"                                              },
    {   "recover",          "0"                                              },
    {   "refresh",          "60"                                             },
    {   "text-400",         "@errors/text-400.htm"                           },
    {   "text-401",         "@errors/text-401.htm"                           },
    {   "text-402",         "@errors/text-402.htm"                           },
    {   "text-403",         "@errors/text-403.htm"                           },
    {   "text-404",         "@errors/text-404.htm"                           },
    {   "text-412",         "@errors/text-412.htm"                           },
    {   "text-413",         "@errors/text-413.htm"                           },
    {   "text-500",         "@errors/text-500.htm"                           },
    {   "text-501",         "@errors/text-501.htm"                           },
    {   "text-502",         "@errors/text-502.htm"                           },
    {   "temp-dir",         "temp"                                           },
    {   "timeout",          "30"                                             },
    {   "webpages",         "webpages"                                       },

    { "wsx:", NULL                                                           },
    {   "xiadmin",          "/admin"                                         },

    { "cgi:", NULL                                                           },
    {   "debug",            "0"                                              },
    {   "dirlist",          "0"                                              },
    {   "enabled",          "1"                                              },
    {   "environment",      "1"                                              },
    {   "errlog",           "cgierr.log"                                     },
    {   "form-fields",      "1"                                              },
    {   "form-prefix",      "FORM_"                                          },
    {   "form-query",       "0"                                              },
    {   "http-fields",      "1"                                              },
    {   "http-prefix",      "HTTP_"                                          },
    {   "mixed-url",        "1"                                              },
    {   "monitor",          "200"                                            },
    {   "msdos-style",      "0"                                              },
    {   "passargs",         "0"                                              },
    {   "stdio",            "1"                                              },
    {   "timeout",          "60"                                             },
    {   "wildcard",         "0"                                              },
    {   "workdir",          "-"                                              },

    { "security:", NULL                                                      },
    {   "dirlist",          "1"                                              },
    {   "encrypt",          "0"         /*  TO BE IMPLEMENTED            */  },
    {   "filename",         "xitami.aut"                                     },
    {   "password-case",    "1"                                              },
    {   "safepaths",        "1"                                              },
    {   "superuser",        ""                                               },
    {   "webmask",          "*"                                              },
    {   "admin",            "1"                                              },
    {   "setuid",           "0"                                              },
    {   "setuid-user",      "nobody"                                         },
    {   "setuid-group",     "nogroup"                                        },

    { "serverlog:", NULL                                                     },
    {   "cycle",            "daily"                                          },
    {   "enabled",          "1"                                              },
    {   "filename",         "xitami.log"                                     },

    { "accesslog:", NULL                                                     },
    {   "cycle",            "daily"                                          },
    {   "enabled",          "1"                                              },
    {   "filename",         "access.log"                                     },
    {   "local",            "1"                                              },
    /*  The following options are only used in Xitami/Pro                    */
    {   "extended",         "1"                                              },
    {   "format",           "XCLF"                                           },
    {   "cycle-how",        "rename"                                         },
    {   "cycle-time",       "00:00"                                          },
    {   "cycle-day",        "0"                                              },
    {   "cycle-size",       "0"                                              },
    {   "cycle-lines",      "0"                                              },
    {   "cycle-arg",        "ac%yy%mm%dd.log"                                },
    {   "translate",        "0"                                              },

    { "errorlog:", NULL                                                      },
    {   "cycle",            "daily"                                          },
    {   "enabled",          "1"                                              },
    {   "filename",         "errors.log"                                     },
    {   "local",            "1"                                              },
    /*  The following options are only used in Xitami/Pro                    */
    {   "extended",         "1"                                              },
    {   "format",           "XCLF"                                           },
    {   "cycle-how",        "rename"                                         },
    {   "cycle-time",       "00:00"                                          },
    {   "cycle-day",        "0"                                              },
    {   "cycle-size",       "0"                                              },
    {   "cycle-lines",      "0"                                              },
    {   "cycle-arg",        "er%yy%mm%dd.log"                                },
    {   "translate",        "0"                                              },

    /*  The following options are only used in Xitami/Pro                    */
    { "rdns:", NULL                                                          },
    {   "primary-server",   "127.0.0.1",                                     },
    {   "secondary-server", "",                                              },
    {   "recurse-lookups",  "1",                                             },
    {   "debug",            "0",                                             },

    { "console:", NULL                                                       },
    {   "append",           "0"                                              },
    {   "capture",          "1"                                              },
    {   "filename",         "console.log"                                    },
    {   "rate",             "10",                                            },
    {   "refresh",          "0"                                              },
    {   "startup",          "1"                                              },
    {   "javascript",       "1"                                              },
    {   "large-icons",      "1"                                              },

    { "ftp:", NULL                                                           },
    {   "email-check",      "0"                                              },
    {   "data-port",        "200"                                            },
    {   "enabled",          "1"                                              },
    {   "force-ip",         "0"                                              },
    {   "http-aliases",     "0",                                             },
    {   "ipaddress",        "*"                                              },
    {   "limit",            "25"                                             },
    {   "port",             "21"                                             },
    {   "root",             "ftproot"                                        },
    {   "signoff",          "@ftpadios.txt"                                  },
    {   "timeout",          "300"                                            },
    {   "user-file",        "ftpusers.aut"                                   },
    {   "directory-file",   "ftpdirs.aut"                                    },
    {   "soft-quota",       "2.5"                                            },
    {   "hard-quota",       "5"                                              },
    {   "dirsort",          "n"                                              },
    {   "password-case",    "1"                                              },
    {   "webmask",          "*"                                              },
    {   "welcome",          "@ftphello.txt"                                  },
    {   "login-text",       "@ftplogin.txt"                                  },

    { "ftplog:", NULL                                                        },
    {   "enabled",          "1"                                              },
    {   "filename",         "access.log"                                     },
    {   "cycle",            "daily"                                          },
    {   "local",            "1"                                              },

    { "ftperrlog:", NULL                                                     },
    {   "enabled",          "1"                                              },
    {   "filename",         "errors.log"                                     },
    {   "cycle",            "daily"                                          },
    {   "local",            "1"                                              },

    { "mime:", NULL                                                          },
    {   "default",          "*/*"                                            },
    {   "doc",              "text/plain"                                     },
    {   "gif",              "image/gif"                                      },
    {   "htm",              "text/html"                                      },
    {   "html",             "text/html"                                      },
    {   "jpg",              "image/jpeg"                                     },
    {   "jpeg",             "image/jpeg"                                     },
    {   "txt",              "text/plain"                                     },

    { "win32:", NULL                                                         },
    {   "16bit-cgi",        "1"                                              },
    {   "secure",           "0"                                              },
    {   "service-name",     "Xitami"                                         },
    {   "service-text",     "Xitami Web Server"                              },
    
    { "lrwp:", NULL                                                          },
    {   "enabled",          "1"                                              },
    {   "port",             "81"                                             },
    {   "webmask",          "local"                                          },

    { "ssl-http:", NULL                                                      },
    {   "enabled",          "0"                                              },
    {   "config-file",      "sslhttp.cfs"                                    },

    { NULL, NULL }
    };
    int
        index;

    defaults = sym_create_table ();
    for (index = 0; default_list [index].name; index++)
      {
        /*  If new heading, get heading name                                 */
        if (default_list [index].value == NULL)
            strcpy (buffer, default_list [index].name);
        else
          {
            /*  Else reuse existing heading name in buffer                   */
            ASSERT (strchr (buffer, ':'));
            *strchr (buffer, ':') = '\0';
            strcat (buffer, ":");
            strcat (buffer, default_list [index].name);
            sym_assume_symbol (defaults, buffer, default_list [index].value);
          }
      }
    defaults_loaded = TRUE;
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_init_context

    Synopsis: Initialises a HTTP_CONTEXT structure; this structure is used
    in calls to the functions that provide HTTP support.  You must allocate
    the structure yourself.
    ---------------------------------------------------------------------[>]-*/

void
http_init_context (HTTP_CONTEXT *p_http)
{
    ASSERT (p_http);
    p_http-> method          = 0;
    p_http-> protocol        = 0;
    p_http-> response        = 0;
    p_http-> file_size       = 0;
    p_http-> file_date       = 0;
    p_http-> file_time       = 0;
    p_http-> file_offset     = 0;
    p_http-> post_size       = 0;
    p_http-> socket          = 0;
    p_http-> port            = 0;
    p_http-> output_timeout  = 0;
    p_http-> keep_alive      = FALSE;
    p_http-> transaction     = 0;
    p_http-> error_type      = 0;
    p_http-> send_file       = FALSE;
    p_http-> temp_file       = FALSE;
    p_http-> file_name       = NULL;
    p_http-> log_request     = NULL;
    p_http-> url             = NULL;
    p_http-> url_param       = NULL;
    p_http-> url_ext         = NULL;
    p_http-> table           = NULL;
    p_http-> username        = NULL;
    p_http-> password        = NULL;
    p_http-> realm           = NULL;
    p_http-> script_path     = NULL;
    p_http-> script_name     = NULL;
    p_http-> path_info       = NULL;
    p_http-> cgi_process_id  = NULL_PROCESS;
    p_http-> cgi_environ     = NULL;
    p_http-> post_data       = NULL;
    p_http-> referrer        = NULL;
    p_http-> cgi_stdin       = NULL;
    p_http-> cgi_status      = NULL;
    p_http-> vhost           = NULL;
    p_http-> wsx_agent       = NULL;
    p_http-> rootdir         = NULL;
    p_http-> cgidir          = NULL;
    p_http-> webmask         = NULL;
    p_http-> cgi_header      = FALSE;
    p_http-> default_page    = TRUE;
    http_refresh_context (p_http);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_refresh_context

    Synopsis: Initialises the various fields in the HTTP structure that
    come from the config table.
    ---------------------------------------------------------------------[>]-*/

void
http_refresh_context (HTTP_CONTEXT *p_http)
{
    p_http-> input_timeout  = atoi (HCONFIG ("server:timeout"));
    p_http-> keep_alive_max = atoi (HCONFIG ("server:keep-alive-max"));
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_free_context

    Synopsis: Frees any strings allocated in the HTTP_CONTEXT block.  Use
    this function when you are finished using the HTTP support functions.
    Does not actually free the HTTP_CONTEXT block.
    ---------------------------------------------------------------------[>]-*/

void
http_free_context (HTTP_CONTEXT *p_http)
{
    ASSERT (p_http);

    http_close_cgi    (p_http);
    http_free_strings (p_http);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_set_priority

    Synopsis: Initialises the HTTP server priority.
    ---------------------------------------------------------------------[>]-*/

void
http_set_priority (void)
{
    if (*CONFIG ("server:priority") == '2')
        process_priority (PRIORITY_LOW);
    else
    if (*CONFIG ("server:priority") == '3')
        process_priority (PRIORITY_HIGH);
    else
        process_priority (PRIORITY_NORMAL);
}


static void
http_close_cgi (HTTP_CONTEXT *p_http)
{
    if (p_http-> table)
      {
        sym_delete_table (p_http-> table);
        p_http-> table = NULL;
      }
    if (p_http-> cgi_environ)
      {
        strtfree (p_http-> cgi_environ);
        p_http-> cgi_environ = NULL;
      }
    http_close_process (p_http);
}


static void
http_free_strings (HTTP_CONTEXT *p_http)
{
    mem_strfree (&p_http-> log_request);
    mem_strfree (&p_http-> url);
    mem_strfree (&p_http-> url_param);
    mem_strfree (&p_http-> username);
    mem_strfree (&p_http-> password);
    mem_strfree (&p_http-> realm);
    mem_strfree (&p_http-> script_path);
    mem_strfree (&p_http-> script_name);
    mem_strfree (&p_http-> path_info);
    mem_strfree (&p_http-> post_data);
    mem_strfree (&p_http-> referrer);
    mem_strfree (&p_http-> cgi_status);
    mem_strfree (&p_http-> vhost);
    mem_strfree (&p_http-> wsx_agent);
    mem_strfree (&p_http-> rootdir);
    mem_strfree (&p_http-> cgidir);
    mem_strfree (&p_http-> webmask);

    if (p_http-> cgi_stdin)
      {
        if (*(HCONFIG ("cgi:debug")) == '0')
            file_delete (p_http-> cgi_stdin);
        mem_strfree (&p_http-> cgi_stdin);
      }
    if (p_http-> file_name)
      {
        if (p_http-> temp_file
        && (p_http-> transaction == TRANSACTION_FILE
        || *(HCONFIG ("cgi:debug")) == '0'))
            file_delete (p_http-> file_name);
        mem_strfree (&p_http-> file_name);
        p_http-> temp_file = FALSE;
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_parse_request

    Synopsis: Extracts the HTTP method, URL, HTTP version from the request,
    and parses all other HTTP headers into the http symbol table.  Returns
    TRUE if okay, FALSE if the header was unreadable.  Note: this function
    destroys the buffer.

    Examples:
    This is a typical request -
        POST /cgi-bin/process HTTP/1.0
        If-Modified-Since: Sunday, 05-Nov-95 20:23:42 GMT; length=683
        Connection: Keep-Alive
        User-Agent: Mozilla/2.0GoldB2 (Win95; I)
        Host: www.imatix.com
        Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg
        <blank line>
        ...post data...
    ---------------------------------------------------------------------[>]-*/

int
http_parse_request (HTTP_CONTEXT *p_http, char *request)
{
    char
        *protocol,
        *method,
        *url,
        *separator,
        *query_body,
        *p_param;
    int
        index;
    Bool
        found = FALSE;

    ASSERT (p_http);
    ASSERT (request);

    /*  Create a symbol table for MIME values in the request header         */
    if (!p_http-> table)
        p_http-> table = sym_create_table ();

    /*  Save the request for later output to the log file.                   */
    separator = strpbrk (request, "\n\r");
    if (separator)
      {
        *separator = '\0';
        mem_strfree (&p_http-> log_request);
        p_http-> log_request = http_clean_request (request);
        *separator = '\r';
      }

    /*  Get the method in the request; delimit on space or tabs              */
    p_http-> response = HTTP_RESPONSE_OK;
    method = strtok (request, "\t ");
    if (method)
      {
        for (index = 0; strused (http_methods [index]); index++)
          {
            if (!lexcmp (method, http_methods [index]))
              {
                p_http-> method = index;
                found = TRUE;
                if (p_http-> method == HTTP_METHOD_GET)
                    p_http-> send_file = TRUE;
                break;
              }
            }
        if (!found)
          {
            p_http-> response = HTTP_RESPONSE_NOTIMPLEMENTED;
            return (FALSE);
          }
      }
    else
      {
        p_http-> response = HTTP_RESPONSE_INTERNALERROR;
        return (FALSE);
      }

    /*  Get the URL in the request; the URL is everything between the method
     *  and the HTTP protocol indicator...  It's a little messy, but we need
     *  to allow for URLs that contain spaces (e.g. Win95).  So, we look from
     *  the end of the line, take-off " HTTP/x.x" and use what remains as the
     *  URL.  If we don't find HTTP/x.x at the end, we default to HTTP/1.0.
     */
    url = strtok (NULL, "\n\r");        /*  Get token up to end of line      */
    if (url)
      {
        /*  Look for HTTP/x.x as last 8 characters of URL string             */
        p_http-> protocol = HTTP_PROT_1_0;
        protocol = url + strlen (url) - 8;
        if (strprefixed (protocol, "HTTP/"))
          {
            for (index = 0; strused (protocols [index]); index++)
                if (streq (protocol, protocols [index]))
                  {
                    p_http-> protocol = index;
                    break;
                  }
            *protocol = '\0';           /*  Cut URL at protocol              */
            strcrop (url);              /*  Kill trailing spaces             */
          }
        /*  Check if URL has parameters (for CGI or image map)               */
        p_param = strchr (url, '?');
        if (p_param)
          {
            *p_param++ = '\0';
            p_http-> url_param = mem_strdup (p_param);
          }
        /*  Prepare URI and guard against over-long URIs                     */
        http_unescape_hex (url, NULL);
        strconvch (url, '\\', '/');     /*  Don't allow '\' in the URL       */
        if (strlen (url) > URI_MAX_LENGTH)
          {
            p_http-> url      = mem_strdup (url);
            p_http-> url [80] = '\0';
            p_http-> response = HTTP_RESPONSE_TOOLARGE;
            return (FALSE);
          }
        /*  Store the URL, resolving all . and .. in path                    */
        strunique (url, '/');           /*  '//' is treated as '/'           */
        p_http-> url = mem_strdup  (resolve_path (url));
        p_http-> url_ext = strrchr (p_http-> url, '.');
      }

    /*  Parse HTTP header variables; point to line after header              */
    query_body = http_parse_header (p_http, strtok (NULL, "\n"));
    if (query_body && !p_http-> cgi_stdin)
      {
        /*  Find and save POSTed data, if it's there and has not already
         *  been saved to the stdin file.
         */
        query_body = strtok (NULL, "");
        if (query_body)                 /*  POST data                        */
          {
            p_http-> post_data = mem_alloc (p_http-> post_size + 1);
            memcpy (p_http-> post_data, query_body, p_http-> post_size);
            p_http-> post_data [p_http-> post_size] = '\0';
          }
      }
    /*  Set the keep-alive connection flag                                   */
    set_keep_alive      (p_http);
    parse_authorization (p_http);

    return (found);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_parse_header

    Synopsis: Parses a HTTP header string, and stores the header values into
    the symbol table.  Each name is stored as lower-case; values are stored
    as-is.  The string should contain header values like 'Length: 85'
    separated by CRLF.   A double CRLFCRLF, or a null byte, ends the header.
    Modifies header.  Returns a pointer to the blank line or null ending the
    header text.
    ---------------------------------------------------------------------[>]-*/

char *
http_parse_header (HTTP_CONTEXT *p_http, char *header)
{
    char
        *header_field,
        *separator;
    int
        fields = 0;

    ASSERT (p_http);

    /*  Insert "0" as default value for numeric fields                       */
    sym_assume_symbol (p_http-> table, "content-length", "0");
    if (header == NULL)
        return (NULL);

    header_field = header;
    while (header_field && header_field [0] != '\r')
      {
        if ((separator = strchr (header_field, ':')) != NULL)
          {
            *separator = '\0';
            separator++;
            while (*separator == ' ')
                separator++;

            strlwc (header_field);      /*  Put name into lowercase          */

            /*  Remove any trailing carriage-return or linefeed              */
            if ((strchr (separator, '\r')) != NULL)
                *strchr (separator, '\r') = '\0';

            /*  It's possible that the Referer: field contains an URL
             *  followed by ? and a whole long argument...  We don't want
             *  that stuff.  Get rid of it.  (But save it all first.)
             */
            if (streq (header_field, "referer"))
              {
                mem_strfree (&p_http-> referrer);
                p_http-> referrer = mem_strdup (separator);
                if (strchr (separator, '?') != NULL)
                    *strchr (separator, '?') = '\0';
              }
            sym_assume_symbol (p_http-> table, header_field, separator);
            fields++;
          }
        header_field = strtok (NULL, "\n");
      }
    return (header_field);
}


/*  ---------------------------------------------------------------------[<]-
    Function: set_keep_alive - internal

    Synopsis: check if keep alive connection is in the mime symbol table
    ---------------------------------------------------------------------[>]-*/

static Bool
set_keep_alive (HTTP_CONTEXT *p_http)
{
    ASSERT (p_http);

    p_http-> keep_alive = FALSE;
    if (*(HCONFIG ("server:keep-alive")) == '1')
      {
        if (strprefixed (
             http_header_value (p_http, "connection"), "Keep-Alive")
        &&  p_http-> keep_alive_max > 1)
          {
            /*  We disable Nagle's algorithm; this makes keep-alive
             *  connections faster.  We don't do it for non-keep-alive
             *  connections, since it can slow-down the network.
             */
            socket_nodelay (p_http-> socket);
            p_http-> keep_alive = TRUE;
          }
      }
    return (p_http-> keep_alive);
}


/*  -------------------------------------------------------------------------
    Function: parse_authorization -- internal

    Synopsis: Parses the Basic Authorization field from the HTTP header.
    If the field is present, fills the HTTP_CONTEXT username and password
    values.  Otherwise these values are left unchanged.
    -------------------------------------------------------------------------*/

static void
parse_authorization (HTTP_CONTEXT *p_http)
{
    char
        *auth,                          /*  Encoded Authorization value      */
        *delim;                         /*  ':' delimiter after name         */
    int
        buflen;                         /*  Length of decoded buffer         */

    ASSERT (p_http);
    ASSERT (p_http-> table);
    ASSERT (p_http-> username == NULL);
    ASSERT (p_http-> password == NULL);

    auth = http_header_value (p_http, "authorization");
    if (strprefixed (auth, "Basic "))
      {
        auth += 6;                      /*  Get & decode authorization       */
        if (strlen (auth) > HTTP_AUTH_MAX)
             auth [HTTP_AUTH_MAX] = '\0';

        buflen = decode_base64 ((byte *) auth, (byte *) buffer, strlen (auth));
        buffer [buflen] = '\0';         /*  Terminate string nicely          */

        delim = strchr (buffer, ':');
        if (delim)
          {
            *delim++ = '\0';
            p_http-> username = mem_strdup (buffer);
            p_http-> password = mem_strdup (delim);
            /*  User names are always compared in lower-case                 */
            strlwc (p_http-> username);
            if (*(HCONFIG ("security:password-case")) == '0')
                strlwc (p_http-> password);
          }
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_header_value

    Synopsis: Returns the value for the specified HTTP header field.  If
    the field was not present in the header, returns an empty string, else
    returns the value.  The header field may be specified in mixed-case;
    the symbol table lookup disregards case.
    ---------------------------------------------------------------------[>]-*/

char *
http_header_value (HTTP_CONTEXT *p_http, char *field)
{
    SYMBOL
        *symptr;                        /*  Symbol to look for               */
    char
        *field_name;

    ASSERT (p_http);
    ASSERT (p_http-> table);

    field_name = mem_strdup (field);
    strlwc (field_name);
    symptr = sym_lookup_symbol (p_http-> table, field_name);
    mem_free (field_name);
    if (symptr)
        return (symptr-> value);
    else
        return ("");
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_get_url_type

    Synopsis: Gets the URL type (used for CGI and image maps).  Algorithm
    used is as follows: if the URL contains '.map' it is a map file.  If
    the URL contains '/cgi-bin', or starts with a CGI alias, it is a CGI
    command.  If the URL matches a WSX pattern, it is a WSX plugin; if it
    matches a filter pattern, it's a filtered file.  Returns one of (in this
    order of priority):
    <Table>
    HTTP_URL_ILLEGAL    Illegal (unsupported) URL
    HTTP_URL_WSX        WSX application
    HTTP_URL_FILTER     Filtered file
    HTTP_URL_IMAP       Image map type
    HTTP_URL_CGI        CGI program
    HTTP_URL_HTML       Normal HTML text
    </Table>
    ---------------------------------------------------------------------[>]-*/

int
http_get_url_type (HTTP_CONTEXT *p_http)
{
    int
        url_type;

    ASSERT (p_http);
    if (!p_http-> url)
        return (HTTP_URL_ILLEGAL);

    /*  Default transaction is a normal file URL                             */
    p_http-> transaction = TRANSACTION_FILE;

    if (p_http-> url [0] != '/') 
        url_type = HTTP_URL_ILLEGAL;
    else
    if (http_match_wsx (p_http))
      {
        p_http-> transaction = TRANSACTION_WSX;
        url_type = HTTP_URL_WSX;
      }
    else
    if (http_get_filter (p_http))
      {
        p_http-> transaction = TRANSACTION_FILTER;
        url_type = HTTP_URL_FILTER;
      }
    else
    if (p_http-> url_ext && streq (p_http-> url_ext, ".map"))
        url_type = HTTP_URL_IMAP;
    else
    if ((*HCONFIG ("cgi:wildcard") == '1'
    &&  strstr      (p_http-> url, HCONFIG ("server:cgi-url")))
    ||  strprefixed (p_http-> url, HCONFIG ("server:cgi-url"))
    ||  http_match_alias (p_http-> config, p_http-> url, "cgi-alias", NULL))
      {
        p_http-> transaction = TRANSACTION_CGI;
        if (*(HCONFIG ("cgi:enabled")) == '1')
            url_type = HTTP_URL_CGI;
        else
            url_type = HTTP_URL_ILLEGAL;
      }
    else
        url_type = HTTP_URL_HTML;

    return (url_type);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_match_alias

    Returns the alias symbol pointer if the URI matches an alias defined
    in the configuration table.  The alias type is the section name without
    a colon.  The alias may optionally start with '/'.  Aliases match only
    whole path components.  For example, the aliases 'demo' and '/demo' both
    match a URI '/demo/myprog/'.  If the 'base' argument is not null, it is
    set to point to the remainder of the URI after the alias.  Assumes that
    the config table is sorted.
    ---------------------------------------------------------------------[>]-*/

SYMBOL *
http_match_alias (
    SYMTAB *config, const char *uri, const char *type, char **base)
{
    SYMBOL
        *symbol;
    char
        *alias_name,                    /*  Name of alias, no leading '/'    */
        *base_char;

    /*  Find section header for aliases                                      */
    symbol = sym_lookup_symbol (config, type);
    if (symbol)
        symbol = symbol-> next;         /*  Start with first section entry   */

    /*  Copy URI to buffer, remove leading / if any, and normalise it        */
    if (*uri == '/')
        uri++;
    strcpy (buffer, uri);
    strlwc (buffer);                    /*  All comparisons in lowercase     */

    /*  This loop is inefficient: it should look for aliases by taking the
        entire URL except the last component and successively dropping
        components until there is a match, or not.   --  PH 98/06/24
     */

    while (symbol && strprefixed (symbol-> name, type))
      {
        /*  Skip 'type:' and '/' at start of alias for matching              */
        alias_name = symbol-> name + strlen (type) + 1;
        if (*alias_name == '/')
            alias_name++;

        /*  Alias should match start of URI, following '/' or null           */
        if (strprefixed (buffer, alias_name))
          {
            base_char = (char *) uri + strlen (alias_name);
            if (*base_char == '/' || *base_char == '\0')
              {
                if (base)               /*  Return base if necessary         */
                    *base = base_char;
                return (symbol);
              }
          }
        symbol = symbol-> next;
      }
    return (NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_match_wsx

    Synopsis: Checks whether the URI matches a WSX agent pattern.  If so,
    returns the name of the WSX agent that should handle the request.  If
    not, returns NULL.  WSX agents must be linked with the main server.
    Static WSX agents are defined in the config file under [WSX] as
    "name=pattern", and can be limited to specific virtual hosts.  Dynamic
    WSX agents can send WSX_INSTALL messages to install WSX aliases.
    Static definitions take precedence over dynamic definitions.

    When a WSX agent is found, sets the p_http-> wsx_agent to point to the
    agent name, and path_info to contain the URL part following the alias,
    if any.
    ---------------------------------------------------------------------[>]-*/

char *
http_match_wsx (HTTP_CONTEXT *p_http)
{
    SYMBOL
        *symbol;
    char
        *info,                          /*  Anything following alias         */
        *value = NULL;                  /*  Symbol value                     */

    ASSERT (wsx_aliases);

    /*  Try static WSX aliases first                                         */
    symbol = http_match_alias (p_http-> config, p_http-> url, "wsx", &info);
    if (symbol == NULL)
      {
        /*  Now try dynamic WSX aliases for current virtual host             */
        symbol = http_match_alias (wsx_aliases, p_http-> url,
                                   p_http-> vhost, &info);
        if (symbol == NULL && p_http-> uses_vhost)
            /*  Now try dynamic WSX aliases for default virtual host         */
            symbol = http_match_alias (wsx_aliases, p_http-> url,
                                       VHOST_ANY, &info);
      }
    if (symbol)
        value = symbol-> value;
    else
    /*  Look for WSX specified by file extension                             */
    if (p_http-> url_ext)
      {
        value = ini_dyn_value (p_http-> config, "wsx",
                               p_http-> url_ext, NULL);
        if (value == NULL)
          {
            /*  Now try dynamic WSX aliases for current virtual host         */
            value = ini_dyn_value (wsx_aliases, p_http-> vhost,
                                   p_http-> url_ext, NULL);
            /*  Now try dynamic WSX aliases for default virtual host         */
            if (value == NULL && p_http-> uses_vhost)
                value = ini_dyn_value (wsx_aliases, VHOST_ANY,
                                       p_http-> url_ext, NULL);
          }
        if (value)
            info = p_http-> url;
      }
    /*  Set-up WSX environment correctly                                     */
    if (value)
      {
        mem_strfree (&p_http-> wsx_agent);
        mem_strfree (&p_http-> path_info);
        mem_strfree (&p_http-> file_name);
        p_http-> wsx_agent = mem_strdup (value);
        p_http-> path_info = mem_strdup (info);
        p_http-> file_name = mem_strdup (p_http-> url);
        return (value);                 /*  Return name of WSX agent         */
      }
    else
        return (NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_wsx_symbols

    Synopsis: Prepares an environment table for a WSX agent and returns
    it as a DESCR block.  The environment table corresponds to the CGI
    environment block (see add_cgi_environment()).  The caller must use
    mem_free() to release the block when finished.  Returns NULL if there
    was insufficient memory to allocate the block, and sets the http
    error_type and response appropriately.
    ---------------------------------------------------------------------[>]-*/

DESCR *
http_wsx_symbols (HTTP_CONTEXT *p_http)
{
    SYMTAB
        *symtab;                        /*  Environment symbol table         */
    char
        **symenv;                       /*  Formatted as environment         */
    DESCR
        *symdesc;                       /*  Formatted as descriptor          */

    /*  Fill in members of p_http that add_cgi_environment() looks for       */
    mem_strfree (&p_http-> script_name);
    mem_strfree (&p_http-> script_path);
    p_http-> script_name = mem_strdup (p_http-> url);
    p_http-> script_path = mem_strdup ("");

    symtab = add_cgi_environment (p_http, FALSE);
    if (symtab)
      {
        /*  Convert symbols names to uppercase, hyphens to underlines        */
        symenv  = symb2env   (symtab);
        symdesc = strt2descr (symenv);
        sym_delete_table (symtab);
        strtfree (symenv);
        if (symdesc)
            return (symdesc);
      }
    p_http-> error_type = ERROR_CGI_NORESOURCES;
    p_http-> response   = HTTP_RESPONSE_INTERNALERROR;
    return (NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_check_file

    Synopsis: Checks that a specified file exists and is readable.  Returns
    one of these values:
    <Table>
    HTTP_FILE_OK            File exists and is readable.
    HTTP_FILE_EXECUTABLE    File exists and is executable.
    HTTP_FILE_DIRECTORY     File is a directory
    HTTP_FILE_NOT_FOUND     File not found
    HTTP_FILE_NOT_OK        Some other error occurred
    </TABLE>
    ---------------------------------------------------------------------[>]-*/

int
http_check_file (HTTP_CONTEXT *p_http)
{
    time_t
        file_time;

    ASSERT (p_http);

    /*  Translate URL into local file name                                   */
    http_get_file_name (p_http);
    if (p_http-> file_name == NULL)
      {
        trace ("- insufficient memory");
        p_http-> response = HTTP_RESPONSE_OVERLOADED;
        return (HTTP_FILE_NOT_OK);
      }

    file_time = get_file_time (p_http-> file_name);
    p_http-> file_date = timer_to_date (file_time);
    p_http-> file_time = timer_to_time (file_time);

    /*  First check that the requested filename is legal on this system.     */
    if (!file_is_legal (p_http-> file_name)
    && *HCONFIG ("security:safepaths") == '1')
      {
        trace ("- request refers to an illegal filename");
        p_http-> response = HTTP_RESPONSE_FORBIDDEN;
        return (HTTP_FILE_NOT_OK);
      }

    /*  First Handle CGI requests.  If the file is an executable program,
     *  we can handle it.  Note that this takes precedence over a directory
     *  with the same name.  If the file is a non-executable file, and the
     *  cgi:mixed_url allows it, we'll send that file.
     */
    if (p_http-> transaction == TRANSACTION_CGI)
      {
        if (file_is_executable (p_http-> file_name))
          {
            trace ("- CGI request refers to an executable file");
            p_http-> response = HTTP_RESPONSE_OK;
            return (HTTP_FILE_EXECUTABLE);
          }
        if (file_is_readable  (p_http-> file_name)
        && !file_is_directory (p_http-> file_name)
        && *HCONFIG ("cgi:mixed-url") == '1')
          {
            trace ("- CGI request refers to a resources file");
            p_http-> response    = HTTP_RESPONSE_OK;
            p_http-> transaction = TRANSACTION_FILE;
            return (HTTP_FILE_OK);
          }
      }

    /*  If the URL is a directory ending in '/' we can handle it.  If it's
     *  a directory without the '/', we send back a 302, so that the browser
     *  will ask for the full directory name...
     */
    if (file_is_directory (p_http-> file_name))
      {
        if (strlast (p_http-> url) == '/')
          {
            trace ("- request refers to a directory name");
            p_http-> transaction = TRANSACTION_FILE;
            return (HTTP_FILE_DIRECTORY);
          }
        else
          {
            /*  Format directory name including trailing slash              */
            format_full_url (p_http, buffer, p_http-> url, "/");
            mem_strfree (&p_http-> url);
            p_http-> url = mem_strdup (buffer);

            /*  Now generate a 302 'error' response                          */
            trace ("- request redirected to %s", buffer);
            p_http-> response    = HTTP_RESPONSE_FOUND;
            p_http-> transaction = TRANSACTION_FILE;
            return (HTTP_FILE_NOT_OK);
          }
      }

    /*  Finally, check that the URL refers to a normal readable file         */
    if (file_is_readable (p_http-> file_name))
      {
        trace ("- request refers to a normal readable file");
        p_http-> response = HTTP_RESPONSE_OK;
        return (HTTP_FILE_OK);
      }
    else
      {
        trace ("- requested file '%s' not found", p_http-> file_name);
        p_http-> response = HTTP_RESPONSE_NOTFOUND;
        return (HTTP_FILE_NOT_FOUND);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_get_file_name

    Synopsis: Builds a filename for the current URL, with full path
    information.  Places the filename in the HTTP_CONTEXT file_name field.
    Allocates a new string for the filename.  Returns a pointer to the
    filename string, or NULL if there was insufficient memory.
    ---------------------------------------------------------------------[>]-*/

char *
http_get_file_name (HTTP_CONTEXT *p_http)
{
    char
        *pathinfo,                      /*  Presumed path info data          */
        *execname,                      /*  Points to executable filename    */
        *alternate;                     /*  Alternative, if necessary        */

    ASSERT (p_http);
    ASSERT (p_http-> url);

    /*  These strings are normally NULL already, but they may be set if we're
     *  handling a redirection from a CGI program.
     */
    mem_strfree (&p_http-> path_info);
    mem_strfree (&p_http-> script_path);
    mem_strfree (&p_http-> script_name);
    mem_strfree (&p_http-> file_name);

    p_http-> file_name = http_map_uri (p_http-> config,
                                       p_http-> rootdir,
                                       p_http-> cgidir,
                                       p_http-> url,
                                       HCONFIG ("server:cgi-url"));

    /*  We now split the CGI URI into an executable filename and the path
     *  info that follows, if any.  We do this by removing components from
     *  the path until it is a valid directory.  The component that follows
     *  must be the executable filename, and anything else is the path info.
     */
    if (p_http-> transaction == TRANSACTION_CGI)
      {
        /*  Start with pathinfo set to the trailing null, and execname to
         *  the previous component.  Then work backwards through the path.
         */
        pathinfo = p_http-> file_name + strlen (p_http-> file_name);
        execname = strrchr (p_http-> file_name, '/');
        while (execname)
          {
            *execname = '\0';           /*  Cut path before filename         */
            if (file_is_directory (p_http-> file_name))
              {
                mem_strfree (&p_http-> path_info);
                p_http-> path_info   = mem_strdup (pathinfo);
                *pathinfo = '\0';       /*  Cut file_name at delimiter       */

                mem_strfree (&p_http-> script_path);
                p_http-> script_path = mem_strdup (p_http-> file_name);

                /*  Script name is original URI without path info            */
                mem_strfree (&p_http-> script_name);
                p_http-> script_name = mem_strdup (p_http-> url);
                p_http-> script_name [strlen (p_http-> url)
                                    - strlen (p_http-> path_info)] = '\0';
                *execname = '/';        /*  Restore path to original state   */
                break;
              }
            pathinfo = execname;
            execname = strrchr (p_http-> file_name, '/');
            *pathinfo = '/';            /*  Restore path to original state   */
          }
      }
    else
    if (p_http-> transaction == TRANSACTION_FILTER)
      {
        p_http-> script_name = mem_strdup (http_get_filter (p_http));
        p_http-> path_info   = mem_strdup ("");
        /*  If the filter name has a path, save in script_path               */
        if (strrchr (p_http-> file_name, '/'))
          {
            p_http-> script_path = mem_strdup (p_http-> file_name);
            *strrchr (p_http-> script_path, '/') = '\0';
          }
        else
            p_http-> script_path = mem_strdup ("");
      }
    /*  Consider alternative files if URL does not end in a slash            */
    if (strlast (p_http-> file_name) != '/'
    && !file_is_readable   (p_http-> file_name)
    && !file_is_executable (p_http-> file_name))
      {
        alternate = look_for_alternate (p_http, p_http-> file_name);
        if (alternate)
          {
            mem_free (p_http-> file_name);
            p_http-> file_name = alternate;
          }
      }
    return (p_http-> file_name);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_map_uri

    Synopsis: Maps an URL into an internal physical filename with full path
    information.  Returns a pointer to a newly-allocated buffer containing
    the name, or NULL if there was a problem.  The mapping algorithm is as
    follows:

    1.  If the URI is a WSX URI, it is returned unchanged.

    2.  Any alias string at the start of the URI is replaced by the
        value of the alias.  Aliases are not case-dependent.

    3.  If the URI starts with server:cgi_url (/cgi-bin) then we take the
        following text and append this to the current CGI directory name.
        This cannot be combined with aliasing: if we attach the CGI dir
        to the result of an alias we get garbage.

    4.  Otherwise we prefix the root directory.
    ---------------------------------------------------------------------[>]-*/

char *
http_map_uri (
    SYMTAB *config,
    const char *rootdir,
    const char *cgidir,
    const char *uri,
    const char *cgi_url)
{
    char
        *full_name,                     /*  Name we build                    */
        *uri_base,                      /*  URI following alias, if any      */
        *local_root,                    /*  What root dir do we use?         */
        *slash;                         /*  We may need a / delimiter        */
    SYMBOL
        *alias;                         /*  Alias symbol pointer             */

    ASSERT (config);
    ASSERT (uri);

    trace ("Resolving URI: %s", uri);

    /*  Check for WSX URIs - these are not mapped                            */
    /*  This function does not handle dynamic WSXs correctly...              */
    if (http_match_alias (config, (char *) uri, "wsx", NULL))
        return (mem_strdup (uri));

    /*  Alias from Outer Space!
     *  Resolve any aliases used in the URI.  We take the URI path and see
     *  if it is a known alias. If so, we replace that by the alias value.
     *  Aliases are lowercase.
     */
    /*  We look for CGI aliases first; these take precedence                 */
    alias = http_match_alias (config, uri, "cgi-alias", &uri_base);

    /*  If that did not find anything, try an ordinary alias                 */
    if (alias == NULL)
        alias = http_match_alias (config, uri, "alias", &uri_base);

    if (alias)
      {
        /*  Get alias path, and clean it up                                  */
        trace ("- using alias: %s=%s", alias-> name, alias-> value);
        local_root = alias-> value;
      }
    else                                /*  No alias: use normal rootdir     */
      {
        uri_base   = (char *) uri;
        local_root = (char *) rootdir;
      }
    /*  If URI matches the CGI directory, construct full filename thus:
     *  1. If URI starts with "/cgi-bin", take text following "/cgi-bin"
     *     and append to specified cgidir path.
     *  2. If URI does not start with "/cgi-bin", prefix root directory.
     *     URI following alias is always in alias location, obviously.
     *  Note that cgidir and rootdir DO NOT end in '/'.
     */
    if (!alias
    &&  strprefixed (uri_base, cgi_url)
    &&  uri_base [strlen (cgi_url)] == '/')
      {
        /*  File is in specific CGI directory                                */
        uri_base += strlen (cgi_url);
        local_root = (char *) cgidir;
        trace ("- in specific CGI directory %s", cgidir);
      }
    else
        trace ("- URL is in webpages directory %s", local_root);

    /*  Translate any environment symbols in the root                        */
    trace ("- URI=%s, rootdir=%s", uri_base, local_root);

#if (defined (MSDOS_FILESYSTEM))
    /*  Simplify the code by using / as path delimiter                       */
    strconvch (local_root, '\\', '/');
#endif
    local_root = resolve_path (local_root);
    if (strlast (local_root) == '/')
        strlast (local_root) = '\0';    /*  Kill slash after local root      */

    /*  We need a slash between the root and the URI only if the URI is not
     *  empty, and does not start with a slash itself.
     */
    if (strnull (uri_base) || *uri_base == '/')
        slash = "";
    else
        slash = "/";

    xstrcpy_debug ();
    full_name = xstrcpy (NULL, local_root, slash, uri_base, NULL);
    trace ("- translated file name: %s", full_name);
    return (full_name);
}


/*  ---------------------------------------------------------------------[<]-
    Function: look_for_alternate -- internal

    Synopsis: When a requested HTML file is not found, looks for alternate
    files by trying .htm in place of .html and vice-versa, and using the
    Accept-Language header, if any.  If an alternative file is found, returns
    a freshly-allocated string containing the filename, else returns NULL.
    ---------------------------------------------------------------------[>]-*/

static char *
look_for_alternate (HTTP_CONTEXT *p_http, char *old_name)
{
    char
        *accept,                        /*  Accept-Languages values          */
        **tokens,                       /*    and broken into tokens         */
        *new_name,                      /*  Full filename                    */
        *extension,                     /*  Old filename extension           */
        *alt_ext_1,                     /*  Alternate extension 1            */
        *alt_ext_2;                     /*  Alternate extension 2            */
    int
        index;                          /*  Index into language list         */

    old_name = mem_strdup (old_name);   /*  First, make a copy               */
    if (file_is_readable (old_name))
        return (old_name);

    /*  We'll try either .htm/.html for HTML files; anything else must match
     */
    trace ("Look for alternatives for: %s", old_name);
    new_name  = NULL;
    extension = strrchr (old_name, '.');
    if (extension == NULL)
      {
        alt_ext_1 = "";
        alt_ext_2 = NULL;
      }
    else
      {
        if (streq (extension, ".htm")
        ||  streq (extension, ".html"))
          {
            alt_ext_1 = "htm";
            alt_ext_2 = "html";
          }
        else
          {
            alt_ext_1 = extension + 1;
            alt_ext_2 = NULL;
          }
        *extension = '\0';              /*  Cut filename at extension        */
      }

    /*  First try alternate extension, if we figured we wanted one.          */
    if (alt_ext_2)
      {
        new_name = try_alt_name (old_name, alt_ext_1, NULL);
        if (!new_name)
            new_name = try_alt_name (old_name, alt_ext_2, NULL);
      }
    /*  If Accept-Language header was supplied, we may have the document
     *  in one of the user-specified languages.  This header holds a list of
     *  accepted languages, e.g. "en, fr;q=.8, de".  We ignore the quality
     *  specifiers, if any.
     */
    accept = mem_strdup (http_header_value (p_http, "accept-language"));
    strconvch (accept, ',', ' ');       /*  Use spaces to delimit tokens     */
    tokens = tok_split (accept);
    for (index = 0; tokens [index]; index++)
      {
        if (new_name)                   /*  May be set before we enter       */
            break;
        new_name = try_alt_name (old_name, alt_ext_1, tokens [index]);
        if (!new_name && alt_ext_2)
            new_name = try_alt_name (old_name, alt_ext_2, tokens [index]);
      }
    tok_free (tokens);
    mem_free (accept);
    mem_free (old_name);
    return (new_name);
}


/*  ---------------------------------------------------------------------[<]-
    Function: try_alt_name -- internal

    Synopsis: Tries to find a filename using the specified extension and
    alternate language code.  Returns an allocated string if found, else
    returns NULL.  The extension and/or language may be empty or NULL.
    ---------------------------------------------------------------------[>]-*/

static char *
try_alt_name (char *filename, char *ext, char *language)
{
    char
        *new_name,
        *dot;

    if (ext && *ext)
        dot = ".";
    else
        dot = "";

    if (language && *language)
      {
        strconvch (language, ';', '\0');     /*  Remove quality information  */
        /*  First try the filename using .xx as language extension           */
        xstrcpy_debug ();
        new_name = xstrcpy (NULL, filename, dot, ext, ".", language, NULL);
        trace (" - trying %s", new_name);
        if (file_is_readable (new_name))
            return (new_name);

        /*  Then try the filename using _xx as language extension            */
        new_name [strlen (new_name) - strlen (language) - 1] = '_';
        trace (" - trying %s", new_name);
        if (file_is_readable (new_name))
            return (new_name);
      }
    else
      {                                 /*  No language, just try extension  */
        xstrcpy_debug ();
        new_name = xstrcpy (NULL, filename, dot, ext, NULL);
        trace (" - trying %s", new_name);
        if (file_is_readable (new_name))
            return (new_name);
      }
    mem_free (new_name);
    return (NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_format_full_url -- internal

    Synopsis: Takes an URL and returns a buffer formatted with the host
    name, port, and url.  If the URL already contains a hostname, it is
    returned as-is, otherwise the host name, and the port number if not
    equal to 80 are prefixed: http://hostname[:port]/url.  The suffix, if
    not NULL or empty is attached to the resulting buffer.  
    ---------------------------------------------------------------------[>]-*/

static void
format_full_url (HTTP_CONTEXT *p_http, char *buffer, char *url, char *suffix)
{
    ASSERT (p_http);
    ASSERT (buffer);
    ASSERT (url);

    if (is_full_url (url))
        strcpy (buffer, url);
    else
      {
        if (p_http-> port == 80)
            sprintf (buffer, "http://%s",    http_hostname (p_http));
        else
            sprintf (buffer, "http://%s:%d", http_hostname (p_http),
                                             p_http-> port);
        if (url [0] != '/')
            strcat (buffer, "/");
        strcat (buffer, url);
        if (suffix && *suffix)
            strcat (buffer, suffix);    /*  Add suffix if necessary          */
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_hostname -- internal

    Synopsis: Returns a static string containing the name of the host that
    made the request.  By preference it takes the value of the Host: HTTP
    header field; if that is missing, uses the server:hostname variable.
    Removes any :port suffix from the hostname.
    ---------------------------------------------------------------------[>]-*/

static char *
http_hostname (HTTP_CONTEXT *p_http)
{
    char
        *hostname;

    hostname = http_header_value (p_http, "host");
    if (strnull (hostname))
        hostname = HCONFIG ("server:hostname");
       
    if (strnull (hostname))
        hostname = get_hostname ();

    if (strchr (hostname, ':'))
       *strchr (hostname, ':') = '\0';

    return (hostname);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_format_header

    Synopsis: Formats a HTTP response header.  Does not output MIME
    information.  Places the formatted header into the buffer argument
    which should be at least HTTP_BUFFERMIN characters long.  Returns
    buffer.
    ---------------------------------------------------------------------[>]-*/

char *
http_format_header (HTTP_CONTEXT *p_http, char *header)
{
    time_t
        file_time;
    char
        size_field [32];

    ASSERT (p_http);
    ASSERT (header);

    /*  Handle the special cases first.  If we just ran a CGI that built     */
    /*  a complete header, our own header is empty.                          */
    if (p_http-> cgi_header)
      {
        strclr (header);
        return (header);
      }
    if (p_http-> cgi_status == NULL)
        sprintf (header, "HTTP/1.0 %s %s\r\n",
                          http_response [p_http-> response].code,
                          http_response [p_http-> response].name);
    else
        /*  CGI program provided Status: field                               */
        sprintf (header, "HTTP/1.0 %s\r\n", p_http-> cgi_status);

    switch (p_http-> response)
      {
        case HTTP_RESPONSE_OK:
            if ((p_http-> file_time == 0 || p_http-> file_date == 0)
            &&  (p_http-> file_name
            &&   p_http-> transaction != TRANSACTION_WSX))
                  {
                    file_time = get_file_time (p_http-> file_name);
                    p_http-> file_date = timer_to_date (file_time);
                    p_http-> file_time = timer_to_time (file_time);
                  }
            if (p_http-> file_size == 0
            &&  p_http-> file_name)
                p_http-> file_size = get_file_size (p_http-> file_name);
        
            if (p_http-> transaction == TRANSACTION_CGI
            ||  p_http-> transaction == TRANSACTION_FILTER
            ||  p_http-> transaction == TRANSACTION_WSX)
              {
                put_dynamic_headers (p_http, header);
                xstrcat (header,
                    "Server: ",
                        server_name, eoln,
                    NULL);
              }
            else
              {
                sprintf (size_field, "%ld", p_http-> file_size);
                xstrcat (header,
                    "Server: ",
                        server_name, eoln,
                    "Content-Type: ",
                        http_get_mime_type (p_http, p_http-> url_ext), eoln,
                    "Content-Length: ",
                        size_field, eoln,
                    "Last-Modified: ",
                        encode_mime_time (p_http-> file_date,
                                          p_http-> file_time), eoln,
                    NULL);
              }
            if (p_http-> keep_alive)
              {
                sprintf (buffer, "timeout=%d, max=%d",
                         p_http-> input_timeout, p_http-> keep_alive_max);
                xstrcat (header,
                    "Connection: ",
                        "Keep-Alive", eoln,
                    "Keep-Alive: ",
                        buffer, eoln,
                    NULL);
              }
            strcat (header, eoln);      /*  End header with a blank line     */
            break;

        case HTTP_RESPONSE_FOUND:
            put_dynamic_headers (p_http, header);
            format_full_url (p_http, buffer, p_http-> url, NULL);
            xstrcat (header,
                "Server: ",
                    server_name, eoln,
                "Location: ",
                    buffer, eoln,
                eoln,                   /*  End header with a blank line     */
                NULL);
            break;

        case HTTP_RESPONSE_UNAUTHORIZED:
            xstrcat (header,            /*  If we set the realm, use that,   */
                "WWW-Authenticate: ",   /*    else use the URL               */
                    "Basic realm=\"",
                    p_http-> realm? p_http-> realm: p_http-> url,
                    "\"", eoln,
                    NULL);
            format_error_header (p_http, header);
            break;

        default:
            /*  Anything >= 400 is an error                                  */
            format_error_header (p_http, header);
            if (p_http-> response >= HTTP_RESPONSE_BADREQUEST)
                error_count++;          /*  Maintain statistics              */
      }
    return (header);
}


static void
put_dynamic_headers (HTTP_CONTEXT *p_http, char *header)
{
    SYMBOL
        *symptr;                        /*  Header field symbol              */
    char
        *char_ptr;
    Bool
        set_upper;
    char
        size_field [32];

    if (!sym_lookup_symbol (p_http-> table, "content-type"))
        sym_assume_symbol (p_http-> table, "content-type", "text/html");

    if (!sym_lookup_symbol (p_http-> table, "content-length"))
      {
        sprintf (size_field, "%ld", p_http-> file_size);
        sym_assume_symbol (p_http-> table, "content-length", size_field);
      }
    /*  Add headers, converting to mixed case                                */
    for (symptr = p_http-> table-> symbols; symptr; symptr = symptr-> next)
      {
        set_upper = TRUE;
        for (char_ptr = symptr-> name; *char_ptr; char_ptr++)
          {
            if (*char_ptr == '-')
                set_upper = TRUE;
            else
            if (set_upper)
              {
                *char_ptr = toupper (*char_ptr);
                set_upper = FALSE;
              }
          }
        xstrcat (header, symptr-> name, ": ", symptr-> value, eoln, NULL);
      }
}


/*  Formats a error header                                                   */

static void
format_error_header (HTTP_CONTEXT *p_http, char *header)
{
    static char
        length [12];
    char
        *error_header,                  /*  We load error header/footer      */
        *error_footer,                  /*    when we initialise             */
        *error_body,                    /*  Get error message body if any    */
        *error_lookup;                  /*  Key for custom error message     */
    DESCR
        *error_header_descr = NULL,
        *error_footer_descr = NULL,
        *error_body_descr   = NULL;

    /*  Handle 3xx status codes                                              */
    if (p_http-> response < HTTP_RESPONSE_BADREQUEST)
      {
        if (p_http-> keep_alive)
          {
            sprintf (buffer, "timeout=%d, max=%d",
                     p_http-> input_timeout, p_http-> keep_alive_max);
            xstrcat (header,
                "Connection: ",
                    "Keep-Alive", eoln,
                "Keep-Alive: ",
                    buffer, eoln,
                NULL);
          }
        strclr (buffer);                /*  No body for 3xx messages         */
      }
    /*  Handle 4xx and 5xx status codes                                      */
    else
      {
        /*  Get header and footer from file if neccessary                    */
        error_header = HCONFIG ("server:error-header");
        if (error_header [0] == '@')
          {
            error_header_descr = file_slurp (error_header + 1);
            if (error_header_descr)
                error_header = (char *) error_header_descr-> data;
            else
                error_header = "\001";  /*  Error                            */
          }
        error_footer = HCONFIG ("server:error-footer");
        if (error_footer [0] == '@')
          {
            error_footer_descr = file_slurp (error_footer + 1);
            if (error_footer_descr)
                error_footer = (char *) error_footer_descr-> data;
            else
                error_footer = "\001";  /*  Error                            */
          }

        /*  Now look-up "server:text-xxx" in config table                    */
        xstrcpy_debug ();
        error_lookup = xstrcpy (NULL, "server:text-",
                                http_response [p_http-> response].code, NULL);
        error_body = HCONFIG (error_lookup);
        if (error_body [0] == '@')
          {
            error_body_descr = file_slurp (error_body + 1);
            if (error_body_descr)
                error_body = (char *) error_body_descr-> data;
            else
                error_body = "\001";    /*  Error                            */
          }

        /*  Make sure error header/body/footer are not too large together    */
        if (strlen (error_header)
         +  strlen (error_body)
         +  strlen (error_footer) > HTTP_HEADER_MAX - 500)
          {
            error_header =
            error_body   =
            error_footer = "\001";
           }

        /*  Use defaults for header/body/footer if necessary                 */
        if (*error_header == '\001')
            error_header = "<HTML><TITLE>Error</TITLE><BODY><H2>";
        if (*error_footer == '\001')
            error_footer = "</H2></BODY></HTML>";
        if (*error_body == '\001')
            sprintf (buffer, "%s\r\n%s %s: %s\r\n",
                     error_header,
                     protocols     [p_http-> protocol],
                     http_response [p_http-> response].code,
                     http_response [p_http-> response].name);
        else
            sprintf (buffer, "%s\r\n%s\r\n", error_header, error_body);

        if (p_http-> error_type)
          {
            strcat (buffer, "<BR>");
            strcat (buffer, error_msg [p_http-> error_type]);
            p_http-> error_type = 0;
          }
        strcat (buffer, error_footer);
        mem_free (error_lookup);
      }
    sprintf (length, "%d", (word) strlen (buffer));
    xstrcat (header,
        "Server: ",
            server_name, eoln,
        "Content-Length: ",
            length, eoln,
        "Content-Type: text/html",
            eoln,
        eoln, buffer,
        NULL);

    /*  Free and reset descriptors; this does no harm if they are NULL       */
    mem_free (error_header_descr);
    mem_free (error_footer_descr);
    mem_free (error_body_descr);
}


/*  -------------------------------------------------------------------------
    Function: http_get_mime_type - internal

    Synopsis: Returns the MIME type corresponding to the file extension.
    -------------------------------------------------------------------------*/

static char *
http_get_mime_type (HTTP_CONTEXT *p_http, char *extension)
{
    char
        *mime_lookup,
        *mime_type;

    /*  Now look-up "mime:xxx" in config table
     *  We skip the extension's dot if any, and if there is no extension
     *  we use a single dot, which is used to signify 'empty'.
     */
    if (extension && *extension)
      {
        if (*extension == '.')
            extension++;
      }
    else
        extension = ".";

    xstrcpy_debug ();
    mime_lookup = xstrcpy (NULL, "mime:", extension, NULL);
    strlwc (mime_lookup);               /*  Always lower-case                */
    mime_type = HCONFIG (mime_lookup);
    mem_free (mime_lookup);

    /*  Get default MIME type if none was found                              */
    if (strnull (mime_type))
        mime_type = HCONFIG ("mime:default");

    return (mime_type);
}


/*  -------------------------------------------------------------------------
    Function: http_get_filter - internal

    Synopsis: If the file should be handled by a filter, returns filter name.
    Else returns NULL.
    -------------------------------------------------------------------------*/

static char *
http_get_filter (HTTP_CONTEXT *p_http)
{
    char
        *filter_lookup,
        *filter_type;

    if (!p_http-> url_ext)
        return (NULL);

    /*  Now look-up "filter:.xxx" and "filter:xxx" in config table           */
    xstrcpy_debug ();
    filter_lookup = xstrcpy (NULL, "filter:", p_http-> url_ext, NULL);
    strlwc (filter_lookup);             /*  Always lower-case                */
    filter_type = HCONFIG (filter_lookup);
    mem_free (filter_lookup);

    /*  "filter:xxx" is deprecated form, but still supported                 */
    if (strnull (filter_type))
      {
        xstrcpy_debug ();
        filter_lookup = xstrcpy (NULL, "filter:", p_http-> url_ext + 1, NULL);
        strlwc (filter_lookup);
        filter_type = HCONFIG (filter_lookup);
        mem_free (filter_lookup);
      }
    return (strnull (filter_type)? NULL: filter_type);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_get_default_page

    Synopsis: Gets the default page for the specified URL, as specified in
    the config file for the virtual host.  Returns TRUE if it finds a
    default page.  The default page is placed into the 'url' field, so
    must be reparsed as if it was a new request.  Uses the normal rules for
    locating an alternative page if necessary.
    ---------------------------------------------------------------------[>]-*/

Bool
http_get_default_page (HTTP_CONTEXT *p_http)
{
    static
        char default_key [20];          /*  server:defaultnnn                */
    char
        *default_name;                  /*  Default name from config file    */
    int
        root_size,                      /*  Size of directory root           */
        default_nbr;                    /*  Read from config file?           */

    ASSERT (p_http);

    p_http-> default_page = FALSE;
    for (default_nbr = 1; default_nbr < MAX_DEFAULTS; default_nbr++)
      {
        sprintf (default_key, "server:default%d", default_nbr);
        default_name = HCONFIG (default_key);
        if (strnull (default_name))
            break;
        else
          {
            /*  file_name holds local directory name, maybe ending in '/'     */
            strcpy (buffer, p_http-> file_name);
            if (*buffer && strlast (buffer) != '/')
                strcat (buffer, "/");
            root_size = strlen (buffer);
            strcat (buffer, default_name);

            /*  If file exists, recreate new URL from previous URL plus
             *  default file name
             */
            default_name = look_for_alternate (p_http, buffer);
            if (default_name)
              {
                strcpy (buffer, p_http-> url);
                if (*buffer && strlast (buffer) != '/')
                    strcat (buffer, "/");
                strcat (buffer, default_name + root_size);
                mem_strfree (&p_http-> url);
                p_http-> url          = mem_strdup (buffer);
                p_http-> url_ext      = strrchr (p_http-> url, '.');
                p_http-> default_page = TRUE;
                mem_free (default_name);
                break;
              }
          }
      }
    return (p_http-> default_page);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_check_file_time

    Synopsis: Checks if the file was modified since the last request.  Sets
    the flag 'send_file' to TRUE or FALSE appropriately.
    ---------------------------------------------------------------------[>]-*/

void
http_check_file_time (HTTP_CONTEXT *p_http)
{
    char
        *modified;
    time_t
        time_secs;
    long
        mime_date = 0,
        mime_time = 0;

    ASSERT (p_http);
    ASSERT (p_http-> table);
    ASSERT (p_http-> file_name);

    /*  In some configurations, defaults page caching is a real pain -
     *  so we allow the user to disable this.
     */
    if (p_http-> default_page
    && *HCONFIG ("server:cache-defaults") == '0')
        return;

    if (p_http-> send_file)
      {
        modified = http_header_value (p_http, "if-modified-since");
        if (*modified)
          {
            /*  Get file date and time                                       */
            if (!p_http-> file_date || !p_http->file_time)
              {
                time_secs = get_file_time (p_http-> file_name);
                p_http-> file_date = timer_to_date (time_secs);
                p_http-> file_time = timer_to_time (time_secs);
              }
            decode_mime_time (modified, &mime_date, &mime_time);
            if (p_http-> file_date < mime_date)
                p_http-> send_file = FALSE;
            else
            if (p_http-> file_date == mime_date)
              {
                if (p_http-> file_time <= mime_time )
                  p_http-> send_file = FALSE;
              }
          }
        if (!p_http-> send_file)
            p_http-> response = HTTP_RESPONSE_NOTMODIFIED;
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_get_url_in_map

    Synopsis: Gets the URL from the image map file.  If a valid URL was
    found, returns TRUE, else returns FALSE.
    ---------------------------------------------------------------------[>]-*/

Bool
http_get_url_in_map (HTTP_CONTEXT *p_http)
{
    char
        *url_map;                       /*  URL for image map                */

    ASSERT (p_http);

    http_get_file_name (p_http);
    url_map = get_map_value (p_http-> file_name, p_http-> url_param);
    if (url_map)
      {
        mem_strfree (&p_http-> url);
        mem_strfree (&p_http-> url_param);
        mem_strfree (&p_http-> file_name);

        /*  Return 302 to browser so that it specifically asks for the       */
        /*  URL; this means that relative addressing will work from there    */
        /*  on.  Also, the data in the log file will be correct.             */
        format_full_url (p_http, buffer, url_map, NULL);
        p_http-> response = HTTP_RESPONSE_FOUND;
        p_http-> url      = mem_strdup (buffer);
        return (TRUE);
      }
    else
      {
        p_http-> response = HTTP_RESPONSE_NOTFOUND;
        return (FALSE);
      }
}


/*  -------------------------------------------------------------------------
    Function: get_map_value - Internal

    Synopsis: Returns a URL in function of a point in the map.  Uses a map
    file in NCSA format.  Returns a static pointer to an URL name if one
    was found, else returns NULL.  The point is supplied as a string
    formatted like this: "X,Y" - e.g. "120,12".  The map file must be fully
    specified.
    -------------------------------------------------------------------------*/

static char *
get_map_value (
    char *map_file,                     /*  Name of map file                 */
    char *request_point                 /*  Point coordinates                */
)
{
    static char
        url         [LINE_MAX],         /*  Buffer to store URL              */
        default_url [LINE_MAX];         /*  Default URL value for the map    */
    char
        *full_uri;                      /*  Full URI                         */
    FILE
        *file;
    int
        point_x = 0,                    /*  Used only for sscanf             */
        point_y = 0;

    ASSERT (map_file);

    strclr (url);
    strclr (default_url);
    file = file_open (map_file, 'r');
    if (file)
      {
        /*  Get the coodinates of point                                      */
        if (request_point)
            sscanf (request_point, "%d,%d", &point_x, &point_y);

        /*  Note: The first line of map sets the value url_def               */
        while (file_readn (file, buffer, HTTP_URL_MAX))
          {
            /*  Ignore comments and blank lines                              */
            if ((buffer [0] == '#') || strnull (buffer))
                continue;
            point_in_map_element (buffer, url, point_x, point_y, default_url);
            if (strused (url))
                break;
           }
        /*  If not found a URL, set the return with the default value        */
        if (strnull (url))
            strcpy (url, default_url);

        file_close (file);
      }

    /*  Return final URL string, or NULL if we did not find anything         */
    if (strused (url))
      {
        full_uri = build_full_url (url, map_file);
        strcpy (url, full_uri);
        mem_free (full_uri);
        return (url);
      }
    else
        return (NULL);
}


/*  -------------------------------------------------------------------------
    Function: point_in_map_element - Internal

    Synopsis: Check if the requested point is in the element.
              The syntax of each map line is:
                  <Type of element> <URL> <x,y>...
              Each item must be separated by 1 or more spaces.
              Element is point, rectangle, circle, polygon, or default.
              Example:
              poly /test.htm 49,6 93,16 88,50
    -------------------------------------------------------------------------*/

static void
point_in_map_element (char *line, char *return_url, int point_x, int point_y,
                      char *default_url)
{
    char
        **tokens,                       /*  Line split into tokens           */
        *map_type,                      /*  Element type name                */
        *map_url,                       /*  Element URL value                */
        *comma;                         /*  Split x,y at comma               */
    FPOINT
        click_point,                    /*  Request point                    */
        shape_points [MAP_MAX_POINTS];  /*  Array of element point           */
    int
        token_nbr,                      /*  Index into token array           */
        nbr_points;                     /*  Number of points in element      */

    /*  Store selected point in image                                        */
    click_point.x = (double) point_x;
    click_point.y = (double) point_y;

    /*  Now parse the map file line into space-delimited tokens              */
    tokens = tok_split (line);

    /*  Ignore anything which is unparsable                                  */
    if (tokens [0] == NULL || tokens [1] == NULL)
      {
        tok_free (tokens);              /*  Release memory                   */
        return;
      }

    /*  First token is image element type; second is the URL                 */
    map_type = strlwc (tokens [0]);
    map_url  = tokens [1];

    /*  Third to n tokens are x,y pairs...                                   */
    token_nbr = 2;
    for (nbr_points = 0; nbr_points < MAP_MAX_POINTS; nbr_points++)
      {
        if (!tokens [token_nbr])
            break;                      /*  Null token => finished           */
        comma = strchr (tokens [token_nbr], ',');
        if (!comma)
            break;                      /*  Syntax error in line => quit     */
        *comma = '\0';                  /*  Else break into separate x & y   */
        shape_points [nbr_points].x = atof (tokens [token_nbr]);
        shape_points [nbr_points].y = atof (comma + 1);
        token_nbr++;                    /*  Bump to next token               */
      }

    /*  Check element type and test the request point                      */
    if (streq (map_type, "poly"))
      {
        if (point_in_poly (&click_point, shape_points, nbr_points))
            strcpy (return_url, map_url);
      }
    else
    if (streq (map_type, "circle"))
      {
        if (point_in_circle (&click_point, shape_points))
            strcpy (return_url, map_url);
      }
    else
    if (streq (map_type, "rect"))
      {
        if (point_in_rect (&click_point, shape_points))
            strcpy (return_url, map_url);
      }
    else
    if (streq (map_type, "point"))
      {
        double dist;
        dist = ((click_point.x - shape_points [0].x)
             *  (click_point.x - shape_points [0].x))
             + ((click_point.y - shape_points [0].y)
             *  (click_point.y - shape_points [0].y));
       if (dist < 10)
          strcpy (return_url, map_url);
      }
    else
    if (streq (map_type, "default"))
        strcpy (default_url, map_url);

    tok_free (tokens);                  /*  Release memory                   */
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_list_directory

    Synopsis: Make a temporary html file with directory listing.
    ---------------------------------------------------------------------[>]-*/

Bool
http_list_directory (
    HTTP_CONTEXT *p_http)
{
    static char
        filedesc [32];                  /*  File size or type                */
    FILE
        *output;
    NODE
        *file_list;
    FILEINFO
        *file_info;
    DIRST
        *dir;                           /*  Current directory entry          */
    size_t
        name_width;
    char
        *delimiter,                     /*  / delimiter in URL               */
        saved_char;                     /*  Character following slash        */

    /*  Load directory listing                                               */
    file_list = load_dir_list (p_http-> file_name, HCONFIG ("server:dirsort"));
    if (!file_list)
        return (FALSE);

    /*  Open temporary output file for HTML directory listing                */
    sprintf (buffer, "tmp%05ld", p_http-> socket);
    mem_strfree (&p_http-> file_name);
    p_http-> file_name = mem_strdup (
        file_where ('s', HCONFIG ("server:temp-dir"), buffer, "htm"));
    p_http-> url_ext = ".htm";

    output = file_open (p_http-> file_name, 'w');
    if (output == NULL)
      {
        free_dir_list (file_list);
        return (FALSE);
      }
    else
        p_http-> temp_file = TRUE;

    /*  Calculate the longest filename                                       */
    name_width = 20;                    /*  Gives a normal listing           */
    for (file_info  = file_list-> next;
         file_info != (FILEINFO *) file_list;
         file_info  = file_info-> next)
        if (name_width < strlen (file_info-> dir.file_name))
            name_width = strlen (file_info-> dir.file_name);

    fprintf (output,
    "<HTML><BODY><H2>File list of %s directory</H2><PRE>", p_http-> url);
    fprintf (output, "<B>Name%*sSize         Last Modified<BR><HR>",
             (int) (name_width - 4), " ");

    /*  Add entry for parent directory if necessary                          */
    /*  The URL always starts and ends in '/'                                */
    ASSERT (p_http-> url [0] == '/');
    ASSERT (p_http-> url [strlen (p_http-> url) - 1] == '/');

    if (strneq (p_http-> url, "/"))
      {
        delimiter = p_http-> url + strlen (p_http-> url) - 2;
        while (*delimiter != '/')
            delimiter--;
        delimiter++;
        saved_char = *delimiter;
        *delimiter = '\0';
        fprintf (output, "<A HREF=\"%s\">%s</A>\r\n\r\n",
            p_http-> url, p_http-> url);
        *delimiter = saved_char;
      }

    for (file_info  = file_list-> next;
         file_info != (FILEINFO *) file_list;
         file_info  = file_info-> next)
      {
        dir = &file_info-> dir;
        if ((dir-> file_attrs & ATTR_HIDDEN) > 0)
            continue;                   /*  Skip hidden files                */

        sprintf (buffer, "<A HREF=\"%s%s\">%s</A>",
            p_http-> url, dir-> file_name, dir-> file_name);

        strpad (buffer, ' ', strlen (p_http-> url)
                           + strlen (dir-> file_name) + name_width + 15);

        if (file_info-> directory)
            strcpy (filedesc, "Directory    ");
        else
        if (dir-> file_size < 99999)
            sprintf (filedesc, "%5ld bytes  ", (long) dir-> file_size);
        else
          {
            dir-> file_size /= 1024;
            if (dir-> file_size < 99999)
                sprintf (filedesc, "%5ld Kb     ", (long) dir-> file_size);
            else
              {
                dir-> file_size /= 1024;
                sprintf (filedesc, "%5ld Mb     ", (long) dir-> file_size);
              }
          }
        xstrcat (buffer, filedesc,
                 encode_mime_time (timer_to_date (dir-> file_time),
                                   timer_to_time (dir-> file_time)),
                 "\r\n", NULL);
        fprintf (output, "%s", buffer);
      }
    file_write (output, "</PRE>");
    if (*HCONFIG ("server:advertize") == '1')
        file_write (output, POWERED_BY);
    file_write (output, "</BODY></HTML>");
    file_close (output);
    free_dir_list (file_list);

    /*  Register the new URL in the context block                            */
    sprintf (buffer, "/tmp%05ld.htm", p_http-> socket);
    mem_strfree (&p_http-> url);
    p_http-> url = mem_strdup (buffer);

    return (TRUE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_create_cgi_process

    Synopsis: Create cgi environment and process.  Returns 0 if process is
    created, else returns -1.
    ---------------------------------------------------------------------[>]-*/

int
http_create_cgi_process (HTTP_CONTEXT *p_http)
{
    char
        *cgi_stdout,                    /*  CGI stdout filename              */
        *escaped,                       /*  CGI filename, escaped            */
        *command,                       /*  CGI command to execute           */
        *workdir;                       /*  CGI working directory            */
    int
        feedback = 0;
    FILE
        *cgi_stdin_stream;
    SYMTAB
        *symtab;

    /*  Unless we know better, we don't have a precise error cause           */
    p_http-> error_type = ERROR_UNSPECIFIED;

    /*  Make stdin and stdout filenames                                      */
    if (!p_http-> cgi_stdin)            /*  May already be created           */
      {
        p_http-> cgi_stdin = http_pipe (p_http, "cgi");
        cgi_stdin_stream = fopen (p_http-> cgi_stdin, FOPEN_WRITE_BINARY);
        if (cgi_stdin_stream)
          {
            /*  Write POSTed data if present                                 */
            if (p_http-> post_data)
              {
                fwrite (p_http-> post_data, p_http-> post_size, 1,
                        cgi_stdin_stream);
                fwrite ("\n", 1, 1, cgi_stdin_stream);
              }
            file_close (cgi_stdin_stream);
          }
      }
    cgi_stdout = mem_strdup (p_http-> cgi_stdin);
    strlast (cgi_stdout) = 'o';
    /*  Remove old stdout file if any                                        */
    if (file_exists (cgi_stdout))
        file_delete (cgi_stdout);

    /*  Initialise process parameters                                        */
    if ((symtab = add_cgi_environment (p_http, FALSE)) == NULL)
      {
        mem_strfree (&p_http-> cgi_stdin);
        mem_strfree (&cgi_stdout);
        p_http-> error_type = ERROR_CGI_NORESOURCES;
        return (-1);                    /*  Insufficient memory              */
      }

    /*  Set CGI input/output filename symbols                                */
    strcpy (buffer, p_http-> cgi_stdin);
    if (*HCONFIG ("cgi:msdos-style") == '1')
        strconvch (buffer, '/', '\\');
    sym_create_symbol (symtab, "Cgi-Stdin",  buffer);

    strcpy (buffer, cgi_stdout);
    if (*HCONFIG ("cgi:msdos-style") == '1')
        strconvch (buffer, '/', '\\');
    sym_create_symbol (symtab, "Cgi-Stdout", buffer);

    sym_create_symbol (symtab, "Cgi-Stderr", HCONFIG ("cgi:errlog"));

    p_http-> cgi_environ = symb2env (symtab);
    sym_delete_table (symtab);          /*  Get rid of environment table     */
    if (p_http-> cgi_environ == NULL)
      {
        mem_strfree (&p_http-> cgi_stdin);
        mem_strfree (&cgi_stdout);
        p_http-> error_type = ERROR_CGI_NORESOURCES;
        return (-1);                    /*  Insufficient memory              */
      }

    /*  Get the working directory                                            */
    workdir = HCONFIG ("cgi:workdir");
    if (streq (workdir, "-"))           /*  '-' means use script directory   */
        workdir = p_http-> script_path;

    /*  Create the process                                                   */
    process_delay = 0;                  /*  Run process and return at once   */
    escaped = process_esc (NULL, p_http-> file_name);

    /*  If URL arguments contain '=' we pass them in the QUERY_STRING only;
     *  if they do not contain '=' then we split on '+' and pass as args to
     *  the CGI process.
     */
    if ((p_http-> url_param && strchr (p_http-> url_param, '='))
    || *HCONFIG ("cgi:passargs") == '0')
        command = mem_strdup (escaped);
    else
      {
        xstrcpy_debug ();
        command = xstrcpy (NULL, escaped, " ", p_http-> url_param, NULL);
        strconvch (command, '+', ' ');
      }
    /*  Set sflproc flag for separate virtual machines                       */
    /*  This only affects 32-bit Windows systems                             */
    process_compatible = *HCONFIG ("win32:16bit-cgi") == '1';

    if (*HCONFIG ("cgi:stdio") == '1')
        p_http-> cgi_process_id = process_create (
            command,                    /*  Command to run                   */
            NULL,                       /*  Arguments for command            */
            workdir,                    /*  Working directory                */
            p_http-> cgi_stdin,         /*  Redirect stdin from here         */
            cgi_stdout,                 /*  Redirect stdout to here          */
            HCONFIG ("cgi:errlog"),     /*  Redirect stderr to here          */
            p_http-> cgi_environ,       /*  Environment table                */
            FALSE);                     /*  Wait until finished?             */
    else
        p_http-> cgi_process_id = process_create (
            command,                    /*  Command to run                   */
            NULL,                       /*  Arguments for command            */
            workdir,                    /*  Working directory                */
            NULL,                       /*  Redirect stdin from here         */
            NULL,                       /*  Redirect stdout to here          */
            NULL,                       /*  Redirect stderr to here          */
            p_http-> cgi_environ,       /*  Environment table                */
            FALSE);                     /*  Wait until finished?             */

    mem_free (command);
    mem_free (escaped);
    if (p_http-> cgi_process_id == NULL_PROCESS)
      {
        p_http-> error_type = ERROR_CGI_PROCESSNF;
        feedback = -1;                  /*  Could not create the process     */
      }
    else
      {
        mem_strfree (&p_http-> file_name);
        p_http-> file_name = cgi_stdout;
        p_http-> temp_file = TRUE;
      }
    return (feedback);
}


/*  -------------------------------------------------------------------------
    Function: add_cgi_environment - Internal

    Synopsis: Loads CGI environment variables into a symbol table, and
    returns that symbol table.  Returns NULL if there was a problem, e.g.
    insufficient free memory.  Creates these symbols:

      - Unless cgi:environment=0, loads process environment.
      - Loads all values under [CGI-Environment] section
      - For each HTTP header field, inserts a symbol called HTTP_xxxx
        where xxxx is the header field name.  The field names are put
        into uppercase, and hyphens replaced by underlines.  This is
        controlled by the cgi:http_fields configuration option.
      - For each variable in the query string, inserts a symbol called
        FORM_xxxx where xxxx is the variable name.
      - SERVER_SOFTWARE is the name of the web server (the global variable
        server_name).
      - SERVER_VERSION is the server version in use.
      - SERVER_URL holds the full URL back to the server.
      - SERVER_NAME is the current host name.
      - SERVER_PORT is the port on which the web server is running.
      - SERVER_PROTOCOL is the HTTP version in use (currently "HTTP/1.0").
      - GATEWAY_INTERFACE is the CGI version in use (currently "CGI/1.1").
      - REQUEST_METHOD is the HTTP method used, either "GET" or "POST".
      - CONTENT_TYPE is the Content-Type: HTTP field.
      - CONTENT_LENGTH is the Content-Length: HTTP field.
      - REMOTE_USER is the authorised username, if any, else "-".
      - REMOTE_HOST is the remote host name, equal to REMOTE_ADDR.
      - REMOTE_ADDR is the remote host address, "xxx.xxx.xxx.xxx".
      - SCRIPT_PATH is the path of the script being executed.
      - SCRIPT_NAME is the URI of the script being executed.
      - QUERY_STRING is the GET query string, or POST data.
      - PATH_INFO is any path data following the CGI program name
      - PATH_TRANSLATED is the webpages root with PATH_INFO argument
      - CGI_ROOT is the CGI binary directory
      - CGI_URL is the server:cgi_url value
      - DOCUMENT_ROOT is the main webpages directory
      - Caller also adds CGI_STDOUT, CGI_STDIN, CGI_STDERR.

    The calling function must delete the symbol table when finished with it.
    -------------------------------------------------------------------------*/

#define SET(name,value) \
    sym_assume_symbol (symtab, (name), (value)? value: "")

static SYMTAB *
add_cgi_environment (HTTP_CONTEXT *p_http, Bool filter)
{
    static char
        port_name [20];                 /*  Enough for a 64-bit system       */
    SYMBOL
        *symbol;                        /*  Next symbol in table             */
    SYMTAB
        *symtab;                        /*  Symbol table we create           */
    char
        *cur_dir,                       /*  Current working directory        */
        *full_rootdir,                  /*  Document root directory          */
        *full_cgiroot,                  /*  Full CGI root directory          */
        *path_translated;               /*  PATH_TRANSLATED symbol           */

    ASSERT (p_http);
    ASSERT (p_http-> table);

    /*  Initial symbol table is either from server environment, or empty     */
    if (*HCONFIG ("cgi:environment") == '1')
        symtab = env2symb ();
    else
        symtab = sym_create_table ();

    if (symtab == NULL)
        return (NULL);                  /*  Insufficient memory              */

    /*  Load all symbols from CGI-Environment section                        */
    for (symbol = p_http-> config-> symbols; symbol; symbol = symbol-> next)
        if (strprefixed (symbol-> name, "cgi-environment:"))
            sym_create_symbol (symtab,
                symbol-> name + strlen ("cgi-environment:"),
                symbol-> value);

    /*  Load HTTP header fields into the temporary symbol table.  This is
     *  only done if cgi:http_fields is 1.  Header fields are prefixed by
     *  cgi:http_prefix.
     */
    if (*HCONFIG ("cgi:http-fields") == '1')
        for (symbol = p_http-> table-> symbols; symbol; symbol = symbol-> next)
          {
            xstrcpy (buffer, HCONFIG ("cgi:http-prefix"), symbol-> name, NULL);
            sym_create_symbol (symtab, buffer, symbol-> value);
          }

    /*  Load CGI query into symbol table, if cgi:form_fields is 1.  The
     *  query fields are also passed on stdin, and may be too large to put
     *  into the environment.  Query fields are prefixed by the value of
     *  cgi:form_prefix.
     */
    if (p_http-> post_data
    && *HCONFIG ("cgi:form-fields") == '1')
        cgi_parse_query_vars (symtab, p_http-> post_data,
                                      HCONFIG ("cgi:form-prefix"));
    /*  Format port number as a string                                       */
    sprintf (port_name, "%d", p_http-> ssl_connection? 443: p_http-> port);

    /*  Get webpages and CGI root as an absolute path values                 */
    cur_dir = get_curdir ();
    full_rootdir = mem_strdup (locate_path (cur_dir, p_http-> rootdir));
    strlast (full_rootdir) = '\0';      /*  Remove trailing slash            */
    full_cgiroot = mem_strdup (locate_path (cur_dir, p_http-> cgidir));
    strlast (full_cgiroot) = '\0';      /*  Remove trailing slash            */

    /*  Format PATH_TRANSLATED symbol
     *  For CGIs this is the document root followed by the path_info.
     *  For filters we simulate this: it's the document root followed by
     *  the file being filtered.
     */
    xstrcpy_debug ();
    path_translated = xstrcpy (NULL,
                               full_rootdir,
                               filter? p_http-> url: p_http-> path_info,
                               NULL);

    if (*HCONFIG ("cgi:msdos-style") == '1')
      {
        strconvch (p_http-> script_path, '/', '\\');
        strconvch (p_http-> script_name, '/', '\\');
        strconvch (full_rootdir,         '/', '\\');
        strconvch (full_cgiroot,         '/', '\\');
        strconvch (path_translated,      '/', '\\');
      }
    format_full_url (p_http, buffer, "/", NULL);

    SET ("Server-Software",   server_name);
    SET ("Server-Version",    CUR_VERSION);
    SET ("Server-Name",       http_hostname (p_http));
    SET ("Server-Url",        buffer);
    SET ("Server-Port",       port_name);
    SET ("Server-Protocol",   "HTTP/1.0");
    SET ("Gateway-Interface", "CGI/1.1");
    SET ("Request-Method",    http_methods [p_http-> method]);
    SET ("Script-Path",       p_http-> script_path);
    SET ("Script-Name",       p_http-> script_name);
    SET ("Content-Type",      http_header_value (p_http, "content-type"));
    SET ("Content-Length",    http_header_value (p_http, "content-length"));
    SET ("Remote-User",       p_http-> username? p_http-> username: "-");
    SET ("Remote-Host",       socket_peeraddr (p_http-> socket));
    SET ("Remote-Addr",       socket_peeraddr (p_http-> socket));
    SET ("Path-Info",         p_http-> path_info);
    SET ("Path-Translated",   path_translated);
    SET ("Document-Root",     full_rootdir);
    SET ("Cgi-Root",          full_cgiroot);
    SET ("Cgi-Url",           HCONFIG ("server:cgi-url"));

    /*  If the url_param is set, we put that into Query-String, otherwise we
     *  put-in the post data; this is switched-off by default, since it's not
     *  standard CGI, and can do strange things if the post data is large.
     */
    if (p_http-> url_param)
        SET ("Query-String",  p_http-> url_param);
    else
    if (p_http-> post_data
    && *HCONFIG ("cgi:form-query") == '1')
        SET ("Query-String",  p_http-> post_data);

    mem_free (path_translated);
    mem_free (full_rootdir);
    mem_free (full_cgiroot);
    mem_free (cur_dir);

    return (symtab);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_create_filter_process

    Synopsis: Create filter environment and process.  Returns 0 if process
    is created, else returns -1.
    ---------------------------------------------------------------------[>]-*/

int
http_create_filter_process (HTTP_CONTEXT *p_http)
{
    char
        *filter_stdin,                  /*  Filter input file                */
        *filter_stdout,                 /*  Filter output file               */
        *workdir,                       /*  FIlter working directory         */
        *command;                       /*  Command to execute               */
    FILE
        *cgi_stdin_stream;
    int
        feedback = 0;
    SYMTAB
        *symtab;

    /*  Get the working directory                                            */
    workdir = HCONFIG ("cgi:workdir");
    if (streq (workdir, "-"))           /*  '-' means use script directory   */
        workdir = NULL;

    if (p_http-> method == HTTP_METHOD_GET
    ||  p_http-> method == HTTP_METHOD_HEAD) 
        filter_stdin = p_http-> file_name;
    else
    if (p_http-> method == HTTP_METHOD_POST)
      {
        /*  Make stdin file if POST was used                                 */
        if (!p_http-> cgi_stdin)        /*  May already be created           */
          {
            p_http-> cgi_stdin = http_pipe (p_http, "flt");
            cgi_stdin_stream = fopen (p_http-> cgi_stdin, FOPEN_WRITE_BINARY);
            if (cgi_stdin_stream)
              {
                /*  Write POSTed data if present                             */
                if (p_http-> post_data)
                    fwrite (p_http-> post_data, p_http-> post_size, 1,
                            cgi_stdin_stream);
                file_close (cgi_stdin_stream);
              }
          }
        filter_stdin = p_http-> cgi_stdin;
      }
    else
      {
        trace ("CGI internal error: invalid method %d", p_http-> method);
        p_http-> error_type = ERROR_CGI_INTERNALERROR;
        return (-1);
      }

    /*  Make stdout filename                                                 */
    filter_stdout = http_pipe (p_http, "flt");
    if (file_exists (filter_stdout))
        file_delete (filter_stdout);

    /*  Build command to execute, then script_name is URI                    */
    xstrcpy_debug ();
    command = xstrcpy (NULL, p_http-> script_name,
                        " ", p_http-> file_name, NULL);
    mem_strfree (&p_http-> script_name);
    p_http-> script_name = mem_strdup (p_http-> url);

    /*  Under Windows, some programs may expect paths to contain \ not /     */
    if (*HCONFIG ("cgi:msdos-style") == '1')
        strconvch (command, '/', '\\');

    /*  Initialise process parameters                                        */
    if ((symtab = add_cgi_environment (p_http, TRUE)) == NULL)
      {
        p_http-> error_type = ERROR_CGI_NORESOURCES;
        return (-1);                    /*  Insufficient memory              */
      }

    p_http-> cgi_environ = symb2env (symtab);
    sym_delete_table (symtab);          /*  Get rid of environment table     */
    if (p_http-> cgi_environ == NULL)
      {
        p_http-> error_type = ERROR_CGI_NORESOURCES;
        return (-1);                    /*  Insufficient memory              */
      }

    /*  Set sflproc flag for separate virtual machines                       */
    /*  This only affects 32-bit Windows systems                             */
    process_compatible = *HCONFIG ("win32:16bit-cgi") == '1';
    process_delay      = 0;             /*  Run process and return at once   */

    /*  Create the process                                                   */
    p_http-> cgi_process_id = process_create (
        command,                        /*  Command to run                   */
        NULL,                           /*  Arguments for command            */
        workdir,                        /*  Working directory                */
        filter_stdin,                   /*  Redirect stdin from here         */
        filter_stdout,                  /*  Redirect stdout to here          */
        HCONFIG ("cgi:errlog"),         /*  Redirect stderr to here          */
        p_http-> cgi_environ,           /*  Environment table                */
        FALSE);                         /*  Wait until finished?             */

    mem_free (command);

    if (p_http-> cgi_process_id != NULL_PROCESS)
      {
        mem_strfree (&p_http-> file_name);
        p_http-> error_type = ERROR_UNSPECIFIED;
        p_http-> file_name = filter_stdout;
        p_http-> temp_file = TRUE;
      }
    else
      {
        mem_strfree (&filter_stdout);
        p_http-> error_type = ERROR_CGI_PROCESSNF;
        feedback = -1;                  /*  Could not create the process     */
      }
    return (feedback);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_process_state

    Synopsis: Get the cgi process state; returns one of these values:
    <Table>
    CGI_STATE_RUNNING  Process is in progess
    CGI_STATE_END      Process ended OK
    CGI_STATE_ERROR    Process ended with error
    </Table>
    ---------------------------------------------------------------------[>]-*/

int
http_process_state (HTTP_CONTEXT *p_http)
{
    int
        feedback;

    ASSERT (p_http);

    if (p_http-> cgi_process_id == NULL_PROCESS)
      {
        trace ("CGI internal error: process not created");
        feedback = CGI_STATE_ERROR;
        p_http-> error_type = ERROR_CGI_INTERNALERROR;
      }
    else
        switch (process_status (p_http-> cgi_process_id))
          {
            case PROCESS_RUNNING:
                feedback = CGI_STATE_RUNNING;
                break;
            case PROCESS_ENDED_OK:
            case PROCESS_ENDED_ERROR:
                feedback = CGI_STATE_END;
                break;
            case PROCESS_INTERRUPTED:
                feedback = CGI_STATE_ERROR;
                p_http-> error_type = ERROR_CGI_INTERRUPTED;
                break;
            default:
                trace ("CGI internal error: unknown process state");
                feedback = CGI_STATE_ERROR;
                p_http-> error_type = ERROR_CGI_INTERNALERROR;
          }
    return (feedback);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_close_process

    Synopsis: Terminates the currently-running CGI process; if the process
    already ended normally, just cleans-up.
    ---------------------------------------------------------------------[>]-*/

void
http_close_process (HTTP_CONTEXT *p_http)
{
    ASSERT (p_http);

    if (p_http-> cgi_process_id != NULL_PROCESS)
      {
        if (process_status (p_http-> cgi_process_id) == PROCESS_RUNNING)
            process_kill  (p_http-> cgi_process_id);
        else
            process_close (p_http-> cgi_process_id);

        p_http-> cgi_process_id = NULL_PROCESS;
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_reparse_output

    Synopsis: Scans the CGI output file and executes the server directives
    in the file.  Accepts these standard CGI directives:

        Location: filename
        Location: URL
        Content-Type: what/type
        Status: code

    Ignores the first line if it starts with 'HTTP/'.  If the first line
    does not look like a server directive, the output is returned as type
    text/html.  Returns 1 if the CGI output refers to a new URL, else
    returns 0.  Sets p_http-> file_offset to point to the start of the data
    in the file.
    ---------------------------------------------------------------------[>]-*/

int
http_reparse_output (HTTP_CONTEXT *p_http)
{
    FILE
        *response;                      /*  CGI response file                */
    char
        *separator;                     /*  ':' character in header          */
    int
        feedback = 0;

    ASSERT (p_http);

    /*  Create a new, empty table for the mime values                        */
    http_close_cgi (p_http);
    p_http-> table = sym_create_table ();

    /*  By default we send the full CGI output, as-is                        */
    p_http-> file_offset = 0;
    p_http-> file_size   = get_file_size (p_http-> file_name);
    p_http-> cgi_header  = FALSE;       /*  Assume normal CGI output         */

    /*  Read the output from the CGI program                                 */
    response = file_open (p_http-> file_name, 'r');
    if (response == NULL)               /*  File not accessible?             */
      {
        trace ("Cannot reparse %s: %s", p_http-> file_name, strerror (errno));
        return (0);
      }
    while (file_readn (response, buffer, HTTP_URL_MAX))
      {
        /*  Header ends if we hit a line starting with <HTML>                */
        if (lexncmp (buffer, "<html>", 6) == 0)
            break;

        /*  (Pick-up current file pointer as next possible break)            */
        p_http-> file_offset = ftell (response);

        /*  Or if we found a blank line                                      */
        if (*buffer == '\0')
            break;

        /*  Or if we hit a non-header line or what looks like HTML           */
        separator = strchr (buffer, ':');
        if (separator == NULL || strchr (buffer, '<'))
          {
            p_http-> file_offset = 0;   /*  In which case we send it all     */
            p_http-> cgi_header = strprefixed (buffer, "HTTP/");
            break;
          }
        if (parse_cgi_header (p_http, buffer, separator))
            feedback = 1;
      }
    /*  We transmit the file from the current position onwards               */
    file_close (response);
    if (feedback == 0)
        p_http-> file_size -= p_http-> file_offset;

    /*  If CGI is redirected, release file_name to refer to new URL          */
    if (feedback == 1)
      {
        file_delete (p_http-> file_name);
        mem_strfree (&p_http-> file_name);
        p_http-> temp_file = FALSE;
        p_http-> file_size = 0;
      }
    return (feedback);
}

static Bool
parse_cgi_header (HTTP_CONTEXT *p_http, char *header, char *separator)
{
    /*  Parse the header and place into the symbol table                     */
    *separator = '\0';                  /*  Split at separator               */
    separator++;                        /*    and skip space after ':'       */
    while (*separator == ' ')
        separator++;
    strlwc (header);                    /*  Lowercase the header name        */

    if (streq (header, "location"))
      {
        mem_strfree (&p_http-> cgi_status);
        mem_strfree (&p_http-> url);
        p_http-> url = mem_strdup (separator);

        /*  If 'Location:' is a full URL, return 302 + url to client         */
        if (is_full_url (separator))
            p_http-> response = HTTP_RESPONSE_FOUND;
        else
        if (*separator == '/')          /*  Local URL                        */
          {
            /*  If URL contains '?', split into URL + params                 */
            separator = strchr (p_http-> url, '?');
            if (separator)
              {
                mem_strfree (&p_http-> url_param);
                *separator++ = '\0';
                p_http-> url_param = mem_strdup (separator);
              }
            /*  Check for an extension, and use if present                   */
            p_http-> url_ext = strrchr (p_http-> url, '.');
            return (TRUE);              /*  We need to cycle the dialog      */
          }
        else                            /*  Relative URLs are not allowed    */
            p_http-> response = HTTP_RESPONSE_NOTFOUND;
      }
    else
    if (streq (header, "status"))
      {
        mem_strfree (&p_http-> cgi_status);
        p_http-> cgi_status = mem_strdup (separator);
      }
    else
        sym_create_symbol (p_http-> table, header, separator);

    return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_reparse_buffer

    Synopsis: Scans a HTTP output buffer and executes the server directives
    in the file.  Accepts the standard CGI directives:

        Location: filename
        Location: URL
        Content-Type: what/type
        Status: code

    The buffer must at least contain a 'Content-Type:' header line and a
    blank line; otherwise the buffer is returned as-is without processing.
    Returns 1 if the HTTP buffer refers to a new URL, else returns 0. The
    p_http-> file_size must be set to the buffer size.  Sets p_http->
    file_offset to point to the start of the data in the buffer.
    ---------------------------------------------------------------------[>]-*/

int
http_reparse_buffer (HTTP_CONTEXT *p_http, char *body)
{
    char
        *eoln,                          /*  Blank line value                 */
        *blank_line,                    /*  Blank line position              */
        *header,                        /*  Header name                      */
        *separator;                     /*  Header value                     */
    int
        feedback = 0;

    ASSERT (p_http);

    /*  Create a new, empty table for the mime values                        */
    http_close_cgi (p_http);
    p_http-> table       = sym_create_table ();
    p_http-> file_offset = 0;
    p_http-> cgi_header  = FALSE;

    /*  Handle special case of HTTP/.. formatted output first                */
    if (strprefixed (body, "HTTP/"))
      {
        p_http-> cgi_header = TRUE;
        return (FALSE);
      }
    else
    if (body [0] == '<')                /*  Special case of HTML output      */
      {
        sym_assume_symbol (p_http-> table, "content-type", "text/html");
        return (FALSE);
      }

    /*  Look for blank line in body                                          */
    eoln = "\r\n\r\n";
    blank_line = memfind_r (body, p_http-> file_size, eoln, 4);
    if (!blank_line)
      {
        eoln = "\n\n";
        blank_line = memfind_r (body, p_http-> file_size, eoln, 2);
      }

    if (blank_line)                     /*  Header is complete               */
      {
        p_http-> file_offset = (blank_line + strlen (eoln)) - body;
        blank_line [strlen (eoln) - 1] = '\0';

        /*  Now process each line in the header block                        */
        header = body;
        while (*header)
          {
            separator = strchr (header, ':');
            if (!separator)
                break;

            /*  Cut at the end-of-line                                       */
            eoln = strchr (separator, '\n');
            if (!eoln)
                break;
            *eoln = '\0';
            if (eoln [-1] == '\r')
                eoln [-1] = '\0';

            if (parse_cgi_header (p_http, header, separator))
                feedback = 1;

            header = eoln + 1;
          }
        if (feedback == 0)
            p_http-> file_size -= p_http-> file_offset;
      }
    else
        sym_assume_symbol (p_http-> table, "content-type", "text/html");

    return (feedback);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_capture_console

    Synopsis: Prepares console capturing according to the current value of
    console:capture and console:filename.
    ---------------------------------------------------------------------[>]-*/

void
http_capture_console (void)
{
    char
        mode;

    if (*CONFIG ("console:capture") == '1')
      {
        if (*CONFIG ("console:append") == '1')
            mode = 'a';
        else
            mode = 'w';

        console_capture (file_where ('s', CONFIG ("server:log-dir"),
                                          CONFIG ("console:filename"),
                                          NULL), mode);
      }
    else
        console_capture (NULL, 0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_uri_protected

    Synopsis:
    Looks for the URI in the authorisation table.  The authorisation table
    always specifies a full URI or directory name.  Searches for the most
    specific URI first, by successively removing path segments from the
    right-hand side.  If asked to look for "/pub/mypages/file", will look
    for entries in this order:

        [pub/mypages/file]
        [pub/mypages]
        [pub]
        [/]

    Returns TRUE if the directory is defined in the authorisation table,
    and modifies the supplied url to match the entry keyword. The specified
    uri MUST start with '/'.
    ---------------------------------------------------------------------[>]-*/

Bool
http_uri_protected (HTTP_CONTEXT *p_http, SYMTAB *passwd, char *uri)
{
    char
        *superuser,                     /*  Superuser password               */
        *slash;                         /*  Position of last '/' in name     */

    ASSERT (passwd);
    ASSERT (uri);
    ASSERT (*uri == '/');

    /*  First check super-user password                                      */
    superuser = HCONFIG ("security:superuser");
    if (*superuser
    &&   http_password_okay (superuser, p_http-> password))
        return (FALSE);                 /*  Not protected                    */

    strlwc (uri);                       /*  All searches in lowercase        */
    FOREVER
      {
        if (sym_lookup_symbol (passwd, uri))
            return (TRUE);              /*  URI was found                    */
        else
        if (*uri == '/'                 /*  Remove leading slash if any      */
        &&  sym_lookup_symbol (passwd, uri + 1))
          {
            memmove (uri, uri + 1, strlen (uri));
            return (TRUE);
          }
        /*  Cut at slash, if any                                             */
        slash = strrchr (uri, '/');
        if (slash)
            *slash = '\0';
        else
          {
            strcpy (uri, "/");
            if (sym_lookup_symbol (passwd, uri))
                return (TRUE);          /*  "/" was found                    */
            else
                return (FALSE);         /*  Not found                        */
          }
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_password_okay

    Synopsis: Returns TRUE if the response matches the challenge.  If the
    challenge is "-", the response is never accepted.  Challenge and
    response may either or both be null.  Neither challenge nor response
    may be '*SSL'.
    ---------------------------------------------------------------------[>]-*/

Bool
http_password_okay (char *challenge, char *response)
{
    if (!challenge || !response)
        return (FALSE);                 /*  Either argument not supplied     */
    else
    if (streq (challenge, "-"))
        return (FALSE);                 /*  Challenge is disabled or empty   */
    else
    if (streq (challenge, "*SSL")
    ||  streq (response,  "*SSL"))
        return (FALSE);
    else
        return (streq (challenge, response));
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_pipe

    Synopsis: Creates a temporary filename used to pass data to a CGI or
    filter process.  The temporary file is located in the server:temp_dir
    directory.  The caller must free the returned filename when finished
    with it, using mem_free or mem_strfree.
    ---------------------------------------------------------------------[>]-*/

char  *
http_pipe (HTTP_CONTEXT *p_http, char *ext)
{
    static int
        counter_value = 0;              /*  CGI number, 0 to 9999            */
    char
        counter_text [9];               /*  pipeNNNN                         */

    /*  Make stdin and stdout filenames                                      */
    sprintf (counter_text, "pipe%04d", ++counter_value);
    if (counter_value > 9999)
        counter_value = 0;

    return (mem_strdup (file_where ('s', HCONFIG ("server:temp-dir"),
                                    counter_text, ext)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_message

    Synopsis: Formats an error message in the global server_message variable.
    Use this function instead of formatting the message directly, since this
    function uses vsnprintf() if possible to guard against overflows.
    ---------------------------------------------------------------------[>]-*/

void
http_message (const char *format, ...)
{
    va_list
        argptr;                         /*  Argument list pointer            */
    va_start (argptr, format);          /*  Start variable args processing   */
#if (defined (DOES_SNPRINTF))
    vsnprintf (server_message, LINE_MAX, format, argptr);
#else
    vsprintf  (server_message,  (char *) format, argptr);
#endif
    va_end (argptr);                    /*  End variable args processing     */
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_webmask

    Synopsis: Returns a freshly allocated string containing the webmask
    specified by the config key.  If the first letter of the specified value
    is '@', reads the webmask from a file.  If the webmask is the string
    "local", and the handle is >0, the webmask is set to the local address
    for the specified socket.  Free the webmask using mem_free().
    ---------------------------------------------------------------------[>]-*/

char *
http_webmask (const char *config_value, sock_t handle)
{
    DESCR
        *descr = NULL;
    char
        *webmask;

   webmask = (char *) config_value;
   if (webmask [0] == '@')
     {
       descr = file_slurp (webmask + 1);
       if (descr)
           webmask = (char *) descr-> data;
       else
         {
           trace ("Webmask file %s not found", webmask + 1);
           webmask = "*";               /*  Defaults to 'allow all'          */
         }
     }
    /*  If 'webmask=local', the local and remote addresses must match        */
    if (handle && streq (webmask, "local"))
        webmask = socket_localaddr (handle);

    webmask = mem_strdup (webmask);
    if (descr)
        mem_free (descr);

    return (webmask);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_reserved_username

    Synopsis: Returns TRUE if the specified user id is one of those values
    reserved by the authentication system for special purposes.
    ---------------------------------------------------------------------[>]-*/

Bool
http_reserved_username (const char *username)
{
    if (streq (username, "realm")
    ||  streq (username, "webmask")
    ||  streq (username, "http-put")
    ||  streq (username, "http-delete"))
        return (TRUE);
    else
        return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_update_resource

    Synopsis: Updates the resource specified by the HTTP request, using the
    HTTP PUT, DELETE, MOVE, or COPY method as specified in the request.  If
    the update was successful, returns 0, else returns -1 and sets the HTTP
    response code in the p_http structure.
    ---------------------------------------------------------------------[>]-*/

int
http_update_resource (HTTP_CONTEXT *p_http)
{
    SYMBOL
        *symptr;                        /*  Symbol in HTTP header table      */
    char
        *content_header,                /*  Content-xxxx header              */
        *content_location = NULL,       /*  Content-Location value           */
        *target_uri = NULL,             /*  Target URI                       */
        *target_filename = NULL,        /*  Target filename                  */
        *target_pathend,                /*  Last / in target URI             */
        *url_pathend;                   /*  Last / in request URL            */

    /*  Start by assuming everything will work.  Huh! :-)                    */
    p_http-> response = HTTP_RESPONSE_OK;

    /*  We first check the various Content- headers:
     *    - Content-Length .......... valid, used during read
     *    - Content-Location ........ valid, used as target URI
     *    - Content-Language ........ accept but don't use
     *    - Content-MD5 ............. accept but don't use
     *    - Content-Type ............ accept but don't use
     *    - Content-Base ............ reject with a 501 Not Implemented
     *    - Content-Encoding ........ reject with a 501 Not Implemented
     *    - Content-Range ........... reject with a 501 Not Implemented
     *    - Content-anything else ... reject with a 400 Bad Request
     */
    for (symptr = p_http-> table-> symbols; symptr; symptr = symptr-> next)
      {
        if (strprefixed (symptr-> name, "content-"))
          {
            content_header = symptr-> name + strlen ("content-");
            if (streq (content_header, "language")
            ||  streq (content_header, "length")
            ||  streq (content_header, "md5")
            ||  streq (content_header, "type")
            ||  streq (content_header, "location"))
                ; /*  Do nothing with these headers                          */
            else
            if (streq (content_header, "base")
            ||  streq (content_header, "encoding")
            ||  streq (content_header, "range"))
                p_http-> response = HTTP_RESPONSE_NOTIMPLEMENTED;
            else
                p_http-> response = HTTP_RESPONSE_BADREQUEST;
          }
      }

    /*  The target URI is either the original URI, or is derived from the
     *  Content-Location:, which may be an absolute or a relative URI.
     *  The target URI MUST have the same base directory as the request URI,
     *  since it is controlled by the same authentication.
     *
     *  We accept Content-Location: or Destination: or New-Uri: as the target
     */
    content_location = http_header_value (p_http, "content-location");
    if (strnull (content_location))
        content_location = http_header_value (p_http, "destination");
    if (strnull (content_location))
        content_location = http_header_value (p_http, "new-uri");

    if (strused (content_location))
      {
        target_uri     = build_full_url (content_location, p_http-> url);
        target_pathend = strrchr (target_uri, '/');
        url_pathend    = strrchr (p_http-> url, '/');
        ASSERT (target_pathend);
        ASSERT (url_pathend);

        /*  Path must be same length and identical in both URIs              */
        if ((target_pathend - target_uri == url_pathend - p_http-> url)
        && memcmp (target_uri, p_http-> url, url_pathend - p_http-> url) == 0)
          {
            /*  Now build target filename using p_http-> filename path       */
            strcpy (buffer, p_http-> file_name);
            url_pathend = strrchr (buffer, '/');
            strcpy (url_pathend + 1, target_pathend + 1);
            target_filename = mem_strdup (buffer);
          }
        else
            p_http-> response = HTTP_RESPONSE_FORBIDDEN;
      }
    else
      {
        target_uri      = mem_strdup (p_http-> url);
        target_filename = mem_strdup (p_http-> file_name);
      }

    if (p_http-> response == HTTP_RESPONSE_OK)
      {
        switch (p_http-> method)
          {
            case HTTP_METHOD_PUT:
                http_put_resource    (p_http, target_filename);
                break;
            case HTTP_METHOD_DELETE:
                http_delete_resource (p_http, target_filename);
                break;
            case HTTP_METHOD_MOVE:
                http_move_resource   (p_http, target_filename);
                break;
            case HTTP_METHOD_COPY:
                http_copy_resource   (p_http, target_filename);
                break;
          }
      }

    mem_strfree (&target_uri);
    mem_strfree (&target_filename);
    if (p_http-> response < HTTP_RESPONSE_BADREQUEST)
        return (0);
    else
        return (-1);
}


/*  -------------------------------------------------------------------------
    Function: http_put_resource -- internal

    Synopsis: Writes the content to the request URI filename and sets the
    HTTP response code to one of the following:

    200 HTTP_RESPONSE_OK          the file was modified
    201 HTTP_RESPONSE_CREATED     the file was created, non-empty
    204 HTTP_RESPONSE_NOCONTENT   the file was emptied
    403 HTTP_RESPONSE_FORBIDDEN   the operation failed
    -------------------------------------------------------------------------*/

static void
http_put_resource (HTTP_CONTEXT *p_http, char *target_filename)
{
    FILE
        *created;                       /*  Created file stream              */

    ASSERT (target_filename);
    trace ("HTTP PUT file=%s size=%ld", target_filename, p_http-> post_size);

    if (file_exists (target_filename))
        file_delete (target_filename);
    else
        p_http-> response = HTTP_RESPONSE_CREATED;

    /*  The content is either in the cgi_stdin file or in the post_data     */
    if (p_http-> cgi_stdin)
      {
        if (file_copy (target_filename, p_http-> cgi_stdin, 'b'))
            set_access_failed (p_http);
      }
    else
      {
        created = fopen (target_filename, FOPEN_WRITE_BINARY);
        if (created)
          {
            /*  Write POSTed data if present                                 */
            if (p_http-> post_data)
                fwrite (p_http-> post_data,
                        p_http-> post_size, 1, created);
            else
                p_http-> response = HTTP_RESPONSE_NOCONTENT;

            file_close (created);
            http_count_transfer (p_http-> post_size);
          }
        else
            p_http-> response = HTTP_RESPONSE_FORBIDDEN;
      }
}


/*  -------------------------------------------------------------------------
    Function: http_delete_resource -- internal

    Synopsis: Deletes the request URI filename and sets the HTTP response
    code to one of the following:

    200 HTTP_RESPONSE_OK          the file was deleted
    403 HTTP_RESPONSE_FORBIDDEN   the operation failed
    404 HTTP_RESPONSE_NOTFOUND    the specified file was not found
    -------------------------------------------------------------------------*/

static void
http_delete_resource (HTTP_CONTEXT *p_http, char *target_filename)
{
    ASSERT (target_filename);
    trace ("HTTP DELETE file=%s", target_filename);

    if (file_exists (target_filename))
      {
        if (file_delete (target_filename))
            set_access_failed (p_http);
      }
    else
        p_http-> response = HTTP_RESPONSE_NOTFOUND;
}


/*  -------------------------------------------------------------------------
    Function: http_move_resource -- internal

    Synopsis: Moves the request URI filename to the target filename and sets
    the HTTP response code to one of the following:

    200 HTTP_RESPONSE_OK            the file was moved correctly
    403 HTTP_RESPONSE_FORBIDDEN     the operation failed
    412 HTTP_RESPONSE_PRECONDITION  the file existed but "Overwrite: false"
    -------------------------------------------------------------------------*/

static void
http_move_resource (HTTP_CONTEXT *p_http, char *target_filename)
{
    ASSERT (target_filename);
    trace ("HTTP MOVE from=%s to=%s", p_http-> file_name, target_filename);

    if (streq (p_http-> file_name, target_filename))
        p_http-> response = HTTP_RESPONSE_FORBIDDEN;
    else
    if (!file_exists (p_http-> file_name))
        p_http-> response = HTTP_RESPONSE_NOTFOUND;
    else
    if (file_exists (target_filename))
      {
        if (!http_overwrite_ok (p_http))
            p_http-> response = HTTP_RESPONSE_PRECONDITION;
        else
        if (file_delete (target_filename))
            set_access_failed (p_http);
      }
    if (p_http-> response == HTTP_RESPONSE_OK
    &&  file_rename (p_http-> file_name, target_filename))
        set_access_failed (p_http);
}


/*  -------------------------------------------------------------------------
    Function: http_copy_resource -- internal

    Synopsis: Copies the URL filename to the target and sets the HTTP
    response code to one of the following:

    200 HTTP_RESPONSE_OK            the file was copied as requested
    403 HTTP_RESPONSE_FORBIDDEN     the operation failed
    412 HTTP_RESPONSE_PRECONDITION  the file existed but "Overwrite: false"
    -------------------------------------------------------------------------*/

static void
http_copy_resource (HTTP_CONTEXT *p_http, char *target_filename)
{
    ASSERT (target_filename);
    trace ("HTTP COPY from=%s to=%s", p_http-> file_name, target_filename);

    if (!file_exists (p_http-> file_name))
        p_http-> response = HTTP_RESPONSE_NOTFOUND;
    else
    if (file_exists (target_filename))
      {
        if (!http_overwrite_ok (p_http))
            p_http-> response = HTTP_RESPONSE_PRECONDITION;
        else
        if (file_delete (target_filename))
            set_access_failed (p_http);
      }
    if (p_http-> response == HTTP_RESPONSE_OK
    &&  file_copy (target_filename, p_http-> file_name, 'b'))
        set_access_failed (p_http);
}


static void
set_access_failed (HTTP_CONTEXT *p_http)
{
    p_http-> response = HTTP_RESPONSE_FORBIDDEN;
    trace ("  failed with error: %s", strerror (errno));
}


static Bool
http_overwrite_ok (HTTP_CONTEXT *p_http)
{
    char
        *overwrite;

    overwrite = http_header_value (p_http, "overwrite");
    if (*overwrite == '\"')
        overwrite++;                    /*  Skip leading quote if any        */

    /*  False -> no overwrite                                                */
    return (tolower (*overwrite) != 'f');
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_count_transfer

    Synopsis: Updates the global server transfer statistic fields.
    ---------------------------------------------------------------------[>]-*/

void
http_count_transfer (long size)
{
    static long
        transfer_bytes = 0;             /*  Count transfer in Kbytes         */

    /*  Keep track of Kbytes for display and individual bytes internally     */
    transfer_bytes += size;
    transfer_size  += transfer_bytes / 1024;
    transfer_bytes  = transfer_bytes % 1024;
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_clean_request

    Synopsis: Returns a cleaned-up copy of the request.  A request string is
    always in the form "method uri protocol", e.g. "GET xxxx HTTP/1.0".  This
    implementation ensures that all spaces are replaced by "%20".  Returns
    a freshly-allocated string which you must free using mem_free() when done,
    or NULL if there was insufficient memory.  The request is truncated to
    HTTP_LOG_REQ_MAX characters plus a null byte if it is longer than that.
    ---------------------------------------------------------------------[>]-*/

char *
http_clean_request (const char *request)
{
    char
        *first_space,                   /*  Space after method               */
        *last_space,                    /*  Space before protocol            */
        *from_ptr,                      /*  Pointer into request string      */
        *to_ptr,                        /*  Pointer into formatted string    */
        *fmt_request;                   /*  Formatted request                */

    first_space = strchr  (request, ' ');
    last_space  = strrchr (request, ' ');

    /*  If we don't have a recognisable request, return the same string      */
    if (!first_space || !last_space || last_space == first_space)
        fmt_request = mem_strdup (request);
    else
      {
        /*  Count 3 chars per space in request and allocate the new string   */
        fmt_request = mem_alloc (strlen (request) + 1
                    + (strcntch (request, ' ') - 2) * 2);
        if (fmt_request)
          {
            /*  Copy and format request                                      */
            to_ptr = fmt_request;
            for (from_ptr = (char *) request; *from_ptr; from_ptr++)
              {
                if (*from_ptr == ' '
                &&   from_ptr != first_space
                &&   from_ptr != last_space)
                  {
                    *to_ptr++ = '%';
                    *to_ptr++ = '2';
                    *to_ptr++ = '0';
                  }
                else
                    *to_ptr++ = *from_ptr;
              }
            *to_ptr = '\0';
          }
      }
    if (fmt_request
    &&  strlen (fmt_request) > HTTP_LOG_REQ_MAX)
        fmt_request [HTTP_LOG_REQ_MAX] = '\0';

    return (fmt_request);
}


/*  ---------------------------------------------------------------------[<]-
    Function: http_clean_hostname

    Synopsis: Accepts a host name string and cleans-it up: converts the
    host name to lowercase, removes a :port specifier if any, and removes
    a trailing dot if any.  Returns a freshly string allocated using the
    mem_alloc() function, or NULL if there was insufficient memory.
    ---------------------------------------------------------------------[>]-*/

char *
http_clean_hostname (const char *hostname)
{
    char
        *clean_name,
        *colon;

    clean_name = mem_strdup (hostname);
    if (clean_name)
      {
        strlwc (clean_name);
        colon = strrchr (clean_name, ':');
        if (colon)
            *colon = '\0';              /*  Cut :port if present         */
        if (strlast (clean_name) == '.')
            strlast (clean_name) = '\0';
      }
    return (clean_name);
}


/*  -------------------------------------------------------------------------
 *  cycle_mode
 *
 *  Searches the config table for a cycle mode for the specified logfile.
 *  Returns one of the sflfile.h CYCLE_ constants; default if no entry is
 *  defined is CYCLE_NEVER.  If startup argument is FALSE, treats the
 *  'startup' mode as 'never'.
 */

int
http_cycle_mode (SYMTAB *table, char *key, Bool startup)
{
    char
        *cycle_mode;                    /*  How do we cycle the file?        */
    int
        cycle_how;                      /*  Cycle mode                       */

    cycle_mode = ini_dyn_value (table, key, "cycle",
                 ini_dyn_value (defaults, key, "cycle", ""));
    if (startup
    && (streq (cycle_mode, "startup")
    ||  streq (cycle_mode, "0")))
        cycle_how = CYCLE_ALWAYS;
    else
    if (streq (cycle_mode, "hourly")
    ||  streq (cycle_mode, "1"))
        cycle_how = CYCLE_HOURLY;
    else
    if (streq (cycle_mode, "daily")
    ||  streq (cycle_mode, "2"))
        cycle_how = CYCLE_DAILY;
    else
    if (streq (cycle_mode, "weekly")
    ||  streq (cycle_mode, "3"))
        cycle_how = CYCLE_WEEKLY;
    else
    if (streq (cycle_mode, "monthly")
    ||  streq (cycle_mode, "4"))
        cycle_how = CYCLE_MONTHLY;
    else
        cycle_how = CYCLE_NEVER;

    return (cycle_how);
}
