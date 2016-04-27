/*---------------------------------------------------------------------------
 *  xiadm01.h - HTML form definition
 *
 *  Generated 1999/01/17, 21:39:48 by fxgen 2.0
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM01__
#define __FORM_XIADM01__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM01_MESSAGE_TO_USER             0

/*  This table contains each block in the form                               */

static byte xiadm01_blocks [] = {
    /*  <HTML>                                                               */
    0, 8, 0, '<', 'H', 'T', 'M', 'L', '>', 10,
    /*  <HEAD><TITLE>Xitami Administration</TITLE></HEAD>                    */
    0, 51, 0, '<', 'H', 'E', 'A', 'D', '>', '<', 'T', 'I', 'T', 'L',
    'E', '>', 'X', 'i', 't', 'a', 'm', 'i', 32, 'A', 'd', 'm', 'i', 'n',
    'i', 's', 't', 'r', 'a', 't', 'i', 'o', 'n', '<', '/', 'T', 'I',
    'T', 'L', 'E', '>', '<', '/', 'H', 'E', 'A', 'D', '>', 10,
    /*  <BODY onLoad="focus()"                                               */
    0, 24, 0, '<', 'B', 'O', 'D', 'Y', 32, 'o', 'n', 'L', 'o', 'a', 'd',
    '=', '"', 'f', 'o', 'c', 'u', 's', '(', ')', '"', 10,
    /*  BGCOLOR="#87CEFA" LINK="#FFF ... K="#CCFFFF" ALINK="#FF9900">        */
    0, 67, 0, 'B', 'G', 'C', 'O', 'L', 'O', 'R', '=', '"', '#', '8',
    '7', 'C', 'E', 'F', 'A', '"', 32, 'L', 'I', 'N', 'K', '=', '"', '#',
    'F', 'F', 'F', 'F', '9', '9', '"', 32, 'V', 'L', 'I', 'N', 'K', '=',
    '"', '#', 'C', 'C', 'F', 'F', 'F', 'F', '"', 32, 'A', 'L', 'I', 'N',
    'K', '=', '"', '#', 'F', 'F', '9', '9', '0', '0', '"', '>', 10,
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
    /*  <IMG SRC="/admin/$left.gif"  ... .gif" BORDER=0 ALIGN=MIDDLE>        */
    0, 212, 0, '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'l', 'e', 'f', 't', '.', 'g',
    'i', 'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A',
    'L', 'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', '<',
    'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i', 't', 'a', 'm',
    'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h', 't', 'm', '"', 32,
    'T', 'A', 'R', 'G', 'E', 'T', '=', '"', 'H', 'e', 'l', 'p', '"',
    '>', '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/', 'a', 'd',
    'm', 'i', 'n', '/', '$', 'h', 'e', 'l', 'p', '.', 'g', 'i', 'f',
    '"', 32, 'A', 'L', 'T', '=', '"', 'H', 'e', 'l', 'p', 32, '"', 32,
    'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A', 'L', 'I', 'G', 'N',
    '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', '<', '/', 'A', '>', '<',
    'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/', 'a', 'd', 'm', 'i',
    'n', '/', '$', 'r', 'i', 'g', 'h', 't', '.', 'g', 'i', 'f', '"', 32,
    'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A', 'L', 'I', 'G', 'N',
    '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', 10,
    /*  <TD ALIGN=CENTER><FONT SIZE=+1></FONT>                               */
    0, 40, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '<', '/', 'F', 'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 6, 1, 1, 1, ';', 0, '2',
    /*  !--ACTION console  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 0, 0, 0, 0, 0, 0, 'c', 'o', 'n', 's', 'o',
    'l', 'e', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'c', 'o', 'n',
    's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION halt  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 1, 0, 0, 0, 0, 0, 'h', 'a', 'l', 't', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't', '.', 'g',
    'i', 'f', 0,
    /*  !--ACTION restart  LABEL="/a ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 2, 0, 0, 0, 0, 0, 'r', 'e', 's', 't', 'a',
    'r', 't', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'e', 's',
    't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0,
    /*  !--ACTION exit  LABEL="/admi ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 33, 20, 2, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 3, 0, 0, 0, 0, 0, 'e', 'x', 'i', 't', 0, '/',
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
    0, 4, 1, 0, 2, ';',
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, '&',
    /*  <CENTER>                                                             */
    0, 10, 0, '<', 'C', 'E', 'N', 'T', 'E', 'R', '>', 10,
    /*  <TABLE WIDTH="80%" BORDER=0  ... PADDING=0 BGCOLOR="#000080">        */
    0, 76, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '8', '0', '%', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=',
    '0', 32, 'C', 'E', 'L', 'L', 'S', 'P', 'A', 'C', 'I', 'N', 'G', '=',
    '0', 32, 'C', 'E', 'L', 'L', 'P', 'A', 'D', 'D', 'I', 'N', 'G', '=',
    '0', 32, 'B', 'G', 'C', 'O', 'L', 'O', 'R', '=', '"', '#', '0', '0',
    '0', '0', '8', '0', '"', '>', 10,
    /*  <TR><TD COLSPAN=2><HR><CENTER>                                       */
    0, 32, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'C', 'O', 'L', 'S',
    'P', 'A', 'N', '=', '2', '>', '<', 'H', 'R', '>', '<', 'C', 'E',
    'N', 'T', 'E', 'R', '>', 10,
    /*  <FONT COLOR="#FFFF99"><H1><I ... NAME="TOC1"></A></H1></FONT>        */
    0, 87, 0, '<', 'F', 'O', 'N', 'T', 32, 'C', 'O', 'L', 'O', 'R', '=',
    '"', '#', 'F', 'F', 'F', 'F', '9', '9', '"', '>', '<', 'H', '1',
    '>', '<', 'I', '>', 'X', 'i', 't', 'a', 'm', 'i', 32, 'A', 'd', 'm',
    'i', 'n', 'i', 's', 't', 'r', 'a', 't', 'i', 'o', 'n', '<', '/',
    'I', '>', '<', 'A', 32, 'N', 'A', 'M', 'E', '=', '"', 'T', 'O', 'C',
    '1', '"', '>', '<', '/', 'A', '>', '<', '/', 'H', '1', '>', '<',
    '/', 'F', 'O', 'N', 'T', '>', 10,
    /*  </CENTER><HR><TR><TD VALIGN=TOP NOWRAP>                              */
    0, 41, 0, '<', '/', 'C', 'E', 'N', 'T', 'E', 'R', '>', '<', 'H',
    'R', '>', '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'V', 'A', 'L', 'I',
    'G', 'N', '=', 'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', '>',
    10,
    /*  !--ACTION menu_config  LABEL ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 40, 20, 2, (byte) ((word) config_event / 256), (byte) ((word)
    config_event & 255), 0, 4, 0, 0, 0, 0, 0, 'm', 'e', 'n', 'u', '_',
    'c', 'o', 'n', 'f', 'i', 'g', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    'c', 'l', 'i', 'c', 'k', '.', 'g', 'i', 'f', 0,
    /*  &nbsp;<FONT COLOR="#FFFF99">Configuration </FONT><BR>                */
    0, 55, 0, '&', 'n', 'b', 's', 'p', ';', '<', 'F', 'O', 'N', 'T', 32,
    'C', 'O', 'L', 'O', 'R', '=', '"', '#', 'F', 'F', 'F', 'F', '9',
    '9', '"', '>', 'C', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't',
    'i', 'o', 'n', 32, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'B', 'R',
    '>', 10,
    /*  !--ACTION menu_hosts  LABEL= ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 39, 20, 2, (byte) ((word) hosts_event / 256), (byte) ((word)
    hosts_event & 255), 0, 5, 0, 0, 0, 0, 0, 'm', 'e', 'n', 'u', '_',
    'h', 'o', 's', 't', 's', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'c',
    'l', 'i', 'c', 'k', '.', 'g', 'i', 'f', 0,
    /*  &nbsp;<FONT COLOR="#FFFF99">Virtual hosts </FONT><BR>                */
    0, 55, 0, '&', 'n', 'b', 's', 'p', ';', '<', 'F', 'O', 'N', 'T', 32,
    'C', 'O', 'L', 'O', 'R', '=', '"', '#', 'F', 'F', 'F', 'F', '9',
    '9', '"', '>', 'V', 'i', 'r', 't', 'u', 'a', 'l', 32, 'h', 'o', 's',
    't', 's', 32, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'B', 'R', '>',
    10,
    /*  !--ACTION menu_console  LABE ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 41, 20, 2, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 6, 0, 0, 0, 0, 0, 'm', 'e', 'n', 'u', '_',
    'c', 'o', 'n', 's', 'o', 'l', 'e', 0, '/', 'a', 'd', 'm', 'i', 'n',
    '/', 'c', 'l', 'i', 'c', 'k', '.', 'g', 'i', 'f', 0,
    /*  &nbsp;<FONT COLOR="#FFFF99">Server Console </FONT><BR>               */
    0, 56, 0, '&', 'n', 'b', 's', 'p', ';', '<', 'F', 'O', 'N', 'T', 32,
    'C', 'O', 'L', 'O', 'R', '=', '"', '#', 'F', 'F', 'F', 'F', '9',
    '9', '"', '>', 'S', 'e', 'r', 'v', 'e', 'r', 32, 'C', 'o', 'n', 's',
    'o', 'l', 'e', 32, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'B', 'R',
    '>', 10,
    /*  !--ACTION menu_wizard  LABEL ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 40, 20, 2, (byte) ((word) wizard_event / 256), (byte) ((word)
    wizard_event & 255), 0, 7, 0, 0, 0, 0, 0, 'm', 'e', 'n', 'u', '_',
    'w', 'i', 'z', 'a', 'r', 'd', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    'c', 'l', 'i', 'c', 'k', '.', 'g', 'i', 'f', 0,
    /*  &nbsp;<FONT COLOR="#FFFF99">VHost Wizard </FONT><BR>                 */
    0, 54, 0, '&', 'n', 'b', 's', 'p', ';', '<', 'F', 'O', 'N', 'T', 32,
    'C', 'O', 'L', 'O', 'R', '=', '"', '#', 'F', 'F', 'F', 'F', '9',
    '9', '"', '>', 'V', 'H', 'o', 's', 't', 32, 'W', 'i', 'z', 'a', 'r',
    'd', 32, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'B', 'R', '>', 10,
    /*  !--ACTION menu_restart  LABE ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 41, 20, 2, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 8, 0, 0, 0, 0, 0, 'm', 'e', 'n', 'u', '_',
    'r', 'e', 's', 't', 'a', 'r', 't', 0, '/', 'a', 'd', 'm', 'i', 'n',
    '/', 'c', 'l', 'i', 'c', 'k', '.', 'g', 'i', 'f', 0,
    /*  &nbsp;<FONT COLOR="#FFFF99">Restart Server </FONT><BR>               */
    0, 56, 0, '&', 'n', 'b', 's', 'p', ';', '<', 'F', 'O', 'N', 'T', 32,
    'C', 'O', 'L', 'O', 'R', '=', '"', '#', 'F', 'F', 'F', 'F', '9',
    '9', '"', '>', 'R', 'e', 's', 't', 'a', 'r', 't', 32, 'S', 'e', 'r',
    'v', 'e', 'r', 32, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'B', 'R',
    '>', 10,
    /*  !--ACTION menu_halt  LABEL=" ... TYPE=IMAGE HEIGHT=? WIDTH=?         */
    0, 38, 20, 2, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 9, 0, 0, 0, 0, 0, 'm', 'e', 'n', 'u', '_',
    'h', 'a', 'l', 't', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'c', 'l',
    'i', 'c', 'k', '.', 'g', 'i', 'f', 0,
    /*  &nbsp;<FONT COLOR="#FFFF99">Halt Server </FONT><BR>                  */
    0, 53, 0, '&', 'n', 'b', 's', 'p', ';', '<', 'F', 'O', 'N', 'T', 32,
    'C', 'O', 'L', 'O', 'R', '=', '"', '#', 'F', 'F', 'F', 'F', '9',
    '9', '"', '>', 'H', 'a', 'l', 't', 32, 'S', 'e', 'r', 'v', 'e', 'r',
    32, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'B', 'R', '>', 10,
    /*  <P>&nbsp;<TD VALIGN=TOP BGCOLOR="#CCFFFF">                           */
    0, 44, 0, '<', 'P', '>', '&', 'n', 'b', 's', 'p', ';', '<', 'T',
    'D', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'B',
    'G', 'C', 'O', 'L', 'O', 'R', '=', '"', '#', 'C', 'C', 'F', 'F',
    'F', 'F', '"', '>', 10,
    /*  <UL>                                                                 */
    0, 6, 0, '<', 'U', 'L', '>', 10,
    /*  <LI>The web-based administra ... ompatible with release 3 and        */
    0, 73, 0, '<', 'L', 'I', '>', 'T', 'h', 'e', 32, 'w', 'e', 'b', 45,
    'b', 'a', 's', 'e', 'd', 32, 'a', 'd', 'm', 'i', 'n', 'i', 's', 't',
    'r', 'a', 't', 'i', 'o', 'n', 32, '(', 'W', 'B', 'A', ')', 32, 'i',
    's', 32, 'c', 'o', 'm', 'p', 'a', 't', 'i', 'b', 'l', 'e', 32, 'w',
    'i', 't', 'h', 32, 'r', 'e', 'l', 'e', 'a', 's', 'e', 32, '3', 32,
    'a', 'n', 'd', 10,
    /*  higher browsers, including M ...  the WBAConsole Preferences.        */
    0, 164, 0, 'h', 'i', 'g', 'h', 'e', 'r', 32, 'b', 'r', 'o', 'w',
    's', 'e', 'r', 's', ',', 32, 'i', 'n', 'c', 'l', 'u', 'd', 'i', 'n',
    'g', 32, 'M', 'S', 'I', 'E', ',', 32, 'N', 'e', 't', 's', 'c', 'a',
    'p', 'e', 32, 'N', 'a', 'v', 'i', 'g', 'a', 't', 'o', 'r', 32, 'a',
    'n', 'd', 32, 'O', 'p', 'e', 'r', 'a', '.', 32, 'I', 'f', 32, 'y',
    'o', 'u', 'r', 10, 10, 'b', 'r', 'o', 'w', 's', 'e', 'r', 32, 's',
    'u', 'p', 'p', 'o', 'r', 't', 's', 32, 'J', 'a', 'v', 'a', 'S', 'c',
    'r', 'i', 'p', 't', ',', 32, 'e', 'n', 'a', 'b', 'l', 'e', 32, 'i',
    't', 32, 'i', 'n', 32, 't', 'h', 'e', 32, 'b', 'r', 'o', 'w', 's',
    'e', 'r', 32, 'a', 'n', 'd', 32, 'i', 'n', 32, 't', 'h', 'e', 32,
    'W', 'B', 'A', 10, 10, 'C', 'o', 'n', 's', 'o', 'l', 'e', 32, 'P',
    'r', 'e', 'f', 'e', 'r', 'e', 'n', 'c', 'e', 's', '.', 10,
    /*  <LI>When using the WBA, don' ...  'Back' button - use the WBA        */
    0, 75, 0, '<', 'L', 'I', '>', 'W', 'h', 'e', 'n', 32, 'u', 's', 'i',
    'n', 'g', 32, 't', 'h', 'e', 32, 'W', 'B', 'A', ',', 32, 'd', 'o',
    'n', 39, 't', 32, 'u', 's', 'e', 32, 't', 'h', 'e', 32, 'b', 'r',
    'o', 'w', 's', 'e', 'r', 32, 39, 'B', 'a', 'c', 'k', 39, 32, 'b',
    'u', 't', 't', 'o', 'n', 32, 45, 32, 'u', 's', 'e', 32, 't', 'h',
    'e', 32, 'W', 'B', 'A', 10,
    /*  icon bar and actions instead ... s at once, it will not work.        */
    0, 201, 0, 'i', 'c', 'o', 'n', 32, 'b', 'a', 'r', 32, 'a', 'n', 'd',
    32, 'a', 'c', 't', 'i', 'o', 'n', 's', 32, 'i', 'n', 's', 't', 'e',
    'a', 'd', '.', 32, 32, 'I', 'f', 32, 'y', 'o', 'u', 32, 'g', 'e',
    't', 32, 'l', 'o', 's', 't', ',', 32, 'u', 's', 'e', 32, 't', 'h',
    'e', 32, 'b', 'r', 'o', 'w', 's', 'e', 'r', 32, 39, 'R', 'e', 'f',
    'r', 'e', 's', 'h', 39, 10, 10, 'b', 'u', 't', 't', 'o', 'n', '.',
    32, 32, 'T', 'h', 'e', 32, 'W', 'B', 'A', 32, 'o', 'n', 'l', 'y',
    32, 'a', 'l', 'l', 'o', 'w', 's', 32, 'o', 'n', 'e', 32, 's', 'e',
    's', 's', 'i', 'o', 'n', 32, 'a', 't', 32, 'o', 'n', 'c', 'e', ',',
    32, 's', 'o', 32, 'i', 'f', 32, 'y', 'o', 'u', 32, 't', 'r', 'y',
    32, 't', 'o', 32, 'u', 's', 'e', 32, 'i', 't', 10, 10, 'f', 'r',
    'o', 'm', 32, 'm', 'u', 'l', 't', 'i', 'p', 'l', 'e', 32, 'b', 'r',
    'o', 'w', 's', 'e', 'r', 's', 32, 'a', 't', 32, 'o', 'n', 'c', 'e',
    ',', 32, 'i', 't', 32, 'w', 'i', 'l', 'l', 32, 'n', 'o', 't', 32,
    'w', 'o', 'r', 'k', '.', 10,
    /*  <LI>Use the Save icon to sav ... and the Back icon to discard        */
    0, 74, 0, '<', 'L', 'I', '>', 'U', 's', 'e', 32, 't', 'h', 'e', 32,
    'S', 'a', 'v', 'e', 32, 'i', 'c', 'o', 'n', 32, 't', 'o', 32, 's',
    'a', 'v', 'e', 32, 'y', 'o', 'u', 'r', 32, 'c', 'h', 'a', 'n', 'g',
    'e', 's', ',', 32, 'a', 'n', 'd', 32, 't', 'h', 'e', 32, 'B', 'a',
    'c', 'k', 32, 'i', 'c', 'o', 'n', 32, 't', 'o', 32, 'd', 'i', 's',
    'c', 'a', 'r', 'd', 10,
    /*  them.  When you've saved you ... tart theweb and ftp servers.        */
    0, 98, 0, 't', 'h', 'e', 'm', '.', 32, 32, 'W', 'h', 'e', 'n', 32,
    'y', 'o', 'u', 39, 'v', 'e', 32, 's', 'a', 'v', 'e', 'd', 32, 'y',
    'o', 'u', 'r', 32, 'c', 'h', 'a', 'n', 'g', 'e', 's', ',', 32, 'u',
    's', 'e', 32, 't', 'h', 'e', 32, 'R', 'e', 's', 't', 'a', 'r', 't',
    32, 'i', 'c', 'o', 'n', 32, 't', 'o', 32, 'r', 'e', 's', 't', 'a',
    'r', 't', 32, 't', 'h', 'e', 10, 10, 'w', 'e', 'b', 32, 'a', 'n',
    'd', 32, 'f', 't', 'p', 32, 's', 'e', 'r', 'v', 'e', 'r', 's', '.',
    10,
    /*  <LI>If you're using a proxy  ...  for local addresses, and/or        */
    0, 76, 0, '<', 'L', 'I', '>', 'I', 'f', 32, 'y', 'o', 'u', 39, 'r',
    'e', 32, 'u', 's', 'i', 'n', 'g', 32, 'a', 32, 'p', 'r', 'o', 'x',
    'y', 32, 's', 'e', 'r', 'v', 'e', 'r', ',', 32, 'd', 'i', 's', 'a',
    'b', 'l', 'e', 32, 'i', 't', 32, 'f', 'o', 'r', 32, 'l', 'o', 'c',
    'a', 'l', 32, 'a', 'd', 'd', 'r', 'e', 's', 's', 'e', 's', ',', 32,
    'a', 'n', 'd', '/', 'o', 'r', 10,
    /*  the address of your web serv ... u're using the WBA remotely.        */
    0, 66, 0, 't', 'h', 'e', 32, 'a', 'd', 'd', 'r', 'e', 's', 's', 32,
    'o', 'f', 32, 'y', 'o', 'u', 'r', 32, 'w', 'e', 'b', 32, 's', 'e',
    'r', 'v', 'e', 'r', 32, 'i', 'f', 32, 'y', 'o', 'u', 39, 'r', 'e',
    32, 'u', 's', 'i', 'n', 'g', 32, 't', 'h', 'e', 32, 'W', 'B', 'A',
    32, 'r', 'e', 'm', 'o', 't', 'e', 'l', 'y', '.', 10,
    /*  </UL>                                                                */
    0, 7, 0, '<', '/', 'U', 'L', '>', 10,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 3, '&',
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
    0, 4, 1, 0, 3, '&',
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm01_fields [] = {
    { 0, 904, 80 },                     /*  message_to_user                 */
    { 82, 0, 0 },                       /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   message_to_user_a    ;
    char   message_to_user      [80 + 1];
    byte   console_a;
    byte   halt_a;
    byte   restart_a;
    byte   exit_a;
    byte   menu_config_a;
    byte   menu_hosts_a;
    byte   menu_console_a;
    byte   menu_wizard_a;
    byte   menu_restart_a;
    byte   menu_halt_a;
    } XIADM01_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm01 = {
    xiadm01_blocks,
    xiadm01_fields,
    68,                                 /*  Number of blocks in form        */
    1,                                  /*  Number of fields in form        */
    10,                                 /*  Number of actions in form       */
    82,                                 /*  Size of fields                  */
    "xiadm01",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */
