#include "io.h"
#include "screenManager.h"

#define DATA_PORT 0x60
#define PIC1_PORT 0x20
#define PIC2_PORT 0xA0
#define EOI_COMMAND 0x20

static int MOUSE_X = 0;
static int MOUSE_Y = 0;

static uint8_t packet_size = 3;
static uint8_t packet_level = 0;
static uint8_t packet[3];

static char mouse_str[6] = {"Mouse"};

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
	printAt(mouse_str,0,75);
	__asm__ volatile("pusha\n\t"
	                 "push  %es\n\t"
	                 "mov $0xb800, %ax\n\t"
	                 "mov %ax, %es\n\t"
	                 "mov $0, %di\n\t"
	                 "movw $0x4e47,%es:(%di)\n\t"
	                 "pop %es\n\t"
	                 "popa\n\t");
}

void print_position() {

}