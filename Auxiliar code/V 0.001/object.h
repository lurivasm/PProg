#ifndef OBJECT_H
#define OBJECT_H
#include <stdio.h>
#include <stdlib.h>

/*We define this macro for all the possible errors in ints*/
#define ERROR -1

typedef struct _object Object;

/*Inicialization of the array ob objects. In the main function object[7]*/
Object **object_ini(void)

/*Destruction of objects*/
void object_destroy(Object **o);

/*Returns the name of an object*/
char *object_name(Object *o);

/*Returns how much the object increases or decreases your life*/
int object_quantity(Object *o);


#endif
