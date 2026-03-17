      	.global main
      	.global initPJ, initPM

      	.text

GPIO_PORTJ_DATA_R	.field 0x4006000C, 32
GPIO_PORTM_DATA_R	.field 0x40063004, 32

VAL_T	.field	108399
MAX_V	.field	13548
MIN_V	.field	2708

Boton1	.equ	0x01
Boton2	.equ	0x02
Paso	.equ	150

main:
		; #######################################
		; Inicializa los puertos PJ [1:0] y PM[0]
		; #######################################
		BL		initPJ
		BL		initPM

		; #######################################
		; Inicializa variables y registros
		; #######################################
		LDR		R4, MIN_V
		LDR		R5, VAL_T

		LDR		R1, GPIO_PORTM_DATA_R

repite:
		; ####################################
		; Lee el estado de los botones PJ[1:0]
		; ####################################
		LDR		R0, GPIO_PORTJ_DATA_R
		LDR		R0, [R0]

		; ####################################
		; Salta a la opción seleccionada
		; ####################################
		CMP		R0, #Boton1
		BEQ		opcion1
		CMP		R0, #Boton2
		BEQ		opcion2
		B		gen_onda

opcion1:
		; ####################################
		; Incrementar T_High (R4) hasta MAX: 180°
		; ####################################
		ADD		R4, #Paso
		LDR		R3, MAX_V

		; T_High > MAX_V
		CMP		R4, R3
		BGT		ifgt
		B		gen_onda
ifgt:
		LDR		R4, MAX_V
		B		gen_onda
opcion2:
		; ####################################
		; Decrementar contador (R4) hasta MIN: 0°
		; ####################################
		SUB		R4, #Paso

		LDR		R3, MIN_V

		; T_High < T_Min
		CMP		R4, R3
		BLE		iflo
		B		gen_onda
iflo:
		LDR		R4, MIN_V
gen_onda:
		; ####################################
		; Poner GPIO_M0 en alto
		; ####################################
		MOV		R2, #0x01
		STR		R2, [R1]
		; ####################################
		; Generar retardo de T_High
		; ####################################
		MOV		R6, R4
ret_h:
		SUBS	R6, #0x01
		BNE		ret_h

		; ####################################
		; Poner GPIO_M0 en bajo
		; ####################################
		MOV		R2, #0x00
		STR		R2, [R1]

		; ####################################
		; Generar retardo de T_Low = T_Onda - T_High
		; ####################################
		SUBS	R6, R5, R4
ret_l:
		SUBS	R6, #0x01
		BNE		ret_l
		B		repite
		.end


