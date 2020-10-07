/*
	ISMAEL G�MEZ GARRIDO 
	GRUPO 31
	GRADO EN INGENIERIA DE TECNOLOGIAS INDUSTRIALES
*/

/*
Este programa consiste en la creación y gestión de una base de datos de drones.

Cada dron tiene unas características asociadas: 
	- Número identificador
	- Nombre del modelo
	- Precio
	- Altura máxima de vuelo
	- Autonomía
	- Peso máximo:
	- Fecha de la última revisión
	- Zonas de operación (son las comunidades autónomas de España)
	- Valoraciones de los usuarios

La aplicación tiene las siguientes funciones:
	- Añadir dron a la flota
	- Mostrar flota de drones
	- Mostrar coste total de la flota
	- Modificar los datos de un dron
	- Mostrar drones a revisar (introduciendo la fecha actual)
	- Mostrar drones por comunidad
	- Valorar un dron
	- Mostrar drones ordenados por autonomía en una comunidad
	- Mostrar drones con mayor autonomía

*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 50
#define COMUNIDADES 15

char comunidades[15][30]={"Andalucia", "Aragon", "Principado de Asturias", "Cantabria", "Castilla La Mancha", "Castilla y Leon", "Catalunya", "Comunidad Valenciana", "Extremadura", "Galicia", "La Rioja", "Comunidad de Madrid", "Comunidad Foral de Navarra", "Pais Vasco", "Region de Murcia"};
struct tipoFecha{int dia; int mes; int ano;};
struct tipoUs{char nombre[20]; float val; char com[1000];};
struct tipoDron{
	int ID;
	char modelo [20];
	int precio;
	float altura;
	int autonomia;
	int peso;
	struct tipoFecha fecha;
	int zonas[15];
	struct tipoUs valor [30];
	int nVal;
	float Vmedia;
};
struct tipoDron flota [TAM_MAX];
struct tipoDron leer (char comunidades [15][30]);
void mostrar (struct tipoDron dron, char comunidades[15][30], int a);
void asignarZonasOperacion (struct tipoDron *dron, char comunidades [15][30]);
void mostrarZonasOperacion (struct tipoDron dron, char comunidades [15][30], int a);
void mostrarFlota (char comunidades [15][30], int n, struct tipoDron flota[TAM_MAX]);
float costeFlota (struct tipoDron flota[TAM_MAX], int n);
void anadirDron (struct tipoDron flota[TAM_MAX], int *n, char comunidades [15][30]);
void modificarDatos (struct tipoDron flota[TAM_MAX], int n, char comuniades[15][30]);
void mostrarDronesARevisar (struct tipoDron flota[TAM_MAX], int n);
void mostrarDronesComunidad (struct tipoDron flota[TAM_MAX], int n, char comunidades [15][30]);
void valorarDron (struct tipoDron flota[TAM_MAX], int n);
int inicializarVectorDrones(struct tipoDron flota[TAM_MAX]);
struct tipoDron flotaOrd [TAM_MAX];
void ordenarFlota(struct tipoDron flotaOrd[TAM_MAX], int n);

int main(int argc, char *argv[]) {
	int cont, i, Ndrones=0, NdronesCOM=0, a=-1, b;
	char com[30];
	for(i=0; i<TAM_MAX; i++){ flota[i].nVal=0;}
	Ndrones=inicializarVectorDrones(flota);
	do{
		printf("MENU\n 1 - Anadir dron repartidor a la flota\n 2 - Mostrar flota de drones\n 3 - Mostar coste total de la flota\n 4 - Modificar los datos de un dron\n 5 - Mostrar drones a revisar\n 6 - Mostar drones por comunidad\n 7 - Valorar un dron\n 8 - Mostrar drones ordenados por autonomia en una comunidad\n 9 - Mostrar drones con mayor autonomia\n 0 - Salir\n");
		scanf("%d", &cont);
		switch (cont){
			case 1:
				if(Ndrones>=TAM_MAX){printf("Ya no se pueden almacenar mas drones");}
				else { 
					anadirDron(flota, &Ndrones, comunidades);
				}
				break;
			case 2:
				mostrarFlota(comunidades, Ndrones, flota); 
				break;
			case 3: 
				for(i=0; i<Ndrones; i++){
					printf("El precio del dron %d es %d\n", i+1, flota[i].precio);
				}
				printf("El coste total de la flota es %f\n", costeFlota(flota, Ndrones));
				break;
			case 4:
				modificarDatos(flota, Ndrones, comunidades);
			    break;
			case 5:
				mostrarDronesARevisar(flota, Ndrones);
				break;
			case 6:
				mostrarDronesComunidad(flota, Ndrones, comunidades);
				break;
			case 7:
				valorarDron(flota, Ndrones);
				break;
			case 8:
				for(i=0; i<15; i++){ printf("%i. %s \n", i+1, comunidades[i]);}
  				printf("Escriba el nombre de la comunidad autonoma que desee:	");
  				scanf(" %[^\n]", com);
  				for(i=0; i<15; i++){if((strcmp(comunidades[i], com))==0){a=i;}}
  				if((a>-1)&&(a<15)){
  					for(i=0; i<Ndrones; i++){
  	 	 				if(flota[i].zonas[a]==1) { flotaOrd[NdronesCOM]=flota[i]; NdronesCOM++;}
					}
					ordenarFlota(flotaOrd, NdronesCOM);
					mostrarFlota(comunidades, NdronesCOM, flotaOrd);	
				}
				else{printf("No has introducido el nombre de ninguna comunidad autonoma\n");}
				break;
			case 9:
				printf("Escriba el numero de drones que desea ver	");
				scanf("%i", &b);
				for(i=0; i<Ndrones; i++){
					flotaOrd[i]=flota[i];
				}
				ordenarFlota(flotaOrd, Ndrones);
				mostrarFlota(comunidades, b, flotaOrd);
				break;
		}
	} while(cont!=0);
	printf("El programa ha finalizado\n");
	return 0;
}

void mostrarZonasOperacion (struct tipoDron dron, char comunidades [15][30], int a){
  	int i=0;
  	printf("Las zonas de operacion del dron  %d son :\n", a+1);
	for (i=0; i<15; i++){
    	if(dron.zonas[i]==1){
    		printf(" %s ", comunidades [i]);
		}
	}
     return;
  }
void asignarZonasOperacion (struct tipoDron *dron, char comunidades[15][30]){
  int i, cont, resp;
  for(i=0; i<15; i++){(*dron).zonas[i]=0;}
  do{
  	 for(i=0; i<15; i++){
  	 	 printf("%i. %s \n", i+1, comunidades[i]);
  	 }
  	 printf("Seleccione una comunidad autonoma, escriba 0 para salir   ");
  	 scanf("%i", &resp);
  	 if(resp==0){cont=1;}
	 if((resp>=1)&&(resp<=15)){
	 	cont=0;
	 	(*dron).zonas[resp-1]=1;
	 }
  }while(cont==0);
  return;
  }
struct tipoDron leer (char comunidades [15][30]){
	struct tipoDron dron;
	printf("Introduzca el identificador	");
	scanf("%i", &dron.ID);
	printf("Introduzca el modelo	");
	scanf(" %[^\n]", dron.modelo);
	printf("Introduzca el precio	");
	scanf("%i", &dron.precio);
	printf("Introduzca la altura maxima de vuelo	");
	scanf("%f", &dron.altura);
	printf("Introduzca la autonomia en minutos	");
	scanf("%i", &dron.autonomia);
	printf("Introduzca el peso maximo en kilogramos	");
	scanf("%i", &dron.peso);
	printf("Introduzca el dia de  ultima revision	");
	scanf("%i", &dron.fecha.dia);
	printf("Introduzca el mes de su ultima revision	");
	scanf("%i", &dron.fecha.mes);
	printf("Introduzca el ano de su ultima revision	");
	scanf("%i", &dron.fecha.ano);
	asignarZonasOperacion (&dron, comunidades);
	
	return dron;
}
void mostrar (struct tipoDron dron, char comunidades [15][30], int a){
	int i;
	float s=0;
	printf("\n");
	printf("El numero identificador del dron %d es: %i \n", a+1, dron.ID);
	printf("El modelo del dron %d es: %s \n", a+1, dron.modelo);
	printf("El precio del dron %d es: %i \n", a+1, dron.precio);
	printf("La altura maxima de vuelo del dron %d es: %f \n", a+1, dron.altura);	
	printf("La autonomia en minutos del dron %d es: %i \n", a+1, dron.autonomia);
	printf("El peso maximo del dron %d es: %i \n", a+1, dron.peso);
	printf("La fecha de la ultima revision del dron %d es %i/%i/%i \n", a+1, dron.fecha.dia, dron.fecha.mes, dron.fecha.ano );  
	mostrarZonasOperacion (dron, comunidades, a);
	printf("\n");
	if(dron.nVal==0){
		dron.Vmedia=0;
		printf("El dron aun no ha tenido valoraciones");
		}
	else {
		printf("Valoraciones del dron %d:\n", a+1);
		for(i=0; i<(dron.nVal); i++){
			printf("Nombre: %s \n Valoracion: %f \n Comentario: %s \n", dron.valor[i].nombre, dron.valor[i].val, dron.valor[i].com);
			s=s+(dron.valor[i].val);
		}
		dron.Vmedia=s/dron.nVal;
		printf("La valoracion media del dron %d es %f:	\n", a+1, dron.Vmedia);
	}
	printf("\n");
	return;
}
void mostrarFlota (char comunidades [15][30], int n, struct tipoDron flota[TAM_MAX]){
	int i;
	for(i=0; i<n; i++) {
		mostrar (flota[i], comunidades, i);
	}
	return;
}
float costeFlota (struct tipoDron flota[TAM_MAX], int n) {
	int i;
	float a=0;
	for(i=0; i<=n; i++){a = a + (flota[i].precio);}
	return (a);
}
void anadirDron (struct tipoDron flota[TAM_MAX], int *n, char comunidades [15][30]) {
	int i, a, rep=0;
	struct tipoDron dron1;
	dron1 = leer (comunidades);
	for (i=0; i<=(*n); i++){
		if((dron1.ID)==(flota[i].ID)){rep++; a=i;}
	}
	if(rep==0){(flota[(*n)])=dron1; (*n)++;}
	else{
		printf("El ID del nuevo dron ya esta registrado en la flota, estos son sus datos:\n");
		mostrar(flota[a], comunidades, a);
	}
	return;
}
void modificarDatos (struct tipoDron flota[TAM_MAX], int n, char comunidades [15][30]){
	int i, id, rep, a;
	printf("Introduzca el ID del dron que desea modificar:	");
	scanf("%i", &id);
	for (i=0; i<=n; i++){
		if(id==(flota[i].ID)){rep=1; a=i;}
	}
	if(rep==0){printf("El Id introducido no pertenece a ningun dron de nuestra flota");}
	else{
		mostrar(flota[a], comunidades, a);
		printf("Introduzca la nueva autonomia del dron en minutos:	");
		scanf("%i", &flota[a].autonomia);
		printf("Introduzca el dia de su nueva revision:	 ");
		scanf("%i", &flota[a].fecha.dia);
		printf("Introduzca el mes de su nueva revision: 	");
		scanf("%i", &flota[a].fecha.mes);
		printf("Introduzca el ano de su nueva revision: 	");
		scanf("%i", &flota[a].fecha.ano);
	}
	return;	
}
void mostrarDronesARevisar (struct tipoDron flota[TAM_MAX], int n){
	int i, a, b;
	struct tipoFecha fechaR;
	printf("Introduzca la fecha actual\n dia:	");
	scanf("%d", &fechaR.dia);
	printf(" mes:	");
	scanf("%d", &fechaR.mes);
	printf(" ano:	");
	scanf("%d", &fechaR.ano);
	a=(fechaR.mes)+(fechaR.ano)*12;
	printf("Se deben revisar los siguientes drones:\n");
	for (i=0; i<n; i++) {
		b=(flota[i].fecha.mes)+(flota[i].fecha.ano)*12;
		if((a-b)>=6) { mostrar(flota[i], comunidades, i);}
	}
	return;
}
void mostrarDronesComunidad (struct tipoDron flota[TAM_MAX], int n, char comunidades [15][30]){
	int i, b=-1;
	char a[30];
	for(i=0; i<15; i++){printf("%i. %s \n", i+1, comunidades[i]);}
  	printf("Escriba el nombre de la comunidad autonoma que desee:	");
  	scanf(" %[^\n]", a);
  	for(i=0; i<15; i++){if((strcmp(comunidades[i], a))==0){b=i;}}
  	if((b>-1)&&(b<15)){
  		printf("En esta comunidad autonoma pueden operar los siguientes drones:\n");
		for(i=0; i<n; i++){
  	 	 	if(flota[i].zonas[b]==1) { printf(" ID: %d	 Modelo: %s	\n", flota[i].ID, flota[i].modelo);}
	   	} 
	}
	else{printf("No has introducido el nombre de ninguna comunidad autonoma\n");}
	printf("\n");
	return;
}
void valorarDron (struct tipoDron flota[TAM_MAX], int n){
	int i, a, b, r=0;
	printf("Introduzca el ID del dron que desee valorar:	");
	scanf("%d", &a);
	for(i=0; i<n; i++){
		if(flota[i].ID==a){r=1; b=i;}
	}
	if(r==0){printf("Ese ID no pertenece a ningun dron de nuestra flota\n");}
	else{
		if(flota[b].nVal>=30){printf("Ya no se pueden hacer mas valoraciones a este dron\n");}
		else{
			printf("Introduce tu nombre:	");
			scanf(" %[^\n]", flota[b].valor[(flota[b].nVal)].nombre);
			printf("Introduce tu valoracion de 0 a 10:	");
			scanf("%f", &flota[b].valor[(flota[b].nVal)].val);
			printf("Introduce tu comentario:	");
			scanf(" %[^\n]", flota[b].valor[(flota[b].nVal)].com);
			(flota[b].nVal)++;
		}
	}
	return;
}
int inicializarVectorDrones(struct tipoDron flota[TAM_MAX]){
    int n;          
    int i, j, k;
    char aux[5];         
    srand (time(NULL));
    n=((rand() % (TAM_MAX/10 + 1))+TAM_MAX/5);
    
    for (i=0; i<n; i++){
        flota[i].ID=(rand()%100) +1;
        
        strcpy(flota[i].modelo, "Modelo");
        itoa(i+1, aux, 10);
        strcat(flota[i].modelo, aux);
        
        flota[i].precio=(rand()%2000) +2000;
        flota[i].altura=(rand()%53) +100;
        flota[i].autonomia=(rand()%180) + 60;
        flota[i].peso=(rand()%10) + 1;
        
        k=(rand()%2);
        if (k==1){
           flota[i].fecha.ano=2016;
           flota[i].fecha.mes=(rand()%12)+1;
        }
        else{
           flota[i].fecha.ano=2017;
           flota[i].fecha.mes=(rand()%3)+1;
        }
        flota[i].fecha.dia=(rand()%29)+1;
               
        for (j=0; j<COMUNIDADES; j++){
            k=(rand()%5) +1;
            if (k==5)
               flota[i].zonas[j]=1;
            else
               flota[i].zonas[j]=0;
        }                
    }
    return n; 
 }
void ordenarFlota(struct tipoDron flotaOrd[TAM_MAX], int n){
	int i, j, max, jmax;
	struct tipoDron AUX;
	for(i=0; i<n; i++) {
		max=flotaOrd[i].autonomia;
		jmax=i;
		for(j=i; j<n; j++){
			if( flotaOrd[j].autonomia > max){
				max=flotaOrd[j].autonomia;
				jmax=j;
			}
		}
		AUX=flotaOrd[i];
		flotaOrd[i]=flotaOrd[jmax];
		flotaOrd[jmax]=AUX;
	}
	return;
}

