#include <sys/stdint.h>
#include <scifreg.h>

#include "serial.h"

char serial_getchar() {
startOver:
	if(SHREG_SCSSR2 & 0x9C) {
		SHREG_SCSSR2 &= 0x63;
		goto startOver;
	}
	if(SHREG_SCLSR2 & 0x01) {
		SHREG_SCLSR2 ^= SHREG_SCLSR2;
		SHREG_SCSSR2 &= 0x63;
		goto startOver;
	}
	if(!(SHREG_SCSSR2 & 0x02)) {
		goto startOver;
	}

	char result = SHREG_SCFRDR2;

	SHREG_SCSSR2 &= 0xFD;

	return result;
}

int serial_getline(char *buf, int len) {
	/* TODO: handle backspace */
	char c;
	int i;
	for(i = 0; i < len - 1; i++) {
		c = serial_getchar();
		serial_putchar(c);
		if(c == '\r') {
			serial_putchar('\n');
			break;
		}

		buf[i] = c;
	}
	buf[i] = '\0';
	return i;
}

void serial_putchar(const char c) {
	/* Spin lock until transmit enable flag is set */
	while(!(SHREG_SCSSR2 & 0x20));

	/* Load the character into the fifo register */
	SHREG_SCFTDR2 = c;

	/* Set flags to send byte */
	SHREG_SCSSR2 &= 0x9F;
}

void serial_print(const char *string) {
	while(*string) {
		serial_putchar(*string++);
	}
}

void serial_init(void) {
	/* Reverse engineered voodoo */
	SHREG_SCSCR2 = 0;
	SHREG_SCFCR2 = 6;
	SHREG_SCSSR2 = 0;
	SHREG_SCSCR2 = 2;
	SHREG_SCSMR2 = 0;
	SHREG_SCFCR2 = 0;
	SHREG_SCSCR2 = 0x32;
}
