

		.global	 main
		.text

DIR_HEX .field   0x20000200, 32

Cte1	.equ	0x3456
Cte2	.equ	0x1298

Var1	.word	0x34567890

main:
		; Carga un dato de 32 bits al registro R0
		MOVW	R1, #Cte1
		MOVT	R1, #Cte2

		; Carga un dato de 32 bits al registro R0
		MOVW	R0, #0x0200
		MOVT	R0, #0x2000

		STR		R1, [R0]
		STRH	R1, [R0, #4]
		STRB	R1, [R0, #8]

		LDR		R8, Var1

		; R8 Apunta a la tabla de constantes
		ADR 	R8, CTS

		; Carga datos de tabla
		LDR 	R1, [R8]
		LDR 	R1, [R8, #4]
		LDR 	R1, [R8, #8]
		LDR 	R1, [R8, #12]

		MOV 	R1, #5     	; Carga el contador
DECR1:	NOP
		NOP
		SUBS 	R1,#1		; Decrementa cuenta
		BNE 	DECR1

		BL		FUNC1

		B 		main

FUNC1:
		NOP
		; Apunta al dato de entrada
		LDR		R0, DIR_HEX

		; Lee dato de entrada
		LDR		R2, [R0]

		MOVT	R1, #0xFFFF
		ADDS	R1, R2

		BX		LR

CTS 	.word 	0x98761233, 0x06AB1234, 0x64901234, 0x60AFFFDE
