//
//  main.cpp
//  Ejercicio 15
//
//  Created by Jorge Emyr Vázquez Juárez on 6/15/15.
//  Copyright (c) 2015 Jorge Emyr Vázquez Juárez. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#include "Header.h"
#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"

using namespace std;

int main(int argc, const char *argv[]) {
	char *ipServer;
	int port, paquetes[1];
	SocketDatagrama s1(7000,0);
	if(argc != 4)
	{
		printf("Forma de uso: %s {IP_Server} {Port} {# Paquetes}\n",argv[0]);
		exit(-1);
	}

	ipServer = (char*)argv[1];
	port = atoi(argv[2]);
	paquetes[0] = atoi(argv[3]);
	int contadorPerdidos = 0;
	int contadorPaquetes, contadorRecibidos;
	
	do
	{
		PaqueteDatagrama p((char *)&paquetes, sizeof(int), ipServer, port);
		contadorPaquetes = 0;
		contadorRecibidos = 1;
		if(s1.envia(p))
		{
			kiBytes KB;
			time_t timerInit,timerEnd;
			time(&timerInit);
			bzero(&KB,sizeof(kiBytes));
			PaqueteDatagrama receive(sizeof(kiBytes));
			while(contadorPaquetes++ < paquetes[0])
			{
				if(s1.recibe(receive,sizeof(kiBytes)) != -1)
				{
					memcpy(&KB, receive.obtieneDatos(), sizeof(kiBytes));
					if(contadorRecibidos++ != KB.result) break;
				}
			}
			contadorRecibidos-=1;
			contadorPerdidos = paquetes[0] - (contadorRecibidos);
			time(&timerEnd);
			double seconds;
			cout << "TOTAL PACKAGE: " << paquetes[0] << endl;
			cout << "Recibidos: " << contadorRecibidos;
			cout << " Perdidos: " << paquetes[0] - contadorRecibidos << endl;
			//cout << contadorPaquetes << endl;
			//seconds = difftime(timerEnd,timerInit);
			//cout << "SECONDS: " << seconds << endl;
			if(contadorRecibidos < 1024)
			{
				cout << contadorRecibidos / seconds << " KB/s\n";
				cout << paquetes[0] / seconds << " KB/s\n";
			}
			if((contadorRecibidos > 1024) && (contadorRecibidos/1024) < 1024)
			{
				cout << (contadorRecibidos/1024) / seconds << " MB/s\n";
				cout << (paquetes[0]/1024) / seconds << " MB/s\n";
			}
			if((contadorRecibidos/1024) > 1024)
			{
				cout << ((contadorRecibidos/1024)/1024) / seconds << " GB/s\n";
				cout << ((paquetes[0]/1024)/1024) / seconds << " GB/s\n";
			}
		}
		paquetes[0]++;
	}while(contadorPerdidos == 0);
	cout << "MAX package to send: " << (paquetes[0]-1) - contadorPerdidos << endl;

	
	return 0;
}