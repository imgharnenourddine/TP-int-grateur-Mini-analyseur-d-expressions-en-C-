/*
 * ds_status.h - Codes de retour communs.
 * Fichier annoncé « fourni » par le sujet, non transmis avec le PDF :
 * cette version compatible est donc fournie dans le livrable.
 */
#ifndef DS_STATUS_H
#define DS_STATUS_H

/* Résultat d'une opération : DS_OK si tout va bien, sinon le type d'erreur. */
typedef enum {
    DS_OK = 0,        /* succès */
    DS_ERR_ALLOC,     /* malloc/realloc a échoué */
    DS_ERR_EMPTY,     /* structure vide (pop/top impossible) */
    DS_ERR_FULL,      /* structure pleine */
    DS_ERR_NULL,      /* pointeur NULL passé en argument */
    DS_ERR_INVALID,   /* argument invalide */
    DS_ERR_DIV_ZERO,  /* division par zéro */
    DS_ERR_SYNTAX     /* expression mal formée */
} DsStatus;

/* Retourne un texte lisible décrivant le code d'erreur. */
const char *ds_status_str(DsStatus status);

#endif
