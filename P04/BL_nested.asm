; Saltos anidados de subrutinas

		.global main
		.text

main:
		BL		func1
		B		main
func1:
		BL		func2
		BX		LR
func2:
		BL		func3
		BX		LR
func3:
		BL		func4
		BX		LR
func4:
		NOP
		BX		LR
		.end
