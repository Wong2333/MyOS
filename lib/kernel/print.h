#ifndef __LIB_KERNEL_PRINT_H
#define __LIB_KERNEL_PRINT_H
#include "../stdint.h"
void put_char(uint8_t ch);
void put_str(char* messags);
void put_int(uint32_t num);	        // 以16进制打印
void set_cursor(uint32_t cursor_pos);

#endif