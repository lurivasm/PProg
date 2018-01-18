#ifndef CONFIGURACIONAP_H
#define CONFIGURACIONAP_H

#include "estado.h"
#include "palabra.h"
#include "stack.h"

#include <stdio.h>

typedef struct _ConfiguracionAp ConfiguracionAp;

/* Se crea una configuración reservando memoria nueva para ella y para copiar
todas las componentes que se proporcionan como argumento */
ConfiguracionAp* configuracionApNueva(Estado* estado, Stack* pila, Palabra* cadena);

/* Se libera toda la memoria asociada con la configuracion */
void configuracionApElimina(ConfiguracionAp* p_cap);

/* Se muestra por pantalla la configuración */
void configuracionApImprime(FILE* fd, ConfiguracionAp* p_cap);

/* Se devuelve una copia en memoria nueva de la configuración */
ConfiguracionAp* configuracionApCopia(const ConfiguracionAp* p_cap);

/* Se utiliza para comparar dos configuraciones deterministas, devolviendo un
valor negativo, 0 o positivo en función de la comparación de sus componentes en
este orden: estados, pilas, cadenas. En el caso de que no sean iguales*/
int configuracionCompara(const ConfiguracionAp* p_cap1,const ConfiguracionAp* p_cap2);

Estado* getEstado(ConfiguracionAp* p_cap);

Stack* getPila(ConfiguracionAp* p_cap);

Palabra* getPalabra(ConfiguracionAp* p_cap);

int esConfiguracionFinal(ConfiguracionAp* p_cap);



#endif
