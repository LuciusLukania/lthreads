#include "lthread_scheluder.h"
#include "lthread.h"
#include "lthread_list.h"
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

static void sched_tick(int);
static lthread_t* active = NULL;

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

lthread_t* lthread_sheluder_get_active()
{
    return active;
}

static void sched_print_threads()
{
    lthread_t* curr = lthread_list_get_head();
    while (curr) {
        printf("ltid: %d state: %d | ", curr->ltid, curr->state);
        curr = curr->next;
    }
    printf("\n");
}

static void sched_tick(int sig)
{
    if (!active) {
        active = lthread_list_get_head();

        if (!active) {
            DBG(printf("No threads in list\n"));
            return;
        }
    }

    lthread_t* prev = active;

    if (active->next) {
        active = active->next;
    } else {
        active = lthread_list_get_head();
    }

    if (!active) {
        DBG(printf("No threads in list\n"));
        return;
    }

    if (prev->state == LTHREAD_STATE_EXITING) {
        lthread_list_del(prev);
        prev->destroy_handler(prev);
        prev = NULL;
    } else {
        prev->state = LTHREAD_STATE_IDLE;
    }

    active->state = LTHREAD_STATE_RUNNING;

    DBG(sched_print_threads());

    if (prev) {
        swapcontext(prev->context, active->context);
    } else {
        setcontext(active->context);
    }
}
