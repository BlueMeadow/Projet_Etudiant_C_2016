#include "../Projet/include/Global.h"

/** DEBUG PROBLEME DE NOM DE FICHIER CAUSANT UN CORE DUMPED */

int Charger()

{
	FILE * Sauvegarde = NULL;
	int i;
	int j;
	int y = 1, x = 0, ch;
	int NbSav = 0;
	char SavTable[100][3];
	char NomFichier[10] = "sav_"; /**< Début de nom ommun à toutes les sauvegardes */
	char temp[4];  	/**< Garde le début du nom de fichier après modifcation */
	char NumSav[3]; /**< Jusqu'à 99 sauvegardes */	

	strcpy(temp, NomFichier);
	NumSav[2] = '\0';	

	/** Recherche des sauvegardes */

	for ( i = 1 ; i < 100 ; i++ )
	{
		NumSav[1] = i%10+48; /**< Code ASCII du chiffre des unités */
		NumSav[0] = i/10+48; /**< Code ASCII du chiffre des dizaines */

		strcat(NomFichier, NumSav); /**< Donne le nom du fichier à rechercher */
		Sauvegarde = fopen(NomFichier, "r");/**< Vérification de l'existence */
		if ( Sauvegarde != NULL ) /**< Si le fichier existe */
		{	
			strcpy(SavTable[NbSav], NumSav); /**< Garde le numéro en mémoire */
			NbSav++;
			fclose(Sauvegarde); /**< Passe au suivant */
			printf("%s", NomFichier);
		}
		strcat(NomFichier, temp);
	}			
		return 1;
}

int main()
{
	Charger();
}

