!----------------------------------------------------------------------------
!   Name:       xiadmin.l
!   Title:      Dialog for Xitami administration agent
!   Package:    Xitami
!
!   Written:    97/08/03  Xitami Team <xitami@imatix.com>
!   Revised:    98/12/15  Xitami Team <xitami@imatix.com>
!
!   Copyright:  Copyright (c) 1991-99 iMatix Corporation
!   License:    This is free software; you can redistribute it and/or modify
!               it under the terms of the SMT License Agreement as provided
!               in the file LICENSE.TXT.  This software is distributed in
!               the hope that it will be useful, but without any warranty.
!----------------------------------------------------------------------------
-schema=smtschm.c
-idle
-nosort
-stats

After-Init:
    (--) Ok                                 -> Start-Session
          +

Start-Session:
    (--) Ok                                 -> Select-Initial
          + Determine-Initial-Screen

Select-Initial:
    (--) Main                               -> Main-Menu
          + Open-Main-Admin-Menu
          + Show-Main-Admin-Menu
          + Decode-Http-Request-Reponse
    (--) Config                             -> Config-Server
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Hosts                              -> Config-List
          + Open-Config-List
          + Show-Config-List-First
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Return                             -> Main-Menu
          + Close-All-Forms
          + Open-Main-Admin-Menu
          + Show-Main-Admin-Menu
          + Decode-Http-Request-Reponse

Main-Menu:
    (--) Config                             -> Config-Server
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Hosts                              -> Config-List
          + Open-Config-List
          + Show-Config-List-First
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Wizard                             -> Vhost-Wizard
          + Open-Vhost-Wizard
          + Show-Vhost-Wizard
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Return                             -> Main-Menu
          + Close-All-Forms
          + Open-Main-Admin-Menu
          + Show-Main-Admin-Menu
          + Decode-Http-Request-Reponse

Config-List:
    (--) Enter                              ->
          + Check-Config-List-Livelink
    (--) Back                               ->
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Close-Current-Form
          + Dialog-Return
    (--) New                                -> Vhost-Wizard
          + Open-Vhost-Wizard
          + Show-Vhost-Wizard
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) First                              ->
          + Show-Config-List-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Show-Config-List-Next
          + Decode-Http-Request-Reponse
    (--) Default                            -> Config-Server
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Basehost                           -> Config-Server
          + Use-Basehost-Config-Name
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
!   Exceptions generated in this state
    (--) Select-Config                      -> Config-Server
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Reshow-Form                        ->
          + Show-Config-List-First
          + Decode-Http-Request-Reponse
    (--) Return                             ->
          + Show-Config-List-First
          + Decode-Http-Request-Reponse

Config-Server:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Server
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Server-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Value-List
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Aliases
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Mimes                              -> Config-Value-List
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Mimes
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Errors                             -> Config-Errors
          + Update-Config-Server
          + Open-Config-Errors
          + Show-Config-Errors
          + Decode-Http-Request-Reponse
    (--) Wsx                                -> Config-Server-List
          + Update-Config-Server
          + Open-Config-Wsx
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Filters                            -> Config-Server-List
          + Update-Config-Server
          + Open-Config-Filter
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Test                               ->
          + Update-Config-Server
          + Test-Url-Mapping
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse

Config-Value-List:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Clear                              ->
          + Clear-Config-Value-List
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Show-Config-Value-List-Next
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Value-List
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Aliases
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Mimes                              -> Config-Value-List
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Mimes
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-Server-List:  <Config-Value-List>
    (--) Back                               -> Config-Server
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Server
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse

Config-Errors:
    (--) Back                               -> Config-Server
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Server
          + Update-Config-Errors
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Default                            ->
          + Show-Config-Errors-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Errors
          + Decode-Http-Request-Reponse

Config-Cgi:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Cgi
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Cgi-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Value-List
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Aliases
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Mimes                              -> Config-Value-List
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Mimes
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Define-Environ                     -> Config-Cgi-Sub-List
          + Update-Config-Cgi
          + Open-Config-Cgi-Envir
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Define-Aliases                     -> Config-Cgi-Sub-List
          + Update-Config-Cgi
          + Open-Config-Cgi-Alias
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-Cgi-Sub-List:  <Config-Value-List>
    (--) Back                               -> Config-Cgi
          + Close-Current-Form
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Cgi
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse

Config-Ftp:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Ftp
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Ftp-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Value-List
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Aliases
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Mimes                              -> Config-Value-List
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Mimes
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Define-Users                       -> Config-Ftp-Users
          + Update-Config-Ftp
          + Open-Config-Ftp-Users
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) Define-Dirs                        -> Config-Ftp-Dirs
          + Update-Config-Ftp
          + Open-Config-Ftp-Dirs
          + Show-Config-Ftp-Dirs-First
          + Decode-Http-Request-Reponse
    (--) Define-Aliases                     -> Config-Ftp-Sub-List
          + Update-Config-Ftp
          + Open-Config-Ftp-Alias
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-Ftp-Users:  <Config-Value-List>
    (--) Enter                              ->
          + Check-Ftp-Users-Livelink
    (--) New                                -> Config-Ftp-User
          + Open-Config-Ftp-User
          + Show-Config-Ftp-User-New
          + Decode-Http-Request-Reponse
    (--) Back                               -> Config-Ftp
          + Cancel-Config-Resource-File
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp
          + Save-Config-Resource-File
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Cancel-Config-Resource-File
          + Open-Config-Ftp-Users
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Show-Config-Ftp-Users-Next
          + Decode-Http-Request-Reponse
    (--) Refresh                            ->
          + Show-Config-Ftp-Users-Same
          + Decode-Http-Request-Reponse
!   Exceptions generated in this state
    (--) Select-User                        -> Config-Ftp-User
          + Open-Config-Ftp-User
          + Show-Config-Ftp-User
          + Decode-Http-Request-Reponse

Config-Ftp-User:
    (--) Back                               -> Config-Ftp-Users
          + Close-Current-Form
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) New                                ->
          + Show-Config-Ftp-User-New
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp-Users
          + Update-Config-Ftp-User
          + Close-Current-Form
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) Delete                             ->
          + Delete-Config-Ftp-User
          + Show-Config-Ftp-User-First
          + Decode-Http-Request-Reponse
    (--) Default                            ->
          + Show-Config-Ftp-User-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Ftp-User
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Update-Config-Ftp-User
          + Show-Config-Ftp-User-First
          + Decode-Http-Request-Reponse
    (--) Define                             ->
          + Set-Permissions-As-Chosen
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Update-Config-Ftp-User
          + Show-Config-Ftp-User-Next
          + Decode-Http-Request-Reponse

Config-Ftp-Dirs:
    (--) Enter                              ->
          + Check-Ftp-Dir-Livelink
    (--) Back                               -> Config-Ftp
          + Cancel-Config-Ftp-Dir-File
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp
          + Save-Config-Ftp-Dir-File
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Show-Config-Ftp-Dirs-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Show-Config-Ftp-Dirs-Next
          + Decode-Http-Request-Reponse
    (--) Define                             -> Config-Ftp-User-List
          + Check-New-Ftp-Dir-Name
          + Open-Config-Ftp-User-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
!   Exceptions generated in this state
    (--) Select-Resource                    -> Config-Ftp-User-List
          + Open-Config-Ftp-User-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-Ftp-User-List:  <Config-Value-List>
    (--) Back                               -> Config-Ftp-Dirs
          + Close-Current-Form
          + Show-Config-Ftp-Dirs-Same
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp-Dirs
          + Validate-Config-Value-List
          + Update-Config-Ftp-User-List
          + Close-Current-Form
          + Show-Config-Ftp-Dirs-Same
          + Decode-Http-Request-Reponse

Config-Ftp-Sub-List:  <Config-Value-List>
    (--) Back                               -> Config-Ftp
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse

Config-Security:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Security
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Security-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Value-List
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Aliases
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Mimes                              -> Config-Value-List
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Mimes
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Define                             -> Config-Resources
          + Update-Config-Security
          + Open-Config-Resources
          + Show-Config-Resources-First
          + Decode-Http-Request-Reponse

Config-Resources:
    (--) Enter                              ->
          + Check-Resources-Livelink
    (--) Back                               -> Config-Security
          + Cancel-Config-Resource-File
          + Close-Current-Form
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Security
          + Update-Config-Resources
          + Save-Config-Resource-File
          + Close-Current-Form
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Resources-First
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Update-Config-Resources
          + Show-Config-Resources-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Update-Config-Resources
          + Show-Config-Resources-Next
          + Decode-Http-Request-Reponse
    (--) Define                             -> Config-User-List
          + Update-Config-Resources
          + Check-New-Resource-Name
          + Open-Config-User-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
!   Exceptions generated in this state
    (--) Select-Resource                    -> Config-User-List
          + Open-Config-User-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-User-List: <Config-Value-List>
    (--) Back                               -> Config-Resources
          + Close-Current-Form
          + Show-Config-Resources-Same
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Resources
          + Update-Config-User-List
          + Close-Current-Form
          + Show-Config-Resources-Same
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Update-Config-Value-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Update-Config-Value-List
          + Show-Config-Value-List-Next
          + Decode-Http-Request-Reponse

Config-Logging:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Logging
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Logging-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Value-List
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Aliases
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Mimes                              -> Config-Value-List
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Mimes
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Console-Panel:
    (--) Back                               -> Main-Menu
          + Close-All-Forms
          + Open-Main-Admin-Menu
          + Show-Main-Admin-Menu
          + Decode-Http-Request-Reponse
    (--) Clear                              ->
          + Clear-Console-Panel-Statistics
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Refresh                            ->
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Define                             -> Console-Config
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Console-Config
          + Show-Console-Config
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Return                             ->
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Messages                           -> Console-Messages
          + Open-Console-Messages
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Details                            -> Connection-List
          + Open-Connection-List
          + Show-Connection-List
          + Decode-Http-Request-Reponse
    (--) Reshow-Form                        ->
          + Show-Console-Panel
          + Decode-Http-Request-Reponse

Console-Messages:
    (--) Back                               -> Console-Panel
          + Close-Current-Form
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Clear                              ->
          + Clear-Console-Messages
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Refresh                            ->
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Define                             -> Console-Config
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Console-Config
          + Show-Console-Config
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Return                             ->
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Invert                             ->
          + Invert-Console-Data
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Reshow-Form                        ->
          + Show-Console-Messages
          + Decode-Http-Request-Reponse

Console-Config:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Console-Config
          + Save-Current-Config-File
          + Reload-Server-Base-Config
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Console-Config-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Console-Config
          + Decode-Http-Request-Reponse

Connection-List:
    (--) Back                               -> Console-Panel
          + Close-Current-Form
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Refresh                            ->
          + Show-Connection-List
          + Decode-Http-Request-Reponse
    (--) Reshow-Form                        ->
          + Show-Connection-List
          + Decode-Http-Request-Reponse

Vhost-Wizard:
    (--) Back                               ->
          + Close-Current-Form
          + Dialog-Return
    (--) Define                             ->
          + Validate-Vhost-Definition
          + Create-Vhost-Definition
          + Close-Current-Form
          + Dialog-Return

Defaults:
    (--) Resource                           ->
          + Send-Resource-File-If-Known
          + Decode-Http-Request-Reponse
    (--) New-Session                        -> Select-Initial
          + Close-All-Forms
          + Determine-Initial-Screen
    (--) Reshow-Form                        ->
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Exception                          ->
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Data-Error                         ->
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Shutdown                           ->
          + Close-All-Forms
          + Terminate-The-Thread
    (--) Timeout                            ->
          +
!   Generally the same
    (--) Enter                              ->
          + Check-Simple-Livelink
    (--) Exit                               -> Start-Session
          + Close-All-Forms
          + Redirect-To-Home-Page
    (--) Console                            -> Console-Panel
          + Close-All-Forms
          + Open-Console-Panel
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Restart                            ->
          + Restart-Http-Server-Agent
          + Decode-Http-Request-Reponse
    (--) Halt                               ->
          + Shutdown-Http-Server-Agent
          + Decode-Http-Request-Reponse
    (--) Help                               ->
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
