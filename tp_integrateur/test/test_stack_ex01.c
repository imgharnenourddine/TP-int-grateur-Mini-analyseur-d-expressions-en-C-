/*
 * test_stack.c - Tests de la pile (même test pour stack_array et stack_list).
 * Cas testés : pile vide, pop/top à vide, plus de 100 éléments,
 * ordre LIFO, destruction avec éléments restants.
 */
#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Alloue un entier sur le tas pour pouvoir le mettre dans la pile. */
static int *make_int(int value) {
    int *ptr = malloc(sizeof(*ptr));
    assert(ptr != NULL);
    *ptr = value;
    return ptr;
}

int main(void) {
    Stack *stack = stack_create();
    assert(stack != NULL);
    assert(stack_is_empty(stack));

    /* pop et top sur pile vide doivent retourner une erreur */
    void *value = NULL;
    assert(stack_pop(stack, &value) == DS_ERR_EMPTY);
    assert(stack_top(stack, &value) == DS_ERR_EMPTY);

    /* 150 empilements : force la croissance du tableau */
    for (int i = 0; i < 150; ++i) {
        assert(stack_push(stack, make_int(i)) == DS_OK);
    }
    assert(stack_size(stack) == 150U);
    assert(stack_top(stack, &value) == DS_OK);
    assert(*(int *)value == 149);

    /* dépilement : on doit retrouver 149, 148, ..., 0 (LIFO) */
    for (int i = 149; i >= 0; --i) {
        assert(stack_pop(stack, &value) == DS_OK);
        assert(*(int *)value == i);
        free(value);
    }
    assert(stack_is_empty(stack));
    assert(stack_pop(stack, &value) == DS_ERR_EMPTY);

    /* réutilisation après vidage, puis destruction avec éléments restants */
    for (int i = 0; i < 10; ++i) {
        assert(stack_push(stack, make_int(i)) == DS_OK);
    }
    stack_destroy(stack, free);
    puts("test_stack: OK");
    return 0;
}
