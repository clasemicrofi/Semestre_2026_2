/*
 * Desarrollar un código en C que realice lo siguiente:
 *
 * A través de un botón conectado a PD3 se hace parpadear el led
 * PL2 cuando ocurre una interrupción (Prioridad alta)
 *
 * A través de un botón conectado a PC7 se hace parpadear el led
 * PL1 cuando ocurre una interrupción (Prioridad media)
 *
  * A través de un botón conectado a PB2 se hace parpadear el led
 * PL0 cuando ocurre una interrupción (Prioridad baja)
 * */
#include <stdint.h>

#define SYSCTL_RCGCGPIO_R1      0x00000002  // GPIO Port B Run Mode Clock
#define SYSCTL_RCGCGPIO_R10     0x00000400  // GPIO Port L Run Mode Clock

#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile uint32_t *)0x400FEA08))

#define GPIO_PORTB_DIR_R        (*((volatile uint32_t *)0x40059400))
#define GPIO_PORTB_DEN_R        (*((volatile uint32_t *)0x4005951C))
#define GPIO_PORTB_PUR_R        (*((volatile uint32_t *)0x40059510))

#define GPIO_PORTB_IS_R         (*((volatile uint32_t *)0x40059404))
#define GPIO_PORTB_IBE_R        (*((volatile uint32_t *)0x40059408))
#define GPIO_PORTB_IEV_R        (*((volatile uint32_t *)0x4005940C))
#define GPIO_PORTB_IM_R         (*((volatile uint32_t *)0x40059410))
#define GPIO_PORTB_ICR_R        (*((volatile uint32_t *)0x4005941C))

#define GPIO_PORTL_DIR_R        (*((volatile uint32_t *)0x40062400))
#define GPIO_PORTL_DEN_R        (*((volatile uint32_t *)0x4006251C))
#define GPIO_PORTL_DATA_R       (*((volatile uint32_t *)0x400623FC))

#define NVIC_EN0_R              (*((volatile uint32_t *)0xE000E100))

void interrupt_1(void)
{
    GPIO_PORTB_ICR_R = 0x00000004;
}

void main(void)
{
    // Activar PB, PC, PD, PL
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1; // Activar reloj de PB

    while((SYSCTL_PRGPIO_R & 0x00000002) == 0){}// Esperar reloj listo de PB

    GPIO_PORTB_DIR_R = (GPIO_PORTB_DIR_R & ~0x00000004); // Dir PB2 = 0 = input
    GPIO_PORTB_DEN_R = (GPIO_PORTB_DEN_R | 0x00000004); // Hab. PB2
    GPIO_PORTB_PUR_R = 0x00000004;

    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R10; // Activar reloj de PL
    while((SYSCTL_PRGPIO_R & 0x00000400) == 0){}// Esperar reloj listo de PL

    GPIO_PORTL_DIR_R = (GPIO_PORTL_DIR_R | 0x00000007); // PL[2:0] = 1 = output
    GPIO_PORTL_DEN_R = (GPIO_PORTL_DEN_R | 0x00000007); // Hab. PL[2:0]

    GPIO_PORTL_DATA_R = 0x00000007;

    GPIO_PORTB_IS_R = ~0x00000004;
    GPIO_PORTB_IBE_R = 0x00000000;
    GPIO_PORTB_IEV_R = ~0x00000004;
    GPIO_PORTB_ICR_R = 0x00000004;
    GPIO_PORTB_IM_R = 0x00000004;

    NVIC_EN0_R = 0x00000002;


    while(1);
}
