
static void lcdDisplayNumber(long number);

int main() {
	for(long i = 0;; i++) {
		lcdDisplayNumber(i);
	}

	return 0;
}

static void lcdDisplayCharacter(int digit, char c) {
	char *lcdStorage = (char *)0xBA202070;
	lcdStorage[digit*2] = c;
}

static char tohexchar(int x) {
	if(x < 0xA) {
		return x + '0';
	}
	else {
		return x + 'A';
	}
}

static void lcdDisplayNumber(long number) {
	for(int i = 0; i < 8; i++) {
		int d = (number >> (i * 4)) & 0xF;
		lcdDisplayCharacter(8-i, tohexchar(d));
	}
}

