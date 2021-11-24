%{
#include "main.h"
#include <stdio.h>
%}
%union {
	double	val;	/* actual value */
	Symbol	*sym;	/* symbol table pointer */
}
%token	<val>	NUMBER
%token	<sym>	VAR BLTIN UNDEF
%type	<val>	expr asgn
%right	'='
%left	'+' '-'
%left	'*' '/'
%left	UNARYMINUS
%right	'^'	/* exponentiation */
%%
list:	  /* nothing */
	| list '\n'
	| list asgn '\n'
	| list expr '\n'	{ printf("\t%.8g\n", $2); }
	| list error '\n'	{ yyerrok; }
	;
asgn:	  VAR '=' expr { $$=$1->value.val=$3; $1->type = VAR; }
	;
expr:	  NUMBER
	| VAR {	if ($1->type == UNDEF)
		    execerror("undefined variable", $1->name);
		$$ = $1->value.val; }
	| BLTIN '(' expr ')'	{ $$ = (*($1->value.ptr))($3); }
	| expr '+' expr	{ $$ = $1 + $3; }
	| expr '-' expr	{ $$ = $1 - $3; }
	| expr '*' expr	{ $$ = $1 * $3; }
	| expr '/' expr	{
		if ($3 == 0.0)
			execerror("division by zero", "");
		$$ = $1 / $3; }
	| expr '^' expr	{ $$ = Pow($1, $3); }
	| '(' expr ')'	{ $$ = $2; }
	| '-' expr  %prec UNARYMINUS  { $$ = -$2; }
	;
%%
