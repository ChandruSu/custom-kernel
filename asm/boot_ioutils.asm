
;
; prints all characters in string (bx) to output.
;
print_str:
    pusha ; stores all registers

print_str_loop:
    mov al, [bx] ; bx is pointer to string
    cmp al, 0
    je print_str_end

    ; uses BIOS interrupt to print char
    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp print_str_loop

print_str_end:
    popa ; restores registers
    ret


;
; prints line-break character to output.
;
print_endl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; \n character
    int 0x10
    mov al, 0x0d ; \r character
    int 0x10

    popa
    ret


;
; prints number in dx as hexadecimal string.
;
print_hex:
    pusha
    mov cx, 0 ; index counter

print_hex_loop:
    cmp cx, 4
    je print_hex_end

    mov ax, dx
    and ax, 0x000f ; mask digit
    add al, 0x30   ; converts digit to ASCII
    cmp al, 0x39
    jle print_hex_store_char
    add al, 0x7    ; A-F representations

print_hex_store_char:
    ; char destination: bx = string + len('0x000') - cx 
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov [bx], al   ; copies char to destination
    ror dx, 0x4    ; rotates number 0x1234 -> 0x4123     

    ; increment and loop
    add cx, 1
    jmp print_hex_loop

print_hex_end:
    ; prints string
    mov bx, HEX_OUT
    call print_str

    popa
    ret


HEX_OUT:
    db "0x0000", 0 ; space reserved to store output string

