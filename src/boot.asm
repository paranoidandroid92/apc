[BITS 16]
extern c_code_entry
GLOBAL _start

section .text
_start:
	mov [disk_drive_number], dl 	; get disk drive number asap
	
	mov ax,0x0000			;initialize segment registers and stack pointer
	mov ds,ax
	mov sp,ax
	mov ax,0x5000
	mov ss,ax

	mov ax, [code_load_addr] 		;read code segment from image to ram
	mov es, ax				;es:bx buffer address pointer	
	xor bx, bx
	mov dh, 0x00				; dh=head
	mov ch, 0x00				; ch=cylinder
	mov cl, [code_sector_position]		; cl=sector position on image, chs first sector number is 1
	mov al, [code_sector_size]		; al=sectors to read count
	mov ah, 0x02				; ah=Read Sectors function number
	int 0x13

	mov ax, [data_load_addr] 		;read data segment from image to ram
	mov es, ax				;es:bx buffer address pointer	
	xor bx, bx
	mov dh, 0x00				; dh=head
	mov ch, 0x00				; ch=cylinder
	mov cl, [data_sector_position]		; cl=sector position on image, chs first sector number is 1
	mov al, [data_sector_size]		; al=sectors to read count
	mov ah, 0x02				; ah=Read Sectors function number
	int 0x13

	mov ax,0x2000
	mov ds,ax
	cli
	jmp code_segment_start
	


code_load_addr dw 0x07e0
code_sector_size db 0x06
code_sector_position db 0x02
data_load_addr dw 0x2000
data_sector_size db 0x01
data_sector_position db 0x08
disk_drive_number db 0x00

times 510-($-$$) db 0
db 0x55
db 0xAA

code_segment_start:
	
