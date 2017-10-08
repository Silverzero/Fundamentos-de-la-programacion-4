#ifndef USUARIO_H
#define USUARIO_H

#include "Fecha.h"
#include "ListaAccesoPartidas.h"
#include <fstream>
#include <sstream>

using namespace std;
const int NRN = 5;
const string NombreNivel[] = { "Principiante", "Medio", "Experto" };
typedef enum{Principiante,Medio,Experto}tNivel;
typedef enum{Gana,Pierde,Empate}tResultado;
typedef struct{

	string nombre;
	string contraseña;
	tNivel nivel;
	int racha;
	bool espera;
	int ganadas;
	int perdidas;
	int empatadas;
	tFecha ultimaConexion;
	string avisos;
	tListaAccesoPartidas listaacceso;


}tUsuario;

void iniciar(tUsuario & usuario, string const& id, string const& pas);
//Recibe un identificador de usuario y una contraseña e inicia todos los campos del usuario.

void guardar(tUsuario const& usuario, ofstream & archivo);
//Dado un flujo de archivo, escribe en el flujo los datos del usuario.Importante : la lista de partidas en curso no se guarda.

bool cargar(tUsuario & usuario, ifstream & archivo);
//Dado un flujo de archivo, lee los datos que corresponde a un usuario en usuario.Importante : el fichero no contiene los datos de las partidas en curso(hay que iniciarla a la lista vacía)

bool iniciarSesion(tUsuario & usuario, string const& clave);
//Recibe una contraseña(clave) y un usuario y devuelve si la contraseña es correcta o no.Además, en caso de ser correcta, actualiza la fecha de la última conexión.

void actualizarAvisos(tUsuario & usu, string const& aviso);
//Actualiza el campo avisos añadiendo al final del string una nueva línea con el nuevo aviso.

void limpiarAvisos(tUsuario & usu);
//Actualiza el campo avisos dejando el string vacío.

bool nuevaPartida(tUsuario & usuario, tParIdEn const& par);
//Si el usuario no ha utilizado todas las partidas en curso que puede tener, inserta en su lista de partidas en curso la información de acceso a la partida par, 
//actualiza el estado de espera y devuelve true.En otro caso devuelve false.

//propia
bool tieneAvisos(tUsuario const & usuario, string & avisos);

string resumenActividad(tUsuario const &usuario);

void aplicarFinPartida(tUsuario & usuario, string const& idPar, tResultado resultado);//leer explicacion

void masNivel(tUsuario & usuario);

void menosNivel(tUsuario & usuario);
#endif //USUARIO_H