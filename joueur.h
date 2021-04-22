char entree_du_joueur (void);
void deplacement(niveau_t* niveau, char direction, char ancienne_case);
void avancer(niveau_t* niveau,char obstacle,char direction, char car);
void avancer_caisse (niveau_t* niveau,char direction,char car);
char* nom_du_joueur (void);
int size(char* nom);
int libere_nom (char* nom);