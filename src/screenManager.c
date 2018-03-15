#include "string.h"
#include "screenManager.h"

static byte TERMINAL_COLOR = 0;
static byte CURRENT_BACKGROUND_COLOR = 0;
static byte CURRENT_FOREGROUND_COLOR = 0;

const byte VGA_COLOR_BLACK = 0x00;
const byte VGA_COLOR_BLUE = 0x01;
const byte VGA_COLOR_GREEN = 0x02;
const byte VGA_COLOR_CYAN = 0x03;
const byte VGA_COLOR_RED = 0x04;
const byte VGA_COLOR_MAGENTA = 0x05;
const byte VGA_COLOR_BROWN = 0x06;
const byte VGA_COLOR_GRAY = 0x07;
const byte VGA_COLOR_DARK_GRAY = 0x08;
const byte VGA_COLOR_BRIGHT_BLUE = 0x09;
const byte VGA_COLOR_BRIGHT_GREEN = 0x0A;
const byte VGA_COLOR_BRIGHT_CYAN = 0x0B;
const byte VGA_COLOR_BRIGHT_RED = 0x0C;
const byte VGA_COLOR_BRIGHT_MAGENTA = 0x0D;
const byte VGA_COLOR_YELLOW = 0x0E;
const byte VGA_COLOR_WHITE = 0x0F;

const short SCREEN_ROW_LIMIT = 80;
const short SCREEN_COLUMN_LIMIT = 25;

static short CURRENT_BUFFER_INDEX = 0;


void screenManagerInit() {
	CURRENT_BACKGROUND_COLOR = VGA_COLOR_WHITE;
	CURRENT_FOREGROUND_COLOR = VGA_COLOR_BLUE;
	TERMINAL_COLOR = (CURRENT_BACKGROUND_COLOR << 4) | CURRENT_FOREGROUND_COLOR;

}

void print(char* message) {
	int str_size = strlength(message);
	short character = 0x0000;
	character = ((character | TERMINAL_COLOR) << 8);
	for (int i = 0; i < str_size; i++) {
		character = character & 0xFF00;
		character = character | message[i];
		__asm__ volatile ("pusha\n\t"
		                  "push %%es\n\t"
		                  "mov $0xb800,%%cx\n\t"
		                  "mov %%cx, %%es\n\t"
		                  "mov %0, %%di\n\t"
		                  "mov %1, %%es:(%%di)\n\t"
		                  "pop %%es\n\t"
		                  "popa\n\t"
		                  :
		                  : "r" (CURRENT_BUFFER_INDEX), "r" (character));
		CURRENT_BUFFER_INDEX += 2;
	}

}

void printAt(char* message, int x, int y) {
	short index = (x * SCREEN_ROW_LIMIT * 2) + (y * 2);
	int str_size = strlength(message);
	short character = 0x0000;
	character = ((character | TERMINAL_COLOR) << 8);
	for (int i = 0; i < str_size; i++) {
		character = character & 0xFF00;
		character = character | message[i];
		__asm__ volatile ("pusha\n\t"
		                  "push %%es\n\t"
		                  "mov $0xb800,%%cx\n\t"
		                  "mov %%cx, %%es\n\t"
		                  "mov %0, %%di\n\t"
		                  "mov %1, %%es:(%%di)\n\t"
		                  "pop %%es\n\t"
		                  "popa\n\t"
		                  :
		                  : "r" (index), "r" (character));
		index += 2;
	}

}

void setBackgroundColor(byte backgroundColor) {
	setTerminalColor(backgroundColor, CURRENT_FOREGROUND_COLOR);
}

void setForegroundColor(byte foregroundColor) {
	setTerminalColor(CURRENT_BACKGROUND_COLOR, foregroundColor);
}

void setTerminalColor(byte backgroundColor, byte foregroundColor) {
	short character_count = (SCREEN_ROW_LIMIT * SCREEN_COLUMN_LIMIT * 2);
	TERMINAL_COLOR = (backgroundColor << 4) | foregroundColor;
	__asm__ volatile("pusha\n\t"
	                 "push %%es\n\t"
	                 "push %%ax\n\t"
	                 "movw $0xb800,%%ax\n\t"
	                 "movw %%ax,%%es\n\t"
	                 "movw $0,%%di\n\t"
	                 "pop %%ax\n\t"
	                 "set_color:\n\t"
	                 "movw %%es:(%%di),%%bx\n\t"
	                 "movb %0,%%bh\n\t"
	                 "movw %%bx,%%es:(%%di)\n\t"
	                 "incw %%di\n\t"
	                 "incw %%di\n\t"
	                 "cmpw %1,%%di\n\t"
	                 "jne set_color\n\t"
	                 "pop %%es\n\t"
	                 "popa\n\t"
	                 :
	                 : "r" (TERMINAL_COLOR), "r" (character_count));
	return;
}

void clearScreen() {
	short clear_char = (0x0000 | TERMINAL_COLOR) << 8;
	for (short i = 0; i < (SCREEN_ROW_LIMIT * SCREEN_COLUMN_LIMIT * 2 - 1); i += 2) {
		__asm__ volatile ("pusha\n\t"
		                  "push %%es\n\t"
		                  "mov $0xb800,%%cx\n\t"
		                  "mov %%cx, %%es\n\t"
		                  "mov %0, %%di\n\t"
		                  "mov %1, %%es:(%%di)\n\t"
		                  "pop %%es\n\t"
		                  "popa\n\t"
		                  :
		                  : "r" (i), "r" (clear_char));
	}
}

void blink(byte x, byte y) {
	short index = (x * SCREEN_ROW_LIMIT * 2) + (y * 2);
	__asm__ volatile("pusha\n\t"
					 "push %%es\n\t"
					 "mov $0xb800,%%ax\n\t"
					 "mov %%ax,%%es\n\t"
					 "mov %0, %%di\n\t"
					 "mov %%es:(%%di), %%bx\n\t"
					 "or $0x80,%%bh\n\t"
					 "mov %%bx,%%es:(%%di)\n\t"
					 "pop %%es\n\t"
					 "popa\n\t"
					 :
					 : "m" (index));
}

void unblink(byte x, byte y) {
	short index = (x * SCREEN_ROW_LIMIT * 2) + (y * 2);
	__asm__ volatile("pusha\n\t"
					 "push %%es\n\t"
					 "mov $0xb800,%%ax\n\t"
					 "mov %%ax,%%es\n\t"
					 "mov %0, %%di\n\t"
					 "mov %%es:(%%di), %%bx\n\t"
					 "and $0x7F,%%bh\n\t"
					 "mov %%bx,%%es:(%%di)\n\t"
					 "pop %%es\n\t"
					 "popa\n\t"
					 :
					 : "m" (index));
}
