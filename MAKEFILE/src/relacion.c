

#include "relacion.h"

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


struct _Relacion {
    char* nombre;
    uint8_t** adyacencia;
    uint8_t** transitivo;
    uint8_t** potencia;
    int num_nodos;
};

/*
 * Funciones internas para el manejo de las matrices de la relacion
 */
static uint8_t** matrix(int n);
static void free_matrix(uint8_t** matriz, int  n);
static void copy_matrix(uint8_t** matriz_dst, uint8_t** const matriz_src, int  n);
static void mult_matrix(uint8_t** matriz, uint8_t** const matriz1,  uint8_t** const matriz2, int  n);
static void union_matrix(uint8_t** matriz,  uint8_t** const matriz1, int  n, uint8_t* change);
static void print_matrix(FILE* fd, const char*  nombre, uint8_t** const matriz, int  n);

/*
 * Reserva memoria para una matriz cuadrada de bytes n x n
 */
static uint8_t** matrix(int n)
{
    uint8_t** matrix;
    register int i;

    matrix = (uint8_t**) calloc(n, sizeof(uint8_t*));
    if (!matrix) {
        return NULL;
    }

    for (i=0; i<n; i++) {
        matrix[i] = (uint8_t*) calloc(n, sizeof(uint8_t));
        if (NULL == matrix[i]) {
            free_matrix(matrix, n);
            return NULL;
        }
    }
    return matrix;
}

/*
 * Libera una matriz n x n
 */
static void free_matrix(uint8_t** matriz, int  n)
{
    register int i;
    if (matriz) {
        for (i=0; i<n; i++) {
            if (matriz[i]) free(matriz[i]);
        }
        free(matriz);
    }
}

static void copy_matrix(uint8_t** matriz_dst, uint8_t** const matriz_src, int  n)
{
    register int i,j;

    for (i=0; i < n; i++) {
        for (j=0; j < n; j++) {
            matriz_dst[i][j] = matriz_src[i][j];
        }
    }
}

/* Variacion de la multiplicacion usual de matrices
 * Donde los valores de la matriz solo toman valores 1 o 0
 * matriz = matriz1*matriz2
 *
 * El caso peor tiene el mismo rendimiento que la multiplicacion matricial estandar O(n^3)
 * El caso mejor tiene un coste de O(n^2) para matrices nxn
 */
static void mult_matrix(uint8_t** matriz, uint8_t** const matriz1, uint8_t** const matriz2, int  n)
{
    register int i,j,k;
    register uint8_t aux;

    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            aux = 0;
            for (k=0; k<n; k++) {
                if (matriz1[i][k] && matriz2[k][j]) {
                    aux=1;
                    break;
                }
            }
            matriz[i][j] = aux;
        }
    }
}

static void union_matrix(uint8_t** matriz, uint8_t** const matriz1, int  n, uint8_t* change)
{
    register int i,j;
    register uint8_t aux;

    *change = 0;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            aux = matriz[i][j] | matriz1[i][j];

            /* Si algun valor cambia modificamos la flag */
            if (matriz[i][j] != aux) *change = 1;


            matriz[i][j] = aux;
        }
    }
}

static void print_matrix(FILE* fd,const char* nombre, uint8_t** const matriz, int  n)
{
    int i,j;

    fprintf(fd,"\t\t%s\n", nombre);

    for (i=0; i<n; i++) {
        fprintf(fd,"\t[%d]\t",i);
        for (j=0; j<n; j++) {
            fprintf(fd," %" PRIu8 "   ",matriz[i][j]);
        }
        fprintf(fd,"\n");
    }
}


Relacion* relacionNueva(const char* nombre, int num_elementos)
{
    Relacion* relacion;

    if (!nombre || num_elementos < 0)
        return NULL;

    relacion = (Relacion*) calloc(1,sizeof(Relacion));
    if (NULL == relacion)
        return NULL;

    relacion->num_nodos = num_elementos;

    /* Reservamos memoria para el nombre */
    relacion->nombre = (char*)calloc(strlen(nombre)+1,sizeof(char));
    if (!relacion->nombre) {
        relacionElimina(relacion);
        return NULL;
    }
    strcpy(relacion->nombre,nombre);

    /* Reservamos para la matriz de adyacencia */
    relacion->adyacencia = matrix(num_elementos);
    if (!relacion->adyacencia) {
        relacionElimina(relacion);
        return NULL;
    }

    /* Reservamos para el cierre transitivo */
    relacion->transitivo = matrix(num_elementos);
    if (!relacion->transitivo) {
        relacionElimina(relacion);
        return NULL;
    }

    /* Reservamos para la matriz de potencia */
    relacion->potencia = matrix(num_elementos);
    if (!relacion->adyacencia) {
        relacionElimina(relacion);
        return NULL;
    }

    return relacion;
}

Relacion* relacionNombreCierre(Relacion* p_r, int num_steps)
{
    size_t len;
    if (NULL == p_r) return NULL;

    len = strlen(p_r->nombre);
    p_r->nombre = realloc(p_r->nombre,  len + num_steps + 1);
    memset(p_r->nombre + len, '+', num_steps);
    p_r->nombre[len + num_steps] = '\0';

    return NULL;
}

void relacionImprime(FILE* fd,const  Relacion* p_r)
{
    int i;
    if (!fd || ! p_r)
        return;

    fprintf(fd,"%s={\n",p_r->nombre);

    /* Imprimimos fila de columnas */
    fprintf(fd,"\t\t");
    for (i=0; i<p_r->num_nodos; i++) {
        fprintf(fd, "[%d]  ",i);
    }

    fprintf(fd,"\n");
    print_matrix(fd, "CIERRE", p_r->transitivo, p_r->num_nodos);

    fprintf(fd,"\n");
    print_matrix(fd, "POTENCIA i", p_r->potencia, p_r->num_nodos);

    fprintf(fd,"\n");
    print_matrix(fd, "RELACION INICIAL i", p_r->adyacencia, p_r->num_nodos);

    fprintf(fd,"}\n");
    return;
}

void relacionElimina(Relacion* p_r)
{
    if (NULL != p_r) {
        if (p_r->nombre) free(p_r->nombre);
        free_matrix(p_r->adyacencia, p_r->num_nodos);
        free_matrix(p_r->transitivo, p_r->num_nodos);
        free_matrix(p_r->potencia, p_r->num_nodos);
        free(p_r);
    }
}


Relacion* relacionCopia(const Relacion* p_r1)
{
    Relacion* p_r2;
    char* nombre;

    if (!p_r1) return NULL;

    /* Nombre auxiliar con ' al final */
    nombre = (char*) calloc(strlen(p_r1->nombre)+2,sizeof(char));
    sprintf(nombre,"%s'",p_r1->nombre);

    p_r2 = relacionNueva(nombre,p_r1->num_nodos);


    free(nombre);

    if (!p_r2) return NULL;

    /* Copiamos matrices */
    copy_matrix(p_r2->adyacencia, p_r1->adyacencia, p_r2->num_nodos);
    copy_matrix(p_r2->transitivo, p_r1->transitivo, p_r2->num_nodos);
    copy_matrix(p_r2->potencia, p_r1->potencia, p_r2->num_nodos);

    return p_r2;
}


Relacion* relacionInserta(Relacion* p_r, int i, int j)
{
    if (!p_r || i<0 || j < 0)
        return NULL;

    if (i >= p_r->num_nodos || j >= p_r->num_nodos)
        return NULL;

    p_r->adyacencia[i][j] = 1;
    p_r->transitivo[i][j] = 1;

    return p_r;
}

int  relacionTamano(const Relacion* p_r)
{
    if (!p_r)
        return 0;

    return p_r->num_nodos * p_r->num_nodos;
}


Relacion* relacionCierreTransitivo(Relacion* p_r)
{
    uint8_t change=1;
    uint8_t** matrix_aux;
    int step = 0;

    if (!p_r) return NULL;

    /* Reservamos memoria para la matriz auxiliar */
    matrix_aux = matrix(p_r->num_nodos);
    if (!matrix_aux) return NULL;

    /* Inicializamos matriz auxiliar con la de adyacencia */
    copy_matrix(matrix_aux, p_r->adyacencia,p_r->num_nodos);

    /* Algoritmo del cierre: Mientras haya cambios, do:*/
    /* Calculamos A^(n+1) = A^n * A (Variacion de la multiplicacion matricial) */
    /* Actualizamos A^n con el valor de A^(n+1)*/
    /* Hacemos la union con el cierre C U A^(n+1) y actualizamos cambio*/

    while (change) {
        mult_matrix(p_r->potencia, matrix_aux, p_r->adyacencia, p_r->num_nodos);
        copy_matrix(matrix_aux, p_r->potencia,p_r->num_nodos);
        union_matrix(p_r->transitivo, p_r->potencia, p_r->num_nodos, &change);
        step++;
    }

    /* Liberamos la matriz auxiliar */
    free_matrix(matrix_aux,p_r->num_nodos);

    /* Añadimos + por cada paso del cierre */
    relacionNombreCierre(p_r,step);

    return p_r;
}

int  relacionIJ(const Relacion* p_r,int i, int j)
{
    if (!p_r || i<0 || j < 0)
        return 0;

    if (i >= p_r->num_nodos || j >= p_r->num_nodos)
        return 0;

    return p_r->adyacencia[i][j];
}


int relacionCierreIJ(const Relacion* p_r, int i, int j)
{
    if (!p_r || i<0 || j < 0)
        return 0;

    if (i >= p_r->num_nodos || j >= p_r->num_nodos)
        return 0;

    return p_r->transitivo[i][j];
}
