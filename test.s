.org 0x08000000

main:
	mov.l ledStorage, r0
	mov #'x', r1
	mov.b r1, @r0
	bsr main
	nop
	nop

ledStorage:
.long 0xBA202070
