#include "stdlib.h"
#include "screenManager.h"
#include "pic.h"
#include "pit.h"
#include "ps2.h"

char greeting[6] = {"He le"};
char greetings[6] = {"Helle"};
char test[11];

int c_code_entry() {
	screenManagerInit();
	clearScreen();
	print(greeting);
	setTerminalColor(VGA_COLOR_BLUE, VGA_COLOR_WHITE);
	printAt(greetings,1,0);
	initialize_pic();
	initialize_pit();
	initialize_ps2();
	initialize_keyboard();
	initialize_mouse();
	itoa(-10, test, 10);
	printAt(test,5,0);
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
	    "in $0x64,%al\n\t"
	    "jmp end\n\t");
	return 0;
}






