#include "funcTable.h"

void add_func(char *s, nodeType* funcTree) {

  funcType *tmp;

  if((tmp = (funcType*) malloc(sizeof(funcType))) == NULL)
  {
      printf("NO MORE MEMORY to save function!\n");
      exit(1);
  }
  // Add to the start of the linked list.
  // more like a stack
  tmp->funcName = strdup(s);
  tmp->funcTree = funcTree;
  tmp->next = funcTable;
  funcTable = tmp;
}

funcType* search_func (char* funcName)
{
  funcType *tmp = funcTable;

  while(tmp != NULL)
  {
    if (strcmp(tmp->funcName,funcName) == 0 )
    {
      break;
    }
    tmp = tmp->next;
  }
  return tmp;
}
