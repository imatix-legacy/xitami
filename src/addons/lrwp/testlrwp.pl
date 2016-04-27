#! /local/perl5/bin/perl
#
#   Name:       testlrwp
#   Title:      Example of LRWP program in Perl
#   Package:    Xitami web server
#
#   Written:    98/05/06  Xitami team <xitami@imatix.com>
#   Revised:    
#
#   Copyright:  Copyright (c) 1991-98 iMatix
#   License:    This is free software; you can redistribute it and/or modify
#               it under the terms of the License Agreement as provided
#               in the file LICENSE.TXT.  This software is distributed in
#               the hope that it will be useful, but without any warranty.
#
#
#   Usage:
#      testlrwp.pl applicationname lrwpserver lrwpport [virtualhost]

require 5;
use strict;
use Socket;
use FileHandle;

# Constants: indexes into LRWP "structure"
my $LRWP_SOCKET        = 0;
my $LRWP_CGI           = 1;
my $LRWP_INDATA        = 2;
my $LRWP_OUTDATA       = 3;

# Number of bytes sent across for length
my $LRWP_SIZE_BYTES    = 9;

# Register as a LRWP process with the main server
# Parameters: arrayref (filled with LRWP details), applicationname, 
#             serveraddress, serverport, virtual host (optional)
# Returns:    undef on success; failure message on failure

sub lrwp_connect
{
    my ($lrwpref, $appname, $serveraddr, $serverport, $vhost) = @_;
    if (! defined ($lrwpref)    || ! defined ($appname)
     || ! defined ($serveraddr) || ! defined ($serverport)) {
	return "register_lrwp: insufficient parameters";
    }

    if (defined ($lrwpref -> [$LRWP_SOCKET])) {
	close ($lrwpref -> [$LRWP_SOCKET]);
	$lrwpref -> [$LRWP_SOCKET] = undef;
    }
    $lrwpref -> [$LRWP_CGI]     = undef;
    $lrwpref -> [$LRWP_INDATA]  = "";
    $lrwpref -> [$LRWP_OUTDATA] = "";

    my ($addr, $port);
    if ($serveraddr =~ /^\d+\.\d+\.\d+\.\d+$/) {
	$addr = inet_aton($serveraddr);       # IP address (dotted quad)
    }
    else {
	$addr = gethostbyname($serveraddr);   # Hostname?
    }
    if (! defined ($addr)) {
	return "lrwp_connect: unable to resolve host: $serveraddr";
    }

    if ($serverport =~ /^\d+$/) {
	$port = $serverport;                  # Port number
    }
    else {
	$port = getservbyname($serverport, 'tcp');
    }
    if (! defined ($port)) {
	return "lrwp_connect: unable to resolve port: $serverport";
    }

    
    my ($proto) = getprotobyname('tcp');
    my $paddr   = sockaddr_in($port, $addr);

    my $SOCKET  = new FileHandle;                    # A local file handle
    if (socket ($SOCKET, PF_INET, SOCK_STREAM, $proto)) {
	$lrwpref -> [$LRWP_SOCKET] = $SOCKET;
    }
    else {
	return "lrwp_connect: Unable to create socket";
    }

    if (connect ($SOCKET, $paddr)) {
    }
    else {
	close ($SOCKET);
	$lrwpref -> [$LRWP_SOCKET] = undef;
	return "lrwp_connect: Unable to connect to remote host ($serveraddr, $serverport)";
    }

    $SOCKET->autoflush();

    # Send LRWP server our identification information
    if (printf $SOCKET "%s\xFF%s\xFF%s", $appname, 
	              (defined($vhost) ? $vhost : ""),
	              "") {
    }
    else {
	close (SOCKET);
	$lrwpref -> [$LRWP_SOCKET] = undef;
	return "lrwp_connect: Unable to identify ourselves to server";
    }

    # Wait for LRWP server to acknowledge us
    my $buffer = ' ' x 1024;
    my $bytes  = sysread $SOCKET, $buffer, 1024;
    if ($bytes > 0) {
	substr ($buffer, $bytes) = "";        # Trim string
	
	if ($buffer eq "OK") {
	    return undef;                     # All is well
	}
	else {
	    return "lrwp_connect: Failed: $buffer";
	}
    }
    else {
	return "lrwp_connect: No response from LRWP server";
    }

    # Unreachable
    return "lrwp_connect: internal logic error";
}


# Accept a request from the LRWP server to process; blocks until it has
# read in the full request.
# Parameters: LRWP array reference
# Returns:    1 on success, undef otherwise

sub lrwp_accept_request
{
    my ($lrwpref) = @_;
    if (! defined ($lrwpref)) {
	warn "lrwp_accept_request: insufficient parameters";
	return undef;
    }

    my ($environsize) =
	read_all_bytes ($lrwpref -> [$LRWP_SOCKET], $LRWP_SIZE_BYTES);
    if (! defined ($environsize)) {
	return undef;
    }

    my ($environment) =
	read_all_bytes ($lrwpref -> [$LRWP_SOCKET], $environsize);
    if (! defined ($environment)) {
	return undef;
    }
    $lrwpref -> [$LRWP_CGI] = string_to_hash_ref($environment);

    my ($postsize) =
	read_all_bytes ($lrwpref -> [$LRWP_SOCKET], $LRWP_SIZE_BYTES);
    if (! defined ($postsize)) {
	return undef;
    }

    if ($postsize > 0) {
	$lrwpref -> [$LRWP_INDATA] = 
	    read_all_bytes ($lrwpref -> [$LRWP_SOCKET], $postsize);
	if (defined ($lrwpref -> [$LRWP_INDATA])) {
	    return 1;              # Valid request with posted data
	}
	else {
	    return undef;
	}
    }
    else {
	$lrwpref -> [$LRWP_INDATA] = "";
	return 1;                  # Valid request with no data
    }

    # Unreachable
    warn "lrwp_accept_request: Internal logic error";
    return undef;
}

# Append a string to the outgoing LRWP data buffer
# Parameters: reference to LRWP array, string to append
# Returns:    1, unless missing parameters (then undef)

sub lrwp_send_string
{
    if (defined ($_[0]) && defined ($_[1])) {
	$_[0] -> [$LRWP_OUTDATA] .= $_[1];
	return 1;
    }
    else 
    {
	return undef;
    }
    
}

# Append general data to end of outgoing LRWP data buffer
# Parameters: reference to LRWP array, string to append
# Returns:    1, unless missing parameters (then undef)

sub lrwp_send_data
{
    return lrwp_send_string(@_);
}

# Write finished report back out to LRWP server
# Parameters: reference to LRWP array
# Returns:    1 if successful, undef otherwise

sub lrwp_finish_request
{
    my ($lrwpref) = @_;
    if (! defined ($lrwpref)) {
	warn "lrwp_finish_report: missing parameters";
	return undef;
    }

    my $socket = $lrwpref -> [$LRWP_SOCKET];
    my $pattern = "%0${LRWP_SIZE_BYTES}d";

    if (printf ($socket $pattern, length ($lrwpref -> [$LRWP_OUTDATA]))) {
    }
    else {
	lrwp_cleanup ($lrwpref);
	return undef;
    }

    if (print $socket $lrwpref -> [$LRWP_OUTDATA]) {
    }
    else {
	lrwp_cleanup ($lrwpref);
	return undef;
    }

    lrwp_cleanup ($lrwpref);
    return 1;
}

# Close LRWP connection to server
# Parameters: reference to LRWP structure
# Returns:    1 unless missing parameters (then undef)

sub lrwp_close
{
    if (! defined ($_[0])) {
	return undef; 
    }

    close ($_[0] -> [$LRWP_SOCKET]);
    $_[0] -> [$LRWP_SOCKET] = undef;
    return lrwp_cleanup (@_);
}

# Cleanup LRWP session (clear out posted data, environment, etc)
# Parameters: reference to LRWP structure
# Returns:    1 unless missing parameters (then undef)

sub lrwp_cleanup 
{
    if (! defined ($_[0])) {
	return undef;
    }

    $_[0] -> [$LRWP_CGI]     = undef;
    $_[0] -> [$LRWP_INDATA]  = "";
    $_[0] -> [$LRWP_OUTDATA] = "";
}


# Read all bytes in from handle -- up to the number specified as required.
# If we don't get all of them return undef; otherwise return the whole
# collection of bytes.
#
# Expects: reference to socket to use, number of bytes required.

sub read_all_bytes 
{
    my ($socket, $bytes_required) = @_;
    if (! defined ($socket) || ! defined ($bytes_required)) {
	warn "read_all_bytes: insufficient parameters";
	return undef;
    }

    my $buffer = "";
    my $input  = "";
    while ($bytes_required > 0) {
	$input  = " " x $bytes_required;

	my $bytes = sysread $socket, $input, $bytes_required;

	if ($bytes > 0) {
	    $buffer .= substr($input, 0, $bytes);
	    $bytes_required -= $bytes;
	}
	else {
	    return undef;                      # Error reading from socket
	}
    }

    # If we get this far, we've read all the bytes we need without errors
    return $buffer;
}

# Convert a string containing a list of x=y strings into a hash keyed on 
# the x values and having the y values as the stored value.
# Parameters: string with the list of x=y bits
# Returns:    reference to hash 

sub string_to_hash_ref
{
    my (%hash) = map { split ('=', $_, 2) } (split(/\0/, $_[0]));
    return \%hash;
}

#---------------------------------------------------------------------------
# Mainline
#---------------------------------------------------------------------------

my @lrwp;
my ($appname, $server, $port, $vhost) = @ARGV;

my $statusmsg = lrwp_connect(\@lrwp, @ARGV);
if (defined ($statusmsg)) {
    warn "LRWP error: $statusmsg\n";
    exit 1;
}

printf("Waiting for requests from %s:%s\n", $server, $port);
printf("Try hitting http://%s/%s with your browser...\n",
        defined ($vhost) ? $vhost : $server, $appname);

my $count = 0;
my $buf;

# only handle 5 reqests, then exit 
while ($count < 5 && lrwp_accept_request(\@lrwp)) {
    warn "Accepted new request...\n";
    $count++;

    lrwp_send_string(\@lrwp, "Content-type: text/html\r\n\r\n");
    $buf = sprintf(
	    "<HTML><HEAD><TITLE>LRWP TestApp (%s)</TITLE></HEAD>\n<BODY>\n",
	    $appname);
    lrwp_send_string(\@lrwp, $buf);

    $buf = sprintf("<H2>LRWP test app (%s)</H2><P>", $appname);
    lrwp_send_string(\@lrwp, $buf);

    $buf = sprintf("<b>request count</b> = %d<br>", $count);
    lrwp_send_string(\@lrwp, $buf);

    lrwp_send_string(\@lrwp, "<br><b>post data:</b> ");
    if (length ($lrwp [$LRWP_INDATA])) {
	lrwp_send_string (\@lrwp, "<pre>");
        lrwp_send_string (\@lrwp, $lrwp [$LRWP_INDATA]);
        lrwp_send_string (\@lrwp, "</pre><br>");
    }

    lrwp_send_string(\@lrwp, "<P><HR><P><pre>");

    my $symbol;
    foreach $symbol (sort keys %{$lrwp [$LRWP_CGI]}) {
	$buf = sprintf("<b>%-20s :</b>  %s\n", 
		       $symbol, $lrwp [$LRWP_CGI] -> {$symbol});
        lrwp_send_string(\@lrwp, $buf);
    }

    lrwp_send_string(\@lrwp, "\n</pre><P><HR>\n</BODY></HTML>\n");
    lrwp_finish_request(\@lrwp);
}

lrwp_close(\@lrwp);

exit 0;

