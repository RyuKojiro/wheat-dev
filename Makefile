TOOLDIR= ../NetBSD/src/obj/tooldir.Darwin-17.3.0-x86_64
AS=      $(TOOLDIR)/bin/shle--netbsdelf-as
CC=      $(TOOLDIR)/bin/shle--netbsdelf-gcc
LD=      $(TOOLDIR)/bin/shle--netbsdelf-ld
OBJCOPY= $(TOOLDIR)/bin/shle--netbsdelf-objcopy
CFLAGS=  -Os
ASFLAGS= --little --isa=sh4a
LDFLAGS= -T eprom.ld
OCFLAGS= -O binary --only-section=.text

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
