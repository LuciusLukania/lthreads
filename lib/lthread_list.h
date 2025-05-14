#ifndef H_LTHREAD_LIST
#define H_LTHREAD_LIST

#include "lthread.h"

void lthread_list_add(lthread_t *lt);
void lthread_list_del(lthread_t *lt);

lthread_t *lthread_list_get_head(void);

#endif // !H_LTHREAD_LIST
