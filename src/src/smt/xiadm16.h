/*---------------------------------------------------------------------------
 *  xiadm16.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM16__
#define __FORM_XIADM16__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM16_MESSAGE_TO_USER             0
#define XIADM16_L_ENABLED                   1
#define XIADM16_ENABLED                     2
#define XIADM16_L_ROOTDIR                   3
#define XIADM16_ROOTDIR                     4
#define XIADM16_L_PORT                      5
#define XIADM16_PORT                        6
#define XIADM16_L_TIMEOUT                   7
#define XIADM16_TIMEOUT                     8
#define XIADM16_L_LIMIT                     9
#define XIADM16_LIMIT                       10
#define XIADM16_L_USER_FILE                 11
#define XIADM16_USER_FILE                   12
#define XIADM16_L_DIRECTORY_FILE            13
#define XIADM16_DIRECTORY_FILE              14
#define XIADM16_L_WELCOME                   15
#define XIADM16_WELCOME                     16
#define XIADM16_L_LOGIN                     17
#define XIADM16_LOGIN                       18
#define XIADM16_L_SIGNOFF                   19
#define XIADM16_SIGNOFF                     20
#define XIADM16_L_DIRSORT                   21
#define XIADM16_DIRSORT                     22
#define XIADM16_L_EMAIL_CHECK               23
#define XIADM16_EMAIL_CHECK                 24
#define XIADM16_L_HTTP_ALIASES              25
#define XIADM16_HTTP_ALIASES                26
#define XIADM16_L_PASSWORD_CASE             27
#define XIADM16_PASSWORD_CASE               28
#define XIADM16_L_SOFT_QUOTA                29
#define XIADM16_SOFT_QUOTA                  30
#define XIADM16_L_HARD_QUOTA                31
#define XIADM16_HARD_QUOTA                  32
#define XIADM16_L_ALOG_ENABLED              33
#define XIADM16_ALOG_ENABLED                34
#define XIADM16_L_ALOG_FILENAME             35
#define XIADM16_ALOG_FILENAME               36
#define XIADM16_L_ALOG_CYCLE                37
#define XIADM16_ALOG_CYCLE                  38
#define XIADM16_L_ALOG_LOCAL                39
#define XIADM16_ALOG_LOCAL                  40
#define XIADM16_L_ELOG_ENABLED              41
#define XIADM16_ELOG_ENABLED                42
#define XIADM16_L_ELOG_FILENAME             43
#define XIADM16_ELOG_FILENAME               44
#define XIADM16_L_ELOG_CYCLE                45
#define XIADM16_ELOG_CYCLE                  46
#define XIADM16_L_ELOG_LOCAL                47
#define XIADM16_ELOG_LOCAL                  48
#define XIADM16_L_WEBMASK                   49
#define XIADM16_WEBMASK                     50
#define XIADM16_L_DATA_PORT                 51
#define XIADM16_DATA_PORT                   52
#define XIADM16_L_IPADDRESS                 53
#define XIADM16_IPADDRESS                   54

/*  This table contains each block in the form                               */

static byte xiadm16_blocks [] = {
    /*  <HTML>                                                               */
    0, 8, 0, '<', 'H', 'T', 'M', 'L', '>', 10,
    /*  <HEAD><TITLE>Xitami Administration</TITLE></HEAD>                    */
    0, 51, 0, '<', 'H', 'E', 'A', 'D', '>', '<', 'T', 'I', 'T', 'L',
    'E', '>', 'X', 'i', 't', 'a', 'm', 'i', 32, 'A', 'd', 'm', 'i', 'n',
    'i', 's', 't', 'r', 'a', 't', 'i', 'o', 'n', '<', '/', 'T', 'I',
    'T', 'L', 'E', '>', '<', '/', 'H', 'E', 'A', 'D', '>', 10,
    /*  <BODY onLoad="focus()" BGCOLOR="#87CEFA">                            */
    0, 43, 0, '<', 'B', 'O', 'D', 'Y', 32, 'o', 'n', 'L', 'o', 'a', 'd',
    '=', '"', 'f', 'o', 'c', 'u', 's', '(', ')', '"', 32, 'B', 'G', 'C',
    'O', 'L', 'O', 'R', '=', '"', '#', '8', '7', 'C', 'E', 'F', 'A',
    '"', '>', 10,
    /*  <TABLE CELLSPACING=0 CELLPADDING=0 WIDTH=100%>                       */
    0, 48, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'C', 'E', 'L', 'L', 'S',
    'P', 'A', 'C', 'I', 'N', 'G', '=', '0', 32, 'C', 'E', 'L', 'L', 'P',
    'A', 'D', 'D', 'I', 'N', 'G', '=', '0', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <FORM METHOD=POST ACTION="#(uri)">                                   */
    0, 36, 0, '<', 'F', 'O', 'R', 'M', 32, 'M', 'E', 'T', 'H', 'O', 'D',
    '=', 'P', 'O', 'S', 'T', 32, 'A', 'C', 'T', 'I', 'O', 'N', '=', '"',
    '#', '(', 'u', 'r', 'i', ')', '"', '>', 10,
    /*  <INPUT TYPE=HIDDEN NAME=jsaction VALUE="">                           */
    0, 44, 0, '<', 'I', 'N', 'P', 'U', 'T', 32, 'T', 'Y', 'P', 'E', '=',
    'H', 'I', 'D', 'D', 'E', 'N', 32, 'N', 'A', 'M', 'E', '=', 'j', 's',
    'a', 'c', 't', 'i', 'o', 'n', 32, 'V', 'A', 'L', 'U', 'E', '=', '"',
    '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT>                                                  */
    0, 21, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 51, 0, '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/', 'a',
    'd', 'm', 'i', 'n', '/', '$', 'l', 'e', 'f', 't', '.', 'g', 'i',
    'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A', 'L',
    'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>',
    /*  !--ACTION back  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 0, 0, 0, 'b', 'a', 'c', 'k', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c', 'k', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION save  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 0, 0, 0, 's', 'a', 'v', 'e', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v', 'e', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION default  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 2, 0, 0, 0, 0, 0, 'd', 'e', 'f', 'a', 'u',
    'l', 't', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'd', 'e', 'f',
    'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION undo  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 0, 0, 0, 'u', 'n', 'd', 'o', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd', 'o', '.', 'g',
    'i', 'f', 0,
    /*  <A HREF="/xitami/index4.htm" ... .gif" BORDER=0 ALIGN=MIDDLE>        */
    0, 162, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x',
    'i', 't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.',
    'h', 't', 'm', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T', '=', '"', 'H',
    'e', 'l', 'p', '"', '>', '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=',
    '"', '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'e', 'l', 'p',
    '.', 'g', 'i', 'f', '"', 32, 'A', 'L', 'T', '=', '"', 'H', 'e', 'l',
    'p', 32, '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A',
    'L', 'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', '<',
    '/', 'A', '>', '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'i', 'g', 'h', 't', '.',
    'g', 'i', 'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32,
    'A', 'L', 'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', 10,
    /*  <TD ALIGN=CENTER><FONT SIZE= ...  - FTP Configuration </FONT>        */
    0, 70, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'F', 'T', 'P', 32, 'C', 'o', 'n', 'f', 'i', 'g',
    'u', 'r', 'a', 't', 'i', 'o', 'n', 32, '<', '/', 'F', 'O', 'N', 'T',
    '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 1, 9,
    /*  !--ACTION console  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 4, 0, 0, 0, 0, 0, 'c', 'o', 'n', 's', 'o',
    'l', 'e', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'c', 'o', 'n',
    's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION halt  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 5, 0, 0, 0, 0, 0, 'h', 'a', 'l', 't', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION restart  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 6, 0, 0, 0, 0, 0, 'r', 'e', 's', 't', 'a',
    'r', 't', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'e', 's',
    't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION exit  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 7, 0, 0, 0, 0, 0, 'e', 'x', 'i', 't', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i', 't', '.', 'g',
    'i', 'f', 0,
    /*  <IMG SRC="/admin/$right.gif" BORDER=0 ALIGN=MIDDLE>                  */
    0, 53, 0, '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/', 'a',
    'd', 'm', 'i', 'n', '/', '$', 'r', 'i', 'g', 'h', 't', '.', 'g',
    'i', 'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A',
    'L', 'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', 10,
    /*  </TABLE>                                                             */
    0, 10, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', 10,
    /*  <TABLE WIDTH=100%><TR><TD ALIGN=LEFT>                                */
    0, 39, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', '<', 'T', 'R', '>', '<', 'T', 'D', 32,
    'A', 'L', 'I', 'G', 'N', '=', 'L', 'E', 'F', 'T', '>', 10,
    /*  !--IF message_to_user                                                */
    0, 5, 2, 0, 0, 0, 3,
    /*  <FONT COLOR="#E00000" SIZE=+1><EM>                                   */
    0, 36, 0, '<', 'F', 'O', 'N', 'T', 32, 'C', 'O', 'L', 'O', 'R', '=',
    '"', '#', 'E', '0', '0', '0', '0', '0', '"', 32, 'S', 'I', 'Z', 'E',
    '=', '+', '1', '>', '<', 'E', 'M', '>', 10,
    /*  !--FIELD TEXTUAL message_to_user SIZE=80                             */
    0, 25, 10, 9, 1, 0, 0, 'P', 0, 'P', 'm', 'e', 's', 's', 'a', 'g',
    'e', '_', 't', 'o', '_', 'u', 's', 'e', 'r', 0, 0,
    /*  </EM></FONT>                                                         */
    0, 14, 0, '<', '/', 'E', 'M', '>', '<', '/', 'F', 'O', 'N', 'T',
    '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 4, 1, 0, 2, 188,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 165,
    /*  <TABLE CELLSPACING=0 CELLPADDING=0 WIDTH=100%><TR>                   */
    0, 52, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'C', 'E', 'L', 'L', 'S',
    'P', 'A', 'C', 'I', 'N', 'G', '=', '0', 32, 'C', 'E', 'L', 'L', 'P',
    'A', 'D', 'D', 'I', 'N', 'G', '=', '0', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', '<', 'T', 'R', '>', 10,
    /*  <TD ALIGN=LEFT><FONT SIZE=-1>                                        */
    0, 31, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E',
    'F', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E', '=',
    45, '1', '>', 10,
    /*  !--ACTION errors  LABEL="Err ... ENT=errors_event TYPE=PLAIN         */
    0, 25, 20, 1, (byte) ((word) errors_event / 256), (byte) ((word)
    errors_event & 255), 0, 8, 0, 0, 0, 0, 0, 'e', 'r', 'r', 'o', 'r',
    's', 0, 'E', 'r', 'r', 'o', 'r', 's', 0,
    /*  !--ACTION wsx  LABEL="WSX" EVENT=wsx_event TYPE=PLAIN                */
    0, 19, 20, 1, (byte) ((word) wsx_event / 256), (byte) ((word)
    wsx_event & 255), 0, 9, 0, 0, 0, 0, 0, 'w', 's', 'x', 0, 'W', 'S',
    'X', 0,
    /*  !--ACTION filters  LABEL="Fi ... NT=filters_event TYPE=PLAIN         */
    0, 27, 20, 1, (byte) ((word) filters_event / 256), (byte) ((word)
    filters_event & 255), 0, 10, 0, 0, 0, 0, 0, 'f', 'i', 'l', 't', 'e',
    'r', 's', 0, 'F', 'i', 'l', 't', 'e', 'r', 's', 0,
    /*  <TD ALIGN=RIGHT><FONT SIZE=-1>                                       */
    0, 32, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E',
    '=', 45, '1', '>', 10,
    /*  !--ACTION server  LABEL="Ser ... ENT=server_event TYPE=PLAIN         */
    0, 25, 20, 1, (byte) ((word) server_event / 256), (byte) ((word)
    server_event & 255), 0, 11, 0, 0, 0, 0, 0, 's', 'e', 'r', 'v', 'e',
    'r', 0, 'S', 'e', 'r', 'v', 'e', 'r', 0,
    /*  !--ACTION aliases  LABEL="Al ... NT=aliases_event TYPE=PLAIN         */
    0, 27, 20, 1, (byte) ((word) aliases_event / 256), (byte) ((word)
    aliases_event & 255), 0, 12, 0, 0, 0, 0, 0, 'a', 'l', 'i', 'a', 's',
    'e', 's', 0, 'A', 'l', 'i', 'a', 's', 'e', 's', 0,
    /*  !--ACTION vhosts  LABEL="Vho ... ENT=vhosts_event TYPE=PLAIN         */
    0, 25, 20, 1, (byte) ((word) vhosts_event / 256), (byte) ((word)
    vhosts_event & 255), 0, 13, 0, 0, 0, 0, 0, 'v', 'h', 'o', 's', 't',
    's', 0, 'V', 'h', 'o', 's', 't', 's', 0,
    /*  !--ACTION cgi  LABEL="CGI" EVENT=cgi_event TYPE=PLAIN                */
    0, 19, 20, 1, (byte) ((word) cgi_event / 256), (byte) ((word)
    cgi_event & 255), 0, 14, 0, 0, 0, 0, 0, 'c', 'g', 'i', 0, 'C', 'G',
    'I', 0,
    /*  !--ACTION security  LABEL="S ... T=security_event TYPE=PLAIN         */
    0, 29, 20, 1, (byte) ((word) security_event / 256), (byte) ((word)
    security_event & 255), 0, 15, 0, 0, 0, 0, 0, 's', 'e', 'c', 'u',
    'r', 'i', 't', 'y', 0, 'S', 'e', 'c', 'u', 'r', 'i', 't', 'y', 0,
    /*  !--ACTION logging  LABEL="Lo ... NT=logging_event TYPE=PLAIN         */
    0, 27, 20, 1, (byte) ((word) logging_event / 256), (byte) ((word)
    logging_event & 255), 0, 16, 0, 0, 0, 0, 0, 'l', 'o', 'g', 'g', 'i',
    'n', 'g', 0, 'L', 'o', 'g', 'g', 'i', 'n', 'g', 0,
    /*  <EM>FTP</EM>                                                         */
    0, 14, 0, '<', 'E', 'M', '>', 'F', 'T', 'P', '<', '/', 'E', 'M',
    '>', 10,
    /*  !--ACTION mime  LABEL="MIME" EVENT=mimes_event TYPE=PLAIN            */
    0, 21, 20, 1, (byte) ((word) mimes_event / 256), (byte) ((word)
    mimes_event & 255), 0, 17, 0, 0, 0, 0, 0, 'm', 'i', 'm', 'e', 0,
    'M', 'I', 'M', 'E', 0,
    /*  </FONT></TABLE><HR>                                                  */
    0, 21, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', '/', 'T', 'A',
    'B', 'L', 'E', '>', '<', 'H', 'R', '>', 10,
    /*  <TABLE WIDTH=100%>                                                   */
    0, 20, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 39, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', '>', 10,
    /*  !--FIELD TEXTUAL f275 NAME=L ... le FTP server?&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '7', '5', 0, 'E', 'n',
    'a', 'b', 'l', 'e', 32, 'F', 'T', 'P', 32, 's', 'e', 'r', 'v', 'e',
    'r', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 34, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I',
    'G', 'N', '=', 'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=',
    '"', '8', '0', '%', '"', '>', 10,
    /*  !--FIELD BOOLEAN f276 NAME=enabled TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '2', '7', '6', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f277 NAME=L ... oot directory:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '2', '7', '7', 0, 'F', 'T',
    'P', 32, 'r', 'o', 'o', 't', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o',
    'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTUAL f278 NAME=r ... 40 MAX=100 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'd', 'f', '2', '7', '8', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f279 NAME=L ... P connections:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '2', '7', '9', 0, 'P', 'o',
    'r', 't', 32, 'f', 'o', 'r', 32, 'F', 'T', 'P', 32, 'c', 'o', 'n',
    'n', 'e', 'c', 't', 'i', 'o', 'n', 's', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD NUMERIC f280 NAME=p ... MMA=0 SIZE=5 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '2', '8', '0',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f281 NAME=L ... r connections:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '2', '8', '1', 0, 'T', 'i',
    'm', 'e', 'o', 'u', 't', 32, 'f', 'o', 'r', 32, 'c', 'o', 'n', 'n',
    'e', 'c', 't', 'i', 'o', 'n', 's', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD NUMERIC f282 NAME=t ... MMA=0 SIZE=6 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '2', '8', '2',
    0, 0,
    /*  seconds                                                              */
    0, 9, 0, 's', 'e', 'c', 'o', 'n', 'd', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f283 NAME=L ... m connections:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '2', '8', '3', 0, 'M', 'a',
    'x', 'i', 'm', 'u', 'm', 32, 'c', 'o', 'n', 'n', 'e', 'c', 't', 'i',
    'o', 'n', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD NUMERIC f284 NAME=l ... MMA=0 SIZE=6 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 1, 0, 'f', '2', '8', '4',
    0, 0,
    /*  if any                                                               */
    0, 8, 0, 'i', 'f', 32, 'a', 'n', 'y', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f285 NAME=L ... guration file:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '2', '8', '5', 0, 'U', 's',
    'e', 'r', 32, 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't', 'i',
    'o', 'n', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTUAL f286 NAME=u ... =40 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '2', '8', '6', 0, 0,
    /*  !--ACTION define_users  LABE ... ine_users_event TYPE=BUTTON         */
    0, 34, 20, 0, (byte) ((word) define_users_event / 256), (byte)
    ((word) define_users_event & 255), 0, 18, 0, 0, 0, 0, 0, 'd', 'e',
    'f', 'i', 'n', 'e', '_', 'u', 's', 'e', 'r', 's', 0, 'D', 'e', 'f',
    'i', 'n', 'e', '.', '.', '.', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f287 NAME=L ... y access file:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '2', '8', '7', 0, 'D', 'i',
    'r', 'e', 'c', 't', 'o', 'r', 'y', 32, 'a', 'c', 'c', 'e', 's', 's',
    32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTUAL f288 NAME=d ... =40 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '2', '8', '8', 0, 0,
    /*  !--ACTION define_dirs  LABEL ... fine_dirs_event TYPE=BUTTON         */
    0, 33, 20, 0, (byte) ((word) define_dirs_event / 256), (byte)
    ((word) define_dirs_event & 255), 0, 19, 0, 0, 0, 0, 0, 'd', 'e',
    'f', 'i', 'n', 'e', '_', 'd', 'i', 'r', 's', 0, 'D', 'e', 'f', 'i',
    'n', 'e', '.', '.', '.', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f289 NAME=L ... lcome message:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '2', '8', '9', 0, 'W', 'e',
    'l', 'c', 'o', 'm', 'e', 32, 'm', 'e', 's', 's', 'a', 'g', 'e', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTBOX f290 NAME=w ... 40 MAX=240 UPPER=0 VALUE=""         */
    0, 14, 14, 0, 1, 1, '(', 0, 0, 240, 'f', '2', '9', '0', 0, 0,
    /*  text or @filename                                                    */
    0, 19, 0, 't', 'e', 'x', 't', 32, 'o', 'r', 32, '@', 'f', 'i', 'l',
    'e', 'n', 'a', 'm', 'e', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f291 NAME=L ... Login message:&nbsp;&nbsp;"         */
    0, 40, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '2', '9', '1', 0, 'L', 'o',
    'g', 'i', 'n', 32, 'm', 'e', 's', 's', 'a', 'g', 'e', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTBOX f292 NAME=l ... 40 MAX=240 UPPER=0 VALUE=""         */
    0, 14, 14, 0, 1, 1, '(', 0, 0, 240, 'f', '2', '9', '2', 0, 0,
    /*  text or @filename                                                    */
    0, 4, 1, 0, 9, 'E',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f293 NAME=L ... n-off message:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '2', '9', '3', 0, 'S', 'i',
    'g', 'n', 45, 'o', 'f', 'f', 32, 'm', 'e', 's', 's', 'a', 'g', 'e',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTBOX f294 NAME=s ... 40 MAX=240 UPPER=0 VALUE=""         */
    0, 14, 14, 0, 1, 1, '(', 0, 0, 240, 'f', '2', '9', '4', 0, 0,
    /*  text or @filename                                                    */
    0, 4, 1, 0, 9, 'E',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f295 NAME=L ... ist sort order&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '2', '9', '5', 0, 'D', 'i',
    'r', 'e', 'c', 't', 'o', 'r', 'y', 32, 'l', 'i', 's', 't', 32, 's',
    'o', 'r', 't', 32, 'o', 'r', 'd', 'e', 'r', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTUAL f296 NAME=d ... ZE=5 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '2', '9', '6', 0, 0,
    /*  n=name x=ext t=time s=size NXTS=invert                               */
    0, 40, 0, 'n', '=', 'n', 'a', 'm', 'e', 32, 'x', '=', 'e', 'x', 't',
    32, 't', '=', 't', 'i', 'm', 'e', 32, 's', '=', 's', 'i', 'z', 'e',
    32, 'N', 'X', 'T', 'S', '=', 'i', 'n', 'v', 'e', 'r', 't', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f297 NAME=L ... ous passwords?&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '2', '9', '7', 0, 'C', 'h',
    'e', 'c', 'k', 32, 'a', 'n', 'o', 'n', 'y', 'm', 'o', 'u', 's', 32,
    'p', 'a', 's', 's', 'w', 'o', 'r', 'd', 's', '?', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD BOOLEAN f298 NAME=e ... k TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '2', '9', '8', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f299 NAME=L ...  HTTP aliases?&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '2', '9', '9', 0, 'S', 'h',
    'a', 'r', 'e', 32, 'H', 'T', 'T', 'P', 32, 'a', 'l', 'i', 'a', 's',
    'e', 's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD BOOLEAN f300 NAME=h ... s TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '0', '0', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--ACTION ftp_aliases  LABEL ... e_aliases_event TYPE=BUTTON         */
    0, 45, 20, 0, (byte) ((word) define_aliases_event / 256), (byte)
    ((word) define_aliases_event & 255), 0, 20, 0, 0, 0, 0, 0, 'f', 't',
    'p', '_', 'a', 'l', 'i', 'a', 's', 'e', 's', 0, 'D', 'e', 'f', 'i',
    'n', 'e', 32, 'F', 'T', 'P', 32, 'a', 'l', 'i', 'a', 's', 'e', 's',
    '.', '.', '.', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f301 NAME=L ... ive passwords?&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '3', '0', '1', 0, 'C', 'a',
    's', 'e', 45, 's', 'e', 'n', 's', 'i', 't', 'i', 'v', 'e', 32, 'p',
    'a', 's', 's', 'w', 'o', 'r', 'd', 's', '?', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD BOOLEAN f302 NAME=p ... e TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '0', '2', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f303 NAME=L ... ft quota (Mb):&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '3', '0', '3', 0, 'D', 'e',
    'f', 'a', 'u', 'l', 't', 32, 's', 'o', 'f', 't', 32, 'q', 'u', 'o',
    't', 'a', 32, '(', 'M', 'b', ')', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTUAL f304 NAME=s ... E=8 MAX=10 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 8, 0, 10, 'f', '3', '0', '4', 0, 0,
    /*  !--FIELD TEXTUAL f305 NAME=L ... rd quota (Mb):&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '3', '0', '5', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'h', 'a', 'r',
    'd', 32, 'q', 'u', 'o', 't', 'a', 32, '(', 'M', 'b', ')', ':', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD TEXTUAL f306 NAME=h ... E=8 MAX=10 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 8, 0, 10, 'f', '3', '0', '6', 0, 0,
    /*  <TR><TD></TD><TD>                                                    */
    0, 19, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', '>', 10,
    /*  <P>                                                                  */
    0, 5, 0, '<', 'P', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f307 NAME=L ...  all accesses?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '3', '0', '7', 0, 'L', 'o',
    'g', 32, 'a', 'l', 'l', 32, 'a', 'c', 'c', 'e', 's', 's', 'e', 's',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD BOOLEAN f308 NAME=a ... d TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '0', '8', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--FIELD TEXTUAL f309 NAME=L ... &nbsp;to file:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '3', '0', '9', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 't', 'o', 32, 'f',
    'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  !--FIELD TEXTUAL f310 NAME=a ... =20 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 'P', 'f', '3', '1', '0', 0, 0,
    /*  !--FIELD TEXTUAL f311 NAME=L ... p;&nbsp;cycle:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '1', '1', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'c', 'y', 'c',
    'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  !--FIELD SELECT f312 NAME=al ... kly" 4="Monthly" 5="Manual"         */
    0, 58, 16, 0, 1, 1, 5, 'f', '3', '1', '2', 0, '0', 0, 'A', 't', 32,
    's', 't', 'a', 'r', 't', 'u', 'p', 0, 'H', 'o', 'u', 'r', 'l', 'y',
    0, 'D', 'a', 'i', 'l', 'y', 0, 'W', 'e', 'e', 'k', 'l', 'y', 0, 'M',
    'o', 'n', 't', 'h', 'l', 'y', 0, 'M', 'a', 'n', 'u', 'a', 'l', 0,
    /*  !--FIELD TEXTUAL f313 NAME=L ... l clients too?&nbsp;&nbsp;"         */
    0, 56, 10, 6, 1, 0, 0, '*', 0, '*', 'f', '3', '1', '3', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'l', 'o', 'c',
    'a', 'l', 32, 'c', 'l', 'i', 'e', 'n', 't', 's', 32, 't', 'o', 'o',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD BOOLEAN f314 NAME=a ... l TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '1', '4', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f315 NAME=L ... og all errors?&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '3', '1', '5', 0, 'L', 'o',
    'g', 32, 'a', 'l', 'l', 32, 'e', 'r', 'r', 'o', 'r', 's', '?', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD BOOLEAN f316 NAME=e ... d TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '1', '6', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--FIELD TEXTUAL f317 NAME=L ... &nbsp;to file:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '3', '1', '7', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 't', 'o', 32, 'f',
    'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  !--FIELD TEXTUAL f318 NAME=e ... =20 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 'P', 'f', '3', '1', '8', 0, 0,
    /*  !--FIELD TEXTUAL f319 NAME=L ... p;&nbsp;cycle:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '1', '9', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'c', 'y', 'c',
    'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  !--FIELD SELECT f320 NAME=el ... kly" 4="Monthly" 5="Manual"         */
    0, 58, 16, 0, 1, 1, 5, 'f', '3', '2', '0', 0, '0', 0, 'A', 't', 32,
    's', 't', 'a', 'r', 't', 'u', 'p', 0, 'H', 'o', 'u', 'r', 'l', 'y',
    0, 'D', 'a', 'i', 'l', 'y', 0, 'W', 'e', 'e', 'k', 'l', 'y', 0, 'M',
    'o', 'n', 't', 'h', 'l', 'y', 0, 'M', 'a', 'n', 'u', 'a', 'l', 0,
    /*  !--FIELD TEXTUAL f321 NAME=L ... l clients too?&nbsp;&nbsp;"         */
    0, 56, 10, 6, 1, 0, 0, '*', 0, '*', 'f', '3', '2', '1', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'l', 'o', 'c',
    'a', 'l', 32, 'c', 'l', 'i', 'e', 'n', 't', 's', 32, 't', 'o', 'o',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD BOOLEAN f322 NAME=e ... l TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '2', '2', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  <TR><TD></TD><TD>                                                    */
    0, 4, 1, 0, 12, 'X',
    /*  <P>                                                                  */
    0, 4, 1, 0, 12, 'm',
    /*  <B>Advanced options</B>                                              */
    0, 25, 0, '<', 'B', '>', 'A', 'd', 'v', 'a', 'n', 'c', 'e', 'd', 32,
    'o', 'p', 't', 'i', 'o', 'n', 's', '<', '/', 'B', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f323 NAME=L ...  address mask:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '3', '2', '3', 0, 'I', 'P',
    32, 'a', 'd', 'd', 'r', 'e', 's', 's', 32, 'm', 'a', 's', 'k', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD TEXTUAL f324 NAME=w ... =40 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '3', '2', '4', 0, 0,
    /*  - eg. 111.222.333.*                                                  */
    0, 21, 0, 45, 32, 'e', 'g', '.', 32, '1', '1', '1', '.', '2', '2',
    '2', '.', '3', '3', '3', '.', '*', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f325 NAME=L ... nnection port:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '3', '2', '5', 0, 'D', 'a',
    't', 'a', 32, 'c', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', 32,
    'p', 'o', 'r', 't', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD NUMERIC f326 NAME=d ... MMA=0 SIZE=5 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '3', '2', '6',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 5, 252,
    /*  !--FIELD TEXTUAL f327 NAME=L ... ve IP address:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '3', '2', '7', 0, 'P', 'a',
    's', 's', 'i', 'v', 'e', 32, 'I', 'P', 32, 'a', 'd', 'd', 'r', 'e',
    's', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 'S',
    /*  !--FIELD SELECT f328 NAME=ip ... pe=dynamic 0="No selection"         */
    0, 25, 16, 0, 1, 1, 0, 'f', '3', '2', '8', 0, '0', 0, 'N', 'o', 32,
    's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 138,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 165,
    /*  </FORM>                                                              */
    0, 9, 0, '<', '/', 'F', 'O', 'R', 'M', '>', 10,
    /*  <SCRIPT>                                                             */
    0, 10, 0, '<', 'S', 'C', 'R', 'I', 'P', 'T', '>', 10,
    /*  function submit(arguments) { ... forms[0].#(_focus).focus();}        */
    0, 202, 0, 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', 32, 's', 'u',
    'b', 'm', 'i', 't', '(', 'a', 'r', 'g', 'u', 'm', 'e', 'n', 't',
    's', ')', 32, '{', 10, 10, 'd', 'o', 'c', 'u', 'm', 'e', 'n', 't',
    '.', 'f', 'o', 'r', 'm', 's', '[', '0', ']', '.', 'j', 's', 'a',
    'c', 't', 'i', 'o', 'n', '.', 'v', 'a', 'l', 'u', 'e', 32, '=', 32,
    'a', 'r', 'g', 'u', 'm', 'e', 'n', 't', 's', ';', 10, 10, 'd', 'o',
    'c', 'u', 'm', 'e', 'n', 't', '.', 'f', 'o', 'r', 'm', 's', '[',
    '0', ']', '.', 's', 'u', 'b', 'm', 'i', 't', '(', ')', ';', 10, 10,
    '}', 10, 10, 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', 32, 'f', 'o',
    'c', 'u', 's', '(', ')', 32, '{', 10, 10, 'i', 'f', 32, '(', '"',
    '#', '(', '_', 'f', 'o', 'c', 'u', 's', ')', '"', 32, '!', '=', 32,
    '"', 'j', 's', 'a', 'c', 't', 'i', 'o', 'n', '"', ')', 10, 10, 'd',
    'o', 'c', 'u', 'm', 'e', 'n', 't', '.', 'f', 'o', 'r', 'm', 's',
    '[', '0', ']', '.', '#', '(', '_', 'f', 'o', 'c', 'u', 's', ')',
    '.', 'f', 'o', 'c', 'u', 's', '(', ')', ';', 10, 10, '}', 10,
    /*  </SCRIPT>                                                            */
    0, 11, 0, '<', '/', 'S', 'C', 'R', 'I', 'P', 'T', '>', 10,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  <TABLE WIDTH=100%><TR>                                               */
    0, 24, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', '<', 'T', 'R', '>', 10,
    /*  <TD><IMG SRC="/admin/im0096c.gif"                                    */
    0, 35, 0, '<', 'T', 'D', '>', '<', 'I', 'M', 'G', 32, 'S', 'R', 'C',
    '=', '"', '/', 'a', 'd', 'm', 'i', 'n', '/', 'i', 'm', '0', '0',
    '9', '6', 'c', '.', 'g', 'i', 'f', '"', 10,
    /*  WIDTH=96 HEIGHT=36>                                                  */
    0, 21, 0, 'W', 'I', 'D', 'T', 'H', '=', '9', '6', 32, 'H', 'E', 'I',
    'G', 'H', 'T', '=', '3', '6', '>', 10,
    /*  <TD ALIGN=CENTER><FONT SIZE= ... 9 1996-99 iMatix Corporation        */
    0, 75, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', 45, '1', '>', 'C', 'o', 'p', 'y', 'r', 'i', 'g', 'h', 't',
    32, '&', '#', '1', '6', '9', 32, '1', '9', '9', '6', 45, '9', '9',
    32, 'i', 'M', 'a', 't', 'i', 'x', 32, 'C', 'o', 'r', 'p', 'o', 'r',
    'a', 't', 'i', 'o', 'n', 10,
    /*  <BR>Powered by iMatix Studio 1.0                                     */
    0, 34, 0, '<', 'B', 'R', '>', 'P', 'o', 'w', 'e', 'r', 'e', 'd', 32,
    'b', 'y', 32, 'i', 'M', 'a', 't', 'i', 'x', 32, 'S', 't', 'u', 'd',
    'i', 'o', 32, '1', '.', '0', 10,
    /*  <TD ALIGN=RIGHT><FONT SIZE=-1>#(date) #(time)                        */
    0, 47, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E',
    '=', 45, '1', '>', '#', '(', 'd', 'a', 't', 'e', ')', 32, '#', '(',
    't', 'i', 'm', 'e', ')', 10,
    /*  <BR>#(product) v2.4d7                                                */
    0, 23, 0, '<', 'B', 'R', '>', '#', '(', 'p', 'r', 'o', 'd', 'u',
    'c', 't', ')', 32, 'v', '2', '.', '4', 'd', '7', 10,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 165,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm16_fields [] = {
    { 0, 1031, 80 },                    /*  message_to_user                 */
    { 82, 1573, 30 },                   /*  l_enabled                       */
    { 114, 1655, 1 },                   /*  enabled                         */
    { 117, 1694, 31 },                  /*  l_rootdir                       */
    { 150, 1747, 100 },                 /*  rootdir                         */
    { 252, 1775, 37 },                  /*  l_port                          */
    { 291, 1834, 5 },                   /*  port                            */
    { 298, 1867, 36 },                  /*  l_timeout                       */
    { 336, 1925, 6 },                   /*  timeout                         */
    { 344, 1969, 32 },                  /*  l_limit                         */
    { 378, 2023, 6 },                   /*  limit                           */
    { 386, 2066, 36 },                  /*  l_user_file                     */
    { 424, 2124, 80 },                  /*  user_file                       */
    { 506, 2188, 34 },                  /*  l_directory_file                */
    { 542, 2244, 80 },                  /*  directory_file                  */
    { 624, 2307, 28 },                  /*  l_welcome                       */
    { 654, 2357, 240 },                 /*  welcome                         */
    { 896, 2406, 26 },                  /*  l_login                         */
    { 924, 2454, 240 },                 /*  login                           */
    { 1166, 2488, 29 },                 /*  l_signoff                       */
    { 1197, 2539, 240 },                /*  signoff                         */
    { 1439, 2573, 37 },                 /*  l_dirsort                       */
    { 1478, 2632, 5 },                  /*  dirsort                         */
    { 1485, 2702, 38 },                 /*  l_email_check                   */
    { 1525, 2762, 1 },                  /*  email_check                     */
    { 1528, 2793, 31 },                 /*  l_http_aliases                  */
    { 1561, 2846, 1 },                  /*  http_aliases                    */
    { 1564, 2924, 37 },                 /*  l_password_case                 */
    { 1603, 2983, 1 },                  /*  password_case                   */
    { 1606, 3014, 36 },                 /*  l_soft_quota                    */
    { 1644, 3072, 10 },                 /*  soft_quota                      */
    { 1656, 3088, 40 },                 /*  l_hard_quota                    */
    { 1698, 3144, 10 },                 /*  hard_quota                      */
    { 1710, 3200, 29 },                 /*  l_alog_enabled                  */
    { 1741, 3251, 1 },                  /*  alog_enabled                    */
    { 1744, 3270, 32 },                 /*  l_alog_filename                 */
    { 1778, 3318, 80 },                 /*  alog_filename                   */
    { 1860, 3334, 30 },                 /*  l_alog_cycle                    */
    { 1892, 3380, 3 },                  /*  alog_cycle                      */
    { 1897, 3440, 42 },                 /*  l_alog_local                    */
    { 1941, 3498, 1 },                  /*  alog_local                      */
    { 1944, 3529, 27 },                 /*  l_elog_enabled                  */
    { 1973, 3578, 1 },                  /*  elog_enabled                    */
    { 1976, 3597, 32 },                 /*  l_elog_filename                 */
    { 2010, 3645, 80 },                 /*  elog_filename                   */
    { 2092, 3661, 30 },                 /*  l_elog_cycle                    */
    { 2124, 3707, 3 },                  /*  elog_cycle                      */
    { 2129, 3767, 42 },                 /*  l_elog_local                    */
    { 2173, 3825, 1 },                  /*  elog_local                      */
    { 2176, 3895, 28 },                 /*  l_webmask                       */
    { 2206, 3945, 80 },                 /*  webmask                         */
    { 2288, 3996, 33 },                 /*  l_data_port                     */
    { 2323, 4051, 5 },                  /*  data_port                       */
    { 2330, 4084, 31 },                 /*  l_ipaddress                     */
    { 2363, 4137, 3 },                  /*  ipaddress                       */
    { 2368, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   l_enabled_a          ;
    char   l_enabled            [30 + 1];
    byte   enabled_a            ;
    char   enabled              [1 + 1];
    byte   l_rootdir_a          ;
    char   l_rootdir            [31 + 1];
    byte   rootdir_a            ;
    char   rootdir              [100 + 1];
    byte   l_port_a             ;
    char   l_port               [37 + 1];
    byte   port_a               ;
    char   port                 [5 + 1];
    byte   l_timeout_a          ;
    char   l_timeout            [36 + 1];
    byte   timeout_a            ;
    char   timeout              [6 + 1];
    byte   l_limit_a            ;
    char   l_limit              [32 + 1];
    byte   limit_a              ;
    char   limit                [6 + 1];
    byte   l_user_file_a        ;
    char   l_user_file          [36 + 1];
    byte   user_file_a          ;
    char   user_file            [80 + 1];
    byte   l_directory_file_a   ;
    char   l_directory_file     [34 + 1];
    byte   directory_file_a     ;
    char   directory_file       [80 + 1];
    byte   l_welcome_a          ;
    char   l_welcome            [28 + 1];
    byte   welcome_a            ;
    char   welcome              [240 + 1];
    byte   l_login_a            ;
    char   l_login              [26 + 1];
    byte   login_a              ;
    char   login                [240 + 1];
    byte   l_signoff_a          ;
    char   l_signoff            [29 + 1];
    byte   signoff_a            ;
    char   signoff              [240 + 1];
    byte   l_dirsort_a          ;
    char   l_dirsort            [37 + 1];
    byte   dirsort_a            ;
    char   dirsort              [5 + 1];
    byte   l_email_check_a      ;
    char   l_email_check        [38 + 1];
    byte   email_check_a        ;
    char   email_check          [1 + 1];
    byte   l_http_aliases_a     ;
    char   l_http_aliases       [31 + 1];
    byte   http_aliases_a       ;
    char   http_aliases         [1 + 1];
    byte   l_password_case_a    ;
    char   l_password_case      [37 + 1];
    byte   password_case_a      ;
    char   password_case        [1 + 1];
    byte   l_soft_quota_a       ;
    char   l_soft_quota         [36 + 1];
    byte   soft_quota_a         ;
    char   soft_quota           [10 + 1];
    byte   l_hard_quota_a       ;
    char   l_hard_quota         [40 + 1];
    byte   hard_quota_a         ;
    char   hard_quota           [10 + 1];
    byte   l_alog_enabled_a     ;
    char   l_alog_enabled       [29 + 1];
    byte   alog_enabled_a       ;
    char   alog_enabled         [1 + 1];
    byte   l_alog_filename_a    ;
    char   l_alog_filename      [32 + 1];
    byte   alog_filename_a      ;
    char   alog_filename        [80 + 1];
    byte   l_alog_cycle_a       ;
    char   l_alog_cycle         [30 + 1];
    byte   alog_cycle_a         ;
    char   alog_cycle           [3 + 1];
    byte   l_alog_local_a       ;
    char   l_alog_local         [42 + 1];
    byte   alog_local_a         ;
    char   alog_local           [1 + 1];
    byte   l_elog_enabled_a     ;
    char   l_elog_enabled       [27 + 1];
    byte   elog_enabled_a       ;
    char   elog_enabled         [1 + 1];
    byte   l_elog_filename_a    ;
    char   l_elog_filename      [32 + 1];
    byte   elog_filename_a      ;
    char   elog_filename        [80 + 1];
    byte   l_elog_cycle_a       ;
    char   l_elog_cycle         [30 + 1];
    byte   elog_cycle_a         ;
    char   elog_cycle           [3 + 1];
    byte   l_elog_local_a       ;
    char   l_elog_local         [42 + 1];
    byte   elog_local_a         ;
    char   elog_local           [1 + 1];
    byte   l_webmask_a          ;
    char   l_webmask            [28 + 1];
    byte   webmask_a            ;
    char   webmask              [80 + 1];
    byte   l_data_port_a        ;
    char   l_data_port          [33 + 1];
    byte   data_port_a          ;
    char   data_port            [5 + 1];
    byte   l_ipaddress_a        ;
    char   l_ipaddress          [31 + 1];
    byte   ipaddress_a          ;
    char   ipaddress            [3 + 1];
    byte   back_a;
    byte   save_a;
    byte   default_a;
    byte   undo_a;
    byte   console_a;
    byte   halt_a;
    byte   restart_a;
    byte   exit_a;
    byte   errors_a;
    byte   wsx_a;
    byte   filters_a;
    byte   server_a;
    byte   aliases_a;
    byte   vhosts_a;
    byte   cgi_a;
    byte   security_a;
    byte   logging_a;
    byte   mime_a;
    byte   define_users_a;
    byte   define_dirs_a;
    byte   ftp_aliases_a;
    } XIADM16_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm16 = {
    xiadm16_blocks,
    xiadm16_fields,
    189,                                /*  Number of blocks in form        */
    55,                                 /*  Number of fields in form        */
    21,                                 /*  Number of actions in form       */
    2368,                               /*  Size of fields                  */
    "xiadm16",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
