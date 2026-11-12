/* Tests et mesures des quatre methodes. */
#include <stdio.h>
#include <time.h>
#include "annuaire.h"

static int nb_echecs = 0;

static void verifier(const char description[], bool obtenu, bool attendu)
{
    if (obtenu == attendu) {
        printf("[OK] %s\n", description);
    } else {
        printf("[ECHEC] %s\n", description);
        nb_echecs++;
    }
}

static void tester_approches(void)
{
    printf("--- Tableau non trie ---\n");
    verifier("Sequentielle : annuaire vide", seq_search("alice@mail.com"), false);

    /* On ajoute dans le desordre pour tester aussi le tableau trie. */
    seq_insert("charlie@mail.com", 3);
    seq_insert("alice@mail.com", 1);
    seq_insert("bob@mail.com", 2);

    verifier("Sequentielle : alice presente", seq_search("alice@mail.com"), true);
    verifier("Sequentielle : bob present", seq_search("bob@mail.com"), true);
    verifier("Sequentielle : charlie present", seq_search("charlie@mail.com"), true);
    verifier("Sequentielle : zoe absente", seq_search("zoe@mail.com"), false);

    seq_free();
    verifier("Sequentielle : vide apres nettoyage", seq_search("alice@mail.com"), false);

    printf("\n--- Table de hachage ---\n");
    verifier("Hachage : annuaire vide", hash_search("alice@mail.com"), false);

    hash_insert("charlie@mail.com", 3);
    hash_insert("alice@mail.com", 1);
    hash_insert("bob@mail.com", 2);

    verifier("Hachage : alice presente", hash_search("alice@mail.com"), true);
    verifier("Hachage : bob present", hash_search("bob@mail.com"), true);
    verifier("Hachage : charlie present", hash_search("charlie@mail.com"), true);
    verifier("Hachage : zoe absente", hash_search("zoe@mail.com"), false);

    hash_free();
    verifier("Hachage : vide apres nettoyage", hash_search("alice@mail.com"), false);

    printf("\n--- Tableau trie ---\n");
    verifier("Dichotomie : annuaire vide", sorted_search("alice@mail.com"), false);

    sorted_insert("charlie@mail.com", 3);
    sorted_insert("alice@mail.com", 1);
    sorted_insert("bob@mail.com", 2);

    verifier("Dichotomie : alice presente", sorted_search("alice@mail.com"), true);
    verifier("Dichotomie : bob present", sorted_search("bob@mail.com"), true);
    verifier("Dichotomie : charlie present", sorted_search("charlie@mail.com"), true);
    verifier("Dichotomie : zoe absente", sorted_search("zoe@mail.com"), false);

    sorted_free();
    verifier("Dichotomie : vide apres nettoyage", sorted_search("alice@mail.com"), false);

    printf("\n--- Liste chainee ---\n");
    verifier("Liste : annuaire vide", list_search("alice@mail.com"), false);

    list_insert("charlie@mail.com", 3);
    list_insert("alice@mail.com", 1);
    list_insert("bob@mail.com", 2);

    verifier("Liste : alice presente", list_search("alice@mail.com"), true);
    verifier("Liste : bob present", list_search("bob@mail.com"), true);
    verifier("Liste : charlie present", list_search("charlie@mail.com"), true);
    verifier("Liste : zoe absente", list_search("zoe@mail.com"), false);

    list_free();
    verifier("Liste : vide apres nettoyage", list_search("alice@mail.com"), false);
}

/* Renvoie 0 si les mesures ont ete enregistrees, 1 sinon. */
static int lancer_mesures(void)
{
    int tailles[] = {100, 1000, 10000, 100000, 1000000};
    long trouves = 0;
    FILE *csv = fopen("resultats.csv", "w");

    if (csv == NULL) {
        printf("Erreur : impossible de creer resultats.csv.\n");
        return 1;
    }

    fprintf(csv, "taille;sequentielle_s;hachage_s;dichotomique_s;liste_chainee_s\n");

    printf("Temps moyen d'une recherche d'un e-mail absent, en secondes\n\n");
    printf("%10s | %14s | %14s | %14s | %14s\n",
           "Taille", "Sequentielle", "Hachage", "Dichotomie", "Liste chainee");

    for (int t = 0; t < 5; t++) {
        int n = tailles[t];
        char email[EMAIL_MAX];

        /* Les quatre structures recoivent les memes utilisateurs. */
        for (int i = 0; i < n; i++) {
            /* Les zeros gardent les e-mails dans l'ordre des numeros. */
            snprintf(email, EMAIL_MAX, "user%07d@mail.com", i);
            seq_insert(email, i);
            hash_insert(email, i);
            sorted_insert(email, i);
            list_insert(email, i);
        }

        /* Les numeros presents vont de 0 a n - 1 : celui-ci est absent. */
        snprintf(email, EMAIL_MAX, "user%07d@mail.com", n);

        long rep_lentes = 50000000L / n;
        long rep_rapides = 5000000L;

        /* On repete les recherches, puis on calcule une moyenne. */
        clock_t debut = clock();
        for (long r = 0; r < rep_lentes; r++) {
            if (seq_search(email)) {
                trouves++;
            }
        }
        clock_t fin = clock();
        double t_seq = (double)(fin - debut) / CLOCKS_PER_SEC / rep_lentes;

        debut = clock();
        for (long r = 0; r < rep_rapides; r++) {
            if (hash_search(email)) {
                trouves++;
            }
        }
        fin = clock();
        double t_hash = (double)(fin - debut) / CLOCKS_PER_SEC / rep_rapides;

        debut = clock();
        for (long r = 0; r < rep_rapides; r++) {
            if (sorted_search(email)) {
                trouves++;
            }
        }
        fin = clock();
        double t_sorted = (double)(fin - debut) / CLOCKS_PER_SEC / rep_rapides;

        debut = clock();
        for (long r = 0; r < rep_lentes; r++) {
            if (list_search(email)) {
                trouves++;
            }
        }
        fin = clock();
        double t_list = (double)(fin - debut) / CLOCKS_PER_SEC / rep_lentes;

        printf("%10d | %14.9f | %14.9f | %14.9f | %14.9f\n",
               n, t_seq, t_hash, t_sorted, t_list);
        fprintf(csv, "%d;%.9f;%.9f;%.9f;%.9f\n",
                n, t_seq, t_hash, t_sorted, t_list);

        /* On vide tout avant de passer a la taille suivante. */
        seq_free();
        hash_free();
        sorted_free();
        list_free();
    }

    fclose(csv);
    /* Afficher ce compteur permet aussi d'utiliser le resultat des recherches. */
    printf("\nRecherches trouvees pendant les mesures : %ld (0 attendu).\n", trouves);
    printf("Resultats ecrits dans resultats.csv.\n");
    return 0;
}

int main(void)
{
    printf("=== TESTS ===\n\n");
    tester_approches();

    if (nb_echecs > 0) {
        printf("\n%d test(s) en echec : mesures annulees.\n", nb_echecs);
        return 1;
    }

    printf("\nTous les tests sont passes.\n\n");
    printf("=== MESURES ===\n\n");
    return lancer_mesures();
}
