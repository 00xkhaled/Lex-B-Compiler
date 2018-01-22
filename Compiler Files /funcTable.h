#ifndef FUNC_TABLE_HEADER
#define FUNC_TABLE_HEADER

#include <stdio.h>
#include <string.h>

#include "tree.h"

typedef struct funcNode
{
  struct funcNode* next;
  char *funcName;
  nodeType* funcTree;
}
funcType;

funcType *funcTable; // Pointer to function table.
int func_array[26]; // Local variables inside funcions.

/* Prototypes */
void add_func ();
funcType* search_func (char *);
int ex_func();

#endif
