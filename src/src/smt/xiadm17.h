/*---------------------------------------------------------------------------
 *  xiadm17.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM17__
#define __FORM_XIADM17__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define FTP_USER_LIST_MAX                   10
#define XIADM17_MESSAGE_TO_USER             0
#define XIADM17_L_USER_NAME                 1
#define XIADM17_L_PASSWORD                  2
#define XIADM17_L_ROOTDIR                   3
#define XIADM17_L_ACCESS                    4
#define XIADM17_L_CUR_USAGE                 5
#define XIADM17_L_CUR_FILES                 6
#define XIADM17_USER_NAME                   7
#define XIADM17_PASSWORD                    8
#define XIADM17_ROOTDIR                     9
#define XIADM17_ACCESS                      10
#define XIADM17_CUR_USAGE                   11
#define XIADM17_CUR_FILES                   12
#define XIADM17_FTP_USER_LIST               13

/*  This table contains each block in the form                               */

static byte xiadm17_blocks [] = {
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
    /*  !--ACTION new  LABEL="/admin ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 31, 20, 2, (byte) ((word) new_event / 256), (byte) ((word)
    new_event & 255), 0, 1, 0, 0, 0, 0, 0, 'n', 'e', 'w', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', '$', 'n', 'e', 'w', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION save  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 2, 0, 0, 0, 0, 0, 's', 'a', 'v', 'e', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v', 'e', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION undo  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 0, 0, 0, 'u', 'n', 'd', 'o', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd', 'o', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION first  LABEL="/adm ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 35, 20, 2, (byte) ((word) first_event / 256), (byte) ((word)
    first_event & 255), 0, 4, 0, 0, 0, 0, 0, 'f', 'i', 'r', 's', 't', 0,
    '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'f', 'i', 'r', 's', 't',
    '.', 'g', 'i', 'f', 0,
    /*  !--ACTION next  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) next_event / 256), (byte) ((word)
    next_event & 255), 0, 5, 0, 0, 0, 0, 0, 'n', 'e', 'x', 't', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'n', 'e', 'x', 't', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION refresh  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) refresh_event / 256), (byte) ((word)
    refresh_event & 255), 0, 6, 0, 0, 0, 0, 0, 'r', 'e', 'f', 'r', 'e',
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ...  - FTP User Profiles </FONT>        */
    0, 70, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'F', 'T', 'P', 32, 'U', 's', 'e', 'r', 32, 'P',
    'r', 'o', 'f', 'i', 'l', 'e', 's', 32, '<', '/', 'F', 'O', 'N', 'T',
    '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 1, 9,
    /*  !--ACTION console  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 7, 0, 0, 0, 0, 0, 'c', 'o', 'n', 's', 'o',
    'l', 'e', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'c', 'o', 'n',
    's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION halt  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 8, 0, 0, 0, 0, 0, 'h', 'a', 'l', 't', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION restart  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 9, 0, 0, 0, 0, 0, 'r', 'e', 's', 't', 'a',
    'r', 't', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'e', 's',
    't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION exit  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 10, 0, 0, 0, 0, 0, 'e', 'x', 'i', 't', 0, '/',
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
    0, 4, 1, 0, 3, '%',
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 4, 14,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  <TABLE WIDTH=90% >                                                   */
    0, 20, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '9', '0', '%', 32, '>', 10,
    /*  <TR>                                                                 */
    0, 6, 0, '<', 'T', 'R', '>', 10,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 30, 0, '<', 'T', 'H', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O',
    'P', '>', 10,
    /*  !--FIELD TEXTUAL f329 NAME=L_user-name VALUE="User name:"            */
    0, 24, 10, 6, 1, 0, 0, 10, 0, 10, 'f', '3', '2', '9', 0, 'U', 's',
    'e', 'r', 32, 'n', 'a', 'm', 'e', ':', 0,
    /*  </TH>                                                                */
    0, 7, 0, '<', '/', 'T', 'H', '>', 10,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 4, 205,
    /*  !--FIELD TEXTUAL f330 NAME=L_password VALUE="Password:"              */
    0, 23, 10, 6, 1, 0, 0, 9, 0, 9, 'f', '3', '3', '0', 0, 'P', 'a',
    's', 's', 'w', 'o', 'r', 'd', ':', 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 5, 7,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 4, 205,
    /*  !--FIELD TEXTUAL f331 NAME=L_rootdir VALUE="Login directory:"        */
    0, 30, 10, 6, 1, 0, 0, 16, 0, 16, 'f', '3', '3', '1', 0, 'L', 'o',
    'g', 'i', 'n', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', ':',
    0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 5, 7,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 4, 205,
    /*  !--FIELD TEXTUAL f332 NAME=L_access VALUE="Permissions:"             */
    0, 26, 10, 6, 1, 0, 0, 12, 0, 12, 'f', '3', '3', '2', 0, 'P', 'e',
    'r', 'm', 'i', 's', 's', 'i', 'o', 'n', 's', ':', 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 5, 7,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 4, 205,
    /*  !--FIELD TEXTUAL f333 NAME=L ... ge VALUE="Space used (Mb):"         */
    0, 30, 10, 6, 1, 0, 0, 16, 0, 16, 'f', '3', '3', '3', 0, 'S', 'p',
    'a', 'c', 'e', 32, 'u', 's', 'e', 'd', 32, '(', 'M', 'b', ')', ':',
    0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 5, 7,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 4, 205,
    /*  !--FIELD TEXTUAL f334 NAME=L ... es VALUE="Number of files:"         */
    0, 30, 10, 6, 1, 0, 0, 16, 0, 16, 'f', '3', '3', '4', 0, 'N', 'u',
    'm', 'b', 'e', 'r', 32, 'o', 'f', 32, 'f', 'i', 'l', 'e', 's', ':',
    0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 5, 7,
    /*  !--REPEAT ftp_user_list  ROWS=10                                     */
    0, 7, 4, 0, 13, 0, 21, 0, 10,
    /*  </TR>                                                                */
    0, 7, 0, '<', '/', 'T', 'R', '>', 10,
    /*  <TR>                                                                 */
    0, 4, 1, 0, 4, 197,
    /*  <TD ALIGN=CENTER VALIGN=TOP>                                         */
    0, 30, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O',
    'P', '>', 10,
    /*  !--FIELD TEXTUAL f335 NAME=u ... E=40 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 10, 10, 0, 0, '(', 0, '(', 'f', '3', '3', '5', 0, 0,
    /*  </TD>                                                                */
    0, 7, 0, '<', '/', 'T', 'D', '>', 10,
    /*  <TD ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 5, 249,
    /*  !--FIELD TEXTUAL f336 NAME=p ... E=40 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 6, 10, 0, 0, '(', 0, '(', 'f', '3', '3', '6', 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 6, ')',
    /*  <TD ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 5, 249,
    /*  !--FIELD TEXTUAL f337 NAME=r ... E=50 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 6, 10, 0, 0, '2', 0, '2', 'f', '3', '3', '7', 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 6, ')',
    /*  <TD ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 5, 249,
    /*  !--FIELD TEXTUAL f338 NAME=a ... ZE=6 MAX=? UPPER=0 VALUE=""         */
    0, 14, 10, 6, 10, 0, 0, 6, 0, 6, 'f', '3', '3', '8', 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 6, ')',
    /*  <TD ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 5, 249,
    /*  !--FIELD NUMERIC f339 NAME=c ... MA=0 SIZE=15 MAX=? VALUE=""         */
    0, 19, 11, 6, 10, 0, 15, 0, 15, 3, 0, 2, 0, 0, 0, 'f', '3', '3',
    '9', 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 6, ')',
    /*  <TD ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 5, 249,
    /*  !--FIELD NUMERIC f340 NAME=c ... MMA=0 SIZE=7 MAX=? VALUE=""         */
    0, 19, 11, 6, 10, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 'f', '3', '4', '0',
    0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 6, ')',
    /*  </TR>                                                                */
    0, 4, 1, 0, 5, 234,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 4, 14,
    /*  !--FIELD NUMERIC ftp_user_list SIZE=4 VALUE=10                       */
    0, 30, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'f', 't', 'p', '_',
    'u', 's', 'e', 'r', '_', 'l', 'i', 's', 't', 0, '1', '0', 0,
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
    0, 4, 1, 0, 4, 167,
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
    0, 4, 1, 0, 4, 14,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm17_fields [] = {
    { 0, 1136, 80 },                    /*  message_to_user                 */
    { 82, 1261, 10 },                   /*  l_user_name                     */
    { 94, 1302, 9 },                    /*  l_password                      */
    { 105, 1339, 16 },                  /*  l_rootdir                       */
    { 123, 1383, 12 },                  /*  l_access                        */
    { 137, 1423, 16 },                  /*  l_cur_usage                     */
    { 155, 1467, 16 },                  /*  l_cur_files                     */
    { 173, 1561, 40 },                  /*  user_name                       */
    { 593, 1592, 40 },                  /*  password                        */
    { 1013, 1620, 50 },                 /*  rootdir                         */
    { 1533, 1648, 6 },                  /*  access                          */
    { 1613, 1676, 15 },                 /*  cur_usage                       */
    { 1783, 1709, 7 },                  /*  cur_files                       */
    { 1873, 1748, 4 },                  /*  ftp_user_list                   */
    { 1879, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   l_user_name_a        ;
    char   l_user_name          [10 + 1];
    byte   l_password_a         ;
    char   l_password           [9 + 1];
    byte   l_rootdir_a          ;
    char   l_rootdir            [16 + 1];
    byte   l_access_a           ;
    char   l_access             [12 + 1];
    byte   l_cur_usage_a        ;
    char   l_cur_usage          [16 + 1];
    byte   l_cur_files_a        ;
    char   l_cur_files          [16 + 1];
    byte   user_name_a          [10] ;
    char   user_name            [10] [40 + 1];
    byte   password_a           [10] ;
    char   password             [10] [40 + 1];
    byte   rootdir_a            [10] ;
    char   rootdir              [10] [50 + 1];
    byte   access_a             [10] ;
    char   access               [10] [6 + 1];
    byte   cur_usage_a          [10] ;
    char   cur_usage            [10] [15 + 1];
    byte   cur_files_a          [10] ;
    char   cur_files            [10] [7 + 1];
    byte   ftp_user_list_a      ;
    char   ftp_user_list        [4 + 1];
    byte   back_a;
    byte   new_a;
    byte   save_a;
    byte   undo_a;
    byte   first_a;
    byte   next_a;
    byte   refresh_a;
    byte   console_a;
    byte   halt_a;
    byte   restart_a;
    byte   exit_a;
    } XIADM17_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm17 = {
    xiadm17_blocks,
    xiadm17_fields,
    91,                                 /*  Number of blocks in form        */
    14,                                 /*  Number of fields in form        */
    11,                                 /*  Number of actions in form       */
    1879,                               /*  Size of fields                  */
    "xiadm17",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
