#include <signal.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
jmp_buf env;
//信号处理函数
void recvSignal(int sig)
{
printf("received signal %d !!!\n",sig);
        // longjmp(env,1);
        siglongjmp(env, 1);
}
int main(int argc,char** argv)
{

    for(int i = 0; i < 2; i++)
    {
            //保存一下上下文
        // int r = setjmp(env);
        int r = sigsetjmp(env, 1);
        if(  r  == 0)
        {
            //初次执行 ，那么可以执行 可能会发生错误的代码
            //给信号注册一个处理函数
            signal(SIGSEGV, recvSignal);
            printf("excute this code!!\n");
               int* s = 0;
                (*s) = 1;
        }
        else
        {
                //是由longjmp 跳转回来的
                printf("jump this code !!\n");
        }
        sleep(5);
    }

    while(1)
    {
        sleep(1);
        printf("sleep 1 \n");
    }
    return 0;
}