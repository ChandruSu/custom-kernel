;
; --- BOOT SECTOR ---
;
[org 0x7c00]
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG
    call print_str
    call print_endl

    call load_kernel
    call switch_to_protected_mode

    jmp $ ; never reached

;
; --- BOOT IMPORTS ---
;
%include "asm/boot_ioutils.asm"
%include "asm/boot_disk.asm"
%include "asm/gdt.asm"
%include "asm/vga_print.asm"

[bits 16]
load_kernel:
    mov bx, MSG3
    call print_str
    call print_endl

    mov bx, KERNEL_OFFSET
    mov dh, 16 ; size of kernel
    mov dl, [BOOT_DRIVE]
    call load_from_disk
    ret

[bits 32]

; destination after 32-bit mode begins
BEGIN_PM:
    mov ebx, MSG2
    call print_string_pm
    call KERNEL_OFFSET
    jmp $

KERNEL_OFFSET equ 0x1000
BOOT_DRIVE db 0
MSG db "Printed in 16-bit read mode", 0
MSG2 db "Printed in 32-bit protected mode", 0
MSG3 db "Loading kernel into memory", 0

; padds program with 0x0000 ... 0x0000 0xaa55 (magic number)
times 510 - ($-$$) db 0
dw 0xaa55
