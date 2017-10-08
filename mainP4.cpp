//Marco Desantes Gutierrez


#include "Gestor.h"

void menuRegistro(tGestor &gestor);
bool AccederCuenta(tGestor &gestor);
void mostrarDatosUsu(tGestor &gestor);
void mostrarPartidasEnCurso(tGestor &gestor);
void menuUsuario(tGestor &gestor);
void leerJugada(int &col);
void menuPartida(tGestor & gestor);
bool elegirPartida(tGestor &gestor);
//era void, lo hago bool

int main(){
	tGestor gestor;
	if (arrancar(gestor)){
		generarAccesos(gestor);
		menuRegistro(gestor);
		apagar(gestor);
	}
	else
	{
		cout << "No se puedo arrancar el gestor";
		system("pause");
	}
	return 0;
}

void menuRegistro(tGestor &gestor){

	int opcion;
	do{

		cout << "MENU REGISTRO" << endl;
		cout << "\t1. Acceder a mi cuenta." << endl;
		cout << "\t2. Registrarse." << endl;
		cout << "\t0. Salir." << endl;
		cout << "Elija una opcion: ";

		cin >> opcion;
		while (opcion < 0 || opcion > 2){

			cout << "Error. Elige una opcion: ";
			cin >> opcion;

		}


		if (opcion == 1)
		{
			if (AccederCuenta(gestor))
			{
				mostrarDatosUsu(gestor);
				menuUsuario(gestor);
			}
			else cout << "Error. Usuario o clave incorrecto.\n\n";
			system("pause");

			system("cls");
		}
		else if (opcion == 2)
		{
			string usuario;
			string clave;

			cout << "Introduzca su nombre : ";
			cin >> usuario;
			cout << "Introduzca su clave: ";
			cin >> clave;
			if (crearCuenta(gestor, usuario, clave)) cout << "Usuario creado correctamente.";
			else cout << "Error. no se ha podido crear el usuario.\n\n";
		}



	} while (opcion != 0);
}

void menuUsuario(tGestor &gestor){
	char opcion;

	do{
		system("cls");
		mostrarPartidasEnCurso(gestor);
		cout << "\n\n\t1. Ver partida\n";
		cout << "\t2. Nueva partida\n";
		cout << "\t3. Partidas por actualizacion\n";
		cout << "\t4. Partidas por turno y fecha\n";
		cout << "\t0. Salir\n";
		cout << "Elija una opcion: ";
		cin >> opcion;
		while (opcion < '0' || opcion > '4')
		{
			cout << "Elija una opcion: ";
			cin >> opcion;
		}

		if (opcion == '1')
		{
			if (elegirPartida(gestor))
			{
				system("cls");
				menuPartida(gestor);
			}
		}
		else if (opcion == '2')
		{
			if (nuevaPartida(gestor));
			else
			{
				cout << "No se pueden crear mas partidas o no hay contrincantes disponibles(Tu estado pasara a estar esperando).\n";
				system("pause");
			}
		}
		else if (opcion == '3') ordenarFecha(gestor);
		else if (opcion == '4')
		{
			ordenarFecha(gestor);
			ordenarTurno(gestor);
		};
	} while (opcion != '0');


}

void menuPartida(tGestor & gestor){

	int opcion;
	mostrar(gestor.listapartidas.partida[gestor.partidaindice].juego, gestor.listapartidas.partida[gestor.partidaindice].jugador1, gestor.listapartidas.partida[gestor.partidaindice].jugador2);
	cout << "\t1. Jugar\n\t2. Abandonar\n\t3. Salir\nElija una opcion: ";
	cin >> opcion;
	while (opcion != 1 && opcion != 2 && opcion != 3)
	{
		cout << "Elija una opcion: ";
		cin >> opcion;
	}
	if (opcion == 1)
	{
		int cols;
		leerJugada(cols);
		jugarPartida(gestor, cols);

	}
	else if (opcion == 2) abandonarPartida(gestor);
	


}
//OPCION1
bool AccederCuenta(tGestor &gestor){

	bool Acceder = false;
	cout << "\nNombre el usuario: ";
	string nombre;
	cin >> nombre;
	cout << "clave: ";
	string clave;
	cin >> clave;
	if (iniciarSesion(gestor, nombre, clave))
	{
		Acceder = true;
		cout << "\nHa abierto correctamente una nueva sesion.\n\n";
	}
	return Acceder;
}

void mostrarDatosUsu(tGestor &gestor){

	string avisos;
	if (tieneAvisos(gestor, avisos)){
		char opcion;
		cout << "Tiene avisos:\n";
		cout << avisos << "\n\n";

		cout << "Quiere borrar los avisos (S/N)? ";
		cin >> opcion;
		while (opcion != 'S' && opcion != 'N')
		{
			cout << "opcion incorrecta.\n(S/N): ";
			cin >> opcion;
		}
		if (opcion == 'S') limpiarAvisos(gestor);

		cout << resumenActividad(gestor) << "\n\n";
	}
}

void mostrarPartidasEnCurso(tGestor &gestor){
		cout << "# T\tJUGADOR1\tJUGADOR2\tFECHA\n----------------------------------------------\n";
		for (int i = 0; i < gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.contador; i++)
		{
			cout << i+1 << cabecera(gestor, i);
		}
		
	}

bool elegirPartida(tGestor &gestor){
	
	int i;
	cout << " A que partida quiere jugar( 0 para salir ): ";
	cin >> i;
	i -= 1;
	while (i < -1 || i > gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.contador)
	{
		cout << " A que partida quiere jugar( 0 para salir ): ";
		cin >> i;
		i -= 1;
	}
	if (i != -1)
	{
		gestor.partidaindice = gestor.listausuarios.usuarios[gestor.usuarioindice].listaacceso.PartidasEnCurso[i].enlace;
		return true;
	}
	else return false;
	
}

void leerJugada(int &col){

	cout << "Introduce la columna: ";
	cin >> col;
	col -= 1;
	while (col < 0 || col > COLS)
	{
		cout << "Introduce la columna: ";
		cin >> col;
		col -= 1;
	}

}
