OSNAME:=$(shell uname -s)
OSVERS:=$(shell uname -r)
OSARCH:=$(shell uname -m)
TOOLSRC= src
TOOLDIR= $(TOOLSRC)/obj/tooldir.$(OSNAME)-$(OSVERS)-$(OSARCH)
AS=      $(TOOLDIR)/bin/shle--netbsdelf-as
CC=      $(TOOLDIR)/bin/shle--netbsdelf-gcc
LD=      $(TOOLDIR)/bin/shle--netbsdelf-ld
OBJCOPY= $(TOOLDIR)/bin/shle--netbsdelf-objcopy
INCLUDE= -I$(TOOLSRC)/sys/ -I$(TOOLSRC)/sys/arch/evbsh3/compile/WHEAT/ -I$(TOOLSRC)/sys/arch/sh3/include -I$(TOOLSRC)/include/ -I$(TOOLSRC)/obj/destdir.evbsh3/usr/include/ -I.
CFLAGS=  -Os $(INCLUDE) -DSH4A
ASFLAGS= --little --isa=sh4a
OCFLAGS= -O binary --only-section=.text
KERNCONF=$(TOOLSRC)/sys/arch/evbsh3/conf/WHEAT
KERNEL=  $(TOOLSRC)/sys/arch/evbsh3/compile/obj/WHEAT/netbsd
LOADEROBJS= loader.o serial.o mmc.o

####################
#### Boot Loader ###
####################

flash-loader: loader.srec
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect flash-loader.exp $<
	./relay-bootflash.sh
	./relay-resetcpu.sh

# This is meant for loading into flash
loader.srec: $(LOADEROBJS)
	$(LD) $(LDFLAGS) -T flash.ld -o $@ $(LOADEROBJS)

# This is meant for loading into RAM
loader.bin: $(LOADEROBJS)
	$(LD) $(LDFLAGS) -T eprom.ld -o $@ $(LOADEROBJS)

####################
###### Kernel ######
####################

netbsd.srec: $(KERNEL)
	$(OBJCOPY) -O srec $< $@

$(KERNEL): $(CC) $(KERNCONF)
	cd $(TOOLSRC) && ./build.sh -a sh3el -m evbsh3 -j 12 -U -u kernel=WHEAT

$(KERNCONF): WHEAT
	ln -s $(PWD)/$< $@

####################
##### Bringup ######
####################

# This announces the program counter from flash
anac-flash: anac.srec
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect flash.exp $<
	./relay-bootflash.sh
	./relay-resetcpu.sh

# This assembly announces the program counter via the LED display
anac: anac.bin
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect run.exp $<

# Same as counter, but implemented in C
ccounter: ccounter.bin
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

# This assembly promises to run only position independent code
pic: pic.bin
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect run.exp $<

####################
### Suffix Rules ###
####################

.o.srec:
	$(OBJCOPY) -O srec $< $@

.o.bin:
	$(LD) $(LDFLAGS) -T eprom.ld -o $@ $<

.s.o: $(CC)
	$(CC) $(CFLAGS) -c -o $@ $<

####################
###### Tools #######
####################

$(TOOLDIR)/bin/shle--netbsdelf-gcc: $(TOOLSRC)/obj
	echo "No tools..."
	cd $(TOOLSRC) && ./build.sh -a sh3el -m evbsh3 -j 12 -U tools

$(TOOLSRC)/obj:
	export CVSROOT="anoncvs@anoncvs.NetBSD.org:/cvsroot"
	export CVS_RSH="ssh"
	cvs checkout -A -P src
	cd $(TOOLSRC) && patch -p0 < ../netbsd.patch
	mkdir $(TOOLSRC)/obj

clean:
	rm -f *.o *.bin *.srec

.SUFFIXES: .o .bin .srec
.PHONY: clean
.POSIX:
