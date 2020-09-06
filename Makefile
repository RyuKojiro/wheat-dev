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
CFLAGS=  -Os $(INCLUDE) -DSH4A -ggdb
ASFLAGS= --little --isa=sh4a
OCFLAGS= -O binary --only-section=.text
KERNCONF=$(TOOLSRC)/sys/arch/evbsh3/conf/WHEAT
KERNEL=  $(TOOLSRC)/sys/arch/evbsh3/compile/obj/WHEAT/netbsd
LOADEROBJS= loader.o serial.o mmc.o lcd.o
CONSOLE=/dev/tty.usbserial-wheat
BAUD=115200

####################
## Kernel Sending ##
####################

netbsd: netbsd.bin send loader
	./relay-resetcpu.sh
	expect prepare.exp netbsd.bin
	./send -s $(CONSOLE) netbsd.bin
	$(MAKE) serial

send: send.c
	cc -ggdb -c -o send.o send.c
	cc -o send send.o

####################
#### Boot Loader ###
####################

loader-flash: loader.srec
	$(MAKE) flash SREC=$<

loader: loader.bin
	$(MAKE) ram BIN=$<

loader.elf: $(LOADEROBJS)
	$(LD) $(LDFLAGS) -T eprom.ld -o $@ $(LOADEROBJS)

####################
###### Kernel ######
####################

netbsd.bin: $(KERNEL)
	$(OBJCOPY) -O binary $< $@

netbsd.srec: $(KERNEL)
	$(OBJCOPY) -O srec $< $@

$(KERNEL): $(CC) $(KERNCONF)
	cd $(TOOLSRC) && ./build.sh -a sh3el -m evbsh3 -j 12 -U kernel=WHEAT

$(KERNCONF): WHEAT
	ln -s $(PWD)/$< $@

####################
##### Bringup ######
####################

# This announces the program counter from flash
anac-flash: anac.srec
	$(MAKE) flash SREC=$<

# This assembly announces the program counter via the LED display
anac: anac.bin
	$(MAKE) ram BIN=$<

# Same as counter, but implemented in C
ccounter: ccounter.bin
	$(MAKE) ram BIN=$<

simple-flash: simple.srec
	$(MAKE) flash SREC=$<

# This is a very rudimentary C program, just to test the basics
simple: simple.bin
	$(MAKE) ram BIN=$<

# This is a very simple LED counter implemented in assembly
counter: counter.bin
	$(MAKE) ram BIN=$<

# This assembly promises to run only position independent code
pic: pic.bin
	$(MAKE) ram BIN=$<

####################
### Code Loading ###
####################

flash: $(SREC)
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect flash.exp $<
	./relay-bootflash.sh
	./relay-resetcpu.sh

ram: $(BIN)
	./relay-bootrom.sh
	./relay-resetcpu.sh
	expect run.exp $<

####################
### Suffix Rules ###
####################

.o.elf:
	$(LD) $(LDFLAGS) -T eprom.ld -o $@ $<

.bin.srec:
	$(OBJCOPY) -I binary -O srec $< $@

.elf.bin:
	$(OBJCOPY) -O binary $< $@

.s.o: $(CC)
	$(CC) $(CFLAGS) -c -o $@ $<

####################
###### Tools #######
####################

$(CC): $(TOOLSRC)/obj
	echo "No tools..."
	cd $(TOOLSRC) && ./build.sh -a sh3el -m evbsh3 -j 12 -U tools

$(TOOLSRC)/obj:
	export CVSROOT="anoncvs@anoncvs.NetBSD.org:/cvsroot"
	export CVS_RSH="ssh"
	cvs checkout -A -P src
	cd $(TOOLSRC) && patch -p0 < ../netbsd.patch
	mkdir $(TOOLSRC)/obj

####################
### Other Stuff ####
####################

serial:
	screen $(CONSOLE) $(BAUD)

clean:
	rm -f *.o *.bin *.srec *.elf $(KERNEL)

.SUFFIXES: .o .bin .srec .elf
.PHONY: clean serial
.POSIX:
