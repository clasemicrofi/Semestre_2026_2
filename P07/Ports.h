
#ifndef PORTS_H_
#define PORTS_H_

#include <Ports.h>
#include <stdint.h>

extern uint8_t var_glob;

#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile uint32_t *)0x400FEA08))

#define GPIO_PORTN_DIR_R        (*((volatile uint32_t *)0x40064400))
#define GPIO_PORTN_DEN_R        (*((volatile uint32_t *)0x4006451C))
#define GPIO_PORTN_DATA_R       (*((volatile uint32_t *)0x4006400C))

#define SYSCTL_RCGC2_CLK_N      0x00001000

void blink();


#endif /* PORTS_H_ */
