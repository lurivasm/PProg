#include "object.h"

typedef struct {
  Type t;
  int recurse[3];
  int take;
  int use;
}Object;

Object *object_ini(){
  Object *o;

  o = (Object*)malloc(sizeof(Object));
  if(!o) return NULL;

  o->take = -2;
  o->t = ERROR;
  for(int i = 0; i < 3; i++){
    o->recurse[i] = -2;
  }
  return o;
}

void object_destroy(Object *o){
  if(!o) return;
  free(o);
  return;

}


Object *object_set(Object *o, Type t, int resource[3], int take, int use);
