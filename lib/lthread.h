#ifndef H_LTHREAD
#define H_LTHREAD

#include <stdint.h>
#include <stdio.h>
#include <ucontext.h>

#define LTHREAD_STACK_SIZE 65536
#define LTHREAD_SCHED_INTERVAL_US 100000
#define LTHREAD_FUNC_PROLOGE_SIZE 32

#ifdef DEBUG
#define DBG(x) x
#else
#define DBG(x)
#endif

typedef enum {
  LTHREAD_STATE_IDLE,
  LTHREAD_STATE_RUNNING,
  LTHREAD_STATE_EXITING
} ltread_state_t;

typedef struct lthread {
  int ltid;
  ltread_state_t state;
  ucontext_t *context;
  uint8_t *stack;
  struct lthread *next;
  struct lthread *prev;
  void (*destroy_handler)(struct lthread *);
} lthread_t;

/**
 * @brief Create lthread
 * Internaly it initialise stack, context, asigns ltid and add it to scheluder
 * thread list.
 *
 * @param func lthread function
 * @return thread id, if negative it means failed
 */
int lthread_create(void (*func)(void));

/**
 * @brief Start lthread scheluder
 *
 * @return Status, if negative - failed
 */
int lthread_start(void);
/**
 * @brief Sleep for seconds.
 *
 * @param sec seconds.
 */
void lthread_sleep(double sec);

/**
 * @brief Exit thread.
 *
 * Invoked from thread fn, removes it from sheduler.
 *
 * @return 0 if success -1 if fail.
 */
int lthread_exit(void);
int lthread_kill(void);

#endif // !H_LTHREAD
