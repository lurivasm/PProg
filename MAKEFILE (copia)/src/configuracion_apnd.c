
#include "configuracion_apnd.h"

#include "list.h"

#include <stdlib.h>

struct _ConfiguracionApnd {
    List* confs;
};

/* Inicializa una configuración no determinista */
ConfiguracionApnd* configuracionApndIni(void)
{
    ConfiguracionApnd* capnd = (ConfiguracionApnd*) calloc(1, sizeof(ConfiguracionApnd));
    if (!capnd)
        return NULL;

    /* Inicializamos una lista de automatas deterministas */
    capnd->confs = list_ini((destroy_element_function_type) configuracionApElimina,
                            (copy_element_function_type) configuracionApCopia,
                            (print_element_function_type) configuracionApImprime,
                            (cmp_element_function_type) configuracionCompara);

    return capnd;
}

/* Inserta una configuración determinista en una no determinista. Se realiza una
copia en memoria propia de la colección para el nuevo elemento y se asegura que
no haya duplicados*/
ConfiguracionApnd* configuracionApndInsert(ConfiguracionApnd* capnd,
        const ConfiguracionAp* p_cap)
{
    if (!capnd || ! p_cap)
        return NULL;

    /* Antes de anadir comprobamos que no este ya */

    /* En list.c/list.h modificador const de p_elem anadido por concordancia */
    if (list_belongs(capnd->confs, p_cap) != 1) {
        list_insertLast(capnd->confs, p_cap);
    }
    return capnd;
}

/* Se obtiene una configuración determinista de la no determinista, que
desaparece de la colección.
No se especifica el orden en el que se extrae */
ConfiguracionAp* configuracionApndExtract(ConfiguracionApnd* capnd)
{
    if (!capnd)
        return NULL;

    if (list_isEmpty(capnd->confs) == TRUE) {
        return NULL;
    }

    return list_extractFirst(capnd->confs);
}

/* Se devuelve 1 si está vacía y 0 en caso contrario */
int configuracionApndIsEmpty(const ConfiguracionApnd* capnd)
{
    if (!capnd)
        return 1;

    return (list_isEmpty(capnd->confs) == TRUE) ? 1 : 0;
}

/* Se devuelve el número de configuraciones deterministas que hay dentro de la no
determinista */
int configuracionApndSize(const ConfiguracionApnd* capnd)
{
    if (!capnd) {
        return -1;
    }

    return list_size(capnd->confs);
}

/* Se imprime todas las configuraciones deterministas. No se especifica en qué
orden */
int configuracionApndPrint(FILE* fd, const ConfiguracionApnd* capnd)
{
    if (!fd || !capnd)
        return 0;

    return list_print(fd, capnd->confs);
}

/* Se libera toda la memoria asociada con la configuracion no determinista */
void configuracionApndDestroy(ConfiguracionApnd* capnd)
{
    if (capnd) {
        list_destroy(capnd->confs);
        free(capnd);
    }
}

ConfiguracionAp* configuracionApndGet(ConfiguracionApnd* capnd, int i)
{
    if (!capnd) return NULL;
    return list_get(capnd->confs, i);
}

int configuracionApndTam(const ConfiguracionApnd* capnd)
{
    if (!capnd) return -1;
    return list_size(capnd->confs);
}
