; Estructura básica de un programa ensamblador
        .global main     ; declara la etiqueta 'main' como global para que el linker la reconozca

        .text            ; indica que lo que sigue está en la sección de código (instrucciones)

main:                    ; define la etiqueta 'main', punto de entrada del programa

        B   main         ; instrucción de salto incondicional, salta a 'main' (bucle infinito)

        .end             ; marca el fin del código fuente
