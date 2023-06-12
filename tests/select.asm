BITS 32
    org 0x7c00
start:
    mov edx, 0x03f8
mainloop:
    mov al, '>'    ; display prompt
    out dx, al
input:
    in al, dx       ; imput a character
    cmp al, 'h'
    je puthello     ; display "hello" if the input character is 'h'
    cmp al, 'w'
    je putworld     ; display "world" if the input character is 'w'
    cmp al, 'q'
    je fin          ; quit if 'q'
    jmp input       ; loop otherwise
puthello:
    mov esi, msghello
    call puts
    jmp mainloop
putworld:
    mov esi, msgworld
    call puts
    jmp mainloop
fin:
    jmp 0

puts:
    mov al, [esi]
    inc esi
    cmp al, 0
    je putsend
    out dx, al
    jmp puts
putsend:
    ret

msghello:
    db "hello", 0x0d, 0x0a, 0
msgworld:
    db "world", 0x0d, 0x0a, 0
