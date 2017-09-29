#ifndef OBJECT_H
#define OBJECT_H

typedef struct_Object Object;
typedef enum {
  ERROR = -2, Beer = 69, Jagger = 70, Absent = 71, Water = 72, Sneakers = 73, VomitPill = 74
}Type;

Object *object_ini();

void object_destroy(Object *o);

Object *object_set(Object *o, Type t, int resource[3], int take, int use);

#endif
