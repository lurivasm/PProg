#ifndef OBJECT_H
#define OBJECT_H

/*We define this macro for all the possible errors in ints*/
#define ERROR -2

typedef struct_Object Object;
typedef enum {
  Error = ERROR, Beer = 69, Jagger = 70, Absent = 71, Water = 72, Sneakers = 73, VomitPill = 74
}Type;

/*Initialization of objects*/
Object *object_ini();

/*Destruction of objects*/
void object_destroy(Object *o);

/*Setting objects*/
Object *object_set(Object *o, Type t, int resource[3], int take, int use);

#endif
