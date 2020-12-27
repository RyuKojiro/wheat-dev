#include <sys/stdbool.h>
#include <sys/reboot.h>
#include <stddef.h>
#include <stdint.h>

#include "serial.h"
#include "loader.h"
#include "lcd.h"

#define LINE_LEN   20
#define CHUNK_SIZE 100
#define RESET_VEC  ((void *)0xA0000000)

#define _STRINGIFY(a) #a
#define STRINGIFY(a) _STRINGIFY(a)

static void go(void *addr) {
	(*(void (*)(void))addr)();
}

static void reboot(void) {
	go(RESET_VEC);
}

static size_t lengthFromDecimalString(int len, const char *buf) {
	size_t result = 0;
	for(int i = 0; i < len && buf[i]; i++) {
		result *= 10;
		result += buf[i] - '0';
	}
	return result;
}

static int fromhexnibble(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'f')
		return c - 'a';
	else if (c >= 'A' && c <= 'F')
		return c - 'A';
	else
		return 0;
}

static char nibbletohex(char nibble) {
	if (nibble <= 9)
		return nibble + '0';
	else
		return nibble - 0xA + 'A';
}

static void printhex(char byte) {
	serial_putchar(nibbletohex((byte >> 4) & 0xF));
	serial_putchar(nibbletohex(byte & 0xF));
}

static void displayHexOnLCD(uint32_t p) {
	char string[8];
	for(int i = 0; i < sizeof(p)*2; i++) {
		string[i] = nibbletohex(p >> ((sizeof(p)*8)-4));
		p <<= 4;
	}
	lcd_print(string);
}

static void *addressFromHexString(int len, const char *buf) {
	unsigned long result = 0;
	for(int i = 0; i < len && buf[i]; i++) {
		result <<= 4;
		result += fromhexnibble(buf[i]);
	}
	return (void *)result;
}

static void bootKernel(void) {
	go(LOAD_ADDR);
}

static void bootAddress(void) {
	char line[LINE_LEN];
	serial_print("Enter eight hex digit address: ");
	int len = serial_getline(line, LINE_LEN);
	void *l = addressFromHexString(len, line);

	serial_print("Booting to ");
	for(int i = 4; i > 0; i--) {
		printhex(((int)l >> i) & 0xFF);
	}
	serial_print("...\n\r");
	go(l);
}

static void loadFromSerialToAddress(void *addr) {
	char line[LINE_LEN];
	serial_print("Enter kernel size in bytes: ");
	int len = serial_getline(line, LINE_LEN);
	size_t size = lengthFromDecimalString(len, line);
	displayHexOnLCD(size);

	serial_print("Send kernel when ready.\n\r");
	char *zone = (char *)addr;
	//serial_putchar('.');
	for(size_t o = 0; o < size; o++) {
		displayHexOnLCD((uint32_t)(zone+o));
		zone[o] = serial_getchar();

		/*
		if (o % CHUNK_SIZE == 0) {
			serial_putchar('.');
		}
		*/
	}
	serial_print("\n\rDone loading.\n\r");
}

static void loadFromSerial(void) {
	loadFromSerialToAddress(LOAD_ADDR);
	serial_print("Commencing boot.\n\r");
	bootKernel();
}

static void loadFromSD(void) {
	serial_print("Booting from SD cards is not yet implemented.\n\r");
}

static void showKernel(void) {
	const char *kernel = LOAD_ADDR;
	for(int i = 0; i < 0xff; i++) {
		if (i % 0xf == 0)
			serial_print("\n\r");

		printhex(kernel[i]);
	}
}

int main(void) {
	lcd_print("Bootload");

	serial_init();
	serial_print("\n\r");
	serial_print(">> NetBSD/sh3 Serial & SD Bootloader.\n\r");
	serial_print(">> Built on " __DATE__ " " __TIME__ "\n\r");
	char selection;
	for(;;) {
		/* Print the options */
		serial_print("\n\r"
		             "\t1. Load kernel via serial\n\r"
		             "\t2. Boot from SD Card\n\r"
		             "\t3. Reboot\n\r"
		             "\t4. Boot to " STRINGIFY(LOAD_ADDR) "\n\r"
		             "\t5. Boot to address\n\r"
		             "\t6. Show start of kernel\n\r"
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
			case '4': {
				bootKernel();
			} break;
			case '5': {
				bootAddress();
			} break;
			case '6': {
				showKernel();
			} break;
			default:
				serial_print("Invalid option.\n\r");
		}
	}
}
