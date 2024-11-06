#ifndef __LIB_KERNEL_BITMAP_H
#define __LIB_KERNEL_BITMAP_H
#define BITMAP_MASK 1
#include "stdint.h"
#include "global.h"
struct bitmap {                 //这个数据结构就是用来管理整个位图
   uint32_t btmp_bytes_len;     //记录整个位图的大小，字节为单位
   uint8_t* bits;               //用来记录位图的起始地址，我们未来用这个地址遍历位图时，操作单位指定为最小的字节
};

void bitmap_init(struct bitmap* btmp);//初始化位图
bool bitmap_scan_test(struct bitmap* btmp, uint32_t bit_idx);//查看位图某一位是否为1
int bitmap_scan(struct bitmap* btmp, uint32_t cnt);//寻找连续的cnt个的0，成功就返回偏移量，否则返回-1
void bitmap_set(struct bitmap* btmp, uint32_t bit_idx, int8_t value);//将位图某一位设定为1或0，传入参数是指向位图的指针与这一位的偏移，与想要的值


#endif

