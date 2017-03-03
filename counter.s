.text

main:
		! r0 = the entire number to print
	mov #0, r0                 ! Reset r0 (counter)
loop:
	bsr displayEntireNumber    ! Display the number
	nop                        ! Branch Delay Slot
	bra loop                   ! Repeat Unconditionally
	add #1, r0                 ! Increment the number

displayEntireNumber:
		! r0 = the entire number to print
		! r1 = digit iterator
		! r2 = digit max constant
		! r3 = digit address in memory
		! r4 = the character to print
		! r5 = temporary relative
	mov #0, r1                       ! r1 will be our digit iterator
	mov #7, r2                       ! r2 will be our upper limit
displayDigit:
	mov.l @(ledDataOffset,pc), r3    ! Get the address to the offset
	shll r1                          ! r1 *= 2
	add r1, r3                       ! Add the digit number (*2) to the offset
	shlr r1                          ! r1 /= 2
	mov #'[', r4                     ! Calculate the character for the digit
	mov.b r4, @r3                    ! Write character to display digit
	cmp/gt r1, r2                    ! Are we done with the 8th digit yet?
	add #1, r1                       ! Increment the digit count
	bt displayDigit                  !   If not, go to the next digit
	rts
	nop


getCurrentDigit:
		! r0 = the entire number to print
		! r1 = digit iterator
		! r6 = the current nibble
		! r4 = the character to print

	; Put the number into the nibble register
	; Shift over to the nibble we want
	; Mask away the rest
	; Normalize to a character

.align 2
ledDataOffset:
.long 0xBA202070
