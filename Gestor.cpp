#include "Gestor.h"

bool arrancar(tGestor & gestor){

	ifstream Usuarios;
	ifstream Partidas;
	bool cargar1, cargar2;
	
	Partidas.open("partidas.txt");
	cargar1 = cargar(gestor.listapartidas, Partidas);

	Usuarios.open("usuarios.txt");
	cargar2 = cargar(gestor.listausuarios, Usuarios);
	
	Usuarios.close();
	Partidas.close();

	return cargar1 && cargar2;
}

void apagar(tGestor & gestor){

	ofstream Usuarios;
	ofstream Partidas;

	Partidas.open("partidas.txt");
	guardar(gestor.listapartidas, Partidas);

	Usuarios.open("usuarios.txt");
	guardar(gestor.listausuarios, Usuarios);
	
	Usuarios.close();
	Partidas.close();

}

bool crearCuenta(tGestor &gestor, string const &idUsu, string const &clave){

	bool creado = false;
	tUsuario usuario;
					
			iniciar(usuario, idUsu, clave);
			creado = insertar(gestor.listausuarios,usuario, gestor.partidaindice);
				

	return creado;
}

bool iniciarSesion(tGestor & gestor, string const &idUsu, string const &clave){
	

	if (buscar(gestor.listausuarios, idUsu,gestor.usuarioindice)){
		
		if (iniciarSesion(gestor.listausuarios.usuarios[gestor.usuarioindice], clave))
		{
			
			return true;
		}
		else return false;
	
	}
	else return false;
}

void limpiarAvisos(tGestor &gestor){
	
	limpiarAvisos(gestor.listausuarios.usuarios[gestor.usuarioindice]);

}

bool tieneAvisos(tGestor const &gestor, string &aviso){

	bool HayAvisos;


	HayAvisos = tieneAvisos(gestor.listausuarios.usuarios[gestor.usuarioindice], aviso);

	return HayAvisos;
}

string resumenActividad(tGestor const &gestor){
	
	string resumen;
	resumen = resumenActividad(gestor.listausuarios.usuarios[gestor.usuarioindice]);
	return resumen;

}

void generarAccesos(tGestor & gestor){
	
	tParIdEn PartidaJugador;

	for (int i = 0; i < gestor.listapartidas.contador; i++)
	{
		int pos;
		if (gestor.listapartidas.partida[i].estadoPartida == EnCurso)
		{
			buscar(gestor.listausuarios, gestor.listapartidas.partida[i].jugador1, pos);
			PartidaJugador.ID = gestor.listapartidas.partida[i].ID;
			PartidaJugador.enlace = i;
			insertar(gestor.listausuarios.usuarios[pos].listaacceso,PartidaJugador);
			buscar(gestor.listausuarios, gestor.listapartidas.partida[i].jugador2, pos);
			PartidaJugador.ID = gestor.listapartidas.partida[i].ID;
			PartidaJugador.enlace = i;
			insertar(gestor.listausuarios.usuarios[pos].listaacceso, PartidaJugador);
		}
	}

}

int partidasUsuario(tGestor const& gestor){

	return gestor.listausuarios.usuarios[gestor.partidaindice].listaacceso.contador;

}

bool nuevaPartida(tGestor & gestor){

	bool encontrado = false;
	int pos;
	gestor.listausuarios.usuarios[gestor.usuarioindice].espera = false;
	if (!llena(gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso) && buscarUsuarioEsperando(gestor.listausuarios, gestor.listausuarios.usuarios[gestor.usuarioindice].nivel, pos) && gestor.listapartidas.contador < MAX)
	{
		encontrado = true;
		gestor.listausuarios.usuarios[gestor.usuarioindice].espera = false;
		tParIdEn partidanew;
		tPartida partida;
		nueva(partida, gestor.listausuarios.usuarios[gestor.usuarioindice].nombre, gestor.listausuarios.usuarios[pos].nombre);
		insertar(gestor.listapartidas, partida, gestor.partidaindice);
		partidanew.ID = partida.ID;
		partidanew.enlace = gestor.partidaindice;
		nuevaPartida(gestor.listausuarios.usuarios[gestor.usuarioindice], partidanew);
		nuevaPartida(gestor.listausuarios.usuarios[pos], partidanew);
	}
	else gestor.listausuarios.usuarios[gestor.usuarioindice].espera = true;
	return encontrado;
}

string cabecera(tGestor const& gestor, int posEnCurso){
	
	string resultado;
	if (gestor.listapartidas.partida[gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[posEnCurso].enlace].juego.turno == Jugador1 && 
	gestor.listausuarios.usuarios[gestor.usuarioindice].nombre == gestor.listapartidas.partida[gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[posEnCurso].enlace].jugador1)
				resultado = resultado + " *" + cabecera(gestor.listapartidas.partida[gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[posEnCurso].enlace]) + "\n";
	else resultado = resultado + "  " + cabecera(gestor.listapartidas.partida[gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[posEnCurso].enlace]) + "\n";

	return resultado;

}

void apuntaPartida(tGestor &gestor, int posParEnCurso)
{
	
	gestor.partidaindice = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[posParEnCurso].enlace;
}

void mostrarPartida(tGestor const& gestor){

	cout << EstadoPartida[gestor.listapartidas.partida[gestor.partidaindice].estadoPartida];

}

bool esSuTurno(tGestor &gestor){
	
	if (gestor.listapartidas.partida[gestor.partidaindice].juego.turno == Jugador1 && gestor.listapartidas.partida[gestor.partidaindice].jugador1 == gestor.listausuarios.usuarios[gestor.usuarioindice].nombre)
	{
		return true;
	}
	else if (gestor.listapartidas.partida[gestor.partidaindice].juego.turno == Jugador2 && gestor.listapartidas.partida[gestor.partidaindice].jugador2 == gestor.listausuarios.usuarios[gestor.usuarioindice].nombre)
	{
		return true;
	}
	else return false;	

}

void abandonarPartida(tGestor &gestor){

	int pos, pos2;
	//Deja la partida en lista de partidas finalizada.
	abandonar(gestor.listapartidas.partida[gestor.partidaindice]);

	buscar(gestor.listausuarios, gestor.listapartidas.partida[gestor.partidaindice].jugador1, pos);
	buscar(gestor.listausuarios, gestor.listapartidas.partida[gestor.partidaindice].jugador2, pos2);
	//Elimina acceso Jugador1.
	if (gestor.listausuarios.usuarios[pos].nombre == gestor.listausuarios.usuarios[gestor.usuarioindice].nombre){

		aplicarFinPartida(gestor.listausuarios.usuarios[pos], gestor.listapartidas.partida[gestor.partidaindice].ID, Pierde);
		aplicarFinPartida(gestor.listausuarios.usuarios[pos2], gestor.listapartidas.partida[gestor.partidaindice].ID, Gana);
		actualizarAvisos(gestor.listausuarios.usuarios[pos2], "Ha ganado por abandono una partida contra " + gestor.listausuarios.usuarios[pos].nombre + ".");

	}
	else
	{
		aplicarFinPartida(gestor.listausuarios.usuarios[pos], gestor.listapartidas.partida[gestor.partidaindice].ID, Gana);
		aplicarFinPartida(gestor.listausuarios.usuarios[pos2], gestor.listapartidas.partida[gestor.partidaindice].ID, Pierde);
		actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha ganado por abandono una partida contra " + gestor.listausuarios.usuarios[pos2].nombre + ".");
	}
}

void ordenarTurno(tGestor &gestor){

	tParIdEn elemento;
	int j;
	bool jota;
	bool jotamenos;
	for (int i = 1; i< gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.contador; ++i)
	{
		elemento = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[i];
		j = i;
		gestor.partidaindice = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j].enlace;
		jota = esSuTurno(gestor);
		gestor.partidaindice = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j-1].enlace;
		jotamenos = esSuTurno(gestor);
		while ((j > 0) && jota && !jotamenos)
		{
			gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j] = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j - 1];
			j--;
			gestor.partidaindice = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j - 1].enlace;
			jotamenos = esSuTurno(gestor);
		}
	gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j] = elemento;
	}

}

void ordenarFecha(tGestor &gestor){

	tParIdEn elemento;
	int j;
		
	for (int i = 1; i< gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.contador; ++i)
	{
		elemento = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[i];
		j = i;
		while ((j > 0) && gestor.listapartidas.partida[gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j].enlace].actualizacion
			< gestor.listapartidas.partida[gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j-1].enlace].actualizacion)
		{
			gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j] = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j - 1];
			j--;
		}
		gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[j] = elemento;
	}

}

void jugarPartida(tGestor &gestor, int col){
	
	string aviso;
	int pos;
	aplicarJugada(gestor.listapartidas.partida[gestor.partidaindice].juego,col);
	if (gestor.listapartidas.partida[gestor.partidaindice].juego.estado == Ganador)
	{
		gestor.listapartidas.partida[gestor.partidaindice].estadoPartida = Terminada;
		aplicarFinPartida(gestor.listausuarios.usuarios[gestor.usuarioindice], gestor.listapartidas.partida[gestor.partidaindice].ID, Gana);
		buscar(gestor.listausuarios, gestor.listapartidas.partida[gestor.partidaindice].jugador2, pos);
		if (pos != gestor.usuarioindice)
			aplicarFinPartida(gestor.listausuarios.usuarios[pos], gestor.listapartidas.partida[gestor.partidaindice].ID, Pierde);
		else
		{
			buscar(gestor.listausuarios, gestor.listapartidas.partida[gestor.partidaindice].jugador1, pos);
			aplicarFinPartida(gestor.listausuarios.usuarios[pos], gestor.listapartidas.partida[gestor.partidaindice].ID, Pierde);
			actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha perdido una partida contra " + gestor.listapartidas.partida[gestor.partidaindice].jugador2 + "el dia " + stringFecha(fechaActual(), true));
		}
	}
	else if (gestor.listapartidas.partida[gestor.partidaindice].juego.estado == Bloqueo)
	{
		gestor.listapartidas.partida[gestor.partidaindice].estadoPartida = Terminada;
		buscar(gestor.listausuarios, gestor.listapartidas.partida[gestor.partidaindice].jugador1, pos);
		aplicarFinPartida(gestor.listausuarios.usuarios[pos], gestor.listapartidas.partida[gestor.partidaindice].ID, Empate);
		actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha empatado una partida contra " + gestor.listapartidas.partida[gestor.partidaindice].jugador2 + "el dia " + stringFecha(fechaActual(), true));
		buscar(gestor.listausuarios, gestor.listapartidas.partida[gestor.partidaindice].jugador2, pos);
		aplicarFinPartida(gestor.listausuarios.usuarios[pos], gestor.listapartidas.partida[gestor.partidaindice].ID, Empate);
		actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha empatado una partida contra " + gestor.listapartidas.partida[gestor.partidaindice].jugador1 + "el dia " + stringFecha(fechaActual(), true));
	}
	
}