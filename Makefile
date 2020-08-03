
TOOLSRC= src
TOOLDIR= $(TOOLSRC)/obj/tooldir.Darwin-17.3.0-x86_64
AS=      $(TOOLDIR)/bin/shle--netbsdelf-as
CC=      $(TOOLDIR)/bin/shle--netbsdelf-gcc
LD=      $(TOOLDIR)/bin/shle--netbsdelf-ld
OBJCOPY= $(TOOLDIR)/bin/shle--netbsdelf-objcopy
CFLAGS=  -Os
ASFLAGS= --little --isa=sh4a
OCFLAGS= -O binary --only-section=.text

# This assembly promises to run only position independent code
pic: pic.bin
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect run.exp $<

# This assembly announces the program counter via the LED display
anac: anac.bin
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect run.exp $<

# This is a very rudimentary C program, just to test the basics
simple: simple.bin
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect run.exp $<

# This is a very simple LED counter implemented in assembly
counter: counter.bin
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect run.exp $<

# Same as counter, but implemented in C
ccounter: ccounter.bin
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect run.exp $<

.o.bin:
	$(LD) $(LDFLAGS) -T eprom.ld -o $@ $<

.s.o: $(CC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TOOLDIR)/bin/shle--netbsdelf-gcc: $(TOOLSRC)/obj
	echo "No tools..."
	cd $(TOOLSRC) && ./build.sh -a sh3el -m evbsh3 -j 12 -U build

$(TOOLSRC)/obj:
	export CVSROOT="anoncvs@anoncvs.NetBSD.org:/cvsroot"
	export CVS_RSH="ssh"
	cvs checkout -A -P src
	mkdir $(TOOLSRC)/obj

clean:
	rm -f *.bin *.o

.SUFFIXES: .o .bin
.PHONY: clean
.POSIX:
