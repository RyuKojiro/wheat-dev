#include "lcd.h"

void main() {
	static char string[] = "It's C! ";

	for (int i = 0; i < sizeof(string); i++) {
		lcdStorage[i*2] = string[i];
	}

	__asm__("sleep");
}
