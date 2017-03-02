.org 0x08000000

main:
	mov.l ledStorage, r0
	mov.b letterX, @r0
	rts
	nop

ledStorage:
.long 0xBA202070

letterX:
.byte 'x'
