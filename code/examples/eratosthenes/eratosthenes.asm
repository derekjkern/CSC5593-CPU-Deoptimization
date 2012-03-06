; ----------------------------------------------------------------------------
; eratosthenes.asm
; ----------------------------------------------------------------------------

        global  _eratosthenes		; Declare the name of this function

        section .text
_eratosthenes:
        push    ebx                     ; Preserve ebx
        
        mov	edi, dword [esp+8] 	; Get the pointer to the array of numbers
        				; This array will be the primes
	mov     eax, [esp+12]           ; Get the integer that tells us how many numbers
        				; are in the array        				
        mov	edx, eax
        
do_sieve:
	dec	eax			; Decrement the array counter
	jz	return			; If the counter reaches zero, then we are done.

	mov	ecx, [edi]		; Get the value being pointed to
	test	ecx, ecx		; Check to see whether the value is zero
	jz 	do_next			; Go on to the next value to mark

	mov	ebx, eax		; Move the array size into ebx
	imul	ebx, 4			; Multiply the array size by the number of bytes (stride)
	add	ebx, edi		; Add the array size in bytes to the address of the 
					; of the beginning of the array.  We will use this to
					; know that we've reached the end of the array
	mov	esi, edi		; Initially, set esi to be the beginning of the array
	imul	ecx, 4			; Multiply the value in ecx by the number of bytes (stride)
					; we will use this to advance esi to the next element
					; being marked
	
do_marking:
	add	esi, ecx		; Stride to the next entry being marked
	cmp	ebx, esi		; Make sure that we haven't gone beyond the end of
					; the array
	jl	do_next			; If we have then go onto the next multiple
	
	mov	dword [esi], 0		; If we haven't, then eliminite this entry from
					; consideration by marking it
	
	jmp	do_marking		; Continue marking
	
do_next:
	add	edi, 4			; Go to the next element
	jmp	do_sieve		; Go to the front of the sieve
	
return:
	pop     ebx                     ; Restore ebx before returning

	ret				; Return