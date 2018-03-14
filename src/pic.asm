[BITS 16]
global  initialize_pic

;############
section .text

initialize_pic: 
	cli
	push ax

	mov al,0x11	;ICW1
	out 0x20,al
	out 0xA0,al
	
	mov al,0x20	;ICW2
	out 0x21,al
	mov al,0x28
	out 0xA1,al
	
	mov al,0x04	;ICW3
	out 0x21,al
	mov al,0x02
	out 0xA1,al
	
	mov al,0x01	;ICW4
	out 0x21,al
	out 0xA1,al
	
	pop ax
	sti
	ret
