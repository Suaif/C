/*
	ISMAEL G�MEZ GARRIDO 
	GROUP 31
	BACHELOR'S DEGREE IN INDUSTRIAL TECHNOLOGY ENGINEERING
*/

/*
This program consist in the creation and management of a drone database

Each drone has some asociated characteristics
	- ID number
	- Model number
	- Model name
	- Price
	- Maximum flying high
	- Autonomy
	- Maximum weight
	- Last inspection date
	- Operation zones (Spanish autonomic regions)
	- Ratings of users

The application has the following functionalities:
	- Add drone to the fleet
	- Show drone fleet
	- Show total price of the fleet
	- Modify a drone's data
	- Show drones to inspection(Introducing the current date)
	- Show drones by region
	- Rate a drone
	- Show drones ordered by autonomy in a region
	- Show drones with the most autonomy (top n)

*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 50
#define REGIONS 15

char regions[15][30]={"Andalucia", "Aragon", "Principado de Asturias", "Cantabria", "Castilla La Mancha", "Castilla y Leon", "Catalunya", "Comunidad Valenciana", "Extremadura", "Galicia", "La Rioja", "Comunidad de Madrid", "Comunidad Foral de Navarra", "Pais Vasco", "Region de Murcia"};
struct typeDate{int day; int month; int year;};
struct typeUs{char name[20]; float rate; char comment[1000];};
struct typeDrone{
	int ID;
	char model [20];
	int price;
	float height;
	int autonomy;
	int weight;
	struct typeDate date;
	int zones[15];
	struct typeUs rating [30];
	int nRates;
	float AvgRating;
};
struct typeDrone fleet [TAM_MAX];
struct typeDrone leer (char regions [15][30]);
void mostrar (struct typeDrone drone, char regions[15][30], int a);
void assignOperationZones (struct typeDrone *drone, char regions [15][30]);
void showOperationZones (struct typeDrone drone, char regions [15][30], int a);
void showFleet (char regions [15][30], int n, struct typeDrone fleet[TAM_MAX]);
float fleetPrice (struct typeDrone fleet[TAM_MAX], int n);
void addDrone (struct typeDrone fleet[TAM_MAX], int *n, char regions [15][30]);
void modifyData (struct typeDrone fleet[TAM_MAX], int n, char comuniades[15][30]);
void showInspectionDrones (struct typeDrone fleet[TAM_MAX], int n);
void showRegionDrones (struct typeDrone fleet[TAM_MAX], int n, char regions [15][30]);
void rateDron (struct typeDrone fleet[TAM_MAX], int n);
int initializeDronesArray(struct typeDrone fleet[TAM_MAX]);
struct typeDrone droneFleet [TAM_MAX];
void sortFleet(struct typeDrone droneFleet[TAM_MAX], int n);

int main(int argc, char *argv[]) {
	int count, i, Ndrones=0, NdronesREG=0, a=-1, b;
	char com[30];
	for(i=0; i<TAM_MAX; i++){ fleet[i].nRates=0;}
	Ndrones=initializeDronesArray(fleet);
	do{
		printf("  ***MAIN MENU***\n 1 - Add delivery drone to the fleet\n 2 - Show dronw fleet\n 3 - Show total fleet price\n 4 - Modify drone's data\n 5 - Show drones to inspection\n 6 - Show drones by region\n 7 - Rate a drone\n 8 - Show drones sorted by autonomy and by region\n 9 - Show drones with greater autonomy\n 0 - Exit\n");
		scanf("%d", &count);
		switch (count){
			case 1:
				if(Ndrones>=TAM_MAX){printf("No more drones can be added to the fleet");}
				else { 
					addDrone(fleet, &Ndrones, regions);
				}
				break;
			case 2:
				showFleet(regions, Ndrones, fleet); 
				break;
			case 3: 
				for(i=0; i<Ndrones; i++){
					printf("	The price of the drone %d is %d\n", i+1, fleet[i].price);
				}
				printf("\nTotal price of the fleet is  %f\n", fleetPrice(fleet, Ndrones));
				break;
			case 4:
				modifyData(fleet, Ndrones, regions);
			    break;
			case 5:
				showInspectionDrones(fleet, Ndrones);
				break;
			case 6:
				showRegionDrones(fleet, Ndrones, regions);
				break;
			case 7:
				rateDron(fleet, Ndrones);
				break;
			case 8:
				for(i=0; i<15; i++){ printf("%i. %s \n", i+1, regions[i]);}
  				printf("Write the name of the autonomic region:	");
  				scanf(" %[^\n]", com);
  				for(i=0; i<15; i++){if((strcmp(regions[i], com))==0){a=i;}}
  				if((a>-1)&&(a<15)){
  					for(i=0; i<Ndrones; i++){
  	 	 				if(fleet[i].zones[a]==1) { droneFleet[NdronesREG]=fleet[i]; NdronesREG++;}
					}
					sortFleet(droneFleet, NdronesREG);
					showFleet(regions, NdronesREG, droneFleet);	
				}
				else{printf("You have not introduced the name of any autonomic region\n");}
				break;
			case 9:
				printf("Write the number of drones you would like to see	");
				scanf("%i", &b);
				for(i=0; i<Ndrones; i++){
					droneFleet[i]=fleet[i];
				}
				sortFleet(droneFleet, Ndrones);
				showFleet(regions, b, droneFleet);
				break;
		}
	} while(count!=0);
	printf("The program has ended\n");
	return 0;
}

void showOperationZones (struct typeDrone drone, char regions [15][30], int a){
  	int i=0;
  	printf("The operational zones of the drone %d are :\n", a+1);
	for (i=0; i<15; i++){
    	if(drone.zones[i]==1){
    		printf(" %s ", regions [i]);
		}
	}
     return;
  }
void assignOperationZones (struct typeDrone *drone, char regions[15][30]){
  int i, count, resp;
  for(i=0; i<15; i++){(*drone).zones[i]=0;}
  do{
  	 for(i=0; i<15; i++){
  	 	 printf("%i. %s \n", i+1, regions[i]);
  	 }
  	 printf("Select an autonomic region, write 0 to exit   ");
  	 scanf("%i", &resp);
  	 if(resp==0){count=1;}
	 if((resp>=1)&&(resp<=15)){
	 	count=0;
	 	(*drone).zones[resp-1]=1;
	 }
  }while(count==0);
  return;
  }
struct typeDrone leer (char regions [15][30]){
	struct typeDrone drone;
	printf("Introduce the ID	");
	scanf("%i", &drone.ID);
	printf("Introduce the model	");
	scanf(" %[^\n]", drone.model);
	printf("Introdce the price	");
	scanf("%i", &drone.price);
	printf("Introduce the maximum flying height	");
	scanf("%f", &drone.height);
	printf("Introduce the autonomy in minutes	");
	scanf("%i", &drone.autonomy);
	printf("Introduce the maximum weight in kilograms	");
	scanf("%i", &drone.weight);
	printf("Introduce the day of the last inspection	");
	scanf("%i", &drone.date.day);
	printf("Introduce the month of the last inspection	");
	scanf("%i", &drone.date.month);
	printf("Introduce the year of the last inspection	");
	scanf("%i", &drone.date.year);
	assignOperationZones (&drone, regions);
	
	return drone;
}
void mostrar (struct typeDrone drone, char regions [15][30], int a){
	int i;
	float s=0;
	printf("\n");
	printf("The ID of the drone %d is: %i \n", a+1, drone.ID);
	printf("The model of the drone %d es: %s \n", a+1, drone.model);
	printf("The price of the drone %d es: %i \n", a+1, drone.price);
	printf("The maximum flying height of the drone %d es: %f \n", a+1, drone.height);	
	printf("The autonomy in minutos of the drone %d es: %i \n", a+1, drone.autonomy);
	printf("The maximum weight of the drone %d es: %i \n", a+1, drone.weight);
	printf("The date of the las inspection of the drone %d es %i/%i/%i \n", a+1, drone.date.day, drone.date.month, drone.date.year );  
	showOperationZones (drone, regions, a);
	printf("\n");
	if(drone.nRates==0){
		drone.AvgRating=0;
		printf("The drone has not any ratings at this moment");
		}
	else {
		printf("Ratings of the drone %d:\n", a+1);
		for(i=0; i<(drone.nRates); i++){
			printf("Name: %s \n Rating(1-10)): %f \n Commment: %s \n", drone.rating[i].name, drone.rating[i].rate, drone.rating[i].comment);
			s=s+(drone.rating[i].rate);
		}
		drone.AvgRating=s/drone.nRates;
		printf("The average rating of the drone %d is %f:	\n", a+1, drone.AvgRating);
	}
	printf("\n");
	return;
}
void showFleet (char regions [15][30], int n, struct typeDrone fleet[TAM_MAX]){
	int i;
	for(i=0; i<n; i++) {
		mostrar (fleet[i], regions, i);
	}
	return;
}
float fleetPrice (struct typeDrone fleet[TAM_MAX], int n) {
	int i;
	float a=0;
	for(i=0; i<=n; i++){a = a + (fleet[i].price);}
	return (a);
}
void addDrone (struct typeDrone fleet[TAM_MAX], int *n, char regions [15][30]) {
	int i, a, rep=0;
	struct typeDrone dron1;
	dron1 = leer (regions);
	for (i=0; i<=(*n); i++){
		if((dron1.ID)==(fleet[i].ID)){rep++; a=i;}
	}
	if(rep==0){(fleet[(*n)])=dron1; (*n)++;}
	else{
		printf("The ID you introduced it is already registered in our database, here are the data of the drone:\n");
		mostrar(fleet[a], regions, a);
	}
	return;
}
void modifyData (struct typeDrone fleet[TAM_MAX], int n, char regions [15][30]){
	int i, id, rep, a;
	printf("Introduce the ID of the drone you would like to modify:	");
	scanf("%i", &id);
	for (i=0; i<=n; i++){
		if(id==(fleet[i].ID)){rep=1; a=i;}
	}
	if(rep==0){printf("The introduced ID does not belong to any drone of our database");}
	else{
		mostrar(fleet[a], regions, a);
		printf("Introduce the new autonomy in minutes:	");
		scanf("%i", &fleet[a].autonomy);
		printf("Introduce the day of the new inspection date:	 ");
		scanf("%i", &fleet[a].date.day);
		printf("Introduce the month of the new inspection date: 	");
		scanf("%i", &fleet[a].date.month);
		printf("Introduve the year of the new inspection date: 	");
		scanf("%i", &fleet[a].date.year);
	}
	return;	
}
void showInspectionDrones (struct typeDrone fleet[TAM_MAX], int n){
	int i, a, b;
	struct typeDate fechaR;
	printf("Introduce the current date\n day:	");
	scanf("%d", &fechaR.day);
	printf(" month:	");
	scanf("%d", &fechaR.month);
	printf(" year:	");
	scanf("%d", &fechaR.year);
	a=(fechaR.month)+(fechaR.year)*12;
	printf("The following drones should be inspected:\n");
	for (i=0; i<n; i++) {
		b=(fleet[i].date.month)+(fleet[i].date.year)*12;
		if((a-b)>=6) { mostrar(fleet[i], regions, i);}
	}
	return;
}
void showRegionDrones (struct typeDrone fleet[TAM_MAX], int n, char regions [15][30]){
	int i, b=-1;
	char a[30];
	for(i=0; i<15; i++){printf("%i. %s \n", i+1, regions[i]);}
  	printf("Write the name of the autonomic region:	");
  	scanf(" %[^\n]", a);
  	for(i=0; i<15; i++){if((strcmp(regions[i], a))==0){b=i;}}
  	if((b>-1)&&(b<15)){
  		printf("In this autonomic region the following drones can operate:\n");
		for(i=0; i<n; i++){
  	 	 	if(fleet[i].zones[b]==1) { printf(" ID: %d	 Model: %s	\n", fleet[i].ID, fleet[i].model);}
	   	} 
	}
	else{printf("You have not introduced the name of any autonomic region\n");}
	printf("\n");
	return;
}
void rateDron (struct typeDrone fleet[TAM_MAX], int n){
	int i, a, b, r=0;
	printf("Introduce the ID of the drone you would like to rate:	");
	scanf("%d", &a);
	for(i=0; i<n; i++){
		if(fleet[i].ID==a){r=1; b=i;}
	}
	if(r==0){printf("This ID does not belong to any drone of our database\n");}
	else{
		if(fleet[b].nRates>=30){printf("No more ratings can be done on this drone, maximum number has been reached\n");}
		else{
			printf("Introduce your name:	");
			scanf(" %[^\n]", fleet[b].rating[(fleet[b].nRates)].name);
			printf("Introduce your rate de 0 a 10:	");
			scanf("%f", &fleet[b].rating[(fleet[b].nRates)].rate);
			printf("Introduce your comment:	");
			scanf(" %[^\n]", fleet[b].rating[(fleet[b].nRates)].comment);
			(fleet[b].nRates)++;
		}
	}
	return;
}
int initializeDronesArray(struct typeDrone fleet[TAM_MAX]){
    int n;          
    int i, j, k;
    char aux[5];         
    srand (time(NULL));
    n=((rand() % (TAM_MAX/10 + 1))+TAM_MAX/5);
    
    for (i=0; i<n; i++){
        fleet[i].ID=(rand()%100) +1;
        
        strcpy(fleet[i].model, "Modelo");
        itoa(i+1, aux, 10);
        strcat(fleet[i].model, aux);
        
        fleet[i].price=(rand()%2000) +2000;
        fleet[i].height=(rand()%53) +100;
        fleet[i].autonomy=(rand()%180) + 60;
        fleet[i].weight=(rand()%10) + 1;
        
        k=(rand()%2);
        if (k==1){
           fleet[i].date.year=2016;
           fleet[i].date.month=(rand()%12)+1;
        }
        else{
           fleet[i].date.year=2017;
           fleet[i].date.month=(rand()%3)+1;
        }
        fleet[i].date.day=(rand()%29)+1;
               
        for (j=0; j<REGIONS; j++){
            k=(rand()%5) +1;
            if (k==5)
               fleet[i].zones[j]=1;
            else
               fleet[i].zones[j]=0;
        }                
    }
    return n; 
 }
void sortFleet(struct typeDrone droneFleet[TAM_MAX], int n){
	int i, j, max, jmax;
	struct typeDrone AUX;
	for(i=0; i<n; i++) {
		max=droneFleet[i].autonomy;
		jmax=i;
		for(j=i; j<n; j++){
			if( droneFleet[j].autonomy > max){
				max=droneFleet[j].autonomy;
				jmax=j;
			}
		}
		AUX=droneFleet[i];
		droneFleet[i]=droneFleet[jmax];
		droneFleet[jmax]=AUX;
	}
	return;
}

