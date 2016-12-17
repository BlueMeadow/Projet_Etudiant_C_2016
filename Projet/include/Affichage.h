#ifndef H_Affichage
#define H_Affichage

void EcranTitre();
void MiseEnPlace();
void FicheDeScore(WINDOW *Fenetre, int y, int x);
void DeUn(WINDOW *Fenetre, int y, int x);
void DeDeux(WINDOW *Fenetre, int y, int x);					
void DeTrois(WINDOW *Fenetre, int y, int x);					
void DeQuatre(WINDOW *Fenetre, int y, int x);				
void DeCinq(WINDOW *Fenetre, int y, int x);					
void DeSix(WINDOW *Fenetre, int y, int x);
void DeVide(WINDOW *Fenetre, int y, int x);
void AffichageDe(int De[5], WINDOW *Fenetre);

#endif
