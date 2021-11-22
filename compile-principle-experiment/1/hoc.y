%{
#define  YYSTYPE  double   /* data type of yacc stack */
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int yylex();
int yyerror(const char * s);
%}
%token  NUMBER
%left  '+' '-'    /* left associative, same precedence */
%left  '*' '/' '%'   /* left assoc., higher precedence */
%left	UNARYMINUS
%%
list:    /* nothing */
  | list '\n'
  | list expr '\n'    { printf("%lf\n", $2); }
  ;
expr:    NUMBER  { $$ = $1; }
  | expr '+' expr  { $$ = $1 + $3; }
  | expr '-' expr  { $$ = $1 - $3; }
  | expr '*' expr  { $$ = $1 * $3; }
  | expr '/' expr  { $$ = $1 / $3; }
  | expr '%' expr  { $$ = fmod($1, $3); }
	| '-' expr  %prec UNARYMINUS { $$ = -$2; }
  | '(' expr ')'  { $$ = $2; }
  ;
%%
  
int lineno = 1;

int main(int argc, char** argv)
{
  yyparse();
  return 0;
}

int yylex()
{
  int c;

  do {
    c = getchar();
  } while (c == ' ' || c == '\t');

  if (c == EOF)
    return 0;

  if (c == '.' || isdigit(c)) {
    ungetc(c, stdin);
    scanf("%lf", &yylval);
    return NUMBER;
  }

  if (c == '\n')
    lineno++;

  return c;
}

int yyerror(const char* s)
{
  fprintf(stderr, "Error occured near line %d\n", lineno);
  return 0;
}
