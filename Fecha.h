#ifndef FECHA_H
#define FECHA_H

#include <ctime>
#include <string>
using namespace std;

typedef time_t tFecha;

//Fecha Actual
inline tFecha fechaActual() { return time(0); }
//Fecha Completa
string stringFecha(tFecha fecha, bool hora);


#endif //FECHA_H