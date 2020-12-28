#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

struct linkedList
{
    int value;
    struct linkedList *next;
};

linkedList *create(int value, linkedList *next)
{
    linkedList *list = malloc(sizeof(linkedList));

    list->value = value;
    list->next = next;

    return list;
}

linkedList *leaf(int value)
{
    return create(value, NULL);
}

linkedList *copy(linkedList *list)
{
    if (list->next)
        return create(list->value, copy(list->next));
    else
        return leaf(list->value);
}

linkedList *fromArray(int array[], int length)
{
    if (length == 0)
        return 0;

    linkedList *list = leaf(array[0]);

    for (int i = 1; i < length; i++)
        append(list, array[i]);

    return list;
}

linkedList *generateHelper(int (*generator)(int), int length, int index){
    return index < length - 1?
        create(generator(index), generateHelper(generator, length, index + 1)):
        leaf(generator(index));
}

linkedList *generate(int (*generator)(int), int length){
    return generateHelper(generator, length, 0);
}

int length(linkedList *list)
{
    int nextLength;
    if (list->next)
        nextLength = length(list->next);
    else
        nextLength = 0;

    return nextLength + 1;
}

void append(linkedList *list, int value)
{
    if (list->next)
        append(list->next, value);
    else
        list->next = leaf(value);
    return;
}

void printHelper(linkedList *list)
{
    printf("( %d ", list->value);
    if (list->next)
        printHelper(list->next);
    printf(")");
    return;
}

int get(linkedList *list, int i)
{
    if (i == 0)
        return list->value;
    else
    {
        if (list->next)
            return get(list->next, i - 1);
        else
            return 0;
    }
}

void print(linkedList *list)
{
    printHelper(list);
    printf("\n");
}

int foldr(linkedList *list, int (*bop)(int, int), int base)
{
    if (list->next)
        return bop(list->value, foldr(list->next, bop, base));
    else
        return bop(list->value, base);
}

int foldl(linkedList *list, int (*bop)(int, int), int acc)
{
    if (list->next)
    {
        return foldl(list->next, bop, bop(acc, list->value));
    }
    else
        return bop(acc, list->value);
}

void map(linkedList *list, int (*uop)(int))
{
    list->value = uop(list->value);
    if (list->next)
        map(list->next, uop);

    return;
}

bool equalsHelper(linkedList *first, linkedList *second)
{
    if (first->value != second->value)
        return false;

    if (first->next)
        return equalsHelper(first->next, second->next);

    return true;
}

bool equals(linkedList *first, linkedList *second)
{
    if (length(first) != length(second))
        return false;
    else
        return equalsHelper(first, second);
}

void clear(linkedList *list)
{
    if (list->next)
        clear(list->next);

    free(list);
}

void toArrayHelper(linkedList *list, int array[], int index)
{
    array[index] = list->value;

    if (list->next)
        toArrayHelper(list->next, array, index + 1);
}

int *toArray(linkedList *list)
{
    int *array = (int *)malloc(length(list) * sizeof(int));
    toArrayHelper(list, array, 0);
    return array;
}

bool contains(linkedList *list, int target)
{
    if (list->value == target)
        return true;

    if (list->next)
        return contains(list->next, target);

    return false;
}

void keep(linkedList *list, int length)
{
    if (length == 1)
    {
        list->next = NULL;
    }
    else if (list->next)
    {
        keep(list->next, length - 1);
    }

    return;
}