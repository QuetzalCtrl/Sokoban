#include "main.h"

int main(int argc, char *argv[]) {
  system("clear");
  int exit = 1;
  char choix_menu='0';
  int choix_niveau;
  char choix_car;
  int replay = 0;
  int nb_essais = 1;
  int coups_a_annuler = 15;
  historique_t* hist;
  while(exit!=0){
    if(choix_menu!='1'){//si le joueur ne veut pas rejouer au même niveau, alors il choisit son niveau, sinon on ne rentre pas dans le if et le choix_niveau reste le même
      printf("\n\t\t\t\t倉庫番\n\t\t\t  LE JEU DU SOKOBAN\n\n");
    
      //demande quel niveau au joueur
      printf("Choix du niveau (0, 1 ou 2) : \n\n0 - Facile\n1 - Intermédiare\n2 - Extrême de la mort qui tue \n\n3 - Quitter le jeu\n\n> ");
      do{
        scanf("%c", &choix_car);
      }while(choix_car != '0' && choix_car!= '1' && choix_car!= '2' && choix_car!= '3');
      if(choix_car=='3'){
        system("clear");
        return 0;
      }
      choix_niveau = choix_car - '0';
      nb_essais = 1;
    }
    
    niveau_t* niveau = lecture_du_niveau(choix_niveau);
    char direction;
    hist = nouvel_historique(coups_a_annuler);
    replay = 0;
    coups_a_annuler = 15;
    
    //tant que le niveau n'est pas terminé ou que le joueur ne veut pas recommencer
    while (niveau_termine(niveau)!=1 && replay ==0){       
      system("clear");
      printf("%d", choix_niveau);
      printf("\n");
      //affiche le niveau
      affichage_niveau(niveau);
      //affiche ne nombre de pas
      printf("Nombre de pas : %d\tNombre d'essais : %d\tCoups restants à annuler : %d\n",niveau->nb_de_pas, nb_essais, coups_a_annuler);

      //demande la direction
      direction = entree_du_joueur();
      switch(direction){
        case 'r' : 
          replay = 1;
          choix_menu = '1';
          nb_essais++;
        break;
        case 'm' : 
          replay = 1;
          choix_menu = '0';
        break;
        case 'a' :
          if (coups_a_annuler!=0 && niveau->nb_de_pas!=0){
            niveau = coup_precedent(hist);
            //sauvegarde la case avant de deplacer le joueur
          niveau->case_a_sauvegarder=lecture_terrain_direction(niveau, direction,1);
            coups_a_annuler--;
          }
        break;
        case 'z':
        case 'q':
        case 's':
        case 'd':
          // Sauvegarde de l'état du niveau
          sauvegarde_un_coup(hist, niveau);
            //sauvegarde la case avant de deplacer le joueur
          niveau->case_a_sauvegarder=lecture_terrain_direction(niveau, direction,1);
          //déplace le joueur
          deplacement(niveau, direction, niveau->ancienne_case);
          //incrémente le compteur de pas
          niveau->nb_de_pas++;
        break;     
      }
      //sauvegarde de la case précédente
      if(niveau->case_a_sauvegarder!='#' && niveau->case_a_sauvegarder!='$'){
        niveau->ancienne_case=niveau->case_a_sauvegarder;
      }
      if (niveau->case_a_sauvegarder=='*') {
        niveau->ancienne_case='.';
      }
      if(niveau->case_a_sauvegarder=='$'||niveau->case_a_sauvegarder=='@'){
        niveau->ancienne_case=' ';
      }
    }
    if(replay == 0){
      system("clear");
      affichage_niveau(niveau);
      libere_historique(hist);
      printf("Bravo, tu as terminé le niveau en %d pas, du %de essai !\n\n",niveau->nb_de_pas, nb_essais);
      
      
      //si il n'y a pas encore 5 scores ou si il a un score plus petit que les 5 premiers de son niveau 
      if (niveau->nb_de_pas < cinquieme_score(choix_niveau) || nb_ligne(choix_niveau)<5){
        //vérifie si il a obtenu le meilleur score
          if(lecture_du_score(choix_niveau,"score")>=niveau->nb_de_pas){
            ecriture_du_score(choix_niveau, niveau->nb_de_pas);
          }
            printf("Féliciations ! Tu t'es inscrit dans le top 5 des scores pour ce niveau !\n");
            char* nom;
            nom =nom_du_joueur();
            //ajoute le score du joueur dans le fichier avec tous les scores correspondant au niveau choisi
            ajouter_score(nom,niveau->nb_de_pas,choix_niveau);
            //un seul pseudo apparait et les moins bons scores de cette personne sont effacés puis on effectue un tri
            pseudo_unique_tri (nom, choix_niveau);
            //on laisse seulement les 5 meilleurs scores
            seulement_5_score( choix_niveau);
            //libère nom
            libere_nom(nom);
            printf("\n");
      }
      printf("Voici le tableau des 5 meilleurs scores pour le niveau %c :\n\n", choix_car);
      top_score(choix_car, "score_multi");
      liberation_du_niveau(niveau);
      nb_essais = 1;
      
      printf("Que voulez-vous faire ?\n\n");
      printf("0 - Retour au menu principal\n");
      printf("1 - Rejouer ce niveau\n\n");
      printf("2 - Quitter le jeu\n\n> ");
      do{
          scanf("%c", &choix_menu);
      }while(choix_menu != '0' && choix_menu!= '1' && choix_menu!='2');
      if(choix_menu=='2'){
        exit = 0;
      }
    }else{
      liberation_du_niveau(niveau);
    }
    
    
    system("clear");
  }

  return 0;
}