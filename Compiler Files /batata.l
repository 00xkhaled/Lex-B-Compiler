%{
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>


  #include "tree.h"
  #include "batata.tab.h"

  extern void yyerror(char *);
  extern YYSTYPE yylval;


  char buf[256];
  char *s;


  int yylineno;
  int yycolno = 1;
%}

%%

"if"  return IF;
"else"  return ELSE;
"while" return WHILE;
"print" return PRINT;
"for" return FOR;
"def" return DEF;
"mod" return MOD;


"<" return LT;
">" return GT;
"<="  return LTE;
">="  return GTE;
"=="  return EQ;
"!="  return NEQ;



[a-z] {
      yylval.sval = *yytext - 'a';
      return ID;
      }

[a-zA-Z_]+ {
            sprintf(buf, "%s", yytext); yylval.string = buf; return S;
            }

[0-9]+  {
        yylval.ival = atoi(yytext);
        return INT;
        }

[-+*/()\[\]{}=;] return *yytext;

\n    yylineno++; yycolno = 1; // NEW LINE NL

[ \t\n]+  yycolno++; // to ignore the whitespace IWS

. { yyerror("Unrecognised Symbol!"); }

%%
