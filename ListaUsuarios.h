#ifndef LISTAUSUARIO_H
#define LISTAUSUARIO_H

#include "Usuario.h"

//40 pre prueba --> 5
const int MAX_Usuarios = 40; //5ToTest;
typedef struct{

	int contador;
	tUsuario usuarios[MAX_Usuarios];

}tListaUsuarios;

bool cargar(tListaUsuarios & usuarios, ifstream & archivo);
//Carga la lista de usuarios desde el flujo(ya abierto) archivo(ver detalles y ejemplo en la sección 2.2).

void guardar(tListaUsuarios const& usuarios, ofstream & archivo);
//Guarda la lista de usuarios en el flujo(ya abierto) archivo.

bool buscar(tListaUsuarios const& usuarios, string const& idUser, int &pos); 
//Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true, y si no existe en la lista, la posición que le correspondería
//y el valor false.

bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int &pos);
//Añade un usuario en la posición de la lista que le corresponde, si hay sitio para ello y no hay otro usuario con el mismo identificador.Además devuelve un booleano indicando
//si la operación tuvo éxito o no, y la posición donde se ha insertado.

bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos);
//Devuelve true y la posición del primer usuario del nivel dado que está esperando para iniciar una partida.Si no existe devuelve false.

//EXTRAS
void desplazarDerecha(tListaUsuarios & usuarios, int pos);

#endif //LISTAUSUARIO_H