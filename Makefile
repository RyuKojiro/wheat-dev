TOOLDIR= ../NetBSD/src/obj/tooldir.Darwin-16.3.0-x86_64
AS=      $(TOOLDIR)/bin/shle--netbsdelf-as
CC=      $(TOOLDIR)/bin/shle--netbsdelf-gcc
OBJCOPY= $(TOOLDIR)/bin/shle--netbsdelf-objcopy
ASFLAGS= --little --isa=sh4a
OCFLAGS= -O binary --only-section=.text

simple: simple.bin
	expect run.exp $<

counter: counter.bin
	expect run.exp $<

ccounter: ccounter.bin
	expect run.exp $<

.o.bin:
	$(OBJCOPY) $(OCFLAGS) $< $@

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f *.bin *.o

.SUFFIXES: .o .s .bin
.PHONY: run clean
.POSIX:
