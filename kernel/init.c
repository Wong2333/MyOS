#include "init.h"
#include "print.h"
#include "interrupt.h"
#include "timer.h"
#include "memory.h"
#include "thread.h"
#include "keyboard.h"
#include "tss.h"
#include "ide.h"
/*负责初始化所有模块 */
void init_all() {
   put_str("init_all\n");
   idt_init();   //初始化中断
   
   mem_init();	  // 初始化内存管理系统
   thread_init();
   timer_init();
   console_init();
   keyboard_init();
   tss_init();
   syscall_init();   // 初始化系统调用
   ide_init();	     // 初始化硬盘
}
