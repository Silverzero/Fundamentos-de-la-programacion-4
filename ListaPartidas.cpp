#include "ListaPartidas.h"

bool cargar(tListaPartidas & partidas, ifstream & archivo){

	archivo >> partidas.contador;

	for (int i = 0; i < partidas.contador;i++)
	{
		cargar(partidas.partida[i], archivo);	
	}
	
	return !archivo.fail();
}

void guardar(tListaPartidas const& partidas, ofstream & archivo){

	archivo << partidas.contador << endl;
	
	for (int i = 0; i < partidas.contador; i++)
	{
		guardar(partidas.partida[i], archivo);
	}
}

bool insertar(tListaPartidas & partidas, tPartida const& partida, int &posicion){


	if (partidas.contador < MAX){
		partidas.partida[partidas.contador] = partida;
		posicion = partidas.contador;
		partidas.contador++;
		return true;
	}
	else return false;


}