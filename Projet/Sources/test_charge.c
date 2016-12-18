#include "../include/Global.h"

int main()
{
	FILE * Sauvegarde = NULL;
	int i;
	int j;
	int y = 1, x = 0, ch;
	int NbSav = 0;
	char SavTable[100][3];
	char NomFichier[10] = "sav_";
	char temp[4]; 
	/* Garde le début du nom de fichier après modifcation */
	char NumSav[3]; 
	/* Jusqu'à 99 sauvegardes */

	

	strcpy(temp, NomFichier);
	NumSav[2] = '\0';
	/* Recherche des sauvegardes */
	for ( i = 1 ; i < 30 ; i++ )
	{
		NumSav[1] = i%10+48; 
		/* Code ASCII du chiffre des dizaines */
		NumSav[0] = i/10+48; 	
		/* Code ASCII du chiffre des unités */

		strcat(NomFichier, NumSav);
		/* Donne le nom du fichier à rechercher */
		Sauvegarde = fopen(NomFichier, "r");
		/* Vérification de l'existence */
		if ( Sauvegarde != NULL )
		{	
			strcpy(SavTable[NbSav], NumSav);
			NbSav++;
			fclose(Sauvegarde);
		}
		strcpy(NomFichier, temp);
	}
	return 1;
}

