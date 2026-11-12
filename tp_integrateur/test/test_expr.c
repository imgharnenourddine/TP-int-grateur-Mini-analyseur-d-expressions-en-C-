/*
 * test_expr.c - Tests de expr_check_brackets (exercice 2).
 * Chaque test vérifie le type d'erreur et, si besoin, sa position (depuis 0).
 */
#include "expr.h"

#include <assert.h>
#include <stdio.h>

int main(void) {

    ExprBracketResult result;

    /* Test 1 : expression correcte */
    result = expr_check_brackets("{[a+b]*(c-d)}");
    assert(result.error == EXPR_BRACKETS_OK);

    /* Test 2 : mauvais appariement */
    result = expr_check_brackets("([a+b)]");
    assert(result.error == EXPR_BRACKETS_MISMATCH);
    assert(result.position == 6U);

    /* Test 3 : expression correcte */
    result = expr_check_brackets("((a+b)*[c-d])");
    assert(result.error == EXPR_BRACKETS_OK);

    /* Test 4 : imbrication correcte */
    result = expr_check_brackets("{[()]}");
    assert(result.error == EXPR_BRACKETS_OK);

    /* Test 5 : mauvais appariement */
    result = expr_check_brackets("([)]");
    assert(result.error == EXPR_BRACKETS_MISMATCH);
    assert(result.position == 2U);

    /* Test 6 : expression correcte (la virgule est ignorée) */
    result = expr_check_brackets("((x), x)");
    assert(result.error == EXPR_BRACKETS_OK);

    /* Test 7 : ouverture non refermée */
    result = expr_check_brackets("{(");
    assert(result.error == EXPR_BRACKETS_UNCLOSED_OPEN);
    assert(result.position == 1U);

    puts("Exercice 2 : tous les tests sont réussis.");

    return 0;
}

