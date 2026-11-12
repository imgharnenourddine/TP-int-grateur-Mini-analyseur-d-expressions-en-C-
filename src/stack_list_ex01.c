/*
 * stack_list.c - Pile implémentée avec une liste chaînée.
 * Le sommet de la pile est la tête de la liste : push/pop en O(1).
 */
#include "stack.h"

#include <stdlib.h>

/* Un maillon : la valeur stockée et le maillon situé en dessous. */
typedef struct StackNode {
    void *value;
    struct StackNode *next;
} StackNode;

/* top : maillon du sommet (NULL si vide), size : nombre d'éléments */
struct Stack {
    StackNode *top;
    size_t size;
};

/* Crée une pile vide. */
Stack *stack_create(void) {
    Stack *stack = calloc(1U, sizeof(*stack));
    return stack;
}

/* Crée un maillon et le place au sommet. */
DsStatus stack_push(Stack *stack, void *value) {
    if (stack == NULL) {
        return DS_ERR_NULL;
    }
    StackNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return DS_ERR_ALLOC;
    }
    node->value = value;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    return DS_OK;
}

/* Retire le maillon du sommet, rend sa valeur, libère le maillon. */
DsStatus stack_pop(Stack *stack, void **out_value) {
    if (stack == NULL || out_value == NULL) {
        return DS_ERR_NULL;
    }
    if (stack->top == NULL) {
        return DS_ERR_EMPTY;
    }
    StackNode *node = stack->top;
    stack->top = node->next;
    stack->size--;
    *out_value = node->value;
    free(node);
    return DS_OK;
}

/* Lit la valeur du sommet sans retirer le maillon. */
DsStatus stack_top(const Stack *stack, void **out_value) {
    if (stack == NULL || out_value == NULL) {
        return DS_ERR_NULL;
    }
    if (stack->top == NULL) {
        return DS_ERR_EMPTY;
    }
    *out_value = stack->top->value;
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

/* Parcourt la liste : libère chaque valeur (si free_value fourni) et chaque maillon. */
void stack_destroy(Stack *stack, void (*free_value)(void *)) {
    if (stack == NULL) {
        return;
    }
    StackNode *node = stack->top;
    while (node != NULL) {
        StackNode *next = node->next;
        if (free_value != NULL) {
            free_value(node->value);
        }
        free(node);
        node = next;
    }
    free(stack);
}
