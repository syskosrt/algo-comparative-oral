# Mini-projet : un annuaire, quatre algorithmes

Un annuaire d'utilisateurs (e-mail + identifiant) implémenté de quatre façons en C, pour comparer leur vitesse de recherche en théorie (Big O) et par la mesure.

## Contenu du dossier

| Fichier | Rôle |
|---|---|
| `annuaire.h` | La structure `User` et les prototypes des quatre approches |
| `seq.c` | Approche 1 : recherche séquentielle (tableau dynamique) |
| `hash.c` | Approche 2 : table de hachage (tableau de listes chaînées) |
| `sorted.c` | Approche 3 : recherche dichotomique (tableau trié) |
| `list.c` | Approche 4 : liste chaînée simple |
| `main.c` | Les tests de chaque approche, puis les mesures de temps |
| `resultats.csv` | Le tableau de mesures produit par le programme |
| `docs/` | Les documents d'explication (voir plus bas) |

## Compiler et lancer

```
gcc -Wall -Wextra -O2 -o annuaire.exe main.c seq.c hash.c sorted.c list.c
annuaire.exe
```

Sur ce PC, le compilateur est `C:\msys64\ucrt64\bin\gcc.exe`. Dans PowerShell, depuis le dossier du projet :

```powershell
& 'C:\msys64\ucrt64\bin\gcc.exe' -std=c11 -Wall -Wextra -O2 -o annuaire.exe main.c seq.c hash.c sorted.c list.c
.\annuaire.exe
```

Le programme affiche d'abord le résultat des tests, puis le tableau des temps, qu'il écrit aussi dans `resultats.csv`. La durée dépend du PC. Une exécution remplace le CSV.

## Documents d'explication

| Document | À lire pour |
|---|---|
| `docs/1-explication-fonctionnelle.md` | Comprendre ce que fait le projet et les quatre approches, sans code |
| `docs/2-explication-technique.md` | Comprendre le code, fichier par fichier |
| `docs/3-reponses-aux-questions.md` | Les réponses aux questions 1 à 6 de l'énoncé, avec les mesures |
| `docs/4-support-oral.md` | Le texte à dire, prévu pour environ huit minutes |
| `docs/5-fiche-memo.md` | Fiche séparée conservée, hors du nouveau script |
| `docs/oral-annuaire.pdf` | Le texte de l'oral uniquement, à imprimer |


## Préparer l'oral

Commencer par [le texte à dire](docs/4-support-oral.md), prévu pour environ huit minutes à deux. Il est fondé sur l'énoncé fourni, « Un annuaire, quatre algorithmes », et couvre les questions 1 à 6 : analyse du besoin, insertion triée, complexités, mesures, choix selon les quatre situations et comparaison du tableau avec la liste.

[La version PDF à imprimer](docs/oral-annuaire.pdf) contient uniquement le script, sans fiche ni questions en annexe. Les chiffres correspondent à une exécution de la version simplifiée et sont arrondis dans le discours. Le document 3 détaille les six réponses avec les pages correspondantes du sujet et propose des questions d'entraînement supplémentaires.

## Version simplifiée pour débuter en C

Les tests et les mesures appellent chaque méthode directement. Il n'y a plus de pointeurs de fonction ni de `volatile`. L'insertion dans le tableau trié utilise une boucle de décalage, sans `memmove`. Les agrandissements des tableaux sont écrits avec des `if / else`.

On garde `malloc`, `realloc`, `free` et les pointeurs nécessaires aux tableaux dynamiques et aux listes. Leur rôle est expliqué dans [le guide de lecture du code](docs/2-explication-technique.md). Le projet conserve les quatre méthodes et les mêmes opérations.
