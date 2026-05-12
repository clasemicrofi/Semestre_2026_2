#include "tm4c1294ncpdt.h"
#include <stdint.h>

void main()
{
    // ---------------- CONF. DEL PUERTO --------------------
    // Pin PA7 como PWM
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // Activar reloj de PA
    while((SYSCTL_PRGPIO_R && SYSCTL_PRGPIO_R0) == 0);

    GPIO_PORTA_AFSEL_R |= 0x80; // Activar funcion alterna de PA7
    GPIO_PORTA_ODR_R &= ~0x80; // PA7 no es open drain
    GPIO_PORTA_PCTL_R |= 0x30000000; // PA7 funcion alterna -> T3CCP1 (PWM)
    GPIO_PORTA_DEN_R |= 0x80; // PA7 digital habilitado
    // -----------------------------------------------------

    /// --------------- CONF DEL TIMER 3, PWM1
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3; // Activar reloj de TIMER 3
    while((SYSCTL_PRTIMER_R && SYSCTL_PRTIMER_R3) == 0); // Esperar reloj de TIMER 3

    TIMER3_CTL_R = 0; // Deshabilitar TMA y TMB de TIMER 3
    TIMER3_CFG_R = 0x00000004; // Seleccionar modo 16 bits para el temporizador
    TIMER3_TBMR_R = 0x0000000A; // TBAMS = 0x1, TBCMR = 0x0, TBMR = 0x2

    //TIMER3_CTL_R |= 0x00004000; // PWM invertido



    TIMER3_CTL_R |= 0x100; // Habilitar TB, de TIMER3
    while(1);
}
