
#include "ap.h"

struct _AP {

    char* nombre;
    List* alfabeto_entrada;
    int n_alfabeto_entrada;
    List* alfabeto_pila;
    int n_alfabeto_pila;
    List* estados;
    int n_estados;
    Palabra* palabra;
    Relacion* relacion;
    List* transiciones;
    ConfiguracionApnd* conf_actual;

};


AP* APNuevo(char* nombre, int num_estados, int num_simbolos_entrada, int num_simbolos_pila)
{

    AP* ap;

    /* Comprobacion de parametros valido */
    if (!nombre || num_estados<1 || num_simbolos_entrada<1 || num_simbolos_pila<1)
        return NULL;

    /* Inicializamos el automata a pila */
    ap = (AP*) calloc(1, sizeof(AP));
    if (NULL == ap) return NULL;

    /* Inicializamos el nombre */
    ap->nombre = (char*) calloc(strlen(nombre) + 1, sizeof(char));
    strcpy(ap->nombre, nombre);

    /* Inicializamos alfabeto de pila vacio */
    ap->n_alfabeto_pila = num_simbolos_pila;
    ap->alfabeto_pila = list_ini(destroy_p_string, copy_p_string, print_p_string, cmp_p_string);

    /* Inicializamos alfabeto de entrada vacio */
    ap->n_alfabeto_entrada = num_simbolos_entrada;
    ap->alfabeto_entrada = list_ini(destroy_p_string, copy_p_string, print_p_string, cmp_p_string);

    /* Iniciamos lista con los estados */
    ap->n_estados = num_estados;
    ap->estados = list_ini(_estadoElimina, _estado_copy, _estadoImprime, _estadoCompara);

    /* Inicializamos la palabra de entrada */
    ap->palabra = palabraNueva();

    /* Inicializamos la configuracion inicial del automata */
    ap->conf_actual =  configuracionApndIni();

    /* Inicializamos la matriz con relaciones lambda */
    ap->relacion = relacionNueva("Lambda pura", num_estados);

    /* Inicializamos la lista que contendra las transiciones */
    ap->transiciones = list_ini(_liberaTransicion, _copiaTransicion, _imprimeTransicion, _comparaTransicion);

    return ap;
}

void APElimina(AP* p_ap)
{
    if (p_ap) {
        free(p_ap->nombre);
        list_destroy(p_ap->alfabeto_pila);
        list_destroy(p_ap->alfabeto_entrada);
        list_destroy(p_ap->estados);
        list_destroy(p_ap->transiciones);
        configuracionApndDestroy(p_ap->conf_actual);
        relacionElimina(p_ap->relacion);
        palabraElimina(p_ap->palabra);
        free(p_ap);
    }
}

void APImprime(FILE* fd, AP* p_ap)
{
    int i;
    if (NULL == fd || NULL == p_ap) return;

    /* Imprimimos los datos del automata */
    fprintf(fd, "AP={\t%s\n", p_ap->nombre);

    /* Alfabeto de entrada */
    fprintf(fd, "\n\tSigma = ");
    list_print(fd, p_ap->alfabeto_entrada);

    /* Alfabeto de la pila */
    fprintf(fd, "\n\n\tGamma = ");
    list_print(fd, p_ap->alfabeto_pila);

    /* Estados del automata */
    fprintf(fd, "\n\n\tQ = ");
    list_print(fd, p_ap->estados);

    /* Configuracion actual del automata */
    fprintf(fd, "\n\n\tConfiguracion actual:\n\t");
    configuracionApndPrint(fd, p_ap->conf_actual);

    /* Palabra a procesar */
    fprintf(fd, "\n\n\tCadena inicial:\n\t");
    palabraImprime(fd, p_ap->palabra);

    /* Matriz con relacion de lambdas puras */
    fprintf(fd, "\n\n\tTransiciones Lambda Puras:\n");
    relacionImprime(fd, p_ap->relacion);


    /* Transiciones no lambdas puras */
    fprintf(fd, "\tTransiciones que modifican la entrada o pila:\n");
    fprintf(fd, "\t[<cima pila> <estado inicial> <simbolo entrada>] ==> {(<estado final> <accion en la pila>) ... }\n\n");

    for (i=0; i<list_size(p_ap->transiciones); i++) {

        /* Imprimimos las transiciones una a una */
        fprintf(fd,"\t");
        imprimeTransicion(fd, (Transicion*) list_get(p_ap->transiciones, i));
        fprintf(fd, "\n\n");
    }
    fprintf(fd, "}\n");
}

AP* APInsertaSimboloAlfabetoEntrada(AP* p_ap, char* simbolo)
{
    /* Comprobacion de parametros */
    if (NULL == p_ap || NULL == simbolo) return NULL;

    /* Insertamos el simbolo, el orden del alfabeto sera in order (A-Za-z) */
    p_ap->alfabeto_entrada = list_insertInOrder(p_ap->alfabeto_entrada, (void*)simbolo);

    return p_ap;
}

AP* APInsertaSimboloAlfabetoPila(AP* p_ap, char* simbolo)
{
    /* Comprobacion de parametros */
    if (NULL == p_ap || NULL == simbolo) return NULL;

    /* Insertamos el simbolo, el orden del alfabeto sera in order (A-Za-z) */
    p_ap->alfabeto_pila = list_insertInOrder(p_ap->alfabeto_pila, (void*)simbolo);

    return p_ap;
}

AP* APInsertaEstado(AP*   p_ap, char* nombre, int tipo)
{
    Estado* e;
    /* Comprobacion de parametros */
    if (NULL == p_ap || NULL == nombre) return NULL;

    /* No podemos insertar mas estados que el limite fijado */
    if (list_size(p_ap->estados) >= p_ap->n_estados) return p_ap;

    /* Creamos un estado que insertaremos */
    e = estadoNuevo(nombre, tipo);
    if (!e) return p_ap;

    p_ap->estados = list_insertInOrder(p_ap->estados, e);

    /* La implementacion de list crea una copia del estado, lo liberamos */
    estadoElimina(e);

    return p_ap;
}

AP* APInsertaLTransicion(AP* p_ap, char* nombre_estado_i, char* nombre_estado_f)
{
    int i;
    int ini=-1, fin=-1;

    if (!p_ap || !nombre_estado_i || !nombre_estado_f) return NULL;

    /* Buscamos el indice de los estados pasados como argumento */
    for (i=0; i < list_size(p_ap->estados); i++) {
        if (estadoEs((Estado*)list_get(p_ap->estados, i), nombre_estado_i))
            ini = i;
        if (estadoEs((Estado*)list_get(p_ap->estados, i), nombre_estado_f))
            fin = i;
    }

    /* Si alguno de los estados no es correcto no insertamos la transicion */
    if (ini == -1 || fin == -1) return p_ap;

    p_ap->relacion = relacionInserta(p_ap->relacion, ini, fin);

    return p_ap;
}

AP* APInsertaTransicion(AP* p_ap, char* nombre_simbolo_pila,  char* nombre_estado_i,
                        char* nombre_estado_f, char* nombre_simbolo_entrada, Palabra* accion)
{

    int i;
    Transicion* t;
    Accion* accion_created;
    Estado* ini=NULL, *fin=NULL;

    if (!p_ap || !nombre_estado_i || !nombre_estado_f || !nombre_simbolo_pila) return NULL;

    /* Comprobamso que ambos estado se encuentran en el automata */
    for (i=0; i < list_size(p_ap->estados); i++) {
        if (estadoEs((Estado*)list_get(p_ap->estados, i), nombre_estado_i))
            ini = list_get(p_ap->estados, i);
        if (estadoEs((Estado*)list_get(p_ap->estados, i), nombre_estado_f))
            fin = list_get(p_ap->estados, i);
    }

    /* Devolvemos error si no se encuentran los estados */
    if (!ini || !fin) return NULL;

    /* Comprobamos si ya hay una transicion entre esos dos estados */
    for (i=0; i<list_size(p_ap->transiciones); i++) {
        t = list_get(p_ap->transiciones, i);

        /* Si ya es una transicion existente, insertamos una accion asociada*/
        if (esTransicion(t, ini, nombre_simbolo_pila, nombre_simbolo_entrada)) {
            accion_created = crearAccion(fin, accion);
            insertaAccion(t, accion_created);
            freeAccion(accion_created);
            break;
        }
    }

    /* Caso es transicion completamente nueva*/
    if (i==list_size(p_ap->transiciones)) {

        /* Creamos una transicion */
        t = creaTransicion(ini, nombre_simbolo_pila, nombre_simbolo_entrada);
        accion_created = crearAccion(fin, accion);
        insertaAccion(t, accion_created);
        freeAccion(accion_created);
        p_ap->transiciones = list_insertFirst(p_ap->transiciones, t);
        liberaTransicion(t);
    }

    return p_ap;

}

AP* APInsertaLetra(AP* p_ap, char* letra)
{
    if (NULL == p_ap || NULL == letra) return NULL;

    p_ap->palabra = palabraInsertaLetra(p_ap->palabra, letra);
    return p_ap;
}

AP* APCierraLTransicion(AP* p_ap)
{
    if (NULL == p_ap) return NULL;

    p_ap->relacion = relacionCierreTransitivo(p_ap->relacion);

    return p_ap;
}

AP* APInicializaEstado(AP* p_ap)
{
    int i, j;
    int tipo;
    Estado* est;
    Estado* aux;
    ConfiguracionAp* conf;
    Stack* pila;

    /* Itero sobre los estados y incluyo las transicciones lambda de los estados iniciales */
    for (i=0; i < list_size(p_ap->estados); i++) {

        est = (Estado*)list_get(p_ap->estados, i);
        tipo = estadoTipo(est);

        if (tipo == INICIAL || tipo == INICIAL_Y_FINAL) {
            for (j=0; j<list_size(p_ap->estados); j++) {

                /* Si existe la transicion lamba o se trata del propio estado lo incluyo en la configuracion actual */
                if (relacionCierreIJ(p_ap->relacion, i, j) || i==j) {

                    aux = list_get(p_ap->estados, j);
                    pila = stack_ini(destroy_p_string, copy_p_string, print_p_string, cmp_p_string);
                    pila = stack_push(pila, SIMBOLO_INICIO_PILA);
                    conf = configuracionApNueva(aux, pila, p_ap->palabra);
                    p_ap->conf_actual = configuracionApndInsert(p_ap->conf_actual, conf);
                    stack_destroy(pila);
                    configuracionApElimina(conf);
                }
            }
        }
    }
    return p_ap;
}

int APTransita(AP* p_ap)
{

    int i, j, k;
    int aceptado = 0; /* Flag para saber si la cadena es aceptada */
    int consume; /* Flag para saber si debe consumirse simbolo de pila */
    int transita; /* Flag para saber si podemos aplicar transicion */
    ConfiguracionAp* conf, *conf_ap_aux;
    Estado* estado, *estadof;
    Stack* pila, *pilaaux;
    Palabra* palabra, *palabra_pop;
    ConfiguracionApnd* conf_apnd_aux;
    Transicion* t;
    char* cima_pila, *cima_palabra, **array, *discard_top;
    List* acciones;
    Accion* accion;
    Palabra* inserta_pila;

    /* Control de errores */
    if (!p_ap) return -1;

    /* Creamos una configuracion auxiliar */
    conf_apnd_aux = configuracionApndIni();

    /* Comprobamos las transiciones no lambda que podemos aplicar */
    while (configuracionApndTam(p_ap->conf_actual)) {

        /* Extrameos una de las configuraciones del ap */
        conf = configuracionApndExtract(p_ap->conf_actual);
        estado = getEstado(conf);
        pila = getPila(conf);
        palabra = getPalabra(conf);

        /* Copia de palabra con el simbolo consumido  */
        palabra_pop = palabraCopia(palabra);
        discard_top = popPalabra(palabra_pop);
        if (NULL != discard_top) free(discard_top);

        /* Obtenemos la cima de la pila y el simbolo a consumir */
        cima_palabra = getTopPalabra(palabra);
        cima_pila = (char*)stack_pop(pila);

        /* Revisamos las transiciones para determinar que acciones podemos realizar */
        for (i=0; i<list_size(p_ap->transiciones); i++) {

            /* Obtenemos la transicion i-esima de la lista */
            t = (Transicion*) list_get(p_ap->transiciones, i);

            /* Comprobamos que podamos aplicar la transicion */
            transita = esTransicion(t, estado, cima_pila, cima_palabra);
            if (transita) {
                /* Guardamos si debemos consumir simbolo de pila */
                consume = transita - 1;

                /* Iteramos sobre las acciones de la transicion */
                acciones = getAcciones(t);
                for (j=0; j < list_size(acciones); j++) {
                    /* Obtenemos la accion j-esima de la transicion i-esima */
                    accion = (Accion*) list_get(acciones, j);
                    inserta_pila = getInsertaPila(accion);
                    estadof = getEstadoF(accion);
                    array = getSimbolos(inserta_pila);

                    /* Hacemos copia de la pila en orden inverso */
                    pilaaux = stack_copy(pila);
                    for (k = getTamPalabra(inserta_pila) - 1; k>=0; k--)
                        pilaaux = stack_push(pilaaux, array[k]);

                    /* Si consume simbolo insertamos la palabra con el simbolo consumido */
                    if (consume) conf_ap_aux = configuracionApNueva(estadof, pilaaux, palabra_pop);
                    else conf_ap_aux = configuracionApNueva(estadof, pilaaux, palabra);

                    /* Insertamos la nueva configuracion determinista en el apnd auxiliar */
                    conf_apnd_aux = configuracionApndInsert(conf_apnd_aux, conf_ap_aux);
                    stack_destroy(pilaaux);
                    configuracionApElimina(conf_ap_aux);
                }
            }
        }

        /* Liberamos configuraciones auxiliares utilizadas */
        configuracionApElimina(conf);
        palabraElimina(palabra_pop);
        free(cima_pila);
    }

    /* Iteramos sobre las configuraciones a las que hemos transitado */
    while (configuracionApndTam(conf_apnd_aux)) {
        /* Obtenemos cada uno de los ap del apnd auxiliar */
        conf_ap_aux = configuracionApndExtract(conf_apnd_aux);

        /* Si alguna de las configuraciones es final la cadena se aceptaria */
        if (esConfiguracionFinal(conf_ap_aux)) aceptado = 1;

        estado = getEstado(conf_ap_aux);
        /* Obtenemos el indice del estado en la relacion */
        for (k=0; k < list_size(p_ap->estados); k++) {
            estadof = (Estado*)list_get(p_ap->estados, k);
            if (!estadoCompara(estado, estadof)) {
                break;
            }
        }
        /* Miramos en el cierre transitivo las transiciones lamba aplicables a ese estado */
        for (j=0; j<list_size(p_ap->estados); j++) {
            /* Anadimos a la configuracion actual la correspondiente a nuestro estado */
            if (k == j) configuracionApndInsert(p_ap->conf_actual, conf_ap_aux);

            else /* En el resto de casos solo la incluimos si hay transicion lamba */
                if (relacionCierreIJ(p_ap->relacion, k, j)) {

                    estado = list_get(p_ap->estados, j);
                    conf = configuracionApNueva(estado, getPila(conf_ap_aux), getPalabra(conf_ap_aux));
                    p_ap->conf_actual = configuracionApndInsert(p_ap->conf_actual, conf);

                    /* Si de las configuraciones marcadas como lambda es final marcamos como aceptado */
                    /* Esto provocara que sepamos que la cadena se acepta una iteracion antes que
                       el ejemplo del enunciado */
                    if (esConfiguracionFinal(conf)) aceptado = 1;

                    configuracionApElimina(conf);
                }
        }

        configuracionApElimina(conf_ap_aux);
    }
    configuracionApndDestroy(conf_apnd_aux);

    return aceptado;
}

int APProcesaEntrada(FILE* fd, AP* p_ap)
{
    int i;
    int aceptado = 0;

    /* Imprimimos la entrada */
    fprintf(fd, "SE VA A PROCESAR LA ENTRADA   ");
    palabraImprime(fd,p_ap->palabra);

    /* Imprimimos la configuracion inicial */
    fprintf(fd, "\n\nA PARTIR DE ESTA CONFIGURACION INICIAL:\n");
    configuracionApndPrint(fd, p_ap->conf_actual);
    fprintf(fd, "\n\n");

    /* Iteramos hasta quedarnos sin ningun estado
        o hasta que al transitar se acepta la cadena */
    for (i=0; aceptado < 1 && !configuracionApndIsEmpty(p_ap->conf_actual); i++) {

        fprintf(fd, "\n\tITERACION %d\n",i);

        /* Transitamos */
        aceptado = APTransita(p_ap);

        /* Imprimimos la configuracion actual */
        fprintf(fd, "\nTRAS ITERAR LA CONFIGURACION ES\n");
        configuracionApndPrint(fd, p_ap->conf_actual);
        fprintf(fd, "\n");
    }
    /* Imprimimos si ha sido aceptada la cadena */
    fprintf(fd,"\n¡¡¡ %s !!!\n\n", (1 == aceptado) ? "RECONOCIDA" : "RECHAZADA");

    /* Limpiamos la configuracion actual */
    configuracionApndDestroy(p_ap->conf_actual);
    p_ap->conf_actual =  configuracionApndIni();

    return aceptado;
}

AP* APInicializaCadena(AP* p_ap)
{

    if (!p_ap) return NULL;

    /* Eliminamos la palabra existente */
    palabraElimina(p_ap->palabra);

    /* Inicializamos la nueva palabra */
    p_ap->palabra = palabraNueva();


    return p_ap;
}
