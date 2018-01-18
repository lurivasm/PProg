#ifndef STATION_H
#define STATION_H
#include <stdio.h>
#define ERR -1
#define OK (!(ERR))
typedef struct _metro Metro;

typedef enum {
TresO = 69, Plazaca = 70, Nuevos = 71, Gregorio = 72, PlazaEsp = 73, Lago = 74, Colonia = 75, Puerta = 76 
}Station;
Metro* create_metro();
/*Create the metro stations*/
void delete_metro(Metro* m);
/*Delete the metro stations*/
int actual_station(Metro* m);
/*Returns actual station*/
int change_station(Metro* m, int station);
/*Changes the actual station*/
#endif