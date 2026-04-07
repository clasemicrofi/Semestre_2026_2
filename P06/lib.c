
#include "lib.h"


#define oper(a, b)   a*b + 4

// En en lenguaje C existen dos términos
// relativos a las funciones, la definición
// y la declaración.

/* Definición:
 * Es el cuerpo de una función, el código
 * que hace la tarea de la función.
*/

// Función que suma el valor de una variable local con
// los parámetros recibidos
int func1(int a, int b)
{
    // Las variables dentro de las funciones
    // se llaman variables locales y solo existen
    // dentro de las funciones
    int varLoc = 5;
    return a + b + varLoc;
}

// Función que recorre los elementos de una
// cadena de caracteres
char func2(const char* str)
{
    char ap;
    while(*str)
    {
        ap = *str++;
    }
    return ap;
}

int func3(int x, int y)
{
    return oper(x, y);
}
