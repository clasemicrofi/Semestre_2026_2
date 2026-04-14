
#include <stdint.h>
#include <Ports.h>

void delay(uint32_t n)
{
    while(n--);
}

void blink(void)
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_CLK_N;

    while((SYSCTL_PRGPIO_R & 0x1000) == 0){};

    GPIO_PORTN_DIR_R |= 0x03;
    GPIO_PORTN_DEN_R |= 0x03;

    GPIO_PORTN_DATA_R = 0x02;

    uint8_t n = 8;
    while(n--)
    {
        GPIO_PORTN_DATA_R ^= 0x03;
        delay(1000000);
    }
}
