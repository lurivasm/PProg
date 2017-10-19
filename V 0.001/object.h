#ifndef OBJECT_H
#define OBJECT_H
#include <stdio.h>
#include <stdlib.h>

/*We define this macro for all the possible errors in ints*/
#define ERROR -2

typedef struct _object Object;
typedef enum {
  Error = ERROR, Beer = 69, Jagger = 70, Absent = 71, Water = 72, Sneakers = 73, VomitPill = 74
}Type;

/*Initialization of objects*/
Object *object_ini(void);

/*Destruction of objects*/
void object_destroy(Object *o);

/*Setting objects*/
Object *object_set(Object *o, Type t, int r1, int take, int use);

/*Read OBJECTS.TXT and create different objects depending on the line*/
Object *object_read(Object *o, char *name, int key);

/*Returns the type of object*/
Type object_type(Object *o);

/*Returns 1 if you can use it and 0 if not*/
int object_use(Object *o);

/*Returns 1 if you can take it and 0 if not*/
int object_take(Object *o);

/*Returns how much the object increases or decreases your life*/
int object_quantity(Object *o);


#endif
