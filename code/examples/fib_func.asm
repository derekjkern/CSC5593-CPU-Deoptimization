; ----------------------------------------------------------------------------
; fib_func.asm
; ----------------------------------------------------------------------------

        global  _fib
        extern  _printf

        section .text
_fib:
        push    ebx                     ; we have to save this since we use it

        mov     ecx, [esp+8]            ; ecx will countdown from the arg to 0
        xor     eax, eax                ; eax will hold the current number
        xor     ebx, ebx                ; ebx will hold the next number
        inc     ebx                     ; ebx is originally 1
print:
        ; We need to call printf, but we are using eax, ebx, and ecx.  printf
        ; may destroy eax and ecx so we will save these before the call and
        ; restore them afterwards.

        push    eax
        push    ecx

        push    eax
        push    format
        call    _printf
        add     esp, 8

        pop     ecx
        pop     eax

        mov     edx, eax                ; save the current number
        mov     eax, ebx                ; next number is now current
        add     ebx, edx                ; get the new next number
        dec     ecx                     ; count down
        jnz     print                   ; if not done counting, do some more

        pop     ebx                     ; restore ebx before returning
        ret
format:
        db      '%10d', 0