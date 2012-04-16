; ----------------------------------------------------------------------------
; factorial_deop_1.asm
; ----------------------------------------------------------------------------

	global _factorial
               
        section .text
_factorial:
	nop				; This is here for alignment purposes
	mov     eax, [esp+4]            ; Get the integer whose factorial is
					; being calculated
	cmp     eax, 1                  ; Have we hit one yet?
	jne    	calculate               ; If we haven't then do another call
	ret				; return with a 1
	
calculate:
	dec     eax                     ; Decrement the integer to get ready
					; for the recursive call
	push    eax                     ; Push the integer minus one
	call    _factorial              ; Make the recursive call
	add     esp, 4                  ; Dump the argument
	imul    eax, [esp+4]            ; Do the multiplication
	ret
