/*---------------------------------------------------------------------------
 *  xiadm10.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM10__
#define __FORM_XIADM10__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM10_MESSAGE_TO_USER             0
#define XIADM10_FILLER                      1
#define XIADM10_L_ERROR_HEADER              2
#define XIADM10_ERROR_HEADER                3
#define XIADM10_L_TEXT_400                  4
#define XIADM10_TEXT_400                    5
#define XIADM10_L_TEXT_401                  6
#define XIADM10_TEXT_401                    7
#define XIADM10_L_TEXT_402                  8
#define XIADM10_TEXT_402                    9
#define XIADM10_L_TEXT_403                  10
#define XIADM10_TEXT_403                    11
#define XIADM10_L_TEXT_404                  12
#define XIADM10_TEXT_404                    13
#define XIADM10_L_TEXT_412                  14
#define XIADM10_TEXT_412                    15
#define XIADM10_L_TEXT_413                  16
#define XIADM10_TEXT_413                    17
#define XIADM10_L_TEXT_500                  18
#define XIADM10_TEXT_500                    19
#define XIADM10_L_TEXT_501                  20
#define XIADM10_TEXT_501                    21
#define XIADM10_L_TEXT_502                  22
#define XIADM10_TEXT_502                    23
#define XIADM10_L_ERROR_FOOTER              24
#define XIADM10_ERROR_FOOTER                25

/*  This table contains each block in the form                               */

static byte xiadm10_blocks [] = {
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ... mised Error Messages </FONT>        */
    0, 78, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'C', 'u', 's', 't', 'o', 'm', 'i', 's', 'e', 'd',
    32, 'E', 'r', 'r', 'o', 'r', 32, 'M', 'e', 's', 's', 'a', 'g', 'e',
    's', 32, '<', '/', 'F', 'O', 'N', 'T', '>', 10,
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
    0, 4, 1, 0, 2, 196,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 173,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  <TABLE WIDTH=100%>                                                   */
    0, 20, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <TR><TD></TD><TD ALIGN=LEFT WIDTH="80%">                             */
    0, 42, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E',
    'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '8', '0', '%', '"',
    '>', 10,
    /*  !--FIELD TEXTUAL f218 NAME=f ... E="HTML text or @filename:"         */
    0, 37, 10, 7, 1, 0, 0, 23, 0, 23, 'f', '2', '1', '8', 0, 'H', 'T',
    'M', 'L', 32, 't', 'e', 'x', 't', 32, 'o', 'r', 32, '@', 'f', 'i',
    'l', 'e', 'n', 'a', 'm', 'e', ':', 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 39, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', '>', 10,
    /*  !--FIELD TEXTUAL f219 NAME=L ... er for errors:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '1', '9', 0, 'H', 'e',
    'a', 'd', 'e', 'r', 32, 'f', 'o', 'r', 32, 'e', 'r', 'r', 'o', 'r',
    's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 34, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I',
    'G', 'N', '=', 'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=',
    '"', '8', '0', '%', '"', '>', 10,
    /*  !--FIELD TEXTBOX f220 NAME=e ... 60 MAX=240 UPPER=0 VALUE=""         */
    0, 14, 14, 0, 1, 2, '<', 0, 0, 240, 'f', '2', '2', '0', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f221 NAME=L ... - Bad request:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '2', '1', 0, '4', '0',
    '0', 32, 45, 32, 'B', 'a', 'd', 32, 'r', 'e', 'q', 'u', 'e', 's',
    't', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f222 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '2', '2', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f223 NAME=L ...  Unauthorized:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '2', '2', '3', 0, '4', '0',
    '1', 32, 45, 32, 'U', 'n', 'a', 'u', 't', 'h', 'o', 'r', 'i', 'z',
    'e', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f224 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '2', '4', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f225 NAME=L ... ment required:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '2', '2', '5', 0, '4', '0',
    '2', 32, 45, 32, 'P', 'a', 'y', 'm', 'e', 'n', 't', 32, 'r', 'e',
    'q', 'u', 'i', 'r', 'e', 'd', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f226 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '2', '6', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f227 NAME=L ... 3 - Forbidden:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '2', '2', '7', 0, '4', '0',
    '3', 32, 45, 32, 'F', 'o', 'r', 'b', 'i', 'd', 'd', 'e', 'n', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f228 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '2', '8', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f229 NAME=L ... 4 - Not found:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '2', '2', '9', 0, '4', '0',
    '4', 32, 45, 32, 'N', 'o', 't', 32, 'f', 'o', 'u', 'n', 'd', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f230 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '3', '0', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f231 NAME=L ... dition failed:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '2', '3', '1', 0, '4', '1',
    '2', 32, 45, 32, 'P', 'r', 'e', 'c', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 32, 'f', 'a', 'i', 'l', 'e', 'd', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f232 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '3', '2', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f233 NAME=L ... ity too large:&nbsp;&nbsp;"         */
    0, 57, 10, 6, 1, 0, 0, '+', 0, '+', 'f', '2', '3', '3', 0, '4', '1',
    '3', 32, 45, 32, 'R', 'e', 'q', 'u', 'e', 's', 't', 32, 'e', 'n',
    't', 'i', 't', 'y', 32, 't', 'o', 'o', 32, 'l', 'a', 'r', 'g', 'e',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f234 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '3', '4', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f235 NAME=L ... nternal error:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '2', '3', '5', 0, '5', '0',
    '0', 32, 45, 32, 'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', 32, 'e',
    'r', 'r', 'o', 'r', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f236 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '3', '6', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f237 NAME=L ... t implemented:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '2', '3', '7', 0, '5', '0',
    '1', 32, 45, 32, 'N', 'o', 't', 32, 'i', 'm', 'p', 'l', 'e', 'm',
    'e', 'n', 't', 'e', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f238 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '3', '8', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f239 NAME=L ... y unavailable:&nbsp;&nbsp;"         */
    0, 64, 10, 6, 1, 0, 0, '2', 0, '2', 'f', '2', '3', '9', 0, '5', '0',
    '2', 32, 45, 32, 'S', 'e', 'r', 'v', 'i', 'c', 'e', 32, 't', 'e',
    'm', 'p', 'o', 'r', 'a', 'r', 'i', 'l', 'y', 32, 'u', 'n', 'a', 'v',
    'a', 'i', 'l', 'a', 'b', 'l', 'e', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTUAL f240 NAME=t ... E=60 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '2', '4', '0', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 197,
    /*  !--FIELD TEXTUAL f241 NAME=L ... er for errors:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '4', '1', 0, 'F', 'o',
    'o', 't', 'e', 'r', 32, 'f', 'o', 'r', 32, 'e', 'r', 'r', 'o', 'r',
    's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 5, 28,
    /*  !--FIELD TEXTBOX f242 NAME=e ... 60 MAX=240 UPPER=0 VALUE=""         */
    0, 14, 14, 0, 1, 2, '<', 0, 0, 240, 'f', '2', '4', '2', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 183,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, 173,
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
    0, 4, 1, 0, 4, 'F',
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
    0, 4, 1, 0, 3, 173,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm10_fields [] = {
    { 0, 1039, 80 },                    /*  message_to_user                 */
    { 82, 1168, 23 },                   /*  filler                          */
    { 107, 1262, 30 },                  /*  l_error_header                  */
    { 139, 1344, 240 },                 /*  error_header                    */
    { 381, 1372, 30 },                  /*  l_text_400                      */
    { 413, 1424, 60 },                  /*  text_400                        */
    { 475, 1452, 31 },                  /*  l_text_401                      */
    { 508, 1505, 60 },                  /*  text_401                        */
    { 570, 1533, 35 },                  /*  l_text_402                      */
    { 607, 1590, 60 },                  /*  text_402                        */
    { 669, 1618, 28 },                  /*  l_text_403                      */
    { 699, 1668, 60 },                  /*  text_403                        */
    { 761, 1696, 28 },                  /*  l_text_404                      */
    { 791, 1746, 60 },                  /*  text_404                        */
    { 853, 1774, 38 },                  /*  l_text_412                      */
    { 893, 1834, 60 },                  /*  text_412                        */
    { 955, 1862, 43 },                  /*  l_text_413                      */
    { 1000, 1927, 60 },                 /*  text_413                        */
    { 1062, 1955, 33 },                 /*  l_text_500                      */
    { 1097, 2010, 60 },                 /*  text_500                        */
    { 1159, 2038, 34 },                 /*  l_text_501                      */
    { 1195, 2094, 60 },                 /*  text_501                        */
    { 1257, 2122, 50 },                 /*  l_text_502                      */
    { 1309, 2194, 60 },                 /*  text_502                        */
    { 1371, 2222, 30 },                 /*  l_error_footer                  */
    { 1403, 2274, 240 },                /*  error_footer                    */
    { 1645, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   filler_a             ;
    char   filler               [23 + 1];
    byte   l_error_header_a     ;
    char   l_error_header       [30 + 1];
    byte   error_header_a       ;
    char   error_header         [240 + 1];
    byte   l_text_400_a         ;
    char   l_text_400           [30 + 1];
    byte   text_400_a           ;
    char   text_400             [60 + 1];
    byte   l_text_401_a         ;
    char   l_text_401           [31 + 1];
    byte   text_401_a           ;
    char   text_401             [60 + 1];
    byte   l_text_402_a         ;
    char   l_text_402           [35 + 1];
    byte   text_402_a           ;
    char   text_402             [60 + 1];
    byte   l_text_403_a         ;
    char   l_text_403           [28 + 1];
    byte   text_403_a           ;
    char   text_403             [60 + 1];
    byte   l_text_404_a         ;
    char   l_text_404           [28 + 1];
    byte   text_404_a           ;
    char   text_404             [60 + 1];
    byte   l_text_412_a         ;
    char   l_text_412           [38 + 1];
    byte   text_412_a           ;
    char   text_412             [60 + 1];
    byte   l_text_413_a         ;
    char   l_text_413           [43 + 1];
    byte   text_413_a           ;
    char   text_413             [60 + 1];
    byte   l_text_500_a         ;
    char   l_text_500           [33 + 1];
    byte   text_500_a           ;
    char   text_500             [60 + 1];
    byte   l_text_501_a         ;
    char   l_text_501           [34 + 1];
    byte   text_501_a           ;
    char   text_501             [60 + 1];
    byte   l_text_502_a         ;
    char   l_text_502           [50 + 1];
    byte   text_502_a           ;
    char   text_502             [60 + 1];
    byte   l_error_footer_a     ;
    char   l_error_footer       [30 + 1];
    byte   error_footer_a       ;
    char   error_footer         [240 + 1];
    byte   back_a;
    byte   save_a;
    byte   default_a;
    byte   undo_a;
    byte   console_a;
    byte   halt_a;
    byte   restart_a;
    byte   exit_a;
    } XIADM10_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm10 = {
    xiadm10_blocks,
    xiadm10_fields,
    109,                                /*  Number of blocks in form        */
    26,                                 /*  Number of fields in form        */
    8,                                  /*  Number of actions in form       */
    1645,                               /*  Size of fields                  */
    "xiadm10",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
