!-------------------------------------------------------------------<Prolog>-
!   Name:       xilrwp.l
!   Title:      Dialog for xilrwp.c agent
!   Package:    Xitami
!
!   Written:    97/10/29   Robin P. Dunn   Total Control Software
!   Revised:    99/03/18   Ewen McNeill    iMatix Corporation    for LRWP 2.0
!               99/11/11   Xitami Team <xitami@imatix.com>
!
!   Notes:      Libero format FSM dialog for my Long Running Web Process
!               interface for plugging into the Xitami web server.  This
!               handles listening for and accepting connections from
!               an external LRWP process, (called a PEER), as well as
!               forwarding HTTP requests to the process and retrieving
!               the response.
!
!   Copyright:  Copyright (c) 1998 Total Control Software
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!------------------------------------------------------------------</Prolog>-*/

-schema=smtschm.c
-idle
-nosort
-stats

!
!------------------------------------------------------------------------
! default state

After-Init:
    (--) Master                             -> Master-Input
          + Open-Master-Socket
          + Wait-For-Socket-Input
    (--) Peer                               -> Peer-Startup
          + Wait-For-Socket-Input
    (--) Router                             -> Wait-For-Router-Request
          + Setup-Router
!
!------------------------------------------------------------------------
! The listening socket

Master-Input:
    (--) Sock-Input-Ok                      -> Master-Input
          + Accept-Peer-Connection
          + Wait-For-Socket-Input
!
!------------------------------------------------------------------------
! Handles communications with the peer application

Peer-Startup:
    (--) Sock-Input-Ok                      -> Peer-Negotiation
          + Read-App-Connection-Request
    (--) Sock-Closed                        ->
          + Terminate-The-Thread

Peer-Negotiation:
    ! For LRWP 1.0 only Peer-Accepted is used (immediately).
    ! For LRWP 2.0 if challenges are turned off, then Peer-Accepted is
    !     used immediately.  Otherwise Challenge-Peer is used to send
    !     out a challenge, and wait for the response.  The response is
    !     received and checked, and if valid Peer-Accepted is used.
    !
    ! Startup-Error is used for errors at any stage in start up negotation
    !
    (--) Peer-Accepted                      -> Waiting-For-Request
          + Register-Peer
          + Send-Peer-Acknowledgement
          + Wait-For-Socket-Input
    (--) Challenge-Peer                     -> Receive-Negotiation-Response-Size
          + Send-Peer-Negotiation-Challenge
          + Wait-For-Socket-Input
    (--) Startup-Error                      ->
          + Signal-startup-error
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Signal-Peer-Closed
          + Terminate-The-Thread

Receive-Negotiation-Response-Size:
    ! Auxilliary peer negotation state -- receives size of challenge response
    (--) Sock-Input-Ok                      -> Receive-Negotiation-Response
          + Read-Peer-Data-Size
          + Wait-For-Socket-Input
    (--) Sock-Closed                        ->
          + Send-Error-Reply
          + Signal-Peer-Closed
    (--) Sock-Error                         ->
          + Send-Error-Reply
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread

Receive-Negotiation-Response:
    ! Auxilliary peer negotation state -- receives challenge response
    ! and validates response (returning to peer-negotation when done)
    (--) Sock-Input-Ok                      -> Receive-Negotiation-Response
          + Read-Peer-Data
          + Wait-For-Socket-Input
    (--) Finished                           -> Peer-Negotiation
          + Check-Peer-Negotiation-Response
    (--) Sock-Closed                        ->
          + Send-Error-Reply
          + Signal-Peer-Closed
    (--) Sock-Error                         ->
          + Send-Error-Reply
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread

Waiting-For-Request:
    (--) LRWP-Request                       -> Waiting-For-Peer-Response
          + Send-Request-Data-To-Peer
          + Wait-For-Socket-Input
    (--) Sock-Closed                        ->
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Sock-Input-Ok                      ->
    ! While waiting on an INPUT and the peer closes the socket, we
    ! get a Sock-Input-Ok event instead of a Sock-Closed event...
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Startup-Error                      ->
          + Signal-startup-error
          + Terminate-The-Thread


Waiting-For-Peer-Response:
    (--) Sock-Input-Ok                      -> Wait-For-Peer-Data-Block
          + Read-Peer-Data-Size
          + Wait-For-Socket-Input
    (--) Sock-Write-Ok                      ->
          +
    (--) Sock-Closed                        ->
          + Send-Error-Reply
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Send-Error-Reply
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread

Wait-For-Peer-Data-Block:
    (--) Sock-Input-Ok                      -> Wait-For-Peer-Data-Block
          + Read-Peer-Data
          + Wait-For-Socket-Input
    (--) Finished                           -> Waiting-For-Request
          + Send-Peer-Data-To-Xitami
          + Cleanup-And-Inform-Router
          + Wait-For-Socket-Input
    (--) Sock-Closed                        ->
          + Send-Error-Reply
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Send-Error-Reply
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread
!
!------------------------------------------------------------------------
! The router thread

Wait-For-Router-Request:
    (--) WSX-Request                        -> Wait-For-Router-Request
          + Find-Available-Peer
    (--) Peer-Job-Completed                 -> Wait-For-Router-Request
          + Check-For-Saved-Requests
    (--) Peer-Closed                        -> Wait-For-Router-Request
          + Check-if-all-gone
!
!------------------------------------------------------------------------
! shared events

Defaults:
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread
    (--) Fatal                              ->
          + Shutdown-The-Application
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Signal-Socket-Error
          + Terminate-The-Thread
    (--) Protocol-Error                     ->
          + Terminate-The-Thread

