.text

! Automatic Number Announcement Circuit
!     In the olden days these were numbers useful for reading back the calling
!     number. Here it announces the PC via the LED display, in the hopes that
!     this will hint at where the flash resides in the address space when
!     booting directly from flash.

main:
	bsr display                ! A bsr/jsr/bsrf is required to populate PR
	nop                        ! Empty Branch Delay Slot
display:
		! r10 = the entire number to print
	sts pr, r10                ! PR -> r10
	add #(main-display), r10               ! Subtract the offset from main
	bsr displayEntireNumber    ! Display the number
	nop                        ! Empty Branch Delay Slot
loop:
	bra loop                   ! Repeat Unconditionally
	nop                        ! Empty Branch Delay Slot

.include "led.s"
