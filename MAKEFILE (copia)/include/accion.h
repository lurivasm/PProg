#ifndef ACCION_H
#define ACCION_H
#include "estado.h"
#include "palabra.h"


typedef struct _Accion Accion;

Accion* crearAccion(Estado* estado, Palabra* str);
int imprimeAccion(FILE* f, Accion* accion);
int comparaAccion(Accion* ac1, Accion* ac2);
Accion* copiaAccion(Accion* accion);
void freeAccion(Accion* accion);
Estado* getEstadoF(Accion* accion);
Palabra* getInsertaPila(Accion* accion);

int _imprimeAccion(FILE* f, const void* accion);
int _comparaAccion(const void* ac1, const void* ac2);
void* _copiaAccion(const void* accion);
void _freeAccion(void* accion);

#endif
