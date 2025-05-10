#include <stdint.h>
#include <stdlib.h>
#include <ucontext.h>

#define LTHREAD_STACK_SIZE 65536

typedef enum {
    LTHREAD_STATE_IDLE,
    LTHREAD_STATE_RUNNING,
    LTHREAD_STATE_STOP,
    LTHREAD_STATE_EXIT
} ltread_state_t;

typedef struct {
    int ltid;
    ltread_state_t state;
    ucontext_t* context;
    uint8_t* stack;
} lthread_t;

/**
 * @brief Create lthread
 * Internaly it initialise stack, context, asigns ltid and add it to scheluder thread list.
 *
 * @param func lthread function
 * @return thread id, if negative it means failed
 */
int lthread_create(void (*func)(void));

/**
 * @brief Start lthread
 *
 * @param ltid Id of ltread
 * @return Status, if negative - failed
 */
int lthread_start(int ltid);

int lthread_exit();
int lthread_kill();
