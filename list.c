/*
 * list.c - Approche 4 : liste chaînée simple.
 *
 * Structure : chaque utilisateur est un noeud alloué séparément (malloc),
 * relié au suivant par un pointeur.
 *
 * Insertion : en tête de liste                  -> O(1)
 * Recherche : on suit les pointeurs un par un   -> O(n)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "annuaire.h"

typedef struct ListNode {
    char email[EMAIL_MAX];
    int id;
    struct ListNode *next;
} ListNode;

static ListNode *tete = NULL; /* premier noeud (NULL = liste vide) */

void list_insert(const char email[], int id)
{
    ListNode *nouveau = malloc(sizeof(ListNode));
    if (nouveau == NULL) {
        printf("Erreur : memoire insuffisante\n");
        exit(1);
    }
    snprintf(nouveau->email, EMAIL_MAX, "%s", email);
    nouveau->id = id;

    /* Le nouveau noeud pointe sur l'ancienne tête, puis devient la tête. */
    nouveau->next = tete;
    tete = nouveau;
}

bool list_search(const char email[])
{
    /* Liste vide : tete vaut NULL, la boucle ne s'exécute pas. */
    ListNode *courant = tete;
    while (courant != NULL) {
        if (strcmp(courant->email, email) == 0) {
            return true;
        }
        courant = courant->next;
    }
    return false;
}

void list_free(void)
{
    ListNode *courant = tete;
    while (courant != NULL) {
        ListNode *suivant = courant->next; /* à lire AVANT le free */
        free(courant);
        courant = suivant;
    }
    tete = NULL;
}
