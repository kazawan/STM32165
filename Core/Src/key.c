#include "key.h"

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
    }
}



void KEY_READ(uint8_t *data, int num, KEY_MAP *key_map,KEY_typedef *KEY_T)
{

    uint8_t i;
    for (i = 0; i < num; i++)
    {
        if (*data & (1 << i))
        {
            if (KEY_T[i].KEY_STATE == idle)
            {
                KEY_T[i].KEY_STATE = press;
                KEY_T[i].time = HAL_GetTick();
            }
            else if (KEY_T[i].KEY_STATE == press)
            {
                if (HAL_GetTick() - KEY_T[i].time > KEY_T[i].debounce_time)
                {
                    KEY_T[i].KEY_STATE = release;
                    // CDC_Transmit_FS(KEY_T[i].key_value, 1);
                    key_handler(i);

                }
            }
        }else{
            if (KEY_T[i].KEY_STATE == release)
            {
                KEY_T[i].KEY_STATE = idle;  
                CDC_Transmit_FS(KEY_T[i].key_value, 1); 
            }
        }
    }
}


// _weak_ void key_handler(int i)
// {
//     char msg[] = "Hello\n";
//     CDC_Transmit_FS(msg, sizeof(msg));
// }