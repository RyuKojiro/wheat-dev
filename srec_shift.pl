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
		my $len = $1;
		my $addr = hex($2) - 0x10000000 + 0x8c000000;
		my $data = $3;
		my @bytes = ( $3 =~ m/../g );
		my $checksum = 0;
		foreach my $byte (@bytes) {
			$checksum = $checksum ^ hex($byte);
		}
		my $result = sprintf("S3%s%02X%s%02X\n", $len, $addr, $data, $checksum);
		print $result;
	}
}
