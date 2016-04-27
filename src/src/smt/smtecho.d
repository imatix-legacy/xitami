/*---------------------------------------------------------------------------*
 *  smtecho.d - LIBERO dialog data definitions for smtecho.c.                *
 *  Generated by LIBERO 2.30 on 22 Dec, 1998, 15:35.                         *
 *  Schema file used: smtschm.c.                                             *
 *---------------------------------------------------------------------------*/

/*- Symbolic constants and event numbers ------------------------------------*/

#define _LR_STOP                        0xFFFFL
#define _LR_NULL_EVENT                  -2
#define _LR_NULL_STATE                  -1
#define terminate_event                 -1
#define client_event                    0
#define closed_event                    1
#define error_event                     2
#define exception_event                 3
#define fatal_event                     4
#define master_event                    5
#define ok_event                        6
#define read_ok_event                   7
#define shutdown_event                  8
#define write_ok_event                  9
#define _LR_STATE_after_init            0
#define _LR_STATE_master_input          1
#define _LR_STATE_echoing_data          2
#define _LR_STATE_defaults              3
#define _LR_STATE_end_thread            4
#define _LR_defaults_state              3


/*- Function prototypes and macros ------------------------------------------*/

#ifndef MODULE
#define MODULE  static void             /*  Libero dialog modules            */
#endif

MODULE initialise_the_thread        (THREAD *thread);
MODULE accept_client_connection     (THREAD *thread);
MODULE check_socket_type            (THREAD *thread);
MODULE close_agent_log_file         (THREAD *thread);
MODULE echo_socket_data             (THREAD *thread);
MODULE open_agent_log_file          (THREAD *thread);
MODULE open_master_socket           (THREAD *thread);
MODULE read_socket_data_repeatedly  (THREAD *thread);
MODULE shutdown_the_application     (THREAD *thread);
MODULE signal_socket_error          (THREAD *thread);
MODULE terminate_the_thread         (THREAD *thread);
MODULE wait_for_socket_input        (THREAD *thread);

#define the_next_event              _the_next_event
#define the_exception_event         _the_exception_event
#define the_external_event          _the_external_event
#define exception_raised            _exception_raised
#define io_completed                _io_completed


/*- Static areas shared by all threads --------------------------------------*/

static word _LR_nextst [5][10] =
{
    { 2,0,0,0,0,1,0,0,0,0 },
    { 0,1,4,0,0,0,1,0,0,0 },
    { 0,2,4,0,0,0,0,2,0,2 },
    { 0,0,0,4,3,0,0,0,4,0 },
    { 4,0,0,0,0,4,0,0,0,0 }
};

static word _LR_action [5][10] =
{
    { 2,0,0,0,0,1,0,0,0,0 },
    { 0,5,4,0,0,0,3,0,0,0 },
    { 0,8,4,0,0,0,0,6,0,7 },
    { 0,0,0,9,5,0,0,0,9,0 },
    { 8,0,0,0,0,10,0,0,0,0 }
};

static word _LR_offset [] =
{
    0,
    0,
    4,
    6,
    9,
    12,
    15,
    17,
    18,
    20,
    22
};

static word _LR_vector [] =
{
    4,5,10,_LR_STOP,
    6,_LR_STOP,
    0,10,_LR_STOP,
    8,1,_LR_STOP,
    7,9,_LR_STOP,
    3,_LR_STOP,
    _LR_STOP,
    9,_LR_STOP,
    1,_LR_STOP,
    2,9,_LR_STOP
};

static HOOK *_LR_module [11] = {
    accept_client_connection,
    check_socket_type,
    close_agent_log_file,
    echo_socket_data,
    open_agent_log_file,
    open_master_socket,
    read_socket_data_repeatedly,
    shutdown_the_application,
    signal_socket_error,
    terminate_the_thread,
    wait_for_socket_input
};

#if (defined (DEBUG))
static char *_LR_mname [11] =
{
     "Accept-Client-Connection",
     "Check-Socket-Type",
     "Close-Agent-Log-File",
     "Echo-Socket-Data",
     "Open-Agent-Log-File",
     "Open-Master-Socket",
     "Read-Socket-Data-Repeatedly",
     "Shutdown-The-Application",
     "Signal-Socket-Error",
     "Terminate-The-Thread",
     "Wait-For-Socket-Input"
};

static char *_LR_sname [5] =
{
     "After-Init",
     "Master-Input",
     "Echoing-Data",
     "Defaults",
     "End-Thread"
};

static char *_LR_ename [10] =
{
     "Client-Event",
     "Closed-Event",
     "Error-Event",
     "Exception-Event",
     "Fatal-Event",
     "Master-Event",
     "Ok-Event",
     "Read-Ok-Event",
     "Shutdown-Event",
     "Write-Ok-Event"
};
#else
static char *_LR_mname [11] =
{
     "0",
     "1",
     "2",
     "3",
     "4",
     "5",
     "6",
     "7",
     "8",
     "9",
     "10"
};

static char *_LR_sname [5] =
{
     "0",
     "1",
     "2",
     "3",
     "4"
};

static char *_LR_ename [10] =
{
     "0",
     "1",
     "2",
     "3",
     "4",
     "5",
     "6",
     "7",
     "8",
     "9"
};
#endif
