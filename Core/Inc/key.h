#ifndef KEY_H
#define KEY_H
#include "stm32f1xx_hal.h"
#include "usbd_cdc_if.h"
#define _weak_ __attribute__((weak)) // 弱引用
typedef struct
{
    char key;
} KEY_MAP;

enum 
{
    idle,
    press,
    release,
}KEY_STATE;

typedef struct
{
    char *key_value;
    int key_index;
    int KEY_STATE;
    int KEY_STATE_LAST;
    unsigned long long time;
    unsigned long debounce_time;
}KEY_typedef;

void KEY_INIT(int num,KEY_typedef *key_typedef,KEY_MAP *key_map);
void KEY_READ(uint8_t *data, int num, KEY_MAP *key_map,KEY_typedef *KEY_T);
_weak_ void key_handler(int i);

#endif