#include "string.h"
#define MAX_CHAR 11

char numbers[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void itoa(int number, char* str, int base) {
	int i = 0, sign;

	if ((sign = number) < 0) {
		number = -number; // make number positive
	}

	do {
		str[i++] = numbers[number % base];
	} while ((number /= base) > 0);

	if (sign < 0) {
		str[i++] = '-';
	}

	str[i] = '\0';

	reverse(str);
}
