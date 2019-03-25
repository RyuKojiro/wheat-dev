.text

main:
		! r10 = the entire number to print
	mov #0, r10                ! Reset r10 (counter)
loop:
	bsr displayEntireNumber    ! Display the number
	nop                        ! Empty Branch Delay Slot
	bra loop                   ! Repeat Unconditionally
	add #1, r10                ! ⤷ Increment the number

.include "led.s"
