/**
 * @file stack.c
 * @author Pablo Marcos pablo.marcosm@estudiante.uam.es
 * @author Jorge Arellano jorge.arellano@estudiante.uam.es
 * @date 6 oct 2017
 * @brief Implementación pila generica
 *
 * Implementacion de pila generica. Utiliza memoria dinamica
 * para almacenar los datos.
 * Nota: No es thread-safe
 */

#include <stdlib.h>

#include "stack.h"


struct _Stack {

    destroy_element_function_type destroy;
    copy_element_function_type copy;
    print_element_function_type print;
    cmp_element_function_type cmp;

    void** elements;
    int size;
};

Stack* stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4)
{
    Stack* stack;

    if (!f1 || ! f2 || !f3 || !f4)
        return NULL;

    /* Calloc inicializa la zona de memoria a 0 */
    stack = (Stack*) calloc(1, sizeof(Stack));
    if (!stack) return NULL;

    stack->destroy = f1;
    stack->copy = f2;
    stack->print = f3;
    stack->cmp = f4;

    return stack;
}


Stack* stack_copy(Stack* stack)
{
    Stack* copy;
    int i=0;

    if (!stack)
        return NULL;

    /* Inicializamos copia de la pila */
    copy = stack_ini(stack->destroy, stack->copy, stack->print, stack->cmp);
    if (!copy) return NULL;

    /* Asignamos mismo tamaño */
    copy->size = stack->size;

    /* Reservamos memoria para el array de elementos */
    copy->elements = (void**) calloc(copy->size, sizeof(void*));
    if (!copy->elements) {
        free(copy);
        return NULL;
    }

    /* Realizamos una copia de cada uno de los elementos */
    for (i=0; i< copy->size; i++) {
        copy->elements[i] = stack->copy(stack->elements[i]);
    }

    return copy;
}



int stack_cmp(const Stack* stack1,const Stack* stack2)
{

    int i, diff;

    /* Comparamos los tamanos */
    if (stack1->size != stack2->size)
        return stack1->size - stack2->size;

    /* Comparamos elemento a elemento si difieren en alguno */
    for (i=0; i<stack1->size; i++) {
        diff = stack1->cmp(stack1->elements[i], stack2->elements[i]);
        if (diff != 0) {
            return diff;
        }
    }
    return 0;
}

void stack_destroy(Stack* stack)
{
    int i;

    if (stack) {
        if (stack->elements) {
            for (i = 0; i < stack->size; i++) {
                stack->destroy(stack->elements[i]);
            }

            free(stack->elements);
        }
        free(stack);
    }
}

Stack* stack_push(Stack* stack, const void* element)
{

    if (!stack || !element)
        return NULL;

    stack->size++;
    stack->elements = realloc(stack->elements, stack->size * sizeof(void*));
    if (!stack->elements) return NULL;

    stack->elements[stack->size-1] = stack->copy(element);
    return stack;
}


void* stack_pop(Stack* stack)
{

    void* element;

    if (!stack) return NULL;

    if (stack_isEmpty(stack)) return NULL;

    element = stack->elements[stack->size - 1];
    stack->size--;
    stack->elements = realloc(stack->elements, stack->size * sizeof(void*));

    return element;
}


void* stack_top(const Stack* stack)
{

    if (!stack) return NULL;

    if (stack_isEmpty(stack)) return NULL;

    return stack->copy(stack->elements[stack->size -1]);
}

void* stack_get_top(Stack* stack)
{

    if (!stack) return NULL;

    if (stack_isEmpty(stack)) return NULL;

    return stack->elements[stack->size -1];
}


Bool stack_isEmpty(const Stack* stack)
{

    if (!stack) return TRUE;

    return (stack->size == 0) ? TRUE : FALSE;

}


Bool stack_isFull(const Stack* stack)
{


    if (!stack) return TRUE;

    return FALSE;

}


int stack_print(FILE* fp, const Stack* stack)
{
    int i, write=0;

    if (!fp || !stack) return ERROR;

    write += fprintf(fp, "<");
    for (i=stack->size-1; i>= 0; i--)
        write += stack->print(fp, stack->elements[i]);

    write += fprintf(fp, ">");
    fflush(fp);

    return write;
}


int stack_size(const Stack* stack)
{
    if (!stack) return ERROR;

    return stack->size;
}
