#include "object.h"

 struct _object {
  char name[12];        /* Name of object*/
  int quantity;         /*-x(decrease)/ +x(increase)*/
};


Object **object_ini(void){
  Object **o;
  int i;

  o = (Object**)malloc(sizeof(Object*)*7);
  if(!o) return NULL;

  for(i = 0; i < 7, i++) o[i] = (Object*)malloc(sizeof(Object));

  strcpy(o[0]->name, "Beer");
  o[0]->quantity = 10;

  strcpy(o[1]->name, "Jagger");
  o[1]->quantity = 20;

  strcpy(o[2]->name, "Absent");
  o[2]->quantity = 30;

  strcpy(o[3]->name, "Water");
  o[3]->quantity = -10;

  strcpy(o[4]->name, "Sneakers");
  o[4]->quantity = -20;

  strcpy(o[5]->name, "VomitPill");
  o[5]->quantity = -30;

  strcpy(o[6]->name, "Clarinet");
  o[6]->quantity = -50;

  return o;
}

/*Destruction of the array of objects objects*/
void object_destroy(Object **o){
  int i;
  if(!o) return;
  for(i = 0; i < 7, i++) free(o[i]);
  free(o);
  return;

}


/*Returns the name of an object*/
char *object_name(Object *o){
  if(!o) return ERROR;
  return o->name;
}


/*Returns how much the object increases or decreases your life*/
int object_quantity(Object *o){
  if(!o) return ERROR;
  return o->quantity;
}
