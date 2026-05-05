#include <stdint.h>
#include "tm4c1294ncpdt.h"

/*
 * =========================
 * ISR: Timer 5A
 * =========================
 * Esta función es la rutina de servicio a interrupción (ISR)
 * del temporizador 5, submódulo A.
 */
void intTIMER5A(void)
{
    /*
     * Limpia la bandera de interrupción del Timer A Timeout (TATOCINT)
     * Escribiendo un '1' en el bit correspondiente del registro ICR.
     *
     * NOTA: Solo es necesario hacerlo UNA vez.
     * Aquí está repetido 3 veces (innecesario).
     */
    int n = 200;
    while(n--);
    TIMER5_ICR_R = TIMER_ICR_TATOCINT;
}

/*
 * ISR: Timer 5B
 * (No implementada)
 */
void intTIMER5B(void)
{
    // Vacía: no se está utilizando el submódulo B
}

/*
 * ISR: Timer 3A
 * (No implementada)
 */
void Timer03AIntHandler(void)
{
    // Vacía: no se utiliza
}

/*
 * =========================
 * Función principal
 * =========================
 */
void main()
{
    /*
     * =========================
     * 1. Habilitar reloj del Timer 5
     * =========================
     */
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R5;

    /*
     * Espera hasta que el periférico esté listo
     */
    while ((SYSCTL_PRTIMER_R & SYSCTL_RCGCTIMER_R5) == 0);

    /*
     * =========================
     * 2. Deshabilitar Timer antes de configurar
     * =========================
     */
    TIMER5_CTL_R = 0;

    /*
     * =========================
     * 3. Configurar modo del temporizador
     * =========================
     */

    /*
     * GPTMCFG = 0
     * Configura el temporizador como:
     * - 32 bits (modo individual)
     */
    TIMER5_CFG_R = 0;

    /*
     * Configuración de Timer A:
     * - TIMER_TAMR_TAMR_1_SHOT → Modo One-Shot (una sola ejecución)
     * - TIMER_TAMR_TACDIR       → Conteo ascendente (UP)
     *
     * NOTA: Si no quieres ascendente, quita TACDIR.
     */
    TIMER5_TAMR_R = TIMER_TAMR_TAMR_1_SHOT | TIMER_TAMR_TACDIR;

    /*
     * =========================
     * 4. Cargar valor inicial
     * =========================
     *
     * Este valor determina cuánto tiempo tarda en generar la interrupción.
     *
     * Ejemplo:
     * Si el reloj del sistema es 16 MHz:
     * - 16,000,000 → 1 segundo
     * - 64,000,000 → 4 segundos
     */

    //TIMER5_TAILR_R = 16000000;   // ~1 segundo
    TIMER5_TAILR_R = 64000000;    // ~4 segundos

    /*
     * =========================
     * 5. Configurar interrupciones
     * =========================
     */

    /*
     * Limpia cualquier bandera previa
     */
    TIMER5_ICR_R = TIMER_ICR_TATOCINT;

    /*
     * Habilita interrupción por timeout (Timer A)
     */
    TIMER5_IMR_R = TIMER_IMR_TATOIM;

    /*
     * Habilita interrupción en el NVIC
     *
     * NVIC_EN2_R controla interrupciones 64–95.
     * El Timer 5A corresponde al bit 1 (IRQ 93).
     */
    NVIC_EN2_R |= 0x2;

    /*
     * =========================
     * 6. Habilitar el temporizador
     * =========================
     *
     * TIMER_CTL_TAEN   → Activa Timer A
     * TIMER_CTL_TASTALL → Detiene el timer al hacer debug (opcional)
     */
    TIMER5_CTL_R = TIMER_CTL_TAEN | TIMER_CTL_TASTALL;

    /*
     * =========================
     * 7. Loop infinito
     * =========================
     */
    while (1)
    {
        // El microcontrolador permanece aquí
        // esperando interrupciones
    }
}
