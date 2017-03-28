#include <sys/stdbool.h>

#include "serial.h"

#define LINE_LEN 20

static void loadFromSerial(void) {
	char line[LINE_LEN];
	serial_print("Enter kernel size in bytes: ");
	serial_getline(line, LINE_LEN);
	serial_print("You entered: ");
	serial_print(line);
}

static void loadFromSD(void) {
	serial_print("Booting from SD cards is not yet implemented.\n\r");
}

static void reboot(void) {
	/* Jump to the reset vector */
	__asm__("mov.l @(4,pc),r0");
	__asm__("jmp @r0");
	__asm__(".long 0xA0000000");
}

int main(void) {
	/* Print the options */
	serial_print(">> NetBSD/sh3 Serial & SD Bootloader.\n\r");

	/* Get a selection */
	char selection;
	for(;;) {
		serial_print("\n\r"
					 "\t1. Load kernel via serial\n\r"
					 "\t2. Boot from SD Card\n\r"
					 "\t3. Reboot\n\r"
					 "\n\r"
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
			case '3': {
				reboot();
			} break;
			default:
				serial_print("Invalid option.\n\r");
		}
	}
}
