#ifndef KEY_H
#define KEY_H
#include "stm32f1xx_hal.h"
#include "main.h"
#include "usbd_hid.h"
#define _weak_ __attribute__((weak)) // 弱引用
extern USBD_HandleTypeDef hUsbDeviceFS;


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
    int buffer_index;
}KEY_typedef;

void KEY_INIT(int num,KEY_typedef *key_typedef,KEY_MAP *key_map);
void KEY_READ(uint8_t *data, int num, KEY_MAP *key_map,KEY_typedef *KEY_T);
int find_buff_emtpy_index(uint8_t *sendBuffer, int key_buffer_size);
void key_buffer_insert(int buffer_index,int i,KEY_MAP *key_value,uint8_t *sendBuffer);
void remove_buff(int buff_index,uint8_t *sendBuffer);
int is_array_all_zero(uint8_t *arr, int size) ;
_weak_ void key_handler(int i);
_weak_ void key_handler_release(int i);

#endif