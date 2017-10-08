#ifndef PARTIDA_H
#define PARTIDA_H

#include "Conecta4.h"
#include "Fecha.h"

const string EstadoPartida[] = {"En Curso","Terminada"};
typedef enum{EnCurso, Terminada}tEstadoPartida;

typedef struct{
	string ID;
	string jugador1;
	string jugador2;
	tFecha inicio;
	tFecha actualizacion;
	tEstadoPartida estadoPartida;
	tConecta4 juego;

}tPartida;

// Recibe los identificadores de los adversarios y devuelve una partida con todos sus datos rellenos.
void nueva(tPartida & partida, string const& jugador1, string const& jugador2);

// Aplica la jugada col al juego, y si se pudo realizar, devuelve true y actualiza los demás campos de la partida.
bool aplicarJugada(tPartida & partida, int col);

// Modifica el estado de la partida a Terminada, y la fecha de la última actualización.
void abandonar(tPartida & partida);

//Dado un flujo de archivo de salida(ya abierto), escribe en el flujo los datos de la partida.
void guardar(tPartida const& partida, ofstream & archivo);

//Dado un flujo de archivode entrada(ya abierto), lee los datos que corresponden a una partida en partida. Devuelve false si la partida no se ha podido cargar correctamente.
bool cargar(tPartida & partida, ifstream & archivo);

string cabecera(tPartida const & partida);

#endif //PARTIDA_H