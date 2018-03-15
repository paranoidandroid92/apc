unsigned char getKeyCode(unsigned char scanCode);

int sc_pos = 0;
int caps_on =0;
unsigned char keyCode[128] =
{
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8',  //10
	'9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', //20
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0, 'a', //30
	's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 0, //40
	0, 0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', //50
	0, 0, 0, 0, '*', 0, ' ', 0, 0, 0, //60
	0, 0, 0, 0, 0, 0, 0, '-', 0, 0, //70
	0, '+',
};
void keyboard_interrupt_service(){
	unsigned char character = 0x00;
	short charim = 0x4e00;
	__asm__ volatile("cli\n\t"
			 "push %ax\n\t"
			 "push %di\n\t"
			 "push %es\n\t"
			 "chk_buff:\n\t"
			 "in $0x64,%al\n\t"
			 "and $0x01,%al\n\t"
			 "cmp $0x01,%al\n\t"
			 "je read_buff\n\t"
			 "jmp read_end\n\t"
			 "read_buff:\n\t"
			 "in $0x60,%al\n\t");
	__asm__ volatile("movb %%al,%0\n\t": : "m" (character));
	if(character <=128){
	character = keyCode[character];
	}
	else{
	character = 0;
	}
	charim = charim | character;
	if((character <= 'Z' && character >= 'A') || (character <= 'z' && character >= 'a')){
	__asm__ volatile("jmp chk_buff\n\t"
			 "read_end:\n\t"
			 "mov $0xb800,%ax\n\t"
			 "mov %ax,%es\n\t");
	__asm__ volatile("movw %0,%%di\n\t": : "m" (sc_pos));
	__asm__ volatile("mov %0,%%ax\n\t": : "m" (charim));
	__asm__ volatile("mov %ax,%es:(%di)\n\t");
			 sc_pos = sc_pos +2;
	}
	__asm__ volatile("mov $0x20,%al\n\t"
			 "out %al,$0x20\n\t"
			 "pop %es\n\t"
			 "pop %di\n\t"
			 "pop %ax\n\t"
			 "sti\n\t");
}
 
unsigned char getKeyCode(unsigned char scanCode){
	switch(scanCode){
    case 0x02: //1
        return '1';
    case 0x03: //2
        return '2';
    case 0x04: //3
        return '3';
    case 0x05: //4
        return '4';
    case 0x06: //5
        return '5';
    case 0x07: //6
        return '6';
    case 0x08: //7
        return '7';
    case 0x09: //8
        return '8';
    case 0x8A: //9
        return '9';
    case 0x8B: //0
        return '0';
    case 0x8C: //-
        return '-';
    case 0x8D: //=
        return '=';
    case 0x8E: //backspace
        return '%';
    case 0x8F: //tab
        return '%';
    case 0x90: //Q
	if(caps_on%2 == 0) return 'q';
        return 'Q';
    case 0x91: //W
	if(caps_on%2 == 0) return 'w';
        return 'W';
    case 0x92: //E
	if(caps_on%2 == 0) return 'e';
        return 'E';
    case 0x93: //R
	if(caps_on%2 == 0) return 'r';
        return 'R';
    case 0x94: //T
	if(caps_on%2 == 0) return 't';
        return 'T';
    case 0x95: //Y
	if(caps_on%2 == 0) return 'y';
        return 'Y';
    case 0x96: //U
	if(caps_on%2 == 0) return 'u';
        return 'U';
    case 0x97: //I
	if(caps_on%2 == 0) return 'i';
        return 'I';
    case 0x98: //O
	if(caps_on%2 == 0) return 'o';
        return 'O';
    case 0x99: //P
	if(caps_on%2 == 0) return 'p';
        return 'P';
    case 0x9A: //[
        return '[';
    case 0x9B: //]
        return ']';
    case 0x9C: //enter
        return '%';
    case 0x9D: //left ctrl
        return '%';
    case 0x9E: //A
	if(caps_on%2 == 0) return 'a';
        return 'A';
    case 0x9F: //S
	if(caps_on%2 == 0) return 's';
        return 'S';
    case 0xA0: //D
	if(caps_on%2 == 0) return 'd';
        return 'D';
    case 0xA1: //F
	if(caps_on%2 == 0) return 'f';
        return 'F';
    case 0xA2: //G
	if(caps_on%2 == 0) return 'g';
        return 'G';
    case 0xA3: //H
	if(caps_on%2 == 0) return 'h';
        return 'H';
    case 0xA4: //J
	if(caps_on%2 == 0) return 'j';
        return 'J';
    case 0xA5: //K
	if(caps_on%2 == 0) return 'k';
        return 'K';
    case 0xA6: //L
	if(caps_on%2 == 0) return 'l';
        return 'L';
    case 0xA7: //;
        return '%';
    case 0xA8: //'
        return '%';
    case 0xA9: //back tick
        return '%';
    case 0xAA: //left shift
        return '%';
    case 0xAB: //backslash
        return '%';
    case 0xAC: //Z
	if(caps_on%2 == 0) return 'z';
        return 'Z';
    case 0xAD: //X
	if(caps_on%2 == 0) return 'x';
        return 'X';
    case 0xAE: //C
	if(caps_on%2 == 0) return 'c';
        return 'C';
    case 0xAF: //V
	if(caps_on%2 == 0) return 'v';
        return 'V';
    case 0xB0: //B
	if(caps_on%2 == 0) return 'b';
        return 'B';
    case 0xB1: //N
	if(caps_on%2 == 0) return 'n';
        return 'N';
    case 0xB2: //M
	if(caps_on%2 == 0) return 'm';
        return 'M';
    case 0xB3: //,
        return '%';
    case 0xB4: //.
        return '%';
    case 0xB5: //slash
        return '%';
    case 0xB6: //right shift
        return '%';
    case 0xB7: //*
        return '*';
    case 0xB8: //left alt
        return '%';
    case 0xB9: //space
        return ' ';
    case 0xBA: //caps loc 
	//if(isCapsOn == 0){ isCapsOn=1;}
	//else if(isCapsOn == 1) isCapsOn=0;
	caps_on++;
	if(caps_on%2 == 0) return 'M';
        return 'F';
    case 0xBB: //F1
        return '%';
    case 0xBC: //F2
        return '%';
    case 0xBD: //F3
        return '%';
    case 0xBE: //F4
        return '%';
    case 0xBF: //F5
        return '%';
    case 0xC0: //F6
        return '%';
    case 0xC1: //F7
        return '%';
    case 0xC2: //F8
        return '%';
    case 0xC3: //F9
        return '%';
    case 0xC4: //F10
        return '%';
    case 0xC5: //Num lock
        return '%';
    case 0xC6: //scroll lock
        return '%';
    case 0xC7: //keypad 7
        return '7';
    case 0xC8: //keypad 8
        return '8';
    case 0xC9: //keypad 9
        return '9';
    case 0xCA: //keypad -
        return '-';
    case 0xCB: //keypad 4
        return '4';
    case 0xCC: //keypad 5
        return '5';
    case 0xCD: //keypad 6
        return '6';
    case 0xCE: //keypad +
        return '+';
    case 0xCF: //keypad 1
        return '1';
    case 0xD0: //keypad 2
        return '2';
    case 0xD1: //keypad 3
        return '3';
    case 0xD2: //keypad 0
        return '0';
    case 0xD3: //keypad .
        return '.';
    case 0xD7: //F11
        return '%';
    default:
        return '%';
	}
}
