#include <inttypes.h>
#include "Header.h"
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[]){
	struct kiBytes KB;
	int *nPaquetes;
	if(argc != 2)
	{
		cout << "Forma de uso: " << argv[0] << " puerto\n";
		exit(0);
	}
	SocketDatagrama socketlocal(atoi(argv[1]));
	while(1)
	{
		PaqueteDatagrama receive(sizeof(int));
		PaqueteDatagrama envio((char *)&KB, sizeof(kiBytes),(char*)"",0);
		socketlocal.recibe(receive);
		nPaquetes = (int *)receive.obtieneDatos();
		envio.inicializaIp(receive.obtieneDireccion());
		envio.inicializaPuerto(receive.obtienePuerto());

		system("clear");
		cout << "Número de paquetes a enviar: " << nPaquetes[0] << "\n\n";

		int contadorPaquetes = 0;
		while(contadorPaquetes++ < nPaquetes[0])
		{
			KB.result = contadorPaquetes;
			envio.inicializaDatos((char*)&KB);
			socketlocal.envia(envio);
		}
		cout << "Paquetes enviados: " << contadorPaquetes-1 << endl;
	}
	return 0;
}