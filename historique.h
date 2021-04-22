historique_t* nouvel_historique(int);
void libere_historique(historique_t* hist);
void sauvegarde_un_coup(historique_t* hist, niveau_t* niveau);
niveau_t* coup_precedent(historique_t* hist);
niveau_t* copie_du_niveau (niveau_t* niveau);