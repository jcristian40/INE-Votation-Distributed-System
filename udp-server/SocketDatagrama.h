//
//  SocketDatagrama.h
//  proyecto
//
//  Created by Jorge Emyr Vázquez Juárez on 5/21/15.
//  Copyright (c) 2015 Jorge Emyr Vázquez Juárez. All rights reserved.
//

#ifndef __proyecto__SocketDatagrama__
#define __proyecto__SocketDatagrama__

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include "PaqueteDatagrama.h"

class SocketDatagrama{
public:
	SocketDatagrama(int);
	SocketDatagrama(int, int);
	~SocketDatagrama();
	int recibe(PaqueteDatagrama & p);
	int recibe(PaqueteDatagrama &p, int size);
	int envia(PaqueteDatagrama & p);
	int getStatus();
	int getPuerto();
	static void printIP();
private:
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	int s;
	int status;
	int puerto;
	
};


#endif /* defined(__proyecto__SocketDatagrama__) */
