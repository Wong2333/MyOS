#include "print.h"
#include "init.h"
#include "fork.h"
#include "stdio.h"
#include "syscall.h"
#include "timer.h"
void init(void);

int main(void)
{
    put_str("I am kernel\n");
    init_all();
    while (1)
        ;
    return 0;
}

/* init进程 */
void init(void)
{
    uint64_t i = 999;
    while(i--){
        printf("this is sleep\n");
    }
    uint32_t ret_pid = fork();
    if (ret_pid)
    {
        while(1){       
            printf("i am father, my pid is %d, child pid is %d\n", getpid(), ret_pid);      
        }
        
    }
    else
    {
        while(1){
            printf("i am child, my pid is %d, ret pid is %d\n", getpid(), ret_pid);
        }
    }
    while (1)
        ;
}

