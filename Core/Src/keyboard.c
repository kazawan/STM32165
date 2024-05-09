#include "keyboard.h"


void KEY_INIT(int num, KEY_typedef *key_typedef, KEY_MAP *key_map)
{
    uint8_t i;
    for (i = 0; i < num; i++)
    {
        key_typedef[i].key_value = &key_map[i].key;
        key_typedef[i].KEY_STATE = idle;
        key_typedef[i].time = 0;
        key_typedef[i].debounce_time = 30;
        key_typedef[i].buffer_index = -1;
    }
}

void key_process(int i ,int state,KEY_typedef *key_typedef)
{
    if(state){
        if(key_typedef[i].KEY_STATE == idle)
        {
            key_typedef[i].KEY_STATE = press;
        }
        else if(key_typedef[i].KEY_STATE == press)
        {
            key_typedef[i].KEY_STATE = release;
            // 按键按下 回调函数
            key_handler(i);
        }
    }else{
        if(key_typedef[i].KEY_STATE == release)
        {
            key_typedef[i].KEY_STATE = idle;
            // 按键释放 回调函数
            key_handler_release(i);
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



