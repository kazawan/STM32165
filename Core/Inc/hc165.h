#ifndef HC165_H
#define HC165_H
#include "stm32f1xx_hal.h"
#include "main.h"




void LATCH_DOWN(void);
void LATCH_UP(void);
void clk(void);
void delay_us(uint32_t us);
uint8_t read_HC165();
void read_HC165s(uint8_t *data, uint8_t num);



#endif