#include "ListaAccesoPartidas.h"

void iniciar(tListaAccesoPartidas & lista){
	
	lista.contador = 0;
	
}

bool llena(tListaAccesoPartidas const& lista){
	
	return lista.contador == (MAX_PAR_US);
	
}

bool insertar(tListaAccesoPartidas & lista, tParIdEn par)
{

	if (!llena(lista))
	{ 
		lista.PartidasEnCurso[lista.contador] = par;
		lista.contador += 1;
		return true;
	}
	else return false;
	
}

bool buscar(tListaAccesoPartidas  const& lista, string const& ID, int &pos){

	bool encontrado = false;
	
	for (int i = 0; i < lista.contador && !encontrado; i++){
		
		if (lista.PartidasEnCurso[i].ID == ID)
		{
			encontrado = true;
			pos = i;
		}
	
	}
	return encontrado;
}


bool eliminarLista(tListaAccesoPartidas & lista, int pos){
	if ((pos < 0) || (pos >= lista.contador)) return false;
	else {
			suprimirIzq(lista, pos);
			lista.contador--;
			return true;
	}
}

bool eliminar(tListaAccesoPartidas &lista, string const& ID) {
	int pos = 0;
	if (buscar(lista,ID,pos))
		return eliminarLista(lista,pos);
	else return false;
}

void suprimirIzq(tListaAccesoPartidas &lista, int pos){

	for (int i = pos + 1; i < lista.contador; i++)
	lista.PartidasEnCurso[i - 1] = lista.PartidasEnCurso[i];
	
}