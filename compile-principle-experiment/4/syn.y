%{
#include "main.h"
#include <stdio.h>
#define	code2(c1,c2)	code(c1); code(c2)
#define	code3(c1,c2,c3)	code(c1); code(c2); code(c3)
%}
%union {
	Symbol	*sym;	/* symbol table pointer */
	double val;
	Inst	*inst;	/* machine instruction */
}
%token	<sym>	NUMBER VAR BLTIN UNDEF
%right	'='
%left	'+' '-'
%left	'*' '/'
%left	UNARYMINUS
%right	'^'	/* exponentiation */
%%
list:	  /* nothing */
	| list '\n'
	| list asgn '\n'  { code2(mypop, STOP); return 1; }
	| list expr '\n'  { code2(print, STOP); return 1; }
	| list error '\n' { yyerrok; }
	;
asgn:	  VAR '=' expr	{ code3(varpush,(Inst)$1,assign); }
	;
expr:	  NUMBER	{ code2(constpush, (Inst)$1); }
	| VAR		{ code3(varpush, (Inst)$1, eval); }
	| asgn
	| BLTIN '(' expr ')' { code2(bltin, (Inst)$1->value.ptr); }
	| '(' expr ')'
	| expr '+' expr	{ code(add); }
	| expr '-' expr	{ code(sub); }
	| expr '*' expr	{ code(mul); }
	| expr '/' expr	{ code(mydiv); }
	| expr '^' expr	{ code(power); }
	| '-' expr  %prec UNARYMINUS  { code(negate); }
	;
%%
