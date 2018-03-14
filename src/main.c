
#include "screenManager.h"
#include "pic.h"
#include "pit.h"
#include "ps2.h"
#define MAX_CHAR 11

char greeting[6] = {"Helle"};
char greetings[6] = {"Helle"};
char numbers[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
char test[11];

void itoa(int, char*, int);
int c_code_entry() {
	screenManagerInit();
	clearScreen();
	print(greeting);
	setTerminalColor(VGA_COLOR_BLUE, VGA_COLOR_WHITE);
	print(greetings);
	initialize_pic();
	initialize_pit();
	initialize_ps2();
	initialize_keyboard();
	itoa(2147483648, test, 10);
	print(test);
	__asm__ volatile(/*"mov $0x13,%al\n\t"
	                 "mov $0x00,%ah\n\t"
	                 "int $0x10\n\t"
	                 "mov $1,%al\n\t"
	                 "mov $0x05,%ah\n\t"
	                 "int $0x10\n\t"
	                 "mov $0x0E,%al\n\t"
	                 "mov $0x01,%bh\n\t"
	                 "mov $100,%cx\n\t"
	                 "mov $100,%dx\n\t"
	                 "mov $0x0C,%ah\n\t"
	                 "int $0x10\n\t"
	                 "mov $102,%cx\n\t"
	                 "int $0x10\n\t"
	                 "mov $0,%cx\n\t"
	                 "mov $0,%dx\n\t"
	                 "int $0x10\n\t"
	                 "mov $319,%cx\n\t"
	                 "mov $199,%dx\n\t"
	                 "int $0x10\n\t"
	                 "mov $0xA000,%ax\n\t"
	                 "mov %ax,%es\n\t"
	                 "mov $0,%di\n\t"
	                 "movb $0x80,%es:(%di)\n\t"
	                 "inc %di\n\t"
	                 "movb $0xAA,%es:(%di)\n\t"
	                 "mov $198,%di\n\t"
	                 "movb $0xAA,%es:(%di)\n\t"*/
	    "end: \n\t"
	    "jmp end\n\t");
	return 0;
}

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




