; Hacer un programa en ensamblador que rote una
; matriz 3x3 en sentido antihorario

			.global main, dat1
			.global port_init
			.data
dat1		.half	 5, 7
			.half	-3, 2

			.text
mat1		.field	dat1, 32
dirmemio  	.field 	0x4005D3FC, 32

cte100k		.field	100000, 32

main:
			BL		port_init
			LDR		R0, dirmemio

			; Inicializa la memoria
			MOV		R1, #6
			STR		R1, [R0]
			B		subrutina1
inicio:
			MOV		R2, #0xFFFF
			MOV		R1, #6
			STR		R1, [R0]
			MOV		R1, #0
			STR		R1, [R0]
			B		inicio

subrutina1:
			; Carga 100,000 en R2
			LDR		R2, cte100k
			; Lee el dato y hace XOR con el
			LDR		R1, [R0]
			EOR		R1, #6
			STR		R1, [R0]
			; Proceso que se repite hasta que R0 = 0
repetir1:
			SUBS	R2, #1
			BNE		repetir1
			B		subrutina1
			.end
