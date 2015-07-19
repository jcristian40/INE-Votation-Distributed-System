//
//  PaqueteDatagrama.cpp
//  proyecto
//
//  Created by Jorge Emyr Vázquez Juárez on 5/21/15.
//  Copyright (c) 2015 Jorge Emyr Vázquez Juárez. All rights reserved.
//

#include "PaqueteDatagrama.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

PaqueteDatagrama::PaqueteDatagrama(char *data, unsigned int size, char *ip, int port)
{
	datos = new char[size];
	memcpy(datos,data,size);
	strcpy(this->ip,ip);
	longitud = size;
	puerto = port;
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int size)
{
	datos = new char[size];
	bzero(datos,size);
	longitud = size;
	
}

PaqueteDatagrama::~PaqueteDatagrama()
{
	delete []datos;
}

char *PaqueteDatagrama::obtieneDireccion(){
	return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud(){
	return longitud;
}

int PaqueteDatagrama::obtienePuerto(){
	return puerto;
}

char *PaqueteDatagrama::obtieneDatos(){
	return datos;
}

void PaqueteDatagrama::inicializaIp(char *ip)
{
	strcpy(this->ip, ip);
}

void PaqueteDatagrama::inicializaPuerto(int port)
{
	puerto = port;
}

void PaqueteDatagrama::inicializaDatos(char *data)
{
	memcpy(datos,data,longitud);
}