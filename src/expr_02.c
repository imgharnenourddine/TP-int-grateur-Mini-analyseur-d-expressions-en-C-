/*
 * expr.c - Vérification du parenthésage avec une pile (exercice 2).
 * Principe : on empile chaque ouverture ; à chaque fermeture, on dépile
 * et on vérifie que les deux symboles se correspondent. Complexité O(n).
 */
#include "expr.h"
#include "stack.h"

#include <stdlib.h>

/* Vérifie si le caractère est une ouverture */
static int is_open_bracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

/* Vérifie si le caractère est une fermeture */
static int is_close_bracket(char c) {
    return c == ')' || c == ']' || c == '}';
}

/* Donne l'ouverture correspondant à une fermeture */
static char matching_open(char c) {
    switch (c) {
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        default:  return '\0';
    }
}

/* Donne la fermeture correspondant à une ouverture */
static char matching_close(char c) {
    switch (c) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        default:  return '\0';
    }
}

/*
 * Parcourt text et retourne le résultat de la vérification :
 * OK, fermeture inattendue, mauvais appariement ou ouverture non refermée.
 * Les autres caractères sont ignorés.
 */
ExprBracketResult expr_check_brackets(const char *text) {

    ExprBracketResult result = {
        EXPR_BRACKETS_OK,
        0U,
        '\0',
        '\0'
    };

    /* Vérifier le pointeur */
    if (text == NULL) {
        result.error = EXPR_BRACKETS_UNEXPECTED_CLOSE;
        return result;
    }

    /* Créer la pile */
    Stack *stack = stack_create();

    if (stack == NULL) {
        result.error = EXPR_BRACKETS_UNEXPECTED_CLOSE;
        return result;
    }

    /* Parcourir la chaîne */
    for (size_t i = 0U; text[i] != '\0'; i++) {

        char c = text[i];

        /* Cas 1 : ouverture */
        if (is_open_bracket(c)) {

            char *saved = malloc(sizeof(char));

            if (saved == NULL) {
                stack_destroy(stack, free);
                result.error = EXPR_BRACKETS_UNEXPECTED_CLOSE;
                result.position = i;
                return result;
            }

            *saved = c;

            if (stack_push(stack, saved) != DS_OK) {
                free(saved);
                stack_destroy(stack, free);
                result.error = EXPR_BRACKETS_UNEXPECTED_CLOSE;
                result.position = i;
                return result;
            }
        }

        /* Cas 2 : fermeture */
        else if (is_close_bracket(c)) {

            void *value = NULL;

            /* Vérifier si la pile est vide */
            if (stack_pop(stack, &value) != DS_OK) {

                result.error = EXPR_BRACKETS_UNEXPECTED_CLOSE;
                result.position = i;
                result.found = c;

                stack_destroy(stack, free);
                return result;
            }

            char open = *(char *) value;
            free(value);

            /* Vérifier si les délimiteurs correspondent */
            if (open != matching_open(c)) {

                result.error = EXPR_BRACKETS_MISMATCH;
                result.position = i;
                result.expected = matching_close(open);
                result.found = c;

                stack_destroy(stack, free);
                return result;
            }
        }
    }

    /* Cas 3 : vérifier les ouvertures restantes */
    if (!stack_is_empty(stack)) {

        void *value = NULL;
        stack_pop(stack, &value);

        char open = *(char *) value;
        free(value);

        result.error = EXPR_BRACKETS_UNCLOSED_OPEN;
        result.position = 0U;
        result.expected = matching_close(open);

        /* Récupérer la position exacte serait nécessaire ici */
    }

    stack_destroy(stack, free);

    return result;
}

