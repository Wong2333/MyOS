#include "bitmap.h"     //不仅是为了通过一致性检查，位图的数据结构struct bitmap也在这里面
#include "stdint.h"     
#include "string.h"     //里面包含了内存初始化函数，memset
#include "print.h"
#include "interrupt.h"
#include "debug.h"      //ASSERT

void bitmap_init(struct bitmap* btmp) {
   memset(btmp->bits, 0, btmp->btmp_bytes_len);   
}

bool bitmap_scan_test(struct bitmap* btmp, uint32_t bit_idx){
    uint32_t byte_idx = bit_idx / 8;
    uint32_t bit_odd = bit_idx % 8;
    return btmp->bits[byte_idx] & (BITMAP_MASK << bit_odd);
}

int bitmap_scan(struct bitmap* bitmap, uint32_t cnt){
    if(cnt == 0) return -1;
    uint32_t num = 0;
    uint32_t idx = 0;
    while(idx + num < bitmap->btmp_bytes_len * 8){
        if(bitmap_scan_test(bitmap,idx + num) == 0){
            if(++num == cnt) return idx;
        }
        else{
            if(num > 0){
                idx += num;
                num = 0;
            }
            idx++;
        }
    }
    return -1;
}

void bitmap_set(struct bitmap* btmp, uint32_t bit_idx, int8_t value) {
   ASSERT((value == 0) || (value == 1));
   uint32_t byte_idx = bit_idx / 8;    //确定要设置的位所在字节的偏移
   uint32_t bit_odd  = bit_idx % 8;    //确定要设置的位在某个字节中的偏移

/* 一般都会用个0x1这样的数对字节中的位操作,
 * 将1任意移动后再取反,或者先取反再移位,可用来对位置0操作。*/
   if (value) {		      // 如果value为1
      btmp->bits[byte_idx] |= (BITMAP_MASK << bit_odd);
   } else {		      // 若为0
      btmp->bits[byte_idx] &= ~(BITMAP_MASK << bit_odd);
   }
}
