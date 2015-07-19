#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#define PORCENTAJE 10 //porcentaje de fraude

struct registro
{
	char celular[10];
	char CURP[18];
	char partido[3];
	char separador;
}; 

char buffer[BUFSIZ]; /* Región de memoria para el almacenamiento temporal de datos */

int main(int argc, char *argv[])
{
	char cadena[31], *cadenota = NULL, telefono[11] ="", curp[19]="", t[11];
	char *partidos[11];
	int i,n, destino, j, opcion;

	struct registro reg1;

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

	if(argc != 4)
	{
		printf("Forma de uso: programa numero_registros archivo_destino OPCION\n");
		exit(0);
	}

	printf("Tamaño de registro = %d\n", sizeof(reg1));
	opcion = atoi(argv[3]);

	if((destino = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1)
	{
		perror(argv[2]);
		exit(-1);
	}

	n = atoi(argv[1]);
	switch (opcion)
	{
		case 1: //Opcion 1
			for(j=0; j<n; j++)
			{
				sprintf(telefono, "%10d", j);
				for(i=0; i<10; i++)
				{
					if(telefono[i] == 32)
						telefono[i]='0';	
				}
				strcpy(reg1.celular, telefono);
				for(i=0; i<10; i++)
				{
					telefono[i]=telefono[i]+17;
				}
				strcpy(t, telefono);
				sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", t[0], t[1], t[2], t[3], rand()%10 + 48, rand()%10 + 48, rand()%10 + 48,rand()%10 + 48, rand()%10 + 48, 
				rand()%10 + 48, t[4], t[5], t[6], t[7], t[8], t[9],rand()%10 + 48, rand()%10 + 48);
				strcpy(reg1.CURP, curp);
				i = rand()%10;    
				strcpy(reg1.partido, partidos[i]);
				reg1.separador = '\n';
				write(destino,  &reg1, sizeof(reg1));
			}
			break;
	
		case 2: //Opcion 2 fraude con telefono, mismo telefono, distinta CURP en 10% de los casos
			//Todos los registros
			for(j=0; j<n; j++)
			{
				sprintf(telefono, "%10d", j);
				for(i=0; i<10; i++)
				{
					if(telefono[i] == 32)
					telefono[i]='0';
				}
				if((rand()%100 +1) > PORCENTAJE)
				{
					strcpy(reg1.celular, telefono);
				}
				for(i=0; i<10; i++)
				{
					telefono[i]=telefono[i]+17;
				}
				strcpy(t, telefono);
				sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", t[0], t[1], t[2], t[3], rand()%10 + 48, rand()%10 + 48, rand()%10 + 48,rand()%10 + 48, 
				rand()%10 + 48, rand()%10 + 48, t[4], t[5], t[6], t[7], t[8], t[9],rand()%10 + 48, rand()%10 + 48);
				strcpy(reg1.CURP, curp);
				i = rand()%10;    
				strcpy(reg1.partido, partidos[i]);
				reg1.separador = '\n';
				write(destino,  &reg1, sizeof(reg1));
			}
		break;
	
		case 3: //Opcion 3 fraude con CURP, distinto telefono, misma CURP en 10% de los casos
			//Todos los registros
			for(j=0; j<n; j++)
			{
				sprintf(telefono, "%10d", j);
				for(i=0; i<10; i++)
				{
					if(telefono[i] == 32)
					telefono[i]='0';
				}
				strcpy(reg1.celular, telefono);
				for(i=0; i<10; i++)
				{
					telefono[i]=telefono[i]+17;
				}
				strcpy(t, telefono);
				sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", t[0], t[1], t[2], t[3], rand()%10 + 48, rand()%10 + 48, rand()%10 + 48,rand()%10 + 48, 
				rand()%10 + 48, rand()%10 + 48, t[4], t[5], t[6], t[7], t[8], t[9],rand()%10 + 48, rand()%10 + 48);
				if((rand()%100 +1) > PORCENTAJE)
				{
					strcpy(reg1.CURP, curp);
				}
				i = rand()%10;    
				strcpy(reg1.partido, partidos[i]);
				reg1.separador = '\n';
				write(destino,  &reg1, sizeof(reg1));
			}
		break;
		
		default:
			printf("opción incorrecta\n");
			exit(0);
	}

	close(destino);
	exit(0);
}