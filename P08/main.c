/*
 * Este código hace uso del ADC0 para que por medio de las entradas
 * PE4 y PE5.

 * El ADC0 emplea el secuenciador 2 (SS2) para el control de las conversiones.
 * Se dispara la conversión por software y se atiende la interrupción correspondiente.
 */

/*
 * Son dos modulos ADC, cada uno con capacidad
 * para tomar hasta 20 muestras por canal (GPIO analógico).
 * El ADC es de 12 bits, es decir puede hacer conversiones
 * desde 0 hasta 4095 (2^12 = 4096) valores.
 * El valor de voltaje máximo de conversión es 3.3v, es decir,
 * si se lee 4095 sería equivalente a 3.3v.
 */

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "tm4c1294ncpdt.h"

uint32_t x, y;

void intADC0SS2(void)
{
    // Se lee el primer resultado almacenado en la FIFO
    x = (ADC0_SSFIFO2_R&0xFFF);
    // Se lee el segundo resultado almacenado en la FIFO
    y = (ADC0_SSFIFO2_R&0xFFF);
    // Limpia bandera de interrupción
    ADC0_ISC_R = 0x0004;
    // Inicia conversión del ADC nuevamente
    ADC0_PSSI_R = 0x0004;
}

void initADC0(void)
{
    // Habilita reloj para Puerto E
    SYSCTL_RCGCGPIO_R |= 0x10;

    // Se espera a que el reloj se estabilice
    while((SYSCTL_PRGPIO_R & 0x10) == 0);

    GPIO_PORTE_AHB_DIR_R = 0x00;            // PE5-4 entradas (analógica)
    GPIO_PORTE_AHB_AFSEL_R |= 0x30;         // Habilita función alterna en PE5-4
    GPIO_PORTE_AHB_DEN_R &= ~0x30;          // Deshabilita función digital PE5-4
    GPIO_PORTE_AHB_AMSEL_R |= 0x30;         // Habilita función analógica de PE5-4

    SYSCTL_RCGCADC_R |= 0x01;               // Habilita reloj para ADC0

    while((SYSCTL_PRADC_R & 0x01) == 0);    // Se espera a que el reloj se estabilice

    ADC0_PC_R = 0x01;                       // Configura para 125Ksamp/s (p.1159)
    ADC0_SSPRI_R = 0x0123;                  // SS3 con la mas alta prioridad

    ADC0_ACTSS_R &= ~0x0004;                // Deshabilita SS2 antes de cambiar configuración de registros

    ADC0_EMUX_R = 0x0000;                   // Se configura SS2 para disparar muestreo por software

    ADC0_SAC_R = 0x0;                       // Se configura para no tener sobremuestreo por hardware

    ADC0_CTL_R = 0x0;                       // Se configura con referencias internas (default VDDA and GNDA)

    ADC0_SSOP2_R = 0x0000;                  // Se configure para salvar los resultados del ADC en FIFO

    ADC0_SSTSH2_R = 0x000;                  // Se configure el ADC para un periodo de 4  S&H (default)

    ADC0_SSMUX2_R = 0x0089;                 // Se configura entrada para muestra AIN9 y muestra=AIN8
    ADC0_SSEMUX2_R &= ~0x0011;              // Canales del SS2 para una muestra y 2�muestra en AIN(15:0)
    ADC0_SSCTL2_R = 0x0060;                 // SI: AIN, Habilitación de INR2; No: muestra diferencial
    ADC0_IM_R &= ~0x0004;                   // Deshabilita interrupción
    ADC0_ACTSS_R |= 0x0004;                 // Habilita SS2

    SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR;  // Encender PLL
    while((SYSCTL_PLLSTAT_R&0x01)==0);            // Espera a que el PLL fije su frecuencia
    SYSCTL_PLLFREQ0_R &= ~SYSCTL_PLLFREQ0_PLLPWR; // Apagar PLL

    ADC0_IM_R |= 0x0004;                    // Deshabilita interrupción SS2
    ADC0_ISC_R = 0x0004;                    // Se recomienda Limpia la bandera RIS del ADC0
    NVIC_EN0_R |= 1<<16;
    ADC0_PSSI_R = 0x0004;     
}

void main(void)
{
    initADC0();

    for(;;);
}
