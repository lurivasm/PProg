
#include "configuracion_ap.h"

#include <stdlib.h>

struct _ConfiguracionAp {
    Estado* estado;
    Stack* pila;
    Palabra* cadena;
};

/* Se crea una configuración reservando memoria nueva para ella y para copiar
todas las componentes que se proporcionan como argumento */
ConfiguracionAp* configuracionApNueva(Estado* estado, Stack* pila, Palabra* cadena)
{
    ConfiguracionAp* conf;

    if (!estado || !pila)
        return NULL;

    conf = (ConfiguracionAp*)calloc(1, sizeof(ConfiguracionAp));
    if (!conf)
        return NULL;

    conf->estado = estado_copy(estado);
    conf->pila = stack_copy(pila);
    if (cadena) conf->cadena = palabraCopia(cadena);
    else conf->cadena = NULL;

    return conf;
}

/* Se libera toda la memoria asociada con la configuracion */
void configuracionApElimina(ConfiguracionAp* p_cap)
{
    if (p_cap) {
        estadoElimina(p_cap->estado);
        stack_destroy(p_cap->pila);
        if (p_cap->cadena) palabraElimina(p_cap->cadena);
        free(p_cap);
    }
}

/* Se muestra por pantalla la configuración */
void configuracionApImprime(FILE* fd, ConfiguracionAp* p_cap)
{
    if (!fd || !p_cap)
        return;

    fprintf(fd,"(");
    estadoImprime(fd, p_cap->estado);
    fprintf(fd," ");
    stack_print(fd, p_cap->pila);
    fprintf(fd," ");
    palabraImprime(fd, p_cap->cadena);

    fprintf(fd,")");
    fflush(fd);
}

/* Se devuelve una copia en memoria nueva de la configuración */
ConfiguracionAp* configuracionApCopia(const ConfiguracionAp* p_cap)
{
    return configuracionApNueva(p_cap->estado, p_cap->pila, p_cap->cadena);
}

/* Se utiliza para comparar dos configuraciones deterministas, devolviendo un
valor negativo, 0 o positivo en función de la comparación de sus componentes en
este orden: estados, pilas, cadenas. En el caso de que no sean iguales*/
int configuracionCompara(const ConfiguracionAp* p_cap1, const ConfiguracionAp* p_cap2)
{

    int diff;

    diff = estadoCompara(p_cap1->estado, p_cap2->estado);
    if (diff) return diff;

    diff = stack_cmp(p_cap1->pila, p_cap2->pila);
    if (diff) return diff;

    diff = palabraCompara(p_cap1->cadena, p_cap2->cadena);
    return diff;

}

Estado* getEstado(ConfiguracionAp* p_cap)
{
    if (!p_cap) return NULL;
    return p_cap->estado;
}

Stack* getPila(ConfiguracionAp* p_cap)
{
    if (!p_cap) return NULL;
    return p_cap->pila;
}

Palabra* getPalabra(ConfiguracionAp* p_cap)
{
    if (!p_cap) return NULL;
    return p_cap->cadena;
}

/*devuelve 1 si es una configuracion de aceptacion de la cadena por vaciado de pila o por estado final*/
int esConfiguracionFinal(ConfiguracionAp* p_cap)
{
    int tipo;
    if (!p_cap) return -1;
    if (!p_cap->cadena || !palabraTamano(p_cap->cadena)) {
        tipo = estadoTipo(p_cap->estado);
        if (tipo == FINAL || tipo == INICIAL_Y_FINAL || stack_isEmpty(p_cap->pila)) return 1;
    }
    return 0;
}

