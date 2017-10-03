#include "object.h"

typedef struct {
  Type t;                 //Type of object
  int recurse[3];         //
  int take;               //Can it be taken? 0 = NO, 1 = YES
  int use;                //Can we use it? 0 = NO, 1 = YES
}Object;

Object *object_ini(){
  Object *o;

  o = (Object*)malloc(sizeof(Object));
  if(!o) return NULL;

  o->take = ERROR;
  o->t = ERROR;
  for(int i = 0; i < 3; i++){
    o->recurse[i] = ERROR;
  }
  return o;
}

void object_destroy(Object *o){
  if(!o) return;
  free(o);
  return;

}


Object *object_set(Object *o, Type t, int resource[3], int take, int use){
  if(!o || t == ERROR || (take != 1 && take != 0) || (use != 0 && use != 1)) return NULL;

  o->take = take;
  o->t = t;
  o->use = use;
  for(int i = 0; i < 3; i++){
    o->resource[i] = resource[i];
  }
  return o;
}
