#include <stdio.h>
#include <stdlib.h>
typedef struct  {
  int colonne;
  int ligne;
} point_t;

typedef struct {
  point_t* perso;
  char* terrain;
  int nb_colonnes;
  int nb_lignes;
  int nb_de_pas;
  char case_a_sauvegarder;
  char ancienne_case;
} niveau_t;

typedef struct {
	int taille;
	int idx;
	niveau_t** tableau;
} historique_t;

#include "terrain.h"
#include "joueur.h"
#include "score.h"
#include "historique.h"