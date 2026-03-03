; Hacer un programa en ensamblador que rote una
; matriz 3x3 en sentido antihorario

		.global main, dat1
		.data
dat1	.half	 5, 7
		.half	-3, 2

		.text
mat1	.field	dat1, 32
main:
		LDR		R0, mat1
loop:
		LDRH	R1, [R0, #0]
		LDRH	R2, [R0, #2]
		LDRH	R3, [R0, #4]
		LDRH	R4, [R0, #6]

		STRH	R1, [R0, #4]
		STRH	R2, [R0, #0]
		STRH	R3, [R0, #6]
		STRH	R4, [R0, #2]

		NOP
		B		loop
fin:
		B		fin
		.end
