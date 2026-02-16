
#include <stdint.h>

#define GPIO_PORTN_DATA_R       (*((volatile unsigned long *)0x4006400C))
#define GPIO_PORTN_DIR_R        (*((volatile unsigned long *)0x40064400))
#define GPIO_PORTN_DEN_R        (*((volatile unsigned long *)0x4006451C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
#define SYSCTL_RCGC2_GPION      0x00001000


void delay(uint32_t n)
{
    while(n--);
}

void main(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPION;

    while((SYSCTL_PRGPIO_R & 0x1000) == 0){};

    GPIO_PORTN_DIR_R |= 0x0F;
    GPIO_PORTN_DEN_R |= 0x0F;

    GPIO_PORTN_DATA_R = 0x02;

    while(1)
    {
        GPIO_PORTN_DATA_R ^= 0x03;
        delay(1000000);
    }
}
