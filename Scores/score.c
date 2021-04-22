#include "main.h"
/*
*retourne l'entier qui correspond au meilleur nombre de pas pour le niveau spécifié en paramètres
*/
int lecture_du_score (int quel_niveau,char* chemin){
  char chaine[30];
  sprintf(chaine, "Scores/%s_%d",chemin, quel_niveau);
  FILE* fichier = fopen(chaine,"r");
  int indice = 0;
  int score=0;
  char car = getc(fichier);
  while(car != EOF && car != '\n'){
    score = score*(indice*10)+car-'0';
    indice=1;
    car = getc(fichier);
  }
  return score;
}

/*
*affichage des 5 meilleurs scores et le nom des joueurs
*/
void top_score(char quel_niveau,char* chemin){
  char* chaine = malloc(sizeof(char)*100);
  sprintf(chaine, "Scores/%s_%c",chemin, quel_niveau);
  FILE* fichier = fopen(chaine,"r");
  char c;
  printf("\tScore\t|\tNom\n________________|__________________\n");
  printf("\t");
  while((c=fgetc(fichier))!=EOF){
    if(c!=' '){
      printf("%c",c);
      if(c=='\n'){
        printf("\t");
      }
    }else{
      printf("\t|\t");
    }
  }
  printf("\n");
  fclose(fichier);
  free(chaine);
}

/*
*écrit le score donné dans le fichier score 
*/
void ecriture_du_score (int quel_niveau,int score){
  char chaine[30];
  sprintf(chaine, "Scores/score_%d", quel_niveau);
  FILE* fichier = fopen(chaine,"w");
  fprintf(fichier,"%d",score);
	fclose(fichier);
}

/*
*ajoute le score et le nom dans le fichier score multi correspondant
*/
void ajouter_score(char* nom,int score,int choix_niveau){
  char chaine[30];
  sprintf(chaine, "Scores/score_multi_%d", choix_niveau);
  FILE* fichier = fopen(chaine,"a");
  char personne[15];
  sprintf(personne,"%d %s\n",score,nom);
  fputs(personne, fichier);
	fclose(fichier);
}

/*
*un seul pseudo par niveau et trier et exporter le résultat dans le fichier
*/
void pseudo_unique_tri (char* nom,int choix_niveau){
  char chaine[200];
  sprintf(chaine,"(grep -i %s Scores/score_multi_%d | sort -n | head -n 1 && grep -v %s Scores/score_multi_%d) | sort -n -o Scores/score_multi_%d ",nom,choix_niveau,nom,choix_niveau,choix_niveau);
  system(chaine);
}

/*
*retourne le cinquieme score du niveau qui est stocké dans le fichier 5e_score
*/
int cinquieme_score (int choix_niveau){
  char chaine[100];
  sprintf(chaine,"grep -o [0-9]* Scores/score_multi_%d |head -n 5 | tail -n 1 > Scores/5_score_%d",choix_niveau,choix_niveau);
  system(chaine);
  return lecture_du_score(choix_niveau,"5_score");
}

/*
*retourne le nombre de ligne dans le score multi du niveau choisi
*/
int nb_ligne (int choix_niveau){
  char chaine[80];
  sprintf(chaine, "cat Scores/score_multi_%d | wc -l > /dev/null", choix_niveau);
  return system(chaine);
}

/*
*garde seulement 5 scores dans le fichier 
*/
void seulement_5_score(int choix_niveau){
  char chaine[100];
  sprintf(chaine,"head -n 5 Scores/score_multi_%d| sort -n -o Scores/score_multi_%d",choix_niveau,choix_niveau);
  system(chaine);
}