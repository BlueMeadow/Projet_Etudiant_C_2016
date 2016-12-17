#ifndef H_Score
#define H_Score

int isBrelan();
int isCarre();
int isYahtzee();
int isFull();
int isPtSuite();
int isGdSuite();
void CalculScore(int Joueur, int Categorie);
void ChoixCategorie (int *Categorie, WINDOW *Fenetre, int Joueur);
void EcrireScore(int Joueur);

#endif
