
;
; loads N sectors from disk (dh) starting from sector after bootsector
;
load_from_disk:
    pusha

    push dx
    
    mov ah, 0x02 ; read when int 0x13 is called
    mov al, dh   ; N sectors to read

    mov cl, 0x02 ; read starting from sector 2
    mov ch, 0x00 ; read from cylinder 0
    mov dh, 0x00 ; read from head 0


    int 0x13
    jc disk_error; if carry is 1, error has occured

    pop dx
    cmp al, dh   ; compares number of sectors read and "number of sectors to read"
    jne sectors_error

    popa
    ret


disk_error:
    ; prints error message
    mov bx, DISK_ERR_MSG
    call print_str
    call print_endl

    ; prints error code
    mov dh, ah   ; ah stores error code
    call print_hex
    jmp disk_error_loop


sectors_error:
    ; prints sector error message
    mov bx, SECTOR_ERR_MSG
    call print_str
    jmp disk_error_loop


disk_error_loop:
    jmp $


DISK_ERR_MSG: db "Disk read error", 0
SECTOR_ERR_MSG: db "Incorrect number of sectors read", 0

