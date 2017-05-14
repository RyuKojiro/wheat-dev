#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <termios.h>
#include <unistd.h>

static void usage() {
	fprintf(stderr, "usage: send [-b baud] /dev/node < input\n");
	exit(EX_USAGE);
}

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

static void send(int in, int out) {
}

int main(int argc, char * const argv[]) {
	/*
	 * The expected usage is something along the lines of:
	 *     send /dev/sttynode < file_to_send
	 */

	int baud = 115200;
	int ch;
	while ((ch = getopt(argc, argv, "b:")) != -1) {
		switch (ch) {
			case 'b': {
				baud = atoi(optarg);
			} break;
			case '?':
			default: {
				usage();
			}
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1) {
		warnx("You must supply exactly one serial device node as an argument");
		usage();
	}

	const int fd = open(argv[argc-1], O_RDWR | O_NOCTTY | O_SYNC);
	configure(fd, baud);
	send(fileno(stdin), fd);
	close(fd);

	return EX_OK;
}
