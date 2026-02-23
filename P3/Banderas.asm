      	.global main
      	.text

main:
		; Limpia banderas
		MOV		R3, #6
		MOVS	R0, R3

		; Operacion 1
		; ----------------------
      	MOVW 	R0, #0x0000
      	MOVT 	R0, #0x0000

      	MOVS	R0, R0 ; Ejecucion
      	; -----------------------

		; Limpia banderas
      	MOVS	R0, R3

		; Operacion 2
		; ----------------------
      	MOVW	R0, #0xFFFF
      	MOVT	R0, #0xFFFF

      	ADDS	R0, R0, #0x01 ; Ejecucion
      	; ----------------------

		; Limpia banderas
      	MOVS	R0, R3

      	; Operacion 3
      	; ----------------------

      	MVNS 	R0, R0	; Ejecucion
      	; ----------------------

		; Limpia banderas
      	MOVS	R0, R3

      	; Operacion 4
      	; ----------------------
      	MOVW	R1, #0x0000
      	MOVT	R1, #0x8000

      	MOVW	R0, #0x0001
      	MOVT	R0, #0x0000

      	SUBS	R2, R1, R0 ; Ejecucion
      	; ----------------------

		; Limpia banderas
      	MOVS	R0, R3

      	; Operacion 5
      	; ----------------------
      	MOVW	R1, #0xFFFF
      	MOVT	R1, #0x7FFF

      	MOVW 	R0, #0x0001
      	MOVT 	R0, #0x0000

      	ADDS	R2, R0, R1 ; Ejecucion
      	; ----------------------

		; Limpia banderas
      	MOVS	R0, R3

		; Proponga otras formas de activar cada una de las banderas
fin:
	    B		fin

		.end


