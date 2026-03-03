; Saltos a subrutinas con retorno
; y restauración de registros.

		.global main
		.text

main:
		; Cargar R3 <- 1 y R4 <- 2
		MOV		R3, #1
		MOV		R4, #2

		; Saltar a subrutina
		BL		func1
		; Hacer la suma de 1 y 2
		ADD		R5, R3, R4
		B		main
func1:
		; Cargar R3 <- 4 y R4 <- 7
		MOV		R3, #4
		MOV		R4, #7
		; Hacer la suma de 4 y 7
		ADD		R3, R3, R4

		; Regresa de subrutina
		BX		LR
		.end
