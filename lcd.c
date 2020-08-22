#include "lcd.h"

void lcd_print(const char *string) {
	for (int i = 0; string[i] ; i++) {
		lcdStorage[i*2] = string[i];
	}
}
