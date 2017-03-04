int main() {

	return 0;
}


void lcdDisplayNumber(long number) {
	for(int i = 0; i < 8; i++) {
		int d = (number >> (i * 4)) & 0xF;
		lcdDisplayCharacter(8-i, tohexchar(d));
	}
}

void lcdDisplayCharacter(int digit, char c) {
}

char tohexchar(int x) {
	if(x < 0xA) {
		return x + '0';
	}
	else {
		return x + 'A';
	}
}

