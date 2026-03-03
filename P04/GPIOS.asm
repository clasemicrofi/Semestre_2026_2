      	.global port_init
      	.text

SYSCTL_RCGCGPIO_R   .field 0x400FE608, 32

GPIO_PORTF_DATA_R   .field 0x4005D3FC, 32
GPIO_PORTF_DIR_R    .field 0x4005D400, 32
GPIO_PORTF_PUR_R    .field 0x4005D510, 32
GPIO_PORTF_PDR_R    .field 0x4005D514, 32
GPIO_PORTF_DEN_R    .field 0x4005D51C, 32

; QPN MLKJ HGFE DCBA

port_init:
		; Habilita reloj del puerto F
		LDR		R0, SYSCTL_RCGCGPIO_R
		LDR		R1, [R0]
		ORR		R1, #0x0020
		STR		R1, [R0]

		; Pone a PF1 y PF2 como salidas
		LDR		R0, GPIO_PORTF_DIR_R
		LDR		R1, [R0]
		ORR		R1, #0x0006
      	STR		R1, [R0]

      	; Habilita salidas digitales
      	LDR		R0, GPIO_PORTF_DEN_R
		LDR		R1, [R0]
		ORR		R1, #0x0006
      	STR		R1, [R0]

      	; Apaga PF2 y PF1
      	LDR		R0, GPIO_PORTF_DATA_R
		LDR		R1, [R0]
		ORR		R1, #0x0000
      	STR		R1, [R0]
      	BX		LR

		.end


