!----------------------------------------------------------------------------
!   Name:       smtrdns.l
!   Title:      Dialog for SMT DNS Resolver agent
!   Package:    Libero SMT 2.x
!
!   Written:    97/10/12  iMatix SMT kernel team <smt@imatix.com>
!   Revised:    97/11/27
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c
-idle

After-Init:
    (--) Master                             -> Master-Input
          + Load-Host-File-In-Cache
          + Load-Name-Server-Config
          + Set-Refresh-Cache-Timer
    (--) Client                             -> Request-Type
          + Prepare-Client-Thread
          + Get-Current-Request-Type
    (--) Initialisation-Error               -> End-Thread
          + Signal-Error
          + Check-Thread-Type

Master-Input:
    (--) Get-Host                           -> After-Thread-Search
          + Get-Host-Message-Value
          + Search-Thread-For-Request
    (--) Get-Ip                             -> After-Thread-Search
          + Get-Ip-Message-Value
          + Search-Thread-For-Request
    (--) Timer                              -> Master-Input
          + Refresh-Cache
          + Set-Refresh-Cache-Timer

After-Thread-Search:
    (--) Not-Found                          -> Master-Input
          + Create-Request-Thread
    (--) Found                              -> Master-Input
          + Add-User-Data-In-Client-Thread

Request-Type:
    (--) Host-Name                          -> Host-Name-In-Cache
          + Lookup-Ip-In-Cache
    (--) Name-Server-Ip                     -> Server-Connection
          + Check-Server-Address
    (--) Ip-Value                           -> Ip-Address-In-Cache
          + Lookup-Host-In-Cache

Host-Name-In-Cache:
    (--) Found                              -> End-Thread
          + Send-Host-Name-Value
          + Check-Thread-Type
    (--) Found-Bad                          -> End-Thread
          + Signal-End-Of-Search
          + Check-Thread-Type
    (--) Not-Found                          -> Server-Connection
          + Create-Timeout-Alarm
          + Check-Server-Address

Ip-Address-In-Cache:
    (--) Found                              -> End-Thread
          + Send-Ip-Address-Value
          + Check-Thread-Type
    (--) Found-Bad                          -> End-Thread
          + Signal-End-Of-Search
          + Check-Thread-Type
    (--) Not-Found                          -> Server-Connection
          + Create-Timeout-Alarm
          + Check-Server-Address

Server-Connection:
    (--) Ok                                 -> Server-Connected
          + Connect-To-Server
    (--) Error                              -> End-Thread
          + Signal-Error
          + Check-Thread-Type

Server-Connected:
    (--) Ok                                 -> Query-Type
          + Get-Socket-Handle
          + Get-Current-Request-Type
    (--) Sock-Timeout                       -> After-Next-Request
          + Get-Next-Request
    (--) Sock-Closed                        -> After-Next-Request
          + Get-Next-Request
    (--) Sock-Error                         -> After-Next-Request
          + Get-Next-Request

Query-Type:
    (--) Host-Name                          -> After-Send-Query
          + Make-Reverse-Query-Buffer
          + Send-Query-To-Server
    (--) Name-Server-Ip                     -> After-Send-Query
          + Make-Ip-Query-Buffer
          + Send-Query-To-Server
    (--) Ip-Value                           -> After-Send-Query
          + Make-Ip-Query-Buffer
          + Send-Query-To-Server

After-Send-Query:
    (--) Ok                                 -> Read-Answer
          + Wait-For-Socket-Input
    (--) Sock-Retry                         -> After-Send-Query
          + Send-Query-To-Server
    (--) Sock-Error                         -> After-Next-Request
          + Get-Next-Request
    (--) Sock-Timeout                       -> After-Next-Request
          + Get-Next-Request
    (--) Sock-Closed                        -> After-Next-Request
          + Get-Next-Request

Read-Answer:
    (--) Input-Ok                           -> Recursive-Check
          + Read-Answer-From-Server
          + Check-If-Answer-Is-Complete
          + Check-Recursive-Value
    (--) Read-More                          -> Read-Answer
          + Wait-For-Socket-Input
    (--) Sock-Error                         -> After-Next-Request
          + Get-Next-Request
    (--) Sock-Timeout                       -> After-Next-Request
          + Get-Next-Request
    (--) Sock-Closed                        -> After-Next-Request
          + Get-Next-Request

Recursive-Check:
    (--) Ok                                 -> Get-Answer
          + Get-Number-Of-Rr
          + Get-Main-Request-Type
    (--) Invalid                            -> Server-Connection
          + Set-New-Value-Of-Recursive
          + Clean-Previous-Request-Resource
          + Check-Server-Address

Get-Answer:
    (--) Host-Name                          -> Answer-For-Host-Request
          + Get-Answer-Result
    (--) Ip-Value                           -> Answer-For-Ip-Request
          + Get-Answer-Result

Answer-For-Host-Request:
    (--) Host-Name                          -> End-Thread
          + Send-Host-Name-Value
          + Add-To-Cache
          + Check-Thread-Type
    (--) Ip-Value                           -> After-Next-Request
          + Create-Host-Request
          + Purge-Equivalent-Request-From-Stack
          + Get-Next-Request
    (--) Name-Server                        -> After-Next-Request
          + Get-Next-Request

Answer-For-Ip-Request:
    (--) Host-Name                          -> After-Next-Request
          + Create-Ip-Request
          + Purge-Equivalent-Request-From-Stack
          + Get-Next-Request
    (--) Ip-Value                           -> End-Thread
          + Send-Ip-Address-Value
          + Add-To-Cache
          + Check-Thread-Type
    (--) Name-Server                        -> After-Next-Request
          + Get-Next-Request

After-Next-Request:
    (--) Ok                                 -> Validate-Request
          + Check-Request-In-Invalid-Server-Table
    (--) End                                -> End-Thread
          + Signal-End-Of-Search
          + Add-Bad-Result-To-Cache
          + Check-Thread-Type
    (--) Error                              -> End-Thread
          + Signal-Error
          + Add-Bad-Result-To-Cache
          + Check-Thread-Type

Validate-Request:
    (--) Ok                                 -> Server-Connection
          + Clean-Previous-Request-Resource
          + Check-Server-Address
    (--) Invalid                            -> After-Next-Request
          + Get-Next-Request

Defaults:
    (--) Timer                              -> End-Thread
          + Signal-Timeout
          + Add-Bad-Result-To-Cache
          + Check-Thread-Type
    (--) Input-Ok                           -> 
          + 
    (--) Ok                                 -> 
          + 
    (--) Exception                          -> End-Thread
          + Check-Thread-Type
    (--) Shutdown                           -> End-Thread
          + Check-Thread-Type
    (--) Fatal                              -> 
          + Terminate-The-Thread
    (--) Error                              -> End-Thread
          + Signal-Error
          + Check-Thread-Type
    (--) Cancel                             -> End-Thread
          + Check-Thread-Type
    (--) Sock-Error                         -> End-Thread
          + Signal-Error
          + Check-Thread-Type
    (--) Sock-Closed                        -> End-Thread
          + Check-Thread-Type
    (--) Sock-Timeout                       -> End-Thread
          + Check-Thread-Type
    (--) Sock-Retry                         -> End-Thread
          + Check-Thread-Type

End-Thread:
    (--) Master                             -> 
          + Free-All-Server-Resources
          + Terminate-The-Thread
    (--) Client                             -> 
          + Flush-Timeout-Alarm
          + Terminate-The-Thread
