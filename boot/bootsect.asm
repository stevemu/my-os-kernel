[org 0x7c00]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE
call print

call load_kernel

call switch_to_pm

jmp $

%include "boot/print.asm"
%include "boot/print_hex.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/32bit_print.asm"
%include "boot/switch_pm.asm"

[bits 16]

load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print

	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call disk_load

	ret

[bits 32]

BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	call KERNEL_OFFSET

	jmp $

BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode. ", 0
MSG_PROT_MODE db "32-bit mode is on.  ", 0
MSG_LOAD_KERNEL db "Loading kernel into memory. ", 0

times 510-($-$$) db 0
dw 0xaa55