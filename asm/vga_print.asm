[bits 32]

VIDEO_MEM_ADDR equ 0xb8000
WHITE_ON_BLACK equ 0x0f

;
; prints character without BIOS interrupt
;
print_string_pm:
    pusha
    mov edx, VIDEO_MEM_ADDR

print_string_pm_loop:
    mov al, [ebx] ; string address
    mov ah, WHITE_ON_BLACK

    cmp al, 0     ; check if string end reached
    je print_string_pm_end

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 0x1  ; next character
    add edx, 0x2  ; next column in vga memory

    jmp print_string_pm_loop

print_string_pm_end:
    popa
    ret