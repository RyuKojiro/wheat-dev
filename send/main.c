#include <stdio.h>
#include <sysexits.h>
#include <err.h>

int main(int argc, const char * const argv[]) {
	if (argc < 2) {
		errx(EX_USAGE, "You must supply the serial device node as an argument");
	}

	return EX_OK;
}
