#include "object.h"

typedef struct {
  Type t;                 /*Type of object*/
  int take;                /*Can it be taken? 0 = NO, 1 = YES*/
  int use;                 /*Can we use it? 0 = NO, 1 = YES*/
  int resourse[2];         /*Resourse[0] = -1(decrease)/ 0(nothing)/ 1(increase)*/
                           /*Resourse[1] = Quantity*/
}Object;


Object *object_ini(){
  Object *o;

  o = (Object*)malloc(sizeof(Object));
  if(!o) return NULL;

  o->take = ERROR;
  o->t = ERROR;
  for(int i = 0; i < 2; i++){
    o->resourse[i] = ERROR;
  }
  return o;
}

void object_destroy(Object *o){
  if(!o) return;
  free(o);
  return;

}


Object *object_set(Object *o, Type t, int resource[2], int take, int use){
  if(!o || t == ERROR || (take != 1 && take != 0) || (use != 0 && use != 1)) return NULL;

  o->take = take;
  o->t = t;
  o->use = use;
  for(int i = 0; i < 2; i++){
    o->resource[i] = resource[i];
  }
  return o;
}
