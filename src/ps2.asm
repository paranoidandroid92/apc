[BITS 16]
global initialize_ps2


section .text

;disable ports and interrupts
initialize_ps2:
	cli
	pusha
	push es

	mov al,0xAD ;disable first ps2 port
	out 0x64,al	

	mov al,0xA7	;disable second ps2 port
	out 0x64,al

	in al,0x60	;flush output buffer

	mov al,0x20	;read configuration byte
	out 0x64,al	
	in al,0x60	
	mov bl,al
	and bl,0xFC	;disable interrupts and keyboard translation
	mov al,0x60
	out 0x64,al	;write configuration byte
	mov al,bl
	out 0x60,al
	
	pop es
	popa
	sti
	ret