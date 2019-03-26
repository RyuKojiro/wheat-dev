main:
	mov.l ledDataOffset, r1    ! Get the address to the offset
	mov #'x', r2               ! Get the character ready
	mov.b r2, @r1              ! Display the character
idle:
	bra idle                   ! Displacement-based branch
	nop                        ! Branch delay slot

.align 2
ledDataOffset:
.long 0xBA202070
