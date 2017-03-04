TOOLDIR=	../NetBSD/src/obj/tooldir.Darwin-16.3.0-x86_64
AS=			$(TOOLDIR)/bin/shle--netbsdelf-as
OBJCOPY=	$(TOOLDIR)/bin/shle--netbsdelf-objcopy
ASFLAGS=	--little --isa=sh4a
SRC=		counter.s
OBJ=		counter.o
BIN=		counter.bin

run: $(BIN)
	expect run.exp $(BIN)

.o.bin:
	$(OBJCOPY) -O binary $< $@

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f *.bin *.o

.SUFFIXES: .o .s .bin
.PHONY: run clean
.POSIX:
