#include "transicion.h"

/*en estas transiciones puede ser NULL la cima_palabra*/
struct _Transicion {
    Estado* estado;
    char* cima_pila;  /*cima de la pila*/
    char* cima_palabra;  /*letra que leo*/
    List* acciones;
};

Transicion* creaTransicion(Estado* estado, char* cima_pila, char* cima_palabra)
{

    Transicion* t;

    if (!estado || !cima_pila) return NULL;

    t = (Transicion*)calloc(1, sizeof(Transicion));
    if (!t) return NULL;

    t->estado = estado_copy(estado);

    t->cima_pila = calloc(strlen(cima_pila) + 1, sizeof(char));
    strcpy(t->cima_pila, cima_pila);

    if (cima_palabra) {
        t->cima_palabra = (char*)calloc(strlen(cima_palabra) + 1,sizeof(char));
        strcpy(t->cima_palabra, cima_palabra);
    } else {
        t->cima_palabra = NULL;
    }

    t->acciones = list_ini(_freeAccion, _copiaAccion, _imprimeAccion, _comparaAccion);

    return t;
}

Transicion* insertaAccion(Transicion* t, Accion* accion)
{

    t->acciones = list_insertFirst(t->acciones, (void*) accion);
    return t;
}

List* getAcciones(Transicion* trans)
{
    return trans->acciones;
}

void liberaTransicion(Transicion* trans)
{
    if (trans) {
        free(trans->cima_pila);
        if (trans->cima_palabra) free(trans->cima_palabra);
        list_destroy(trans->acciones);
        estadoElimina(trans->estado);
        free(trans);
    }
}
/*devuelve 2 si transito consumiendo entrada*/
/*devuelvo 1 si transito sin consumir entrada*/
/*me dice si debo transitar con la transicion dada si me encuentro ante estos valores en cienta conf determinista*/
int esTransicion(Transicion* trans, Estado* estado, char* cima_pila, char* cima_palabra)
{
    if (!trans) return -1;
    if (!cima_pila) return 0;
    if (strcmp(cima_pila, trans->cima_pila)) return 0;
    if (estadoCompara(estado, trans->estado)) return 0;
    if (trans->cima_palabra) {
        if (!cima_palabra)
            return 0;
        else
            if (strcmp(cima_palabra, trans->cima_palabra))
                return 0;
            else return 2;
    }
    return 1;
}

Transicion* copiaTransicion(Transicion* trans)
{
    Transicion* copia;
    int i;
    if (!trans) return NULL;
    copia = creaTransicion(trans->estado, trans->cima_pila, trans->cima_palabra);
    for (i=0; i<list_size(trans->acciones); i++) {
        copia->acciones = list_insertFirst(copia->acciones, list_get(trans->acciones, i));
    }
    return copia;
}

int imprimeTransicion(FILE* f, Transicion* trans)
{
    int a = 0; /* Contador de caracteres */

    /* Comprobacion de argumentos */
    if (NULL == f || NULL == trans) return 0;

    /* El formato de una transicion es
       [<cima pila> <estado inicial> <simbolo entrada>] ==> { ( <estado final> <accion en la pila> ) } */

    /* Impresion cima pila */
    a += fprintf(f, "[%s,", (trans->cima_pila) ? trans->cima_pila : "lambda");

    /* Impresion del estado inicial */
    a += estadoImprime(f, trans->estado);

    /* Impresion del simbolo de entrada */
    a += fprintf(f, ",%s] ==> ", (trans->cima_palabra) ? trans->cima_palabra : "lambda");

    /* Impresion de las acciones */
    a += list_print(f, trans->acciones);

    return a;
}
/*devuelve numero distinto de cero si algun valor de la tupla estado, cima_pila o cima_palabra no son iguales*/
int comparaTransicion(Transicion* t1, Transicion* t2)
{

    return estadoCompara(t1->estado, t2->estado) || strcmp(t1->cima_palabra, t2->cima_palabra)
           || strcmp(t1->cima_pila, t2->cima_pila);
}

void _liberaTransicion(void* trans)
{
    liberaTransicion((Transicion*) trans);
}
void* _copiaTransicion(const void* trans)
{
    return (void*) copiaTransicion((Transicion*)trans);
}
int _imprimeTransicion(FILE* f, const void* trans)
{
    return imprimeTransicion(f, (Transicion*)trans);
}
int _comparaTransicion(const void* t1, const void* t2)
{
    return comparaTransicion((Transicion*)t1, (Transicion*)t2);
}