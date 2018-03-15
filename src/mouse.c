#include "io.h"
#include "screenManager.h"
#include "stdlib.h"

#define DATA_PORT 0x60
#define PIC1_PORT 0x20
#define PIC2_PORT 0xA0
#define EOI_COMMAND 0x20

static int MOUSE_X = 0;
static int MOUSE_Y = 0;
byte count_x = 0;
byte count_y = 0;

static uint8_t packet_size = 3;
static uint8_t packet_level = 0;
static uint8_t packet[3];

static char mouse_str[6] = {"Mouse"};
static char x_str[3] = {"X:"};
static char y_str[3] = {"Y:"};
char clear[4] = {"   "};
void process_mouse_packet();

void mouse_interrupt_service() {
	uint8_t data = inb(DATA_PORT);

	packet[packet_level++] = data;

	if (packet_size && packet_level == packet_size) {
		process_mouse_packet();
		packet_level = 0;
	}
	outb(PIC1_PORT, EOI_COMMAND);
	outb(PIC2_PORT, EOI_COMMAND);
}

void process_mouse_packet() {
	MOUSE_X = packet[1];
	MOUSE_Y = packet[2];
	char position_x[5];
	char position_y[5];
	itoa(MOUSE_X,position_x,10);
	itoa(MOUSE_Y,position_y,10);
	printAt(mouse_str,0,75);
	printAt(x_str,1,75);
	printAt(y_str,2,75);
	printAt(clear,1,77);
	printAt(clear,2,77);
	printAt(position_x,1,77);
	printAt(position_y,2,77);
	count_y++;
	count_x += count_y / 160;
	count_y = count_y % 80;
	blink(count_x,count_y);
}

void print_position() {

}