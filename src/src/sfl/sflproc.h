/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflproc.h
    Title:      Process control functions
    Package:    Standard Function Library (SFL)

    Written:    96/09/09  iMatix SFL project team <sfl@imatix.com>
    Revised:    98/12/17

    Synopsis:   Provides functions to create and manage processes.  The main
                set of functions lets you create, monitor, and end processes.
                A secondary function lets you run the current process as a
                background process.

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef SFLPROC_INCLUDED                /*  Allow multiple inclusions        */
#define SFLPROC_INCLUDED

/*  Type definitions                                                         */

#if (defined (__WINDOWS__))
#  if (!defined(NULL_HANDLE))
#    define NULL_HANDLE ((HANDLE) 0)
#  endif
#else
typedef int HANDLE;                     /*  Windows uses HANDLE for files    */
#  define NULL_HANDLE ((HANDLE)-1)      /*  0 is a valid handle => -1 is NULL*/
#endif

#if (defined (WIN32))
typedef struct {
    HANDLE process;
    HANDLE in;
    HANDLE out;
    HANDLE err;
    DESCR  *envd;                       /*  Environment data                 */
} PROC_HANDLE;
typedef PROC_HANDLE *PROCESS;           /*  Process ID type                  */
#define NULL_PROCESS NULL               /*    and null process               */

#elif (defined (__VMS__))
typedef struct {
    long id;
    long status;
} PROC_HANDLE;
typedef PROC_HANDLE *PROCESS;           /*  Process ID type                  */
#define NULL_PROCESS NULL               /*    and null process               */

#else
typedef qbyte        PROCESS;           /*  Process ID type                  */
#   define NULL_PROCESS ((PROCESS)0)    /*    and null process               */
#endif

/*  Process creation data structure -- contains all the information needed   */
/*  to create a new process, including I/O redirection, changing directories */
/*  changing UID/GID.  The uid/gid values are applicable only to unix.       */
/*  The rootdir option does a chroot() under unix, and a _chdir() under DOS, */
/*  Windows, and OS/2 (which will also change drive).                        */
/*                                                                           */
/*  The macro PROC_DATA_INIT can be used to initialised this struct          */
/*  at variable declaration time.                                            */

typedef struct {
    /*  Program name and arguments ----------------------------------------- */
    /*  The filename string can contain arguments (which will be parsed)     */
    /*  if argv == NULL.  If argv != NULL filename will not be parsed for    */
    /*  arguments.                                                           */
    /*  The searchext field is relevant only to DOS-like systems, and lists  */
    /*  extensions to try adding to the file to find it.  The default is     */
    /*  operating system specific, covering standard executable extensions.  */
    const char *filename;
          char **argv;
    const char *path;                   /*  Override PATH, if not null       */
    const char *shell;                  /*  Override default shell, if ! null*/
    const char **searchext;             /*  Extensions to try, to find file  */
    Bool       searchpath;              /*  Look in path for filename        */
    Bool       intsearch;               /*  Look in path for interpreter     */
    Bool       useshell;                /*  Invoked via shell                */
    Bool       createdaemon;            /*  Create daemon process (detached) */
    Bool       wait;                    /*  Wait for process to finish       */
    int        delay;                   /*  ms to wait to see if exec worked */

    /*  Directories to change to ------------------------------------------- */
    const char *rootdir;                /*  Dir to chroot() to, if not NULL  */
    const char *workdir;                /*  Work dir; done after any chroot()*/

    /*  I/O Redirection ---------------------------------------------------- */
    /*  A handle of NULL_HANDLE means "no change".                           */
    /*  no_handles specifies the number of handles that should be inherited  */
    /*  by the child process, and under unix all handles above that number   */
    /*  (up to some fixed limit) will be closed after fork(), before exec()  */
    HANDLE in;
    HANDLE out;
    HANDLE err;
    int    no_handles;                  /*  File handles inherited; default 3*/

    /*  Environment -------------------------------------------------------- */
    /*  Default is to inherit the current environment, without change.  This */
    /*  can either be replaced entirely by supplying envv != NULL, or things */
    /*  can be added/removed from the current environment to get a new one.  */
    char   **envv;                      /*  Whole replacement environment    */
    SYMTAB *envadd;                     /*  Entries to add to environment    */
    SYMTAB *envrm;                      /*  Keys to remove from environment  */

    /*  Permissions -------------------------------------------------------- */
    /*  UID/GID values are relevant only under unix, and are ignored under   */
    /*  other operating systems.                                             */
    /*  NOTE: Because any uid value could be valid, flags indicate that      */
    /*  the values have been set; use PD_SETUID(), and PD_SETGID() macros.   */
    uid_t  uid;
    gid_t  gid;
    Bool   dosetuid;
    Bool   dosetgid;

    /*  Output ------------------------------------------------------------- */
    /*  This section contains elements set by process_create_full().         */
    PROCESS  pid;
    int      returncode;
    int      error;
} PROC_DATA;

/*  Macros:
 *  FILEHANDLE_MAX      Maximum possible number of open files
 *  PROC_DATA_INIT      Process data structure (empty) initialisation
 *  PD_SETUID(*pd, newuid)  Set uid to change to in process data structure
 *  PD_SETGID(*pd, newgid)  Set gid to change to in process data structure
 */

/*  getdtablesize () is not available on all systems                         */
#if (defined (__UNIX__))
#   if (defined (__UTYPE_UNIXWARE))
#       define FILEHANDLE_MAX   sysconf (_SC_OPEN_MAX)
#   elif (defined (__UTYPE_HPUX))
#       define FILEHANDLE_MAX   FD_SETSIZE
#   elif (defined (__UTYPE_SINIX))
#       define FILEHANDLE_MAX   FD_SETSIZE
#   else
#       define FILEHANDLE_MAX   getdtablesize ()
#   endif
#elif (defined (FD_SETSIZE))
#   define FILEHANDLE_MAX       FD_SETSIZE
#else
#   define FILEHANDLE_MAX       32      /*  Arbitrary                        */
#endif

/*  Usage: PROC_DATA myproc = PROC_DATA_INIT;                                */
#define PROC_DATA_INIT \
    {\
      /*  Filename, args,   */  NULL, NULL, NULL, NULL, NULL,           \
      /*    flags           */  FALSE, FALSE, FALSE, FALSE, FALSE, 1000,\
      /*  Directories       */  NULL, NULL,                             \
      /*  I/O redirection   */  NULL_HANDLE, NULL_HANDLE, NULL_HANDLE,3,\
      /*  Environment       */  NULL, NULL, NULL,                       \
      /*  UID/GID           */  0, 0, FALSE, FALSE,                     \
      /*  Output            */  NULL_PROCESS, 0, 0                      \
    }

#define PD_SETUID(pd, newuid)  pd.uid = newuid; pd.dosetuid = TRUE
#define PD_SETGID(pd, newgid)  pd.gid = newgid; pd.dosetgid = TRUE

/*  Global variables                                                         */

extern int process_errno;               /*  Last process exit code           */
extern int process_delay;               /*  Wait for child to start          */
extern Bool process_compatible;         /*  Try to be compatible             */
extern const char **sfl_default_ext;    /*  Default extensions               */

#ifdef __cplusplus
extern "C" {
#endif

PROCESS process_create_full (PROC_DATA *procinfo);
PROCESS process_create      (const char *file, char *argv [],
        const char *workdir, const char *std_in, const char *std_out,
        const char *std_err, char *envv [], Bool wait);
int     process_status      (PROCESS process_id);
int     process_kill        (PROCESS process_id);
void    process_close       (PROCESS process_id);
int     process_server      (const char *workdir, const char *lockfile,
                             int argc, char *argv [], const char *sswitch []);
Bool    process_alarm       (long delay);
char   *process_esc         (char *dest, const char *src);
char   *process_unesc       (char *dest, const char *src);
int     process_priority    (int priority);

#ifdef __cplusplus
}
#endif

/*  Return values from process_status()                                      */

#define PROCESS_RUNNING         0
#define PROCESS_ENDED_OK        1
#define PROCESS_ENDED_ERROR     2
#define PROCESS_INTERRUPTED     3

/*  Values for process_priority()                                            */

#define PRIORITY_LOW            0
#define PRIORITY_NORMAL         1
#define PRIORITY_HIGH           2

#endif

