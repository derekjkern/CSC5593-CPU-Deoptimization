; ----------------------------------------------------------------------------
; insertion_sort.asm
; ----------------------------------------------------------------------------

        global  _insertion_sort		; Declare the name of this function

        section .text
_insertion_sort:
        push    ebx                     ; Preserve ebx
        
        mov	esi, dword [esp+8] 	; Get the pointer to the array of numbers
        				; This array will be sorted
	mov     eax, [esp+12]           ; Get the integer that tells us how many numbers
        				; are in the array        				

        mov	edi, esi		; edi will point to the next element being sorted
        
do_sort_outer:
	dec	eax			; Decrement the array counter
	je	return			; If the counter reaches zero, then we are done.

	mov	ebx, edi		; Keep a handle on the previous element
	add	edi, 4			; Get a handle on the element being sorted/inserted
	mov	ecx, [edi]		; Get the value of the  element being sorted/inserted
	
do_sort_inner:
	mov	edx, [ebx]		; Get the value pointed to by ebx

	cmp	edx, ecx		; Compare the two values
	jl	do_insertion		; If it is supposed to appear before, then do the insert

	mov	dword [ebx+4], edx	; Store the ith element into i + 1
	sub	ebx, 4			; Go to another previous element        
        cmp	ebx, esi		; Compare the addresses to see if we've hit the array start
        jl     	do_insertion		; Do an insertion if we have hit the start

	jmp	do_sort_inner		; Move on to the next (previos) element

do_insertion:
	mov	dword [ebx+4], ecx	; Store the search value into i + 1
	jmp	do_sort_outer		; Sort the next element of the array
	
return:
	pop     ebx                     ; Restore ebx before returning

	ret				; Return