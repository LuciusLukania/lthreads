#include "lthread_list.h"
#include <unistd.h>

static lthread_t* lt_head = NULL;

void lthread_list_add(lthread_t* lt)
{
    if (!lt_head) {
        lt_head = lt;
    } else {
        lt_head->next = lt;
    }
}

lthread_t* lthread_list_get_head(void)
{
    return lt_head;
}
