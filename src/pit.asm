[BITS 16]
global pit_irq_handler
global initialize_pit

;############
section .text
initialize_pit:
	cli
	push ax
	push di
	push es
	mov ax,0
	mov es,ax
	mov di,[pit_irq_offset]
	mov ax,pit_irq_handler
	mov [es:di],ax
	inc di
	inc di
	mov ax,0
	mov [es:di],ax
	mov al,0x30
	out 0x43,al
	mov al,0xFF
	out 0x40,al
	out 0x40,al
	pop es
	pop di
	pop ax
	sti
	ret

pit_irq_handler:
	pusha
	push es
	mov bl,[counter]
	inc bl
	mov [counter],bl
	cmp bl,0xFF
	jne .pit_irq_ret
	mov ax,0xb800
	mov es,ax
	mov di,[screen_pos]
	mov ax, 0x4e45
	mov [es:di],ax
	add word [screen_pos],2
.pit_irq_ret:	
	mov al,0x20
	out 0x20,al
	mov al,0x7F
	out 0x40,al
	out 0x40,al
	pop es
	popa
	iret

;############
section .data
counter db 0x00
screen_pos dw 0x0000
pit_irq_offset dw 0x0080
