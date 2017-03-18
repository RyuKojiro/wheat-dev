static void main() {
	char *lcdStorage = (char *)0xBA202070;
	char string[] = "It's C! ";

	for (int i = 0; i < sizeof(string); i++) {
		lcdStorage[i*2] = string[i];
	}

	__asm__("sleep");
}
