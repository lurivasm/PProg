#ifndef CONFIGURACIONAPND_H
#define CONFIGURACIONAPND_H

#include "configuracion_ap.h"

typedef struct _ConfiguracionApnd ConfiguracionApnd;

/* Inicializa una configuración no determinista */
ConfiguracionApnd* configuracionApndIni();

/* Inserta una configuración determinista en una no determinista. Se realiza una
copia en memoria propia de la colección para el nuevo elemento y se asegura que
no haya duplicados*/
ConfiguracionApnd* configuracionApndInsert(ConfiguracionApnd* capnd, const
        ConfiguracionAp* p_cap);

/* Se obtiene una configuración determinista de la no determinista, que
desaparece de la colección.
No se especifica el orden en el que se extrae */
ConfiguracionAp* configuracionApndExtract(ConfiguracionApnd* capnd);

/* Se devuelve 1 si está vacía y 0 en caso contrario */
int configuracionApndIsEmpty(const ConfiguracionApnd* capnd);

/* Se devuelve el número de configuraciones deterministas que hay dentro de la no
determinista */
int configuracionApndSize(const ConfiguracionApnd* capnd);

/* Se imprime todas las configuraciones deterministas. No se especifica en qué
orden */
int configuracionApndPrint(FILE* fd, const ConfiguracionApnd* capnd);

/* Se libera toda la memoria asociada con la configuracion no determinista */
void configuracionApndDestroy(ConfiguracionApnd* capnd);

/*toma la configuracion determinista i del automata*/
ConfiguracionAp* configuracionApndGet(ConfiguracionApnd* capnd, int i);

/*devulve numero de configuraciones deterministas del automata*/
int configuracionApndTam(const ConfiguracionApnd* capnd);

#endif
