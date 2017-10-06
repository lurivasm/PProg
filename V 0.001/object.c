#include "object.h"

 struct _object {
  Type t;                 /*Type of object*/
  int take;                /*Can it be taken? 0 = NO, 1 = YES*/
  int use;                 /*Can we use it? 0 = NO, 1 = YES*/
  int resource[2];         /*Resourse[0] = -1(decrease)/ 0(nothing)/ 1(increase)*/
                           /*Resourse[1] = Quantity*/
};


Object *object_ini(void){
  Object *o;
  int i;

  o = (Object*)malloc(sizeof(Object));
  if(!o) return NULL;

  o->take = ERROR;
  o->t = ERROR;
  for(i = 0; i < 2; i++){
    o->resource[i] = ERROR;
  }
  return o;
}

void object_destroy(Object *o){
  if(!o) return;
  free(o);
  return;

}


Object *object_set(Object *o, Type t, int r0, int r1, int take, int use){
  if(!o || t == ERROR || (take != 1 && take != 0) || (use != 0 && use != 1)) return NULL;

  int i;

  o->take = take;
  o->t = t;
  o->use = use;
  o->resource[0]= r0;
  o->resource[1]= r1;
  return o;
}


Object *object_read(Object *o, char *name, int key){
  FILE *file = NULL;
  int key_aux, type_aux, r0_aux, r1_aux, take_aux, use_aux;

  file = fopen(name, "r");
  if(!file) return NULL;

  while(!feof(file)){
    fscanf(file, "%d %d %d %d %d %d", &key_aux, &type_aux, &r0_aux, &r1_aux, &take_aux, &use_aux);
    if(key_aux == key) break;
  }

  o = object_set(o, type_aux, r0_aux, r1_aux, take_aux, use_aux);
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


int object_indecrease(Object *o){
  if(!o) return ERROR;
  return o->resource[0];
}


int object_quantity(Object *o){
  if(!o) return ERROR;
  return o->resource[1];
}
