/*
 * stack.h - Interface d'une pile (LIFO : dernier entré, premier sorti).
 * La pile stocke des pointeurs génériques (void *).
 * Deux implémentations existent : stack_array.c (tableau) et stack_list.c (liste).
 */
#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "ds_status.h"

/* Type opaque : le contenu de la pile est caché dans le fichier .c. */
typedef struct Stack Stack;

/* Crée une pile vide. Retourne NULL si l'allocation échoue. */
Stack *stack_create(void);

/* Empile value au sommet. */
DsStatus stack_push(Stack *stack, void *value);

/* Retire le sommet et le range dans *out_value. DS_ERR_EMPTY si pile vide. */
DsStatus stack_pop(Stack *stack, void **out_value);

/* Lit le sommet sans le retirer. DS_ERR_EMPTY si pile vide. */
DsStatus stack_top(const Stack *stack, void **out_value);

/* Vrai si la pile est vide (ou NULL). */
bool stack_is_empty(const Stack *stack);

/* Nombre d'éléments dans la pile. */
size_t stack_size(const Stack *stack);

/* Libère la pile. Si free_value n'est pas NULL, il est appelé sur chaque élément restant. */
void stack_destroy(Stack *stack, void (*free_value)(void *));

#endif
