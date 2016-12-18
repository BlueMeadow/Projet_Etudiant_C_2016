#include "./Global.h"

/**
* \file Score.c
* \brief Permet de calculer les combinaisons de dés et les scores
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/

int isBrelan()
/* \fn isBrelan()
* \brief Fonction booléenne calculant la présence d'un brelan dans les dés
* \return VRAI s'il y a un brelan
*/
{
	int i;
	for( i = 0; i < 6 ; i++)
	{
		if (Occurrences[i] > 2)
			return 1;
	}
	return 0;
}

int isCarre()
/* \fn
* \briefFonction booléenne calculant la présence d'un carré dans les dés
* \return VRAI s'il y a un carré
*/
{
	int i;
	
	for( i = 0; i < 6 ; i++)
	{
		if (Occurrences[i] > 3)
			return 1;
	}
	return 0;		
}

int isYahtzee()
/* \fn
* \brief Fonction booléenne calculant la présence d'un brelan dans les dés
* \return VRAI s'il y a un brelan
*/
{
	for (int i=0; i < 6; i++){
		if ( Occurrences[i] == 5){
			return 1;
		}
	}
	return 0;
}

int isFull()
/* \fn
* \brief Fonction booléenne calculant la présence d'un full dans les dés
* \return VRAI s'il y a un brelan et une paire ( pas nécessairement de valeurs différentes )
*/
{

	int i, cpt2 = 0, cpt3 = 0;

	for( i = 0 ; i < 6 ; i++)
	{		
		if( Occurrences[i] == 2 )
			cpt2 = 1;
		else if( Occurrences[i] == 3 )
			cpt3 = 1;
	}
	if (cpt2 == 1 && cpt3 == 1)
		return 1;
	return (isYahtzee());	/**< Un Yahtzee est considéré comme un Full */
}



int isPtSuite()
/* \fn
* \brief Fonction booléenne calculant la présence d'une petite suite dans les dés
* \return VRAI si les valeurs de quatre dés se suivent
*/
{

	int i;
	for( i = 0 ; i <= 2 ; i++){
		if(Occurrences[i] > 0 && Occurrences[i+1] > 0 && Occurrences[i+2] > 0 && Occurrences[i+3] > 0)
			return 1;
	}
	return 0;
}

int isGdSuite()
/* \fn
* \brief Fonction booléenne calculant la présence d'une grande suite dans les dés
* \return VRAI si les valeurs de cinq dés se suivent
*/
{
	int i;
	
	for(i = 0; i < 1; i++)
	{
		if ((Occurrences[i] > 0) && (Occurrences[i+1] > 0) && (Occurrences[i+2] > 0) && (Occurrences[i+3] > 0) && (Occurrences[i+4] > 0))
			return 1;
	}
	return 0;
}


