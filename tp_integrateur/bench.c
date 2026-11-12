/* Micro-benchmark : mêmes opérations, deux implémentations (voir Makefile).
   Mesure avec timespec_get (C11, <time.h>). */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "queue.h"

#ifndef IMPL_NAME
#define IMPL_NAME "?"
#endif

static double now_ms(void)
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (double)ts.tv_sec * 1e3 + (double)ts.tv_nsec / 1e6;
}

int main(int argc, char **argv)
{
    long n = (argc > 1) ? atol(argv[1]) : 5000000L;
    Item x;

    Stack *s = stack_create();
    double t0 = now_ms();
    for (long i = 0; i < n; i++) stack_push(s, (Item)i);
    while (!stack_is_empty(s)) stack_pop(s, &x);
    double t_stack = now_ms() - t0;
    stack_destroy(s);

    Queue *q = queue_create();
    t0 = now_ms();
    for (long i = 0; i < n; i++) queue_enqueue(q, (Item)i);
    while (!queue_is_empty(q)) queue_dequeue(q, &x);
    double t_queue = now_ms() - t0;
    queue_destroy(q);

    printf("%-6s  n=%ld  pile: %8.1f ms   file: %8.1f ms\n", IMPL_NAME, n, t_stack, t_queue);
    return EXIT_SUCCESS;
}
