/*---------------------------------------------------------------------------
 *  xiadm08.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM08__
#define __FORM_XIADM08__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM08_MESSAGE_TO_USER             0
#define XIADM08_MAIN_CONFIG                 1
#define XIADM08_EXTENDED                    2
#define XIADM08_L_LOG_DIR                   3
#define XIADM08_LOG_DIR                     4
#define XIADM08_L_SRV_ENABLED               5
#define XIADM08_SRV_ENABLED                 6
#define XIADM08_L_SRV_FILENAME              7
#define XIADM08_SRV_FILENAME                8
#define XIADM08_L_SRV_CYCLE                 9
#define XIADM08_SRV_CYCLE                   10
#define XIADM08_L_ACC_ENABLED               11
#define XIADM08_ACC_ENABLED                 12
#define XIADM08_L_ACC_FILENAME              13
#define XIADM08_ACC_FILENAME                14
#define XIADM08_L_ACC_CYCLE                 15
#define XIADM08_ACC_CYCLE                   16
#define XIADM08_L_ACC_LOCAL                 17
#define XIADM08_ACC_LOCAL                   18
#define XIADM08_L_ACC_EXTENDED              19
#define XIADM08_ACC_EXTENDED                20
#define XIADM08_L_ACC_FORMAT                21
#define XIADM08_ACC_FORMAT                  22
#define XIADM08_L_ACC_CUSTOM                23
#define XIADM08_ACC_CUSTOM                  24
#define XIADM08_L_ACC_CYCLEX                25
#define XIADM08_ACC_CYCLEX                  26
#define XIADM08_L_ACC_CYTIME                27
#define XIADM08_ACC_CYTIME                  28
#define XIADM08_L_ACC_CYDAY                 29
#define XIADM08_ACC_CYDAY                   30
#define XIADM08_L_ACC_CYSIZE                31
#define XIADM08_ACC_CYSIZE                  32
#define XIADM08_L_ACC_CYLINES               33
#define XIADM08_ACC_CYLINES                 34
#define XIADM08_L_ACC_CYHOW                 35
#define XIADM08_ACC_CYHOW                   36
#define XIADM08_L_ACC_CYARG                 37
#define XIADM08_ACC_CYARG                   38
#define XIADM08_L_ACC_XLATE                 39
#define XIADM08_ACC_XLATE                   40
#define XIADM08_L_ERR_ENABLED               41
#define XIADM08_ERR_ENABLED                 42
#define XIADM08_L_ERR_FILENAME              43
#define XIADM08_ERR_FILENAME                44
#define XIADM08_L_ERR_CYCLE                 45
#define XIADM08_ERR_CYCLE                   46
#define XIADM08_L_ERR_LOCAL                 47
#define XIADM08_ERR_LOCAL                   48
#define XIADM08_L_ERR_EXTENDED              49
#define XIADM08_ERR_EXTENDED                50
#define XIADM08_L_ERR_FORMAT                51
#define XIADM08_ERR_FORMAT                  52
#define XIADM08_L_ERR_CUSTOM                53
#define XIADM08_ERR_CUSTOM                  54
#define XIADM08_L_ERR_CYCLEX                55
#define XIADM08_ERR_CYCLEX                  56
#define XIADM08_L_ERR_CYTIME                57
#define XIADM08_ERR_CYTIME                  58
#define XIADM08_L_ERR_CYDAY                 59
#define XIADM08_ERR_CYDAY                   60
#define XIADM08_L_ERR_CYSIZE                61
#define XIADM08_ERR_CYSIZE                  62
#define XIADM08_L_ERR_CYLINES               63
#define XIADM08_ERR_CYLINES                 64
#define XIADM08_L_ERR_CYHOW                 65
#define XIADM08_ERR_CYHOW                   66
#define XIADM08_L_ERR_CYARG                 67
#define XIADM08_ERR_CYARG                   68
#define XIADM08_L_ERR_XLATE                 69
#define XIADM08_ERR_XLATE                   70
#define XIADM08_L_PRIMARY                   71
#define XIADM08_PRIMARY                     72
#define XIADM08_L_SECONDARY                 73
#define XIADM08_SECONDARY                   74
#define XIADM08_L_RECURSE                   75
#define XIADM08_RECURSE                     76
#define XIADM08_L_DEBUG                     77
#define XIADM08_DEBUG                       78

/*  This table contains each block in the form                               */

static byte xiadm08_blocks [] = {
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
    /*  <TD ALIGN=CENTER><FONT SIZE=+1>#(config) - Log Files </FONT>         */
    0, 62, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'L', 'o', 'g', 32, 'F', 'i', 'l', 'e', 's', 32,
    '<', '/', 'F', 'O', 'N', 'T', '>', 10,
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
    0, 4, 1, 0, 2, 180,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 157,
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
    /*  <EM>Logging</EM>                                                     */
    0, 18, 0, '<', 'E', 'M', '>', 'L', 'o', 'g', 'g', 'i', 'n', 'g',
    '<', '/', 'E', 'M', '>', 10,
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
    /*  !--FIELD NUMERIC extended SIZE=4 VALUE=1                             */
    0, 24, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'e', 'x', 't', 'e',
    'n', 'd', 'e', 'd', 0, '1', 0,
    /*  <TABLE WIDTH=100%>                                                   */
    0, 20, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 39, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', '>', 10,
    /*  !--FIELD TEXTUAL f137 NAME=L ... ile directory:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '1', '3', '7', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o',
    'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 34, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I',
    'G', 'N', '=', 'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=',
    '"', '8', '0', '%', '"', '>', 10,
    /*  !--FIELD TEXTUAL f138 NAME=l ... E=50 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '1', '3', '8', 0, 0,
    /*  May be blank                                                         */
    0, 14, 0, 'M', 'a', 'y', 32, 'b', 'e', 32, 'b', 'l', 'a', 'n', 'k',
    10,
    /*  !--IF main_config                                                    */
    0, 5, 2, 0, 1, 0, 12,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f139 NAME=L ... rver messages:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '1', '3', '9', 0, 'L', 'o',
    'g', 32, 's', 'e', 'r', 'v', 'e', 'r', 32, 'm', 'e', 's', 's', 'a',
    'g', 'e', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f140 NAME=s ... d TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '4', '0', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--FIELD TEXTUAL f141 NAME=L ... &nbsp;to file:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '1', '4', '1', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 't', 'o', 32, 'f',
    'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  !--FIELD TEXTUAL f142 NAME=s ... =40 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '1', '4', '2', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f143 NAME=L ...  VALUE="Cycle:&nbsp;&nbsp;"         */
    0, 32, 10, 6, 1, 0, 0, 18, 0, 18, 'f', '1', '4', '3', 0, 'C', 'y',
    'c', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f144 NAME=sr ... kly" 4="Monthly" 5="Manual"         */
    0, 58, 16, 0, 1, 1, 5, 'f', '1', '4', '4', 0, '0', 0, 'A', 't', 32,
    's', 't', 'a', 'r', 't', 'u', 'p', 0, 'H', 'o', 'u', 'r', 'l', 'y',
    0, 'D', 'a', 'i', 'l', 'y', 0, 'W', 'e', 'e', 'k', 'l', 'y', 0, 'M',
    'o', 'n', 't', 'h', 'l', 'y', 0, 'M', 'a', 'n', 'u', 'a', 'l', 0,
    /*  <TR><TD></TD><TD>                                                    */
    0, 19, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', '>', 10,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f145 NAME=L ... ep access log:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '1', '4', '5', 0, 'K', 'e',
    'e', 'p', 32, 'a', 'c', 'c', 'e', 's', 's', 32, 'l', 'o', 'g', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f146 NAME=a ... d TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '4', '6', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--FIELD TEXTUAL f147 NAME=L ... &nbsp;to file:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '1', '4', '7', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 't', 'o', 32, 'f',
    'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  !--FIELD TEXTUAL f148 NAME=a ... =40 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '1', '4', '8', 0, 0,
    /*  !--UNLESS extended                                                   */
    0, 5, 3, 0, 2, 0, 5,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f149 NAME=L ...  VALUE="Cycle:&nbsp;&nbsp;"         */
    0, 32, 10, 6, 1, 0, 0, 18, 0, 18, 'f', '1', '4', '9', 0, 'C', 'y',
    'c', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f150 NAME=ac ... kly" 4="Monthly" 5="Manual"         */
    0, 58, 16, 0, 1, 1, 5, 'f', '1', '5', '0', 0, '0', 0, 'A', 't', 32,
    's', 't', 'a', 'r', 't', 'u', 'p', 0, 'H', 'o', 'u', 'r', 'l', 'y',
    0, 'D', 'a', 'i', 'l', 'y', 0, 'W', 'e', 'e', 'k', 'l', 'y', 0, 'M',
    'o', 'n', 't', 'h', 'l', 'y', 0, 'M', 'a', 'n', 'u', 'a', 'l', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f151 NAME=L ... cal addresses:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '1', '5', '1', 0, 'I', 'n',
    'c', 'l', 'u', 'd', 'e', 32, 'l', 'o', 'c', 'a', 'l', 32, 'a', 'd',
    'd', 'r', 'e', 's', 's', 'e', 's', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f152 NAME=a ... l TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '5', '2', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--IF extended                                                       */
    0, 5, 2, 0, 2, 0, '1',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f153 NAME=L ... ended logging:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '1', '5', '3', 0, 'E', 'n',
    'a', 'b', 'l', 'e', 32, 'e', 'x', 't', 'e', 'n', 'd', 'e', 'd', 32,
    'l', 'o', 'g', 'g', 'i', 'n', 'g', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f154 NAME=a ... d TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '5', '4', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f155 NAME=L ... g file format:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '1', '5', '5', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'f', 'o', 'r', 'm', 'a', 't', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f156 NAME=ac ... pe=dynamic 0="No selection"         */
    0, 25, 16, 0, 1, 1, 0, 'f', '1', '5', '6', 0, '0', 0, 'N', 'o', 32,
    's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f157 NAME=L ... format string:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '1', '5', '7', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'f', 'o', 'r', 'm', 'a', 't', 32,
    's', 't', 'r', 'i', 'n', 'g', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD TEXTUAL f158 NAME=a ... 80 MAX=512 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 'P', 2, 0, 'f', '1', '5', '8', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f159 NAME=L ...  VALUE="Cycle:&nbsp;&nbsp;"         */
    0, 32, 10, 6, 1, 0, 0, 18, 0, 18, 'f', '1', '5', '9', 0, 'C', 'y',
    'c', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f160 NAME=ac ... ytes" 7="More than X lines"         */
    0, 95, 16, 0, 1, 1, 7, 'f', '1', '6', '0', 0, '0', 0, 'A', 't', 32,
    's', 't', 'a', 'r', 't', 'u', 'p', 0, 'H', 'o', 'u', 'r', 'l', 'y',
    0, 'D', 'a', 'i', 'l', 'y', 0, 'W', 'e', 'e', 'k', 'l', 'y', 0, 'M',
    'o', 'n', 't', 'h', 'l', 'y', 0, 'M', 'a', 'n', 'u', 'a', 'l', 0,
    'M', 'o', 'r', 'e', 32, 't', 'h', 'a', 'n', 32, 'X', 32, 'K', 'b',
    'y', 't', 'e', 's', 0, 'M', 'o', 'r', 'e', 32, 't', 'h', 'a', 'n',
    32, 'X', 32, 'l', 'i', 'n', 'e', 's', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f161 NAME=L ...  time (HH:MM):&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '1', '6', '1', 0, 'C', 'y',
    'c', 'l', 'e', 32, 'a', 't', 32, 't', 'i', 'm', 'e', 32, '(', 'H',
    'H', ':', 'M', 'M', ')', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD TEXTUAL f162 NAME=a ... ZE=5 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '1', '6', '2', 0, 0,
    /*  !--FIELD TEXTUAL f163 NAME=L ... week or month:&nbsp;&nbsp;"         */
    0, 62, 10, 6, 1, 0, 0, '0', 0, '0', 'f', '1', '6', '3', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'o', 'n', 32, 'd',
    'a', 'y', 32, 'o', 'f', 32, 'w', 'e', 'e', 'k', 32, 'o', 'r', 32,
    'm', 'o', 'n', 't', 'h', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD NUMERIC f164 NAME=a ... MMA=0 SIZE=3 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 'f', '1', '6', '4',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f165 NAME=L ...  for log file:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '1', '6', '5', 0, 'M', 'a',
    'x', '.', 32, 'k', 'b', 'y', 't', 'e', 's', 32, 'f', 'o', 'r', 32,
    'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD NUMERIC f166 NAME=a ... MMA=0 SIZE=6 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '1', '6', '6',
    0, 0,
    /*  !--FIELD TEXTUAL f167 NAME=L ...  for log file:&nbsp;&nbsp;"         */
    0, 62, 10, 6, 1, 0, 0, '0', 0, '0', 'f', '1', '6', '7', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'm', 'a', 'x',
    '.', 32, 'l', 'i', 'n', 'e', 's', 32, 'f', 'o', 'r', 32, 'l', 'o',
    'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD NUMERIC f168 NAME=a ... MMA=0 SIZE=9 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 'f', '1', '6', '8',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f169 NAME=L ...  old log file:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '1', '6', '9', 0, 'H', 'o',
    'w', 32, 't', 'o', 32, 'c', 'y', 'c', 'l', 'e', 32, 'o', 'l', 'd',
    32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f170 NAME=ac ... ng command specified below"         */
    0, 209, 16, 0, 1, 1, 4, 'f', '1', '7', '0', 0, '0', 0, 'R', 'e',
    'n', 'a', 'm', 'e', 32, 't', 'o', 32, 'p', 'a', 't', 'h', '/', 'f',
    'i', 'l', 'e', 'n', 'a', 'm', 'e', 32, 'a', 's', 32, 's', 'p', 'e',
    'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o', 'w', 0, 'D',
    'e', 'l', 'e', 't', 'e', 32, 'o', 'l', 'd', 32, 'l', 'o', 'g', 32,
    'f', 'i', 'l', 'e', 0, 'M', 'o', 'v', 'e', 32, 'l', 'o', 'g', 32,
    'f', 'i', 'l', 'e', 32, 't', 'o', 32, 'p', 'a', 't', 'h', 32, 's',
    'p', 'e', 'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o', 'w',
    0, 'A', 'p', 'p', 'e', 'n', 'd', 32, 'l', 'o', 'g', 32, 'f', 'i',
    'l', 'e', 32, 't', 'o', 32, 'p', 'a', 't', 'h', '/', 'f', 'i', 'l',
    'e', 'n', 'a', 'm', 'e', 32, 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e',
    'd', 32, 'b', 'e', 'l', 'o', 'w', 0, 'P', 'r', 'o', 'c', 'e', 's',
    's', 32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', 32, 'u', 's', 'i',
    'n', 'g', 32, 'c', 'o', 'm', 'm', 'a', 'n', 'd', 32, 's', 'p', 'e',
    'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o', 'w', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f171 NAME=L ... ycle operation&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '1', '7', '1', 0, 'A', 'r',
    'g', 'u', 'm', 'e', 'n', 't', 32, 'f', 'o', 'r', 32, 'c', 'y', 'c',
    'l', 'e', 32, 'o', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD TEXTUAL f172 NAME=a ... =40 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '1', '7', '2', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f173 NAME=L ...  IP addresses?&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '1', '7', '3', 0, 'T', 'r',
    'a', 'n', 's', 'l', 'a', 't', 'e', 32, 'I', 'P', 32, 'a', 'd', 'd',
    'r', 'e', 's', 's', 'e', 's', '?', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f174 NAME=a ... e TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '7', '4', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  <TR><TD></TD><TD>                                                    */
    0, 4, 1, 0, 7, 215,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 7, 236,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f175 NAME=L ... eep error log:&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '1', '7', '5', 0, 'K', 'e',
    'e', 'p', 32, 'e', 'r', 'r', 'o', 'r', 32, 'l', 'o', 'g', ':', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f176 NAME=e ... d TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '7', '6', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--FIELD TEXTUAL f177 NAME=L ... &nbsp;to file:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '1', '7', '7', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 't', 'o', 32, 'f',
    'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  !--FIELD TEXTUAL f178 NAME=e ... =40 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '1', '7', '8', 0, 0,
    /*  !--UNLESS extended                                                   */
    0, 5, 3, 0, 2, 0, 5,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f179 NAME=L ...  VALUE="Cycle:&nbsp;&nbsp;"         */
    0, 32, 10, 6, 1, 0, 0, 18, 0, 18, 'f', '1', '7', '9', 0, 'C', 'y',
    'c', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f180 NAME=er ... kly" 4="Monthly" 5="Manual"         */
    0, 58, 16, 0, 1, 1, 5, 'f', '1', '8', '0', 0, '0', 0, 'A', 't', 32,
    's', 't', 'a', 'r', 't', 'u', 'p', 0, 'H', 'o', 'u', 'r', 'l', 'y',
    0, 'D', 'a', 'i', 'l', 'y', 0, 'W', 'e', 'e', 'k', 'l', 'y', 0, 'M',
    'o', 'n', 't', 'h', 'l', 'y', 0, 'M', 'a', 'n', 'u', 'a', 'l', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f181 NAME=L ... cal addresses:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '1', '8', '1', 0, 'I', 'n',
    'c', 'l', 'u', 'd', 'e', 32, 'l', 'o', 'c', 'a', 'l', 32, 'a', 'd',
    'd', 'r', 'e', 's', 's', 'e', 's', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f182 NAME=e ... l TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '8', '2', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--IF extended                                                       */
    0, 5, 2, 0, 2, 0, '1',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f183 NAME=L ... ended logging:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '1', '8', '3', 0, 'E', 'n',
    'a', 'b', 'l', 'e', 32, 'e', 'x', 't', 'e', 'n', 'd', 'e', 'd', 32,
    'l', 'o', 'g', 'g', 'i', 'n', 'g', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f184 NAME=e ... d TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '8', '4', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f185 NAME=L ... g file format:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '1', '8', '5', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'f', 'o', 'r', 'm', 'a', 't', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f186 NAME=er ... pe=dynamic 0="No selection"         */
    0, 25, 16, 0, 1, 1, 0, 'f', '1', '8', '6', 0, '0', 0, 'N', 'o', 32,
    's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f187 NAME=L ... format string:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '1', '8', '7', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'f', 'o', 'r', 'm', 'a', 't', 32,
    's', 't', 'r', 'i', 'n', 'g', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD TEXTUAL f188 NAME=e ... 80 MAX=512 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 'P', 2, 0, 'f', '1', '8', '8', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f189 NAME=L ...  VALUE="Cycle:&nbsp;&nbsp;"         */
    0, 32, 10, 6, 1, 0, 0, 18, 0, 18, 'f', '1', '8', '9', 0, 'C', 'y',
    'c', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f190 NAME=er ... ytes" 7="More than X lines"         */
    0, 95, 16, 0, 1, 1, 7, 'f', '1', '9', '0', 0, '0', 0, 'A', 't', 32,
    's', 't', 'a', 'r', 't', 'u', 'p', 0, 'H', 'o', 'u', 'r', 'l', 'y',
    0, 'D', 'a', 'i', 'l', 'y', 0, 'W', 'e', 'e', 'k', 'l', 'y', 0, 'M',
    'o', 'n', 't', 'h', 'l', 'y', 0, 'M', 'a', 'n', 'u', 'a', 'l', 0,
    'M', 'o', 'r', 'e', 32, 't', 'h', 'a', 'n', 32, 'X', 32, 'K', 'b',
    'y', 't', 'e', 's', 0, 'M', 'o', 'r', 'e', 32, 't', 'h', 'a', 'n',
    32, 'X', 32, 'l', 'i', 'n', 'e', 's', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f191 NAME=L ...  time (HH:MM):&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '1', '9', '1', 0, 'C', 'y',
    'c', 'l', 'e', 32, 'a', 't', 32, 't', 'i', 'm', 'e', 32, '(', 'H',
    'H', ':', 'M', 'M', ')', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD TEXTUAL f192 NAME=e ... ZE=5 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '1', '9', '2', 0, 0,
    /*  !--FIELD TEXTUAL f193 NAME=L ... week or month:&nbsp;&nbsp;"         */
    0, 62, 10, 6, 1, 0, 0, '0', 0, '0', 'f', '1', '9', '3', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'o', 'n', 32, 'd',
    'a', 'y', 32, 'o', 'f', 32, 'w', 'e', 'e', 'k', 32, 'o', 'r', 32,
    'm', 'o', 'n', 't', 'h', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD NUMERIC f194 NAME=e ... MMA=0 SIZE=3 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 'f', '1', '9', '4',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f195 NAME=L ...  for log file:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '1', '9', '5', 0, 'M', 'a',
    'x', '.', 32, 'k', 'b', 'y', 't', 'e', 's', 32, 'f', 'o', 'r', 32,
    'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD NUMERIC f196 NAME=e ... MMA=0 SIZE=6 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '1', '9', '6',
    0, 0,
    /*  !--FIELD TEXTUAL f197 NAME=L ...  for log file:&nbsp;&nbsp;"         */
    0, 62, 10, 6, 1, 0, 0, '0', 0, '0', 'f', '1', '9', '7', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'm', 'a', 'x',
    '.', 32, 'l', 'i', 'n', 'e', 's', 32, 'f', 'o', 'r', 32, 'l', 'o',
    'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD NUMERIC f198 NAME=e ... MMA=0 SIZE=9 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 'f', '1', '9', '8',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f199 NAME=L ...  old log file:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '1', '9', '9', 0, 'H', 'o',
    'w', 32, 't', 'o', 32, 'c', 'y', 'c', 'l', 'e', 32, 'o', 'l', 'd',
    32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD SELECT f200 NAME=er ... ng command specified below"         */
    0, 209, 16, 0, 1, 1, 4, 'f', '2', '0', '0', 0, '0', 0, 'R', 'e',
    'n', 'a', 'm', 'e', 32, 't', 'o', 32, 'p', 'a', 't', 'h', '/', 'f',
    'i', 'l', 'e', 'n', 'a', 'm', 'e', 32, 'a', 's', 32, 's', 'p', 'e',
    'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o', 'w', 0, 'D',
    'e', 'l', 'e', 't', 'e', 32, 'o', 'l', 'd', 32, 'l', 'o', 'g', 32,
    'f', 'i', 'l', 'e', 0, 'M', 'o', 'v', 'e', 32, 'l', 'o', 'g', 32,
    'f', 'i', 'l', 'e', 32, 't', 'o', 32, 'p', 'a', 't', 'h', 32, 's',
    'p', 'e', 'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o', 'w',
    0, 'A', 'p', 'p', 'e', 'n', 'd', 32, 'l', 'o', 'g', 32, 'f', 'i',
    'l', 'e', 32, 't', 'o', 32, 'p', 'a', 't', 'h', '/', 'f', 'i', 'l',
    'e', 'n', 'a', 'm', 'e', 32, 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e',
    'd', 32, 'b', 'e', 'l', 'o', 'w', 0, 'P', 'r', 'o', 'c', 'e', 's',
    's', 32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', 32, 'u', 's', 'i',
    'n', 'g', 32, 'c', 'o', 'm', 'm', 'a', 'n', 'd', 32, 's', 'p', 'e',
    'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o', 'w', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f201 NAME=L ... ycle operation&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '2', '0', '1', 0, 'A', 'r',
    'g', 'u', 'm', 'e', 'n', 't', 32, 'f', 'o', 'r', 32, 'c', 'y', 'c',
    'l', 'e', 32, 'o', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD TEXTUAL f202 NAME=e ... =40 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '2', '0', '2', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f203 NAME=L ...  IP addresses?&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '2', '0', '3', 0, 'T', 'r',
    'a', 'n', 's', 'l', 'a', 't', 'e', 32, 'I', 'P', 32, 'a', 'd', 'd',
    'r', 'e', 's', 's', 'e', 's', '?', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f204 NAME=e ... e TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '2', '0', '4', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  !--IF main_config                                                    */
    0, 5, 2, 0, 1, 0, 19,
    /*  <TR><TD></TD><TD>                                                    */
    0, 4, 1, 0, 7, 215,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 7, 236,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f205 NAME=L ... ers - primary:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '2', '0', '5', 0, 'D', 'N',
    'S', 32, 's', 'e', 'r', 'v', 'e', 'r', 's', 32, 45, 32, 'p', 'r',
    'i', 'm', 'a', 'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD TEXTUAL f206 NAME=p ... E=20 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '2', '0', '6', 0, 0,
    /*  !--FIELD TEXTUAL f207 NAME=L ... bsp;secondary:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '2', '0', '7', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 's', 'e', 'c',
    'o', 'n', 'd', 'a', 'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  !--FIELD TEXTUAL f208 NAME=s ... E=20 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '2', '0', '8', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f209 NAME=L ... rsive queries?&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '2', '0', '9', 0, 'A', 'l',
    'l', 'o', 'w', 32, 'r', 'e', 'c', 'u', 'r', 's', 'i', 'v', 'e', 32,
    'q', 'u', 'e', 'r', 'i', 'e', 's', '?', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f210 NAME=recurse TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '2', '1', '0', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 6, 39,
    /*  !--FIELD TEXTUAL f211 NAME=L ... e-DNS queries?&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '2', '1', '1', 0, 'D', 'e',
    'b', 'u', 'g', 32, 'r', 'e', 'v', 'e', 'r', 's', 'e', 45, 'D', 'N',
    'S', 32, 'q', 'u', 'e', 'r', 'i', 'e', 's', '?', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 6, '',
    /*  !--FIELD BOOLEAN f212 NAME=debug TRUE=yes FALSE=no VALUE=0           */
    0, 17, 15, 0, 1, 'f', '2', '1', '2', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 6, 202,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 157,
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
    0, 4, 1, 0, 7, 236,
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
    0, 4, 1, 0, 3, 157,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm08_fields [] = {
    { 0, 1023, 80 },                    /*  message_to_user                 */
    { 82, 1498, 4 },                    /*  main_config                     */
    { 88, 1527, 4 },                    /*  extended                        */
    { 94, 1616, 31 },                   /*  l_log_dir                       */
    { 127, 1699, 50 },                  /*  log_dir                         */
    { 179, 1758, 32 },                  /*  l_srv_enabled                   */
    { 213, 1812, 1 },                   /*  srv_enabled                     */
    { 216, 1831, 32 },                  /*  l_srv_filename                  */
    { 250, 1879, 80 },                  /*  srv_filename                    */
    { 332, 1907, 18 },                  /*  l_srv_cycle                     */
    { 352, 1947, 3 },                   /*  srv_cycle                       */
    { 357, 2048, 28 },                  /*  l_acc_enabled                   */
    { 387, 2098, 1 },                   /*  acc_enabled                     */
    { 390, 2117, 32 },                  /*  l_acc_filename                  */
    { 424, 2165, 80 },                  /*  acc_filename                    */
    { 506, 2200, 18 },                  /*  l_acc_cycle                     */
    { 526, 2240, 3 },                   /*  acc_cycle                       */
    { 531, 2312, 36 },                  /*  l_acc_local                     */
    { 569, 2370, 1 },                   /*  acc_local                       */
    { 572, 2408, 36 },                  /*  l_acc_extended                  */
    { 610, 2466, 1 },                   /*  acc_extended                    */
    { 613, 2497, 28 },                  /*  l_acc_format                    */
    { 643, 2547, 3 },                   /*  acc_format                      */
    { 648, 2586, 35 },                  /*  l_acc_custom                    */
    { 685, 2643, 512 },                 /*  acc_custom                      */
    { 1199, 2671, 18 },                 /*  l_acc_cyclex                    */
    { 1219, 2711, 3 },                  /*  acc_cyclex                      */
    { 1224, 2820, 34 },                 /*  l_acc_cytime                    */
    { 1260, 2876, 5 },                  /*  acc_cytime                      */
    { 1267, 2892, 48 },                 /*  l_acc_cyday                     */
    { 1317, 2956, 3 },                  /*  acc_cyday                       */
    { 1322, 2989, 37 },                 /*  l_acc_cysize                    */
    { 1361, 3048, 6 },                  /*  acc_cysize                      */
    { 1369, 3069, 48 },                 /*  l_acc_cylines                   */
    { 1419, 3133, 9 },                  /*  acc_cylines                     */
    { 1430, 3166, 38 },                 /*  l_acc_cyhow                     */
    { 1470, 3226, 3 },                  /*  acc_cyhow                       */
    { 1475, 3449, 40 },                 /*  l_acc_cyarg                     */
    { 1517, 3511, 80 },                 /*  acc_cyarg                       */
    { 1599, 3539, 35 },                 /*  l_acc_xlate                     */
    { 1636, 3596, 1 },                  /*  acc_xlate                       */
    { 1639, 3639, 27 },                 /*  l_err_enabled                   */
    { 1668, 3688, 1 },                  /*  err_enabled                     */
    { 1671, 3707, 32 },                 /*  l_err_filename                  */
    { 1705, 3755, 80 },                 /*  err_filename                    */
    { 1787, 3790, 18 },                 /*  l_err_cycle                     */
    { 1807, 3830, 3 },                  /*  err_cycle                       */
    { 1812, 3902, 36 },                 /*  l_err_local                     */
    { 1850, 3960, 1 },                  /*  err_local                       */
    { 1853, 3998, 36 },                 /*  l_err_extended                  */
    { 1891, 4056, 1 },                  /*  err_extended                    */
    { 1894, 4087, 28 },                 /*  l_err_format                    */
    { 1924, 4137, 3 },                  /*  err_format                      */
    { 1929, 4176, 35 },                 /*  l_err_custom                    */
    { 1966, 4233, 512 },                /*  err_custom                      */
    { 2480, 4261, 18 },                 /*  l_err_cyclex                    */
    { 2500, 4301, 3 },                  /*  err_cyclex                      */
    { 2505, 4410, 34 },                 /*  l_err_cytime                    */
    { 2541, 4466, 5 },                  /*  err_cytime                      */
    { 2548, 4482, 48 },                 /*  l_err_cyday                     */
    { 2598, 4546, 3 },                  /*  err_cyday                       */
    { 2603, 4579, 37 },                 /*  l_err_cysize                    */
    { 2642, 4638, 6 },                  /*  err_cysize                      */
    { 2650, 4659, 48 },                 /*  l_err_cylines                   */
    { 2700, 4723, 9 },                  /*  err_cylines                     */
    { 2711, 4756, 38 },                 /*  l_err_cyhow                     */
    { 2751, 4816, 3 },                  /*  err_cyhow                       */
    { 2756, 5039, 40 },                 /*  l_err_cyarg                     */
    { 2798, 5101, 80 },                 /*  err_cyarg                       */
    { 2880, 5129, 35 },                 /*  l_err_xlate                     */
    { 2917, 5186, 1 },                  /*  err_xlate                       */
    { 2920, 5236, 34 },                 /*  l_primary                       */
    { 2956, 5292, 20 },                 /*  primary                         */
    { 2978, 5308, 34 },                 /*  l_secondary                     */
    { 3014, 5358, 20 },                 /*  secondary                       */
    { 3036, 5386, 36 },                 /*  l_recurse                       */
    { 3074, 5444, 1 },                  /*  recurse                         */
    { 3077, 5475, 38 },                 /*  l_debug                         */
    { 3117, 5535, 1 },                  /*  debug                           */
    { 3120, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   main_config_a        ;
    char   main_config          [4 + 1];
    byte   extended_a           ;
    char   extended             [4 + 1];
    byte   l_log_dir_a          ;
    char   l_log_dir            [31 + 1];
    byte   log_dir_a            ;
    char   log_dir              [50 + 1];
    byte   l_srv_enabled_a      ;
    char   l_srv_enabled        [32 + 1];
    byte   srv_enabled_a        ;
    char   srv_enabled          [1 + 1];
    byte   l_srv_filename_a     ;
    char   l_srv_filename       [32 + 1];
    byte   srv_filename_a       ;
    char   srv_filename         [80 + 1];
    byte   l_srv_cycle_a        ;
    char   l_srv_cycle          [18 + 1];
    byte   srv_cycle_a          ;
    char   srv_cycle            [3 + 1];
    byte   l_acc_enabled_a      ;
    char   l_acc_enabled        [28 + 1];
    byte   acc_enabled_a        ;
    char   acc_enabled          [1 + 1];
    byte   l_acc_filename_a     ;
    char   l_acc_filename       [32 + 1];
    byte   acc_filename_a       ;
    char   acc_filename         [80 + 1];
    byte   l_acc_cycle_a        ;
    char   l_acc_cycle          [18 + 1];
    byte   acc_cycle_a          ;
    char   acc_cycle            [3 + 1];
    byte   l_acc_local_a        ;
    char   l_acc_local          [36 + 1];
    byte   acc_local_a          ;
    char   acc_local            [1 + 1];
    byte   l_acc_extended_a     ;
    char   l_acc_extended       [36 + 1];
    byte   acc_extended_a       ;
    char   acc_extended         [1 + 1];
    byte   l_acc_format_a       ;
    char   l_acc_format         [28 + 1];
    byte   acc_format_a         ;
    char   acc_format           [3 + 1];
    byte   l_acc_custom_a       ;
    char   l_acc_custom         [35 + 1];
    byte   acc_custom_a         ;
    char   acc_custom           [512 + 1];
    byte   l_acc_cyclex_a       ;
    char   l_acc_cyclex         [18 + 1];
    byte   acc_cyclex_a         ;
    char   acc_cyclex           [3 + 1];
    byte   l_acc_cytime_a       ;
    char   l_acc_cytime         [34 + 1];
    byte   acc_cytime_a         ;
    char   acc_cytime           [5 + 1];
    byte   l_acc_cyday_a        ;
    char   l_acc_cyday          [48 + 1];
    byte   acc_cyday_a          ;
    char   acc_cyday            [3 + 1];
    byte   l_acc_cysize_a       ;
    char   l_acc_cysize         [37 + 1];
    byte   acc_cysize_a         ;
    char   acc_cysize           [6 + 1];
    byte   l_acc_cylines_a      ;
    char   l_acc_cylines        [48 + 1];
    byte   acc_cylines_a        ;
    char   acc_cylines          [9 + 1];
    byte   l_acc_cyhow_a        ;
    char   l_acc_cyhow          [38 + 1];
    byte   acc_cyhow_a          ;
    char   acc_cyhow            [3 + 1];
    byte   l_acc_cyarg_a        ;
    char   l_acc_cyarg          [40 + 1];
    byte   acc_cyarg_a          ;
    char   acc_cyarg            [80 + 1];
    byte   l_acc_xlate_a        ;
    char   l_acc_xlate          [35 + 1];
    byte   acc_xlate_a          ;
    char   acc_xlate            [1 + 1];
    byte   l_err_enabled_a      ;
    char   l_err_enabled        [27 + 1];
    byte   err_enabled_a        ;
    char   err_enabled          [1 + 1];
    byte   l_err_filename_a     ;
    char   l_err_filename       [32 + 1];
    byte   err_filename_a       ;
    char   err_filename         [80 + 1];
    byte   l_err_cycle_a        ;
    char   l_err_cycle          [18 + 1];
    byte   err_cycle_a          ;
    char   err_cycle            [3 + 1];
    byte   l_err_local_a        ;
    char   l_err_local          [36 + 1];
    byte   err_local_a          ;
    char   err_local            [1 + 1];
    byte   l_err_extended_a     ;
    char   l_err_extended       [36 + 1];
    byte   err_extended_a       ;
    char   err_extended         [1 + 1];
    byte   l_err_format_a       ;
    char   l_err_format         [28 + 1];
    byte   err_format_a         ;
    char   err_format           [3 + 1];
    byte   l_err_custom_a       ;
    char   l_err_custom         [35 + 1];
    byte   err_custom_a         ;
    char   err_custom           [512 + 1];
    byte   l_err_cyclex_a       ;
    char   l_err_cyclex         [18 + 1];
    byte   err_cyclex_a         ;
    char   err_cyclex           [3 + 1];
    byte   l_err_cytime_a       ;
    char   l_err_cytime         [34 + 1];
    byte   err_cytime_a         ;
    char   err_cytime           [5 + 1];
    byte   l_err_cyday_a        ;
    char   l_err_cyday          [48 + 1];
    byte   err_cyday_a          ;
    char   err_cyday            [3 + 1];
    byte   l_err_cysize_a       ;
    char   l_err_cysize         [37 + 1];
    byte   err_cysize_a         ;
    char   err_cysize           [6 + 1];
    byte   l_err_cylines_a      ;
    char   l_err_cylines        [48 + 1];
    byte   err_cylines_a        ;
    char   err_cylines          [9 + 1];
    byte   l_err_cyhow_a        ;
    char   l_err_cyhow          [38 + 1];
    byte   err_cyhow_a          ;
    char   err_cyhow            [3 + 1];
    byte   l_err_cyarg_a        ;
    char   l_err_cyarg          [40 + 1];
    byte   err_cyarg_a          ;
    char   err_cyarg            [80 + 1];
    byte   l_err_xlate_a        ;
    char   l_err_xlate          [35 + 1];
    byte   err_xlate_a          ;
    char   err_xlate            [1 + 1];
    byte   l_primary_a          ;
    char   l_primary            [34 + 1];
    byte   primary_a            ;
    char   primary              [20 + 1];
    byte   l_secondary_a        ;
    char   l_secondary          [34 + 1];
    byte   secondary_a          ;
    char   secondary            [20 + 1];
    byte   l_recurse_a          ;
    char   l_recurse            [36 + 1];
    byte   recurse_a            ;
    char   recurse              [1 + 1];
    byte   l_debug_a            ;
    char   l_debug              [38 + 1];
    byte   debug_a              ;
    char   debug                [1 + 1];
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
    byte   ftp_a;
    byte   mime_a;
    } XIADM08_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm08 = {
    xiadm08_blocks,
    xiadm08_fields,
    241,                                /*  Number of blocks in form        */
    79,                                 /*  Number of fields in form        */
    18,                                 /*  Number of actions in form       */
    3120,                               /*  Size of fields                  */
    "xiadm08",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
