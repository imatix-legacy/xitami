/*---------------------------------------------------------------------------
 *  xiadm03.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM03__
#define __FORM_XIADM03__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM03_MESSAGE_TO_USER             0
#define XIADM03_MAIN_CONFIG                 1
#define XIADM03_ON_UNIX                     2
#define XIADM03_ON_WINDOWS_32               3
#define XIADM03_L_WEBPAGES                  4
#define XIADM03_WEBPAGES                    5
#define XIADM03_L_CGI_BIN                   6
#define XIADM03_CGI_BIN                     7
#define XIADM03_L_CGI_URL                   8
#define XIADM03_CGI_URL                     9
#define XIADM03_L_DEBUG                     10
#define XIADM03_DEBUG                       11
#define XIADM03_L_REFRESH_RATE              12
#define XIADM03_REFRESH_RATE                13
#define XIADM03_L_LIMIT                     14
#define XIADM03_LIMIT                       15
#define XIADM03_L_BACKGROUND                16
#define XIADM03_BACKGROUND                  17
#define XIADM03_L_AUTOSTART                 18
#define XIADM03_AUTOSTART                   19
#define XIADM03_L_RECOVER                   20
#define XIADM03_RECOVER                     21
#define XIADM03_L_DEFAULT1                  22
#define XIADM03_DEFAULT1                    23
#define XIADM03_L_DEFAULT2                  24
#define XIADM03_DEFAULT2                    25
#define XIADM03_DEFAULT3                    26
#define XIADM03_DEFAULT4                    27
#define XIADM03_L_CACHE_DEFAULTS            28
#define XIADM03_CACHE_DEFAULTS              29
#define XIADM03_L_KEEP_ALIVE                30
#define XIADM03_KEEP_ALIVE                  31
#define XIADM03_L_KEEP_ALIVE_MAX            32
#define XIADM03_KEEP_ALIVE_MAX              33
#define XIADM03_L_TIMEOUT                   34
#define XIADM03_TIMEOUT                     35
#define XIADM03_L_DIRSORT                   36
#define XIADM03_DIRSORT                     37
#define XIADM03_L_ADVERTIZE                 38
#define XIADM03_ADVERTIZE                   39
#define XIADM03_L_PRIORITY                  40
#define XIADM03_PRIORITY                    41
#define XIADM03_L_PORTBASE                  42
#define XIADM03_PORTBASE                    43
#define XIADM03_L_PORTBASE1                 44
#define XIADM03_PORTBASE1                   45
#define XIADM03_L_BASE_HOST                 46
#define XIADM03_BASE_HOST                   47
#define XIADM03_L_IPADDRESS                 48
#define XIADM03_IPADDRESS                   49
#define XIADM03_L_TEMP_DIR                  50
#define XIADM03_TEMP_DIR                    51
#define XIADM03_L_DEBUG_DIR                 52
#define XIADM03_DEBUG_DIR                   53
#define XIADM03_L_TRANSLATE                 54
#define XIADM03_TRANSLATE                   55
#define XIADM03_L_HOSTNAME                  56
#define XIADM03_HOSTNAME                    57
#define XIADM03_L_TEST_URI                  58
#define XIADM03_TEST_URI                    59
#define XIADM03_L_MAPPED_URI                60
#define XIADM03_MAPPED_URI                  61

/*  This table contains each block in the form                               */

static byte xiadm03_blocks [] = {
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ...  - Server Properties </FONT>        */
    0, 70, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'S', 'e', 'r', 'v', 'e', 'r', 32, 'P', 'r', 'o',
    'p', 'e', 'r', 't', 'i', 'e', 's', 32, '<', '/', 'F', 'O', 'N', 'T',
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
    /*  <EM>Server</EM>                                                      */
    0, 17, 0, '<', 'E', 'M', '>', 'S', 'e', 'r', 'v', 'e', 'r', '<',
    '/', 'E', 'M', '>', 10,
    /*  !--ACTION aliases  LABEL="Al ... NT=aliases_event TYPE=PLAIN         */
    0, 27, 20, 1, (byte) ((word) aliases_event / 256), (byte) ((word)
    aliases_event & 255), 0, 11, 0, 0, 0, 0, 0, 'a', 'l', 'i', 'a', 's',
    'e', 's', 0, 'A', 'l', 'i', 'a', 's', 'e', 's', 0,
    /*  !--ACTION vhosts  LABEL="Vho ... ENT=vhosts_event TYPE=PLAIN         */
    0, 25, 20, 1, (byte) ((word) vhosts_event / 256), (byte) ((word)
    vhosts_event & 255), 0, 12, 0, 0, 0, 0, 0, 'v', 'h', 'o', 's', 't',
    's', 0, 'V', 'h', 'o', 's', 't', 's', 0,
    /*  !--ACTION cgi  LABEL="CGI" EVENT=cgi_event TYPE=PLAIN                */
    0, 19, 20, 1, (byte) ((word) cgi_event / 256), (byte) ((word)
    cgi_event & 255), 0, 13, 0, 0, 0, 0, 0, 'c', 'g', 'i', 0, 'C', 'G',
    'I', 0,
    /*  !--ACTION security  LABEL="S ... T=security_event TYPE=PLAIN         */
    0, 29, 20, 1, (byte) ((word) security_event / 256), (byte) ((word)
    security_event & 255), 0, 14, 0, 0, 0, 0, 0, 's', 'e', 'c', 'u',
    'r', 'i', 't', 'y', 0, 'S', 'e', 'c', 'u', 'r', 'i', 't', 'y', 0,
    /*  !--ACTION logging  LABEL="Lo ... NT=logging_event TYPE=PLAIN         */
    0, 27, 20, 1, (byte) ((word) logging_event / 256), (byte) ((word)
    logging_event & 255), 0, 15, 0, 0, 0, 0, 0, 'l', 'o', 'g', 'g', 'i',
    'n', 'g', 0, 'L', 'o', 'g', 'g', 'i', 'n', 'g', 0,
    /*  !--ACTION ftp  LABEL="FTP" EVENT=ftp_event TYPE=PLAIN                */
    0, 19, 20, 1, (byte) ((word) ftp_event / 256), (byte) ((word)
    ftp_event & 255), 0, 16, 0, 0, 0, 0, 0, 'f', 't', 'p', 0, 'F', 'T',
    'P', 0,
    /*  !--ACTION mime  LABEL="MIME" EVENT=mimes_event TYPE=PLAIN            */
    0, 21, 20, 1, (byte) ((word) mimes_event / 256), (byte) ((word)
    mimes_event & 255), 0, 17, 0, 0, 0, 0, 0, 'm', 'i', 'm', 'e', 0,
    'M', 'I', 'M', 'E', 0,
    /*  </FONT></TABLE><HR>                                                  */
    0, 21, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', '/', 'T', 'A',
    'B', 'L', 'E', '>', '<', 'H', 'R', '>', 10,
    /*  !--FIELD NUMERIC main_config SIZE=4 VALUE=1                          */
    0, 27, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'm', 'a', 'i', 'n',
    '_', 'c', 'o', 'n', 'f', 'i', 'g', 0, '1', 0,
    /*  !--FIELD NUMERIC on_unix SIZE=4 VALUE=1                              */
    0, 23, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'o', 'n', '_', 'u',
    'n', 'i', 'x', 0, '1', 0,
    /*  !--FIELD NUMERIC on_windows_32 SIZE=4 VALUE=1                        */
    0, 29, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'o', 'n', '_', 'w',
    'i', 'n', 'd', 'o', 'w', 's', '_', '3', '2', 0, '1', 0,
    /*  <TABLE WIDTH=100%>                                                   */
    0, 20, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 39, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', '>', 10,
    /*  !--FIELD TEXTUAL f8 NAME=L_w ... TML directory:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '8', 0, 'M', 'a', 'i', 'n',
    32, 'H', 'T', 'M', 'L', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r',
    'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 34, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I',
    'G', 'N', '=', 'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=',
    '"', '8', '0', '%', '"', '>', 10,
    /*  !--FIELD TEXTUAL f9 NAME=web ... 40 MAX=100 UPPER=0 VALUE=""         */
    0, 12, 10, 0, 1, 0, 0, '(', 0, 'd', 'f', '9', 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f10 NAME=L_ ... CGI directory:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '1', '0', 0, 'M', 'a', 'i',
    'n', 32, 'C', 'G', 'I', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r',
    'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f11 NAME=cg ... 40 MAX=100 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, '(', 0, 'd', 'f', '1', '1', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f12 NAME=L_ ... Ls start with:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '1', '2', 0, 'C', 'G', 'I',
    32, 'U', 'R', 'L', 's', 32, 's', 't', 'a', 'r', 't', 32, 'w', 'i',
    't', 'h', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f13 NAME=cg ... E=40 MAX=? UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, '(', 0, '(', 'f', '1', '3', 0, 0,
    /*  !--IF main_config                                                    */
    0, 5, 2, 0, 1, 0, 18,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f14 NAME=L_ ... in debug mode?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '1', '4', 0, 'R', 'u', 'n',
    32, 'i', 'n', 32, 'd', 'e', 'b', 'u', 'g', 32, 'm', 'o', 'd', 'e',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD BOOLEAN f15 NAME=debug TRUE=yes FALSE=no VALUE=0            */
    0, 16, 15, 0, 1, 'f', '1', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0,
    /*  - creates additional log files                                       */
    0, 32, 0, 45, 32, 'c', 'r', 'e', 'a', 't', 'e', 's', 32, 'a', 'd',
    'd', 'i', 't', 'i', 'o', 'n', 'a', 'l', 32, 'l', 'o', 'g', 32, 'f',
    'i', 'l', 'e', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f16 NAME=L_ ...  config every:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '1', '6', 0, 'R', 'e', 'f',
    'r', 'e', 's', 'h', 32, 'c', 'o', 'n', 'f', 'i', 'g', 32, 'e', 'v',
    'e', 'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD NUMERIC f17 NAME=re ... MMA=0 SIZE=8 MAX=? VALUE=""         */
    0, 18, 11, 0, 1, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 'f', '1', '7', 0, 0,
    /*  seconds                                                              */
    0, 9, 0, 's', 'e', 'c', 'o', 'n', 'd', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f18 NAME=L_ ... P connections:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '1', '8', 0, 'M', 'a', 'x',
    '.', 32, 'H', 'T', 'T', 'P', 32, 'c', 'o', 'n', 'n', 'e', 'c', 't',
    'i', 'o', 'n', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD NUMERIC f19 NAME=li ... MMA=0 SIZE=4 MAX=? VALUE=""         */
    0, 18, 11, 0, 1, 0, 4, 0, 4, 0, 0, 0, 0, 1, 0, 'f', '1', '9', 0, 0,
    /*  if any                                                               */
    0, 8, 0, 'i', 'f', 32, 'a', 'n', 'y', 10,
    /*  !--IF on_unix                                                        */
    0, 5, 2, 0, 2, 0, 5,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f20 NAME=L_ ... in background?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '0', 0, 'R', 'u', 'n',
    32, 'i', 'n', 32, 'b', 'a', 'c', 'k', 'g', 'r', 'o', 'u', 'n', 'd',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD BOOLEAN f21 NAME=ba ... d TRUE=yes FALSE=no VALUE=0         */
    0, 16, 15, 0, 1, 'f', '2', '1', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0,
    /*  !--IF on_windows_32                                                  */
    0, 5, 2, 0, 3, 0, 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f22 NAME=L_ ... P/IP is ready?&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, 39, 0, 39, 'f', '2', '2', 0, 'S', 't', 'a',
    'r', 't', 32, 'w', 'h', 'e', 'n', 32, 'T', 'C', 'P', '/', 'I', 'P',
    32, 'i', 's', 32, 'r', 'e', 'a', 'd', 'y', '?', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD BOOLEAN f23 NAME=autostart TRUE=yes FALSE=no VALUE=0        */
    0, 16, 15, 0, 1, 'f', '2', '3', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f24 NAME=L_ ...  from crashes?&nbsp;&nbsp;"         */
    0, 55, 10, 6, 1, 0, 0, '*', 0, '*', 'f', '2', '4', 0, 'R', 'e', 'c',
    'o', 'v', 'e', 'r', 32, 's', 'i', 'l', 'e', 'n', 't', 'l', 'y', 32,
    'f', 'r', 'o', 'm', 32, 'c', 'r', 'a', 's', 'h', 'e', 's', '?', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD BOOLEAN f25 NAME=recover TRUE=yes FALSE=no VALUE=0          */
    0, 16, 15, 0, 1, 'f', '2', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f26 NAME=L_ ... ult HTML page:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '6', 0, 'D', 'e', 'f',
    'a', 'u', 'l', 't', 32, 'H', 'T', 'M', 'L', 32, 'p', 'a', 'g', 'e',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f27 NAME=de ... =12 MAX=80 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 12, 0, 'P', 'f', '2', '7', 0, 0,
    /*  !--FIELD TEXTUAL f28 NAME=L_ ... sp;&nbsp;Then:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '2', '8', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'T', 'h', 'e', 'n',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD TEXTUAL f29 NAME=de ... =12 MAX=80 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 12, 0, 'P', 'f', '2', '9', 0, 0,
    /*  !--FIELD TEXTUAL f30 NAME=de ... =12 MAX=80 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 12, 0, 'P', 'f', '3', '0', 0, 0,
    /*  !--FIELD TEXTUAL f31 NAME=de ... =12 MAX=80 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 12, 0, 'P', 'f', '3', '1', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f32 NAME=L_ ... efaults pages?&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '3', '2', 0, 'C', 'a', 'c',
    'h', 'e', 32, 'd', 'e', 'f', 'a', 'u', 'l', 't', 's', 32, 'p', 'a',
    'g', 'e', 's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD BOOLEAN f33 NAME=ca ... s TRUE=yes FALSE=no VALUE=0         */
    0, 16, 15, 0, 1, 'f', '3', '3', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f34 NAME=L_ ... e connections?&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, ')', 0, ')', 'f', '3', '4', 0, 'A', 'l', 'l',
    'o', 'w', 32, 'K', 'e', 'e', 'p', 45, 'A', 'l', 'i', 'v', 'e', 32,
    'c', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', 's', '?', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD BOOLEAN f35 NAME=ke ... e TRUE=yes FALSE=no VALUE=0         */
    0, 16, 15, 0, 1, 'f', '3', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0,
    /*  !--FIELD TEXTUAL f36 NAME=L_ ... p;Allow up to:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '3', '6', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'A', 'l', 'l', 'o',
    'w', 32, 'u', 'p', 32, 't', 'o', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD NUMERIC f37 NAME=ke ... MMA=0 SIZE=4 MAX=? VALUE=""         */
    0, 18, 11, 0, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'f', '3', '7', 0, 0,
    /*  requests                                                             */
    0, 10, 0, 'r', 'e', 'q', 'u', 'e', 's', 't', 's', 10,
    /*  !--FIELD TEXTUAL f38 NAME=L_ ... p;Close after:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '3', '8', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'C', 'l', 'o', 's',
    'e', 32, 'a', 'f', 't', 'e', 'r', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD NUMERIC f39 NAME=ti ... MMA=0 SIZE=4 MAX=? VALUE=""         */
    0, 18, 11, 0, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'f', '3', '9', 0, 0,
    /*  seconds                                                              */
    0, 4, 1, 0, 8, 'N',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f40 NAME=L_ ... ist sort order&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '4', '0', 0, 'D', 'i', 'r',
    'e', 'c', 't', 'o', 'r', 'y', 32, 'l', 'i', 's', 't', 32, 's', 'o',
    'r', 't', 32, 'o', 'r', 'd', 'e', 'r', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f41 NAME=di ... ZE=5 MAX=? UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '4', '1', 0, 0,
    /*  n=name x=ext t=time s=size N,X,T,S=inverted                          */
    0, 45, 0, 'n', '=', 'n', 'a', 'm', 'e', 32, 'x', '=', 'e', 'x', 't',
    32, 't', '=', 't', 'i', 'm', 'e', 32, 's', '=', 's', 'i', 'z', 'e',
    32, 'N', ',', 'X', ',', 'T', ',', 'S', '=', 'i', 'n', 'v', 'e', 'r',
    't', 'e', 'd', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f42 NAME=L_ ... name in lists?&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '4', '2', 0, 'S', 'h', 'o',
    'w', 32, 's', 'e', 'r', 'v', 'e', 'r', 32, 'n', 'a', 'm', 'e', 32,
    'i', 'n', 32, 'l', 'i', 's', 't', 's', '?', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD BOOLEAN f43 NAME=advertize TRUE=yes FALSE=no VALUE=0        */
    0, 16, 15, 0, 1, 'f', '4', '3', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0,
    /*  !--IF main_config                                                    */
    0, 5, 2, 0, 1, 0, '3',
    /*  <TR><TD></TD><TD>                                                    */
    0, 19, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', '>', 10,
    /*  <B>Advanced options</B>                                              */
    0, 25, 0, '<', 'B', '>', 'A', 'd', 'v', 'a', 'n', 'c', 'e', 'd', 32,
    'o', 'p', 't', 'i', 'o', 'n', 's', '<', '/', 'B', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f44 NAME=L_ ... r performance:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '4', '4', 0, 'S', 'e', 'r',
    'v', 'e', 'r', 32, 'p', 'e', 'r', 'f', 'o', 'r', 'm', 'a', 'n', 'c',
    'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD RADIO f45 NAME=prio ... 0 DETAIL=0 VALUE=0 NULL="?"         */
    0, 24, 17, 0, 1, 0, 0, 'f', '4', '5', 0, '0', 0, 'N', 'o', 32, 's',
    'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  !--FIELD RADIO f45 OPTION="Normal"                                   */
    0, 11, 18, 13, 27, 1, 'N', 'o', 'r', 'm', 'a', 'l', 0,
    /*  !--FIELD RADIO f45 OPTION="Background"                               */
    0, 15, 18, 13, 27, 2, 'B', 'a', 'c', 'k', 'g', 'r', 'o', 'u', 'n',
    'd', 0,
    /*  !--FIELD RADIO f45 OPTION="Turbo!"                                   */
    0, 11, 18, 13, 27, 3, 'T', 'u', 'r', 'b', 'o', '!', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f46 NAME=L_ ... "IP port base:&nbsp;&nbsp;"         */
    0, 38, 10, 6, 1, 0, 0, 25, 0, 25, 'f', '4', '6', 0, 'I', 'P', 32,
    'p', 'o', 'r', 't', 32, 'b', 'a', 's', 'e', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD NUMERIC f47 NAME=po ... MMA=0 SIZE=5 MAX=? VALUE=""         */
    0, 18, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '4', '7', 0, 0,
    /*  !--FIELD TEXTUAL f48 NAME=L_ ... ;Fall-back to:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '4', '8', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'F', 'a', 'l', 'l', 45,
    'b', 'a', 'c', 'k', 32, 't', 'o', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD NUMERIC f49 NAME=po ... MMA=0 SIZE=5 MAX=? VALUE=""         */
    0, 18, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 1, 0, 'f', '4', '9', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f50 NAME=L_ ... t config file:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '5', '0', 0, 'B', 'a', 's',
    'e', 32, 'h', 'o', 's', 't', 32, 'c', 'o', 'n', 'f', 'i', 'g', 32,
    'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f51 NAME=ba ... =30 MAX=80 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '5', '1', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f52 NAME=L_ ... er IP address:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '5', '2', 0, 'S', 'e', 'r',
    'v', 'e', 'r', 32, 'I', 'P', 32, 'a', 'd', 'd', 'r', 'e', 's', 's',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD SELECT f53 NAME=ipa ... pe=dynamic 0="No selection"         */
    0, 24, 16, 0, 1, 1, 0, 'f', '5', '3', 0, '0', 0, 'N', 'o', 32, 's',
    'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f54 NAME=L_ ... or temp files:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '5', '4', 0, 'D', 'i', 'r',
    'e', 'c', 't', 'o', 'r', 'y', 32, 'f', 'o', 'r', 32, 't', 'e', 'm',
    'p', 32, 'f', 'i', 'l', 'e', 's', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f55 NAME=te ... 30 MAX=100 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 30, 0, 'd', 'f', '5', '5', 0, 0,
    /*  Can be an environment variable                                       */
    0, 32, 0, 'C', 'a', 'n', 32, 'b', 'e', 32, 'a', 'n', 32, 'e', 'n',
    'v', 'i', 'r', 'o', 'n', 'm', 'e', 'n', 't', 32, 'v', 'a', 'r', 'i',
    'a', 'b', 'l', 'e', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f56 NAME=L_ ... r debug files:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '5', '6', 0, 'D', 'i', 'r',
    'e', 'c', 't', 'o', 'r', 'y', 32, 'f', 'o', 'r', 32, 'd', 'e', 'b',
    'u', 'g', 32, 'f', 'i', 'l', 'e', 's', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f57 NAME=de ... 30 MAX=100 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 30, 0, 'd', 'f', '5', '7', 0, 0,
    /*  Can be an environment variable                                       */
    0, 4, 1, 0, 14, 246,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f58 NAME=L_ ... directed URLs?&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '5', '8', 0, 'T', 'r', 'a',
    'n', 's', 'l', 'a', 't', 'e', 32, 'r', 'e', 'd', 'i', 'r', 'e', 'c',
    't', 'e', 'd', 32, 'U', 'R', 'L', 's', '?', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD BOOLEAN f59 NAME=translate TRUE=yes FALSE=no VALUE=0        */
    0, 16, 15, 0, 1, 'f', '5', '9', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0,
    /*  Disable to redirect using only numeric addresses                     */
    0, 50, 0, 'D', 'i', 's', 'a', 'b', 'l', 'e', 32, 't', 'o', 32, 'r',
    'e', 'd', 'i', 'r', 'e', 'c', 't', 32, 'u', 's', 'i', 'n', 'g', 32,
    'o', 'n', 'l', 'y', 32, 'n', 'u', 'm', 'e', 'r', 'i', 'c', 32, 'a',
    'd', 'd', 'r', 'e', 's', 's', 'e', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f60 NAME=L_ ... o this server:&nbsp;&nbsp;"         */
    0, 59, 10, 6, 1, 0, 0, '.', 0, '.', 'f', '6', '0', 0, 'F', 'o', 'r',
    'c', 'e', 32, 'r', 'e', 'd', 'i', 'r', 'e', 'c', 't', 'i', 'o', 'n',
    's', 32, 't', 'o', 32, 't', 'h', 'i', 's', 32, 's', 'e', 'r', 'v',
    'e', 'r', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f61 NAME=ho ... =30 MAX=80 UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '6', '1', 0, 0,
    /*  If empty, uses the Host: header field                                */
    0, 39, 0, 'I', 'f', 32, 'e', 'm', 'p', 't', 'y', ',', 32, 'u', 's',
    'e', 's', 32, 't', 'h', 'e', 32, 'H', 'o', 's', 't', ':', 32, 'h',
    'e', 'a', 'd', 'e', 'r', 32, 'f', 'i', 'e', 'l', 'd', 10,
    /*  <TR><TD></TD><TD>                                                    */
    0, 4, 1, 0, 12, 171,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f62 NAME=L_ ... t URI mapping:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '6', '2', 0, 'T', 'e', 's',
    't', 32, 'U', 'R', 'I', 32, 'm', 'a', 'p', 'p', 'i', 'n', 'g', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f63 NAME=te ... E=50 MAX=? UPPER=0 VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '6', '3', 0, 0,
    /*  !--ACTION test  LABEL="Test" EVENT=test_event TYPE=BUTTON            */
    0, 21, 20, 0, (byte) ((word) test_event / 256), (byte) ((word)
    test_event & 255), 0, 18, 0, 0, 0, 0, 0, 't', 'e', 's', 't', 0, 'T',
    'e', 's', 't', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 'N',
    /*  !--FIELD TEXTUAL f64 NAME=L_ ... lt of mapping:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '6', '4', 0, 'R', 'e', 's',
    'u', 'l', 't', 32, 'o', 'f', 32, 'm', 'a', 'p', 'p', 'i', 'n', 'g',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, 165,
    /*  !--FIELD TEXTUAL f65 NAME=ma ... E=50 MAX=? UPPER=0 VALUE=""         */
    0, 13, 10, 6, 1, 0, 0, '2', 0, '2', 'f', '6', '5', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 215,
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
    0, 4, 1, 0, 16, 142,
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

static FIELD_DEFN xiadm03_fields [] = {
    { 0, 1031, 80 },                    /*  message_to_user                 */
    { 82, 1507, 4 },                    /*  main_config                     */
    { 88, 1536, 4 },                    /*  on_unix                         */
    { 94, 1561, 4 },                    /*  on_windows_32                   */
    { 100, 1655, 32 },                  /*  l_webpages                      */
    { 134, 1737, 100 },                 /*  webpages                        */
    { 236, 1771, 31 },                  /*  l_cgi_bin                       */
    { 269, 1823, 100 },                 /*  cgi_bin                         */
    { 371, 1850, 32 },                  /*  l_cgi_url                       */
    { 405, 1903, 40 },                  /*  cgi_url                         */
    { 447, 1937, 30 },                  /*  l_debug                         */
    { 479, 1988, 1 },                   /*  debug                           */
    { 482, 2052, 33 },                  /*  l_refresh_rate                  */
    { 517, 2106, 8 },                   /*  refresh_rate                    */
    { 527, 2149, 34 },                  /*  l_limit                         */
    { 563, 2204, 4 },                   /*  limit                           */
    { 569, 2253, 30 },                  /*  l_background                    */
    { 601, 2304, 1 },                   /*  background                      */
    { 604, 2341, 39 },                  /*  l_autostart                     */
    { 645, 2401, 1 },                   /*  autostart                       */
    { 648, 2431, 42 },                  /*  l_recover                       */
    { 692, 2494, 1 },                   /*  recover                         */
    { 695, 2524, 30 },                  /*  l_default1                      */
    { 727, 2575, 80 },                  /*  default1                        */
    { 809, 2590, 29 },                  /*  l_default2                      */
    { 840, 2634, 80 },                  /*  default2                        */
    { 922, 2649, 80 },                  /*  default3                        */
    { 1004, 2664, 80 },                 /*  default4                        */
    { 1086, 2691, 33 },                 /*  l_cache_defaults                */
    { 1121, 2745, 1 },                  /*  cache_defaults                  */
    { 1124, 2775, 41 },                 /*  l_keep_alive                    */
    { 1167, 2837, 1 },                  /*  keep_alive                      */
    { 1170, 2855, 36 },                 /*  l_keep_alive_max                */
    { 1208, 2906, 4 },                  /*  keep_alive_max                  */
    { 1214, 2938, 36 },                 /*  l_timeout                       */
    { 1252, 2989, 4 },                  /*  timeout                         */
    { 1258, 3027, 37 },                 /*  l_dirsort                       */
    { 1297, 3085, 5 },                  /*  dirsort                         */
    { 1304, 3159, 38 },                 /*  l_advertize                     */
    { 1344, 3218, 1 },                  /*  advertize                       */
    { 1347, 3303, 31 },                 /*  l_priority                      */
    { 1380, 3355, 3 },                  /*  priority                        */
    { 1385, 3436, 25 },                 /*  l_portbase                      */
    { 1412, 3482, 5 },                  /*  portbase                        */
    { 1419, 3502, 37 },                 /*  l_portbase1                     */
    { 1458, 3554, 5 },                  /*  portbase1                       */
    { 1465, 3586, 34 },                 /*  l_base_host                     */
    { 1501, 3641, 80 },                 /*  base_host                       */
    { 1583, 3668, 30 },                 /*  l_ipaddress                     */
    { 1615, 3719, 3 },                  /*  ipaddress                       */
    { 1620, 3757, 37 },                 /*  l_temp_dir                      */
    { 1659, 3815, 100 },                /*  temp_dir                        */
    { 1761, 3876, 38 },                 /*  l_debug_dir                     */
    { 1801, 3935, 100 },                /*  debug_dir                       */
    { 1903, 3968, 38 },                 /*  l_translate                     */
    { 1943, 4027, 1 },                  /*  translate                       */
    { 1946, 4109, 46 },                 /*  l_hostname                      */
    { 1994, 4176, 80 },                 /*  hostname                        */
    { 2076, 4258, 29 },                 /*  l_test_uri                      */
    { 2107, 4308, 50 },                 /*  test_uri                        */
    { 2159, 4358, 30 },                 /*  l_mapped_uri                    */
    { 2191, 4409, 50 },                 /*  mapped_uri                      */
    { 2243, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   main_config_a        ;
    char   main_config          [4 + 1];
    byte   on_unix_a            ;
    char   on_unix              [4 + 1];
    byte   on_windows_32_a      ;
    char   on_windows_32        [4 + 1];
    byte   l_webpages_a         ;
    char   l_webpages           [32 + 1];
    byte   webpages_a           ;
    char   webpages             [100 + 1];
    byte   l_cgi_bin_a          ;
    char   l_cgi_bin            [31 + 1];
    byte   cgi_bin_a            ;
    char   cgi_bin              [100 + 1];
    byte   l_cgi_url_a          ;
    char   l_cgi_url            [32 + 1];
    byte   cgi_url_a            ;
    char   cgi_url              [40 + 1];
    byte   l_debug_a            ;
    char   l_debug              [30 + 1];
    byte   debug_a              ;
    char   debug                [1 + 1];
    byte   l_refresh_rate_a     ;
    char   l_refresh_rate       [33 + 1];
    byte   refresh_rate_a       ;
    char   refresh_rate         [8 + 1];
    byte   l_limit_a            ;
    char   l_limit              [34 + 1];
    byte   limit_a              ;
    char   limit                [4 + 1];
    byte   l_background_a       ;
    char   l_background         [30 + 1];
    byte   background_a         ;
    char   background           [1 + 1];
    byte   l_autostart_a        ;
    char   l_autostart          [39 + 1];
    byte   autostart_a          ;
    char   autostart            [1 + 1];
    byte   l_recover_a          ;
    char   l_recover            [42 + 1];
    byte   recover_a            ;
    char   recover              [1 + 1];
    byte   l_default1_a         ;
    char   l_default1           [30 + 1];
    byte   default1_a           ;
    char   default1             [80 + 1];
    byte   l_default2_a         ;
    char   l_default2           [29 + 1];
    byte   default2_a           ;
    char   default2             [80 + 1];
    byte   default3_a           ;
    char   default3             [80 + 1];
    byte   default4_a           ;
    char   default4             [80 + 1];
    byte   l_cache_defaults_a   ;
    char   l_cache_defaults     [33 + 1];
    byte   cache_defaults_a     ;
    char   cache_defaults       [1 + 1];
    byte   l_keep_alive_a       ;
    char   l_keep_alive         [41 + 1];
    byte   keep_alive_a         ;
    char   keep_alive           [1 + 1];
    byte   l_keep_alive_max_a   ;
    char   l_keep_alive_max     [36 + 1];
    byte   keep_alive_max_a     ;
    char   keep_alive_max       [4 + 1];
    byte   l_timeout_a          ;
    char   l_timeout            [36 + 1];
    byte   timeout_a            ;
    char   timeout              [4 + 1];
    byte   l_dirsort_a          ;
    char   l_dirsort            [37 + 1];
    byte   dirsort_a            ;
    char   dirsort              [5 + 1];
    byte   l_advertize_a        ;
    char   l_advertize          [38 + 1];
    byte   advertize_a          ;
    char   advertize            [1 + 1];
    byte   l_priority_a         ;
    char   l_priority           [31 + 1];
    byte   priority_a           ;
    char   priority             [3 + 1];
    byte   l_portbase_a         ;
    char   l_portbase           [25 + 1];
    byte   portbase_a           ;
    char   portbase             [5 + 1];
    byte   l_portbase1_a        ;
    char   l_portbase1          [37 + 1];
    byte   portbase1_a          ;
    char   portbase1            [5 + 1];
    byte   l_base_host_a        ;
    char   l_base_host          [34 + 1];
    byte   base_host_a          ;
    char   base_host            [80 + 1];
    byte   l_ipaddress_a        ;
    char   l_ipaddress          [30 + 1];
    byte   ipaddress_a          ;
    char   ipaddress            [3 + 1];
    byte   l_temp_dir_a         ;
    char   l_temp_dir           [37 + 1];
    byte   temp_dir_a           ;
    char   temp_dir             [100 + 1];
    byte   l_debug_dir_a        ;
    char   l_debug_dir          [38 + 1];
    byte   debug_dir_a          ;
    char   debug_dir            [100 + 1];
    byte   l_translate_a        ;
    char   l_translate          [38 + 1];
    byte   translate_a          ;
    char   translate            [1 + 1];
    byte   l_hostname_a         ;
    char   l_hostname           [46 + 1];
    byte   hostname_a           ;
    char   hostname             [80 + 1];
    byte   l_test_uri_a         ;
    char   l_test_uri           [29 + 1];
    byte   test_uri_a           ;
    char   test_uri             [50 + 1];
    byte   l_mapped_uri_a       ;
    char   l_mapped_uri         [30 + 1];
    byte   mapped_uri_a         ;
    char   mapped_uri           [50 + 1];
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
    byte   aliases_a;
    byte   vhosts_a;
    byte   cgi_a;
    byte   security_a;
    byte   logging_a;
    byte   ftp_a;
    byte   mime_a;
    byte   test_a;
    } XIADM03_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm03 = {
    xiadm03_blocks,
    xiadm03_fields,
    215,                                /*  Number of blocks in form        */
    62,                                 /*  Number of fields in form        */
    19,                                 /*  Number of actions in form       */
    2243,                               /*  Size of fields                  */
    "xiadm03",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
