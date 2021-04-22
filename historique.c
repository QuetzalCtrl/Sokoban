#include "main.h"

/*
*Crée un nouvel historique
*/
historique_t* nouvel_historique(int nb_niv){
	historique_t* hist = malloc(sizeof(historique_t*));
	hist->taille = nb_niv;
	hist->tableau = malloc(sizeof(niveau_t) * nb_niv);
	for (int i = 0; i < hist->taille; i++){
		hist->tableau[i] = malloc(sizeof(niveau_t));
	}
	return hist;
}

/*
*Libère l'historique
*/
void libere_historique(historique_t* hist){
	for(int i = 0; i<hist->taille; i++){
		*(hist->tableau+i)=NULL;
	}
	free(hist->tableau);
	free(hist);
}

/*
*Sauvegarde un coup
*/
void sauvegarde_un_coup(historique_t* hist, niveau_t* niveau){
	*(hist->tableau + hist->taille) = copie_du_niveau(niveau);
	hist->taille++;
}

/*
*Revenir en arrière dans l'historique
*/
niveau_t* coup_precedent(historique_t* hist){
	hist->taille--;
	return copie_du_niveau(hist->tableau[hist->taille]);
}


/*
* retourne une copie du niveau passé en paramètre
*/
niveau_t* copie_du_niveau (niveau_t* niveau)
{
  niveau_t* copie=malloc(sizeof(niveau_t));
  copie->terrain=malloc(sizeof(char)*niveau->nb_lignes*niveau->nb_colonnes);
  copie->perso=malloc(sizeof(point_t));
  copie->nb_de_pas=niveau->nb_de_pas;
  copie->nb_lignes=niveau->nb_lignes;
  copie->nb_colonnes=niveau->nb_colonnes;
  for(int i=0; i<niveau->nb_lignes*niveau->nb_colonnes; i++){
    *(copie->terrain+i)=*(niveau->terrain+i);
  }
  copie->perso->ligne=niveau->perso->ligne;
  copie->perso->colonne=niveau->perso->colonne;
  copie->case_a_sauvegarder = niveau->case_a_sauvegarder;
  copie->ancienne_case = niveau->ancienne_case;
  return copie;
}