#ifndef HC165_DRIVER_H
#define HC165_DRIVER_H
#include "stm32f1xx_hal.h"
#include "gpio.h"



typedef struct
{
    uint16_t LATCH;
    uint16_t CLK;
    uint16_t DATA;
    GPIO_TypeDef *LATCH_PORT;
    GPIO_TypeDef *CLK_PORT;
    GPIO_TypeDef *DATA_PORT;
    unsigned int keys_number_total;
}HC165_typedef;



void HC165_INIT(HC165_typedef *hc165_typedef);
void latch_down(HC165_typedef *hc165_typedef);
void latch_up(HC165_typedef *hc165_typedef);
void clk_down(HC165_typedef *hc165_typedef);
void clk_up(HC165_typedef *hc165_typedef);
int HC165_read_one_bit(HC165_typedef *hc165_typedef);
void HC165_read(HC165_typedef *hc165_typedef);
_weak_ void HC165_data_handler(int i,int key_state);


#endif