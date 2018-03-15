[BITS 16]
global initialize_mouse
extern mouse_interrupt_service
;############
section .text

initialize_mouse:
	cli
	pusha
	push es

	mov ax,0
	mov es,ax
	mov di,[mouse_irq_offset] ; set handler in IVT, vector offset 0x2C
	mov ax,mouse_irq_handler
	mov [es:di],ax
	inc di
	inc di
	mov ax,0
	mov [es:di],ax


	mov al,0xA8	; Enable mouse port
	out 0x64,al

	mov al,0xD4 ; reset mouse
	out 0x64,al
	in al,0x64
	mov al,0xFF
	out 0x60,al
	in al,0x60
	in al,0x60
	in al,0x60

	mov al,0xD4 ; set to default
	out 0x64,al
	mov al,0xF6
	out 0x60,al
	in al,0x60
	in al,0x60
	in al,0x60

	mov al,0xD4 ; enable scanning 
	out 0x64,al
	mov al,0xF4
	out 0x60,al
	in al,0x60

	mov al,0x20	;read configuration byte
	out 0x64,al	
	in al,0x60	
	mov bl,al
	or bl,0x02	;enable mouse interrupt
	mov al,0x60
	out 0x64,al	;write configuration byte
	mov al,bl
	out 0x60,al

	in al,0x64

	pop es
	popa
	sti
	ret


mouse_irq_handler:
	call 0x0000:mouse_interrupt_service
	iret

;############
section .data

mouse_irq_offset dw 0x00B0
screen_kb dw 0