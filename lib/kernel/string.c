#include "string.h"
#include "global.h"
#include "debug.h"  //定义了ASSERT

#define NN(var) ASSERT(var != NULL) //not null

//将dst起始的size个字节置为value，这个函数最常用的用法就是来初始化一块内存区域，也就是置为ASCII码为0
void memset(void* dst_, uint8_t value, uint32_t size) {
    NN(dst_);
    uint8_t* dst = dst_;
    while (size--)
    {
        *dst++ = value;
    }
}

void memcpy(void* dst_, const void* src_, uint32_t size){
    NN(dst_);
    NN(src_);
    uint8_t* dst = dst_;
    uint8_t* src = src_;
    while(size--){
        *dst++ = *src++;
    }
}

int memcmp(const void* a_, const void* b_, uint32_t size){
    NN(a_);
    NN(b_);
    const uint8_t* a = a_,*b = b_;
    while(size--){
        if(*a != *b) return *a > *b ? 1 : -1;
        a++;
        b++;
    }
    return 0;
}

char* strcpy(char* dst_, const char* src_){
    NN(dst_);
    NN(src_);
    char* ret = dst_;
    while(*dst_++ = *src_++);
    return ret;
}

uint32_t strlen(const char* str){
    NN(str);
    const char* p = str;
    while(*p++);
    return p - str -1;
}

int8_t strcmp (const char* a, const char* b){
    NN(a);
    NN(b);
    while(*a != NULL && *a == *b){
        a++;
        b++;
    }
    return *a < *b ? -1 : *a > *b;  
}

char* strchr(const char* str, const uint8_t ch) {
    NN(str);
    while (*str != 0) {
        if (*str == ch) {
	        return (char*)str;	    // 需要强制转化成和返回值类型一样,否则编译器会报const属性丢失,下同.
        }
        str++;
    }
    return NULL;
}

char* strrchr(const char* str, const uint8_t ch) {
    NN(str);
    const char* last_char = NULL;
    /* 从头到尾遍历一次,若存在ch字符,last_char总是该字符最后一次出现在串中的地址(不是下标,是地址)*/
    while (*str != 0) {
        if (*str == ch) {
	        last_char = str;
        }
        str++;
    }
    return (char*)last_char;
}

char* strcat(char* dst_, const char* src_) {
    NN(dst_);
    NN(src_);
    char* str = dst_;
    while (*str++);
    --str;                       // 别看错了，--str是独立的一句，并不是while的循环体。这一句是为了让str指向dst_的最后一个非0字符
    while((*str++ = *src_++));	//1、*str=*src  2、判断*str     3、str++与src++，这一步不依赖2
    return dst_;
}

/* 在字符串str中查找指定字符ch出现的次数 */
uint32_t strchrs(const char* str, uint8_t ch) {
    NN(str);
    uint32_t ch_cnt = 0;
    const char* p = str;
    while(*p != 0) {
        if (*p == ch) {
            ch_cnt++;
        }
        p++;
    }
    return ch_cnt;
}


