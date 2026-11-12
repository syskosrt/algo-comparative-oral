/*
 * sorted.c - Approche 3 : recherche dichotomique.
 *
 * Structure : un tableau de User alloué dynamiquement, TOUJOURS trié
 * par e-mail (ordre alphabétique de strcmp).
 *
 * Insertion : on insère directement à la bonne place, en décalant
 *             d'une case les éléments plus grands -> O(n)
 * Recherche : on coupe l'intervalle en deux à chaque étape -> O(log n)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "annuaire.h"

static User *tab = NULL;
static int taille = 0;
static int capacite = 0;

void sorted_insert(const char email[], int id)
{
    if (taille == capacite) {
        int nouvelle_capacite;
        if (capacite == 0) {
            nouvelle_capacite = 16;
        } else {
            nouvelle_capacite = capacite * 2;
        }

        User *nouveau_tab = realloc(tab, nouvelle_capacite * sizeof(User));
        if (nouveau_tab == NULL) {
            printf("Erreur : memoire insuffisante\n");
            exit(1);
        }
        tab = nouveau_tab;
        capacite = nouvelle_capacite;
    }

    /* On part de la fin. Chaque utilisateur plus grand est decale a droite. */
    int position = taille;
    while (position > 0 && strcmp(tab[position - 1].email, email) > 0) {
        tab[position] = tab[position - 1];
        position--;
    }

    /* La case position est maintenant libre pour le nouvel utilisateur. */
    snprintf(tab[position].email, EMAIL_MAX, "%s", email);
    tab[position].id = id;
    taille++;
}

bool sorted_search(const char email[])
{
    /* Annuaire vide : droite vaut -1, la boucle ne s'exécute pas. */
    int gauche = 0;
    int droite = taille - 1;

    while (gauche <= droite) {
        int milieu = (gauche + droite) / 2;
        int comparaison = strcmp(tab[milieu].email, email);

        if (comparaison == 0) {
            return true;         /* trouvé */
        } else if (comparaison < 0) {
            gauche = milieu + 1; /* l'e-mail cherché est plus loin */
        } else {
            droite = milieu - 1; /* l'e-mail cherché est avant */
        }
    }
    return false;
}

void sorted_free(void)
{
    free(tab);
    tab = NULL;
    taille = 0;
    capacite = 0;
}
