typedef long long uint32_t;

static void lcdDisplayNumber(long number);
static uint32_t i;

int main() {
	while(++i) {
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
		return x - 10 + 'A';
	}
}

static void lcdDisplayNumber(long number) {
	for(int i = 0; i < 8; i++) {
		int d = (number >> (i * 4)) & 0xF;
		lcdDisplayCharacter(7-i, tohexchar(d));
	}
}

