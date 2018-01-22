#include <stdio.h>
#include "tree.h"
#include <math.h>
#include "batata.tab.h"
#include "funcTable.h"

int ex_func();

int ex(nodeType *p){
  if (!p) return 0;

  switch(p->type){

    case typeCon:
      return p->con.value;

    case typeId:
      return sym[p->id.i];

    case typeFunc:
      return ex_func(p->func.name);

    case typeOpr:
    switch(p->opr.oper){
      case WHILE:
        while (ex(p->opr.op[0])){
          ex(p->opr.op[1]);
        }
        return 0;
        case FOR: {
          int i;
            for (i = ex(p->opr.op[0]); ex(p->opr.op[1]); ex(p->opr.op[2]) ){
              ex(p->opr.op[3]);
            }
            return 0;
          }
      case IF:
        if (ex(p->opr.op[0]))
          ex(p->opr.op[1]);
        else if (p->opr.nops > 2)
          ex(p->opr.op[2]);
        return 0;


      case PRINT:
        printf("%d\n", ex(p->opr.op[0]));
        return 0;

      case ';':
        ex(p->opr.op[0]);
        return ex(p->opr.op[1]);


      case '=':
        return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);

      case UMINUS:
        return -ex(p->opr.op[0]);
      case '+':
        return ex(p->opr.op[0]) + ex(p->opr.op[1]);

      case '-':
        return ex(p->opr.op[0]) - ex(p->opr.op[1]);

      case '*':
        return ex(p->opr.op[0]) * ex(p->opr.op[1]);

      case '/':
        return ex(p->opr.op[0]) / ex(p->opr.op[1]);

      case LT:
        return ex(p->opr.op[0]) < ex(p->opr.op[1]);

      case GT:
        return ex(p->opr.op[0]) > ex(p->opr.op[1]);

      case LTE:
        return ex(p->opr.op[0]) <= ex(p->opr.op[1]);

      case GTE:
        return ex(p->opr.op[0]) >= ex(p->opr.op[1]);

      case EQ:
        return ex(p->opr.op[0]) == ex(p->opr.op[1]);

      case NEQ:
        return ex(p->opr.op[0]) != ex(p->opr.op[1]);
    }
  }
  return 0;
}


int ex_func(char *s)
{
  funcType *func = search_func(s);

  if (func == NULL)
  {
    printf("Function doesn't exist | Please define the function \n");
    return 0;
  }
  
  nodeType *p = func->funcTree;

  if(p == NULL)
  {
    printf("Error\n");
    return 0;
  }

  return ex(p);
}
