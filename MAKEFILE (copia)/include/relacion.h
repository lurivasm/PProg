
#ifndef RELACION_H
#define RELACION_H

#include <stdio.h>

typedef struct _Relacion Relacion;

/*
Crea una nueva relación a la que se le da como nombre el proporcionado como argumento para un conjunto con el número de elementos que se prorpociona como argumento.
Debe reservar memoria propia para todas las componentes que decidas utilizar en la relación.
*/
Relacion* relacionNueva(const char* nombre, int num_elementos);

/*
Muestra por el FILE * la relación. Puedes suponer el formato de salida utilizado en los ejemplos.
*/
void relacionImprime(FILE* fd,const Relacion* p_r);

/*
Libera toda la memoria asociada con la relación.
*/
void relacionElimina(Relacion* p_r);

/*
Genera en memoria nueva una copia de la relación proporcionada como argumento y la devuelve.
*/
Relacion* relacionCopia(const Relacion* p_r1);

/*
Modifica la relación proporcionada como argumento para que tenga constancia de que el elemento i está relacionado con el j.
Se está suponiendo que los elementos están dispuestos en un orden precondebido y conocido por el usuario de la librería.
Una vez modificada, la relación es también devuelta.
*/
Relacion* relacionInserta(Relacion* p_r, int i, int j);

/*
Devuelve el cardinal del conjunto sobre el que está definida la relación.
*/
int  relacionTamano(const Relacion* p_r);

/*
Modifica la relación para conservar el ella su cierre transitivo. Devuelve la relación como retorno.
*/
Relacion* relacionCierreTransitivo(Relacion* p_r);

/*
Devuelve 1 si el elemento i está relacionado originalmente con el j y 0 en caso contrario.
*/
int  relacionIJ(const Relacion* p_r,int i, int j);

/*
Devuelve 1 si el elemento i está relacionado (en el cierre transitivo) con el j y 0 en el caso contrario.
*/
int relacionCierreIJ(const Relacion* p_r, int i, int j);

#endif /* RELACION_H */
