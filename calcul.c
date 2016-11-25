int occ[6]={0,0,0,0,0,0};
int Calcul_Score(){
	int total=0;
	switch(Categorie){//choix score a utiliser
		
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 ://fonction qui calcule le score pour les dé de un a six
			int i;
			int occ[6]={0,0,0,0,0,0};
			for(i=0;i<5;i++){
				occ[De[i]-1]++;
			}
			total=Categorie*occ[Categorie];
			Score[Categorie]=total;
			break;
			}
			
		case 7:
			if(isBrelan()){
				total=de[0]+De[1]+De[2]+De[3]+De[4]+De[5];
				Score[7]=total;
				break;
			}
		case 8:
			if(isCarre()){
				total=De[0]+De[1]+De[2]+De[3]+De[4]+De[5];
				Score[8]=total;
				break;
			}
		case 9:
			if(isFull()){
				total=25;
				Score[9]=total;
				break;
			}
		case 10:
			if(isPtSuite()){
				total=30;
				Score[10]=total;
				break;
			}
		case 11:
			if(isGdSuite()){
				total=40;
				Score[11]=total;
				break;
			}
		case 12:
			if(isYahtzee()){
				total=50;
				Score[12]=total;
				break;
			}
		case 13://case chance
			total= De[0]+De[1]+De[2]+De[3]+De[4]+De[5];
			Score[13]=total;
			break;
		
		
	}
}	
