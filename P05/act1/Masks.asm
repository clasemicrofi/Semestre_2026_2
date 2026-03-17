; A partir de la dirección base en
; GPIO_PORTF_DATA_R definir las máscaras
; a aplicar según sea el caso

		.global main
		.global portF_init
		.text

GPIO_PORTF_DATA_ALL	.field 0x4005D3FC, 32

; Dirección base para el registro GPIO_DATA del puerto F
GPIO_PORTF_DATA_R	.field 0x4005D000, 32

main:
		; Inicializa el puerto
		BL		portF_init
		LDR		R0, GPIO_PORTF_DATA_ALL
		MOV		R1, #0x0000
		STR		R1, [R0]

		; R1 almacena un valor constante de 0x0000 FFFF
		MOV		R1, #0xFFFF
		; R2 almacena un valor constante de 0x0000 0000
		MOV		R2, #0x0000

		; Defina el uso de una máscara que permita
		; encender o apagar en cada caso lo que se indica

		; Recomendación: se puede sumar a la dirección base
		; el valor de la máscara a aplicar

		; Encender solo el bit 3
		LDR		R0, GPIO_PORTF_DATA_R
		STR		R1, [R0]

		; Encender solo el bit 1
		LDR		R0, GPIO_PORTF_DATA_R
		STR		R1, [R0]

		; Encender solo el bit 4
		LDR		R0, GPIO_PORTF_DATA_R
		STR		R1, [R0]

		; Encender solo el bit 0
		LDR		R0, GPIO_PORTF_DATA_R
		STR		R1, [R0]

		; Apagar los bits 3 y 1
		LDR		R0, GPIO_PORTF_DATA_R
		STR		R2, [R0]

		; Encender todo el puerto F [4:0]
		LDR		R0, GPIO_PORTF_DATA_R
		STR		R1, [R0]

		; Apagar los bits 4, 2, 0
		LDR		R0, GPIO_PORTF_DATA_R
		STR		R2, [R0]
fin:
		B		fin
		.end
