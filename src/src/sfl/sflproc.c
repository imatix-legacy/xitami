/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflproc.c
    Title:      Process control functions
    Package:    Standard Function Library (SFL)

    Written:    96/09/09  iMatix SFL project team <sfl@imatix.com>
    Revised:    99/06/01

    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "prelude.h"                    /*  Universal header file            */
#include "sfllist.h"                    /*  Linked-list functions            */
#include "sflmem.h"                     /*  Memory-handling functions        */
#include "sflstr.h"                     /*  String-handling functions        */
#include "sflfile.h"                    /*  File access functions            */
#include "sflnode.h"                    /*  Memory node functions            */
#include "sfldir.h"                     /*  Directory access functions       */
#include "sflcons.h"                    /*  Prototypes for functions         */
#include "sflsymb.h"                    /*  Symbol table handling            */
#include "sfltok.h"                     /*  Token-handling functions         */
#include "sflenv.h"                     /*  Environment handling functions   */

#include "sflproc.h"                    /*  Prototypes for functions         */


/*  Global variables                                                         */

int  process_errno = 0;                 /*  Last process exit code           */
int  process_delay = 1000;              /*  Wait for child to start, msecs   */
Bool process_compatible = TRUE;         /*  Try to be compatible             */


/*  Function prototypes                                                      */

#if (defined (WIN32))
static HANDLE redirect_io (const char *device, int fileno, int err_pipe,
                           Bool read_only);
#endif

#if (defined (__OS2__) || defined (__UNIX__))
static HANDLE redirect_io_fh         (int srcfh, int destfh);
static char **prefix_argv_with_shell (char **argv, const char *shell);
static char **merge_environment      (char **curenv, SYMTAB *envadd,
                                      SYMTAB *envrm);
static Bool   helper_remove_symbol   (SYMBOL *sym, ...);
#endif

#if (defined (__OS2__))
static void   restore_redirection (HANDLE old_stdin, HANDLE old_stdout,
                                   HANDLE old_stderr);
static char  *redirect_exec_full  (const char *command, Bool searchpath,
                                   const char *suppliedpath,
                                   const char **searchext);
static void   free_argv           (char **argv, Bool tokenarray);
#endif

#if (defined (WIN32))
static char  *redirect_exec  (const char *command);
#endif

#if (defined (__VMS__))
static void translate_to_vms (char *filename);
#endif

/*  Default extensions to search when looking for a file we can run.         */
/*  Using no preceeding "."s is encouraged, as this uses the extensions      */
/*  only if the file doesn't already have an extension.  This is used if     */
/*  NULL is passed for searchext in the PROC_DATA structure                  */

#if   (defined (__OS2__))
static const char *default_ext [] = { "exe", "cmd", NULL };
#elif (defined (WIN32))
static const char *default_ext [] = { "exe", "com", "bat", NULL };
#endif

/*  Extensions to search when looking for executable file.                   */
/*  This differs from default_ext in that it should contain only extensions  */
/*  that can be _directly_executed_.  It is used for looking for             */
/*  interpreters and the like when no further redirection will take place.   */

#if   (defined (__OS2__))
static const char *runnable_ext [] = { "exe", NULL };
#elif (defined (WIN32))
static const char *runnable_ext [] = { "exe", "com", NULL };
#endif


/*  ---------------------------------------------------------------------[<]-
    Function: process_create_full

    Synopsis: Creates a subprocess and returns a PROCESS identifying the new
    process.  Optionally redirects standard input, output, error file handles
    to supplied file handles, changes working directory, and environment.
    In some operating systems can also optinally change the root directory
    (chroot()), and the uid/gid with which the new process runs.
    All information required to start the new process is specified in a
    PROC_DATA structure.  Where elements are not specified, they remain the
    same as the current process.  The following elements can be specified
    in the PROC_DATA structure:
    <Table>
    filename      File to execute, can include arguments if argv is NULL.
    argv_[]       List of arguments; argv [0] is filename; ends in a NULL.
    path          Search path (environments PATH is used if NULL).
    shell         Shell to use if useshell is TRUE (default is OS specific)
    searchext     Array of extensions to search when looking for filename
    searchpath    Flag: TRUE indicates path should be searched for filename
    useshell      Flag: TRUE indicates program should be started via a shell
    createdaemon  Flag: TRUE indicates a (separate) daemon should be started
    wait          Flag: TRUE indicates wait for process to finish
    delay         Amount of time to wait around for errors to happen (unix)
    rootdir       Root directory for new process (chroot()) if not NULL
    workdir       Working directory; if NULL, remains in current directory.
    in            File handle to use for standard input; -1 = no redirection.
    out           File handle to use for standard output; -1 = no redirection.
    err           File handle to use for standard error; -1 = no redirection.
    envv_[]       Whole environment for new process; if NULL current env used
    envadd        Strings to add into current environment (if envv NULL).
    envrm         Keys to remove from current environment (if envv NULL).
    uid           (Real) UID for new process (set if dosetuid TRUE)
    gid           (Real) GID for new process (set if dosetgid TRUE)
    dosetuid      Flag: TRUE indicates that uid should be set
    dosetgid      Flag: TRUE indicates that gid should be set
    </Table>
    If argv is NULL, parses the filename argument into words delimited by
    whitespace and builds the necessary argv table automatically.  Use this
    feature to execute a command with arguments, specified as one string.
    To search for the program in the path set searchpath to TRUE, and
    optionally supply a path to search.  To run shell builtins set useshell
    to TRUE.
    The envv list consists of strings in the form "name=value", ending in a
    NULL pointer.  If the envv argument is null, the environment of the
    current process is passed, with additions from envadd (if not NULL),
    and the keys listed in envrm removed (if not NULL).  If envv is not null
    then the envv environment is used as is.
    The child process may optionally start in a new root directory and with
    a different uid/gid (if supported by the operating system).  If rootdir,
    workdir, uid, and gid are all non null, then they are processed in the
    order: rootdir, workdir, gid, uid, to ensure all changes take place.
    Note that in this instance workdir is relative to the new root directory.
    Under DOS, Windows, and OS/2, the rootdir may be used to specify a change
    to a new drive letter (processed by _chdir() or _chdir2()).
    If the process is started correctly, this function will sleep for
    'process_delay' milliseconds.  If the child command detects an error
    at startup, it may exit with an error status.  The sleep allows this
    error to be collected by calling process_status() after this call.  If
    process_delay is 0, any child error is ignored.
    Returns child process id, or 0 if there was an error.  The PROC_DATA
    structure contains the following fields used for output:
    <Table>
    pid           Process identifier (as returned by function)
    returncode    Return code from sub process (only set if wait is TRUE)
    error         Code indicating error that occured (like libc errno)
    </Table>
    Under VMS, the filename must have been defined as a command before the
    calling process was started; the path is disregarded.
    Under Windows and OS/2 processing of the #! line is emulated, and the
    interpreter mentioned in the #! line will be invoked on the script.
    Under OS/2 the filename can be the name of a CMD script, and this will
    be run with the interpreter specified in the first line (EXTPROC line,
    or "'/'*!" line; or failing that with the default command interpreter.

    Known bugs: when parsing filename argument into words, does not handle
    quotes in any special way; "this text" is 2 words, '"this' and 'text"'.
    You should have passed the filename through process_esc() before adding
    any optional arguments.
    ---------------------------------------------------------------------[>]-*/

PROCESS process_create_full (PROC_DATA *procinfo)
{
    /*  Implementation note: due to the size of this function, and the       */
    /*  sizeable differences between operating systems supported, the        */
    /*  implementation of this function for each operating system is in      */
    /*  a different file, and the appropriate one is included here.          */

    /*  WARNING: do not put any code here, otherwise it will prevent the     */
    /*  implementations from declaring variables.                            */

#if   (defined (__UNIX__))
#   include "sflprocu.imp"              /*  Unix implementation              */
#elif (defined (__OS2__))
#   include "sflproco.imp"              /*  OS/2 implementation              */
#elif (defined (WIN32))
#   include "sflprocw.imp"              /*  Windows (32-bit) implementation  */
#elif (defined (__VMS__))
#   include "sflprocv.imp"              /*  VMS implementation               */
#else
    return ((PROCESS) 0);               /*  Not supported on this system     */
#endif
}

 /*  ---------------------------------------------------------------------[<]-
    Function: process_create

    Synopsis: Creates a subprocess and returns a PROCESS identifying the new
    process.  Optionally directs standard input, output, and error streams
    to specified devices.  The caller can also specify environment symbols
    that the subprocess can access.  Accepts these arguments:
    <Table>
    filename    File to execute; if not fully specified, searches PATH.
    argv_[]     List of arguments; argv [0] is filename; ends in a NULL.
    workdir     Working directory; if NULL, remains in current directory.
    std_in      Device to use for standard input; NULL = no redirection.
    std_out     Device to use for standard output; NULL = no redirection.
    std_err     Device to use for standard error; NULL = no redirection.
    envs_[]     List of environment symbols to define, or NULL.
    </Table>
    If argv is NULL, parses the filename argument into words delimited by
    whitespace and builds the necessary argv table automatically.  Use this
    feature to execute a command with arguments, specified as one string.
    The envv list consists of strings in the form "name=value", ending in a
    NULL pointer.  If the envv argument is null, the environment of the
    current process is passed.  Otherwise the envv environment is used.
    If the process is started correctly, this function will sleep for
    'process_delay' milliseconds.  If the child command detects an error
    at startup, it may exit with an error status.  The sleep allows this
    error to be collected by calling process_status() after this call.  If
    process_delay is 0, any child error is ignored.
    Returns child process id, or 0 if there was an error.
    Under VMS, the filename must have been defined as a command before the
    calling process was started; the path is disregarded.
    Under OS/2 the filename can be the name of a CMD script, and this will
    be run with the interpreter specified in the first line (EXTPROC line,
    or "'/'*!" line; or failing that with the default command interpreter.

    Implementation: Under Unix and OS/2 this function is implemented using
    the process_create_full() function.

    Known bugs: when parsing filename argument into words, does not handle
    quotes in any special way; "this text" is 2 words, '"this' and 'text"'.
    You should have passed the filename through process_esc() before adding
    any optional arguments.
    ---------------------------------------------------------------------[>]-*/

PROCESS
process_create (
    const char *filename,               /*  Name of file to execute          */
    char *argv [],                      /*  Arguments for process, or NULL   */
    const char *workdir,                /*  Working directory, or NULL       */
    const char *std_in,                 /*  Stdin device, or NULL            */
    const char *std_out,                /*  Stdout device, or NULL           */
    const char *std_err,                /*  Stderr device, or NULL           */
    char *envv [],                      /*  Environment variables, or NULL   */
    Bool  wait                          /*  Wait for process to end          */
)
{
#if (defined (__UNIX__) || defined (__OS2__))
    PROC_DATA   procinfo = PROC_DATA_INIT;
    PROCESS     process  = NULL_PROCESS;
    int         error    = 0;            /*  Temporary save of errno         */
    Bool        okay     = TRUE;         /*  Hope for the best...            */
    const char *spacepos = NULL,
               *slashpos = NULL;
#   if (defined (__OS2__))
    const char *pos      = NULL;
#   endif

    ASSERT (filename);
    if (!filename)
        return NULL_PROCESS;

    /*  Set up information to start the new process                          */
    procinfo.filename = filename;
    procinfo.argv     = argv;
    procinfo.workdir  = workdir;
    procinfo.envv     = envv;
    procinfo.wait     = wait;

    /*  Figure out if it is permissable to search the path                   */
    /*  It's permissable if the filename to be run doesn't contain a slash   */
    /*  of its own already.                                                  */
    spacepos = strchr (filename, ' ');
    if (spacepos == NULL)
        spacepos = filename + strlen (filename);
    slashpos = strchr (filename, '/');
#if (defined (__OS2__))
    pos = strchr (filename, '\\');
    if (pos != NULL
    &&  (slashpos == NULL || pos < slashpos))
        slashpos = pos;
#endif
    if (slashpos == NULL || slashpos > spacepos)
        procinfo.searchpath = TRUE;

    /*  We are always allowed to search for interpreters under OS/2; and     */
    /*  don't need to under Unix (because the kernel does it).               */
#if (defined (__OS2__))
    procinfo.intsearch = TRUE;
#endif

    /*  If required, open the file streams for reading/writing.              */
    if (std_in && okay)
      {
        procinfo.in = open (std_in, O_RDONLY | O_NOCTTY);
        if (procinfo.in < 0)
          {
            error = errno;
#if (defined (DEBUG))
            perror ("Error opening stdin");
#endif
            okay  = FALSE;
          }
      }
    if (std_out && okay)
      {
        procinfo.out = open (std_out, O_WRONLY |O_CREAT | O_NOCTTY,
                                      S_IREAD | S_IWRITE);
        if (procinfo.out < 0)
          {
            error = errno;
#if (defined (DEBUG))
            perror ("Error opening stdout");
#endif
            okay = FALSE;
          }
      }
    if (std_err && okay)
      {
        procinfo.err = open (std_err, O_WRONLY | O_CREAT | O_NOCTTY,
                                      S_IREAD | S_IWRITE);
        if (procinfo.err < 0)
          {
            error = errno;
#if (defined (DEBUG))
            perror("Error opening stderr");
#endif
            okay = FALSE;
          }
      }
    /*  If it still looks okay, then lets start that process                 */
    if (okay)
      {
        process = process_create_full (&procinfo);
        if (process == NULL_PROCESS)
            error = procinfo.error;
      }
    /*  Tidy up, and go home                                                 */
    if (procinfo.in  >= 0)
        close (procinfo.in);
    if (procinfo.out >= 0)
        close (procinfo.out);
    if (procinfo.err >= 0)
        close (procinfo.err);

    /*  Stuff value into errno, to emulate old behaviour                     */
    errno = error;
    return (process);

#elif (defined (WIN32))
    PROCESS
        process;                        /*  Our created process handle       */
    STARTUPINFO
        newinfo = {0},                  /*  Specification for new process    */
        curinfo;                        /*  Specification of cur process     */
    PROCESS_INFORMATION
        procinfo;                       /*  Information about created proc   */
    DWORD
        dwCreateFlags = CREATE_NEW_CONSOLE;
    char
        *olddir,                        /*  Caller's working directory       */
        *fulldir,                       /*  Process' working directory       */
        *args,                          /*  Command arguments, if any        */
        *actual_command,                /*  Command, possibly qualified      */
        *buffer = NULL;                 /*  Working buffer                   */
    int
        argn;                           /*  Argument number                  */

    /*  Format full working directory, if specified                          */
    if (workdir)
      {
        olddir = get_curdir ();         /*  Just a lazy way to let the OS    */
        set_curdir (workdir);           /*  figure-out if the workdir is a   */
        fulldir = get_curdir ();        /*  relative or absolute directory.  */
        set_curdir (olddir);
        mem_free (olddir);
      }
    else
        fulldir = NULL;

    /*  Under Windows we accept the magic file header "#!".  If the          */
    /*  caller supplied an argument list, we attach this to the command.     */
    actual_command = redirect_exec (filename);
    strconvch (actual_command, '/', '\\');
    GetShortPathName (actual_command, actual_command,
                              strlen (actual_command) + 1);

    args = strchr (filename, ' ');      /*  Find arguments, if any           */
    if (argv)
      {                                 /*  Build full command buffer        */
        buffer = mem_alloc (tok_text_size ((char **) argv)
                                + strlen (actual_command) + 1);
        strcpy (buffer, actual_command);
        for (argn = 1; argv [argn]; argn++)
            xstrcat (buffer, " ", argv [argn], NULL);
        actual_command = buffer;
      }
    else
    if (args)
      {
        xstrcpy_debug ();
        buffer = xstrcpy (NULL, actual_command, args, NULL);
        actual_command = buffer;
      }
    process = mem_alloc (sizeof (PROC_HANDLE));
    process-> process = NULL;
    process-> in  = redirect_io (std_in,  0, 0, TRUE);
    process-> out = redirect_io (std_out, 0, 0, FALSE);
    process-> err = redirect_io (std_err, 0, 0, FALSE);

    /*  Convert environment to a Windows-type packed block of strings        */
    /*  Use supplied environment, or parent environment if necessary.        */
    process-> envd = strt2descr (envv? (char **) envv: environ);

    GetStartupInfo (&curinfo);
    newinfo.cb          = sizeof (newinfo);
    newinfo.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    newinfo.wShowWindow = SW_HIDE;
    newinfo.hStdInput   = process-> in?  process-> in:  curinfo.hStdInput;
    newinfo.hStdOutput  = process-> out? process-> out: curinfo.hStdOutput;
    newinfo.hStdError   = process-> err? process-> err: curinfo.hStdError;
    newinfo.lpTitle     = NULL;

    /*  If necessary, run in separate VM, for 16-bit programs                */
    if (process_compatible)
        dwCreateFlags |= CREATE_SEPARATE_WOW_VDM;

    /*  CreateProcess returns errors sometimes, even when the process was    */
    /*  started correctly.  The cause is not evident.  For now: we detect    */
    /*  an error by checking the value of procinfo.hProcess after the call.  */
    procinfo.hProcess = NULL;
    CreateProcess (
        NULL,                           /*  Name of executable module        */
        actual_command,                 /*  Command line string              */
        NULL,                           /*  Process security attributes      */
        NULL,                           /*  Thread security attributes       */
        TRUE,                           /*  Handle inheritance flag          */
        dwCreateFlags,                  /*  Creation flags                   */
        process-> envd-> data,          /*  New environment block            */
        fulldir,                        /*  Current directory name           */
        &newinfo,                       /*  STARTUPINFO                      */
        &procinfo);                     /*  PROCESS_INFORMATION              */

    mem_strfree (&fulldir);
    mem_strfree (&buffer);              /*  Deallocate buffer, if used       */

    if (procinfo.hProcess == NULL)      /*  Error, we presume                */
      {
        process_close (process);
        return (NULL);
      }

    /*  Release our hold on the thread                                       */
    CloseHandle (procinfo.hThread);
    process-> process = procinfo.hProcess;

    /*  We do not need access to the files any longer in this process        */
    if (process-> in)
      {
        CloseHandle (process-> in);
        process-> in = NULL;
      }
    if (process-> out)
      {
        CloseHandle (process-> out);
        process-> out = NULL;
      }
    if (process-> err)
      {
        CloseHandle (process-> err);
        process-> err = NULL;
      }

    /*  Wait for the process to finish or be cancelled                       */
    if (wait)
      {
        WaitForSingleObject (procinfo.hProcess, INFINITE);
        process_close (process);
      }
    return (process);

#elif (defined (__VMS__))
    PROCESS
        process;                        /*  Our created process handle       */
    char
        *curdir,                        /*  Current directory                */
        *clean_filename,                /*  Unescaped filename               */
        *full_filename = NULL,
        *full_std_in   = NULL,
        *full_std_out  = NULL;
    qbyte
        process_flags;                  /*  Process creation flags           */
    int
        argn,                           /*  Argument number                  */
        rc;                             /*  Return code from lib$spawn       */
    Bool
        rebuilt_argv = FALSE;           /*  Did we rebuild argv[]?           */

    VMS_STRING (command_dsc, "");       /*  Define string descriptors        */
    VMS_STRING (std_in_dsc,  "");
    VMS_STRING (std_out_dsc, "");

    /*  If argv[] array was not supplied, build it now from filename         */
    if (!argv)
      {
        argv = tok_split (filename);
        filename = argv [0];
        rebuilt_argv = TRUE;
      }
    /*  If filename contains a path or extension, disregard them             */
    clean_filename = strrchr (filename, '/');
    if (clean_filename)
        clean_filename++;
    else
        clean_filename = (char *) filename;
    if (strchr (clean_filename, '.'))
       *strchr (clean_filename, '.') = '\0';

    /*  Rebuild full command from filename and arguments                     */
    full_filename = mem_alloc (tok_text_size ((char **) argv)
                               + strlen (clean_filename) + 1);
    strcpy (full_filename, clean_filename);
    for (argn = 1; argv [argn]; argn++)
        xstrcat (full_filename, " ", argv [argn], NULL);

    /*  Free argument table if we allocated it dynamically here              */
    if (rebuilt_argv)
        tok_free (argv);

    command_dsc.value  = full_filename;
    command_dsc.length = strlen (full_filename);

    /*  Prepare full names for stdin and stdout                              */
    curdir = get_curdir ();
    if (std_in)
      {
        if (strchr (std_in, '/'))       /*  If already with path, use as is  */
            full_std_in = mem_strdup (std_in);
        else
          {
            xstrcpy_debug ();
            full_std_in = xstrcpy (NULL, curdir, "/", std_in, NULL);
          }
        translate_to_vms  (full_std_in);
        std_in_dsc.value = full_std_in;
      }
    if (std_out)
      {
        if (strchr (std_out, '/'))      /*  If already with path, use as is  */
            full_std_out = mem_strdup (std_out);
        else
          {
            xstrcpy_debug ();
            full_std_out = xstrcpy (NULL, curdir, "/", std_out, NULL);
          }
        translate_to_vms   (full_std_out);
        std_out_dsc.value = full_std_out;
      }
    std_in_dsc.length  = std_in?  strlen (std_in_dsc.value): 0;
    std_out_dsc.length = std_out? strlen (std_out_dsc.value): 0;

    /*  If requested, change to working directory                            */
    if (workdir)
        chdir (workdir);

    /*  Prepare process flags                                                */
    if (wait)
        process_flags = 0;
    else
        process_flags = 1;              /*  Bit 1 = don't wait for child     */

    process = mem_alloc (sizeof (PROC_HANDLE));
    process-> id     = 0;
    process-> status = 0;               /*  Completion status                */

/*  char *envv [],  */                  /*  Environment variables, or NULL   */

    rc = lib$spawn (
        &command_dsc,                   /*  Command to run                   */
        std_in?  &std_in_dsc: NULL,     /*  Stdin descriptor                 */
        std_out? &std_out_dsc: NULL,    /*  Stdout+stderr                    */
        &process_flags,                 /*  Options for new process          */
        &NULL,                          /*  Process name -- generated        */
        &process-> id,                  /*  Returned process ID              */
        &process-> status);

    if (workdir)                        /*  Switch back to original dir      */
        chdir (curdir);
    mem_free (curdir);

    mem_strfree (&full_filename);       /*  Deallocate various buffers,      */
    mem_strfree (&full_std_in);         /*    if they were used              */
    mem_strfree (&full_std_out);        /*                                   */

    /*  Return process ID.  If we waited for completion, the process id      */
    /*  is always NULL.                                                      */
    if (rc != 1)                        /*  Process failed with error        */
      {
        process_close (process);
        process = NULL;
      }
    else
    if (wait)                           /*  Finished with process            */
        process_close (process);

    return (process);

#else
    return ((PROCESS) 0);               /*  Not supported on this system     */
#endif
}


#if (defined (WIN32))
/*  --------------------------------------------------------------------------
 *  redirect_io -- local
 *
 *  Redirects the specified file number to the specified device, if the
 *  device name is not null or empty.  If the redirection fails, leaves
 *  the original device unchanged, writes the errno to the error pipe and
 *  exits the current process.  Returns the file handle, or 0 if the
 *  device name was empty or NULL.  Existing files are not truncated.
 */

static HANDLE
redirect_io (const char *device, int fileno, int err_pipe, Bool read_only)
{
    HANDLE
        file_handle = 0;                /*  Opened file handle               */

    /*  If device name is not null, and not empty, redirect it               */
    if (device && *device)
      {
        SECURITY_ATTRIBUTES
            g_sa = { sizeof (SECURITY_ATTRIBUTES), NULL, TRUE };
        char
            *short_path;
        MSG Msg;
        int waitCount;

        /*  Get the path without long file name                              */
        short_path = mem_strdup (device);
        if (short_path)
          {
            strconvch (short_path, '/', '\\');
            GetShortPathName (short_path, short_path, strlen (short_path) + 1);
          }
        if (read_only)
          {
            for (waitCount = 0; waitCount < 5; waitCount++)
              {
                file_handle = CreateFile (short_path, GENERIC_READ,
                                          FILE_SHARE_READ, &g_sa, OPEN_ALWAYS,
                                          FILE_ATTRIBUTE_NORMAL, NULL);
                if (file_handle != INVALID_HANDLE_VALUE)
                    break;
                /*  Yield CPU time                                           */
                PeekMessage (&Msg, NULL, 0, 0, PM_NOREMOVE);
                Sleep (1000);
              }
            if (waitCount == 5)
                file_handle = 0;        /*  Did not succeed                  */
          }
        else
          {
            /*  Open the file for appending, and move pointer to file end    */
            file_handle = CreateFile (short_path, GENERIC_READ | GENERIC_WRITE,
                                      FILE_SHARE_READ + FILE_SHARE_WRITE,
                                      &g_sa, OPEN_ALWAYS,
                                      FILE_ATTRIBUTE_NORMAL, NULL);
            SetFilePointer (file_handle, 0, NULL, FILE_END);
          }
        if (short_path != device)
            mem_strfree (&short_path);
      }
    return (file_handle);
}
#endif


#if (defined (__OS2__) || defined (__UNIX__))
/*  --------------------------------------------------------------------------
 *  redirect_io_fh -- local
 *
 *  Under OS/2: Duplicates the destfh to a safe location (ie, save a backup
 *  copy of it.  Then duplicates the srcfh into the destfh.  Returns the
 *  backup of the original destfh, which can be used to undo the redirection
 *  later.  If errors are encountered -2 is returned.
 *
 *  Under Unix: Duplicates srcfh onto destfh.  Returns -2 if this fails, or
 *  0 if it works.
 */
static HANDLE redirect_io_fh (int srcfh, int destfh)
{
#if (defined (__OS2__))
    int
        dupe_file_handle = 0;

    dupe_file_handle = dup (destfh);
    if (dupe_file_handle <= -1)
        return (-2);                    /*  Cannot acomplish redirection     */

    /*  Let dup2() close destfh (if open) if duplication suceeds             */
    if (dup2 (srcfh, destfh) != destfh)
      {
        close (dupe_file_handle);       /*  Close unneeded duplicate         */
        return (-2);                    /*  Cannot accomplish redirection    */
      }

    return (dupe_file_handle);          /*  Return copy of file handle       */

#elif (defined (__UNIX__))
    /*  Let dup2() close destfh (if open) if duplication suceeds             */
    if (dup2 (srcfh, destfh) != destfh)
        return (-2);                    /*  Cannot accomplish redirection    */

    return (0);                         /*  All went well.                   */

#else
#   error redirect_io_fh not defined for your operating system
#endif
}
#endif

#if (defined (__OS2__))
/*  --------------------------------------------------------------------------
 *  restore_redirection -- local
 *
 *  If the file handles for old_stdin, old_stdout, old_stderr, are zero or
 *  greater then duplicate those file handles over stdin, stdout, stderr
 *  respectively, and close the old file handles.  Each of the file handles
 *  is considered seperately.
 *
 *  This is primarily used to restore the file handles after IO redirection.
 */

static void
restore_redirection (HANDLE old_stdin, HANDLE old_stdout, HANDLE old_stderr)
{
    if (old_stdin >= 0)
      {
        dup2 (old_stdin, STDIN_FILENO);
        if (old_stdin != STDIN_FILENO)
           close (old_stdin);
      }
    if (old_stdout >= 0)
      {
        dup2 (old_stdout, STDOUT_FILENO);
        if (old_stdout != STDOUT_FILENO)
           close (old_stdout);
      }
    if (old_stderr >= 0)
      {
        close (STDERR_FILENO);
        dup2 (old_stderr, STDERR_FILENO);
        if (old_stderr != STDERR_FILENO)
           close (old_stderr);
      }
}
#endif


#if (defined (WIN32))
/*  --------------------------------------------------------------------------
 *  redirect_exec -- local
 *
 *  NOTE: This version is depreciated in favour of redirect_exec_full()
 *  for use with process_create_full().  The single argument version may
 *  go away completely.
 *
 *  If the specified file is an executable script (it starts with the bytes
 *  "#!"), then extracts the script interpreter name from the first line
 *  of the file, and prepares a new command consisting of the interpreter
 *  name followed by the command.  This emulates the UNIX action, e.g. to
 *  run a Perl script, the script starts with a line "#! /usr/bin/perl".
 *  If the combined command is too long it is truncated, brutally.  If the
 *  filename does not contain '/', searches the PATH for the file.
 *  Does not return any arguments following the command.  The characters
 *  '/''*''!' are treated as equivalent to '#!'.  If the interpreter name
 *  contains a path (e.g. '/usr/bin') but does not exist, the path is
 *  removed so that the executable can be located on the PATH.
 *
 *  Under OS/2 the EXTPROC line will be scanned for in the same way as the
 *  "#!" and "'/'*!" lines above.  The EXTPROC line should _not_ be used to
 *  invoke a command processor (but the "'/'*!" line can be), since some
 *  command processors (eg, 4OS/2, see page 92 of version 4 manual) will
 *  scan the EXTPROC line and invoke the program in it (ie, the command
 *  processor) again.  Repeat until the heat death of the universe, or
 *  running out of resources, whichever comes first.
 */

#define COMMAND_MAX         1024        /*  Program name with path           */

static char *
redirect_exec (const char *command)
{
    static char
        buffer [COMMAND_MAX + 1];       /*  Working buffer                   */
    char
        *first_space,                   /*  Cut buffer into filename + args  */
        *full_filename,                 /*  Filename with path               */
        *arguments = NULL,              /*  Program arguments if any         */
        input_char;                     /*  Character read from file stream  */
    int
        buffer_index;                   /*  Index into buffer                */
    FILE
        *stream;                        /*  File input stream                */
    Bool
        redirected;                     /*  Did we redirect the filename?    */

    /*  Copy command to buffer, but don't let it overflow                    */
    strncpy (buffer, command, COMMAND_MAX);
    buffer [COMMAND_MAX] = '\0';
    strconvch (buffer, '\\', '/');

    /*  Now truncate at first space to separate filename from arguments.     */
    /*  Caller should have used process_esc() somewhere to escape spaces...  */
    first_space = strchr (buffer, ' ');
    if (first_space)
        *first_space = '\0';

    process_unesc (buffer, buffer);     /*  Unescape any spaces in filename  */
    redirected = FALSE;

    /*  Now look for the file on the PATH, unless it already has a path      */
    if (strchr (buffer, '/') == NULL)
      {
        full_filename = file_where ('r', "PATH", buffer, NULL);
#if (defined (__OS2__))
        /*  Special case for .CMD scripts, so we don't have to specify the   */
        /*  whole name, and thus they run like they would in a shell.        */
        if (full_filename == NULL)
           full_filename = file_where ('r', "PATH", buffer, ".cmd");
#endif
      }
    else
      {
        full_filename = file_where ('r', NULL, buffer, NULL);
#if (defined (__OS2__))
        /*  Special case for .CMD scripts, so we don't have to specify the   */
        /*  whole name, and thus they run like they would in a shell.        */
        if (full_filename == NULL)
           full_filename = file_where ('r', NULL, buffer, ".cmd");
#endif
      }

    if (full_filename)
      {
        /*  Open the file, and check whether it matches the "#!" rule        */
        full_filename = mem_strdup (full_filename);
        stream = file_open (full_filename, 'r');
        if (stream)
          {
            input_char = fgetc (stream);
            if ((input_char == '#' && fgetc (stream) == '!')
            ||  (input_char == '/' && fgetc (stream) == '*'
                                   && fgetc (stream) == '!')
#if (defined (__OS2__))
            /*  Look for EXTPROC line, in both capitals and lower case       */
            /*  NOTE: If the EXTPROC line happens to specify a command       */
            /*  processor that understands EXTPROC lines then if it is       */
            /*  poorly written (eg 4OS/2) it may attempt to run itself       */
            /*  over the script repeatedly until running out of memory       */

            /*  NOTE: we work in a round about way because toupper may       */
            /*  be a macro, and we don't want to call fgetc() too much       */

            ||  (                                toupper(input_char) == 'E' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'X' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'T' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'P' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'R' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'O' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'C')
#endif
            )
              {
                /*  It matches, so skip 0 or more spaces and pick-up the     */
                /*  interpreter name                                         */
                do
                    input_char = fgetc (stream);
                until (input_char != ' ');

                /*  Read up to COMMAND_MAX chars; stop at end of line        */
                for (buffer_index = 0;
                     buffer_index < COMMAND_MAX;
                     buffer_index++)
                  {
                    buffer [buffer_index] = input_char;
                    input_char = fgetc (stream);
                    if (input_char == '\n'
                    ||  input_char == '\r')
                        break;
                  }
                /*  Terminate the buffer cleanly                             */
                redirected = (buffer_index > 0);
                buffer [++buffer_index] = '\0';

                /*  Strip trailing spaces and OS/2 end of comment            */
                strcrop (buffer);
                buffer_index = strlen (buffer);
                if (buffer [buffer_index - 1] == '/'
                &&  buffer [buffer_index - 2] == '*')
                  {
                    buffer [buffer_index - 2] = '\0';
                    strcrop (buffer);
                  }
                /*  Remove and save arguments after program name, if any     */
                first_space = strchr (buffer, ' ');
                if (first_space)
                  {
                    arguments = mem_strdup (first_space);
                    *first_space = '\0';
                  }
                /*  If buffer contains path, but can't be found, kill path   */
                if (!file_is_program (buffer))
                    strip_file_path (buffer);
              }
            file_close (stream);
          }
        /*  Prepare full command name in buffer                              */
        if (redirected)
          {                             /*  Put quotes around argument       */
            if (file_is_executable (buffer))
                strcpy (buffer, file_exec_name (buffer));
            if (arguments)
                strcat (buffer, arguments);
            strncat (buffer, " \"",         COMMAND_MAX - strlen (buffer));
            strncat (buffer, full_filename, COMMAND_MAX - strlen (buffer));
            strncat (buffer, "\"",          COMMAND_MAX - strlen (buffer));
          }
        else
            strcpy (buffer, full_filename);

        mem_strfree (&arguments);
        mem_strfree (&full_filename);
      }
    /*  If we did not find the file as specified, but the file is directly   */
    /*  executable, format and return a name with an .exe, .com, .cmd, or    */
    /*  .bat extension (as is appropriate).  Otherwise the filename is in    */
    /*  buffer.                                                              */
    if (!redirected && file_is_program (buffer))
        return (file_where ('r', "PATH", file_exec_name (buffer), NULL));
    else
        return (buffer);
}
#endif

#if (defined (__OS2__))
/*  --------------------------------------------------------------------------
 *  redirect_exec_full -- local
 *
 *  NOTE: This is the same as redirect_exec(), but takes additional arguments
 *  to add flexibility.  Once all of the code in this file has been converted
 *  to use the additional arguments, this should be renamed redirect_exec(),
 *  and the old version removed.
 *
 *  If the specified file is an executable script (it starts with the bytes
 *  "#!"), then extracts the script interpreter name from the first line
 *  of the file, and prepares a new command consisting of the interpreter
 *  name followed by the command.  This emulates the UNIX action, e.g. to
 *  run a Perl script, the script starts with a line "#! /usr/bin/perl".
 *  If the combined command is too long it is truncated, brutally.  If the
 *  filename does not contain '/', searches the PATH for the file.
 *  Does not return any arguments following the command.  The characters
 *  '/''*''!' are treated as equivalent to '#!'.  If the interpreter name
 *  contains a path (e.g. '/usr/bin') but does not exist, the path is
 *  removed so that the executable can be located on the PATH.
 *
 *  Under OS/2 the EXTPROC line will be scanned for in the same way as the
 *  "#!" and "'/'*!" lines above.  The EXTPROC line should _not_ be used to
 *  invoke a command processor (but the "'/'*!" line can be), since some
 *  command processors (eg, 4OS/2, see page 92 of version 4 manual) will
 *  scan the EXTPROC line and invoke the program in it (ie, the command
 *  processor) again.  Repeat until the heat death of the universe, or
 *  running out of resources, whichever comes first.
 *
 *  XXX: It'd be nice if this function didn't use/return a static buffer,
 *  but file_where returns a static buffer so a lot would need to change.
 */

#   if (!defined(COMMAND_MAX))
#       define COMMAND_MAX 1024         /*  Program name with path           */
#   endif

static char *redirect_exec_full (const char *command, Bool searchpath,
                                 const char *suppliedpath,
                                 const char **searchext)
{
    static char
        buffer [COMMAND_MAX + 1];       /*  Working buffer                   */
    const char
        *path = suppliedpath;           /*  Path to search along             */
    const char
        **extensions = searchext;       /*  Extensions to try on command     */
    char
        *first_space,                   /*  Cut buffer into filename + args  */
        *full_filename,                 /*  Filename with path               */
        *arguments = NULL,              /*  Program arguments if any         */
        input_char;                     /*  Character read from file stream  */
    int
        buffer_index;                   /*  Index into buffer                */
    FILE
        *stream = NULL;                 /*  File input stream                */
    Bool
        redirected = FALSE;             /*  Did we redirect the filename?    */

    ASSERT(command);
    if (!command)
        return (NULL);
    if (!extensions)
        extensions = default_ext;       /*  Use default extensions for OS    */
    if (!path)
        path = "PATH";                  /*  Default path to search           */

    /*  Copy command to buffer, but don't let it overflow                    */
    strncpy (buffer, command, COMMAND_MAX);
    buffer [COMMAND_MAX] = '\0';
    strconvch (buffer, '\\', '/');

    /*  Now truncate at first space to separate filename from arguments.     */
    /*  Caller should have used process_esc() somewhere to escape spaces...  */
    first_space = strchr (buffer, ' ');
    if (first_space)
        *first_space = '\0';

    process_unesc (buffer, buffer);     /*  Unescape any spaces in filename  */
    redirected = FALSE;

    /*  We look for the file on the path, if search path is true             */
    /*  We first try the filename just as we got it, possibly without any    */
    /*  extensions, and then if that didn't work, we try our default         */
    /*  extensions (and optionally mandatory extensions).                    */

    if (searchpath)
        full_filename = file_where_ext ('r', path, buffer, NULL);
    else
        full_filename = file_where_ext ('r', NULL, buffer, NULL);

    if (! full_filename)
      {
        if (searchpath)
            full_filename = file_where_ext ('r', path, buffer, extensions);
        else
            full_filename = file_where_ext ('r', NULL, buffer, extensions);
      }

    if (full_filename)
      {
        /*  Open the file, and check whether it matches the "#!" rule        */
        full_filename = mem_strdup (full_filename);
        stream = file_open (full_filename, 'r');
        if (stream)
          {
            input_char = fgetc (stream);
            if ((input_char == '#' && fgetc (stream) == '!')
            ||  (input_char == '/' && fgetc (stream) == '*'
                                   && fgetc (stream) == '!')
#   if (defined (__OS2__))
            /*  Look for EXTPROC line, in both capitals and lower case       */
            /*  NOTE: If the EXTPROC line happens to specify a command       */
            /*  processor that understands EXTPROC lines then if it is       */
            /*  poorly written (eg 4OS/2) it may attempt to run itself       */
            /*  over the script repeatedly until running out of memory       */

            /*  NOTE: we work in a round about way because toupper may       */
            /*  be a macro, and we don't want to call fgetc() too much       */

            ||  (                                toupper(input_char) == 'E' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'X' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'T' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'P' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'R' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'O' &&
                 (input_char = fgetc(stream)) && toupper(input_char) == 'C')
#   endif
            )
              {
                /*  It matches, so skip 0 or more spaces and pick-up the     */
                /*  interpreter name                                         */
                do
                    input_char = fgetc (stream);
                until (input_char != ' ');

                /*  Read up to COMMAND_MAX chars; stop at end of line        */
                for (buffer_index = 0;
                     buffer_index < COMMAND_MAX;
                     buffer_index++)
                  {
                    buffer [buffer_index] = input_char;
                    input_char = fgetc (stream);
                    if (input_char == '\n'
                    ||  input_char == '\r')
                        break;
                  }
                /*  Terminate the buffer cleanly                             */
                redirected = (buffer_index > 0);
                buffer [++buffer_index] = '\0';

                /*  Strip trailing spaces and OS/2 end of comment            */
                strcrop (buffer);
                buffer_index = strlen (buffer);
                if (buffer [buffer_index - 1] == '/'
                &&  buffer [buffer_index - 2] == '*')
                  {
                    buffer [buffer_index - 2] = '\0';
                    strcrop (buffer);
                  }
                /*  Remove and save arguments after program name, if any     */
                first_space = strchr (buffer, ' ');
                if (first_space)
                  {
                    arguments = mem_strdup (first_space);
                    *first_space = '\0';
                  }
                /*  If buffer contains path, but can't be found, kill path   */
                if (!file_is_program (buffer))
                    strip_file_path (buffer);
              }
            file_close (stream);
          }
        /*  Prepare full command name in buffer                              */
        if (redirected)
          {                             /*  Put quotes around argument       */
            if (file_is_executable (buffer))
                strcpy (buffer, file_exec_name (buffer));
            if (arguments)
                strcat (buffer, arguments);
            strncat (buffer, " \"",         COMMAND_MAX - strlen (buffer));
            strncat (buffer, full_filename, COMMAND_MAX - strlen (buffer));
            strncat (buffer, "\"",          COMMAND_MAX - strlen (buffer));
          }
        else
            strcpy (buffer, full_filename);

        mem_strfree (&arguments);
        mem_strfree (&full_filename);
      }

    /*  If we did not find the file as specified, but the file is directly   */
    /*  executable, format and return a name with a suitable extension.      */
    /*  Otherwise the filename is in buffer.                                 */

    if (!redirected && file_is_program (buffer))
    {
        char *exec_name = file_exec_name (buffer);
        if (exec_name != NULL)
        {
            if (searchpath)
                return (file_where ('r', path, exec_name, NULL));
            else
                return exec_name;
        }
        else
            return (NULL);
    }
    else
        return (buffer);
}
#endif

#if (defined (__OS2__))
/*  --------------------------------------------------------------------------
 *  free_argv -- local
 *
 *  Frees an char *argv[] style array, freeing all the elements, and the array
 *  of pointers.  If tokenarray is true, it is assumed to be a sfltok style
 *  token array, and is freed with tok_free().  Otherwise it is assumed to
 *  contain strings allocated by strdupl() or similiar, and the strings are
 *  freed with strfree().
 */
static void
free_argv (char **argv, Bool tokenarray)
{
  ASSERT (argv);
  if (!argv)
      return;

  if (tokenarray)
      tok_free (argv);
  else
    {
      char **ptr = argv;
      while (*ptr != NULL)
        {
          strfree(ptr);
          ++ptr;
        }
      mem_free(argv);
    }
}
#endif

#if (defined (__OS2__) || defined (__UNIX__))
/*   -------------------------------------------------------------------------
 *   prefix_argv_with_shell -- local
 *
 *   Returns a new argv style array which starts with an invocation of the
 *   shell to run a command, and ends with a copy of the existing argv.  Once
 *   this returns, the original argv can be freed if desired (strings are
 *   copied with strdupl()).  If shell is NULL, then the operating system
 *   default shell is used.
 *
 *   Returns either the new argv, or NULL to indicate an error.
 */
static char **
prefix_argv_with_shell (char **argv, const char *shell)
{
/*  TODO: Possibly this should be changed on the fly to "-c" if the shell  */
/*  chosen is one that is *sh like; and left as /c for cmd.exe/4os2.exe etc*/
#if (defined (__OS2__))
#   define SHELL_RUN_COMMAND "/c"
#elif (defined (__UNIX__))
#   define SHELL_RUN_COMMAND "-c"
#else
#   error  Do not know how to tell shell to run a command
#endif
    char
        **newargs = NULL,
        *command_processor = NULL;

    ASSERT (argv);
    ASSERT (!command_processor || *command_processor);
    if (!argv)
        return (NULL);

    if (shell)
        command_processor = strdupl (shell);
    else
#if   (defined (__OS2__))
        command_processor = strdupl (env_get_string ("COMSPEC", ""));
#elif (defined (__UNIX__))
        command_processor = strdupl (env_get_string ("SHELL", ""));
#else
#   error Do not know how to figure out default shell
#endif

    if (command_processor && *command_processor != '\0')
      {                                 /*  Determine command processor args */
        char
            **cmdargs = NULL;
        int
            num_new = 0,
            num_existing = 0;
        Bool
            success = FALSE;

        cmdargs = tok_split (command_processor);
        if (!cmdargs)
            return NULL;

        /*  Count the number of existing and new arguments (at least 1 new)  */
        for (num_existing = 0; argv[num_existing] != NULL; num_existing++)
            ;    /* EMPTY_BODY */
        for (num_new = 0; cmdargs[num_new] != NULL; num_new++)
            ;    /* EMPTY BODY */

        ASSERT (num_new >= 1);

        /*  Now merge those arguments with script name                       */
        /*  Need: num_new + 1 to tell shell to run command + num_existing    */
        /*        + 1 to terminate array                                     */
        newargs = mem_alloc ((num_new+1 + num_existing+1) * sizeof (char *));

        if (newargs != NULL)
          {
            /*  Okay, copy all the arguments into place                      */
            int
                i = 0;
            for (i = 0; i < num_new; i++)
                newargs [i] = strdupl (cmdargs [i]);

            newargs [num_new++] = strdupl (SHELL_RUN_COMMAND);
            for (i = 0; i < num_existing; i++)
                newargs [num_new++] = strdupl (argv [i]);
            newargs [num_new] = NULL;

            /*  Free the token array of command arguments                    */
            tok_free (cmdargs);

            /*  Looks okay, check that everything got allocated correctly    */
            success = TRUE;
            for (i = 0; i < num_new; i++)
                if (newargs [i] == NULL)
                    success = FALSE;

            if (!success)
              {
                for (i = 0; i < num_new; i++)
                  if (newargs [i] != NULL)
                      strfree (&newargs [i]);

                mem_free(newargs);
                newargs = NULL;
              }
          }
      }
    /*  Free the command processor string                                    */
    if (command_processor)
        strfree (&command_processor);
    return newargs;
}
#endif

#if (defined (__OS2__) || defined (__UNIX__))
/*  --------------------------------------------------------------------------
 *  merge_environment -- local
 *
 *  Creates a new environment variable bundle which contains the entries from
 *  curenv, with the entries from envadd put in (overwriting any existing
 *  entries of that name), and the entries for the keys in envrm removed.
 *
 *  curenv may be NULL, in which case the processes current environment is
 *  used.  If envadd or envrm are NULL then no change is made for that part.
 *
 *  Returns the new environment variable bundle, or NULL if errors encountered.
 *
 *  When the environment is no longer required it should be freed with
 *  strtfree().
 *
 *  NOTE: strt2symb() is used to convert the environment to a symbol table,
 *  rather than env2symb(), so no conversions are applied to the strings.
 *  The environment should be "ready to go" prior to using this function.
 */
static char **
merge_environment (char **cur_env, SYMTAB *envadd, SYMTAB *envrm)
{
  int
    rc = 0;
  SYMTAB
    *envtable = NULL;
  char
    **new_env = NULL,
    **base_env;

    base_env = cur_env? cur_env: environ;
    ASSERT (base_env);
    if (!base_env)
        return NULL;

    ASSERT (envadd || envrm);     /*  Should be doing some translation       */

    /*  If no changes are required, just return copy of base environment     */
    if (!envadd && !envrm)
        return (env_copy (base_env));

    envtable = strt2symb (cur_env);
    if (envtable == NULL)
        return (NULL);

    if (envadd)
      {
        rc = sym_merge_tables (envtable, envadd);
        ASSERT (rc > 0);                /*  0 = nothing imported; +ve okay   */
        if (rc < 0)                     /*  -ve means error during import    */
          {
            sym_delete_table (envtable);
            return (NULL);
          }
      }
    if (envrm)
      {
        /*  To remove the symbols we process the whole envrm table,          */
        /*  removing symbols from the main table                             */
        rc = sym_exec_all (envrm, helper_remove_symbol, envtable);
        ASSERT (rc > 0);                /*  0 = nothing imported; +ve okay   */
        if (rc < 0)                     /*  -ve means error during import    */
          {
            sym_delete_table (envtable);
            return (NULL);
          }
    }

    /*  Now turn the symbol table back into a set of environment variables   */
    new_env = symb2env (envtable);

    /*  Free up the symbol table, and exit.                                  */
    sym_delete_table (envtable);

    return (new_env);
}


/*  --------------------------------------------------------------------------
 *  helper_remove_symbol -- local
 *
 *  Helper function to remove symbols from a supplied table.
 *
 *  Extracting the argument that we want to the function is rather tricky due
 *  to the very unfortunate prototype required by sym_exec_all().
 *
 *  We have to have variable length arguments, even though sym_exec_all() will
 *  only ever give us one argument, which is a va_list which contains the
 *  arguments the caller to sym_exec_all() wants to pass to us.  So to get
 *  our argument:
 *  1.  We need to get the va_list that is passed to us, by using another
 *      va_list, and extracting the first argument.
 *  2.  Having got that, we must make a copy of the va_list entry, so
 *      that hopefully our use of va_arg doesn't disturb the list for
 *      _next_time_.  (WARNING: Unportable assumptions about va_list;
 *      for some implementations a shallow copy of va_list may be
 *      insufficient  Should work for most reasonable implementations.).
 *  3.  With that copy we can use va_arg to get our symbol table.
 *
 *  Hopefully at some stage the prototype required by sym_exec_all can be
 *  improved.
 *
 *  This function always returns TRUE, even if the delete fails because
 *  the most likely reason for it to fail is that it does not exist (which
 *  is good).
 *
 *  --------------------------------------------------------------------------
 */

static Bool
helper_remove_symbol (SYMBOL *refsym, ...)
{
    va_list
       args_from_sym_exec,            /*  arguments that we received         */
       args_to_sym_exec,              /*  argument list that we want         */
       ourargs;                       /*  our copy of that argument list     */
    SYMTAB
       *table = NULL;                 /*  Table to manipulate                */
    SYMBOL
       *sym   = NULL;                 /*  Symbol to remove, in table         */

    /*  Get the pointer to the symbol table to modify.                       */
    /*  the args_to_sym_exec have already been va_list'd so we don't do that */
    /*  We also don't va_end either the args_to_sym_exec or ourargs, to      */
    /*  reduce the chance of inadvertantly affecting the structure.  This    */
    /*  may leak memory.                                                     */

    va_start (args_from_sym_exec, refsym);
    args_to_sym_exec = va_arg (args_from_sym_exec, va_list);
    memcpy (&ourargs, &args_to_sym_exec, sizeof(va_list));
    table = va_arg (ourargs, SYMTAB*);
    va_end (args_from_sym_exec);

    ASSERT (table);
    ASSERT (refsym);
    if (!table || !refsym)
        return FALSE;

    /*  Remove all matching symbols from the table                           */
    sym = sym_lookup_symbol (table, sym_get_name (refsym));

    while (sym)
        sym = sym_delete_symbol (table, sym);

    return TRUE;
}
#endif

#if (defined (__VMS__))
/*  --------------------------------------------------------------------------
 *  translate_to_vms -- local
 *
 *  Translates POSIX style filename /top/path2/path2/filename into OpenVMS
 *  style filename top:[path1.path2]filename, which is always the same size.
 *  Does nothing if the filename is not valid, i.e. with at least a top,
 *  one path component, and a filename.
 */

static void
translate_to_vms (char *filename)
{
    char
        *path_start,
        *path_end;

    /*  Filename must start with '/'                                         */
    if (*filename != '/')
        return;

    /*  Find start and end of file path                                      */
    path_start = strchr  (filename + 1, '/');
    path_end   = strrchr (filename, '/');
    if (path_start == NULL || path_start == path_end)
        return;                         /*  Badly-formed filename            */

    path_start--;
    memmove (filename, filename + 1, path_start - filename);
    *path_start++ = ':';
    *path_start++ = '[';
    *path_end     = '\0';               /*  Cut string before filename       */
    strconvch (path_start, '/', '.');   /*    and replace slashes by dots    */
    *path_end     = ']';                /*  Finally, add ']' after path      */
}
#endif


/*  ---------------------------------------------------------------------[<]-
    Function: process_status

    Synopsis: Returns status of process specified by process ID.  Returns
    one of these values, or -1 if there was an error:
    <Table>
    PROCESS_RUNNING       Process is still running.
    PROCESS_ENDED_OK      Process ended normally.
    PROCESS_ENDED_ERROR   Process ended with an error status.
    PROCESS_INTERRUPTED   Process was interrupted (killed).
    </Table>
    In the case of PROCESS_ENDED_ERROR, the global variable process_errno is
    set to the exit code returned by the process.
    ---------------------------------------------------------------------[>]-*/

int
process_status (
    PROCESS process)
{
#if (defined (__UNIX__) || defined (__OS2__))
    int
        status;
    pid_t
        return_pid;

    /*  waitpid() returns 0 if the child process is still running, or the    */
    /*  process id if it stopped.  It can also return -1 in case of error.   */
    /*  No other return value is possible.                                   */

    return_pid = waitpid (process, &status, WNOHANG | WUNTRACED);
    if (return_pid == 0)
        return (PROCESS_RUNNING);
    else
    if (return_pid == process)
      {
        if (WIFEXITED (status))        /*  Program called exit()             */
          {
            process_errno = WEXITSTATUS (status);
            if (process_errno)         /*  Treat exit (0) as normal end      */
                return (PROCESS_ENDED_ERROR);
            else
                return (PROCESS_ENDED_OK);
          }
        else
        if (WIFSIGNALED (status))       /*  Process was interrupted          */
            return (PROCESS_INTERRUPTED);
        else
            return (PROCESS_ENDED_OK);
      }
    else
        return (-1);

#elif (defined (WIN32))
    DWORD
         status;

    ASSERT (process);
    status = WaitForSingleObject (process-> process, 0);

    if (status == WAIT_TIMEOUT)
        return (PROCESS_RUNNING);
    else
    if (status == WAIT_OBJECT_0)
        return (PROCESS_ENDED_OK);
    else
    if (status == WAIT_ABANDONED)
        return (PROCESS_ENDED_ERROR);
    else
        return (-1);

#elif (defined (__VMS__))
    ASSERT (process);
    if (process-> status == 0)
        return (PROCESS_RUNNING);
    else
        return (PROCESS_ENDED_OK);

#else
    return (-1);                        /*  Not supported on this system     */
#endif
}


/*  ---------------------------------------------------------------------[<]-
    Function: process_kill

    Synopsis: Ends a process specified by a process id.  The current process
    must have the appropriate authority to stop the specified process.
    Returns zero if the process was killed, -1 if there was an error.
    ---------------------------------------------------------------------[>]-*/

int
process_kill (
    PROCESS process)
{
#if (defined (__UNIX__) || defined (__OS2__))
    int count = 5;

    /*  First give it a chance to gracefully exit...                         */
    kill (process, SIGTERM);
    while (process_status (process) == PROCESS_RUNNING && count--)
        sleep (1);

    /*  Then get brutal if neccessary.                                       */
    if (process_status (process) == PROCESS_RUNNING)
      {
        kill (process, SIGKILL);
        while (process_status (process) == PROCESS_RUNNING)
            sleep (1);
      }
    return (0);

#elif (defined (WIN32))
    ASSERT (process);
    TerminateProcess (process-> process, 1);
    while (process_status (process) == PROCESS_RUNNING)
        Sleep (100);

    process_close (process);
    return (0);

#elif (defined (__VMS__))
    ASSERT (process);
    sys$delprc (process-> id);
    process_close (process);
    return (0);

#else
    return (-1);                        /*  Not supported on this system     */
#endif
}


/*  ---------------------------------------------------------------------[<]-
    Function: process_close

    Synopsis: You should call this function when a process has ended
    normally, if you did not specify the wait option when calling the
    process_create() function.  On some systems, each created process
    uses some memory.  process_close() guarantees that this memory is
    correctly freed.  Does nothing if the process handle is NULL.
    ---------------------------------------------------------------------[>]-*/

void
process_close (
    PROCESS process)
{
#if (defined (WIN32))
    if (process)
      {
        if (process-> process)
            CloseHandle (process-> process);
        if (process-> in)
            CloseHandle (process-> in);
        if (process-> out)
            CloseHandle (process-> out);
        if (process-> err)
            CloseHandle (process-> err);

        mem_free (process-> envd);
        mem_free (process);
      }

#elif (defined (__VMS__))
    mem_free (process);

#endif
}


/*  ---------------------------------------------------------------------[<]-
    Function: process_server

    Synopsis: Converts the process from an interactive foreground process
    into a background process.  Depending on the system either the existing
    process becomes a background process, or a new process is started as
    a background process and the existing process terminates.
    
    Requires the original command-line arguments as passed to the main()
    function.  If a new process is started, any arguments that match any
    of the values in the (NULL terminated) 'sswitch' array will be omitted
    from the arguments to the new process.  You should specify the
    command-line switch(es) your main program uses to run as a background
    service.   If it returns, returns 0 if okay, and returns -1 if there
    was an error.

    The precise effect of this function depends on the system.  On UNIX,
    does this:
    <LIST>
    Switches the process to run as a background job, under init;
    closes all open files;
    moves to a safe, known working directory, if required;
    sets the umask for new files;
    opens stdin, stdout, and stderr to the null device;
    enforces exclusive execution through a lock file, if required;
    logs the process id in the lock file;
    ignores the hangup unwanted signals.
    </LIST>
    On OS/2, starts a new copy of the program up, detached, and running
    separately from the current process, and if successful, the existing
    process exits.

    On other systems does nothing except return 0.
    ---------------------------------------------------------------------[>]-*/

int
process_server (
    const char *workdir,                /*  Where server runs, or NULL/""    */
    const char *lockfile,               /*  For exclusive execution          */
    int   argc,                         /*  Original command-line arguments  */
    char *argv [],                      /*  Original command-line arguments  */
    const char *sswitch [])             /*  Filter these options from argv   */
{
#if (defined (__UNIX__))
    int
        fork_result,
        file_handle;
    char
        pid_buffer [10];
    struct flock
        lock_file;                      /*  flock() argument block           */
#endif
    int
        argi = 0,                       /*  Input arguments iterator         */
        argo = 0;                       /*  Output arguments iterator        */
    char
        **newargv = NULL;               /*  Array of new arguments           */

    newargv = malloc (argc * sizeof (char *));
    if (newargv == NULL)
        return (-1);

    /*  Copy the arguments across, skipping any in sswitch                   */
    for (argi = argo = 0; argi < argc; argi++)
      {
      	Bool
      	    copy_argument = TRUE;
      	int
      	    i = 0;

      	for (i = 0; sswitch != NULL && sswitch [i] != NULL; i++)
      	  {
            if (strcmp (argv [argi], sswitch [i]) == 0)
                copy_argument = FALSE;
          }

        if (copy_argument)
            newargv [argo++] = argv [argi];
      }

    /*  Terminate the new argument array                                     */
    newargv [argo] = NULL;

#if (defined (__UNIX__))
    /*  We recreate our process as a child of init.  The process continues   */
    /*  to exit in the background.  UNIX calls wait() for all children of    */
    /*  the init process, so the server will exit cleanly.                   */

    fork_result = fork ();
    if (fork_result < 0)                /*  < 0 is an error                  */
        return (-1);                    /*  Could not fork                   */
    else
    if (fork_result > 0)                /*  > 0 is the parent process        */
        exit (EXIT_SUCCESS);            /*  End parent process               */

    /*  We close all open file descriptors that may have been inherited      */
    /*  from the parent process.  This is to reduce the resources we use.    */

    for (file_handle = FILEHANDLE_MAX - 1; file_handle >= 0; file_handle--)
        close (file_handle);            /*  Ignore errors                    */

    /*  We move to a safe and known directory, which is supplied as an       */
    /*  argument to this function (or not, if workdir is NULL or empty).     */

    if (workdir && strused (workdir))
        chdir (workdir);

    /*  We set the umask so that new files are given mode 750 octal          */

    umask (027);                        /*  Complement of 0750               */

    /*  We set standard input and output to the null device so that any      */
    /*  functions that assume that these files are open can still work.      */

    file_handle = open ("/dev/null", O_RDWR);    /*  stdin = handle 0        */
    dup (file_handle);                           /*  stdout = handle 1       */
    dup (file_handle);                           /*  stderr = handle 2       */

    /*  We enforce a lock on the lockfile, if specified, so that only one    */
    /*  copy of the server can run at once.  We return -1 if the lock fails. */
    /*  This locking code might be better isolated into a separate package,  */
    /*  since it is not very portable between unices.                        */

    if (lockfile && strused (lockfile))
      {
        file_handle = open (lockfile, O_RDWR | O_CREAT, 0640);
        if (file_handle < 0)
            return (-1);                /*  We could not open lock file      */
        else
          {
            lock_file.l_type = F_WRLCK;
            if (fcntl (file_handle, F_SETLK, &lock_file))
                return (-1);            /*  We could not obtain a lock       */
          }
        /*  We record the server's process id in the lock file               */
        sprintf (pid_buffer, "%6d\n", getpid ());
        write   (file_handle, pid_buffer, strlen (pid_buffer));
      }

    /*  We ignore any hangup signal from the controlling TTY                 */
    signal (SIGHUP, SIG_IGN);
    return (0);                         /*  Initialisation completed ok      */

#elif (defined (__OS2__))

    /*  Start a new copy of the program up, running detached from this
     *  program.  Quote the arguments to prevent expansion because they've
     *  already been expanded once if applicable.  The program name is taken
     *  to be argv[0] due to the lack of better options, and the path will be
     *  searched to try to find it.
     *
     *  Providing the program starts successfully, this process exits,
     *  otherwise an error is returned.
     */
#   if (defined (__EMX__))

    if (spawnvp ((P_NOWAIT | P_DETACH | P_QUOTE), newargv [0], newargv) == -1)
        return -1;
    else
        exit (EXIT_SUCCESS);

#   else
#   error Do not know how to run detached program.    
#   endif 

#else
    return (0);                         /*  Nothing to do on this system     */
#endif
}


#if (defined (__WINDOWS__))

/*  handle_timer -- internal
 *
 *  This function is called by Windows when the timer goes off.  We use this
 *  to send a SIGALRM to whoever is handling signals.  (SIGALRM is actually
 *  SIGFPE, since MSVC does not know SIGALRM, and its raise() function
 *  only works with the pathetic little group of standard signals.)
 *  We call WSACancelBlockingCall(), which *should* unblock any select() or
 *  other blocking winsock call that is in progress.  If you are waiting in
 *  a select() loop, and a timer goes off, you want to go handle it right
 *  away.  Sadly, this does not work with all (any?) winsocks.  So, a word
 *  to the wise: if you use select() and timers, under Windows you should
 *  use a select() timeout that matches the level of responsiveness that
 *  you need.  (Typically 100-500ms.)
 */
static UINT                             /*  We only want a single timer to   */
    last_timer = 0;                     /*    be active at once.             */
#   if (defined (WIN32))
void FAR PASCAL handle_timer (UINT idTimer, UINT msg,
                              DWORD dw1, DWORD dw2, DWORD dw3)
#   else
void CALLBACK handle_timer (HWND hwnd, UINT msg, UINT timerid, DWORD time)
#   endif
{
    WSACancelBlockingCall ();           /*  Force "interrupted system call"  */
    raise (SIGALRM);                    /*  Simulate UNIX signal             */
    last_timer = 0;                     /*    and note that timer has gone   */
}
#endif

/*  ---------------------------------------------------------------------[<]-
    Function: process_alarm

    Synopsis: Sets a system timer to raise a SIGALRM after a specified
    interval in milliseconds.  Returns TRUE if the timer could be created
    and FALSE if there were insufficient resources, or if the system does
    not support timers.  Permits a single alarm for the current process:
    any alarm that was still pending when you called this function is
    annulled.  The implementation is system-dependent and highly
    non-portable.

    Under UNIX we use the setitimer() system function, which is clean and
    simple.

    Under 16-bit Windows we use the SetTimer() call.  This does not work
    in 32-bit console applications.  Under 32-bit Windows we use the
    'multimedia' timer, which provides better resolution and does work
    in console applications.  In both these cases we cache the id of the
    last-created alarm (and kill it before each new request), to avoid
    multiple active alarms.  It is not a good idea to create too many
    concurrent timers; after 16 or so the alarms start to fail.  This is
    not supposed to happen with MM timers, but does anyway.  Under
    Windows, SIGALRM does not exist.  Since signal() only accepts one of
    a small set of fixed signals, we hijack the SIGFPE signal...  It's a
    compromise and requires that any code which expects a SIGALRM does
    not use SIGFPE.  This can be tweaked in prelude.h.

    Under OS/2 we use the alarm() function which is accurate to one
    second only.  The required accuracy of timing is not easily
    achieved, so process_alarm() rounds down to whole seconds (except if
    rounding down would give 0, in which case it will delay 1 second).
    This will probably cause problems in code applications that depends
    on sub-second timing resolution.

    Under OpenVMS 7 and later we use the setitimer() function as for
    UNIX.  Under OpenVMS 6 and earlier we use the alarm() function as
    for OS/2.  This code may be tuned to use native VMS system calls.
    ---------------------------------------------------------------------[>]-*/

Bool
process_alarm (long delay)
{
#if (defined (__UNIX__) || defined (__VMS_XOPEN))
    struct itimerval
        timeout;                        /*  Timeout for setitimer            */

    /*  If the system supports interval timers, ask for a signal             */
    timeout.it_interval.tv_sec  = 0;
    timeout.it_interval.tv_usec = 0;
    timeout.it_value.tv_sec     = delay / 1000;
    timeout.it_value.tv_usec    = delay % 1000 * 1000L;
    setitimer (ITIMER_REAL, &timeout, 0);
    return (TRUE);

#elif (defined (__OS2__) || defined (__VMS__))
    /*  Since we use alarm() for our timeout, we can only time to            */
    /*  the nearest second, and alarm(0) turns off the alarm.                */
    /*  NOTE: we also have only one timer -- if alarm() is called while      */
    /*  the alarm is active, then it will be reset to the new value, and     */
    /*  only a single SIGALRM will be generated.                             */
    delay = (delay < 1000) ? 1 : (delay / 1000);
    alarm (delay);
    return (TRUE);

#elif (defined (__WINDOWS__))
#   if (defined (WIN32))
#   pragma comment (lib, "winmm")       /*  Link-in multimedia library       */
    /*  The multimedia timer gives the best accuracy, and works in console   */
    /*  applications                                                         */
    int rc;
    if (last_timer)
        __try {
            rc = timeKillEvent (last_timer);
        }
        __except (1) {
            coprintf ("timeKillEvent %d failed", last_timer);
        }
    __try {
        last_timer = timeSetEvent (delay, 50, handle_timer, 0, TIME_ONESHOT);
    }
    __except (1) {
        coprintf ("timeSetEvent %ld failed", delay);
    }
    return (TRUE);

#   else
    /*  But the normal Windows timer will do if we're in 16 bits             */
    if (last_timer)
        KillTimer ((HWND) NULL, last_timer);

    last_timer = SetTimer ((HWND) NULL, 0, (UINT) delay, handle_timer);
    return (TRUE);
#   endif

#else
    return (FALSE);                     /*  No timers - function failed      */
#endif
}


/*  ---------------------------------------------------------------------[<]-
    Function: process_esc

    Synopsis: Escapes a directory string so that process_create() can handle
    it correctly.  If you pass a command to process_create with a directory
    name that contains spaces, it will assume that the spaces delimit the
    command from its arguments.  For instance, under Windows 95, the filename
    "C:\Program Files\Myprog.exe" will be incorrectly treated as a program
    called "C:\Program" with arguments "Files\Myprog.exe".  This function
    replaces spaces by the escape character (0x1B).  You cannot use this
    value in a filename and expect process_create() to work correctly.  On
    an EBCDIC system, the escape character (0x27) is also used.  If the
    dest argument is NULL, allocates a string using mem_alloc() and returns
    that.  Otherwise copies into the dest string and returns that.  If the
    src string is NULL, returns an empty string.
    ---------------------------------------------------------------------[>]-*/

char *
process_esc (char *dest, const char *src)
{
#if (defined (__EBCDIC__))
#   define ESC_CHAR   0x27
#else
#   define ESC_CHAR   0x1B
#endif
    /*  Copy to dest, allocate if necessary                                  */
    if (dest != src)
      {
        xstrcpy_debug ();
        dest = xstrcpy (dest, src, NULL);
      }
    strconvch (dest, ' ', ESC_CHAR);
    return (dest);
}


/*  ---------------------------------------------------------------------[<]-
    Function: process_unesc

    Synopsis: Does the reverse translaction to process_esc().
    ---------------------------------------------------------------------[>]-*/

char *
process_unesc (char *dest, const char *src)
{
    /*  Copy to dest, allocate if necessary                                  */
    if (dest != src)
      {
        xstrcpy_debug ();
        dest = xstrcpy (dest, src, NULL);
      }
    strconvch (dest, ESC_CHAR, ' ');
    return (dest);
}


/*  ---------------------------------------------------------------------[<]-
    Function: process_priority

    Synopsis: Sets process priority as specified, to one of PRIORITY_LOW,
    PRIORITY_NORMAL, or PRIORITY_HIGH.  Currently has an effect only under
    Windows NT/95.  Returns 0 if okay, -1 if there was an error.
    ---------------------------------------------------------------------[>]-*/

int
process_priority (int priority)
{
#if (defined (WIN32))
    int
        class;

    if (priority == PRIORITY_HIGH)
        class = HIGH_PRIORITY_CLASS;
    else
    if (priority == PRIORITY_LOW)
        class = IDLE_PRIORITY_CLASS;
    else
        class = NORMAL_PRIORITY_CLASS;

    return (SetPriorityClass (GetCurrentProcess (), class));
#else
    return (0);
#endif
}

