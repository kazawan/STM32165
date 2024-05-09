#include "hc165_driver.h"


void HC165_INIT(HC165_typedef *hc165_typedef){

}

void latch_down(HC165_typedef *hc165_typedef){
    HAL_GPIO_WritePin(hc165_typedef->LATCH_PORT, hc165_typedef->LATCH, GPIO_PIN_RESET);
}

void latch_up(HC165_typedef *hc165_typedef){
    HAL_GPIO_WritePin(hc165_typedef->LATCH_PORT, hc165_typedef->LATCH, GPIO_PIN_SET);
}

void clk_down(HC165_typedef *hc165_typedef){
    HAL_GPIO_WritePin(hc165_typedef->CLK_PORT, hc165_typedef->CLK, GPIO_PIN_RESET);
}

void clk_up(HC165_typedef *hc165_typedef){
    HAL_GPIO_WritePin(hc165_typedef->CLK_PORT, hc165_typedef->CLK, GPIO_PIN_SET);
}



int HC165_read_one_bit(HC165_typedef *hc165_typedef){
    int bit = 0;
    clk_down(hc165_typedef);
    bit = HAL_GPIO_ReadPin(hc165_typedef->DATA_PORT, hc165_typedef->DATA);
    clk_up(hc165_typedef);
    return bit;
}

void HC165_read(HC165_typedef *hc165_typedef){
    int i = 0;
    
    latch_up(hc165_typedef);
    for(i = 0; i < hc165_typedef->keys_number_total; i++){
        int key_state = HC165_read_one_bit(hc165_typedef);
        HC165_data_handler(i,key_state);
    }
    latch_down(hc165_typedef);
}


