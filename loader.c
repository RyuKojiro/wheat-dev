#include <sys/stdbool.h>
#include <stddef.h>

#include "serial.h"

#define LINE_LEN   20
#define CHUNK_SIZE 100
#define LOAD_ADDR  0x09000000
#define RESET_VEC  0xA0000000

#define _STRINGIFY(a) #a
#define STRINGIFY(a) _STRINGIFY(a)

#define JUMP_TO_ADDRESS(addr) { \
	asm volatile (".align 3"); \
	asm volatile ("mov.l @(4,pc),r0"); \
	asm volatile ("jmp @r0"); \
	asm volatile (".long " STRINGIFY(addr)); \
}

static void bootKernel(void) {
	JUMP_TO_ADDRESS(LOAD_ADDR);
}

static void reboot(void) {
	JUMP_TO_ADDRESS(RESET_VEC);
}

static size_t lengthFromDecimalString(int len, const char *buf) {
	size_t result = 0;
	for(int i = 0; i < len && buf[i]; i++) {
		result *= 10;
		result += buf[i] - '0';
	}
	return result;
}

static void loadFromSerial(void) {
	char line[LINE_LEN];
	serial_print("Enter kernel size in bytes: ");
	int len = serial_getline(line, LINE_LEN);
	size_t size = lengthFromDecimalString(len, line);

	serial_print("Send kernel when ready.\n\r");
	char *zone = (char *)LOAD_ADDR;
	serial_putchar('.');
	for(size_t o = 0; o < size; o++) {
		zone[o] = serial_getchar();

		if (o % CHUNK_SIZE == 0) {
			serial_putchar('.');
		}
	}
	serial_print("Done loading. Commencing boot.\n\r");
	bootKernel();
}

static void loadFromSD(void) {
	serial_print("Booting from SD cards is not yet implemented.\n\r");
}

int main(void) {
	serial_print(">> NetBSD/sh3 Serial & SD Bootloader.\n\r");

	char selection;
	for(;;) {
		/* Print the options */
		serial_print("\n\r"
		             "\t1. Load kernel via serial\n\r"
		             "\t2. Boot from SD Card\n\r"
		             "\t3. Reboot\n\r"
		             "\n\r"
		             "Choose an Option: ");

		/* Get a selection */
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
