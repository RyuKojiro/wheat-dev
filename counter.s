.text

main:
	mov #0, r0                 ! Reset r0 (counter)
loop:
	bsr displayEntireNumber    ! Display the number
	nop                        ! Branch Delay Slot
	bra loop                   ! Repeat Unconditionally
	add #1, r0                 ! Increment the number

displayEntireNumber:
	mov.l r1, @-r15            ! Push r1 onto the stack

	mov #7, r2                 ! r2 will be our upper limit
displayDigit:
	
	cmp/gt r1, r2              ! Are we done with the 8th digit yet?
	bt displayDigit            ! If not, go to the next digit
	add #1, r1                 ! Delayed Branch - Increment the digit count

	mov.l @r15+, r1            ! Pop the stack
	rts
	nop
