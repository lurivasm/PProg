/**
 * @file generic_string.h
 * @author Pablo Marcos pablo.marcosm@estudiante.uam.es
 * @author Jorge Arellano jorge.arellano@estudiante.uam.es
 * @date 6 oct 2017
 * @brief Definicion elementación funciones para el manejo de string en la pila
 *
 * Implementacion de las funciones para imprimir, destruir y copiar
 * cadenas en la pila.
 * Compilar con la macro CHECK_ARGS para realizar control para que los argumentos
 * sean validos. No se realiza por defecto por eficiencia ya que no es necesario
 * si se realiza la comprobacion a otro nivel.
 */

#ifndef GENERIC_STRING_H
#define GENERIC_STRING_H

#include <stdio.h>

int print_p_string(FILE* fd,const void* p_char);

int cmp_p_string(const void* p_char1, const void* p_char2);

void destroy_p_string(void* p_char);

void* copy_p_string(const void* p_char);

#endif /* GENERIC_STRING_H */
