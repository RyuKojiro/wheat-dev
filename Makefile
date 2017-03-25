TOOLDIR= ../NetBSD/src/obj/tooldir.Darwin-16.3.0-x86_64
AS=      $(TOOLDIR)/bin/shle--netbsdelf-as
CC=      $(TOOLDIR)/bin/shle--netbsdelf-gcc
LD=      $(TOOLDIR)/bin/shle--netbsdelf-ld
OBJCOPY= $(TOOLDIR)/bin/shle--netbsdelf-objcopy
CFLAGS=  -fpic -Os
ASFLAGS= --little --isa=sh4a
LDFLAGS= -T wheat.ld
OCFLAGS= -O binary --only-section=.text

serial: serial.bin
	expect run.exp $<

simple: simple.bin
	expect run.exp $<

counter: counter.bin
	expect run.exp $<

ccounter: ccounter.bin
	expect run.exp $<

.o.bin:
	$(LD) $(LDFLAGS) -o $@ $<

clean:
	rm -f *.bin *.o

.SUFFIXES: .o .bin
.PHONY: clean
.POSIX:
