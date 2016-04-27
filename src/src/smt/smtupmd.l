!----------------------------------------------------------------------------
!   Name:       smtupmd.l
!   Title:      Dialog for SMT Unattended Task Manager daemon
!   Package:    Libero SMT 2.x
!
!   Written:    96/09/05  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    97/09/08
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   This program is free software; you can redistribute it and/or modify it
!   under the terms of the GNU General Public License as published by the Free
!   Software Foundation; either version 2 of the License, or (at your option)
!   any later version. This program is distributed in the hope that it will be
!   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
!   Public License for more details.  You should have received a copy of the
!   GNU General Public License along with this program; if not, write to the
!   Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
!----------------------------------------------------------------------------
-schema=smtschm.c

After-Init:
    !   Master thread manages connection requests on UPM master socket
    (--) Master                             -> Master-Input
          + Create-Task-Threads
          + Open-Manager-Log-File
          + Open-Master-Socket
          + Wait-For-Socket-Input
    !   Control threads handle front-end control socket connections
    (--) Control                            -> Have-Control-Message
          + Reply-Ready-For-Command
          + Read-Control-Message
          + Check-Control-Message
    !   Task threads each handle one defined UPM task
    (--) Task                               -> Task-Stopped
          + Load-Task-Time-Slots
          + Load-Task-Values
          + Run-Task-Idle-Command

!  These states control the master thread, which waits for control
!  connections.

Master-Input:
    (--) Ok                                 -> Master-Input
          + Accept-Control-Connection
          + Wait-For-Socket-Input

!  These states define the control threads, one for each client
!  connection.

Have-Control-Message:
    (--) List                               -> Have-Control-Message
          + Reply-List-Of-Tasks
          + Reply-Ready-For-Command
          + Read-Control-Message
          + Check-Control-Message
    (--) Halt                               ->
          + Reply-Halting
          + Commit-Outgoing-Replies
          + Shutdown-The-Application
          + Terminate-The-Thread
    (--) Start                              -> Have-Task-For-Start
          + Get-First-Affected-Task
    (--) Stop                               -> Have-Task-For-Stop
          + Get-First-Affected-Task
    (--) Status                             -> Have-Task-For-Status
          + Get-First-Affected-Task
    (--) Error                              -> Have-Control-Message
          + Reply-Unrecognised-Control
          + Reply-Ready-For-Command
          + Read-Control-Message
          + Check-Control-Message

Have-Task-For-Start:
    (--) Ok                                 -> Wait-Task-Started
          + Pass-Start-To-Task-Thread
    (--) No-More                            -> Have-Control-Message
          + Reply-Ready-For-Command
          + Read-Control-Message
          + Check-Control-Message
    (--) Not-Found                          -> Have-Control-Message
          + Reply-Ready-For-Command
          + Read-Control-Message
          + Check-Control-Message

Wait-Task-Started:
    (--) Ok                                 -> Have-Task-For-Start
          + Reply-Task-Started-Ok
          + Get-Next-Affected-Task
    (--) Error                              -> Have-Task-For-Start
          + Reply-Task-Started-Error
          + Get-Next-Affected-Task

Have-Task-For-Stop: <Have-Task-For-Start>
    (--) Ok                                 -> Wait-Task-Stopped
          + Pass-Stop-To-Task-Thread

Wait-Task-Stopped:
    (--) Ok                                 -> Have-Task-For-Stop
          + Reply-Task-Stopped-Ok
          + Get-Next-Affected-Task
    (--) Error                              -> Have-Task-For-Stop
          + Reply-Task-Stopped-Error
          + Get-Next-Affected-Task

Have-Task-For-Status: <Have-Task-For-Start>
    (--) Ok                                 -> Wait-Task-Status
          + Pass-Status-To-Task-Thread

Wait-Task-Status:
    (--) Running                            -> Have-Task-For-Status
          + Reply-Task-Running
          + Get-Next-Affected-Task
    (--) Stopped                            -> Have-Task-For-Status
          + Reply-Task-Stopped
          + Get-Next-Affected-Task
    (--) Error                              -> Have-Task-For-Status
          + Get-Next-Affected-Task

!  These states define the task threads, one for each task defined
!  in the UPM initialisation file.

Task-Stopped:
    (--) Start                              -> Task-Running
          + Load-Task-Time-Slots
          + Load-Task-Values
          + Run-Task-Startup-Command
          + Monitor-Active-Task-Status
          + Signal-Task-Started-Okay
    (--) Stop                               -> Task-Stopped
          + Signal-Task-Not-Running
    (--) Start-Auto                         -> Task-Running
          + Load-Task-Values
          + Run-Task-Startup-Command
          + Monitor-Active-Task-Status
    (--) Stop-Auto                          -> Task-Stopped
          + 
    (--) Status                             -> Task-Stopped
          + Signal-Task-Stopped
    (--) Task-Alarm                         -> Task-Stopped
          +
    (--) Exception                          -> Task-Stopped
          + Signal-Task-Started-Error

Task-Running:
    (--) Start                              -> Task-Running
          + Shut-Down-Child-Task
          + Run-Task-Cancel-Command
          + Load-Task-Time-Slots
          + Load-Task-Values
          + Run-Task-Startup-Command
          + Signal-Task-Started-Okay
    (--) Stop                               -> Task-Stopped
          + Shut-Down-Child-Task
          + Run-Task-Cancel-Command
          + Run-Task-Idle-Command
          + Signal-Task-Stopped-Okay
    (--) Start-Auto                         -> Task-Running
          + 
    (--) Stop-Auto                          -> Task-Stopped
          + Shut-Down-Child-Task
          + Run-Task-Cancel-Command
          + Run-Task-Idle-Command
    (--) Status                             -> Task-Running
          + Signal-Task-Running
    (--) Task-Alarm                         -> Task-Running
          + Check-Task-Still-Running
          + Monitor-Active-Task-Status
    (--) Task-Stopped                       -> Task-Stopped
          + Run-Task-Idle-Command
    (--) Exception                          -> Task-Stopped
          + Signal-Task-Started-Error
    !  Shutdown handling for an active task is a special case
    (--) Shutdown                           -> 
          + Shut-Down-Child-Task
          + Run-Task-Cancel-Command
          + Run-Task-Idle-Command
          + Destroy-The-Task
          + Terminate-The-Thread

Defaults:
    (--) Sock-Error                         -> End-Thread
          + Signal-Socket-Error
          + Check-Thread-Type
    (--) Sock-Closed                        -> End-Thread
          + Check-Thread-Type
    (--) Exception                          -> End-Thread
          + Check-Thread-Type
    (--) Shutdown                           -> End-Thread
          + Check-Thread-Type
    (--) Fatal                              -> End-Thread
          + Check-Thread-Type

End-Thread:
    (--) Master                             ->
          + Close-Manager-Log-File
          + Shutdown-The-Application
          + Terminate-The-Thread
    (--) Control                            ->
          + Terminate-The-Thread
    (--) Task                               ->
          + Destroy-The-Task
          + Terminate-The-Thread
