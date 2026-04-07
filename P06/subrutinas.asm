	.global func4, func5
	.text
func4:
	PUSH	{R7, R8, R9}
	MOV		R7, #4
	MOV		R8, #3
	ADD		R9, R7, R8
	POP		{R9, R8, R7}
	BX		LR

func5:
	PUSH	{R0, R1, R2}
	ADD		R2, R0, R1
	POP		{R2, R1, R0}
	BX	LR
	.end
