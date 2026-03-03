        .global main
		.data
Val:	.word	3, 0, 1, 2, 7, 4


        .text

; Inicia variables
mat		.field	Val,  32

main:
		; ################################
		; if ((R1 & R2) == 0xA)
		; ################################
		MOV		R1, #0xA
		MOV		R2, #0xA

		AND		R3, R1, R2
		CMP		R3, #0xA
		BEQ		true
		B		false
true:
		NOP
		B		continua
false:
		NOP
		B		continua

continua:
		NOP
		; ################################
		; for (i = 1, i < 9; i = i + 2)
		; ################################

		; i = 1
		MOV		R1, #1
for:
		; i < 9?
		CMP		R1, #9
		BGE		finFor
		; Cuerpo de ejecución
		; -------------------
		NOP
		; -------------------
		; i = i + 2
		ADD		R1, #2
		B		for

		; ################################
		; for (i = 0, i < 4; i = i + 1)
		; 		for (j = 0, j < 4; j = j + 1)
		; ################################
finFor:
		; i = 0
		MOV		R1, #0
for1:
		; i < 4?
		CMP		R1, #4
		BGE		finFor1
; --------------------------------
		; j = 0
		MOV		R2, #0
for2:
		; j < 4?
		CMP		R2, #4
		BGE		finFor2
		; Cuerpo de ejecución de for2
		; ----------
		NOP
		; ----------
		; j = j + 1
		ADD		R2, #1
		B		for2
finFor2:
; --------------------------------
		; i = i + 1
		ADD		R1, #1
		B		for1

finFor1:
		NOP
		NOP
		; ################################
		; While (R3 < 5)
		; ################################
		MOV		R3, #0
while:
		CMP		R3, #5
		BGE		finWhile
		; Cuerpo de ejecución
		; -------------------
		NOP
		; -------------------
		ADD		R3, #1
		B		while
finWhile:
		NOP
		NOP
		; ################################
		; Switch case R3: 2, 1, (3 o 0)
		; ################################
		MOV		R3, #0
switch:
		CMP		R3, #0x1
		BEQ		caso1
		CMP		R3, #0x2
		BEQ		caso2
		B		otros
caso1:
		NOP
		B		sigue
caso2:
		NOP
		B		sigue
otros:
		NOP
		B		sigue
sigue:
		NOP
		ADD		R3, #1
		B		switch
        .end
