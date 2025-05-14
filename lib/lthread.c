#include "lthread.h"
#include "lthread_list.h"
#include "lthread_scheluder.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <sys/ucontext.h>
/**
 * @brief Initialise lthread struct
 *
 * @return NULL if fail lthread pointer if success.
 */
static lthread_t* create();

static void destroy(lthread_t* lt)
{
    if (!lt) {
        return;
    }
    if (lt->stack) {
        free(lt->stack);
    }

    if (lt->context) {
        free(lt->context);
    }

    free(lt);
}

static lthread_t* create()
{
    lthread_t* lt = (lthread_t*)malloc(sizeof(lthread_t));
    if (!lt) {
        return NULL;
    }

    lt->stack = (uint8_t*)malloc(sizeof(uint8_t) * LTHREAD_STACK_SIZE);
    if (!lt->stack) {
        destroy(lt);
        return NULL;
    }

    lt->context = (ucontext_t*)malloc(sizeof(ucontext_t));
    if (!lt->context) {
        destroy(lt);
        return NULL;
    }
    return lt;
}

// FIXME: int will overflow
int lthread_create(void (*func)(void))
{
    static uint64_t lthread_cnt = 0;

    lthread_t* lt = create();
    if (!lt) {
        return -1;
    }

    if (getcontext(lt->context) == -1) {
        destroy(lt);
        return -1;
    }

    lt->context->uc_stack.ss_sp = lt->stack;
    lt->context->uc_stack.ss_size = LTHREAD_STACK_SIZE;
    lt->context->uc_link = NULL;
    makecontext(lt->context, func, 0);

    lt->next = NULL;
    lt->prev = NULL;

    lt->state = LTHREAD_STATE_IDLE;
    lt->destroy_handler = &destroy;

    lthread_list_add(lt);

    lt->ltid = lthread_cnt++;

    return lt->ltid;
}

int lthread_start(void)
{
    lthread_scheluder_start();
    return 0;
}

int lthread_exit(void)
{

    lthread_t* lt = lthread_sheluder_get_active();
    lt->state = LTHREAD_STATE_EXITING;
    DBG(printf("ltid: %d exiting\n", lt->ltid));

    while (1) {
        // wait for exit
    }
    return 0;
}
//
void lthread_sleep(double sec)
{
    clock_t start = clock();
    clock_t current = start;

    while (((double)(current - start) / CLOCKS_PER_SEC) < sec) {
        current = clock();
    }
}
