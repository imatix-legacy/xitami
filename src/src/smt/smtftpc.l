!----------------------------------------------------------------------------
!   Name:       smtftpc.l
!   Title:      Dialog for SMT FTP server control agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/08/20  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    99/01/17
!               99/12/07  for 2.4c4
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c

After-Init:
    (--) Master                             -> Master-Startup
          + Check-That-Http-Is-Active
          + Initialise-Master-Thread
          + Check-If-Ftp-Enabled
    (--) Sock-Retry                         -> Master-Input
          + Open-Master-Socket
          + Wait-For-Socket-Input
    (--) Client                             -> Before-User
          + Resolve-Virtual-Hostname
          + Initialise-Client-Thread
          + Check-Client-Ip-Allowed
          + Write-Service-Ready
    (--) Unauthorised                       ->
          + Write-Service-Unavailable
          + Terminate-The-Thread
!   It's possible that the HTTP thread already quit - so do we
    (--) Shutdown                           ->
          + Terminate-The-Thread

Master-Startup:
    (--) Ok                                 -> Master-Input
          + Load-Virtual-Hosts
          + Check-Rootdir-Exists
          + Open-Master-Socket
          + Wait-For-Socket-Input
    (--) Disabled                           -> Master-Disabled
          +

Master-Disabled:
    (--) Restart                            -> Master-Startup
          + Check-If-Ftp-Enabled
    (--) Shutdown                           ->
          + Terminate-The-Thread
    (--) $other                             -> Master-Disabled
          +

Master-Input:
    (--) Input-Ok                           -> Master-Input
          + Accept-Client-Connection
          + Wait-For-Socket-Input
    (--) Reload                             -> Master-Input
          + Reload-Config-If-Needed
    (--) Restart                            -> Master-Restart
          + Free-All-Server-Resources
          + Kill-All-Active-Connections
          + Prepare-To-Close-Master-Socket
          + Wait-For-Connections-To-Close
    (--) Cancel                             -> Master-Input
          +

Master-Restart:
    (--) Timeout                            -> Master-Startup
          + Close-Master-Socket
          + Check-If-Ftp-Enabled
    (--) Cancel                             -> Master-Restart
          +

!   This substate gets the next FTP command from the client
!   We must have just sent something to the server; we need an Ok event.
!
Client-Input:
    (--) Input-Ok                           ->
          + Read-Ftp-Request
          + Check-If-More-Input
          + Flush-Time-Out
          + Dialog-Return
    (--) Sock-Retry                         -> Client-Input
          + Wait-For-Socket-Input
    (--) Timeout                            -> End-Thread
          + Write-Time-Out-Message
          + Check-Socket-Type
    (--) Ok                                 -> Client-Input
          + Wait-For-Socket-Input

!   These states handle the actual FTP dialogue
!
Before-User:
    (--) Ok                                 -> Client-Input
          + Set-Time-Out
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
          + Dialog-Call
    (--) Return                             -> Expect-User
          + Get-Ftp-Command

Expect-User:
    (--) User                               -> Have-User
          + Check-User-Profile
    (--) Quit                               -> End-Thread
          + Write-Closing-Connection
          + Check-Socket-Type
    (--) Help                               -> Before-User
          + Write-Help-Message
    (--) Noop                               -> Before-User
          + Write-Return-Message
    (--) Unsupported                        -> Before-User
          + Write-Unsupported-Command
    (--) Invalid                            -> Before-User
          + Write-Invalid-Command
    (--) $other                             -> Before-User
          + Write-Unexpected-Command

Have-User:
    (--) Ok                                 -> Before-Password
          + Write-Return-Message
    (--) Not-Protected                      -> Before-Command
          + Initialise-User-Session
          + Write-User-Logged-In

Before-Password:
    (--) Ok                                 -> Client-Input
          + Set-Time-Out
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
          + Dialog-Call
    (--) Return                             -> Expect-Password
          + Get-Ftp-Command

Expect-Password:
    (--) User                               -> Have-User
          + Check-User-Profile
    (--) Password                           -> Have-Password
          + Check-User-Password
    (--) Quit                               -> End-Thread
          + Write-Closing-Connection
          + Check-Socket-Type
    (--) Help                               -> Before-Password
          + Write-Help-Message
    (--) Noop                               -> Before-Password
          + Write-Return-Message
    (--) Unsupported                        -> Before-User
          + Write-Unsupported-Command
    (--) Invalid                            -> Before-User
          + Write-Invalid-Command
    (--) $other                             -> Before-User
          + Write-Unexpected-Command

Have-Password:
    (--) Ok                                 -> Before-Command
          + Initialise-User-Session
          + Write-Entry-To-Logfile
          + Check-User-Quotas
          + Write-User-Logged-In
    (--) Invalid                            -> Failed-Password
          + Sleep-After-Failed-Password

Failed-Password:
    (--) Timeout                            -> Before-User
          + Write-Entry-To-Logfile
          + Write-Invalid-Password
    (--) $other                             -> Before-User
          + Write-Unexpected-Command

Before-Command:
    (--) Ok                                 -> Client-Input
          + Set-Time-Out
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
          + Dialog-Call
    (--) Return                             -> Expect-Command
          + Get-Ftp-Command

Expect-Command:
    (--) User                               -> Have-User
          + Check-User-Profile
    (--) List                               -> Downloading-File
          + Make-Full-Directory-Listing
          + Check-Ready-For-File-Transfer
          + Send-Put-Data-File-Request
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
    (--) Names                              -> Downloading-File
          + Make-Brief-Directory-Listing
          + Check-Ready-For-File-Transfer
          + Send-Put-Data-File-Request
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
    (--) Mkdir                              -> Before-Command
          + Make-New-Directory
          + Write-Return-Message
    (--) Rmdir                              -> Before-Command
          + Remove-Directory
          + Write-Return-Message
    (--) System                             -> Before-Command
          + Write-Name-Of-System
    (--) Type                               -> Before-Command
          + Set-Representation-Type
          + Write-Return-Message
    (--) Structure                          -> Before-Command
          + Set-Structure-Type
          + Write-Return-Message
    (--) Size                               -> Check-File-For-Size
          + Make-File-Name
          + Check-If-File-Exists
    (--) Pwd                                -> Before-Command
          + Write-Working-Directory
    (--) Cwd                                -> Before-Command
          + Change-Current-Directory
          + Write-Return-Message
    (--) Cdup                               -> Before-Command
          + Directory-Move-Up
          + Write-Return-Message
    (--) Restart                            -> Before-Command
          + Set-Restart-Position
          + Write-Return-Message
    (--) Retrieve                           -> Check-File-To-Download
          + Make-File-Name
          + Check-If-File-Exists
    (--) Store                              -> Uploading-File
          + Make-File-Name
          + Check-Ready-For-File-Transfer
          + Send-Get-Data-File-Request
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
    (--) Append                             -> Uploading-File
          + Make-File-Name
          + Check-Ready-For-File-Transfer
          + Send-Append-Data-File-Request
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
    (--) Delete                             -> Before-Command
          + Make-File-Name
          + Delete-The-File
          + Write-Entry-To-Logfile
          + Write-Return-Message
    (--) Rename-From                        -> Check-File-To-Rename
          + Make-File-Name
          + Check-If-File-Exists
    (--) Mode                               -> Before-Command
          + Set-Stream-Mode
          + Write-Return-Message
    (--) Port                               -> Before-Command
          + Get-Data-Port
          + Write-Return-Message
    (--) Quit                               -> End-Thread
          + Write-Entry-To-Logfile
          + Check-User-Quotas
          + Write-Closing-Connection
          + Check-Socket-Type
    (--) Reinit                             -> Before-User
          + Write-Service-Ready
    (--) Passive                            -> After-Open-Passive
          + Open-Passive-Data-Connection
    (--) Help                               -> Before-Command
          + Write-Help-Message
    (--) Noop                               -> Before-Command
          + Write-Return-Message
    (--) Unexpected                         -> Before-Command
          + Check-If-Temporary-File
          + Write-Unexpected-Command
    (--) Unauthorised                       -> Before-Command
          + Write-User-Not-Authorised
    (--) Over-Quota                         -> Before-Command
          + Write-User-Over-Quota     

Uploading-File:
    (--) Connected                          -> Uploading-File
          + Flush-Time-Out
          + Write-Data-Connected
    (--) Error                              -> Before-Command
          + Check-If-Temporary-File
          + Write-Entry-To-Logfile
          + Write-Return-Message
    (--) End                                -> Before-Command
          + Check-If-Temporary-File
          + Set-Transfer-Ended
          + Get-Uploaded-File-Size
          + Write-Entry-To-Logfile
          + Check-User-Quotas
          + Write-Return-Message
    (--) Input-Ok                           -> Transfer-Command
          + Read-Ftp-Request
          + Check-If-More-Input
          + Get-Ftp-Command
    (--) Sock-Retry                         -> Uploading-File
          + Wait-For-Socket-Input
    (--) Sock-Error                         -> End-Thread
          + Signal-Socket-Error
          + Check-Socket-Type
    (--) Sock-Closed                        -> End-Thread
          + Check-Socket-Type
    (--) Sock-Timeout                       -> End-Thread
          + Check-Socket-Type
    (--) Invalid                            -> Before-Command
          + Write-Invalid-Command
    (--) $other                             -> Uploading-File
          +

Downloading-File:
    (--) Connected                          -> Downloading-File
          + Flush-Time-Out
          + Write-Data-Connected
    (--) Error                              -> Before-Command
          + Check-If-Temporary-File
          + Write-Entry-To-Logfile
          + Write-Return-Message
    (--) End                                -> Before-Command
          + Check-If-Temporary-File
          + Set-Transfer-Ended
          + Write-Entry-To-Logfile
          + Write-Return-Message
    (--) Input-Ok                           -> Transfer-Command
          + Read-Ftp-Request
          + Check-If-More-Input
          + Get-Ftp-Command
    (--) Sock-Retry                         -> Downloading-File
          + Wait-For-Socket-Input
    (--) Sock-Error                         -> End-Thread
          + Signal-Socket-Error
          + Check-Socket-Type
    (--) Sock-Closed                        -> End-Thread
          + Check-Socket-Type
    (--) Sock-Timeout                       -> End-Thread
          + Check-Socket-Type
    (--) Invalid                            -> Before-Command
          + Write-Invalid-Command
    (--) $other                             -> Downloading-File
          +

Transfer-Command:
    (--) Abort                              -> Aborting-Transfer
          + Send-Abort-To-Data-Connection

Aborting-Transfer:
    (--) Aborted                            -> Before-Command
          + Write-Transfer-Aborted
    (--) $other                             -> Aborting-Transfer
          +

Check-File-To-Download:
    (--) Ok                                 -> Downloading-File
          + Check-Ready-For-File-Transfer
          + Send-Put-Data-File-Request
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
    (--) Unexpected                         -> Before-Command
          + Check-If-Temporary-File
          + Write-Unexpected-Command
    (--) Unauthorised                       -> Before-Command
          + Write-Entry-To-Logfile
          + Write-User-Not-Authorised
    (--) Not-Found                          -> Before-Command
          + Write-Entry-To-Logfile
          + Write-File-Not-Found

Check-File-To-Rename:
    (--) Ok                                 -> Client-Input
          + Write-Pending-Action
          + Set-Time-Out
          + Prepare-To-Get-Input
          + Wait-For-Socket-Input
          + Dialog-Call
    (--) Return                             -> Expect-Rename-To
          + Get-Ftp-Command
    (--) Unauthorised                       -> Before-Command
          + Write-Entry-To-Logfile
          + Write-User-Not-Authorised
    (--) Not-Found                          -> Before-Command
          + Write-Entry-To-Logfile
          + Write-File-Not-Found

Expect-Rename-To:
    (--) Rename-To                          -> Before-Command
          + Rename-The-File
          + Write-Entry-To-Logfile
          + Write-Return-Message
    (--) Quit                               -> End-Thread
          + Write-Closing-Connection
          + Check-Socket-Type
    (--) Help                               -> Before-Command
          + Write-Help-Message
    (--) Noop                               -> Before-Command
          + Write-Return-Message

Check-File-For-Size:
    (--) Ok                                 -> Before-Command
          + Write-File-Size
    (--) Unauthorised                       -> Before-Command
          + Write-Entry-To-Logfile
          + Write-User-Not-Authorised
    (--) Not-Found                          -> Before-Command
          + Write-Entry-To-Logfile
          + Write-File-Not-Found

After-Open-Passive:
    (--) Ok                                 -> Before-Command
          + Make-Open-Passive-Message
          + Write-Open-Passive-Okay
    (--) Error                              -> Before-Command
          + Write-Open-Passive-Failed

Defaults:
    (--) Exception                          -> End-Thread
          + Check-Socket-Type
    (--) Shutdown                           -> End-Thread
          + Check-Socket-Type
    (--) Error                              -> End-Thread
          + Write-Return-Message
          + Write-Closing-Connection
          + Check-Socket-Type
    (--) Cancel                             -> End-Thread
          + Check-Socket-Type
    (--) Sock-Error                         -> End-Thread
          + Signal-Socket-Error
          + Check-Socket-Type
    (--) Sock-Closed                        -> End-Thread
          + Check-Socket-Type
    (--) Sock-Timeout                       -> End-Thread
          + Check-Socket-Type
    (--) Sock-Retry                         -> End-Thread
          + Check-Socket-Type
    (--) Connected                          -> Before-Command
          + Write-Data-Connected
    (--) Unsupported                        -> Before-Command
          + Write-Unsupported-Command
    (--) Invalid                            -> Before-Command
          + Write-Invalid-Command
    (--) $other                             -> Before-Command
          + Write-Unexpected-Command

End-Thread:
    (--) Master                             ->
          + Free-All-Server-Resources
          + Prepare-To-Close-Master-Socket
          + Close-Master-Socket
          + Terminate-The-Thread
    (--) Client                             ->
          + Cancel-Data-Thread
          + Terminate-The-Thread
