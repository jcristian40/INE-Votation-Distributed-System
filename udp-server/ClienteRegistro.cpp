#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

using namespace std;

#define PORCENTAJE 10 //porcentaje de fraude

struct registro{
char celular[10];
char CURP[18];
char partido[3];
char opcion[1];
};

int main(int argc, char *argv[]){

char  telefono[11] ="", curp[19]="", t[11];
char *direccion_servidor, *partidos[11],*opcionc;

int i, n, j, opcion, numero_registros,puerto;
//Se crea la estructura
struct registro reg1;

//Se crea un datagrama para enviar el numero de registros al Servidor como pimer valor
PaqueteDatagrama *pr;
// Se crea un dtaagrama
PaqueteDatagrama *p;

//Partidos 
partidos[0] = "PRI";
partidos[1] = "PAN";
partidos[2] = "PRD";
partidos[3] = "P_T";
partidos[4] = "VDE";
partidos[5] = "MVC";
partidos[6] = "NVA";
partidos[7] = "MOR";
partidos[8] = "HUM";
partidos[9] = "ENC";


if(argc != 4){
printf("Forma de uso: programa numero_registros direccion_servidor OPCION\n");
exit(0);
}

//Numero de registros a crear
n=atoi(argv[1]);
//nr=(argv[1]);

//El puerto donde estara escuchando el servidor
puerto=atoi(argv[2]);

//Direccion del servidor
direccion_servidor=(char *)argv[3];

//Opcion fraude
opcion=atoi(argv[4]);
opcionc= argv[4];

//Crecion de un objeto socket
SocketDatagrama s1(puerto);
//Confrimacion del puerto
//cout<<"\nPuerto socket: "<< s1.getPuerto()<<endl;


//Enviando el numero de registros al servidor para que se crea del lado del servidor un for que reciba hasta n mensajes
 pr= new PaqueteDatagrama((char*)&n, sizeof(&n), (char*)direccion_servidor, puerto );
 //Corrobora la direccion del servidor
 cout<<pr->obtieneDireccion();
 s1.envia(*pr);

cout<<"\n";


switch(opcion){
	case 1: //Opcion 1
			for(j=0; j<n; j++){
				//Envio de paquetes
				cout<<"\n\nSe envia el paquete "<<(j+1);
				sprintf(telefono, "%10d", j);
				for(i=0; i<10; i++)
				{
					if(telefono[i] == 32)
					telefono[i]='0';
				}
			//El telefono celular generado	
			strcpy(reg1.celular, telefono);

			for(i=0; i<10; i++){
				telefono[i]=telefono[i]+17;
			}
			strcpy(t, telefono);		
			cout<<"\nreg1 celular "<<reg1.celular;			
			
			//La CURP
			sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c ", t[0], t[1], t[2], t[3],rand()%10 + 48, rand()%10 + 48, rand()%10 + 48,rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, t[4], t[5], t[6], t[7], t[8], t[9],rand()%10 + 48, rand()%10 + 48);			
			strcpy(reg1.CURP, curp);
			cout<<"\nreg1.curp "<< reg1.CURP;
			//El partido que se eligio
			i = rand()%10;
			strcpy(reg1.partido, partidos[i]);
			cout<<"\nreg1.partido "<<reg1.partido;
			//La opcion de Fraude 
			strcpy(reg1.opcion, opcionc);
			cout<<"\nopcion: "<<reg1.opcion;

			//Se crea el paquete a enviar el cual contiene la estructura con los datos previamente llenados de los registros
			p= new PaqueteDatagrama((char *)&reg1, sizeof(registro), (char*)direccion_servidor, puerto);
			//Tamaño a enviar de cada paquete 32 bytes
			cout<<"\nTamaño paquete: " << sizeof(registro);
			//Se envia el datagrama;			
			s1.envia(*p);
			}
			
			break;

			case 2: //Opcion 2 fraude con telefono, mismo telefono, distinta CURP en 10% de los casos
			//Todos los registros
				for(j=0; j<n; j++){
					sprintf(telefono, "%10d", j);
				for(i=0; i<10; i++){
					if(telefono[i] == 32)
					telefono[i]='0';
				}
				if((rand()%100 +1) > PORCENTAJE){
					strcpy(reg1.celular, telefono);
				}
				for(i=0; i<10; i++){
					telefono[i]=telefono[i]+17;
				}
				strcpy(t, telefono);
				sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c \n", t[0], t[1], t[2], t[3],rand()%10 + 48, rand()%10 + 48, rand()%10 + 48,rand()%10 + 48, rand()%10 + 48, rand()%10 +48, t[4], t[5], t[6], t[7], t[8], t[9],rand()%10 + 48, rand()%10 + 48);
				strcpy(reg1.CURP, curp);
				i = rand()%10;
				strcpy(reg1.partido, partidos[i]);
				
				//opcion de fraude
				strcpy(reg1.opcion, opcionc);
			    cout<<"\nopcion: "<<reg1.opcion;
			    //Se envia el paquete 
			    p= new PaqueteDatagrama((char *)&reg1, sizeof(registro), (char*)direccion_servidor, puerto );
			    //Tamaño a enviar de cada paquete 32 bytes
				cout<<"\nTamaño paquete: " << sizeof(registro);
				//Se envia el datagrama;			
				s1.envia(*p);

				}
		break;

		case 3: //Opcion 3 fraude con CURP, distinto telefono, misma CURP en 10% de los casos
			//Todos los registros
				for(j=0; j<n; j++){
					sprintf(telefono, "%10d\n", j);
				for(i=0; i<10; i++){
				if(telefono[i] == 32)
					telefono[i]='0';
				}
				strcpy(reg1.celular, telefono);
				for(i=0; i<10; i++){
					telefono[i]=telefono[i]+17;
				}
				strcpy(t, telefono);
				sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", t[0], t[1], t[2], t[3],rand()%10 + 48, rand()%10 + 48, rand()%10 + 48,rand()%10 + 48, rand()%10 + 48, rand()%10 +48, t[4], t[5], t[6], t[7], t[8], t[9],rand()%10 + 48, rand()%10 + 48);
				if((rand()%100 +1) > PORCENTAJE){
					strcpy(reg1.CURP, curp);
				}
				i = rand()%10;
				strcpy(reg1.partido, partidos[i]);
				
				//Se envia el paquete 
			    p= new PaqueteDatagrama((char *)&reg1, sizeof(registro), (char*)direccion_servidor, puerto );
			    //Tamaño a enviar de cada paquete 32 bytes
				cout<<"\nTamaño paquete: " << sizeof(registro);
				//Se envia el datagrama;			
				s1.envia(*p);

				}
			break ;

			default:
				printf("opción incorrecta\n");
				exit(0);
}



		}
		

