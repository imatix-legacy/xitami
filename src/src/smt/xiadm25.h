/*---------------------------------------------------------------------------
 *  xiadm25.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM25__
#define __FORM_XIADM25__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM25_MESSAGE_TO_USER             0
#define XIADM25_L_HOST_FILE                 1
#define XIADM25_HOST_FILE                   2
#define XIADM25_L_OVERWRITE                 3
#define XIADM25_OVERWRITE                   4
#define XIADM25_L_HOST_ADDR                 5
#define XIADM25_HOST_ADDR                   6
#define XIADM25_L_HOST_NAME                 7
#define XIADM25_HOST_NAME                   8
#define XIADM25_L_WEBPAGES                  9
#define XIADM25_WEBPAGES                    10
#define XIADM25_L_CGI_BIN                   11
#define XIADM25_CGI_BIN                     12
#define XIADM25_L_FTPROOT                   13
#define XIADM25_FTPROOT                     14
#define XIADM25_L_MAKEDIRS                  15
#define XIADM25_MAKEDIRS                    16
#define XIADM25_L_SUPERUSER                 17
#define XIADM25_SUPERUSER                   18
#define XIADM25_L_SHARELOGS                 19
#define XIADM25_SHARELOGS                   20
#define XIADM25_L_USE_ADMIN                 21
#define XIADM25_USE_ADMIN                   22
#define XIADM25_L_ADMIN_USER                23
#define XIADM25_ADMIN_USER                  24
#define XIADM25_L_ADMIN_PASS                25
#define XIADM25_ADMIN_PASS                  26

/*  This table contains each block in the form                               */

static byte xiadm25_blocks [] = {
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
    /*  <TD ALIGN=CENTER><FONT SIZE=+1>Virtual Host Wizard </FONT>           */
    0, 60, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', 'V', 'i', 'r', 't', 'u', 'a', 'l', 32, 'H',
    'o', 's', 't', 32, 'W', 'i', 'z', 'a', 'r', 'd', 32, '<', '/', 'F',
    'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 1, 9,
    /*  !--ACTION console  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 1, 0, 0, 0, 0, 0, 'c', 'o', 'n', 's', 'o',
    'l', 'e', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'c', 'o', 'n',
    's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION halt  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 2, 0, 0, 0, 0, 0, 'h', 'a', 'l', 't', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION restart  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 3, 0, 0, 0, 0, 0, 'r', 'e', 's', 't', 'a',
    'r', 't', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'e', 's',
    't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION exit  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 4, 0, 0, 0, 0, 0, 'e', 'x', 'i', 't', 0, '/',
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
    0, 4, 1, 0, 2, 'C',
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, ',',
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  <H2><A NAME="TOC2">Virtual Host Wizard</A></H2>                      */
    0, 49, 0, '<', 'H', '2', '>', '<', 'A', 32, 'N', 'A', 'M', 'E', '=',
    '"', 'T', 'O', 'C', '2', '"', '>', 'V', 'i', 'r', 't', 'u', 'a',
    'l', 32, 'H', 'o', 's', 't', 32, 'W', 'i', 'z', 'a', 'r', 'd', '<',
    '/', 'A', '>', '<', '/', 'H', '2', '>', 10,
    /*  <TABLE WIDTH=100%>                                                   */
    0, 20, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 39, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', '>', 10,
    /*  !--FIELD TEXTUAL f402 NAME=L ...  host profile:&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '4', '0', '2', 0, 'C', 'r',
    'e', 'a', 't', 'e', 32, 'v', 'i', 'r', 't', 'u', 'a', 'l', 32, 'h',
    'o', 's', 't', 32, 'p', 'r', 'o', 'f', 'i', 'l', 'e', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 34, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I',
    'G', 'N', '=', 'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=',
    '"', '8', '0', '%', '"', '>', 10,
    /*  !--FIELD TEXTUAL f403 NAME=h ... =30 MAX=80 UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '4', '0', '3', 0, 0,
    /*  .cfg extension is assumed                                            */
    0, 27, 0, '.', 'c', 'f', 'g', 32, 'e', 'x', 't', 'e', 'n', 's', 'i',
    'o', 'n', 32, 'i', 's', 32, 'a', 's', 's', 'u', 'm', 'e', 'd', 10,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f404 NAME=L ... rite existing?&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '4', '0', '4', 0, 'O', 'v',
    'e', 'r', 'w', 'r', 'i', 't', 'e', 32, 'e', 'x', 'i', 's', 't', 'i',
    'n', 'g', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD BOOLEAN f405 NAME=o ... e TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '4', '0', '5', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  <TR><TD></TD><TD>                                                    */
    0, 19, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', '>', 10,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 3, 197,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f406 NAME=L ... ct IP address:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '4', '0', '6', 0, 'S', 'e',
    'l', 'e', 'c', 't', 32, 'I', 'P', 32, 'a', 'd', 'd', 'r', 'e', 's',
    's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD SELECT f407 NAME=ho ... pe=dynamic 0="No selection"         */
    0, 25, 16, 0, 1, 1, 0, 'f', '4', '0', '7', 0, '0', 0, 'N', 'o', 32,
    's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f408 NAME=L ... DNS host name:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '4', '0', '8', 0, 'O', 'r',
    ',', 32, 'e', 'n', 't', 'e', 'r', 32, 'D', 'N', 'S', 32, 'h', 'o',
    's', 't', 32, 'n', 'a', 'm', 'e', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD TEXTUAL f409 NAME=h ... E=50 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '4', '0', '9', 0, 0,
    /*  <TR><TD></TD><TD>                                                    */
    0, 4, 1, 0, 5, '$',
    /*  <HR>                                                                 */
    0, 4, 1, 0, 3, 197,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f410 NAME=L ... oot directory:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '4', '1', '0', 0, 'W', 'e',
    'b', 32, 'p', 'a', 'g', 'e', 32, 'r', 'o', 'o', 't', 32, 'd', 'i',
    'r', 'e', 'c', 't', 'o', 'r', 'y', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD TEXTUAL f411 NAME=w ... E=50 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '4', '1', '1', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f412 NAME=L ... bin directory:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '4', '1', '2', 0, 'C', 'G',
    'I', 45, 'b', 'i', 'n', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r',
    'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD TEXTUAL f413 NAME=c ... E=50 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '4', '1', '3', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f414 NAME=L ... oot directory:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '4', '1', '4', 0, 'F', 'T',
    'P', 32, 'r', 'o', 'o', 't', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o',
    'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD TEXTUAL f415 NAME=f ... E=50 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '4', '1', '5', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f416 NAME=L ...  if necessary?&nbsp;&nbsp;"         */
    0, 58, 10, 6, 1, 0, 0, ',', 0, ',', 'f', '4', '1', '6', 0, 'C', 'r',
    'e', 'a', 't', 'e', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'i',
    'e', 's', 32, 'i', 'f', 32, 'n', 'e', 'c', 'e', 's', 's', 'a', 'r',
    'y', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD BOOLEAN f417 NAME=makedirs TRUE=yes FALSE=no VALUE=0        */
    0, 17, 15, 0, 1, 'f', '4', '1', '7', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f418 NAME=L ... user password:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '4', '1', '8', 0, 'S', 'u',
    'p', 'e', 'r', 'u', 's', 'e', 'r', 32, 'p', 'a', 's', 's', 'w', 'o',
    'r', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD TEXTUAL f419 NAME=s ... E=20 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '4', '1', '9', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f420 NAME=L ... ared logfiles?&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '4', '2', '0', 0, 'U', 's',
    'e', 's', 32, 's', 'h', 'a', 'r', 'e', 'd', 32, 'l', 'o', 'g', 'f',
    'i', 'l', 'e', 's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD BOOLEAN f421 NAME=s ... s TRUE=yes FALSE=no VALUE=0         */
    0, 17, 15, 0, 1, 'f', '4', '2', '1', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f422 NAME=L ... r-Based Admin?&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '4', '2', '2', 0, 'C', 'a',
    'n', 32, 'u', 's', 'e', 32, 'B', 'r', 'o', 'w', 's', 'e', 'r', 45,
    'B', 'a', 's', 'e', 'd', 32, 'A', 'd', 'm', 'i', 'n', '?', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD BOOLEAN f423 NAME=u ...  TRUE=yes FALSE=no VALUE=no         */
    0, 17, 15, 0, 1, 'f', '4', '2', '3', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f424 NAME=L ... f so, user id:&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '4', '2', '4', 0, 'I', 'f',
    32, 's', 'o', ',', 32, 'u', 's', 'e', 'r', 32, 'i', 'd', ':', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD TEXTUAL f425 NAME=a ... E=20 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '4', '2', '5', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP>                                */
    0, 4, 1, 0, 4, 22,
    /*  !--FIELD TEXTUAL f426 NAME=L ... "and password:&nbsp;&nbsp;"         */
    0, 39, 10, 6, 1, 0, 0, 25, 0, 25, 'f', '4', '2', '6', 0, 'a', 'n',
    'd', 32, 'p', 'a', 's', 's', 'w', 'o', 'r', 'd', ':', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    /*  </TD><TD ALIGN=LEFT WIDTH="80%">                                     */
    0, 4, 1, 0, 4, 'w',
    /*  !--FIELD TEXTUAL f427 NAME=a ... E=20 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '4', '2', '7', 0, 0,
    /*  <TR><TD></TD><TD>                                                    */
    0, 4, 1, 0, 5, '$',
    /*  <P>                                                                  */
    0, 5, 0, '<', 'P', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  <TR><TD></TD><TD ALIGN=LEFT WIDTH="80%">                             */
    0, 42, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E',
    'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '8', '0', '%', '"',
    '>', 10,
    /*  !--ACTION create  LABEL="Cre ... NT=define_event TYPE=BUTTON         */
    0, 25, 20, 0, (byte) ((word) define_event / 256), (byte) ((word)
    define_event & 255), 0, 5, 0, 0, 0, 0, 0, 'c', 'r', 'e', 'a', 't',
    'e', 0, 'C', 'r', 'e', 'a', 't', 'e', 0,
    /*  !--ACTION cancel  LABEL="Cancel" EVENT=back_event TYPE=BUTTON        */
    0, 25, 20, 0, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 6, 0, 0, 0, 0, 0, 'c', 'a', 'n', 'c', 'e',
    'l', 0, 'C', 'a', 'n', 'c', 'e', 'l', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 200,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, ',',
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
    0, 4, 1, 0, 3, 197,
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
    0, 4, 1, 0, 3, ',',
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm25_fields [] = {
    { 0, 910, 80 },                     /*  message_to_user                 */
    { 82, 1087, 40 },                   /*  l_host_file                     */
    { 124, 1179, 80 },                  /*  host_file                       */
    { 206, 1244, 31 },                  /*  l_overwrite                     */
    { 239, 1297, 1 },                   /*  overwrite                       */
    { 242, 1355, 30 },                  /*  l_host_addr                     */
    { 274, 1407, 3 },                   /*  host_addr                       */
    { 279, 1446, 36 },                  /*  l_host_name                     */
    { 317, 1504, 50 },                  /*  host_name                       */
    { 369, 1544, 36 },                  /*  l_webpages                      */
    { 407, 1602, 50 },                  /*  webpages                        */
    { 459, 1630, 30 },                  /*  l_cgi_bin                       */
    { 491, 1682, 50 },                  /*  cgi_bin                         */
    { 543, 1710, 31 },                  /*  l_ftproot                       */
    { 576, 1763, 50 },                  /*  ftproot                         */
    { 628, 1791, 44 },                  /*  l_makedirs                      */
    { 674, 1857, 1 },                   /*  makedirs                        */
    { 677, 1888, 31 },                  /*  l_superuser                     */
    { 710, 1941, 20 },                  /*  superuser                       */
    { 732, 1969, 33 },                  /*  l_sharelogs                     */
    { 767, 2024, 1 },                   /*  sharelogs                       */
    { 770, 2055, 40 },                  /*  l_use_admin                     */
    { 812, 2117, 1 },                   /*  use_admin                       */
    { 815, 2148, 27 },                  /*  l_admin_user                    */
    { 844, 2197, 20 },                  /*  admin_user                      */
    { 866, 2225, 25 },                  /*  l_admin_pass                    */
    { 893, 2272, 20 },                  /*  admin_pass                      */
    { 915, 0, 0 },                      /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   l_host_file_a        ;
    char   l_host_file          [40 + 1];
    byte   host_file_a          ;
    char   host_file            [80 + 1];
    byte   l_overwrite_a        ;
    char   l_overwrite          [31 + 1];
    byte   overwrite_a          ;
    char   overwrite            [1 + 1];
    byte   l_host_addr_a        ;
    char   l_host_addr          [30 + 1];
    byte   host_addr_a          ;
    char   host_addr            [3 + 1];
    byte   l_host_name_a        ;
    char   l_host_name          [36 + 1];
    byte   host_name_a          ;
    char   host_name            [50 + 1];
    byte   l_webpages_a         ;
    char   l_webpages           [36 + 1];
    byte   webpages_a           ;
    char   webpages             [50 + 1];
    byte   l_cgi_bin_a          ;
    char   l_cgi_bin            [30 + 1];
    byte   cgi_bin_a            ;
    char   cgi_bin              [50 + 1];
    byte   l_ftproot_a          ;
    char   l_ftproot            [31 + 1];
    byte   ftproot_a            ;
    char   ftproot              [50 + 1];
    byte   l_makedirs_a         ;
    char   l_makedirs           [44 + 1];
    byte   makedirs_a           ;
    char   makedirs             [1 + 1];
    byte   l_superuser_a        ;
    char   l_superuser          [31 + 1];
    byte   superuser_a          ;
    char   superuser            [20 + 1];
    byte   l_sharelogs_a        ;
    char   l_sharelogs          [33 + 1];
    byte   sharelogs_a          ;
    char   sharelogs            [1 + 1];
    byte   l_use_admin_a        ;
    char   l_use_admin          [40 + 1];
    byte   use_admin_a          ;
    char   use_admin            [1 + 1];
    byte   l_admin_user_a       ;
    char   l_admin_user         [27 + 1];
    byte   admin_user_a         ;
    char   admin_user           [20 + 1];
    byte   l_admin_pass_a       ;
    char   l_admin_pass         [25 + 1];
    byte   admin_pass_a         ;
    char   admin_pass           [20 + 1];
    byte   back_a;
    byte   console_a;
    byte   halt_a;
    byte   restart_a;
    byte   exit_a;
    byte   create_a;
    byte   cancel_a;
    } XIADM25_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm25 = {
    xiadm25_blocks,
    xiadm25_fields,
    120,                                /*  Number of blocks in form        */
    27,                                 /*  Number of fields in form        */
    7,                                  /*  Number of actions in form       */
    915,                                /*  Size of fields                  */
    "xiadm25",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
