# Comprendre le projet avant de le présenter

Le projet répond à une question simple : **est-ce qu'une adresse e-mail est déjà dans un annuaire ?** Chaque utilisateur possède un e-mail et un identifiant. La recherche renvoie oui ou non ; elle ne renvoie pas la fiche de l'utilisateur.

On a écrit quatre versions en C. Elles font la même chose, mais elles ne rangent pas les données de la même façon. C'est cette différence que l'on veut comparer.

## 1. Le tableau non trié : regarder une case après l'autre

On ajoute les utilisateurs à la fin d'un tableau. Pour chercher un e-mail, on commence à la première case et on avance jusqu'à le trouver.

Si l'e-mail est absent, il faut lire tout le tableau. Avec un million d'utilisateurs, cela représente un million de comparaisons. C'est une recherche en **O(n)** : le travail augmente avec le nombre d'utilisateurs.

L'ajout est rapide en général. Parfois, le tableau est plein et il faut l'agrandir. On dit donc que l'ajout coûte O(1) **amorti** : il est constant en moyenne sur une longue suite d'ajouts, mais un agrandissement peut coûter O(n).

## 2. Le hachage : calculer où chercher

Une fonction transforme l'e-mail en numéro de case. La recherche commence directement dans cette case, sans parcourir tout l'annuaire.

Deux e-mails différents peuvent donner le même numéro : c'est une **collision**. On garde alors les utilisateurs concernés dans une petite liste attachée à cette case. On compare les e-mails pour trouver le bon.

La recherche est en moyenne en **O(1)** si les données sont bien réparties et si la table est assez grande. Si tous les utilisateurs tombent dans la même case, elle peut coûter O(n).

Dans notre programme, la table garde toujours 100 003 cases. Quand l'annuaire grossit, les listes peuvent donc s'allonger. Le temps n'est pas garanti constant quelle que soit la taille de l'annuaire.

## 3. Le tableau trié : éliminer la moitié à chaque étape

Cette fois, les e-mails sont rangés dans l'ordre défini par `strcmp`. On regarde celui du milieu. Selon le résultat de la comparaison, on continue dans la moitié de gauche ou dans celle de droite.

On recommence jusqu'à trouver l'e-mail ou jusqu'à ne plus avoir de case à examiner. C'est la **recherche dichotomique**. Elle coûte **O(log n)** : pour un million d'utilisateurs, une vingtaine d'étapes suffisent.

La contrepartie se voit à l'ajout : pour garder le tableau trié, il faut parfois décaler beaucoup d'utilisateurs. Une insertion coûte donc O(n) dans le pire cas.

## 4. La liste chaînée : suivre les liens

Chaque utilisateur est stocké dans un nœud qui contient aussi l'adresse du suivant. Pour chercher, on suit ces liens un par un.

Comme avec le tableau non trié, on peut devoir parcourir tout l'annuaire : **O(n)**. Pour ajouter, on place simplement le nouveau nœud au début : O(1).

La liste et le tableau non trié ont la même complexité de recherche, mais ils n'ont pas forcément le même temps réel. Les cases d'un tableau sont côte à côte en mémoire. Les nœuds d'une liste sont alloués séparément, ce qui rend généralement le parcours moins efficace pour le processeur.

## Ce que mesure le programme

Il commence par vérifier des cas simples : annuaire vide, utilisateurs présents, e-mail absent et recherche après libération de la mémoire.

Ensuite, il remplit les quatre structures avec les mêmes e-mails, de 100 à un million d'utilisateurs. Il répète la recherche d'un même e-mail absent, mesure le temps total, puis calcule une moyenne par recherche. Le résultat est enregistré dans `resultats.csv`.

Un e-mail absent oblige le tableau non trié et la liste à tout parcourir. **Cela ne provoque pas le pire cas du hachage**, puisqu'on ne visite que la liste de la case calculée.

## Ce qu'il faut retenir des résultats

À un million d'utilisateurs, le CSV actuel donne environ :

| Méthode | Temps moyen d'une recherche |
|---|---:|
| Tableau non trié | 12 millisecondes |
| Hachage | 0,06 microseconde |
| Tableau trié | 0,10 microseconde |
| Liste chaînée | 57 millisecondes |

Une milliseconde vaut 1 000 microsecondes. Les chiffres sont arrondis pour être faciles à lire ; les valeurs exactes sont dans le CSV.

Le hachage et la dichotomie sont beaucoup plus rapides sur ce test. La liste est environ cinq fois plus lente que le tableau non trié à un million d'utilisateurs, même si les deux sont en O(n).

Ces mesures portent sur un e-mail absent répété, sur une machine. Elles illustrent des différences ; elles ne prouvent pas qu'une méthode gagnera dans toutes les situations.

## Comment choisir ?

- Pour un petit annuaire, le tableau non trié est simple et suffit souvent.
- Pour beaucoup de recherches et d'ajouts, le hachage est adapté si la table est bien dimensionnée.
- Pour des données déjà triées et rarement modifiées, la dichotomie est un bon choix.
- La liste rend l'ajout en tête simple, mais elle n'aide pas à retrouver rapidement un e-mail.

L'idée à expliquer à l'oral : **on ne compare pas seulement des boucles. On compare aussi des façons de ranger les données.**
