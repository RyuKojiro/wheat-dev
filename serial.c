#include <sys/stdint.h>
#include <scifreg.h>

#include "serial.h"

void main() {
	serial_print("Hello, world!\n\r");
	char c = serial_getchar();
	serial_putchar(c);
	serial_print("\n\r");
}

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

