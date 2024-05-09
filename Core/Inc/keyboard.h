#ifndef keyboard_H
#define keyboard_H
#include "stm32f1xx_hal.h"
#include "main.h"

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
    unsigned long long time;
    unsigned long debounce_time;
    int buffer_index;
}KEY_typedef;


void KEY_INIT(int num, KEY_typedef *key_typedef, KEY_MAP *key_map);
void key_process(int i ,int state,KEY_typedef *key_typedef);
_weak_ void key_handler(int i);
_weak_ void key_handler_release(int i);
int find_buff_emtpy_index(uint8_t *sendBuffer, int key_buffer_size);
void key_buffer_insert(int buffer_index,int i,KEY_MAP *key_value,uint8_t *sendBuffer);
void remove_buff(int buff_index,uint8_t *sendBuffer);
_weak_ void key_handler(int i);
_weak_ void key_handler_release(int i);


#endif
