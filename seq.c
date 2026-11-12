/*
 * seq.c - Approche 1 : recherche séquentielle.
 *
 * Structure : un tableau de User alloué dynamiquement.
 * Insertion : on ajoute à la fin              -> O(1) amorti
 * Recherche : on parcourt tout, case par case -> O(n)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "annuaire.h"

static User *tab = NULL; /* le tableau (NULL tant que l'annuaire est vide) */
static int taille = 0;   /* nombre d'utilisateurs présents */
static int capacite = 0; /* nombre de cases réservées en mémoire */

void seq_insert(const char email[], int id)
{
    /* Tableau plein : on double sa capacité avec realloc. */
    if (taille == capacite) {
        int nouvelle_capacite;
        if (capacite == 0) {
            nouvelle_capacite = 16;
        } else {
            nouvelle_capacite = capacite * 2;
        }

        /* realloc reserve plus de place et garde les utilisateurs deja ajoutes. */
        User *nouveau_tab = realloc(tab, nouvelle_capacite * sizeof(User));
        if (nouveau_tab == NULL) {
            printf("Erreur : memoire insuffisante\n");
            exit(1);
        }
        tab = nouveau_tab;
        capacite = nouvelle_capacite;
    }

    snprintf(tab[taille].email, EMAIL_MAX, "%s", email);
    tab[taille].id = id;
    taille++;
}

bool seq_search(const char email[])
{
    /* Annuaire vide : taille vaut 0, la boucle ne s'exécute pas. */
    for (int i = 0; i < taille; i++) {
        if (strcmp(tab[i].email, email) == 0) {
            return true;
        }
    }
    return false;
}

void seq_free(void)
{
    free(tab);
    tab = NULL;
    taille = 0;
    capacite = 0;
}
