#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

using namespace std;

sem_t mutex1;
sem_t mutex2;

int numregistro[0];

struct registro
	{
		char celular[10];
		char CURP[18];
		char partido[3];
		char separador;
	}; 


vector<registro> pilaregistro;

int puerto1=7777;
int puerto2=8888;

SocketDatagrama socketudpcliente(puerto1);
SocketDatagrama socketudpserverc(puerto2);
			
//Se crean los paquetes para envio y recepcion
struct registro Envreg;
struct registro Recreg;
struct registro envPila;

//bzero((char*)&Envreg, sizeof(struct registro));
//bzero((char*)&Recreg, sizeof(struct registro));
//bzero((char*)&envPila, sizeof(struct registro));

void *ReciboUDPCliente(void*)
{
	PaqueteDatagrama pr(sizeof(registro));
   	//char ip[16];
   	//in_addr dir;
   	int j=1;

   	while(1)
   	{
      	if(socketudpcliente.recibe(pr))
      	{
	        printf("recibido: %d",j);
	        //dir.s_addr = inet_addr(pr.obtieneDireccion()); //DUDA AQUI
	        memcpy((char *)&Recreg, pr.obtieneDatos(), sizeof(registro));
		    //pr.obtieneDatos();
	        pilaregistro.push_back(Recreg);
	        j++;
      	}
   	}
}

void *EnvioServerCentralizado(void*)
{
   	char *ip="127.0.0.1";   	

   	while(1)
   	{
      	sem_wait(&mutex2);
      	while(1)
		{
			while (!pilaregistro.empty())
			{  		
				cout<<"EnvioServerCentralizado";
				envPila=pilaregistro.back();

				PaqueteDatagrama paquete((char *)&envPila, sizeof(registro),ip, puerto2);
				//PaqueteDatagrama paqueteR(tamr);
				//Estructura para reenvio de paquetes 

			    //struct timeval tiempoFuera;
			    //bzero((char *)&tiempoFuera, sizeof(struct timeval));
			    //tiempoFuera.tv_sec = 0;
			    //tiempoFuera.tv_usec = 500000;

				//socketudpserverc.setTiempo(tiempoFuera);
				
		    	//Se envia el paquete
				socketudpserverc.envia(paquete);
		    	pilaregistro.pop_back();
		  	}
		 }
      
      	sem_post(&mutex1);
   }
}

void *ReciboServerCentralizado(void*)
{
   int num[0];
   char *ip="127.0.0.1";
   //PaqueteDatagrama p((char *)(&Recreg), sizeof(registro),ip, puerto2);
   PaqueteDatagrama pr(sizeof(int));

   while(1)
   {
      sem_wait(&mutex1);
      printf("\n ReciboServerCentralizado.. \n");  
      
		if(socketudpserverc.recibe(pr) != -1)
		{
			//emcpy(ip,(char *)&dir.s_addr,4);  
         	pr.obtieneDatos();
         	memcpy(&num[0], pr.obtieneDatos(), sizeof(int));
         	cout<<"Numero de registros que llegaron: "<<num[0]<<endl;
		}

      sleep(5);
      sem_post(&mutex2);
   }
}

int main(void)
{
   pthread_t th1, th2, th3;

   //s.concurrente();
   // Inicializa los semaforos
   sem_init(&mutex1, 0, 1);
   sem_init(&mutex2, 0, 0);
   
   /* Se crean dos hilos con atributos predeterminados */
   
   pthread_create(&th3, NULL, &ReciboUDPCliente, NULL);
   pthread_create(&th2, NULL, &EnvioServerCentralizado, NULL);
   pthread_create(&th1, NULL, &ReciboServerCentralizado, NULL);
   
   //printf("El hilo principal espera a sus hijos\n");
   //}
   /* se espera su terminación */
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   pthread_join(th3, NULL);
   printf("El hilo principal termina\n");
   
   exit(0);
}