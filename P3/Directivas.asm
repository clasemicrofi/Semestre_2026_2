		; La directiva .global define la visibilidad de
		; los simbolos dentro de un módulo
		.global main       ; main será accesible desde el linker
		.global mydata     ; símbolo mydata también visible
		.global data2      ; símbolo data2 también visible

		; La directiva .data indica que las siguientes
		; líneas de ensamblador estarán en memoria de datos
		.data
		; Se pueden definir los siguientes tipos de datos:
		; .byte, .char, .int, .long, .word, .double
		; .half, .short, .string, .float y .field

		; Ejemplo: definición de variables y constantes en memoria
mydata	.byte	12, 0xFF, 10101100b, 99, -15  ; define 5 bytes
		.char	'C', 'h', 'a', 'r'             ; define caracteres ASCII
		.int	23, 876, -56                   ; enteros de 32 bits
		.long	123, 987                       ; enteros largos (32 bits en ARM)
		.word	45, 37, -21, 89, 0x12, 0xFF, 0x1A, 0x95 ; palabras (16 bits)
		.space	8                              ; reserva 8 bytes sin inicializar
		.double	2.3345                         ; número en doble precisión (64 bits)
		.half	121                            ; número de 16 bits
		.short	12                             ; entero corto (16 bits)
		.string	"Hello"                        ; cadena terminada en 0
		.float	3.456, 4.567, -2.11, -4.25     ; números en punto flotante

		; La directiva .field indica que se define un espacio de
		; memoria que contiene un dato del tamaño indicado:
		; Símbolo	.field	dato, tamaño en bits
Var1	.field	0x20000200, 32   ; valor de 32 bits
var2	.field	0xFFAB, 16       ; valor de 16 bits
var3	.field	5, 8             ; valor de 8 bits

		; La directiva .set y .equ asignan un valor a un símbolo
cte1	.set	4                ; cte1 = 4
cte2	.equ	6                ; cte2 = 6

		; Asignación de símbolos/etiquetas a datos ya definidos
dat1	.word	45, 67, 99       ; define 3 palabras consecutivas

		; Sección de código (.text)
		.text

		; ¿Cuál de las siguientes directivas no genera datos en memoria?
cte3	.field	0xABCDF012, 32
cte4	.field	0x01010101, 32

cte5	.set	4
cte6	.equ	6

cte7	.field	0x12345678, 32
cte8	.field	0xFFA67983, 32

		; Se puede hacer referencia a los datos de otra sección
vect	.field	dat1, 32   ; guarda la dirección de dat1 (puntero)

; Etiqueta que representa el inicio de la subrutina main
main:
		LDR		R0, vect    ; carga en R0 la dirección almacenada en 'vect'
		LDR		R0, [R0]    ; carga en R0 el contenido apuntado por esa dirección

		MOV		R0, #cte1   ; mueve el valor inmediato de cte1 a R0
		MOV		R0, #cte2   ; sobrescribe R0 con el valor inmediato de cte2
		MOV		R1, #0x24   ; mueve el valor inmediato 0x24 a R1

		LDR		R0, cte3    ; carga en R0 la constante definida en cte3
		LDR		R0, cte8    ; carga en R0 la constante definida en cte8
		B		main        ; salto incondicional a main (bucle infinito)

		; Nueva sección de datos, después del código
		.data
data2	.word	0x45, 0x56, 0x43, 0x00 ; arreglo de palabras

		; Fin del ensamblado
		.end
