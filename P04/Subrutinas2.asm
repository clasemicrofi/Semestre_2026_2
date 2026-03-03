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

cte100k		.field	5, 32

main:
			BL		port_init
			LDR		R0, dirmemio

			; Inicializa la memoria
			MOV		R1, #6
			STR		R1, [R0]

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
			LDR		R3, cte100k
			PUSH	{R14}
			BL		retardo1
			POP		{R14}
			BNE		repetir1
			B		subrutina1
retardo1:
			LDR		R4, cte100k
			PUSH	{R14}
			BL		retardo2
			POP		{R14}
			SUBS	R3, #1
			BNE		retardo1
			BX		LR
retardo2:
			SUBS	R4, #1
			BNE		retardo2
			BX		LR
			.end
