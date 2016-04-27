/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflmail.h
    Title:      SMTP mailer function
    Package:    standard function library (sfl)

    Written:    06/18/97 Scott Beasley (jscottb@infoave.com)
    Revised:    98/05/11

    Synopsis:   Functions to format and send SMTP messages.  Messages
                can contain attachments, and be sent with "cc"'s "bcc"'s as
                well as the normal "to" receivers.
            
    Copyright:  Copyright (c) 1991-99 iMatix Corporation
    License:    this is free software; you can redistribute it and/or modify
                it under the terms of the sfl license agreement as provided
                in the file license.txt.  this software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _sflmail_included               /*  allow multiple inclusions        */
#define _sflmail_included

typedef struct SMTP {
   char *strSmtpServer;
   char *strMessageBody;
   char *strSubject;
   char *strSenderUserId;
   char *strDestUserIds;
   char *strCcUserIds;
   char *strBccUserIds;
   char *strRetPathUserId;
   char *strRrcpUserId;
   char *strMsgComment;
   char *strMailerName;
   char *strBinFiles;
   char *strTxtFiles;
   char strlast_smtp_message[513];
   int  debug;
   int  mime;
   int  encode_type;
   int  connect_retry_cnt;
   int  retry_wait_time;
} SMTP;

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "c" {
#endif
int       smtp_send_mail_ex (SMTP *smtp);
int       smtp_send_mail    (char *strsmtpserver, char *strmsgbody,
                             char *strsubject, char *strsenderuserid,
                             char *strDestUserIds, char *strccuserids,
                             char *strbccuserids, char *strRetPathUserId,
                             char *strRrcpUserId, char *strMsgComment,
                             char *strMailerName, char *strBinfiles, 
                             char *strTxtFiles);
#ifdef __cplusplus
}
#endif

#endif
