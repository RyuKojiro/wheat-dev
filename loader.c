#include <sys/stdbool.h>

#include "serial.h"

static void loadFromSerial(void) {
	serial_print("Enter kernel size in bytes: ");
	//serial_getline(line);
}

static void loadFromSD(void) {
	serial_print("Loading from SD cards is not yet implemented.\n\r");
}

int main(void) {
	/* Print the options */
	serial_print(">> NetBSD/sh3 Serial & SD Bootloader. Version 0.0\n\r"
	             "\n\r"
	             "\t1. Load via serial\n\r"
	             "\t2. Load from SD Card\n\r");

	/* Get a selection */
	char selection;
	for(;;) {
		serial_print("\n\r"
					 "Choose an Option: ");

		selection = serial_getchar();
		serial_putchar(selection);
		serial_print("\n\r");

		/* Act on the selection */
		switch(selection) {
			case '1': {
				loadFromSerial();
			} break;
			case '2': {
				loadFromSD();
			} break;
			default:
				serial_print("Invalid option.\n\r");
		}
	}
}
