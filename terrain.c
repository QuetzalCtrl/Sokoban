#include "main.h"

/*
*niveau_t est un pointeur possédant comme attribut terrain.
*celui-ci pointe vers la première case d'un tableau de char de
*taille nb_colonnes et nb_lignes
*
*nouveau_niveau génère un nouveau niveau avec un nombre de
*colonnes et de lignes initialisées et où terrain cible un espace
*mémoire correspondant à un tableau de la bonne taille et qui *retourne un pointeur vers la structure générée.
*
*Cela retourne un tableau à une dimension de nombre de
*lignes "nb_lignes" et de nombre de colonnes "nb_colonnes" 
*/
niveau_t* nouveau_niveau(int nb_colonnes, int nb_lignes)
{
  niveau_t* niveau = malloc(sizeof(niveau_t));
  niveau->nb_lignes = nb_lignes;
  niveau->nb_colonnes = nb_colonnes;
  niveau->terrain = malloc((nb_colonnes * nb_lignes)*sizeof(char));
  niveau->perso = malloc(sizeof(point_t));
  niveau->perso->ligne = 0;
  niveau->perso->colonne = 0;
  niveau->nb_de_pas = 0;
  niveau->case_a_sauvegarder = ' ';
  niveau->ancienne_case = ' ';
  return niveau;
}

/*
*place_sur_terrain place le caractère "car" sur le terrain 
*aux positions de la ligne "ligne" et à la colonne "colonne"
*/
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car){
  niveau->terrain[ligne*niveau->nb_colonnes+colonne]=car;
}

/*
*Retourne le caractère à la ligne "ligne", et à la colonne "colonne" du tableau "terrain"
*/
char lecture_du_terrain (niveau_t* niveau,int colonne,int ligne){
  return niveau->terrain[ligne*niveau->nb_colonnes+colonne];
}


/*
*Retourne le caractère du tableau "terrain" en fonction de la direction demandée et du nombre de cases plus loin 
*(dans le cas où il faut vérifier si un obstacle nous empêche de pousser une caisse ou non par exemple)
*/
char lecture_terrain_direction(niveau_t* niveau, char direction, int nb_case){
  switch(direction){
    case 'z': return lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-nb_case);
    break;
    case 's': return lecture_du_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+nb_case);
    break;
    case 'q': return lecture_du_terrain(niveau, niveau->perso->colonne-nb_case, niveau->perso->ligne);
    break;
    case 'd': return lecture_du_terrain(niveau, niveau->perso->colonne+nb_case, niveau->perso->ligne);
    break;
  }
  return niveau->ancienne_case;
}

/*
*Initialise le terrain selon le niveau 
*/
void initialise_le_terrain (niveau_t* niveau){
  for(int i=0; i<niveau->nb_lignes; i++){
    for(int j=0; j<niveau->nb_colonnes; j++){
      place_sur_terrain(niveau, j, i, '#');
    }
  }
}

/*
*Affiche le terrain précédemment initialisé
*/
void affichage_niveau (niveau_t* niveau){
  system("clear");
  for(int i=0; i<niveau->nb_lignes; i++){
    for(int j=0; j<niveau->nb_colonnes; j++){
      printf("%c",lecture_du_terrain(niveau, j, i));
    }
    printf("\n");
  }
  printf("\n");
}

/*
*Libère la mémoire occupée
*/
void liberation_du_niveau (niveau_t* niveau){
  free(niveau->terrain);
  free(niveau->perso);
  free(niveau);
}

/*
*lecture du fichier niveau spécifié
*/
niveau_t* lecture_du_niveau(int nb_niveau)
{
  char chaine[30];
  sprintf(chaine, "Niveaux/niveau_%d", nb_niveau);
  FILE* fichier = fopen(chaine,"r");
  int colonne = 1;
  int indice = 0;
  char car = getc(fichier);
  while(car != ' '){
    colonne = colonne*(indice*10)+car-'0';
    indice = 1;
    car = getc(fichier);
  }
  car = getc(fichier);
  int ligne = 0;
  indice = 0;
  while(car != '\n'){
    ligne = ligne * (indice * 10) + car - '0';
    indice = 1;
    car = getc(fichier);
  }
  niveau_t* niveau = nouveau_niveau(colonne, ligne);
  for (int l = 0; l < ligne; l++){
    for (int c = 0; c < colonne; c++){
      car = getc(fichier);
      if(car == '\n')
        car = getc(fichier);
      if (car == '@')
      {
        niveau->perso->colonne = c;
        niveau->perso->ligne = l;
      }
      place_sur_terrain(niveau, c, l, car);
    }
  }
  fclose(fichier);
  return niveau;
}


/*
*retourne 1 si le jeu est fini
*/
int niveau_termine (niveau_t* niveau){
  for (int l = 0; l < niveau->nb_lignes; l++){
    for (int c = 0; c < niveau->nb_colonnes; c++){
      if(lecture_du_terrain(niveau, c, l)=='$')
        return 0;
    }
  }
  return 1;
}
