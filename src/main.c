#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "rlutil.h"
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"
#define TEMPSEGMIN 30
#define TEMPSEGMAX 70
#define MARGEMIN 1
#define MARGEMAX 20

int main(){
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	srand(time(NULL));
	
	printf("Ivan Fernàndez Montalvo\n");

	int tempSeg,marge, numGenerat, tempMin, tempMax, tempTotal=0, hora=0, risc=0, lecturaZona1=0, lecturaZona2=0,
	tempZona1=0, tempZona2=0, lecturaNova, tempZona3=0, lecturaZona3=0,lecturaPromig=0;
	float mitjana, mitjanaZona1, mitjanaZona2, mitjanaZona3; 
	bool sortir=false;

	do{
		printf("\nIntrodueix la temperatura de control (30..70): \n");
		scanf("%d",&tempSeg);
	}while(tempSeg>TEMPSEGMAX || tempSeg<TEMPSEGMIN);

	do{
		printf("Introdueix el marge (1..20): \n");
		scanf("%d",&marge);
	}while(marge>MARGEMAX || marge<MARGEMIN);

	printf("Temperatura de control: %d\n",tempSeg);
	printf("Marge de seguretat: %d\n",marge);

	int meitatMarge=marge/2;
	int tempMaxZ1=tempSeg-meitatMarge;
	int tempMaxZ2=tempSeg+meitatMarge;


	printf("Zona 1: 00 fins %d \n", tempMaxZ1);
	printf("Zona 2: %d fins %d \n",tempMaxZ1+1, tempMaxZ2);
	printf("Zona 3: %d fins 100\n\n", tempMaxZ2+1);

	printf("COMENÇAMENT DE LES LECTURES DEL REACTOR...\n\n");
	
	int lecturaInicial;

	do{
		printf("Introdueix la lectura inicial del reactor [0..%d]: \n",tempMaxZ2);
		scanf("%d",&lecturaInicial);
	}while(lecturaInicial<0 || lecturaInicial>tempMaxZ2);

	//colors
		if(lecturaInicial<=tempMaxZ1){
			setColor(LIGHTGREEN);
			tempZona1=tempZona1+lecturaInicial;
			lecturaZona1++;
		}else if(lecturaInicial>tempMaxZ1 && lecturaInicial<=tempMaxZ2){
			setColor(YELLOW);
			tempZona2=tempZona2+lecturaInicial;
			lecturaZona2++;
		}else{
			setColor(LIGHTRED);
		}

	printf("Hora [00]: %d\n",lecturaInicial);

	tempMax=lecturaInicial;
	tempMin=lecturaInicial;
	
	while(hora<=23 && sortir==false)
	{
		numGenerat = rand() % 11 - 5;//genero un rand entre 5 i -5
		lecturaNova=lecturaInicial+numGenerat;

		//per guardar temperatura maxima i minima
		if(lecturaNova>tempMax)
		{
			tempMax=lecturaNova;
		}else if(lecturaNova<tempMin)
		{
			tempMin=lecturaNova;
		}

		//colors
		if(lecturaNova<=tempMaxZ1){
			setColor(LIGHTGREEN);
			tempZona1=tempZona1+lecturaNova;
			lecturaZona1++;
			lecturaZona3=0;
		}else if(lecturaNova>tempMaxZ1 && lecturaNova<=tempMaxZ2){
			setColor(YELLOW);
			tempZona2=tempZona2+lecturaNova;
			lecturaZona2++;
			lecturaZona3=0;
		}else{
			setColor(LIGHTRED);
			tempZona3=tempZona3+lecturaNova;
			lecturaZona3++;
			lecturaPromig++;
		}
			
		

		if(lecturaZona3==3){
			sortir=true;
		}
		
		//per printar correctament si baixa de 0
		if(lecturaNova<0){
			tempMin=0;
			lecturaNova=0;
			printf("Hora [%02d]: %d\n",hora,lecturaNova);
		}else{
			printf("Hora [%02d]: %d\n",hora,lecturaNova);
		}
		lecturaInicial=lecturaNova;
		tempTotal=tempTotal+lecturaNova;
		hora++;
	}
	tempTotal=tempTotal+lecturaInicial;
	mitjana=(float)tempTotal/(float)hora;
	mitjanaZona1=(float)tempZona1/(float)lecturaZona1;
	mitjanaZona2=(float)tempZona2/(float)lecturaZona2;
	mitjanaZona3=(float)tempZona3/(float)lecturaPromig;


	if(risc==3){
		setColor(RED);
		printf("\nALERTA SISTEMA EN RISC.\n");
	}else{
		setColor(GREEN);
		printf("\nPROCÉS ACABAT CORRECTAMENT.\n");
	}

	setColor(GREY);
	printf("\nRESUM DEL SISTEMA:\n");
	printf("Temperatura màxima del reactor: %d\n",tempMax);
	printf("Temperatura mínima del reactor: %d\n\n",tempMin);
	printf("Temperatura mitjana del reactor: %.2f\n\n",mitjana);

	if(lecturaZona1>0 ){
		printf("Promig lectures zones de no risc: %.2f\n", mitjanaZona1);
	}else{
		printf("No s'ha produit cap valor en la zona de no risc.\n");
	}

	if(lecturaZona2>0){
		printf("Promig lectures zones de seguretat: %.2f\n", mitjanaZona2);
	}else{
		printf("No s'ha produit cap valor en la zona seguretat.\n");
	}

	if(lecturaPromig>0){
		printf("Promig lectures zones de risc: %.2f\n", mitjanaZona3);
	}else{
		printf("No s'ha produit cap valor en la zona de risc.\n");
	}



	






	acabament();
	return 0;
}
