#include "Partida.h"
#include <sstream>
#include <iostream>
using namespace std;

void nueva(tPartida & partida, string const& jugador1, string const& jugador2){

	ostringstream flujo;
	flujo << fechaActual() << "_" << jugador1 << "_" << jugador2;
	partida.ID = flujo.str();
	partida.jugador1 = jugador1;
	partida.jugador2 = jugador2;
	partida.inicio = fechaActual();
	partida.actualizacion = fechaActual();
	partida.estadoPartida = EnCurso;
	iniciar(partida.juego);//conecta4.h

}

bool cargar(tPartida & partida, ifstream & archivo){

	int aux; string aux2;
	getline(archivo, aux2,'\n');
	getline(archivo, partida.ID,'\n');
	getline(archivo, partida.jugador1, '\n');
	getline(archivo, partida.jugador2, '\n');
	archivo >> partida.inicio;
	archivo >> partida.actualizacion;
	archivo >> aux;	partida.estadoPartida = tEstadoPartida(aux);
	cargar(partida.juego, archivo);//conecta4.h

	return !archivo.fail();

}

void guardar(tPartida const& partida, ofstream & archivo){

	archivo << partida.ID << endl;
	archivo << partida.jugador1 << endl;
	archivo << partida.jugador2 << endl;
	archivo << partida.inicio << " " << partida.actualizacion << endl;
	archivo << partida.estadoPartida << endl;
	guardar(partida.juego, archivo);//conecta4.h

};

string cabecera(tPartida const & partida){

	
	string resultado = "";
 	
	resultado = resultado + "\t" + partida.jugador1;
	resultado = resultado + "\t\t" + partida.jugador2;
	resultado = resultado + "\t" + stringFecha(partida.actualizacion,1);

	return resultado;


}

void abandonar(tPartida & partida){

	partida.estadoPartida = Terminada;
	partida.actualizacion = fechaActual();
}

bool aplicarJugada(tPartida & partida, int col){

	return aplicarJugada(partida.juego,col);
		
}
