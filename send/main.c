#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define BLOCK_SIZE 512

__attribute__((noreturn)) static void usage(void) {
	fprintf(stderr, "usage: send [-b baud] -s /dev/node input ...\n");
	exit(EX_USAGE);
}

static void configure(const int fd, const speed_t baud) {
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

static void send(FILE *in, const int out) {
	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC, &start);

	size_t totalSize = 0;
	int rate = 0;
	int percent = 0;
	int timeRemaining = 0;
	char buf[BLOCK_SIZE];
	off_t offset = 0;
	size_t bytesRead;
	while((bytesRead = fread(buf, BLOCK_SIZE, 1, in))) {
		offset += bytesRead;
		fprintf(stderr, "%#08llx - %lld/%lu bytes - %d bytes/sec - %u%% - %u remaining\r",
				offset + 0x80000000,
				offset,
				totalSize,
				rate,
				percent,
				timeRemaining
				);
		write(out, buf, bytesRead);
	}
}

int main(int argc, char * const argv[]) {
	/*
	 * The expected usage is something along the lines of:
	 *     send -b 9600 -s /dev/sttynode file_to_send ...
	 */

	speed_t baud = 115200;
	int ch;
	const char *node = NULL;
	while ((ch = getopt(argc, argv, "b:")) != -1) {
		switch (ch) {
			case 'b': {
				baud = strtoul(optarg, NULL, 10);
			} break;
			case 's': {
				node = optarg;
			} break;
			case '?':
			default: {
				usage();
			}
		}
	}
	argc -= optind;
	argv += optind;

	if (!node) {
		warnx("You must specify a valid serial device node");
		usage();
	}

	const int out = open(node, O_RDWR | O_NOCTTY | O_SYNC);
	configure(out, baud);

	FILE *in = fopen(argv[0], "r");
	send(in, out);
	fclose(in);

	close(out);

	return EX_OK;
}
