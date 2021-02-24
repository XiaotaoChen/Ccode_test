/*
** file name CException.h
*/
#ifndef _CEXCEPTION_H_
#define _CEXCEPTION_H_
#include <setjmp.h>
#include <stdlib.h>
#include <stdarg.h>
#include <execinfo.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <string.h>
typedef struct Except_frame
{
    jmp_buf env;
    int flag;
    void clear()
    {
       flag = 0;
       bzero(env,sizeof(env));
    }
    bool isDef()
    {
       return flag;
    }
    Except_frame()
    {
      clear();
    }
}Except_frame;
extern Except_frame* except_stack;
extern void recvSignal(int sig);
Except_frame* except_stack = new Except_frame;

void recvSignal(int sig)
{
    printf("received signal %d !!!\n",sig);
    siglongjmp(except_stack->env,1);
}
#define TRY \
    except_stack->flag = sigsetjmp(except_stack->env,1);\
    if(!except_stack->isDef()) \
    { \
      signal(SIGSEGV,recvSignal); \
      printf("start use TRY\n");
#define END_TRY \
    }\
    else\
    {\
      except_stack->clear();\
    }\
    printf("stop use TRY\n");
#define RETURN_NULL \
    } \
    else \
    { \
      except_stack->clear();\
    }\
    return NULL;
#define EXIT_ZERO \
    }\
    else \
    { \
      except_stack->clear();\
    }\
    exit(0);
#endif