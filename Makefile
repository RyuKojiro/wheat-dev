AS=			../NetBSD/src/obj/tooldir.Darwin-16.3.0-x86_64/bin/shle--netbsdelf-as
ASFLAGS=	--little --isa=sh4a
SRC=		counter.s
BIN=		counter.bin

$(BIN): $(SRC)
	$(AS) $(ASFLAGS) $(SRC)
