# Fiche à garder sous les yeux

**But :** retrouver le fil avec quelques mots. Ne lis pas cette fiche comme un texte.

## Personne 1 - environ 4 minutes

**Départ.** Annuaire = e-mail + identifiant. Question = cet e-mail existe déjà ? Quatre façons de ranger les mêmes données.

**Tableau non trié.** Cases une par une. Absent = tout parcourir. Recherche O(n).

**Hachage.** E-mail → numéro de case. Collision = plusieurs utilisateurs dans la même case. Recherche O(1) en moyenne si bien dimensionné ; O(n) au pire.

**Tableau trié.** Milieu → garder une moitié → recommencer. Recherche O(log n), environ 20 étapes pour un million. Ajout : décalages, O(n) au pire.

**Liste chaînée.** Suivre les liens. Ajout en tête O(1), recherche O(n).

**Code.** Montrer `annuaire.h`. Même interface : ajout, recherche, nettoyage. Mêmes tests pour les quatre versions. Passer la parole.

## Personne 2 - environ 4 minutes

**Mesure.** Mêmes données, de 100 à un million. Même e-mail absent répété. Chronométrer beaucoup de recherches, puis diviser. Le remplissage n'est pas chronométré.

**Nuance.** Absent = parcours complet pour tableau non trié et liste ; pas forcément pire cas du hachage.

**Un million d'utilisateurs - chiffres arrondis du CSV actuel :**

| Tableau non trié | Hachage | Dichotomie | Liste |
|---:|---:|---:|---:|
| 12 ms | 0,06 µs | 0,10 µs | 57 ms |

**Unités.** 1 ms = 1 000 µs. Liste ≈ 5 fois plus lente que tableau non trié à un million.

**À expliquer.** Même O(n), temps différents : tableau contigu, liste avec pointeurs. Hachage : 100 003 cases fixes, listes plus longues quand l'annuaire grossit.

**Limite.** Une recherche absente répétée, une machine. Pas une preuve pour tous les usages.

**Fin.** Petit annuaire → simplicité. Beaucoup d'ajouts et de recherches → hachage bien dimensionné. Déjà trié, peu modifié → dichotomie.

## Si tu perds le fil

Reviens à cette question : **« Qu'est-ce que la méthode doit parcourir pour trouver l'e-mail ? »**

Pour le tableau non trié et la liste : potentiellement tout. Pour la dichotomie : une zone qu'on divise en deux. Pour le hachage : la liste d'une case.
