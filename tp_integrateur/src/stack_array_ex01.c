/*
 * stack_array.c - Pile implémentée avec un tableau dynamique.
 * Le tableau double de taille quand il est plein (push en O(1) amorti).
 */
#include "stack.h"

#include <stdlib.h>

/* data : tableau d'éléments, size : nombre d'éléments, capacity : taille du tableau */
struct Stack {
    void **data;
    size_t size;
    size_t capacity;
};

/* Agrandit le tableau (8 au départ, puis x2). */
static DsStatus stack_grow(Stack *stack) {
    size_t new_capacity = stack->capacity == 0U ? 8U : stack->capacity * 2U;
    void **new_data = realloc(stack->data, new_capacity * sizeof(*new_data));
    if (new_data == NULL) {
        return DS_ERR_ALLOC;
    }
    stack->data = new_data;
    stack->capacity = new_capacity;
    return DS_OK;
}

/* Crée une pile vide (calloc met tous les champs à 0/NULL). */
Stack *stack_create(void) {
    Stack *stack = calloc(1U, sizeof(*stack));
    return stack;
}

/* Ajoute à la fin du tableau ; agrandit d'abord si plein. */
DsStatus stack_push(Stack *stack, void *value) {
    if (stack == NULL) {
        return DS_ERR_NULL;
    }
    if (stack->size == stack->capacity) {
        DsStatus status = stack_grow(stack);
        if (status != DS_OK) {
            return status;
        }
    }
    stack->data[stack->size] = value;
    stack->size++;
    return DS_OK;
}

/* Retire le dernier élément ; erreur si la pile est vide. */
DsStatus stack_pop(Stack *stack, void **out_value) {
    if (stack == NULL || out_value == NULL) {
        return DS_ERR_NULL;
    }
    if (stack->size == 0U) {
        return DS_ERR_EMPTY;
    }
    stack->size--;
    *out_value = stack->data[stack->size];
    stack->data[stack->size] = NULL;
    return DS_OK;
}

/* Lit le dernier élément sans le retirer. */
DsStatus stack_top(const Stack *stack, void **out_value) {
    if (stack == NULL || out_value == NULL) {
        return DS_ERR_NULL;
    }
    if (stack->size == 0U) {
        return DS_ERR_EMPTY;
    }
    *out_value = stack->data[stack->size - 1U];
    return DS_OK;
}

/* Vrai si aucun élément. */
bool stack_is_empty(const Stack *stack) {
    return stack == NULL || stack->size == 0U;
}

/* Retourne le nombre d'éléments. */
size_t stack_size(const Stack *stack) {
    return stack == NULL ? 0U : stack->size;
}

/* Libère les éléments (si free_value fourni), puis le tableau, puis la pile. */
void stack_destroy(Stack *stack, void (*free_value)(void *)) {
    if (stack == NULL) {
        return;
    }
    if (free_value != NULL) {
        for (size_t i = 0U; i < stack->size; ++i) {
            free_value(stack->data[i]);
        }
    }
    free(stack->data);
    free(stack);
}
