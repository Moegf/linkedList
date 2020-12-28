#include <stdbool.h>

#ifndef LINKEDLIST
#define LINKEDLIST

typedef struct linkedList linkedList;

linkedList *create(int value, linkedList *next);
linkedList *leaf(int value);
linkedList *copy(linkedList *list);
linkedList *fromArray(int array[], int size);
linkedList *generate(int (*generator)(int), int length);
int length(linkedList *list);
void append(linkedList *list, int value);
int get(linkedList *list, int i);
void print(linkedList *list);
int foldr(linkedList *list, int (*bop)(int, int), int base);
int foldl(linkedList *list, int(*bop)(int, int), int base);
void map(linkedList *list, int (*uop)(int));
bool equals(linkedList *first, linkedList *second);
void clear(linkedList *list);
int *toArray(linkedList *list);
bool contains(linkedList *list, int target);
void keep(linkedList *list, int length);

#endif