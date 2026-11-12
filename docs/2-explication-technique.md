# Lire le code quand on débute en C

Le programme garde les quatre méthodes. Les tests appellent chaque version directement, et les mesures sont écrites dans quatre blocs qui se ressemblent. Il y a un peu de répétition, mais on peut suivre ce qui se passe sans connaître les pointeurs de fonction.

Pour commencer, lis **`annuaire.h`, puis `seq.c`**. Passe ensuite à `sorted.c`. Garde `list.c` et `hash.c` pour la fin : les listes demandent de comprendre les pointeurs.

## 1. Les quelques signes à connaître

| Écriture | Sens dans notre code |
|---|---|
| `int taille = 0;` | Un nombre entier, initialisé à zéro |
| `char email[100];` | Un tableau qui peut contenir une chaîne de caractères |
| `bool` | Une réponse `true` ou `false` |
| `if`, `else` | Faire un choix selon une condition |
| `for`, `while` | Répéter des instructions |
| `taille++` | Ajouter 1 à `taille` |
| `tab[i]` | Lire ou modifier la case numéro `i` |
| `tab[i].email` | Accéder à l'e-mail de l'utilisateur de cette case |
| `strcmp(a, b) == 0` | Les deux chaînes contiennent le même texte |
| `NULL` | Un pointeur qui ne désigne aucun élément |

Une chaîne C se termine par le caractère `\0`. Dans nos tableaux de 100 caractères, il reste donc 99 caractères utiles pour l'e-mail.

## 2. `annuaire.h` : les données et les fonctions disponibles

`User` regroupe l'e-mail et l'identifiant d'un utilisateur dans une **structure**.

Chaque méthode propose trois opérations :

```c
void seq_insert(const char email[], int id);
bool seq_search(const char email[]);
void seq_free(void);
```

`insert` ajoute, `search` répond si l'e-mail existe et `free` nettoie la mémoire. Les autres méthodes ont les mêmes opérations, avec un autre préfixe.

`const` indique que la fonction ne modifie pas l'e-mail reçu. `void` avant le nom signifie que la fonction ne renvoie pas de résultat. `void` entre les parenthèses signifie qu'elle ne reçoit aucun argument.

## 3. `seq.c` : la version la plus simple

On garde trois informations : le tableau `tab`, le nombre d'utilisateurs `taille` et le nombre de places réservées `capacite`.

Pour ajouter, on écrit dans `tab[taille]`, puis on augmente `taille` de 1.

Pour chercher, on utilise une boucle :

```c
for (int i = 0; i < taille; i++) {
    if (strcmp(tab[i].email, email) == 0) {
        return true;
    }
}
return false;
```

À expliquer ainsi : « Je regarde chaque utilisateur. Si son e-mail correspond, je réponds vrai. Si j'arrive à la fin sans le trouver, je réponds faux. »

Si le tableau est plein, `realloc` lui réserve plus de place. On commence avec 16 places, puis on double : 32, 64, 128, etc. Le bloc `if / else` choisit la nouvelle capacité.

`sizeof(User)` donne la taille d'un utilisateur en octets. On multiplie cette taille par le nombre de places à réserver. `nouveau_tab` permet de vérifier que la réservation a réussi avant de remplacer l'ancien pointeur.

## 4. `sorted.c` : garder le tableau trié

L'ajout part de la fin du tableau. Tant que l'utilisateur précédent doit être placé après le nouveau, on le décale d'une case vers la droite.

Exemple : pour ajouter Bob à `[Alice, Charlie]`, on décale Charlie. On obtient une place entre Alice et Charlie, puis on y écrit Bob.

La ligne `tab[position] = tab[position - 1];` copie un utilisateur entier vers la case suivante. On utilise une boucle ordinaire, sans `memmove` ni recherche dichotomique pour l'insertion.

La **recherche**, elle, reste dichotomique : `gauche` et `droite` délimitent les cases encore possibles. On regarde `milieu`, on compare les e-mails, puis on garde une moitié.

Pour `strcmp`, zéro signifie égal ; un résultat négatif signifie que le premier texte est avant le second ; un résultat positif signifie qu'il est après. Cet ordre permet de savoir de quel côté continuer.

## 5. `list.c` : les notions de mémoire à comprendre

Une liste est faite de nœuds. Chaque nœud contient un utilisateur et l'adresse du suivant.

- `ListNode *courant` : `courant` contient l'adresse d'un nœud. C'est un **pointeur**.
- `malloc(sizeof(ListNode))` : réserver de la mémoire pour un nouveau nœud.
- `courant->email` : accéder au champ `email` du nœud pointé par `courant`.
- `courant = courant->next` : passer au nœud suivant.
- `free(courant)` : libérer la mémoire du nœud.

Pour ajouter en tête, le nouveau nœud pointe sur l'ancienne tête, puis devient la nouvelle tête. Pour chercher, on suit `next` jusqu'à trouver l'e-mail ou atteindre `NULL`.

Pour nettoyer, on garde l'adresse du suivant **avant** de libérer le nœud courant. On ne doit pas lire un nœud après son `free`.

## 6. `hash.c` : une liste dans chaque case

La table contient 100 003 cases. Chaque case donne le début d'une liste de `Node`.

La petite fonction `hacher` lit les caractères de l'e-mail pour calculer un nombre. Le calcul utilisé s'appelle **djb2**. Ses constantes, 5381 et 33, viennent de cette formule ; elles ne sont pas liées au nombre d'utilisateurs.

`unsigned int` représente un entier sans signe. La conversion en `unsigned char` permet d'utiliser la valeur d'un caractère sans signe négatif. Le symbole `%` donne le reste d'une division : ici, il ramène le résultat à un numéro de case valide.

Pour chercher, on calcule la case, puis on parcourt sa liste. Même en cas de collision, on compare les e-mails avec `strcmp` pour reconnaître le bon utilisateur.

## 7. `main.c` : des appels écrits directement

Les tests appellent `seq_search`, `hash_search`, `sorted_search` et `list_search` par leur nom. Ils vérifient les mêmes cas pour les quatre versions : vide, trois utilisateurs présents, un absent et vide après nettoyage.

Pour les mesures, on remplit les quatre structures avec les mêmes adresses. Le format `user%07d@mail.com` ajoute des zéros devant le numéro. Les e-mails arrivent ainsi déjà dans l'ordre, ce qui évite les décalages dans le tableau trié pendant le remplissage.

Chaque méthode a ensuite son bloc :

1. Lire l'heure avec `clock()`.
2. Répéter les recherches dans une boucle.
3. Lire à nouveau l'heure.
4. Convertir la différence en secondes avec `CLOCKS_PER_SEC`, puis diviser par le nombre de recherches.

Le compteur de recherches réussies est affiché à la fin. Comme on cherche un e-mail absent, on attend zéro. Le résultat du calcul est donc utilisé, sans avoir besoin de `volatile`. On compile les fichiers séparément, sans option d'optimisation entre fichiers (`-flto`).

## Ce qu'il faut savoir expliquer à l'oral

Commencez par le parcours de recherche de chaque version. Ensuite, entraînez-vous à expliquer une insertion dans le tableau trié et un ajout en tête de liste.

Les notions propres au C qui restent nécessaires sont les structures, les chaînes, les pointeurs et la réservation de mémoire. Le code vérifie les échecs d'allocation, mais aucun outil spécialisé de détection de fuites n'a été utilisé.

Les e-mails doivent faire au maximum 99 caractères. `snprintf` limite la copie, mais tronquerait un e-mail trop long. Les doublons ne sont pas bloqués. Les variables `static` au niveau d'un fichier conservent les données entre deux appels et les rendent privées à ce fichier.
