#include "key.h"
extern keyboardHID;
void KEY_INIT(int num, KEY_typedef *key_typedef, KEY_MAP *key_map)
{
    uint8_t i;
    for (i = 0; i < num; i++)
    {
        key_typedef[i].key_value = &key_map[i].key;
        key_typedef[i].KEY_STATE = idle;
        key_typedef[i].KEY_STATE_LAST = idle;
        key_typedef[i].time = 0;
        key_typedef[i].debounce_time = 20;
        key_typedef[i].buffer_index = -1;
    }
}

void KEY_READ(uint8_t *data, int num, KEY_MAP *key_map, KEY_typedef *KEY_T)
{

    uint8_t i;
    for (i = 0; i < num; i++)
    {
        if (*data & (1 << i))
        {
            if (KEY_T[i].KEY_STATE == idle)
            {
                KEY_T[i].KEY_STATE = press;
                // KEY_T[i].time = HAL_GetTick();
            }
            else if (KEY_T[i].KEY_STATE == press)
            {
                // if (HAL_GetTick() - KEY_T[i].time > KEY_T[i].debounce_time)
                // {
                //     KEY_T[i].KEY_STATE = release;
                //     key_handler(i);
                // }
                KEY_T[i].KEY_STATE = release;
                key_handler(i);
            }
        }
        else
        {
            if (KEY_T[i].KEY_STATE == release)
            {
                KEY_T[i].KEY_STATE = idle;
                // key_handler(i);
                key_handler_release(i);
            }
        }
    }
}

int find_buff_emtpy_index(uint8_t *sendBuffer, int key_buffer_size)
{
    uint8_t i;
    int index = -1;

    for (i = 2; i < key_buffer_size; i++) // 循环buff
    {
        if (index == -1)
        {
            if (sendBuffer[i] == 0) // 如果找到一个位置是空的则返回i
            {
                index = i;
                break;
            }
        }
        else
        {
            index = -1;
        }
    }
    return index;
}

void key_buffer_insert(int buffer_index, int i, KEY_MAP *key_value, uint8_t *sendBuffer)
{
    if (buffer_index != -1)
    {
        sendBuffer[buffer_index] = key_value[i].key;
    }
}

void remove_buff(int buff_index, uint8_t *sendBuffer)
{
    sendBuffer[buff_index] = 0x00;
}

int is_array_all_zero(uint8_t *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != 0)
        {
            return 0; // 如果发现非0元素，返回0
        }
    }
    return 1; // 如果遍历完数组没有发现非0元素，返回1
}

// _weak_ void key_handler(int i)
// {
//     char msg[] = "Hello\n";
//     CDC_Transmit_FS(msg, sizeof(msg));
// }