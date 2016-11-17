#include <stdio.h>
#include <stdlib.h>
int De[5]={3,3,6,5,4};

int isCarre(){
	int i;
	int j;
	int total = 0;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(De[i]==De[j] && i!=j){//i!=j pour qu'il ne compte pas si les deux sont sur la meme case
				total++;
			}
		}
		if(total==3){
			return 1;

		}
		total=0;
	}
	return 0;
}

int isPtSuite(){
	int i;
	int j;
	int occ[6]={0,0,0,0,0,0};//compte le nombre d'occurence
	for(i=0;i<5;i++){
		occ[De[i]-1]++;
	}
	for(j=0;j<=2;j++){
		if(occ[j]>0 && occ[j+1] >0 && occ[j+2]>0 && occ [j+3]>0)
			return 1;
	
	}
	return 0;
}	

int isGdSuite(){
	int i;
	int j;
	int occ[6]={0,0,0,0,0,0};
	for(i=0;i<5;i++){//compte le nombre d'occurence
		occ[De[i]-1]++;
	}
	for(j=0;j<1;j++){
		if(occ[0]==1){//pour trouver si il y a un 1
			if(occ[j]>0 && occ[j+1] >0 && occ[j+2]>0 && occ [j+3]>0 && occ[j+4]>0){
				return 1;
			}
		}else{
			if(occ[j+1]>0 && occ[j+2] >0 && occ[j+3]>0 && occ [j+4]>0 && occ[j+5]>0){//pour trouver si il y a un six
				return 1;
			}
		}
	}
	return 0;
}		
int main(){
	isGdSuite(); 
}
	