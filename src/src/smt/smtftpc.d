/*---------------------------------------------------------------------------*
 *  smtftpc.d - LIBERO dialog data definitions for smtftpc.c.                *
 *  Generated by LIBERO 2.30 on  7 Dec, 1999, 14:09.                         *
 *  Schema file used: smtschm.c.                                             *
 *---------------------------------------------------------------------------*/

/*- Symbolic constants and event numbers ------------------------------------*/

#define _LR_STOP                        0xFFFFL
#define _LR_NULL_EVENT                  -2
#define _LR_NULL_STATE                  -1
#define terminate_event                 -1
#define abort_event                     0
#define aborted_event                   1
#define append_event                    2
#define cancel_event                    3
#define cdup_event                      4
#define client_event                    5
#define connected_event                 6
#define cwd_event                       7
#define delete_event                    8
#define disabled_event                  9
#define end_event                       10
#define error_event                     11
#define exception_event                 12
#define help_event                      13
#define input_ok_event                  14
#define invalid_event                   15
#define list_event                      16
#define master_event                    17
#define mkdir_event                     18
#define mode_event                      19
#define names_event                     20
#define noop_event                      21
#define not_found_event                 22
#define not_protected_event             23
#define ok_event                        24
#define over_quota_event                25
#define passive_event                   26
#define password_event                  27
#define port_event                      28
#define pwd_event                       29
#define quit_event                      30
#define reinit_event                    31
#define reload_event                    32
#define rename_from_event               33
#define rename_to_event                 34
#define restart_event                   35
#define retrieve_event                  36
#define return_event                    37
#define rmdir_event                     38
#define shutdown_event                  39
#define size_event                      40
#define sock_closed_event               41
#define sock_error_event                42
#define sock_retry_event                43
#define sock_timeout_event              44
#define store_event                     45
#define structure_event                 46
#define system_event                    47
#define timeout_event                   48
#define type_event                      49
#define unauthorised_event              50
#define unexpected_event                51
#define unsupported_event               52
#define user_event                      53
#define _LR_STATE_after_init            0
#define _LR_STATE_master_startup        1
#define _LR_STATE_master_disabled       2
#define _LR_STATE_master_input          3
#define _LR_STATE_master_restart        4
#define _LR_STATE_client_input          5
#define _LR_STATE_before_user           6
#define _LR_STATE_expect_user           7
#define _LR_STATE_have_user             8
#define _LR_STATE_before_password       9
#define _LR_STATE_expect_password       10
#define _LR_STATE_have_password         11
#define _LR_STATE_failed_password       12
#define _LR_STATE_before_command        13
#define _LR_STATE_expect_command        14
#define _LR_STATE_uploading_file        15
#define _LR_STATE_downloading_file      16
#define _LR_STATE_transfer_command      17
#define _LR_STATE_aborting_transfer     18
#define _LR_STATE_check_file_to_download 19
#define _LR_STATE_check_file_to_rename  20
#define _LR_STATE_expect_rename_to      21
#define _LR_STATE_check_file_for_size   22
#define _LR_STATE_after_open_passive    23
#define _LR_STATE_defaults              24
#define _LR_STATE_end_thread            25
#define _LR_defaults_state              24


/*- Function prototypes and macros ------------------------------------------*/

#ifndef MODULE
#define MODULE  static void             /*  Libero dialog modules            */
#endif

MODULE initialise_the_thread        (THREAD *thread);
MODULE check_that_http_is_active    (THREAD *thread);
MODULE initialise_master_thread     (THREAD *thread);
MODULE check_if_ftp_enabled         (THREAD *thread);
MODULE open_master_socket           (THREAD *thread);
MODULE wait_for_socket_input        (THREAD *thread);
MODULE resolve_virtual_hostname     (THREAD *thread);
MODULE initialise_client_thread     (THREAD *thread);
MODULE check_client_ip_allowed      (THREAD *thread);
MODULE write_service_ready          (THREAD *thread);
MODULE write_service_unavailable    (THREAD *thread);
MODULE terminate_the_thread         (THREAD *thread);
MODULE load_virtual_hosts           (THREAD *thread);
MODULE check_rootdir_exists         (THREAD *thread);
MODULE accept_client_connection     (THREAD *thread);
MODULE reload_config_if_needed      (THREAD *thread);
MODULE free_all_server_resources    (THREAD *thread);
MODULE kill_all_active_connections  (THREAD *thread);
MODULE prepare_to_close_master_socket (THREAD *thread);
MODULE wait_for_connections_to_close (THREAD *thread);
MODULE close_master_socket          (THREAD *thread);
MODULE read_ftp_request             (THREAD *thread);
MODULE check_if_more_input          (THREAD *thread);
MODULE flush_time_out               (THREAD *thread);
MODULE dialog_return                (THREAD *thread);
MODULE write_time_out_message       (THREAD *thread);
MODULE check_socket_type            (THREAD *thread);
MODULE set_time_out                 (THREAD *thread);
MODULE prepare_to_get_input         (THREAD *thread);
MODULE dialog_call                  (THREAD *thread);
MODULE get_ftp_command              (THREAD *thread);
MODULE check_user_profile           (THREAD *thread);
MODULE write_closing_connection     (THREAD *thread);
MODULE write_help_message           (THREAD *thread);
MODULE write_return_message         (THREAD *thread);
MODULE write_unsupported_command    (THREAD *thread);
MODULE write_invalid_command        (THREAD *thread);
MODULE write_unexpected_command     (THREAD *thread);
MODULE initialise_user_session      (THREAD *thread);
MODULE write_user_logged_in         (THREAD *thread);
MODULE check_user_password          (THREAD *thread);
MODULE write_entry_to_logfile       (THREAD *thread);
MODULE check_user_quotas            (THREAD *thread);
MODULE sleep_after_failed_password  (THREAD *thread);
MODULE write_invalid_password       (THREAD *thread);
MODULE make_full_directory_listing  (THREAD *thread);
MODULE check_ready_for_file_transfer (THREAD *thread);
MODULE send_put_data_file_request   (THREAD *thread);
MODULE make_brief_directory_listing (THREAD *thread);
MODULE make_new_directory           (THREAD *thread);
MODULE remove_directory             (THREAD *thread);
MODULE write_name_of_system         (THREAD *thread);
MODULE set_representation_type      (THREAD *thread);
MODULE set_structure_type           (THREAD *thread);
MODULE make_file_name               (THREAD *thread);
MODULE check_if_file_exists         (THREAD *thread);
MODULE write_working_directory      (THREAD *thread);
MODULE change_current_directory     (THREAD *thread);
MODULE directory_move_up            (THREAD *thread);
MODULE set_restart_position         (THREAD *thread);
MODULE send_get_data_file_request   (THREAD *thread);
MODULE send_append_data_file_request (THREAD *thread);
MODULE delete_the_file              (THREAD *thread);
MODULE set_stream_mode              (THREAD *thread);
MODULE get_data_port                (THREAD *thread);
MODULE open_passive_data_connection (THREAD *thread);
MODULE check_if_temporary_file      (THREAD *thread);
MODULE write_user_not_authorised    (THREAD *thread);
MODULE write_user_over_quota        (THREAD *thread);
MODULE write_data_connected         (THREAD *thread);
MODULE set_transfer_ended           (THREAD *thread);
MODULE get_uploaded_file_size       (THREAD *thread);
MODULE signal_socket_error          (THREAD *thread);
MODULE send_abort_to_data_connection (THREAD *thread);
MODULE write_transfer_aborted       (THREAD *thread);
MODULE write_file_not_found         (THREAD *thread);
MODULE write_pending_action         (THREAD *thread);
MODULE rename_the_file              (THREAD *thread);
MODULE write_file_size              (THREAD *thread);
MODULE make_open_passive_message    (THREAD *thread);
MODULE write_open_passive_okay      (THREAD *thread);
MODULE write_open_passive_failed    (THREAD *thread);
MODULE cancel_data_thread           (THREAD *thread);

#define the_next_event              _the_next_event
#define the_exception_event         _the_exception_event
#define the_external_event          _the_external_event
#define exception_raised            _exception_raised
#define io_completed                _io_completed


/*- Static areas shared by all threads --------------------------------------*/

static word _LR_nextst [26][54] =
{
    { 0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
     ,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
    },
    { 0,0,0,3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,3,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,25,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0
     ,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
     ,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,9,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0
     ,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 6,6,6,6,6,6,6,6,6,6,6,6,6,9,6,6,6,6,6,6,6,9,6,6,6,6,6,11,6,6
     ,25,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,13,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
     ,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0
     ,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,15,0,13,0,0,13,13,0,0,0,0,13,0,0,16,0,13,13,16,13,0,0,0
     ,13,23,0,13,13,25,6,0,20,0,13,19,0,13,0,22,0,0,0,0,15,13,13
     ,0,13,13,13,0,8
    },
    { 15,15,15,15,15,15,15,15,15,15,13,13,15,15,17,13,15,15,15,15
     ,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15
     ,15,25,25,15,25,15,15,15,15,15,15,15,15,15
    },
    { 16,16,16,16,16,16,16,16,16,16,13,13,16,16,17,13,16,16,16,16
     ,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16
     ,16,25,25,16,25,16,16,16,16,16,16,16,16,16
    },
    { 18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 18,13,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18
     ,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18
     ,18,18,18,18,18,18,18,18,18,18,18,18,18,18
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,16,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,13,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,5,0,0,0,0,0
     ,0,0,0,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0
     ,0,25,0,0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,13,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 13,13,13,25,13,13,13,13,13,13,13,25,25,13,13,13,13,13,13,13
     ,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,25
     ,13,25,25,25,25,13,13,13,13,13,13,13,13,13
    },
    { 0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    }
};

static word _LR_action [26][54] =
{
    { 0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,5,0,0,0,2,0,0,0,0,0,0,4,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
     ,7,7,7,7,7,8,7,7,7,5,7,7,7,7,7,7,7,7,7,7,7,7,7,7
    },
    { 0,0,0,7,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,10,0,0,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,0,14,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,15,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0
     ,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 24,24,24,24,24,24,24,24,24,24,24,24,24,20,24,23,24,24,24,24
     ,24,21,24,24,24,24,24,24,24,24,19,24,24,24,24,24,24,24,24,24
     ,24,24,24,24,24,24,24,24,24,24,24,24,22,18
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,21,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0
     ,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 24,24,24,24,24,24,24,24,24,24,24,24,24,20,24,23,24,24,24,24
     ,24,21,24,24,24,24,24,26,24,24,19,24,24,24,24,24,24,24,24,24
     ,24,24,24,24,24,24,24,24,24,24,24,24,22,18
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,0,27,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24
     ,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24
     ,24,24,24,24,24,24,24,24,29,24,24,24,24,24
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0
     ,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,43,0,40,0,0,39,44,0,0,0,0,20,0,0,30,0,32,45,31,21,0,0,0
     ,52,49,0,46,38,47,48,0,37,0,41,37,0,33,0,37,0,0,0,0,42,36,34
     ,0,35,51,50,0,18
    },
    { 7,7,7,7,7,7,53,7,7,7,55,54,7,7,56,23,7,7,7,7,7,7,7,7,7,7,7,7
     ,7,7,7,7,7,7,7,7,7,7,7,7,7,58,57,14,58,7,7,7,7,7,7,7,7,7
    },
    { 7,7,7,7,7,7,53,7,7,7,59,54,7,7,56,23,7,7,7,7,7,7,7,7,7,7,7,7
     ,7,7,7,7,7,7,7,7,7,7,7,7,7,58,57,14,58,7,7,7,7,7,7,7,7,7
    },
    { 60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 7,61,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
     ,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,62,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,50,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,65,0,0,0,0
     ,0,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,0,63,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,21,0,0,0,0,0,0,0
     ,0,19,0,0,0,66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,67,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,0,0,0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,69,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },
    { 24,24,24,58,24,24,71,24,24,24,24,70,58,24,24,23,24,24,24,24
     ,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,58
     ,24,58,57,58,58,24,24,24,24,24,24,24,22,24
    },
    { 0,0,0,0,0,73,0,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0
     ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    }
};

static word _LR_offset [] =
{
    0,
    0,
    4,
    7,
    12,
    15,
    17,
    22,
    23,
    25,
    28,
    30,
    35,
    38,
    43,
    45,
    48,
    53,
    55,
    57,
    60,
    62,
    64,
    66,
    68,
    70,
    73,
    75,
    80,
    82,
    85,
    91,
    97,
    100,
    103,
    105,
    108,
    111,
    114,
    116,
    119,
    122,
    125,
    131,
    137,
    142,
    145,
    148,
    153,
    155,
    157,
    160,
    162,
    164,
    167,
    171,
    178,
    182,
    185,
    187,
    192,
    194,
    196,
    201,
    204,
    207,
    213,
    217,
    219,
    222,
    224,
    228,
    230,
    235
};

static word _LR_vector [] =
{
    0,1,2,_LR_STOP,
    3,4,_LR_STOP,
    5,6,7,8,_LR_STOP,
    9,10,_LR_STOP,
    10,_LR_STOP,
    11,12,3,4,_LR_STOP,
    _LR_STOP,
    2,_LR_STOP,
    13,4,_LR_STOP,
    14,_LR_STOP,
    15,16,17,18,_LR_STOP,
    19,2,_LR_STOP,
    20,21,22,23,_LR_STOP,
    4,_LR_STOP,
    24,25,_LR_STOP,
    26,27,4,28,_LR_STOP,
    29,_LR_STOP,
    30,_LR_STOP,
    31,25,_LR_STOP,
    32,_LR_STOP,
    33,_LR_STOP,
    34,_LR_STOP,
    35,_LR_STOP,
    36,_LR_STOP,
    37,38,_LR_STOP,
    39,_LR_STOP,
    37,40,41,38,_LR_STOP,
    42,_LR_STOP,
    40,43,_LR_STOP,
    44,45,46,27,4,_LR_STOP,
    47,45,46,27,4,_LR_STOP,
    48,33,_LR_STOP,
    49,33,_LR_STOP,
    50,_LR_STOP,
    51,33,_LR_STOP,
    52,33,_LR_STOP,
    53,54,_LR_STOP,
    55,_LR_STOP,
    56,33,_LR_STOP,
    57,33,_LR_STOP,
    58,33,_LR_STOP,
    53,45,59,27,4,_LR_STOP,
    53,45,60,27,4,_LR_STOP,
    53,61,40,33,_LR_STOP,
    62,33,_LR_STOP,
    63,33,_LR_STOP,
    40,41,31,25,_LR_STOP,
    8,_LR_STOP,
    64,_LR_STOP,
    65,36,_LR_STOP,
    66,_LR_STOP,
    67,_LR_STOP,
    22,68,_LR_STOP,
    65,40,33,_LR_STOP,
    65,69,70,40,41,33,_LR_STOP,
    20,21,29,_LR_STOP,
    71,25,_LR_STOP,
    25,_LR_STOP,
    65,69,40,33,_LR_STOP,
    72,_LR_STOP,
    73,_LR_STOP,
    45,46,27,4,_LR_STOP,
    40,66,_LR_STOP,
    40,74,_LR_STOP,
    75,26,27,4,28,_LR_STOP,
    76,40,33,_LR_STOP,
    77,_LR_STOP,
    78,79,_LR_STOP,
    80,_LR_STOP,
    33,31,25,_LR_STOP,
    68,_LR_STOP,
    15,17,19,10,_LR_STOP,
    81,10,_LR_STOP
};

static HOOK *_LR_module [82] = {
    check_that_http_is_active,
    initialise_master_thread,
    check_if_ftp_enabled,
    open_master_socket,
    wait_for_socket_input,
    resolve_virtual_hostname,
    initialise_client_thread,
    check_client_ip_allowed,
    write_service_ready,
    write_service_unavailable,
    terminate_the_thread,
    load_virtual_hosts,
    check_rootdir_exists,
    accept_client_connection,
    reload_config_if_needed,
    free_all_server_resources,
    kill_all_active_connections,
    prepare_to_close_master_socket,
    wait_for_connections_to_close,
    close_master_socket,
    read_ftp_request,
    check_if_more_input,
    flush_time_out,
    dialog_return,
    write_time_out_message,
    check_socket_type,
    set_time_out,
    prepare_to_get_input,
    dialog_call,
    get_ftp_command,
    check_user_profile,
    write_closing_connection,
    write_help_message,
    write_return_message,
    write_unsupported_command,
    write_invalid_command,
    write_unexpected_command,
    initialise_user_session,
    write_user_logged_in,
    check_user_password,
    write_entry_to_logfile,
    check_user_quotas,
    sleep_after_failed_password,
    write_invalid_password,
    make_full_directory_listing,
    check_ready_for_file_transfer,
    send_put_data_file_request,
    make_brief_directory_listing,
    make_new_directory,
    remove_directory,
    write_name_of_system,
    set_representation_type,
    set_structure_type,
    make_file_name,
    check_if_file_exists,
    write_working_directory,
    change_current_directory,
    directory_move_up,
    set_restart_position,
    send_get_data_file_request,
    send_append_data_file_request,
    delete_the_file,
    set_stream_mode,
    get_data_port,
    open_passive_data_connection,
    check_if_temporary_file,
    write_user_not_authorised,
    write_user_over_quota,
    write_data_connected,
    set_transfer_ended,
    get_uploaded_file_size,
    signal_socket_error,
    send_abort_to_data_connection,
    write_transfer_aborted,
    write_file_not_found,
    write_pending_action,
    rename_the_file,
    write_file_size,
    make_open_passive_message,
    write_open_passive_okay,
    write_open_passive_failed,
    cancel_data_thread
};

#if (defined (DEBUG))
static char *_LR_mname [82] =
{
     "Check-That-Http-Is-Active",
     "Initialise-Master-Thread",
     "Check-If-Ftp-Enabled",
     "Open-Master-Socket",
     "Wait-For-Socket-Input",
     "Resolve-Virtual-Hostname",
     "Initialise-Client-Thread",
     "Check-Client-Ip-Allowed",
     "Write-Service-Ready",
     "Write-Service-Unavailable",
     "Terminate-The-Thread",
     "Load-Virtual-Hosts",
     "Check-Rootdir-Exists",
     "Accept-Client-Connection",
     "Reload-Config-If-Needed",
     "Free-All-Server-Resources",
     "Kill-All-Active-Connections",
     "Prepare-To-Close-Master-Socket",
     "Wait-For-Connections-To-Close",
     "Close-Master-Socket",
     "Read-Ftp-Request",
     "Check-If-More-Input",
     "Flush-Time-Out",
     "Dialog-Return",
     "Write-Time-Out-Message",
     "Check-Socket-Type",
     "Set-Time-Out",
     "Prepare-To-Get-Input",
     "Dialog-Call",
     "Get-Ftp-Command",
     "Check-User-Profile",
     "Write-Closing-Connection",
     "Write-Help-Message",
     "Write-Return-Message",
     "Write-Unsupported-Command",
     "Write-Invalid-Command",
     "Write-Unexpected-Command",
     "Initialise-User-Session",
     "Write-User-Logged-In",
     "Check-User-Password",
     "Write-Entry-To-Logfile",
     "Check-User-Quotas",
     "Sleep-After-Failed-Password",
     "Write-Invalid-Password",
     "Make-Full-Directory-Listing",
     "Check-Ready-For-File-Transfer",
     "Send-Put-Data-File-Request",
     "Make-Brief-Directory-Listing",
     "Make-New-Directory",
     "Remove-Directory",
     "Write-Name-Of-System",
     "Set-Representation-Type",
     "Set-Structure-Type",
     "Make-File-Name",
     "Check-If-File-Exists",
     "Write-Working-Directory",
     "Change-Current-Directory",
     "Directory-Move-Up",
     "Set-Restart-Position",
     "Send-Get-Data-File-Request",
     "Send-Append-Data-File-Request",
     "Delete-The-File",
     "Set-Stream-Mode",
     "Get-Data-Port",
     "Open-Passive-Data-Connection",
     "Check-If-Temporary-File",
     "Write-User-Not-Authorised",
     "Write-User-Over-Quota",
     "Write-Data-Connected",
     "Set-Transfer-Ended",
     "Get-Uploaded-File-Size",
     "Signal-Socket-Error",
     "Send-Abort-To-Data-Connection",
     "Write-Transfer-Aborted",
     "Write-File-Not-Found",
     "Write-Pending-Action",
     "Rename-The-File",
     "Write-File-Size",
     "Make-Open-Passive-Message",
     "Write-Open-Passive-Okay",
     "Write-Open-Passive-Failed",
     "Cancel-Data-Thread"
};

static char *_LR_sname [26] =
{
     "After-Init",
     "Master-Startup",
     "Master-Disabled",
     "Master-Input",
     "Master-Restart",
     "Client-Input",
     "Before-User",
     "Expect-User",
     "Have-User",
     "Before-Password",
     "Expect-Password",
     "Have-Password",
     "Failed-Password",
     "Before-Command",
     "Expect-Command",
     "Uploading-File",
     "Downloading-File",
     "Transfer-Command",
     "Aborting-Transfer",
     "Check-File-To-Download",
     "Check-File-To-Rename",
     "Expect-Rename-To",
     "Check-File-For-Size",
     "After-Open-Passive",
     "Defaults",
     "End-Thread"
};

static char *_LR_ename [54] =
{
     "Abort-Event",
     "Aborted-Event",
     "Append-Event",
     "Cancel-Event",
     "Cdup-Event",
     "Client-Event",
     "Connected-Event",
     "Cwd-Event",
     "Delete-Event",
     "Disabled-Event",
     "End-Event",
     "Error-Event",
     "Exception-Event",
     "Help-Event",
     "Input-Ok-Event",
     "Invalid-Event",
     "List-Event",
     "Master-Event",
     "Mkdir-Event",
     "Mode-Event",
     "Names-Event",
     "Noop-Event",
     "Not-Found-Event",
     "Not-Protected-Event",
     "Ok-Event",
     "Over-Quota-Event",
     "Passive-Event",
     "Password-Event",
     "Port-Event",
     "Pwd-Event",
     "Quit-Event",
     "Reinit-Event",
     "Reload-Event",
     "Rename-From-Event",
     "Rename-To-Event",
     "Restart-Event",
     "Retrieve-Event",
     "Return-Event",
     "Rmdir-Event",
     "Shutdown-Event",
     "Size-Event",
     "Sock-Closed-Event",
     "Sock-Error-Event",
     "Sock-Retry-Event",
     "Sock-Timeout-Event",
     "Store-Event",
     "Structure-Event",
     "System-Event",
     "Timeout-Event",
     "Type-Event",
     "Unauthorised-Event",
     "Unexpected-Event",
     "Unsupported-Event",
     "User-Event"
};
#else
static char *_LR_mname [82] =
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
     "10",
     "11",
     "12",
     "13",
     "14",
     "15",
     "16",
     "17",
     "18",
     "19",
     "20",
     "21",
     "22",
     "23",
     "24",
     "25",
     "26",
     "27",
     "28",
     "29",
     "30",
     "31",
     "32",
     "33",
     "34",
     "35",
     "36",
     "37",
     "38",
     "39",
     "40",
     "41",
     "42",
     "43",
     "44",
     "45",
     "46",
     "47",
     "48",
     "49",
     "50",
     "51",
     "52",
     "53",
     "54",
     "55",
     "56",
     "57",
     "58",
     "59",
     "60",
     "61",
     "62",
     "63",
     "64",
     "65",
     "66",
     "67",
     "68",
     "69",
     "70",
     "71",
     "72",
     "73",
     "74",
     "75",
     "76",
     "77",
     "78",
     "79",
     "80",
     "81"
};

static char *_LR_sname [26] =
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
     "10",
     "11",
     "12",
     "13",
     "14",
     "15",
     "16",
     "17",
     "18",
     "19",
     "20",
     "21",
     "22",
     "23",
     "24",
     "25"
};

static char *_LR_ename [54] =
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
     "10",
     "11",
     "12",
     "13",
     "14",
     "15",
     "16",
     "17",
     "18",
     "19",
     "20",
     "21",
     "22",
     "23",
     "24",
     "25",
     "26",
     "27",
     "28",
     "29",
     "30",
     "31",
     "32",
     "33",
     "34",
     "35",
     "36",
     "37",
     "38",
     "39",
     "40",
     "41",
     "42",
     "43",
     "44",
     "45",
     "46",
     "47",
     "48",
     "49",
     "50",
     "51",
     "52",
     "53"
};
#endif

MODULE dialog_call (THREAD *thread)
{
    if (thread-> LR_stack_size < 20)
        thread-> LR_stack [thread-> LR_stack_size++] = thread-> LR_state;
    else
      {
        fprintf (stdout,
            "State %d - Dialog-Call overflow\n", thread-> LR_state);
        exit (EXIT_FAILURE);
      }
}

MODULE dialog_return (THREAD *thread)
{
    if (thread-> LR_stack_size > 0)
      {
        thread-> LR_state = thread-> LR_stack [--(thread-> LR_stack_size)];
        raise_exception (return_event);
      }
    else
      {
        fprintf (stdout,
            "State %d - Dialog-Return underflow\n", thread-> LR_state);
        exit (EXIT_FAILURE);
      }
}