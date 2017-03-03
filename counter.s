.text

main:
	mov #0, r0                 ! Reset r0 (counter)
loop:
	bsr displayEntireNumber    ! Display the number
	nop                        ! Branch Delay Slot
	bra loop                   ! Repeat Unconditionally
	add #1, r0                 ! Increment the number

displayEntireNumber:
		! r0 = the entire number to print
		! r1 = digit number
		! r2 = digit max constant
		! r3 = digit address in memory
		! r4 = the character to print

	mov #7, r2                 ! r2 will be our upper limit
displayDigit:
	mov r1, r3                 ! Put the target digit location in r3
	shll r3                    ! r3 *= 2

	cmp/gt r1, r2              ! Are we done with the 8th digit yet?
	bt displayDigit            ! If not, go to the next digit
	add #1, r1                 ! Delayed Branch - Increment the digit count

	rts
	nop
