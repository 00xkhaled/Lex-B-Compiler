#ifndef TREE_HEADER
#define TREE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum { typeCon, typeId, typeOpr, typeFunc} nodeEnum;

typedef struct {
  int value;
} conNodeType;

typedef struct {
  int i;
} idNodeType;

typedef struct {
  char *name;
} funcNodeType;

typedef struct {
  int oper;
  int nops;
  struct nodeTypeTag *op[1];
} oprNodeType;

typedef struct nodeTypeTag{
  nodeEnum type;

  union {
    conNodeType con;
    idNodeType id;
    funcNodeType func;
    oprNodeType opr;
  };
} nodeType;

extern int sym[26];

#endif
