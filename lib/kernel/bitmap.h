#ifndef __LIB_KERNEL_BITMAP_H
#define __LIB_KERNEL_BITMAP_H
#define BITMAP_MASK 1
#include "stdint.h"
struct bitmap {                 //这个数据结构就是用来管理整个位图
   uint32_t btmp_bytes_len;     //记录整个位图的大小，字节为单位
   uint8_t* bits;               //用来记录位图的起始地址，我们未来用这个地址遍历位图时，操作单位指定为最小的字节
};


#endif

