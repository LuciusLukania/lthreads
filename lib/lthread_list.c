#include "lthread_list.h"
#include <unistd.h>

static lthread_t* lt_head = NULL;
static lthread_t* lt_tail = NULL;

// TODO: make cyclic list
void lthread_list_add(lthread_t* lt)
{
    lt->next = lt_head;
    lt->prev = NULL;

    if (lt_head) {

        lt_head->prev = lt;
    }

    lt_head = lt;
}

void lthread_list_del(lthread_t* lt)
{
    lthread_t* next;
    lthread_t* prev;

    next = lt->next;
    prev = lt->prev;

    if (next) {
        next->prev = prev;
    }
    if (prev) {
        prev->next = next;
    } else {
        lt_head = lt->next;
    }
}

lthread_t* lthread_list_get_head(void)
{
    return lt_head;
}
