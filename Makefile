TOOLDIR=	../NetBSD/src/obj/tooldir.Darwin-16.3.0-x86_64
AS=			$(TOOLDIR)/bin/shle--netbsdelf-as
OBJCOPY=	$(TOOLDIR)/bin/shle--netbsdelf-objcopy
ASFLAGS=	--little --isa=sh4a
SRC=		test.s
OBJ=		counter.o
BIN=		counter.bin

run: $(BIN)
	expect run.exp $(BIN)

$(BIN): $(OBJ)
	$(OBJCOPY) -O binary $(OBJ) $(BIN)

$(OBJ): $(SRC)
	$(AS) $(ASFLAGS) -o $(OBJ) $(SRC)

.PHONY: run
.POSIX:
