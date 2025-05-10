#include "lthread.h"

/**
 * @brief Initialise lthread struct
 *
 * @return NULL if fail lthread pointer if success.
 */
static lthread_t* init();

static void deinit(lthread_t* lt)
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

    lt = NULL;
}

static lthread_t* init()
{
    lthread_t* lt = (lthread_t*)malloc(sizeof(lthread_t));
    if (!lt) {
        return NULL;
    }

    lt->stack = (uint8_t*)malloc(sizeof(uint8_t) * LTHREAD_STACK_SIZE);
    if (!lt->stack) {
        deinit(lt);
        return NULL;
    }

    lt->context = (ucontext_t*)malloc(sizeof(ucontext_t));
    if (!lt->context) {
        deinit(lt);
        return NULL;
    }
    return lt;
}

int lthread_create(void (*func)(void))
{
    lthread_t* lt = init();
    if (!lt) {
        return -1;
    }

    if (getcontext(lt->context) == -1) {
        deinit(lt);
        return -1;
    }

    lt->context->uc_stack.ss_sp = lt->stack;
    lt->context->uc_stack.ss_size = LTHREAD_STACK_SIZE;
    lt->context->uc_link = NULL;
    makecontext(lt->context, func, 0);
    return 0;
}
