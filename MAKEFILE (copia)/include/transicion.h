#ifndef TRANSICION_H
#define TRANSICION_H

#include "accion.h"
#include "list.h"


typedef struct _Transicion Transicion;

Transicion* creaTransicion(Estado* estado, char* cima_pila, char* cima_palabra);
Transicion* insertaAccion(Transicion* trans, Accion* accion);
List* getAcciones(Transicion* trans);
void liberaTransicion(Transicion* trans);
int esTransicion(Transicion* trans, Estado* estado, char* cima_pila, char* cima_palabra);
Transicion* copiaTransicion(Transicion* trans);
int imprimeTransicion(FILE* f, Transicion* trans);
int comparaTransicion(Transicion* t1, Transicion* t2);

void _liberaTransicion(void* trans);
void* _copiaTransicion(const void* trans);
int _imprimeTransicion(FILE* f, const void* trans);
int _comparaTransicion(const void* t1, const void* t2);



#endif