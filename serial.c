#include "serial.h"

void main() {
	serial_print("Hello, world!\n\r");
	char c = serial_getchar();
	serial_putchar(c);
	serial_print("\n\r");
}

char serial_getchar() {
	volatile short *status_register = 0xFFE00010;
	volatile char *in_register = 0xFFE00014;
	volatile short *port_register = 0xFFE00024;

startOver:
	if(*status_register & 0x9C) {
		*status_register &= 0x63;
		goto startOver;
	}
	if(*port_register & 0x01) {
		*port_register ^= *port_register;
		*status_register &= 0x63;
		goto startOver;
	}
	if(!(*status_register & 0x02)) {
		goto startOver;
	}

	char result = *in_register;

	*status_register &= 0xFD;

	return result;
}

void serial_putchar(const char c) {
	volatile short *status_register = 0xFFE00010;
	volatile char *out_register = 0xFFE0000C;

	/* Spin lock until transmit enable flag is set */
	while(!(*status_register & 0x20));

	/* Load the character into the fifo register */
	*out_register = c;

	/* Set flags to send byte */
	*status_register &= 0x9F;
}

void serial_print(const char *string) {
	while(*string) {
		serial_putchar(*string++);
	}
}

