%{
#include "main.h"
#include "syn.h"
%}
%option noyywrap
%%
[ \t]	{ ; }	/* skip blanks and tabs */
[0-9]+\.?|[0-9]*\.[0-9]+ {
	Symbol *s = cru_symbol_install("", UNDEF, (SymbolValue)0.0);
	sscanf(yytext, "%lf", &s->value.val);
	yylval.sym = s;
	return NUMBER; }
[a-zA-Z][a-zA-Z0-9]* {
	Symbol *s;
	if ((s=cru_symbol_lookup(yytext)) == 0)
		s = cru_symbol_install(yytext, UNDEF, (SymbolValue)0.0);
	yylval.sym = s;
	return s->type == UNDEF ? VAR : s->type; }
\n	{ lineno++; return '\n'; }   /* everything else */
.	{ return yytext[0]; }
