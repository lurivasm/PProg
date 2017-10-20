#include "station.h"

 struct _metro {
  int stations[8];
  int actual_station;
};

Metro* create_metro(){
	Metro *m;
	int i;
	m=(Metro *)malloc(sizeof(Metro));
	if (m==NULL) return NULL;
	for(i=0;i<8;i++){
		stations[i]=TresO +i;
	}
	actual_station=2;
	return m;
};

void delete_metro(Metro* m){
	if (metro==NULL) return;
	free(m);
	return;
};

int actual_station(Metro* m){
	if (m==NULL) return ERR;
	return m->actual_station;
};

int change_station(Metro* m, int station){
	if (m==NULL) return ERR;
	if (station<0 || station>8) return ERR;
	m->actual_station=station;
	return OK;
}