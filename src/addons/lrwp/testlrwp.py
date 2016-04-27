#!/bin/env python
#------------------------------------------------------------------------
#               Copyright (c) 1997 by Total Control Software
#                         All Rights Reserved
#------------------------------------------------------------------------
#
# Module Name:  testlrwp.py
#
# Description:  Class LRWP handles the connection to the LRWP agent in
#               Xitami.  This class can be used standalone or derived
#               from to override behavior.
#
# Creation Date:    11/11/97 8:36:21PM
#
#             $Id:$
#
#------------------------------------------------------------------------

import  sys, socket, string
from    cStringIO import StringIO


LENGTHSIZE  = 9
LENGTHFMT   = '%09d'

#---------------------------------------------------------------------------
# Exception objects

ConnectError        = 'lrwp.ConnectError'
ConnectionClosed    = 'lrwp.ConnectionClosed'
SocketError         = 'lrwp.SocketError'

#---------------------------------------------------------------------------

class Request:
    def __init__(self, lrwp):
        self.inp = lrwp.inp
        self.out = lrwp.out
        self.err = lrwp.out
        self.env = lrwp.env
        self.lrwp = lrwp

    def finish(self):
        self.lrwp.finish()

    def getFieldStorage(self):
        method = 'POST'
        if self.env.has_key('REQUEST_METHOD'):
            method = string.upper(self.env['REQUEST_METHOD'])
        if method == 'GET':
            return cgi.FieldStorage(environ=self.env, keep_blank_values=1)
        else:
            return cgi.FieldStorage(fp=self.inp, environ=self.env, keep_blank_values=1)


#---------------------------------------------------------------------------

class LRWP:
    def __init__(self, name, host, port, vhost='', filter='', useStdio=0):
        self.name = name
        self.host = host
        self.port = port
        self.vhost = vhost
        self.filter = filter
        self.useStdio = useStdio
        self.sock = None
        self.env = None
        self.inp = None
        self.out = None

    #----------------------------------------
    def connect(self):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect(self.host, self.port)
            self.sock.send("%s\xFF%s\xFF%s" % (self.name, self.vhost, self.filter) )
            buf = self.sock.recv(1024)
            if buf != 'OK':
                raise ConnectError, buf
        except socket.error, val:
            raise SocketError, val

    #----------------------------------------
    def acceptRequest(self):
        if self.out:
            self.finish()
        try:
            # get the length of the environment data
            data = self.sock.recv(LENGTHSIZE)
            if not data:        # server closed down
                raise ConnectionClosed
            length = string.atoi(data)

            # and then the environment data
            data = self.sock.recv(length)
            if not data:        # server closed down
                raise ConnectionClosed
            data = string.split(data, '\000')
            self.env = {}
            for x in data:
                x = string.split(x, '=')
                if len(x) > 1:
                    self.env[x[0]] = string.join(x[1:], '=')

            # now get the size of the POST data
            data = self.sock.recv(LENGTHSIZE)
            if not data:        # server closed down
                raise ConnectionClosed
            length = string.atoi(data)

            # and the POST data...
            if length:
                data = self.sock.recv(length)
                if not data:        # server closed down
                    raise ConnectionClosed
                self.inp = StringIO(data)
            else:
                self.inp = StringIO()

            self.out = StringIO()

            if self.useStdio:
                self.saveStdio = sys.stdin, sys.stdout, sys.stderr, os.environ
                sys.stdin, sys.stdout, sys.stderr, os.environ = \
                    self.inp, self.out, self.out, self.env

            return Request(self)

        except socket.error, val:
            raise SocketError, val


    #----------------------------------------
    def finish(self):
        doc = self.out.getvalue()
        size = LENGTHFMT % (len(doc), )
        try:
            self.sock.send(size)
            self.sock.send(doc)
        except socket.error, val:
            raise SocketError, val

        if self.useStdio:
            sys.stdin, sys.stdout, sys.stderr, os.environ = self.saveStdio

        self.env = None
        self.inp = None
        self.out = None

    #----------------------------------------
    def close(self):
        self.sock.close()
        self.sock = None
        self.env = None
        self.inp = None
        self.out = None

#---------------------------------------------------------------------------


def _test():
    import os, time

    eol = '\r\n'
    appname = 'testapp1'
    vhost = ''
    if len(sys.argv) > 1:
        appname = sys.argv[1]
    if len(sys.argv) > 2:
        vhost = sys.argv[2]
    lrwp = LRWP(appname, 'rogue', 5081, vhost)
    lrwp.connect()

    count = 0
    while count < 5:
        req = lrwp.acceptRequest()

        doc = ['<HTML><HEAD><TITLE>LRWP TestApp ('+appname+')</TITLE></HEAD>\n<BODY>\n']
        count = count + 1
        doc.append('<H2>LRWP test app ('+appname+')</H2><P>')
        doc.append('<b>request count</b> = %d<br>' % (count, ))
        if hasattr(os, 'getpid'):
            doc.append('<b>pid</b> = %s<br>' % (os.getpid(), ))
        doc.append('<br><b>post data:</b> ' + req.inp.read() + '<br>')

        doc.append('<P><HR><P><pre>')
        keys = req.env.keys()
        keys.sort()
        for k in keys:
            doc.append('<b>%-20s :</b>  %s\n' % (k, req.env[k]))
        doc.append('\n</pre><P><HR>\n')
        doc.append('</BODY></HTML>\n')


        req.out.write('Content-type: text/html' + eol)
        req.out.write(eol)
        req.out.write(string.join(doc, ''))

        #time.sleep(2)
        req.finish()

    lrwp.close()


if __name__ == '__main__':
    #import pdb
    #pdb.run('_test()')
    _test()

