//	SocketDatargrama.cpp
//	Jorge Macías
//	2015
#include <stdlib.h>
#include <stdio.h>
#include "SocketDatagrama.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <ifaddrs.h>


using namespace std;

SocketDatagrama::SocketDatagrama(int p)
{
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&direccionLocal, sizeof(struct sockaddr_in));
	bzero((char *)&direccionForanea, sizeof(struct sockaddr_in));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons(p);
	bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
	puerto=p;
}

int SocketDatagrama::getPuerto(){
	return puerto;
}


SocketDatagrama::SocketDatagrama(int p, int flag)
{
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&direccionLocal, sizeof(struct sockaddr_in));
	bzero((char *)&direccionForanea, sizeof(struct sockaddr_in));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons(p);
	bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
	if(flag)
	{
		int yes = 1;
		setsockopt(s, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
	}
	else
	{
		struct timeval timeOut;
		timeOut.tv_sec = 0;
		timeOut.tv_usec = 10000;
		setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeOut, sizeof(timeOut));
	}
}

SocketDatagrama::~SocketDatagrama()
{
	close(s);
	//cout << "Destruido objeto SocketDatargrama...";
	//delete SocketDatagrama;
}

int SocketDatagrama::recibe(PaqueteDatagrama &p)
{
	
	//char *datos = new char[p.obtieneLongitud()];
	socklen_t clilen = sizeof(direccionForanea);
	int res;
	res = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(),0, (struct sockaddr *)&direccionForanea, &clilen);
	p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));

	//cout << "Recibiendo de " << inet_ntoa(direccionForanea.sin_addr) << " en el puerto : " <<ntohs(direccionForanea.sin_port)<<endl;
	//cout << &res << endl;
	//printf("%d",res);
	//p.inicializaDatos((char *)&res);
	return res;
}

int SocketDatagrama::recibe(PaqueteDatagrama &p, int size)
{
	
	//char *datos = new char[p.obtieneLongitud()];
	socklen_t clilen = sizeof(direccionForanea);
	
	int status = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(),0, (struct sockaddr *)&direccionForanea, &clilen);
	p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));
	//cout << "Recibiendo de " << inet_ntoa(direccionForanea.sin_addr) << " en el puerto : " <<ntohs(direccionForanea.sin_port)<<endl;
	//cout << &res << endl;
	//printf("%d",res);
	return status;
}
int SocketDatagrama::envia(PaqueteDatagrama & p)
{
	int status;
	//char *datos = p.obtieneDatos();
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr((char *)p.obtieneDireccion());
	direccionForanea.sin_port = htons(p.obtienePuerto());
	
	status = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
	//cout << (char*) p.obtieneDatos() << endl;
	return status;
}

void SocketDatagrama::printIP(){
	
	struct ifaddrs *ifaddr, *ifa;
	int family, s, n;
	char host[NI_MAXHOST];
	
	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}
	cout << "La ip local es : " <<endl;
	for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
		if (ifa->ifa_addr == NULL)
			continue;
		family = ifa->ifa_addr->sa_family;
		if (family == AF_INET) {
			s = getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, NI_MAXHOST,NULL, 0, NI_NUMERICHOST);
			if (s != 0) {
				printf("getnameinfo() failed: %s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			}
			printf("%s\n", host);
			
		}
	}
	
	freeifaddrs(ifaddr);
	
	
	return;
}