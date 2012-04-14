; ----------------------------------------------------------------------------
; mod_ten_counter.asm - This is the optimized version
; ----------------------------------------------------------------------------

        global  _mod_ten_counter	; Declare the name of this function

        section .text
_mod_ten_counter:
        push    ebx                     ; Preserve ebx
        
        mov	esi, dword [esp+8] 	; Get the pointer to the array of counts
        mov	edi, dword [esp+12] 	; Get the pointer to the array of numbers
        				; This array will be counted
	mov     eax, [esp+16]           ; Get the integer that tells us how many numbers
        				; are in the array        				

do_count:
	dec	eax			; Decrement the array counter
	je	return			; If the counter reaches zero, then we are done.
	
	mov	ecx, [edi]		; Get the next value to be counted
	
	cmp	ecx, 0
	je	mark_0			; We have a 0
	nop
	dec	ecx			
	je	mark_1			; We have a 1
	nop
	dec	ecx
	je	mark_2			; We have a 2
	nop
	dec	ecx
	je	mark_3			; We have a 3
	nop
	dec	ecx
	je	mark_4			; We have a 4
	nop
	dec	ecx
	je	mark_5			; We have a 5
	nop
	dec	ecx
	je	mark_6			; We have a 6
	nop
	dec	ecx
	je	mark_7			; We have a 7
	nop
	dec	ecx
	je	mark_8			; We have a 8
	nop
	dec	ecx
	je	mark_9			; We have a 9
			
return:
	pop     ebx                     ; Restore ebx before returning

	ret				; Return	
	
mark_0:
	mov     ebx, [esi]
	inc	ebx			; Increment the count of zeros
	mov	[esi], ebx
	jmp	do_next

mark_1:
	mov     ebx, [esi+4]
	inc	ebx			; Increment the count of ones
	mov	[esi+4], ebx
	jmp	do_next

mark_2:
	mov     ebx, [esi+8]
	inc	ebx			; Increment the count of twos
	mov	[esi+8], ebx
	jmp	do_next

mark_3:
	mov     ebx, [esi+12]
	inc	ebx			; Increment the count of threes
	mov	[esi+12], ebx
	jmp	do_next
	
mark_4:
	mov     ebx, [esi+16]
	inc	ebx			; Increment the count of fours
	mov	[esi+16], ebx
	jmp	do_next

mark_5:
	mov     ebx, [esi+20]
	inc	ebx			; Increment the count of fives
	mov	[esi+20], ebx
	jmp	do_next

mark_6:
	mov     ebx, [esi+24]
	inc	ebx			; Increment the count of sixes
	mov	[esi+24], ebx
	jmp	do_next

mark_7:
	mov     ebx, [esi+28]
	inc	ebx			; Increment the count of sevens	
	mov	[esi+28], ebx
	jmp	do_next

mark_8:
	mov     ebx, [esi+32]
	inc	ebx			; Increment the count of eights
	mov	[esi+32], ebx
	jmp	do_next
	
mark_9:
	mov     ebx, [esi+36]
	inc	ebx			; Increment the count of nines
	mov	[esi+36], ebx

do_next:
	add	edi, 4			; Goto the next element to be counted
	jmp	do_count		; Start the next count cycle
