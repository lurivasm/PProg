

#include "estado.h"

#include <stdlib.h>
#include <string.h>


struct _Estado {
    char* nombre;
    int tipo;
};

/* Reserva memoria nueva para el estado y para la cadena de su nombre, crea un
estado con las dos componentes que se le proporcionan como argumento */
Estado* estadoNuevo(char* nombre, int tipo)
{
    Estado* estado;

    if (!nombre)
        return NULL;

    estado = (Estado*) calloc(1,sizeof(Estado));
    if (!estado) return NULL;

    estado->nombre = (char*) calloc(strlen(nombre) + 1, sizeof(char));
    if (!nombre) {
        free(estado);
        return NULL;
    }

    strcpy(estado->nombre, nombre);
    estado->tipo = tipo;

    return estado;
}

/* Libera la memoria asociada con el estado */
void estadoElimina(Estado* p_s)
{
    if (p_s) {
        if (p_s->nombre) free(p_s->nombre);
        free(p_s);
    }
}

/* Muestra por el FILE * el estado */
int estadoImprime(FILE* fd, Estado* p_s)
{
    int a=0;
    if (!fd || ! p_s)
        return 0;


    if (p_s->tipo == INICIAL || p_s->tipo == INICIAL_Y_FINAL) {
        a+=fprintf(fd,"->");
    }

    a+=fprintf(fd,"%s",p_s->nombre);

    if (p_s->tipo == FINAL || p_s->tipo == INICIAL_Y_FINAL) {
        a+=fprintf(fd,"*");
    }

    fflush(fd);
    return a;
}

/* Función de comparación de estados por nombre, devuelve 1 si el estado tiene el
nombre proporcionado */
int estadoEs(Estado* p_s, char* nombre)
{

    if (!p_s || !nombre)
        return -1;

    return !strcmp(p_s->nombre, nombre) ? 1 : 0;
}

/* Devuelve (un puntero) al nombre del estado */
char* estadoNombre(Estado* p_s)
{

    if (!p_s)
        return NULL;

    return p_s->nombre;
}

/* Devuelve el tipo de estado */
int estadoTipo(Estado* p_s)
{
    if (!p_s)
        return -1;

    return p_s->tipo;
}

/* Se usa para comparar estados por su nombre y devuelve el strcmp de sus nombres */
int estadoCompara(Estado* p_s1, Estado* p_s2)
{
    return strcmp(p_s1->nombre, p_s2->nombre);
}

/* Se crea una copia en memoria nueva del estado proporcionado como argumento */
Estado* estado_copy(Estado* p_s)
{

    if (!p_s)
        return NULL;

    return estadoNuevo(p_s->nombre,p_s->tipo);
}

int _estadoCompara(const void* p_s1, const void* p_s2)
{
    return estadoCompara((Estado*)p_s1, (Estado*)p_s2);
}

void* _estado_copy(const void* p_s)
{
    return (void*)estado_copy((Estado*) p_s);
}

void _estadoElimina(void* p_s)
{
    estadoElimina((Estado*)p_s);
}

int _estadoImprime(FILE* fd, const void* p_s)
{
    return estadoImprime(fd, (Estado*)p_s);
}
