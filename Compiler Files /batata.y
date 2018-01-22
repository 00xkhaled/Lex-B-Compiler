%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdarg.h>

  #include "tree.h"
  #include "batata.tab.h"
  #include "funcTable.h"

  extern int yyparse();
  extern int yylex();
  extern int ex(nodeType *);
  extern FILE *yyin;
  extern int yylineno;
  extern int yycolno;

  void yyerror(char *s) { printf("%s\n",s); }


  // Function prototypes
  nodeType *opr (int oper, int nops, ...);
  nodeType *id (int i);
  nodeType *con (int value);
  nodeType *func(char *s);
  void freeNode (nodeType *p);


  int sym[26];
%}

%union {
  int ival; //Integer values.
  char sval; // Char values.
  char *string; //string values;

  nodeType *nPtr;


}

%token <ival> INT
%token <sval> ID
%token <string> S
%token PRINT WHILE IF FOR DEF
%token LT GT LTE GTE EQ NEQ MOD

%nonassoc IFX
%nonassoc ELSE

%left LT GT LTE GTE EQ NEQ
%left '+' '-'
%left '*' '/'

%right '^'

%nonassoc UMINUS


%type <nPtr> stmt expr stmt_list
%%

program:
  function { exit (0); }
  ;

function:
  function stmt {ex($2); freeNode($2);}
  | function DEF S '(' ')' '{' stmt '}' { add_func($3,$7); }
  | /* NULL */
  ;

stmt:
  ';' { $$ = opr(';', 2 , NULL, NULL); }
  | expr ';' { $$ = $1; }
  | PRINT expr ';' { $$ = opr(PRINT, 1, $2); }
  | ID '=' expr ';' { $$ = opr('=', 2, id($1), $3); }
  | WHILE '(' expr ')' stmt { $$ = opr(WHILE, 2, $3, $5); }
  | FOR '(' ID '=' expr ';' expr ';' ID '=' expr ')' stmt { $$ = opr(FOR, 4, opr('=', 2, id($3), $5), $7, opr('=', 2, id($9), $11), $13);}
  | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
  | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
  | S '(' ')' ';' { $$ = func($1); }
  | '{' stmt_list '}' {$$ = $2; }
  ;

stmt_list:
  stmt { $$ = $1; }
  | stmt_list stmt {$$ = opr(';', 2, $1, $2); }
  ;

expr:
  INT { $$ = con($1); }
  | ID { $$ = id($1); }
  | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
  | expr '+' expr { $$ = opr('+', 2, $1, $3); }
  | expr '-' expr { $$ = opr('-', 2, $1, $3); }
  | expr '*' expr { $$ = opr('*', 2, $1, $3); }
  | expr '/' expr { $$ = opr('/', 2, $1, $3); }
  | expr LT expr { $$ = opr(LT, 2, $1, $3); }
  | expr GT expr { $$ = opr(GT, 2, $1, $3); }
  | expr LTE expr { $$ = opr(LTE, 2, $1, $3); }
  | expr GTE expr { $$ = opr(GTE, 2, $1, $3); }
  | expr EQ expr { $$ = opr(EQ, 2, $1, $3); }
  | expr NEQ expr { $$ = opr(NEQ, 2, $1, $3); }
  | '(' expr ')' { $$ = $2; }
  ;

%%

#define SIZEOF_NODETYPE ((char *)&p->con - (char*)p)

nodeType *con (int value) {
  nodeType *p;
  size_t nodeSize;

  nodeSize = SIZEOF_NODETYPE + sizeof(conNodeType);
  if((p = malloc(nodeSize)) == NULL) {
    yyerror ("out of memory!");
  }

  p->type = typeCon;
  p->con.value = value;
  return p;
}

nodeType *id (int i) {
  nodeType *p;
  size_t nodeSize;

  nodeSize = SIZEOF_NODETYPE + sizeof(idNodeType);
  if((p = malloc(nodeSize)) == NULL) {
    yyerror ("out of memory!");
  }

  p->type = typeId;
  p->id.i = i;
  return p;
}

nodeType *opr (int oper, int nops, ...) {
  va_list ap;
  nodeType *p;
  size_t nodeSize;
  int i;

  nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) + (nops -1) + sizeof(nodeType*);
  if((p = malloc(nodeSize)) == NULL) {
    yyerror ("out of memory!");
  }

  p->type = typeOpr;
  p->opr.oper = oper;
  p->opr.nops = nops;
  va_start(ap, nops);
  for (i = 0; i < nops; i++){
    p->opr.op[i] = va_arg(ap, nodeType*);
  }
  va_end(ap);

  return p;
}

void freeNode (nodeType *p){
  int i;
  if (!p)
    return;

  if(p->type == typeOpr){
    for(i = 0; i < p->opr.nops; i++){
      freeNode(p->opr.op[i]);
    }
  }

  free (p);
}

nodeType *func(char *s){
  nodeType *p;
  size_t nodeSize;

  nodeSize = SIZEOF_NODETYPE + sizeof(funcNodeType);
  if((p = malloc(nodeSize)) == NULL) {
    yyerror ("out of memory!");
  }

  p->type = typeFunc;
  p->func.name = s;
  printf("FUNC DONE!\n");
  return p;
}

int main(int argc, char **argv){
    yyparse();
  return 0;
}
