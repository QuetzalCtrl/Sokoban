#include "main.h"

/*
*Retourne un caractère entré par le joueur et attend que celui-ci saisisse z, q, s ou d
*/
char entree_du_joueur (void){
  char direction;
  printf("\nActions possibles :\nz --> haut\tq --> gauche\ts --> bas\td --> droite\ta --> annuler le coup\nr --> rejouer le niveau\t\tm --> revenir au menu principal\n\n> ");
  while (direction != 'z' && direction !='d' && direction != 'q' && direction != 's' && direction != 'a' && direction != 'r' && direction != 'm'){
    scanf(" %c", &direction);
  }
  return direction;
}


/*
*Déplace le personnage en prenant en compte les bordures du niveau
*/
void deplacement(niveau_t* niveau, char direction, char ancienne_case){
  char case_apres=lecture_terrain_direction(niveau, direction, 1);
  char deux_cases=lecture_terrain_direction(niveau, direction, 2);// on vérifie le char qui est 2 cases plus loin que le joueur
  switch(case_apres){
    case ' ': avancer(niveau,ancienne_case,direction,'@');
    break;
    case '.':  avancer(niveau,ancienne_case,direction,'+');
    break;
    case '#': niveau->nb_de_pas--;//on annule l'incrémentation des pas car on ne peut pas se déplacer
    break;
    case '$': case '*': 
      switch(deux_cases){//un switch dans un switch ¯\_(ツ)_/¯
        case '.': 
          if(case_apres == '$'){
            avancer(niveau,ancienne_case, direction,'@'); // avance le personnage en restant @
          }else{
            avancer(niveau,ancienne_case, direction,'+');// avance le personnage et le remplace par un + car il sera sur un point
          }
          avancer_caisse(niveau, direction, '*'); // avance la caisse et transforme le $ par un * car elle est maintenant sur un point
        break;
        case ' ':
          if(case_apres=='$'){
            avancer(niveau,ancienne_case, direction,'@'); //avance le personnage normalement
          }else if(case_apres=='*'){
            avancer(niveau,ancienne_case, direction,'+'); //avance le personnage et le remplace par un + car il sera sur un point
          }
          
          avancer_caisse(niveau, direction, '$'); // avance la caisse normalement
        break;
        default: 
          niveau->nb_de_pas--; //dans tous les autres cas, on ne pousse pas la caisse pas et on on annule l'incrémentation des pas
        break;
      }
    break;
  }
}

/*
*fait avancer le personnage, remplaçant son ancienne position par ancienne_case et le modifie en @ ou + selon le car en paramètre
*/
void avancer(niveau_t* niveau,char ancienne_case,char direction, char car){
  place_sur_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne, ancienne_case);
  switch(direction){
    case 'z': niveau->perso->ligne--;
    break;
    case 'q': niveau->perso->colonne--;
    break;
    case 's': niveau->perso->ligne++;
    break;
    case 'd': niveau->perso->colonne++;
    break;
  }
  place_sur_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne,car);
}

/*
*avance la caisse dans le direction demandé, et le modifie en $ ou * selon le car en paramètre
*/
void avancer_caisse (niveau_t* niveau,char direction,char car){
  switch(direction){
    case 'z': place_sur_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne-1,car);
    break;
    case 'q': place_sur_terrain(niveau, niveau->perso->colonne-1, niveau->perso->ligne, car);
    break;
    case 's': place_sur_terrain(niveau, niveau->perso->colonne, niveau->perso->ligne+1, car);
    break;
    case 'd': place_sur_terrain(niveau, niveau->perso->colonne+1, niveau->perso->ligne, car);
    break;
  }
}

/*
*Retourne le nom entré par le joueur
*/
char* nom_du_joueur (void){
  int length;
  char* nom = malloc(sizeof(char)*8);
  do{
    printf("Rentre ton nom (max. 8 caractères) : ");
    scanf("%s", nom);
    length=size(nom);
  }while(length>8); // tant que la taille du nom est plus grande que 8 on redemande
  return nom;
}

/*
*retourne la taille du nom passé en paramètre
*/
int size(char* nom){
  int idx=0;
  while(*(nom+idx)!='\0'){
    idx++;
  }
  return idx;
}

/*
*libère la mémoire
*/
int libere_nom (char* nom){
  free(nom);
  return 1;
}