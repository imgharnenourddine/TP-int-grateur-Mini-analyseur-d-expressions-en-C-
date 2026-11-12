/*
 * expr.h - Vérification du parenthésage d'une expression (exercice 2).
 */
#ifndef EXPR_H
#define EXPR_H

#include <stddef.h>

/* Type d'erreur trouvé dans le parenthésage. */
typedef enum {
    EXPR_BRACKETS_OK,                /* tout est équilibré */
    EXPR_BRACKETS_UNEXPECTED_CLOSE,  /* fermeture sans ouverture */
    EXPR_BRACKETS_MISMATCH,          /* ex. "(]" : mauvais type de fermeture */
    EXPR_BRACKETS_UNCLOSED_OPEN      /* ouverture jamais refermée */
} ExprBracketError;

/* Résultat de la vérification. */
typedef struct {
    ExprBracketError error;  /* nature de l'erreur */
    size_t position;         /* indice (depuis 0) de l'erreur */
    char expected;           /* fermeture attendue (si mismatch) */
    char found;              /* caractère réellement trouvé */
} ExprBracketResult;

/* Vérifie (), [] et {} dans text à l'aide d'une pile. */
ExprBracketResult expr_check_brackets(const char *text);

#endif
