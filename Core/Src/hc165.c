#include "hc165.h"


void delay_us(uint32_t us){
    uint32_t start = HAL_GetTick(); // 获取当前时间（毫秒）
    while ((HAL_GetTick() - start) < us);
}


void LATCH_DOWN(void)
{
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_RESET);
}

void LATCH_UP(void)
{
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_SET);
}

void clk(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
    // delay_us(2);
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
}

uint8_t read_HC165(void)
{
    uint8_t i;
    uint8_t data = 0;
    for (i = 0; i < 8; i++)
    {
        data = data << 1;
        if (HAL_GPIO_ReadPin(DATA_GPIO_Port, DATA_Pin) == GPIO_PIN_SET)
        {
            data++;
        }
        clk();
    }
    return  data;
}

void read_HC165s(uint8_t *data, uint8_t num)
{
    uint8_t i;
    for (i = 0; i < num; i++)
    {
        data[i] = read_HC165();
        LATCH_DOWN();
        LATCH_UP();
    }
}



