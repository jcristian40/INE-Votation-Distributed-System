//
//  PaqueteDatagrama.h/Users/emyrkr/Desktop/Sistemas Distribuidos/Ejercicio11/proyecto/proyecto.xcodeproj
//  proyecto
//
//  Created by Jorge Emyr Vázquez Juárez on 5/21/15.
//  Copyright (c) 2015 Jorge Emyr Vázquez Juárez. All rights reserved.
//

#ifndef __proyecto__PaqueteDatagrama__
#define __proyecto__PaqueteDatagrama__

#include <stdio.h>

class PaqueteDatagrama{
public:
	PaqueteDatagrama(char *, unsigned int, char *, int );
	PaqueteDatagrama(unsigned int );
	~PaqueteDatagrama();
	char *obtieneDireccion();
	unsigned int obtieneLongitud();
	int obtienePuerto();
	char *obtieneDatos();
	void inicializaPuerto(int);
	void inicializaIp(char *);
	void inicializaDatos(char *);
	
private:
	char *datos;
	char ip[16];
	unsigned int longitud;
	int puerto;
};
#endif /* defined(__proyecto__PaqueteDatagrama__) */
