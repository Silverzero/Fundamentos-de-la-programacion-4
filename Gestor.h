#ifndef GESTOR_H
#define GESTOR_H

#include "ListaPartidas.h"
#include "ListaUsuarios.h"

typedef struct{

	tListaPartidas listapartidas;
	tListaUsuarios listausuarios;
	int usuarioindice;
	int partidaindice;

}tGestor;



bool arrancar(tGestor & gestor);

void apagar(tGestor & gestor);

bool crearCuenta(tGestor &gestor, string const& idUsu, string const &clave);

bool iniciarSesion(tGestor & gestor, string const &idUsu, string const &clave);

void limpiarAvisos(tGestor &gestor);

string resumenActividad(tGestor const &gestor);

void generarAccesos(tGestor & gestor);

int partidasUsuario(tGestor const& gestor);

bool nuevaPartida(tGestor & gestor);

string cabecera(tGestor const& gestor, int posEnCurso);

bool tieneAvisos(tGestor const &gestor, string &aviso);

void apuntaPartida(tGestor &gestor, int posParEnCurso);

void mostrarPartida(tGestor const& gestor);

bool esSuTurno(tGestor &gestor);

void ordenarTurno(tGestor &gestor);

void ordenarFecha(tGestor &gestor);

void jugarPartida(tGestor &gestor, int col);

void abandonarPartida(tGestor &gestor);
#endif //GESTOR_H

