# Sokoban

## Installation 

Pour installer le jeu, suivez ces étapes:

- Clonez le repo sur votre machine locale:

  `git clone https://github.com/QuetzalCtrl/Sokoban.git`

- Déplacez vous dans le répertoire qui vient d'être créé (où le repo a été clonné):

  `cd Sokoban`

- Compilez le jeu:

  `make`

- Lancez le jeu:

  `./sokoban.o`

Vous devriez arriver dans le menu principal, qui ressemble à ça : 

![sokoban](https://user-images.githubusercontent.com/58345798/210526459-8bc9776e-3833-4bc8-a463-e8a13fcf753a.png)

## But du jeu

Sokoban (ou « garde d’entrepôt ») est un jeu vidéo de réflexion inventé au Japon en 1982. Dans ce jeu, le joueur doit ranger des caisses sur des cases cibles.
Il peut se déplacer dans les quatre directions, et pousser (mais pas tirer) une seule caisse à la fois. Une fois toutes les caisses rangées, le niveau est réussi.
L’idéal est de réussir avec le moins de déplacement possible.

Ce jeu a connu beaucoup de versions et d’adaptation différentes. Dans le cadre de ce projet, j'ai développé une version programmée en C et utilisable sur le terminal. 

![sokoban](https://user-images.githubusercontent.com/58345798/210526525-41f4d515-93dc-451e-a23c-d33fc2b05ba3.gif)

Dans cette version : 
- le joueur est représenté par `@` (ou par `+` lorsqu'il est sur une case cible)
- une caisse est représentée par `$` lorsqu'elle n'est pas sur une case cible, et par `*` lorsqu'elle est sur une case cible.
- une case cible est représentée par `.`
- un mur est représenté par `#`
