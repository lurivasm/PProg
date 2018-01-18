/**
 * @file stack.h
 * @author Pablo Marcos pablo.marcosm@estudiante.uam.es
 * @author Jorge Arellano jorge.arellano@estudiante.uam.es
 * @date 6 oct 2017
 * @brief Definicion pila generica
 *
 * Definicion de pila generica. Utiliza memoria dinamica
 * para almacenar los datos.
 * Nota: No es thread-safe
 */

#ifndef STACK_H
#define STACK_H

#include "basic_types.h"
#include "generic_collections_types.h"

#include <stdio.h>

typedef struct _Stack Stack;

/**------------------------------------------------------------------
Inicializa la pila reservando memoria y almacenando los tres punteros a función pasados como parámetro (el primero para destruir elementos, el segundo para copiar elementos y el tercero para imprimir elementos). Salida: NULL si ha habido error o la pila si ha ido bien
------------------------------------------------------------------*/
Stack* stack_ini(destroy_element_function_type, copy_element_function_type, print_element_function_type, cmp_element_function_type);
/**------------------------------------------------------------------
Elimina la pila Entrada: la pila que se va a eliminar
------------------------------------------------------------------*/
void stack_destroy(Stack*);
/**------------------------------------------------------------------
Inserta un elemento en la pila. Entrada: un elemento y la pila donde insertarlo. Salida: NULL si no logra insertarlo o la pila resultante si lo logra
------------------------------------------------------------------*/
Stack* stack_push(Stack*, const void*);
/**------------------------------------------------------------------
Extrae un elemento en la pila. Entrada: la pila de donde extraerlo. Salida: NULL si no logra extraerlo o el elemento extraido si lo logra. Nótese que la pila quedará modificada
------------------------------------------------------------------*/
void* stack_pop(Stack*);
/**------------------------------------------------------------------
Copia un elemento (reservando memoria) sin modificar el top de la pila. Entrada: la pila de donde copiarlo. Salida: NULL si no logra copiarlo o el elemento si lo logra
------------------------------------------------------------------*/
void* stack_top(const Stack*);
/**------------------------------------------------------------------
Devuelve el puntero del elemento en el top de la pila Salida: NULL si falla o el elemento si lo logra
------------------------------------------------------------------*/
void* stack_get_top(Stack*);
/**------------------------------------------------------------------
Comprueba si la pila esta vacia. Entrada: pila. Salida: TRUE si está vacia o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack*);
/**------------------------------------------------------------------
Comprueba si la pila esta llena. Entrada: pila. Salida: TRUE si está llena o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isFull(const Stack*);
/**------------------------------------------------------------------
Imprime toda la pila, colocando el elemento en la cima al principio de la impresión (y un elemento por línea). Entrada: pila y fichero donde imprimirla. Salida: Devuelve el número de caracteres escritos.
------------------------------------------------------------------*/
int stack_print(FILE*, const Stack*);
/**------------------------------------------------------------------
Devuelve el tamano de la pila
------------------------------------------------------------------*/
int stack_size(const Stack*);
/**------------------------------------------------------------------
Compara dos pilas, devuelve 0 si son iguales. Si los tipos de las pilas son diferentes el resultado es indefinido.
------------------------------------------------------------------*/
int stack_cmp(const Stack*, const Stack*);
/**------------------------------------------------------------------
Devuelve una copia de la pila, la cual habra que liberar tambien.
------------------------------------------------------------------*/
Stack* stack_copy(Stack* stack);

#endif /* STACK_H */

