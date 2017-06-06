#!/usr/bin/perl

use warnings;
use strict;

# S31510000000862F38C7962FA62FB62FC62FD62F35DC9C
# AABBCCCCCCCCDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDEE
# A - Record Type
# B - Byte Count
# C - Address
# D - Data
# E - Checksum
#
# This script shifts an S-record that targets 0x10000000, to instead target
# 0x8c000000, which is the location of flash when booted from EPROM. This
# allows the linker to arrange things as they need to be when booted from
# flash, but allows the S-record to be written from EPROM.


while(<>) {
	if($_ =~ /S3([0-9A-F]{2})([0-9A-F]{8})([0-9A-F]*)([0-9A-F]{2})/) {
		print "size $1\n";
		print "addr $2\n";
		print "data $3\n";
		print "csum $4\n";
	}
}
