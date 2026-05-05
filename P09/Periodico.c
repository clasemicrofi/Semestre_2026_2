#include <stdint.h>
#include "tm4c1294ncpdt.h"

/*
 * =========================
 * ISR: Timer 5A
 * =========================
 * Rutina de servicio a interrupción del Timer 5A.
 * Se ejecuta cada vez que ocurre un timeout del temporizador.
 */
void intTIMER5A(void)
{
    /*
     * 1. Deshabilita temporalmente el Timer A
     *    Esto evita que ocurra otra interrupción mientras se ejecuta la ISR.
     */
    TIMER5_CTL_R &= ~TIMER_CTL_TAEN;

    /*
     * 2. Limpia la bandera de interrupción (TATOCINT)
     *    Escribiendo '1' en el bit correspondiente del registro ICR.
     */
    TIMER5_ICR_R = TIMER_ICR_TATOCINT;

    /*
     * 3. Alterna (toggle) el estado del pin PN0
     *    XOR con 1:
     *    - Si estaba en 0 → pasa a 1
     *    - Si estaba en 1 → pasa a 0
     *
     * Esto típicamente se usa para parpadear un LED.
     */
    GPIO_PORTN_DATA_R ^= 0x1;

    /*
     * 4. Vuelve a habilitar el Timer A
     */
    TIMER5_CTL_R |= TIMER_CTL_TAEN;
}

/*
 * ISR: Timer 5B (no utilizada)
 */
void intTIMER5B(void)
{
    // No implementada
}

/*
 * ISR: Timer 3A (no utilizada)
 */
void Timer03AIntHandler(void)
{
    // No implementada
}

/*
 * =========================
 * Inicialización del Puerto N
 * =========================
 * Configura PN0 y PN1 como salidas digitales.
 */
void initPORTN(void)
{
    /*
     * 1. Habilita el reloj del puerto N
     *    (bit 12 en RCGCGPIO)
     */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12;

    /*
     * Esperar a que el puerto esté listo:
     */
    while((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R12) == 0);

    /*
     * 2. Configura PN0 y PN1 como salidas
     */
    GPIO_PORTN_DIR_R = 0x03;

    /*
     * 3. Habilita función digital en PN0 y PN1
     */
    GPIO_PORTN_DEN_R = 0x03;

    /*
     * 4. Inicializa los pines en bajo (apagados)
     */
    GPIO_PORTN_DATA_R = 0x0;
}

/*
 * =========================
 * Función principal
 * =========================
 */
void main()
{
    /*
     * Inicializa el puerto N (LEDs)
     */
    initPORTN();

    /*
     * =========================
     * 1. Habilitar reloj del Timer 5
     * =========================
     */
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R5;

    /*
     * Espera hasta que el Timer 5 esté listo
     */
    while ((SYSCTL_PRTIMER_R & SYSCTL_RCGCTIMER_R5) == 0);

    /*
     * =========================
     * 2. Deshabilitar el temporizador antes de configurar
     * =========================
     */
    TIMER5_CTL_R = 0;

    /*
     * =========================
     * 3. Configuración del modo del temporizador
     * =========================
     */

    /*
     * Modo 32 bits (individual)
     */
    TIMER5_CFG_R = 0;

    /*
     * Configuración de Timer A:
     *
     * TIMER_TAMR_TAMR_PERIOD → Modo periódico (se repite automáticamente)
     * TIMER_TAMR_TACDIR      → Conteo ascendente
     *
     * NOTA: Por defecto suele usarse descendente.
     */
    TIMER5_TAMR_R = TIMER_TAMR_TAMR_PERIOD | TIMER_TAMR_TACDIR;

    /*
     * =========================
     * 4. Valor de recarga
     * =========================
     *
     * Determina el periodo de interrupción.
     *
     * Ejemplo (si el clock es 16 MHz):
     * 16,000,000 → 1 segundo
     * 48,000,000 → 3 segundos
     */

    //TIMER5_TAILR_R = 16000000;  // ~1 segundo
    TIMER5_TAILR_R = 48000000;   // ~3 segundos

    /*
     * =========================
     * 5. Configuración de interrupciones
     * =========================
     */

    /*
     * Limpia bandera previa
     */
    TIMER5_ICR_R = TIMER_ICR_TATOCINT;

    /*
     * Habilita interrupción por timeout
     */
    TIMER5_IMR_R = TIMER_IMR_TATOIM;

    /*
     * Habilita interrupción en NVIC
     * Timer 5A corresponde a IRQ 93 → bit 1 en EN2
     */
    NVIC_EN2_R |= 0x2;

    /*
     * =========================
     * 6. Habilitar temporizador
     * =========================
     */
    TIMER5_CTL_R = TIMER_CTL_TAEN | TIMER_CTL_TASTALL;

    /*
     * =========================
     * 7. Loop infinito
     * =========================
     */
    while (1)
    {
        // El sistema queda en espera de interrupciones
    }
}
