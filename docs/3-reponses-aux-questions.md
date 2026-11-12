# Réponses simples pour préparer les questions

Les six premières rubriques répondent aux questions de l'énoncé `Mini-projet.pdf`. Les pages indiquées permettent de retrouver chaque demande dans le sujet. Les réponses correspondent à la version simplifiée du code.

## Question 1. Comment décrire le besoin ?

**Demande du sujet, page 2 :** appliquer la grille IOCSF au projet en décrivant les données, la sortie, les contraintes, le volume et la fréquence de recherche.

Voici une phrase pour chacune des cinq dimensions données entre parenthèses dans le sujet, sans inventer les noms utilisés pour les lettres dans le cours :

- **Données :** on ajoute des utilisateurs avec un e-mail et un identifiant entier, puis on reçoit un e-mail à rechercher.
- **Sortie :** la recherche renvoie `true` si l'e-mail est présent et `false` sinon.
- **Contraintes :** le programme est écrit en C, les méthodes gardent la même interface, un annuaire vide doit être géré et la mémoire allouée doit être libérée.
- **Volume :** nos mesures vont de 100 à un million d'utilisateurs, et les situations de l'énoncé envisagent aussi un annuaire de cinq millions d'utilisateurs.
- **Fréquence :** elle dépend de l'usage, de deux consultations par jour à des milliers de recherches par seconde, avec parfois des inscriptions en continu.

Le programme mesure le temps d'une recherche répétée ; il ne mesure pas la fréquence d'utilisation d'une application réelle.

## Question 2. Comment insérer dans le tableau trié ?

**Demande du sujet, page 3 :** choisir une stratégie pour garder le tableau trié et donner le coût de l'insertion, pas seulement celui de la recherche.

« On part de la fin. Tant que l'utilisateur précédent doit être placé après le nouveau, on le décale d'une case vers la droite. Quand on a trouvé la place, on écrit le nouvel utilisateur. »

La boucle peut déplacer tous les utilisateurs déjà présents. Une insertion coûte donc **O(n) dans le pire cas**. Il n'est pas nécessaire de retrier tout le tableau à chaque fois. La dichotomie sert à la recherche, pas à l'insertion dans cette version simplifiée.

## Question 3. Quelles sont les complexités ?

**Demande du sujet, page 4 :** prévoir la complexité de recherche des trois premières méthodes dans le pire cas, avant de regarder les mesures.

Ici, `n` représente le nombre d'utilisateurs. On considère des e-mails de longueur bornée, comme dans le programme. Le tableau ajoute le coût des insertions et la quatrième méthode pour avoir une vue d'ensemble.

| Méthode | Recherche | Ajout |
|---|---|---|
| Tableau non trié | O(n) au pire | O(1) amorti ; O(n) lors d'un agrandissement |
| Hachage | O(1) en moyenne si bien dimensionné ; O(n) au pire | O(1), sans vérification des doublons |
| Tableau trié | O(log n) au pire | O(n) au pire |
| Liste chaînée | O(n) au pire | O(1), en tête |

« O(n), ça veut dire qu'on peut avoir à parcourir tous les utilisateurs. O(log n), c'est le cas de la dichotomie : on élimine la moitié à chaque étape. O(1), c'est un coût qui ne dépend pas de `n`, sous les conditions annoncées. »

Pour être précis sur le hachage : avec une bonne répartition, le coût moyen de recherche est O(1 + n/m), où `m` est le nombre de cases. Ici `m` reste fixé à 100 003. On ne peut donc pas promettre une recherche constante si `n` augmente sans limite.

## Question 4. Est-ce que les mesures correspondent à ce qu'on attendait ?

**Demande du sujet, page 4 :** comparer les mesures aux prévisions et expliquer les écarts possibles avec les constantes de calcul, la mémoire et l'environnement.

« Oui, dans l'ensemble. Parcourir tout l'annuaire devient coûteux quand il grossit. Le hachage et la dichotomie restent beaucoup plus rapides dans notre test. Mais on ne retrouve pas forcément des proportions exactes, parce que le temps dépend aussi de la mémoire et de la machine. »

Valeurs du `resultats.csv` produit par une exécution de la version simplifiée, converties en microsecondes :

| Utilisateurs | Tableau non trié | Hachage | Dichotomie | Liste chaînée |
|---|---:|---:|---:|---:|
| 100 | 0,392 | 0,023 | 0,059 | 0,210 |
| 1 000 | 6,540 | 0,009 | 0,068 | 9,440 |
| 10 000 | 99,400 | 0,030 | 0,097 | 93,000 |
| 100 000 | 1 158,000 | 0,021 | 0,135 | 5 522,000 |
| 1 000 000 | 12 280,000 | 0,062 | 0,098 | 57 060,000 |

Pour l'oral, retiens surtout : **12 ms pour le tableau non trié, 57 ms pour la liste et moins d'une microseconde pour le hachage et la dichotomie**. Ne mélange pas les unités : 1 ms vaut 1 000 µs.

Deux observations à commenter :

- Les temps très courts du hachage et de la dichotomie fluctuent : ils ne montent pas régulièrement avec la taille dans cette exécution. Il faut refaire plusieurs séries pour analyser finement ces écarts. La table de hachage reste fixe ; cela ne garantit pas un coût constant pour un annuaire qui grandit sans limite.
- La liste est environ cinq fois plus lente que le tableau non trié à un million. La disposition des données et les accès mémoire aident à expliquer cet écart, sans que ce test en établisse la cause exacte. Elle n'est pas plus lente à toutes les tailles dans cette série.

## Question 5. Quelle méthode choisir selon le cas ?

**Demande du sujet, page 4 :** recommander une méthode pour chacune des quatre situations et justifier le choix.

**Un annuaire de 30 employés, consulté deux fois par jour.**

« Je prendrais le tableau non trié. Il est simple et, pour 30 personnes, parcourir toutes les cases ne pose pas de problème. »

**Cinq millions d'utilisateurs et des milliers de recherches par seconde.**

« Je choisirais le hachage, en prévoyant une table assez grande ou redimensionnable. Je ne garderais pas automatiquement les 100 003 cases de notre démonstration. »

**Un fichier déjà trié, beaucoup consulté et jamais modifié.**

« La dichotomie est bien adaptée. On profite du tri sans payer le coût des décalages lors d'ajouts. »

**Des inscriptions et des recherches en continu.**

« Le hachage est un bon compromis : on ajoute en tête d'une liste et on cherche dans la case calculée. Il faut surveiller le nombre de collisions quand l'annuaire grandit. »

## Question 6. Pourquoi la liste et le tableau n'ont-ils pas le même temps ?

**Demande du sujet, page 5 :** comparer les temps de la liste chaînée et du tableau non trié, malgré leur même complexité, puis expliquer un éventuel écart par leur disposition en mémoire et le cache.

« Ils sont tous les deux en O(n), car ils peuvent devoir visiter tous les utilisateurs. Mais une visite n'a pas forcément le même coût. Dans un tableau, les données sont côte à côte. Dans une liste, on doit suivre un pointeur pour atteindre le nœud suivant. Le processeur exploite généralement mieux le tableau. »

Le **cache** est une petite mémoire rapide près du processeur. Le tableau facilite l'utilisation des données voisines et leur préchargement. Dans une liste, suivre les adresses rend ce travail plus difficile. Il serait trop fort de dire qu'aucun préchargement n'est possible ou de fixer une limite précise de cache sans mesurer la machine.

## Questions courtes à répéter à deux

### Pourquoi chercher un e-mail absent ?

« Ça force le tableau non trié et la liste à aller jusqu'au bout. En revanche, ça ne crée pas le pire cas du hachage. »

### C'est quoi, une collision ?

« Deux e-mails donnent la même case. On les garde dans la liste de cette case, puis on compare les e-mails pour trouver le bon. »

### Pourquoi 100 003 cases ?

« C'est la taille choisie dans le code, et c'est un nombre premier. Ce choix peut aider certaines répartitions, mais il ne garantit pas l'absence de collisions. La fonction de hachage et les données comptent aussi. »

### Pourquoi répéter la recherche ?

« Une seule est trop courte pour être mesurée correctement avec cette horloge. On mesure beaucoup de recherches, puis on divise le temps total par leur nombre. »

### Pourquoi doubler la capacité du tableau ?

« Pour éviter une réallocation à chaque ajout. Un agrandissement peut être coûteux, mais il devient de moins en moins fréquent. »

### Pourquoi ajouter vite ne veut pas dire chercher vite ?

« Dans la liste, on peut ajouter directement en tête. Mais pour retrouver un e-mail, on ne sait pas à quel endroit il est : il faut suivre les nœuds. »

### Que se passe-t-il avec un doublon ?

« Il est ajouté une deuxième fois. Le code ne bloque pas les doublons. Il faut appeler `search` avant `insert` si on veut les éviter. »

### Comment vérifier la mémoire ?

« Le code libère les tableaux et les nœuds. Les tests vérifient le retour à un annuaire vide. Pour affirmer qu'il n'y a pas de fuite, il faudrait aussi un contrôle avec un outil spécialisé. »

### Pourquoi `%07d` dans les e-mails ?

« Les zéros permettent de garder le même ordre entre les numéros et les chaînes. Pendant le remplissage, le tableau trié reçoit donc les e-mails dans l'ordre. »

### Pourquoi la dichotomie exige-t-elle un tableau trié ?

« Sans le tri, la comparaison avec le milieu ne permettrait pas de savoir quelle moitié éliminer. On risquerait d'écarter celle qui contient l'e-mail. »

### Est-ce qu'on a prouvé que le hachage est toujours le plus rapide ?

« Non. Il gagne sur nos mesures. Pour généraliser, il faudrait varier les e-mails, tester des recherches réussies, refaire plusieurs séries et étudier davantage les collisions. »
