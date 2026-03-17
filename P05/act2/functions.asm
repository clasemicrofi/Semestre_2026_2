        .global initPJ, initPM
        .text

SYSCTL_RCGCGPIO_R   .field 0x400FE608, 32

GPIO_PORTJ_DATA_R   .field 0x400603FC, 32
GPIO_PORTJ_DIR_R    .field 0x40060400, 32
GPIO_PORTJ_PUR_R    .field 0x40060510, 32
GPIO_PORTJ_PDR_R    .field 0x40060514, 32
GPIO_PORTJ_DEN_R    .field 0x4006051C, 32
GPIO_PORTJ_CR_R     .field 0x40060524, 32

GPIO_PORTM_DATA_R   .field 0x400633FC, 32
GPIO_PORTM_DIR_R    .field 0x40063400, 32
GPIO_PORTM_DEN_R    .field 0x4006351C, 32

initPJ:
		; Habilita reloj del puerto J
		LDR		R0, SYSCTL_RCGCGPIO_R
		LDR		R1, [R0]
		ORR		R1, #0x0100
		STR		R1, [R0]

		; Pone a PJ1 y PJ0 como entradas
		LDR		R0, GPIO_PORTJ_DIR_R
		LDR		R1, [R0]
		AND		R1, #0x00FC
      	STR		R1, [R0]

		; Commit register
		;LDR		R0, GPIO_PORTJ_CR_R
		;LDR		R1, [R0]
		;ORR		R1, #0x0003
      	;STR		R1, [R0]

		; Resistencias de pull up
		LDR		R0, GPIO_PORTJ_PUR_R
		LDR		R1, [R0]
		ORR		R1, #0x0003
      	STR		R1, [R0]

      	; Habilita entradas digitales
      	LDR		R0, GPIO_PORTJ_DEN_R
		LDR		R1, [R0]
		ORR		R1, #0x0003
      	STR		R1, [R0]
      	BX		LR

; Function for initialize the port M
initPM:
		; Habilita reloj del puerto M
		LDR		R0, SYSCTL_RCGCGPIO_R
		LDR		R1, [R0]
		ORR		R1, #0x0800
		STR		R1, [R0]

		; Pone a PM0 como salida
		LDR		R0, GPIO_PORTM_DIR_R
		LDR		R1, [R0]
		ORR		R1, #0x0001
      	STR		R1, [R0]

      	; Habilita salida digital
      	LDR		R0, GPIO_PORTM_DEN_R
		LDR		R1, [R0]
		ORR		R1, #0x0001
      	STR		R1, [R0]

      	BX		LR
		.end
