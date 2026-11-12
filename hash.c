/*
 * hash.c - Approche 2 : table de hachage.
 *
 * Structure : un tableau fixe de "cases". Chaque case est le début d'une
 * liste chaînée de Node (chaînage en cas de collision).
 * La fonction de hachage transforme l'e-mail en numéro de case.
 *
 * Insertion : calcul de la case + ajout en tête de sa liste -> O(1)
 * Recherche : calcul de la case + parcours de sa seule liste
 *             -> rapide si la table est assez grande, O(n) au pire
 *                (si tous les e-mails tombaient dans la même case)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "annuaire.h"

#define TAILLE_TABLE 100003 /* nombre de cases (un nombre premier) */

typedef struct Node {
    User user;
    struct Node *next;
} Node;

/* Variable globale statique : toutes les cases valent NULL au départ. */
static Node *table[TAILLE_TABLE];

/* Fonction de hachage "djb2" : mélange les caractères de l'e-mail
 * pour obtenir un nombre, ramené entre 0 et TAILLE_TABLE - 1. */
static unsigned int hacher(const char email[])
{
    unsigned int h = 5381;
    for (int i = 0; email[i] != '\0'; i++) {
        h = h * 33 + (unsigned char)email[i];
    }
    return h % TAILLE_TABLE;
}

void hash_insert(const char email[], int id)
{
    unsigned int indice = hacher(email);

    Node *nouveau = malloc(sizeof(Node));
    if (nouveau == NULL) {
        printf("Erreur : memoire insuffisante\n");
        exit(1);
    }
    snprintf(nouveau->user.email, EMAIL_MAX, "%s", email);
    nouveau->user.id = id;

    /* Ajout en tête de la liste de cette case. */
    nouveau->next = table[indice];
    table[indice] = nouveau;
}

bool hash_search(const char email[])
{
    /* On ne regarde que la liste de la case concernée. */
    Node *courant = table[hacher(email)];
    while (courant != NULL) {
        if (strcmp(courant->user.email, email) == 0) {
            return true;
        }
        courant = courant->next;
    }
    return false;
}

void hash_free(void)
{
    for (int i = 0; i < TAILLE_TABLE; i++) {
        Node *courant = table[i];
        while (courant != NULL) {
            Node *suivant = courant->next; /* à lire AVANT le free */
            free(courant);
            courant = suivant;
        }
        table[i] = NULL;
    }
}
