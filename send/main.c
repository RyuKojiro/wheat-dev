#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <sysexits.h>
#include <termios.h>
#include <unistd.h>

static void configure(const int fd, const int baud) {
	struct termios tty = {0};

	if (tcgetattr(fd, &tty) != 0) {
		err(EX_NOINPUT, "tcgetattr");
	}

	cfsetispeed(&tty, baud);
	cfsetospeed(&tty, baud);

	if (tcsetattr(fd, TCSANOW, &tty) != 0) {
		err(EX_OSERR, "tcsetattr");
	}
}

int main(int argc, const char * const argv[]) {
	/*
	 * The expected usage is something along the lines of:
	 *     send /dev/sttynode < file_to_send
	 */

	if (argc < 2) {
		errx(EX_USAGE, "You must supply the serial device node as an argument");
	}

	const int baud = 115200;
	const int fd = open(argv[argc-1], O_RDWR | O_NOCTTY | O_SYNC);

	configure(fd, baud);


	close(fd);

	return EX_OK;
}
