/*---------------------------------------------------------------------------
 *  xiadm23.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM23__
#define __FORM_XIADM23__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM23_MESSAGE_TO_USER             0
#define XIADM23_L_STARTUP                   1
#define XIADM23_STARTUP                     2
#define XIADM23_L_REFRESH_FLAG              3
#define XIADM23_REFRESH_FLAG                4
#define XIADM23_L_REFRESH_RATE              5
#define XIADM23_REFRESH_RATE                6
#define XIADM23_L_CAPTURE                   7
#define XIADM23_CAPTURE                     8
#define XIADM23_L_FILENAME                  9
#define XIADM23_FILENAME                    10
#define XIADM23_L_APPEND                    11
#define XIADM23_APPEND                      12
#define XIADM23_L_JAVASCRIPT                13
#define XIADM23_JAVASCRIPT                  14
#define XIADM23_L_LARGE_ICONS               15
#define XIADM23_LARGE_ICONS                 16

/*  This table contains each block in the form                               */

static byte xiadm23_blocks [] = {
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
    /*  <TD ALIGN=CENTER><FONT SIZE=+1>Console Preferences </FONT>           */
    0, 60, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', 'C', 'o', 'n', 's', 'o', 'l', 'e', 32, 'P',
    'r', 'e', 'f', 'e', 'r', 'e', 'n', 'c', 'e', 's', 32, '<', '/', 'F',
    'O', 'N', 'T', '>', 10,
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
    0, 4, 1, 0, 2, 178,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 155,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  <TABLE WIDTH=100%>                                                   */
    0, 20, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 39, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', '>', 10,
    /*  !--FIELD TEXTUAL f380 NAME=L ... Start-up page:&nbsp;&nbsp;"         */
    0, 40, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '3', '8', '0', 0, 'S', 't',
    'a', 'r', 't', 45, 'u', 'p', 32, 'p', 'a', 'g', 'e', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 34, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I',
    'G', 'N', '=', 'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=',
    '"', '8', '0', '%', '"', '>', 10,
    /*  !--FIELD RADIO f381 NAME=sta ... 0 DETAIL=0 VALUE=0 NULL="?"         */
    0, 25, 17, 0, 1, 0, 0, 'f', '3', '8', '1', 0, '0', 0, 'N', 'o', 32,
    's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  !--FIELD RADIO f381 OPTION="Main menu"                               */
    0, 14, 18, 4, 201, 1, 'M', 'a', 'i', 'n', 32, 'm', 'e', 'n', 'u', 0,
    /*  !--FIELD RADIO f381 OPTION="Basic config"                            */
    0, 17, 18, 4, 201, 2, 'B', 'a', 's', 'i', 'c', 32, 'c', 'o', 'n',
    'f', 'i', 'g', 0,
    /*  !--FIELD RADIO f381 OPTION="VHost config"                            */
    0, 17, 18, 4, 201, 3, 'V', 'H', 'o', 's', 't', 32, 'c', 'o', 'n',
    'f', 'i', 'g', 0,
    /*  !--FIELD RADIO f381 OPTION="Console page"                            */
    0, 17, 18, 4, 201, 4, 'C', 'o', 'n', 's', 'o', 'l', 'e', 32, 'p',
    'a', 'g', 'e', 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 'R',
    /*  !--FIELD TEXTUAL f382 NAME=L ... matic refresh?&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '8', '2', 0, 'A', 'u',
    't', 'o', 'm', 'a', 't', 'i', 'c', 32, 'r', 'e', 'f', 'r', 'e', 's',
    'h', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 165,
    /*  !--FIELD BOOLEAN f383 NAME=r ... g TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '8', '3', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, 45,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 'R',
    /*  !--FIELD TEXTUAL f384 NAME=L ... refresh every:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '3', '8', '4', 0, 32, 45, 32,
    'r', 'e', 'f', 'r', 'e', 's', 'h', 32, 'e', 'v', 'e', 'r', 'y', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 165,
    /*  !--FIELD NUMERIC f385 NAME=r ... MMA=0 SIZE=5 MAX=? VALUE=""         */
    0, 19, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '3', '8', '5',
    0, 0,
    /*  seconds                                                              */
    0, 9, 0, 's', 'e', 'c', 'o', 'n', 'd', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, 45,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 'R',
    /*  !--FIELD TEXTUAL f386 NAME=L ... pture console?&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '3', '8', '6', 0, 'C', 'a',
    'p', 't', 'u', 'r', 'e', 32, 'c', 'o', 'n', 's', 'o', 'l', 'e', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 165,
    /*  !--FIELD BOOLEAN f387 NAME=capture TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '8', '7', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, 45,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 'R',
    /*  !--FIELD TEXTUAL f388 NAME=L ... pture to file:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '3', '8', '8', 0, 32, 45, 32,
    'c', 'a', 'p', 't', 'u', 'r', 'e', 32, 't', 'o', 32, 'f', 'i', 'l',
    'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 165,
    /*  !--FIELD TEXTUAL f389 NAME=f ... =30 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '3', '8', '9', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, 45,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 'R',
    /*  !--FIELD TEXTUAL f390 NAME=L ... - append data?&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '3', '9', '0', 0, 32, 45, 32,
    'a', 'p', 'p', 'e', 'n', 'd', 32, 'd', 'a', 't', 'a', '?', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 165,
    /*  !--FIELD BOOLEAN f391 NAME=append TRUE=yes FALSE=no VALUE=0          */
    0, 17, 15, 0, 1, 'f', '3', '9', '1', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, 45,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 'R',
    /*  !--FIELD TEXTUAL f392 NAME=L ... se JavaScript?&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '3', '9', '2', 0, 'U', 's',
    'e', 32, 'J', 'a', 'v', 'a', 'S', 'c', 'r', 'i', 'p', 't', '?', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 165,
    /*  !--FIELD BOOLEAN f393 NAME=j ... t TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '9', '3', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, 45,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 'R',
    /*  !--FIELD TEXTUAL f394 NAME=L ... w large icons?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '3', '9', '4', 0, 'S', 'h',
    'o', 'w', 32, 'l', 'a', 'r', 'g', 'e', 32, 'i', 'c', 'o', 'n', 's',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 165,
    /*  !--FIELD BOOLEAN f395 NAME=l ... s TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '9', '5', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  Flush browser cache when changing this                               */
    0, 40, 0, 'F', 'l', 'u', 's', 'h', 32, 'b', 'r', 'o', 'w', 's', 'e',
    'r', 32, 'c', 'a', 'c', 'h', 'e', 32, 'w', 'h', 'e', 'n', 32, 'c',
    'h', 'a', 'n', 'g', 'i', 'n', 'g', 32, 't', 'h', 'i', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 5, 45,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 155,
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
    0, 4, 1, 0, 4, '4',
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
    0, 4, 1, 0, 3, 155,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm23_fields [] = {
    { 0, 1021, 80 },                    /*  message_to_user                 */
    { 82, 1147, 26 },                   /*  l_startup                       */
    { 110, 1225, 3 },                   /*  startup                         */
    { 115, 1345, 30 },                  /*  l_refresh_flag                  */
    { 147, 1397, 1 },                   /*  refresh_flag                    */
    { 150, 1428, 29 },                  /*  l_refresh_rate                  */
    { 181, 1479, 5 },                   /*  refresh_rate                    */
    { 188, 1523, 28 },                  /*  l_capture                       */
    { 218, 1573, 1 },                   /*  capture                         */
    { 221, 1604, 31 },                  /*  l_filename                      */
    { 254, 1657, 80 },                  /*  filename                        */
    { 336, 1685, 27 },                  /*  l_append                        */
    { 365, 1734, 1 },                   /*  append                          */
    { 368, 1765, 27 },                  /*  l_javascript                    */
    { 397, 1814, 1 },                   /*  javascript                      */
    { 400, 1845, 29 },                  /*  l_large_icons                   */
    { 431, 1896, 1 },                   /*  large_icons                     */
    { 434, 0, 0 },                      /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   l_startup_a          ;
    char   l_startup            [26 + 1];
    byte   startup_a            ;
    char   startup              [3 + 1];
    byte   l_refresh_flag_a     ;
    char   l_refresh_flag       [30 + 1];
    byte   refresh_flag_a       ;
    char   refresh_flag         [1 + 1];
    byte   l_refresh_rate_a     ;
    char   l_refresh_rate       [29 + 1];
    byte   refresh_rate_a       ;
    char   refresh_rate         [5 + 1];
    byte   l_capture_a          ;
    char   l_capture            [28 + 1];
    byte   capture_a            ;
    char   capture              [1 + 1];
    byte   l_filename_a         ;
    char   l_filename           [31 + 1];
    byte   filename_a           ;
    char   filename             [80 + 1];
    byte   l_append_a           ;
    char   l_append             [27 + 1];
    byte   append_a             ;
    char   append               [1 + 1];
    byte   l_javascript_a       ;
    char   l_javascript         [27 + 1];
    byte   javascript_a         ;
    char   javascript           [1 + 1];
    byte   l_large_icons_a      ;
    char   l_large_icons        [29 + 1];
    byte   large_icons_a        ;
    char   large_icons          [1 + 1];
    byte   back_a;
    byte   save_a;
    byte   default_a;
    byte   undo_a;
    byte   console_a;
    byte   halt_a;
    byte   restart_a;
    byte   exit_a;
    } XIADM23_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm23 = {
    xiadm23_blocks,
    xiadm23_fields,
    92,                                 /*  Number of blocks in form        */
    17,                                 /*  Number of fields in form        */
    8,                                  /*  Number of actions in form       */
    434,                                /*  Size of fields                  */
    "xiadm23",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
