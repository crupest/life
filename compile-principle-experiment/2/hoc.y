%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int yylex();
int yyerror(const char * s);
void execerror(const char* s, const char* t);
void warning(const char* s, const char* t);

double	mem[26];	/* memory for variables 'a'..'z' */
%}

%union {		/* stack type */
	double	val;	/* actual value */
	int	index;	/* index into mem[] */
}
%token	<val>	NUMBER
%token	<index>	VAR
%type	<val>	expr
%right	'='
%left	'+' '-'
%left	'*' '/'
%left	UNARYMINUS
%%
list:	  /* nothing */
	| list '\n'
	| list expr '\n'	{ printf("\t%.8g\n", $2); }
	| list error '\n'	{ yyerrok; }
	;
expr:	  NUMBER
	| VAR		{ $$ = mem[$1]; }
	| VAR '=' expr	{ $$ = mem[$1] = $3; }	
	| expr '+' expr	{ $$ = $1 + $3; }
	| expr '-' expr	{ $$ = $1 - $3; }
	| expr '*' expr	{ $$ = $1 * $3; }
	| expr '/' expr	{
		if ($3 == 0.0)
			execerror("division by zero", "");
		$$ = $1 / $3; }
	| '(' expr ')'	{ $$ = $2; }
	| '-' expr  %prec UNARYMINUS  { $$ = -$2; }
	;
%%
	/* end of grammar */

int	lineno = 1;
#include <signal.h>
#include <setjmp.h>
jmp_buf	begin;

void fpecatch(int s);

int main(int argc, char** argv)
{
	(void)setjmp(begin);
	signal(SIGFPE, fpecatch);
	yyparse();
}

int yylex()
{
	int c;

	while ((c=getchar()) == ' ' || c == '\t')
		;
	if (c == EOF)
		return 0;
	if (c == '.' || isdigit(c)) {	/* number */
		ungetc(c, stdin);
		scanf("%lf", &yylval.val);
		return NUMBER;
	}
	if (islower(c)) {
		yylval.index = c - 'a';	/* ASCII only */
		return VAR;
	}
	if (c == '\n')
		lineno++;
	return c;
}

int yyerror(const char *s)
{
	warning(s, (char *)0);
	return 0;
}

void execerror(const char* s, const char* t)
{
	warning(s, t);
	longjmp(begin, 0);
}

void fpecatch(int s)
{
	execerror("floating point exception", (char *) 0);
}

void warning(const char* s, const char* t)
{
	fprintf(stderr, "%s", s);
	if (t && *t)
		fprintf(stderr, " %s", t);
	fprintf(stderr, " near line %d\n", lineno);
}
