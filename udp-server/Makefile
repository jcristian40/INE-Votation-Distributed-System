ClienteRegistro: ClienteRegistro.cpp SocketDatagrama.o
	g++ ClienteRegistro.cpp SocketDatagrama.o PaqueteDatagrama.o -o clienteregistro
ServidorUDP: ServidorUDP.cpp SocketDatagrama.o
	g++ ServidorUDP.cpp SocketDatagrama.o PaqueteDatagrama.o -o ServidorUDP -lpthread 
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
