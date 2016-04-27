/*---------------------------------------------------------------------------
 *  xiadm21.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM21__
#define __FORM_XIADM21__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM21_MESSAGE_TO_USER             0
#define XIADM21_REFRESH_ON                  1
#define XIADM21_L_DATE_STARTED              2
#define XIADM21_DATE_STARTED                3
#define XIADM21_L_TIME_STARTED              4
#define XIADM21_TIME_STARTED                5
#define XIADM21_L_SERVER_MESSAGE            6
#define XIADM21_SERVER_MESSAGE              7
#define XIADM21_L_HTTP_PORT                 8
#define XIADM21_HTTP_PORT                   9
#define XIADM21_L_FTP_PORT                  10
#define XIADM21_FTP_PORT                    11
#define XIADM21_L_CUR_CONNECTS              12
#define XIADM21_CUR_CONNECTS                13
#define XIADM21_L_MAX_CONNECTS              14
#define XIADM21_MAX_CONNECTS                15
#define XIADM21_L_CONNECT_COUNT             16
#define XIADM21_CONNECT_COUNT               17
#define XIADM21_L_ERROR_COUNT               18
#define XIADM21_ERROR_COUNT                 19
#define XIADM21_L_TRANSFER_SIZE             20
#define XIADM21_TRANSFER_SIZE               21
#define XIADM21_TRANSFER_UNIT               22

/*  This table contains each block in the form                               */

static byte xiadm21_blocks [] = {
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
    /*  !--ACTION clear  LABEL="/adm ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 35, 20, 2, (byte) ((word) clear_event / 256), (byte) ((word)
    clear_event & 255), 0, 1, 0, 0, 0, 0, 0, 'c', 'l', 'e', 'a', 'r', 0,
    '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'c', 'l', 'e', 'a', 'r',
    '.', 'g', 'i', 'f', 0,
    /*  !--ACTION refresh  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) refresh_event / 256), (byte) ((word)
    refresh_event & 255), 0, 2, 0, 0, 0, 0, 0, 'r', 'e', 'f', 'r', 'e',
    's', 'h', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'e', 'f',
    'r', 'e', 's', 'h', '.', 'g', 'i', 'f', 0,
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
    /*  <TD ALIGN=CENTER><FONT SIZE=+1>Server Console Panel </FONT>          */
    0, 61, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', 'S', 'e', 'r', 'v', 'e', 'r', 32, 'C', 'o',
    'n', 's', 'o', 'l', 'e', 32, 'P', 'a', 'n', 'e', 'l', 32, '<', '/',
    'F', 'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 1, 9,
    /*  !--ACTION console  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 3, 0, 0, 0, 0, 0, 'c', 'o', 'n', 's', 'o',
    'l', 'e', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'c', 'o', 'n',
    's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION halt  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 4, 0, 0, 0, 0, 0, 'h', 'a', 'l', 't', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION restart  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 5, 0, 0, 0, 0, 0, 'r', 'e', 's', 't', 'a',
    'r', 't', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'e', 's',
    't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION exit  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 6, 0, 0, 0, 0, 0, 'e', 'x', 'i', 't', 0, '/',
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
    0, 4, 1, 0, 2, 146,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, '{',
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  !--FIELD NUMERIC refresh_on SIZE=4 VALUE=1                           */
    0, 26, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'r', 'e', 'f', 'r',
    'e', 's', 'h', '_', 'o', 'n', 0, '1', 0,
    /*  !--IF refresh_on                                                     */
    0, 5, 2, 0, 1, 0, 1,
    /*  <META HTTP-EQUIV="REFRESH" CONTENT="#(rate)">                        */
    0, 47, 0, '<', 'M', 'E', 'T', 'A', 32, 'H', 'T', 'T', 'P', 45, 'E',
    'Q', 'U', 'I', 'V', '=', '"', 'R', 'E', 'F', 'R', 'E', 'S', 'H',
    '"', 32, 'C', 'O', 'N', 'T', 'E', 'N', 'T', '=', '"', '#', '(', 'r',
    'a', 't', 'e', ')', '"', '>', 10,
    /*  <TABLE WIDTH=100%>                                                   */
    0, 20, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 39, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', '>', 10,
    /*  !--FIELD TEXTUAL f359 NAME=L ... er started at:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '5', '9', 0, 'S', 'e',
    'r', 'v', 'e', 'r', 32, 's', 't', 'a', 'r', 't', 'e', 'd', 32, 'a',
    't', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 34, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I',
    'G', 'N', '=', 'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=',
    '"', '8', '0', '%', '"', '>', 10,
    /*  !--FIELD DATE f360 NAME=date ... AR=? MONTH=? DAY=? VALUE=""         */
    0, 17, 12, 0, 1, 0, 15, 0, 1, 0, 0, 0, 'f', '3', '6', '0', 0, 0, 0,
    /*  !--FIELD TEXTUAL f361 NAME=L_time-started VALUE=":"                  */
    0, 15, 10, 6, 1, 0, 0, 1, 0, 1, 'f', '3', '6', '1', 0, ':', 0,
    /*  !--FIELD TIME f362 NAME=time ... ss" SIZE=12 MAX=20 VALUE=""         */
    0, 20, 13, 0, 1, 0, 12, 'f', '3', '6', '2', 0, 0, 'h', 'h', ':',
    'm', 'm', ':', 's', 's', 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 134,
    /*  !--FIELD TEXTUAL f363 NAME=L ... error message:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '3', '6', '3', 0, 'L', 'a',
    's', 't', 32, 's', 'e', 'r', 'v', 'e', 'r', 32, 'e', 'r', 'r', 'o',
    'r', 32, 'm', 'e', 's', 's', 'a', 'g', 'e', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 221,
    /*  !--FIELD TEXTUAL f364 NAME=s ... E=80 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 'P', 0, 'P', 'f', '3', '6', '4', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, ';',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 134,
    /*  !--FIELD TEXTUAL f365 NAME=L ... ce is on port:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '3', '6', '5', 0, 'H', 'T',
    'T', 'P', 32, 's', 'e', 'r', 'v', 'i', 'c', 'e', 32, 'i', 's', 32,
    'o', 'n', 32, 'p', 'o', 'r', 't', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 221,
    /*  !--FIELD NUMERIC f366 NAME=h ... MMA=0 SIZE=5 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '3', '6', '6',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, ';',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 134,
    /*  !--FIELD TEXTUAL f367 NAME=L ... ce is on port:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '3', '6', '7', 0, 'F', 'T',
    'P', 32, 's', 'e', 'r', 'v', 'i', 'c', 'e', 32, 'i', 's', 32, 'o',
    'n', 32, 'p', 'o', 'r', 't', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 221,
    /*  !--FIELD NUMERIC f368 NAME=f ... MMA=0 SIZE=5 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '3', '6', '8',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, ';',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 134,
    /*  !--FIELD TEXTUAL f369 NAME=L ... n connections:&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, 39, 0, 39, 'f', '3', '6', '9', 0, 'N', 'u',
    'm', 'b', 'e', 'r', 32, 'o', 'f', 32, 'o', 'p', 'e', 'n', 32, 'c',
    'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', 's', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 221,
    /*  !--FIELD NUMERIC f370 NAME=c ... MMA=0 SIZE=6 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '3', '7', '0',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, ';',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 134,
    /*  !--FIELD TEXTUAL f371 NAME=L ... n connections:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '3', '7', '1', 0, 'H', 'i',
    'g', 'h', 'e', 's', 't', 32, 'o', 'p', 'e', 'n', 32, 'c', 'o', 'n',
    'n', 'e', 'c', 't', 'i', 'o', 'n', 's', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 221,
    /*  !--FIELD NUMERIC f372 NAME=m ... MMA=0 SIZE=6 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '3', '7', '2',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, ';',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 134,
    /*  !--FIELD TEXTUAL f373 NAME=L ... umber of hits:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '3', '7', '3', 0, 'T', 'o',
    't', 'a', 'l', 32, 'n', 'u', 'm', 'b', 'e', 'r', 32, 'o', 'f', 32,
    'h', 'i', 't', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 221,
    /*  !--FIELD NUMERIC f374 NAME=c ... MA=0 SIZE=10 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 10, 0, 10, 0, 0, 0, 0, 0, 0, 'f', '3', '7', '4',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, ';',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 134,
    /*  !--FIELD TEXTUAL f375 NAME=L ... ber of errors:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '3', '7', '5', 0, 'T', 'o',
    't', 'a', 'l', 32, 'n', 'u', 'm', 'b', 'e', 'r', 32, 'o', 'f', 32,
    'e', 'r', 'r', 'o', 'r', 's', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 221,
    /*  !--FIELD NUMERIC f376 NAME=e ... MA=0 SIZE=10 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 10, 0, 10, 0, 0, 0, 0, 0, 0, 'f', '3', '7', '6',
    0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, ';',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 134,
    /*  !--FIELD TEXTUAL f377 NAME=L ... ta transferred&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '3', '7', '7', 0, 'T', 'o',
    't', 'a', 'l', 32, 'd', 'a', 't', 'a', 32, 't', 'r', 'a', 'n', 's',
    'f', 'e', 'r', 'r', 'e', 'd', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 221,
    /*  !--FIELD NUMERIC f378 NAME=t ... MA=0 SIZE=10 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 10, 0, 10, 0, 0, 0, 0, 0, 0, 'f', '3', '7', '8',
    0, 0,
    /*  !--FIELD TEXTUAL f379 NAME=t ... ZE=5 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '3', '7', '9', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, ';',
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, '{',
    /*  <P>                                                                  */
    0, 5, 0, '<', 'P', '>', 10,
    /*  !--ACTION messages  LABEL="M ... =messages_event TYPE=BUTTON         */
    0, 32, 20, 0, (byte) ((word) messages_event / 256), (byte) ((word)
    messages_event & 255), 0, 7, 0, 0, 0, 0, 0, 'm', 'e', 's', 's', 'a',
    'g', 'e', 's', 0, 'M', 'e', 's', 's', 'a', 'g', 'e', 's', '.', '.',
    '.', 0,
    /*  !--ACTION details  LABEL="De ... T=details_event TYPE=BUTTON         */
    0, 30, 20, 0, (byte) ((word) details_event / 256), (byte) ((word)
    details_event & 255), 0, 8, 0, 0, 0, 0, 0, 'd', 'e', 't', 'a', 'i',
    'l', 's', 0, 'D', 'e', 't', 'a', 'i', 'l', 's', '.', '.', '.', 0,
    /*  !--ACTION preferences  LABEL ... NT=define_event TYPE=BUTTON         */
    0, 38, 20, 0, (byte) ((word) define_event / 256), (byte) ((word)
    define_event & 255), 0, 9, 0, 0, 0, 0, 0, 'p', 'r', 'e', 'f', 'e',
    'r', 'e', 'n', 'c', 'e', 's', 0, 'P', 'r', 'e', 'f', 'e', 'r', 'e',
    'n', 'c', 'e', 's', '.', '.', '.', 0,
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
    0, 4, 1, 0, 4, 20,
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
    0, 4, 1, 0, 3, '{',
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm21_fields [] = {
    { 0, 989, 80 },                     /*  message_to_user                 */
    { 82, 1052, 4 },                    /*  refresh_on                      */
    { 88, 1199, 30 },                   /*  l_date_started                  */
    { 120, 1281, 8 },                   /*  date_started                    */
    { 130, 1300, 1 },                   /*  l_time_started                  */
    { 133, 1317, 8 },                   /*  time_started                    */
    { 143, 1359, 38 },                  /*  l_server_message                */
    { 183, 1419, 80 },                  /*  server_message                  */
    { 265, 1447, 36 },                  /*  l_http_port                     */
    { 303, 1505, 5 },                   /*  http_port                       */
    { 310, 1538, 35 },                  /*  l_ftp_port                      */
    { 347, 1595, 5 },                   /*  ftp_port                        */
    { 354, 1628, 39 },                  /*  l_cur_connects                  */
    { 395, 1689, 6 },                   /*  cur_connects                    */
    { 403, 1722, 37 },                  /*  l_max_connects                  */
    { 442, 1781, 6 },                   /*  max_connects                    */
    { 450, 1814, 33 },                  /*  l_connect_count                 */
    { 485, 1869, 10 },                  /*  connect_count                   */
    { 497, 1902, 35 },                  /*  l_error_count                   */
    { 534, 1959, 10 },                  /*  error_count                     */
    { 546, 1992, 34 },                  /*  l_transfer_size                 */
    { 582, 2048, 10 },                  /*  transfer_size                   */
    { 594, 2069, 5 },                   /*  transfer_unit                   */
    { 601, 0, 0 },                      /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   refresh_on_a         ;
    char   refresh_on           [4 + 1];
    byte   l_date_started_a     ;
    char   l_date_started       [30 + 1];
    byte   date_started_a       ;
    char   date_started         [8 + 1];
    byte   l_time_started_a     ;
    char   l_time_started       [1 + 1];
    byte   time_started_a       ;
    char   time_started         [8 + 1];
    byte   l_server_message_a   ;
    char   l_server_message     [38 + 1];
    byte   server_message_a     ;
    char   server_message       [80 + 1];
    byte   l_http_port_a        ;
    char   l_http_port          [36 + 1];
    byte   http_port_a          ;
    char   http_port            [5 + 1];
    byte   l_ftp_port_a         ;
    char   l_ftp_port           [35 + 1];
    byte   ftp_port_a           ;
    char   ftp_port             [5 + 1];
    byte   l_cur_connects_a     ;
    char   l_cur_connects       [39 + 1];
    byte   cur_connects_a       ;
    char   cur_connects         [6 + 1];
    byte   l_max_connects_a     ;
    char   l_max_connects       [37 + 1];
    byte   max_connects_a       ;
    char   max_connects         [6 + 1];
    byte   l_connect_count_a    ;
    char   l_connect_count      [33 + 1];
    byte   connect_count_a      ;
    char   connect_count        [10 + 1];
    byte   l_error_count_a      ;
    char   l_error_count        [35 + 1];
    byte   error_count_a        ;
    char   error_count          [10 + 1];
    byte   l_transfer_size_a    ;
    char   l_transfer_size      [34 + 1];
    byte   transfer_size_a      ;
    char   transfer_size        [10 + 1];
    byte   transfer_unit_a      ;
    char   transfer_unit        [5 + 1];
    byte   back_a;
    byte   clear_a;
    byte   refresh_a;
    byte   console_a;
    byte   halt_a;
    byte   restart_a;
    byte   exit_a;
    byte   messages_a;
    byte   details_a;
    byte   preferences_a;
    } XIADM21_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm21 = {
    xiadm21_blocks,
    xiadm21_fields,
    100,                                /*  Number of blocks in form        */
    23,                                 /*  Number of fields in form        */
    10,                                 /*  Number of actions in form       */
    601,                                /*  Size of fields                  */
    "xiadm21",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
