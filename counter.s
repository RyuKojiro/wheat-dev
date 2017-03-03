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
		! r5 = temporary relative

	mov #7, r2                 ! r2 will be our upper limit
displayDigit:
	mov.l ledDataOffset, r5    ! Get the address to the offset
	mov.l @r5, r3              ! Set r3 to the offset
	shll r1                    ! r1 *= 2
	add r1, r3                 ! Add the digit number (*2) to the offset
	shlr r1                    ! r1 /= 2
	mov #'[', r4               ! Calculate the character for the digit
	mov.b r4, @r3              ! Write character to display digit
	cmp/gt r1, r2              ! Are we done with the 8th digit yet?
	bt displayDigit            ! If not, go to the next digit
	add #1, r1                 ! Delayed Branch - Increment the digit count

	rts
	nop

.align 2
ledDataOffset:
.long 0xBA202070
