#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <unistd.h>

#define UCTX_LEN 2
#define INT 500000

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

static ucontext_t uctx[UCTX_LEN];
static ucontext_t uctx_main;
// start
// exit
// kill

static void func1()
{
    while (1) {
        printf("func1\n");
        usleep(100000);
    }
}

static void func2()
{
    while (1) {
        printf("func2\n");
        usleep(100000);
    }
}

static char stack[UCTX_LEN][65536] = { 0 };
static void (*func[UCTX_LEN])() = {
    &func1,
    &func2
};

void sig_clb(int i)
{
    // 0 1
    // 1 2
    // 2 0
    static int active = 0;
    int prev = active;

    active = (active + 1) % UCTX_LEN;

    printf("From %d to %d\n", prev, active);
    // return;

    int ret = swapcontext(&uctx[prev], &uctx[active]);
    if (ret == -1)
        handle_error("swapcontext");

    // ualarm(100000, 100000);
}

int main(void)
{
    signal(SIGALRM, &sig_clb);

    for (int i = 0; i < UCTX_LEN; i++) {
        getcontext(&uctx[i]);
        uctx[i].uc_stack.ss_sp = stack[i];
        uctx[i].uc_stack.ss_size = sizeof(stack[i]);
        uctx[i].uc_link = &uctx_main;
        makecontext(&uctx[i], func[i], 0);
    }
    ualarm(INT, INT);
    // alarm(1);
    setcontext(&uctx[0]);
    while (1) {
    }
}
