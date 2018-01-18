#include "accion.h"

/*inserta_pila puede ser null*/
struct _Accion {
    Estado* estado_final;
    Palabra* inserta_pila;
};

Accion* crearAccion(Estado* estado, Palabra* str)
{

    Accion* accion;

    if (!estado) return NULL;
    accion = (Accion*) malloc(sizeof(Accion));
    if (!accion) return NULL;

    accion->estado_final = estado_copy(estado);
    if (str) accion->inserta_pila = palabraCopia(str);
    else accion->inserta_pila = NULL;
    return accion;
}

void freeAccion(Accion* accion)
{

    if (accion) {
        estadoElimina(accion->estado_final);
        if (accion->inserta_pila) palabraElimina(accion->inserta_pila);
        free(accion);
    }
}

Accion* copiaAccion(Accion* accion)
{
    if (!accion) return NULL;
    return crearAccion(accion->estado_final, accion->inserta_pila);
}

int comparaAccion(Accion* ac1, Accion* ac2)
{
    if (estadoCompara(ac1->estado_final, ac2->estado_final)) return 1;
    if (ac1->inserta_pila) {
        if (ac2->inserta_pila) {
            return palabraCompara(ac1->inserta_pila, ac2->inserta_pila);
        } else return 1;
    } else {
        if (ac2->inserta_pila) return 1;
    }
    return 0;
}

/*No hace falta imprimirla*/
int imprimeAccion(FILE* pf, Accion* accion)
{
    int a=0;
    if (!pf || !accion) return 0;
    a+=fprintf(pf, "(");
    a+=estadoImprime(pf, accion->estado_final);
    a+=fprintf(pf, ", ");
    if (NULL != accion->inserta_pila)
        a+=palabraImprime(pf, accion->inserta_pila);
    else
        a+=fprintf(pf, "[(0)]");

    a+=fprintf(pf, ")");
    return a;
}

Estado* getEstadoF(Accion* accion)
{
    if (!accion) return NULL;
    return accion->estado_final;
}
Palabra* getInsertaPila(Accion* accion)
{
    if (!accion) return NULL;
    return accion->inserta_pila;
}

int _imprimeAccion(FILE* f, const void* accion)
{
    return imprimeAccion(f, (Accion*) accion);
}

int _comparaAccion(const void* ac1, const void* ac2)
{
    return comparaAccion((Accion*)ac1, (Accion*)ac2);
}
void* _copiaAccion(const void* accion)
{
    return (void*) copiaAccion((Accion*)accion);
}
void _freeAccion(void* accion)
{
    freeAccion((Accion*)accion);
}

