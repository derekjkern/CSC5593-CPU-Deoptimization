; ----------------------------------------------------------------------------
; fib_func.asm
; ----------------------------------------------------------------------------

        global  _asm_fib		; Declare the name of this function

        section .text
_asm_fib:
        push    ebx                     ; Preserve ebx
        
        mov	edi, dword [esp+8] 	; Get the pointer to the array of fibonacci numbers
        				; This array will be populated with values
        mov     ecx, [esp+12]           ; Get the integer that tells us how many fibonacci numbers
        				; to generate
        
        mov 	dword [edi], 0		; Manually do the first fibonacci number
        add	edi, 4			; Advance the array pointer
        dec	ecx			; Decrement the fibonacci number counter
        je 	return			; Return if only the first number was requested
        
        mov 	dword [edi], 1		; Manually do the second fibonacci number	
        add	edi, 4			; Advance the array pointer
        dec	ecx			; Decrement the fibonacci number counter
        je 	return			; Return if only the first number was requested

        mov     eax, 0                	; Initialize the fib1 number register
        mov     ebx, 1                	; Initialize the fib2 number register
        
calculate:
        mov     edx, eax                ; Save the current fib1 into edx
        mov     eax, ebx                ; Save the current fib2 into eax
        add     ebx, edx                ; Generate the next fibonacci number into ebx
        
        mov 	dword [edi], ebx	; Move the next fibonacci into the array
        add	edi, 4			; Advance the array pointer
        
        dec     ecx                     ; Decrement the counter of fibonacci numbers
        jnz     calculate               ; If we are not done (i.e. if the previous instruction
        				; didn't result in a zero), then jump back to the 
        				; the beginning of calculate

return:
	pop     ebx                     ; Restore ebx before returning

	ret				; Return