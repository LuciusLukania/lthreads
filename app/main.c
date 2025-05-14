#include "lthread.h"
#include <stdio.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <unistd.h>

void func1()
{
    while (1) {
        printf("%s\n", __FUNCTION__);
        lthread_sleep(2);
        lthread_exit();
    }
}

void func2()
{
    while (1) {
        printf("%s\n", __FUNCTION__);
        lthread_sleep(1);
        lthread_exit();
    }
}

void func3()
{
    ucontext_t temp;
    while (1) {
        printf("%s\n", __FUNCTION__);
        lthread_sleep(3);
        lthread_exit();
    }
}

int main(void)
{
    lthread_create(&func1);
    lthread_create(&func2);
    lthread_create(&func3);

    lthread_start();
}
