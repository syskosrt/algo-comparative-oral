/*
 * annuaire.h - Déclarations communes aux quatre approches.
 *
 * Les quatre approches exposent exactement la même interface :
 *   xxx_insert(email, id) : ajoute un utilisateur
 *   xxx_search(email)     : dit si l'e-mail existe (true / false)
 *   xxx_free()            : libère toute la mémoire de l'approche
 *
 * Seul le préfixe change : seq_, hash_, sorted_, list_.
 */
#ifndef ANNUAIRE_H
#define ANNUAIRE_H

#include <stdbool.h>

#define EMAIL_MAX 100 /* taille maximale d'un e-mail, '\0' compris */

/* Étape 1 : un utilisateur = un e-mail + un identifiant numérique. */
typedef struct User {
    char email[EMAIL_MAX];
    int id;
} User;

/* Approche 1 : recherche séquentielle dans un tableau dynamique */
/* email[] est une chaine de caracteres ; const signifie qu'on ne la modifie pas. */
void seq_insert(const char email[], int id);
bool seq_search(const char email[]);
void seq_free(void);

/* Approche 2 : table de hachage (tableau de listes chaînées) */
void hash_insert(const char email[], int id);
bool hash_search(const char email[]);
void hash_free(void);

/* Approche 3 : recherche dichotomique dans un tableau trié */
void sorted_insert(const char email[], int id);
bool sorted_search(const char email[]);
void sorted_free(void);

/* Approche 4 : liste chaînée simple */
void list_insert(const char email[], int id);
bool list_search(const char email[]);
void list_free(void);

#endif
