#include "serial.h"

void main() {
	serial_print("Hello, world!");
}

void serial_putchar(const char c) {
	volatile short *status_register = 0xFFE00010;
	volatile char *fifo_register = 0xFFE0000C;

	/* Spin lock until transmit enable flag is set */
	while(!(*status_register & 0x20));

	/* Load the character into the fifo register */
	*fifo_register = c;

	/* Set flags to send byte */
	*status_register &= 0x9F;
}

void serial_print(const char *string) {
	while (*string) {
		serial_putchar(*string++);
	}
}

