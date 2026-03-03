; Convertir la lista de 5 números almacenados en memoria
; en formato byte signado a 32 bits signado. Almacenarlos
; a partir de la dirección de memoria 0x20000300

		.global main, nums
		.data
nums	.byte	-4, -5, -3, -7, 2
		.text
list	.field	nums, 32
dest	.field	0x20000300, 32
main:
		LDR		R0, list
		LDR		R1, dest

		LDRB	R2, [R0], #1
		LSL		R2, #24
		ASR		R2, #24
		STR		R2, [R1], #4

		LDRB	R2, [R0], #1
		LSL		R2, #24
		ASR		R2, #24
		STR		R2, [R1], #4

		LDRB	R2, [R0], #1
		LSL		R2, #24
		ASR		R2, #24
		STR		R2, [R1], #4

		LDRB	R2, [R0], #1
		LSL		R2, #24
		ASR		R2, #24
		STR		R2, [R1], #4

		LDRB	R2, [R0], #1
		LSL		R2, #24
		ASR		R2, #24
		STR		R2, [R1], #4
fin:
		B		fin
		.end
