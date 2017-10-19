#include "object.h"

 struct _object {
  Type t;                 /*Type of object*/
  int take;                /*Can it be taken? 0 = NO, 1 = YES*/
  int use;                 /*Can we use it? 0 = NO, 1 = YES*/
  int quantity;         /*-x(decrease)/ 0(nothing)/ 1(increase)*/
};


Object *object_ini(void){
  Object *o;
  int i;

  o = (Object*)malloc(sizeof(Object));
  if(!o) return NULL;

  o->take = ERROR;
  o->t = ERROR;
  o->quantity = ERROR;
  return o;
}

void object_destroy(Object *o){
  if(!o) return;
  free(o);
  return;

}


Object *object_set(Object *o, Type t, int q, int take, int use){
  if(!o || t == ERROR || (take != 1 && take != 0) || (use != 0 && use != 1) || q == ERROR) return NULL;

  int i;

  o->take = take;
  o->t = t;
  o->use = use;
  o->quantity = q;
  return o;
}


Object *object_read(Object *o, char *name, int key){
  FILE *file = NULL;
  int key_aux, type_aux, q_aux, take_aux, use_aux;

  file = fopen(name, "r");
  if(!file) return NULL;

  while(!feof(file)){
    fscanf(file, "%d %d %d %d %d", &key_aux, &type_aux, &q_aux, &take_aux, &use_aux);
    if(key_aux == key) break;
  }

  o = object_set(o, type_aux, q_aux, take_aux, use_aux);
  if(!o) return NULL;

  return o;
}


Type object_type(Object *o){
  if(!o) return ERROR;
  return o->t;
}


int object_use(Object *o){
  if(!o) return ERROR;
  return o->use;
}


int object_take(Object *o){
  if(!o) return ERROR;
  return o->take;
}


int object_quantity(Object *o){
  if(!o) return ERROR;
  return o->quantity;
}

