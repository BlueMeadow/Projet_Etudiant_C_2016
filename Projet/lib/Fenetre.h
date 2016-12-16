#ifndef H_Fenetre
#define H_Fenetre

WINDOW *CreerFenetre(int Hauteur, int Longueur, int DebutY, int DebutX);
void Nettoyer(WINDOW * Fenetre, int DebutY, int DebutX, int FinY, int FinX);
void DetruireFenetre(WINDOW * Fenetre);

#endif
