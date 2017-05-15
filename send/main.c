#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sysexits.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT_BAUD_RATE 115200
#define BLOCK_SIZE        512
#define START_ADDRESS     0x08000000

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

static void send(const int sock, const char *filename) {
	struct stat s;
	if(stat(filename, &s)) {
		errx(EX_IOERR, "stat");
	}
	const off_t totalSize = s.st_size;

	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC, &start);

	FILE *in = fopen(filename, "r");
	int rate = 0;
	char buf[BLOCK_SIZE];
	off_t offset = 0;
	size_t bytesRead;
	struct timespec now, elapsed;
	while((bytesRead = fread(buf, BLOCK_SIZE, 1, in))) {
		offset += bytesRead;

		clock_gettime(CLOCK_MONOTONIC, &now);
		elapsed.tv_sec = now.tv_sec - start.tv_sec;
		elapsed.tv_nsec = now.tv_nsec - start.tv_nsec;

		fprintf(stderr, "%#08llx - %lld/%lld bytes - %d bytes/sec - %lld%% - %u remaining\r",
				offset + START_ADDRESS,
				offset,
				totalSize,
				rate,
				(offset * 100) / totalSize,
				0
				);
		write(sock, buf, bytesRead);
	}
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
