PROG=send
OBJS=main.o

run: $(PROG)
	./prepare.exp
	./$(PROG) -s /dev/tty.usbserial-AL020VX7 ~/Code/NetBSD/src/wheatkernel

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

clean:
	rm -f $(OBJS)
