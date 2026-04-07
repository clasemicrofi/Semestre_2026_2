
/* Los archivos cabecera permiten definir funciones o tipos de datos
 * Se usan <header.h> cuando las cabeceras están incluidas como parte
 * del estándar y se usan "header.h" cuando son definidas por el
 * usuario dentro del proyecto.
 */
#include <stdint.h>
#include <stdbool.h>
#include "lib.h"

// Define una variable global
uint32_t varGlob = 4;

// Plantilla para crear una estructura
typedef struct
{
    int data1;
    float data2;
    char data3;
}ST;

// Declaración de una función
void control_y_flujo(void);

extern void func4(void);
extern void func5(uint32_t x, uint32_t y);

// La función main es la función principal
/* int: representa el tipo de dato que la función devuelve.
 * main: es el nombre de la función.
 * (void): son los parámetros que recibe la función y cuyo
 * tipo de dato es indicado para cada uno.
 */
int main(void)
{
    // En C podemos tener los siguientes tipos de datos básicos
    // Entero
    int n = 0;
    // Flotante
    float f = 3.1416;
    // Double
    double d = 543e-8;
    // Caracter
    char c = 'A';

    // Tipos enteros de longitud fija (Usar stdint.h)
    uint8_t u1 = 32;
    uint16_t u2 = 237;
    uint32_t u3 = -54;
    uint64_t u4 = 0xFFFF;

    // Conversiones entre tipos de datos
    // Flotante a entero
    f = -8.935;
    n = (int)f;
    // Entero a flotante
    n = 897;
    f = (float)n;
    // Caracter a entero
    c = 'G';
    n = (int)c;
    // Caracter a entero sin signo de 8 bits
    c = 'g';
    uint8_t n2 = (uint8_t)c;

    // Arreglos
    char s1[] = "String\0";
    char s2[6] = "Texto\0";
    int AR1[2][2] = {{0, -3}, {2, 7}};

    n = AR1[0][1];

    // Estructuras
    ST t1 = {.data1 = -2, .data2 = -1.25, .data3 = 'T'};
    t1.data1 = 0;
    t1.data3 = 'H';

    // Apuntadores
    char* ap;
    ap = &s1;

    // Se puede usar un apuntador para acceder
    // a los elementos de un arreglo
    char letra;
    letra = *ap++;
    letra = *ap++;
    letra = *ap++;
    letra = *ap++;
    letra = *ap++;
    letra = *ap++;
    letra = *ap++;

    // Operadores lógicos bitwise
    uint32_t dato = 0;

    // Operador NOT
    dato = ~dato;
    // Operador AND
    dato = dato & 0x0000FFFF; // Otra forma equivalente es: dato &= 0x0000FFFF
    // Operador OR
    dato = dato | 0x14000000;
    // Operador XOR
    dato = dato ^ 0x000000AA;

    // Operadores lógicos de condición
    bool val;
    uint32_t num1 = 0xF, num2 = 0xF;

    val = num1 && num2;
    val = num1 || num2;
    val = !num1;

    // Operadores aritméticos
    dato = 0;
    // Suma
    dato = dato + 3; // Otra forma equivalente es: dato +=3

    // Resta
    dato = dato - 1;
    // Multiplicación
    dato = dato*8;
    // División
    dato = dato/4;

    // Incremento
    dato = dato++;
    // Decremento
    dato = dato--;
    dato++;
    dato--;

    // Aplica a todos los tipos
    char m = '2';
    m = m + 4;
    m = m*1;

    // Funciones
    int r = func1(2, 4);
    func2("Texto2\0");
    r = func3(2, 3);
    func4();
    func5(4, 6);
    control_y_flujo();
	return 0;
}


void control_y_flujo(void)
{
    // Estructura if-else
    int num = 10;
    bool isPositive;

    if (num > 0)
    {
        isPositive = true; // El número es positivo
    }
    else if (num == 0)
    {
        isPositive = false; // El número es cero
    }
    else
    {
        isPositive = false; // El número es negativo
    }
    isPositive = 0;

    // Estructura for
    int i, j;
    for (i = 0; i < 3; i++)
    {
                    // Realiza alguna operación, como incrementar una variable
        num += i;   // Acumula el valor de i en num
    }

    // Recorre elementos de una matriz
    char M[2][2] = {{'E', 'F'}, {'1', 'P'}};
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
        {
            num = (int)M[i][j];
        }

    // Estructura while
    i = 0;                  // Reinicializamos i
    while (i < 3)
    {
        // Incrementar una variable
        num += i;           // Acumula el valor de i en num
        i++;                // Incrementar i
    }

    // Estructura do-while
    i = 0;                  // Reinicializamos i
    do
    {
        // Incrementar una variable
        num += i;           // Acumula el valor de i en num
        i++;                // Incrementar i
    } while (i < 3);

    // Estructura switch
    int opcion = 2;
    int resultado = 0;

    switch (opcion)
    {
        case 1:
            resultado = 1; // Asignar resultado
            break;
        case 2:
            resultado = 2; // Asignar resultado
            break;
        case 3:
            resultado = 3; // Asignar resultado
            break;
        default:
            resultado = -1; // Opción no válida
            break;
    }
    return;
}

