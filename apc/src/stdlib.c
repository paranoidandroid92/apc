#define MAX_CHAR 11
char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int number[MAX_CHAR];
int* itoa(int num) {
	int count = 0, remainder, quotinent, i, temp;

	do {
		quotinent = num / 10;
		remainder = num % 10;
		number[count] = remainder;
		num = quotinent;
		count++;
	} while (quotinent != 0);
	number[count] = '\0';

	return number;
}