#include <sys/stdbool.h>
#include <stddef.h>

#include "serial.h"

#define LINE_LEN 20
#define LOAD_ADDR 0x09000000
#define RESET_VEC 0xA0000000

#define JUMP_TO_ADDRESS(addr) \
	__asm__("mov.l @(4,pc),r0"); \
	__asm__("jmp @r0"); \
	__asm__(".long " # addr); \

static void bootKernel(void) {
	JUMP_TO_ADDRESS(LOAD_ADDR);
}

static void reboot(void) {
	JUMP_TO_ADDRESS(RESET_VEC);
}

/*
 * The len argument here is the actual length of the string,
 * not larger, not smaller.
 */
static size_t lengthFromDecimalString(int len, const char *buf) {
	size_t result = 0;
	while(len) {
		result *= 10;
		result += buf[len--];
	}
	return result;
}

static void loadFromSerial(void) {
	char line[LINE_LEN];
	serial_print("Enter kernel size in bytes: ");
	int len = serial_getline(line, LINE_LEN);
	size_t size = lengthFromDecimalString(len, line);
	serial_print("You entered: ");
	serial_print(line);
}

static void loadFromSD(void) {
	serial_print("Booting from SD cards is not yet implemented.\n\r");
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
