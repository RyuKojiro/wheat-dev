AS=			../NetBSD/src/obj/tooldir.Darwin-16.3.0-x86_64/bin/shle--netbsdelf-as
ASFLAGS=	--little --isa=sh4a
SRC=		test.s
BIN=		counter.o

$(BIN): $(SRC)
	$(AS) $(ASFLAGS) -o $(BIN) $(SRC)
