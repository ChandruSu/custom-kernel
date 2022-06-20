
gdt_start:
    ; GDT starts with 8 null bytes
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0x0      
    db 0x0      
    db 10011010b
    db 11001111b
    db 0x0 

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

[bits 16]
switch_to_protected_mode:
    cli ; disable interrupts
    lgdt [gdt_descriptor]
    
    ; loads and sets 32-bit mode on control register
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_protected_mode

[bits 32]
init_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM
