#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sysexits.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "loader.h"

#define NSEC_PER_SEC      (1000000000ULL)
#define DEFAULT_BAUD_RATE 115200
#define BLOCK_SIZE        32

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

static size_t rate(struct timespec start, struct timespec now, size_t bytes) {
	struct timespec diff;
	diff.tv_sec = now.tv_sec - start.tv_sec;
	diff.tv_nsec = now.tv_nsec - start.tv_nsec;

	size_t rate = 0;

	if (diff.tv_sec != 0) {
		rate += bytes/diff.tv_sec;
	}

	if (diff.tv_nsec != 0) {
		rate += bytes/diff.tv_nsec/NSEC_PER_SEC;
	}

	return rate;
}

static void send(const int sock, const char *filename) {
	struct stat s;
	if(stat(filename, &s)) {
		errx(EX_IOERR, "stat");
	}
	const size_t totalSize = s.st_size;

	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC, &start);

	FILE *in = fopen(filename, "r");
	char buf[BLOCK_SIZE];
	size_t offset = 0;
	size_t bytesRead;
	struct timespec now;
	size_t bps;
	long remaining = 0;
	while((bytesRead = fread(buf, 1, BLOCK_SIZE, in))) {
		offset += bytesRead;
		clock_gettime(CLOCK_MONOTONIC, &now);
		bps = rate(start, now, offset);
		if (bps) {
			remaining = (totalSize - offset) / bps;
		}

		fprintf(stderr,
				"%#08zx - "
				"%zu/%zu bytes - "
				"%zu bytes/sec - "
				"%zu%% - "
				"%lum%lus remaining  \r",
				offset + (size_t)LOAD_ADDR,
				offset, totalSize,
				bps,
				(offset * 100) / totalSize,
				remaining / 60, remaining % 60
				);
		write(sock, buf, bytesRead);
	}

	// FIXME: This is just here temporarily, since it looks like tcdrain is broken on my host OS
	sleep(10);
	fprintf(stderr, "\n");
	fclose(in);
}

int main(int argc, char * const argv[]) {
	/*
	 * The expected usage is something along the lines of:
	 *     send -b 9600 -s /dev/sttynode file_to_send ...
	 */

	speed_t baud = DEFAULT_BAUD_RATE;
	int ch;
	const char *node = NULL;
	while ((ch = getopt(argc, argv, "b:s:")) != -1) {
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

	send(out, argv[0]);

	close(out);

	return EX_OK;
}
