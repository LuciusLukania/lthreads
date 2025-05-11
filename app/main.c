#include "lthread.h"
#include <stdio.h>
#include <unistd.h>

static void func1()
{
    while (1) {
        printf("%s\n", __FUNCTION__);
        sleep(2);
    }
}

static void func2()
{
    while (1) {
        printf("%s\n", __FUNCTION__);
        // FIXME: sleep blocks entire process, create lthread_sleep to calculate time baed on sched tick
        sleep(2);
    }
}

int main(void)
{
    lthread_create(&func1);
    lthread_create(&func2);

    lthread_start();
}
