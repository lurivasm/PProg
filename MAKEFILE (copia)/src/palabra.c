
#include "palabra.h"

#include <stdlib.h>
#include <string.h>

struct _Palabra {
    char** simbolos;
    int tam;
};

/* Crea una palabra nueva */
Palabra* palabraNueva()
{
    /*Inicializo el array al insertar primer simbolo*/
    /* Calloc inicializa la zona de memoria a 0, tam inicializado a 0 */
    Palabra* palabra= (Palabra*) calloc(1, sizeof(Palabra));
    if (!palabra)
        return NULL;

    return palabra;
}

/* Libera la memoria asociada con la palabra */
void palabraElimina(Palabra* p_p)
{
    int i;

    if (p_p) {
        if (p_p->simbolos) {
            for (i = 0; i < p_p->tam; i++) {
                free(p_p->simbolos[i]);
            }

            free(p_p->simbolos);
        }
        free(p_p);
    }
}


/* Muestra por el FILE * la palabra */
int palabraImprime(FILE* fd, Palabra* p_p)
{
    int i, a=0;

    if (!p_p || !fd)
        return 0;

    a+=fprintf(fd,"[(%d)",p_p->tam);

    for (i=0; i<p_p->tam; i++)
        a+=fprintf(fd, " %s", p_p->simbolos[i]);

    a+=fprintf(fd,"]");
    fflush(fd);
    return a;
}

/* Inserta una letra (que es un string - char * - ) en la palabra proporcionada
como argumento (modificándola, por tanto) y devuelve la palabra resultante. Para
ello debe hacer una copia en memoria nueva para la nueva letra */
Palabra* palabraInsertaLetra(Palabra* palabra, char* letra)
{
    if (!palabra || !letra)
        return NULL;

    palabra->tam++;

    /* Reservamos memoria para la nueva letra */
    palabra->simbolos = realloc(palabra->simbolos, palabra->tam * sizeof(char*));
    if (!palabra->simbolos)
        return NULL;

    palabra->simbolos[palabra->tam-1] = (char*) calloc((strlen(letra) + 1),sizeof(char));
    strcpy(palabra->simbolos[palabra->tam-1], letra);

    return palabra;
}


/* Devuelve la longitud de la palabra */
int palabraTamano(Palabra* p_p)
{
    if (!p_p)
        return -1;

    return p_p->tam;
}

/* Hace en memoria nueva una copia de la palabra y la devuelve */
Palabra* palabraCopia(Palabra* p_p)
{
    int i;
    Palabra* copia;

    if (!p_p)
        return NULL;

    copia = palabraNueva();
    if (!copia)
        return NULL;

    /* Insertamos cada una de las letras de la palbra original */
    for (i=0; i < p_p->tam; i++)
        palabraInsertaLetra(copia, p_p->simbolos[i]);

    return copia;
}

/* Para comparar dos palabras, devuelve un valor negativo, cero o positivo en
función de que todas las letras de la misma posición y de izquierda a derecha
sean iguales. En el caso de que no lo sean, se devuelve el strcmp de la primera
pareja de letras que no sean iguales */
int palabraCompara(Palabra* p_p1, Palabra* p_p2)
{
    int i,diff;

    if (!p_p1) {
        if (p_p2) return -1;
        else return 0;
    }
    if (!p_p2) return 1;
    for (i=0; i<p_p1->tam && i<p_p2->tam; i++) {
        diff=strcmp(p_p1->simbolos[i], p_p2->simbolos[i]);
        if (diff) return diff;
    }

    if (i < p_p2->tam) return -1;
    else
        if (i < p_p1->tam) return 1;
    return 0;
}

char* getTopPalabra(Palabra* pal)
{
    if (!pal || !pal->tam) return NULL;
    return pal->simbolos[0];
}

char* popPalabra(Palabra* pal)
{
    char* simbolo;
    int i;
    if (!pal || !pal->tam) return NULL;

    simbolo = pal->simbolos[0];
    for (i=0; i<pal->tam - 1; i++)
        pal->simbolos[i] = pal->simbolos[i + 1];
    pal->simbolos[pal->tam - 1] = NULL;
    pal->tam--;

    return simbolo;
}

int getTamPalabra(Palabra* pal)
{
    if (!pal) return -1;
    return pal->tam;
}

char** getSimbolos(Palabra* pal)
{
    if (!pal) return NULL;
    return pal->simbolos;
}

