#include "print.h"
#include "init.h"
#include "thread.h"
#include "interrupt.h"
#include "console.h"

void k_thread_a(void*);
void k_thread_b(void*);
void k_thread_c(void*);

int main(void) {
   put_str("I am kernel\n");
   init_all();

   // thread_start("k_thread_a", 1, k_thread_a, "argA");
   // thread_start("k_thread_b", 1, k_thread_b, "argB");
   // thread_start("k_thread_c", 1, k_thread_c, "argC");
   intr_enable();
   int i = 0;
   while(1);// {
   //    console_put_str("argX");
   //    // console_put_int(i);
   //    // console_put_str(" ");
   //    // i++;
   // };
   return 0;
}

/* 在线程中运行的函数 */
void k_thread_a(void* arg) {     
/* 用void*来通用表示参数,被调用的函数知道自己需要什么类型的参数,自己转换再用 */
   char* para = arg;
   int i = 0;
   while(1) {
      console_put_str(para);
      // console_put_int(i++);
      // console_put_str(" ");
   }
}

/* 在线程中运行的函数 */
void k_thread_b(void* arg) {     
/* 用void*来通用表示参数,被调用的函数知道自己需要什么类型的参数,自己转换再用 */
   char* para = arg;
   int i = 0;
   while(1) {
      console_put_str(para);
      // console_put_int(i++);
      // console_put_str(" ");
   }
}

/* 在线程中运行的函数 */
void k_thread_c(void* arg) {     
/* 用void*来通用表示参数,被调用的函数知道自己需要什么类型的参数,自己转换再用 */
   char* para = arg;
   int i = 0;
   while(1) {
      console_put_str(para);
      // console_put_int(i++);
      // console_put_str(" ");
   }
}










