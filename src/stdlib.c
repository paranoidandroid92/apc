#define MAX_CHAR 11

char numbers[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void itoa(int number, char* str, int base) {
	int count = 0, remainder, quotinent, i, temp;

	do {
		quotinent = number / base;
		remainder = number % base;
		str[count] = numbers[remainder];
		number = quotinent;
		count++;
	} while (quotinent != 0);

	str[count] = '\0';

	for (i = 0; i < count / 2; i++) {
		temp = str[i];
		str[i] = str[count - 1 - i];
		str[count - 1 - i] = temp;
	}
}