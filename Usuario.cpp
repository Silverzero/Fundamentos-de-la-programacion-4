#include "Usuario.h"


bool cargar(tUsuario & usuario, ifstream & archivo){
	int aux;
	archivo >> usuario.nombre;
	archivo >> usuario.contraseña;
	archivo >> aux;
	usuario.nivel = tNivel(aux);
	archivo >> usuario.racha >> usuario.espera;
	archivo >> usuario.ganadas >> usuario.perdidas >> usuario.empatadas;
	archivo >> usuario.ultimaConexion;
	archivo.ignore();
	string aux2;
	getline(archivo,aux2);
	while(aux2 != "_X_X_X_")
	{
		usuario.avisos += aux2 + "\n";
		getline(archivo, aux2);
	}	
	if (usuario.avisos != "") usuario.avisos.pop_back();
	iniciar(usuario.listaacceso);
	return !archivo.fail();
}

void guardar(tUsuario const& usuario, ofstream & archivo){

	archivo << usuario.nombre << endl;
	archivo << usuario.contraseña << endl;
	archivo << usuario.nivel << " " << usuario.racha << " " << usuario.espera << endl;
	archivo << usuario.ganadas << " " << usuario.perdidas << " " << usuario.empatadas << endl;
	archivo << usuario.ultimaConexion << endl;
	archivo << usuario.avisos << endl;
	archivo << "_X_X_X_" << endl;

}

void iniciar(tUsuario & usuario, string const& id, string const& pas){

	usuario.nombre = id;
	usuario.contraseña = pas;
	usuario.nivel = Principiante;
	usuario.racha = 0;
	usuario.espera = 0;
	usuario.ganadas = 0;
	usuario.perdidas = 0;
	usuario.empatadas = 0;
	usuario.ultimaConexion = fechaActual();
	usuario.avisos = "";
	iniciar(usuario.listaacceso);

}

bool iniciarSesion(tUsuario & usuario, string const& clave){

	if (usuario.contraseña == clave) usuario.ultimaConexion = fechaActual();



	return usuario.contraseña == clave;
}

void limpiarAvisos(tUsuario & usu){

	usu.avisos = "";

}

bool tieneAvisos(tUsuario const & usuario, string & avisos){

	if (usuario.avisos != "")
	{
		avisos = usuario.avisos;
		return true;
	}
	else return false;
	
}

string resumenActividad(tUsuario const &usuario){

	string resumen;
	ostringstream flujo;
	flujo << "\n\nResumen de actividad"
		  << "\nPartidas Ganadas: " << usuario.ganadas
		  << "\nPartidas Perdidas:" << usuario.perdidas
		  << "\nPartidas Empatadas:" << usuario.empatadas
		  << "\nNivel:" << NombreNivel[usuario.nivel]
		  << "\nRacha: " << usuario.racha;

	resumen = flujo.str();

	return  resumen;
}

bool nuevaPartida(tUsuario & usuario, tParIdEn const& par){

	if (insertar(usuario.listaacceso, par))
	{
		return true;
		usuario.espera = false;
	}
	else
	{
		usuario.espera = true;
		return false;
	}
}

void actualizarAvisos(tUsuario & usu, string const& aviso){

	usu.avisos = usu.avisos + aviso;

}

void aplicarFinPartida(tUsuario & usuario, string const& idPar, tResultado resultado){

	eliminar(usuario.listaacceso, idPar);

	if (resultado == Gana)
	{
		masNivel(usuario);
	}
	else if (resultado == Pierde)
	{
		menosNivel(usuario);
	}
	else
	{
		usuario.empatadas++;
		usuario.racha = 0;
	}

	

}

void masNivel(tUsuario & usuario){
	
	usuario.ganadas++;
	usuario.racha++;
	if (usuario.racha == NRN)
	{
		if (usuario.nivel == Principiante) usuario.nivel = Medio;
		else if (usuario.nivel == Medio) usuario.nivel = Experto;
	}
}

void menosNivel(tUsuario & usuario){

	usuario.perdidas++;
	usuario.racha--;
	if (usuario.racha == -NRN)
	{
		if (usuario.nivel == Experto) usuario.nivel = Medio;
		else if (usuario.nivel == Medio) usuario.nivel = Principiante;
	}
}