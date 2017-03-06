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
		! r9 = temporary digit math
	sts.l pr, @-r15
	mov #0, r1                 ! r1 will be our digit iterator
	mov #7, r2                 ! r2 will be our upper limit
displayDigit:
	mov.l ledDataOffset, r3    ! Get the address to the offset
	mov #7, r9                 ! r9 = 7
	sub r1, r9                 ! r9 -= r1
	shll r9                    ! r9 *= 2
	add r9, r3                 ! Add the digit number (*2) to the offset
	bsr getCurrentDigit        ! Calculate the character for the digit
	nop
	mov.b r4, @r3              ! Write character to display digit
	add #1, r1                 ! Increment the digit count
	cmp/hs r1, r2              ! Are we done with the 8th digit yet?
	bt displayDigit            !   If not, go to the next digit
	lds.l @r15+, pr
	rts
	nop

.align 2
ledDataOffset:
.long 0xBA202070

getCurrentDigit:
		! r0 = the entire number to print
		! r1 = digit iterator
		! r7 = shift iterator
		! r6 = the current nibble
		! r4 = the character to print
		! r8 = hex alpha limit
	sts.l pr, @-r15
	mov #0, r7                 ! Reset the shift iterator
	mov r0, r6                 ! Put the number into the nibble register
	cmp/hi r7, r1              ! Is there more to shift?
	bf doneShifting            !   If not, bail
shift:
	shlr2 r6                   ! Shift over to the nibble we want
	shlr2 r6
	add #1, r7
	cmp/hi r7, r1              ! Is there more to shift?
	bt shift                   !   If so, repeat
doneShifting:
	mov #0xF, r8               ! Load up 0xF constant for masking
	and r8, r6                 ! Mask away anything higher than the nibble we care about
	mov #0xA, r8               ! Move 0xA constant into place for comparison
	cmp/hs r8, r6              ! Is r6 ≥ 0xA?
    bt itsAlpha                !   If so, it's alpha, go there
	add #'0', r6               ! Normalize to a numeric character
	bf digitDone

itsAlpha:
	add #'A' - 0xA, r6         ! Normalize to an alpha character
digitDone:
	mov r6, r4
	lds.l @r15+, pr
	rts
	nop
