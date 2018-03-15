[BITS 16]
global initialize_keyboard
extern keyboard_interrupt_service

;############
section .text

initialize_keyboard:
	cli
	pusha
	push es

	mov ax,0
	mov es,ax
	mov di,[kb_irq_offset] ; set handler in IVT, vector offset 0x21
	mov ax,kb_irq_handler
	mov [es:di],ax
	inc di
	inc di
	mov ax,0
	mov [es:di],ax

	mov al,0xAE	;Enable keyboard port
	out 0x64,al
	
	mov al,0x20	;read configuration byte
	out 0x64,al	
	in al,0x60	
	mov bl,al
	or bl,0x01	;enable keyboard interrupt
	mov al,0x60
	out 0x64,al	;write configuration byte
	mov al,bl
	out 0x60,al
chk_buff:
	in al,0x64
	and al,0x01
	cmp al,0x01
	je read_buff
	jmp read_end
read_buff:
	in al,0x60
	jmp chk_buff
read_end:
	pop es
	popa
	sti
	ret


kb_irq_handler:
	call 0x0000:keyboard_interrupt_service
	iret

;############
section .data

kb_irq_offset dw 0x0084