#include "lthread_scheluder.h"
#include "lthread.h"
#include "lthread_list.h"
#include <signal.h>
#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

static void sched_tick(int);

int lthread_scheluder_start(void)
{
    lthread_t* curr = lthread_list_get_head();

    if (!curr) {
        return -1;
    }

    printf("Created lthreads\n");
    while (curr) {
        printf("ltid: %d\n", curr->ltid);
        curr = curr->next;
    }

    signal(SIGALRM, &sched_tick);
    ualarm(LTHREAD_SCHED_INTERVAL_US, LTHREAD_SCHED_INTERVAL_US);
    setcontext(lthread_list_get_head()->context);

    return 0;
}

static void sched_tick(int sig)
{
    static lthread_t* active = NULL;

    if (!active) {
        active = lthread_list_get_head();
    }

    lthread_t* prev = active;

    if (active->next) {
        active = active->next;
    } else {
        active = lthread_list_get_head();
    }

    // FIXME: handle error
    // printf("Prev %d, Active %d\n", prev->ltid, active->ltid);
    swapcontext(prev->context, active->context);
}
