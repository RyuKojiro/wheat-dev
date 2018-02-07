NETBSDSRC= ../NetBSD/src
TOOLDIR= $(NETBSDSRC)/obj/tooldir.Darwin-17.3.0-x86_64
AS=      $(TOOLDIR)/bin/shle--netbsdelf-as
CC=      $(TOOLDIR)/bin/shle--netbsdelf-gcc
LD=      $(TOOLDIR)/bin/shle--netbsdelf-ld
OBJCOPY= $(TOOLDIR)/bin/shle--netbsdelf-objcopy
INCLUDE= -I$(NETBSDSRC)/sys/ -I$(NETBSDSRC)/sys/arch/evbsh3/compile/WHEAT/ -I$(NETBSDSRC)/sys/arch/sh3/include -I$(NETBSDSRC)/include/ -I.
CFLAGS=  -Wall -fpic -Os $(INCLUDE) -DSH4A -D_STANDALONE
ASFLAGS= --little --isa=sh4a
OCFLAGS= -O binary --only-section=.text

OBJS=loader.o serial.o mmc.o

KERNEL=$(NETBSDSRC)/sys/arch/evbsh3/compile/obj/WHEAT/netbsd

send-kernel: send
	expect prepare.exp $(KERNEL)
	./send -s /dev/tty.usbserial-AL020VX7 $(KERNEL)

send-loader: loader.bin
	expect run.exp $<

# TODO: This rule needs fixing, but is set up to use the local cc, rather than the cross-cc
send: send.c
	cc -ggdb -c -o send.o send.c
	cc -o send send.o

# This is meant for loading into RAM/EPROM
loader.bin: $(OBJS)
	$(LD) $(LDFLAGS) -T eprom.ld -o $@ $(OBJS)

# This is meant for loading into flash
loader.srec: $(OBJS)
	$(LD) $(LDFLAGS) -T flash.ld -o $@ $(OBJS)

clean:
	rm -f *.bin *.o *.srec send

.SUFFIXES: .o .bin
.PHONY: clean send-loader send-kernel
.POSIX:
