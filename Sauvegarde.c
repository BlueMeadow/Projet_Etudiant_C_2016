#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TabOccurrences[6]={0}; 
int Score[4][13]={{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
int De[5]={0,0,0,0,0};
int Garde[5]={0};
int NbJoueur = 3;
char PseudoJ[4][10];
char Pseudos[40];
int Joueur=0;
int nb_tour=0;
int nb_lancers=1;
int isAide[4]={0};
void Aide(int isAide[], int Joueur);

%i


void Sauvegarder()
{
	FILE * Sauvegarde = NULL;
	int i;
	int j;
	char NomFichier[10] = "sav_";
	char temp[4];
	char NumSav[2]; // Jusqu'à 99 sauvegardes
	strcpy(temp, NomFichier);
	NumSav[1] = '1'; // Code ASCII du caractère 1
	NumSav[0] = '0'; // Code ASCII du caractère 0
	strcat(NomFichier, NumSav);
	if (NumSav[1] == 48)
		NumSav[1]++;
	/* Vérification du numéro de sauvegarde à attribuer */
	for (i = 0; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			Sauvegarde = fopen(NomFichier, "r");
			if (Sauvegarde != NULL)
			{
				fclose(Sauvegarde);
				strcpy(NomFichier, temp);
				NumSav[1]++;
				if (NumSav[1] > '9')
				{
					NumSav[1] = '0';
					NumSav[0]++;
				}
				strcat(NomFichier, NumSav);
				printf("\n%s\n\n", NomFichier);
			}
			else break; 
			/* Si le fichier n'existe pas, on sort des boucles de vérification */
		}
		if (Sauvegarde == NULL) break; 
		/* Si le fichier n'existe pas, on sort des boucles de vérification */
	}
	Sauvegarde = fopen(NomFichier, "w");
	fclose(Sauvegarde);
	fprintf( 
			
}

int main() 
{
	Sauvegarder();
}
	


