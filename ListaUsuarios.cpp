#include "ListaUsuarios.h"
#include <fstream>



bool cargar(tListaUsuarios & usuarios, ifstream & archivo){

	archivo >> usuarios.contador;

	for (int i = 0; i < usuarios.contador; i++)
	{
		cargar(usuarios.usuarios[i], archivo);
	}

	return !archivo.fail();

}


void guardar(tListaUsuarios const& usuarios, ofstream & archivo){

	archivo << usuarios.contador << endl;

	for (int i = 0; i < usuarios.contador; i++)
	{
		guardar(usuarios.usuarios[i], archivo);
	}

}

bool buscar(tListaUsuarios const& usuarios, string const& idUser, int &pos){

	int ini = 0, fin = usuarios.contador - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (idUser < usuarios.usuarios[mitad].nombre) fin = mitad - 1;
		else if (usuarios.usuarios[mitad].nombre < idUser) ini = mitad + 1;
		else encontrado = true;
	}
	
	if (encontrado) pos = mitad;
	else pos = ini;

	return encontrado;

}


bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int &pos){

	
		if (usuarios.contador == MAX_Usuarios) return false;
		else {
			int pos = 0;
			if (!buscar(usuarios,usuario.nombre,pos)) {
				desplazarDerecha(usuarios, pos);
				usuarios.usuarios[pos] = usuario;
				usuarios.contador++;
				return true;
			}
			else return false;
		}
	}

void desplazarDerecha(tListaUsuarios & usuarios, int pos){
	
	for (int i = usuarios.contador; i > pos; i--)
		usuarios.usuarios[i] = usuarios.usuarios[i - 1];
}

bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos){

	bool encontrado = false;

	for (int i = 0; i < usuarios.contador && !encontrado ; i++){
	
		if (usuarios.usuarios[i].nivel == nivel && usuarios.usuarios[i].espera)
		{
			pos = i;
			encontrado = true;
		}
	
	}
	return encontrado;
}