!----------------------------------------------------------------------------
!   Name:       smtupmc.l
!   Title:      Dialog for UPM client agent
!   Package:    Libero SMT 2.x
!
!   Written:    96/09/06  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    97/09/08
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c

After-Init:
    (--) Ok                                 -> Have-Connection
          + Connect-To-Upm-Daemon
    (--) Error                              ->
          + Terminate-The-Thread

Have-Connection:
    (--) Ok                                 -> Making-Connection
          + Store-Connection-Data
          + Get-Daemon-Message
          + Check-Daemon-Message

Making-Connection:
    (--) Upm-Ready                          -> User-Command
          + Signal-Connected-Okay
          + Get-User-Command-Input

Daemon-Message:
    (--) Upm-Ready                          -> User-Command
          + Get-User-Command-Input
    (--) Upm-Task-Id                        -> Daemon-Message
          + Show-Task-Name
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Start-Ok                       -> Daemon-Message
          + Signal-Task-Started-Ok
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Start-Error                    -> Daemon-Message
          + Signal-Task-Not-Started
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Stop-Ok                        -> Daemon-Message
          + Signal-Task-Stopped-Ok
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Stop-Error                     -> Daemon-Message
          + Signal-Task-Not-Stopped
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Task-Nf                        -> Daemon-Message
          + Signal-Task-Not-Known
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Task-Running                   -> Daemon-Message
          + Signal-Task-Running
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Task-Stopped                   -> Daemon-Message
          + Signal-Task-Stopped
          + Get-Daemon-Message
          + Check-Daemon-Message

User-Command:
    (--) List                               -> Daemon-Message
          + Send-Daemon-List-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Stop                               -> Daemon-Message
          + Send-Daemon-Stop-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Start                              -> Daemon-Message
          + Send-Daemon-Start-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Status                             -> Daemon-Message
          + Send-Daemon-Status-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Halt                               -> Daemon-Halting
          + Send-Daemon-Halt-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Version                            -> User-Command
          + Show-Version-Information
          + Get-User-Command-Input
    (--) Help                               -> User-Command
          + Show-Help-Information
          + Get-User-Command-Input
    (--) Exit                               ->
          + Terminate-The-Thread
    (--) Empty                              -> User-Command
          + Get-User-Command-Input
    (--) Error                              -> User-Command
          + Signal-Invalid-Command
          + Get-User-Command-Input

Daemon-Halting:
    (--) Upm-Halting                        ->
          + Terminate-The-Thread

Defaults:
    (--) Sock-Closed                        ->
          + Signal-Socket-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Terminate-The-Thread
    (--) Upm-Ready                          ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Error                          ->
          + Signal-Upm-Fatal-Error
          + Terminate-The-Thread
    (--) Upm-Halting                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Id                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Ok                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Nf                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Running                   ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Stopped                   ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Start-Ok                       ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Start-Error                    ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Stop-Ok                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Stop-Error                     ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread
