#include "hc165.h"

void delay_us(uint32_t us)
{
    uint32_t start = HAL_GetTick(); // 获取当前时间（毫秒）
    while ((HAL_GetTick() - start) < us)
        ;
}


/**
 * @brief LATCH 引脚拉低
*/
void LATCH_DOWN(void)
{
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_RESET);
}

/**
 * @brief LATCH 引脚拉高
*/
void LATCH_UP(void)
{
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_SET);
}


/**
 * @brief CLK 时钟信号
*/
void clk(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
    // delay_us(2);
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
}


/**
 * @brief CLK 时钟信号 低
*/
void clk_down(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
}

/**
 * @brief CLK 时钟信号 高
*/
void clk_up(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
}


/**
 * @brief 读取 单1组HC165 数据
 * @return uint8_t 读取到的数据
*/
uint8_t read_HC165()
{
    uint8_t i;
    uint8_t data = 0;
    for (i = 0; i < 8; i++)
    {
        // clk();
        data = data << 1;
        clk_down();
        if (HAL_GPIO_ReadPin(DATA_GPIO_Port, DATA_Pin) == GPIO_PIN_SET)
        {
            data++;
        }
        clk_up();
    }
    return data;
}


/**
 * @brief 读取多组HC165 数据
 * @param data 读取到的数据
 * @param num HC165 数量
*/
void read_HC165s(uint8_t *data, uint8_t num)
{
    uint8_t i;
    LATCH_UP();
    for (i = 0; i < num; i++)
    {
        data[i] = read_HC165();
    }
    LATCH_DOWN();

}
