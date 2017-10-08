#ifndef LISTAPARTIDAS_H
#define LISTAPARTIDAS_H
#include "Partida.h"
#include <iostream>
using namespace std;


const int MAX = 30; //5ToTest
typedef struct{

	int contador;
	tPartida partida[MAX];

}tListaPartidas;

//Carga la lista de partidas desde el flujo archivo.Devuelve false si la lista no se ha podido cargar correctamente.
bool cargar(tListaPartidas & partidas, ifstream & archivo);

//Dada una partida, si hay espacio en la lista, la añade al final de la lista y devuelve true.Si no se ha podido insertar devuelve false.
bool insertar(tListaPartidas & partidas, tPartida const& partida, int &posicion);

//Guarda la lista de partidas en el flujo archivo.
void guardar(tListaPartidas const& partidas, ofstream & archivo);


#endif //LISTAPARTIDAS_H