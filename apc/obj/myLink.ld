ENTRY(_start)

SECTIONS
     {
	.text  0x7c00: { *(.text)}
	.data  0x0000: { *(.data) *(.rodata) *(.bss)}
	.eh_frame_hdr 0x3000 : { *(.eh_frame_hdr)}

	 /DISCARD/ : {
		*(.eh_frame);
		*(.comment);
		*(.note.gnu.build-id);
	    }
     }
