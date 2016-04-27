/************************************************************************

               Copyright (c) 1998 by Eugen Woronenko

------------------------------------------------------------------------

Class Name:     LRWP_Connection.java

Description:    The Java class providing interface to 
                assist with the creation of LRWP Peer applications.

Creation Date:  14/08/1998 

# License:      This is free software.  You may use this software for any
#               purpose including modification/redistribution, so long as
#               this header remains intact and that you do not claim any
#               rights of ownership or authorship of this software.  This
#               software has been tested, but no warranty is expressed or
#               implied.

************************************************************************/

import java.lang.*;
import java.net.*;
import java.io.*;
import java.util.*;

/**********************************************************************************/

public class LRWP_Connection {

  protected static int lenSize=9;

  protected Socket sock=null;
  protected DataInputStream in=null;
  protected DataOutputStream out=null;

  protected byte[] postBytes=null;
  protected byte[] envBytes=null;

  protected String error="";

/**********************************************************************************/
  public LRWP_Connection() {}


/**********************************************************************************
    Method: main

    Demonstrates the class functionality. Can be useful for debugging.   
**********************************************************************************/

  public static void main(String[] args) {
    
    LRWP_Connection t=new LRWP_Connection();
    if (!t.connect("lrwp","localhost",81)) {
    	System.out.println(t.getError());
	return;
    }

    System.out.println("Connected!");

    for(int i=1;i<=3;i++) {

      if(t.accept_request()) {

        System.out.println(new String(t.getEnv()));

        System.out.println("\n");

        if(t.getPost()!=null) {
          System.out.println(new String(t.getPost()));
        }

        System.out.println("\n\n");

        String s="Content-type: text/plain\n\n *** Response " + i + " ***";

        if(!t.sendData(s.getBytes(),s.getBytes().length)) {
          System.out.println(t.getError());
          break;
        }      

      } else {
        System.out.println(t.getError());
        break;  
      }
    }

    t.disconnect();
  }

/**********************************************************************************
    Method: connect

    Connects to the LRWP agent running in Xitami on host and port.  Sends
    the given appname to use as the URI alias that will trigger requests to
    be sent to this peer. 

    Returns true on success, false otherwise. getError() method than returns
    a readable error message.
**********************************************************************************/

  public boolean connect(String appname,       /* Name or alias of Peer app         */
                         String host,          /* hostname/IP address to connect to */
                         int port              /* port number to connect to         */
                        ) 
  {

  byte[] buf=new byte[1024];
  int len=0;

  try {

    this.sock=new Socket(host, port);
    sock.setSoTimeout(0);

  } catch(Exception e) {
    cleanUp("Cannot open socket: "+e.toString());
    return false;
  }

  try {

    this.in=new DataInputStream(sock.getInputStream());

  } catch(Exception e) {
    cleanUp("Cannot open DataInputStream: "+e.toString());
    return false;
  }	

  try {

  this.out=new DataOutputStream(sock.getOutputStream());    

  } catch(Exception e) {
    cleanUp("Cannot open DataOutputStream: "+e.toString());
    return false;
  }

  /* send the startup sting */

  byte[] appnameBytes=appname.getBytes();
  
  for(int i=0;i<appnameBytes.length;i++)
    buf[i]=appnameBytes[i];

  buf[appnameBytes.length]=(byte)255;
  buf[appnameBytes.length+1]=(byte)255;

  try {

  out.write(buf,0,appnameBytes.length+2);  
  out.flush();    

  } catch(Exception e) {
    cleanUp("Cannot write startup string: "+e.toString());
    return false;
  }

  /* wait for an acknowledgement... */

  try {

  in.read(buf);    

  } catch(Exception e) {
    cleanUp("Cannot read startup response: "+e.toString());
    return false;
  }

  if (new String(buf).startsWith("OK"))
      return true;
  else {
      cleanUp(new String(buf)); 
      return false;
  }
}

/**********************************************************************************
    Method: accept_request

    This method waits for and recieves a request from the LRWP agent.
    On return, the received POST and environment data can be accessed via
    getPost() and getEnv() methods.

    Returns true on success, false otherwise. getError() method than returns
    a readable error message.
**********************************************************************************/

  public boolean accept_request() {
    
    postBytes =null;
    envBytes  =null;
    error     ="";

    byte[] lenBuf=new byte[lenSize];

    try {

      in.readFully(lenBuf,0,lenSize);

      int envLen=Integer.parseInt(new String(lenBuf));

      envBytes=new byte[envLen];

      in.readFully(envBytes,0,envLen);

      in.readFully(lenBuf,0,lenSize);
      int postLen=Integer.parseInt(new String(lenBuf));

      if(postLen!=0) {
        postBytes=new byte[postLen];
        in.readFully(postBytes,0,postLen); 
      }
     
      return true;    

    } catch(Exception e) {
      error="Accept_request error: "+e.toString();
      return false;
    }
  }

/**********************************************************************************
    Method: getEnv

    This method returns the received environment data.
**********************************************************************************/

  public byte[] getEnv() {

    return envBytes;
  }

/**********************************************************************************
    Method: getPost

    This method returns the received POST data or null if there isn't any.
**********************************************************************************/

  public byte[] getPost() {

    return postBytes;
  }

/**********************************************************************************
    Method: sendData

    Sends the response data as array of bytes back to Xitami.

    Returns true on success, false otherwise. getError() method than returns
    a readable error message.
**********************************************************************************/

  public boolean sendData(byte[] data,  /* The data array */
                          int len       /* The position in the array to start from */
                         )
  {
    try {

      out.write(LRWPInt(len).getBytes(), 0, lenSize);
      out.write(data, 0, len); 

      out.flush();    

      return true;

    } catch(Exception e) {
      error="sendData error: "+e.toString();
      return false;
    }
  }

/**********************************************************************************
    Method: disconnect

    Closes the connection to Xitami.

    Returns true on success, false otherwise. getError() method than returns
    a readable error message.
**********************************************************************************/

  public boolean disconnect() {
     return cleanUp("");
  }

/**********************************************************************************
    Method: getError

    Returns a readable error message.
**********************************************************************************/

  public String getError() {
    return error;
  }

/**********************************************************************************/

  protected boolean cleanUp(String err) {

    try {

      if (sock!=null) sock.close();
      this.error=err;
      return true;

    } catch(Exception e) {
      error="Cannot close the socket: "+e.toString();
      return false;
    }
  }

/**********************************************************************************/

  protected String LRWPInt(int i) {

    String num=String.valueOf(i);
    String nulls="";

    for(int x=0;x<this.lenSize-num.length();x++) {
      nulls=nulls+"0";
    }
        
    return nulls+num;
  }

/**********************************************************************************/
}