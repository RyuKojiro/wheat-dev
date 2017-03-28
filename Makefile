TOOLDIR= ../NetBSD/src/obj/tooldir.Darwin-16.3.0-x86_64
AS=      $(TOOLDIR)/bin/shle--netbsdelf-as
CC=      $(TOOLDIR)/bin/shle--netbsdelf-gcc
LD=      $(TOOLDIR)/bin/shle--netbsdelf-ld
OBJCOPY= $(TOOLDIR)/bin/shle--netbsdelf-objcopy
INCLUDE= -I../NetBSD/src/sys/ -I../NetBSD/src/sys/arch/evbsh3/compile/WHEAT/ -I../NetBSD/src/sys/arch/sh3/include
CFLAGS=  -Wall -fpic -Os $(INCLUDE) -DSH4A
ASFLAGS= --little --isa=sh4a
LDFLAGS= -T wheat.ld
OCFLAGS= -O binary --only-section=.text

loader: loader.bin
	expect run.exp $<

loader.bin: loader.o serial.o
	$(LD) $(LDFLAGS) -o $@ $?

serial: serial.bin
	expect run.exp $<

serial.bin: serial.o
	$(LD) $(LDFLAGS) -o $@ $?

clean:
	rm -f *.bin *.o

.SUFFIXES: .o .bin
.PHONY: clean
.POSIX:
