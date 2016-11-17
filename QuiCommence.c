void QuiCommence(){
	int joueur;
	int max=0;
	int retient;
	for(joueur=1;joueur<nb_joueur;joueur++){
		lancer();
		if(max<lancer){
			max=lancer;
			retient=joueur;
		}
	}
	printf("le joueur %i ayant fais le plus gros score c'est lui qui commence",retient);
	return retient;
}