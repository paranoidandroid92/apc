[BITS 16]
global initialize_mouse

;############
section .text

initialize_mouse:
	cli

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
	or bl,0x03	;enable mouse interrupt
	and bl,0xCF ;enable mouse clock
	mov al,0x60
	out 0x64,al	;write configuration byte
	mov al,bl
	out 0x60,al

	sti
	ret


mouse_irq_handler:
	cli
	pusha
	push es
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
	mov ax,0xb800
	mov es,ax
	mov di,[screen_kb]
	mov ax, 0x4e45
	mov [es:di],ax
	add word [screen_kb],2
	mov al,0x20
	out 0x20,al
	pop es
	popa
	sti
	iret

;############
section .data

mouse_irq_offset dw 0x00B0