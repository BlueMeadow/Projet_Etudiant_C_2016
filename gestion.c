//Conception

//Structures de données : 


int De[5] /* stock les résultats des 5 dés */
int Garder[5] /* tableau de booléens, permet de savoir si on veut relancer les dés */
int Score[13][4] /* Garde le score de chaque joueur */

//Découpage fonctionnel : 

void Partie() /* Rassemble toutes les fonctions et permet de faire une partie de Yahtzee */
Boucle jusqu'à 13 (parce que 13 catégorie)



int ChangerJoueur(int Joueur) /* Change de joueur */

void FicheDeScore() /* Affiche une fiche de score vide */

void Lancer(int De[5], int Garder[5]) /* Lance les dés qu'un ne souhaite pas garder, tous au premier lancer */

void Garde(int Garder[5]) /* change la valeur des booléens selon si on veut garder les dés ou non */

void AffichageDe(int De[5]) /* Dessine les dés en utilisant les fonctions De_Un, De_Deux… */

void De_Un() /* Dessine un De de valeur 1, même fonctions pour les autres valeurs de dés */

void Calcul_Score(int Score[13][4]) /* Calcule le score pour chaque case pour un lancer donné, utilise  */

int isBrelan(De[5]) /* Renvoie 1 si les dés forment un brelan, 0 sinon. Même fonction pour le carré, le full, la petite et grande suite et le yahtzee */

void Mise_A_Jour(int Score[13][4], int Num_joueur) /* Met à jour la valeur du score dans la fiche, en utilisant  gotoxy et le tableau rendu par Calcul_Score*/


