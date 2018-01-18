/**
 * @file generic_string.c
 * @author Pablo Marcos pablo.marcosm@estudiante.uam.es
 * @author Jorge Arellano jorge.arellano@estudiante.uam.es
 * @date 6 oct 2017
 * @brief Implementación funciones para el manejo de string en la pila
 *
 * Implementacion de las funciones para imprimir, destruir y copiar
 * cadenas en la pila.
 */

#include "generic_string.h"

#include <stdlib.h>
#include <string.h>


int print_p_string(FILE* fd,const void* p_char)
{
    int w = fprintf(fd,"%s ",(char*)p_char);
    fflush(fd);

    return w;

}

int cmp_p_string(const void* p_char1, const void* p_char2)
{
    return strcmp((char*)p_char1,(char*)p_char2);
}

void destroy_p_string(void* p_char)
{
    if (p_char) free(p_char);
}

void* copy_p_string(const void* p_char)
{
    char* p_copy;

    if (!p_char) return NULL;

    p_copy = (char*) calloc(strlen(p_char) + 1, sizeof(char));
    if (!p_copy) return NULL;

    strcpy(p_copy, p_char);

    return p_copy;
}

