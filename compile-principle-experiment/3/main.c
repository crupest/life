#include "main.h"

#include "syn.h"

#include <errno.h>
#include <math.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Symbol *symlist = 0; /* symbol table: linked list */

void *emalloc(size_t n) /* check return from malloc */
{
  void *p = malloc(n);
  if (p == 0)
    execerror("out of memory", (char *)0);
  return p;
}

Symbol *cru_symbol_lookup(const char *name) {
  for (Symbol *sp = symlist; sp != NULL; sp = sp->next)
    if (strcmp(sp->name, name) == 0)
      return sp;
  return NULL;
}

Symbol *cru_symbol_install(const char *name, int type, SymbolValue value) {
  Symbol *sp = (Symbol *)emalloc(sizeof(Symbol));
  sp->name = emalloc(strlen(name) + 1);
  strcpy(sp->name, name);
  sp->type = type;
  sp->value = value;
  sp->next = symlist;
  symlist = sp;
  return sp;
}

jmp_buf begin;
int lineno;

void warning(const char *s, const char *t) {
  fprintf(stderr, "%s", s);
  if (t)
    fprintf(stderr, " %s", t);
  fprintf(stderr, " near line %d\n", lineno);
}

void yyerror(const char *s) { warning(s, NULL); }

void execerror(const char *s, const char *t) {
  warning(s, t);
  longjmp(begin, 0);
}

double errcheck(double result, const char *name) {
  if (errno == EDOM) {
    errno = 0;
    execerror(name, "argument out of domain");
  } else if (errno == ERANGE) {
    errno = 0;
    execerror(name, "result out of range");
  }
  return result;
}

double Log(double x) { return errcheck(log(x), "log"); }
double Log10(double x) { return errcheck(log10(x), "log10"); }
double Sqrt(double x) { return errcheck(sqrt(x), "sqrt"); }
double Exp(double x) { return errcheck(exp(x), "exp"); }
double Pow(double x, double y) { return errcheck(pow(x, y), "exponentiation"); }
double integer(double x) { return (double)(long)x; }

static struct { /* Constants */
  char *name;
  double cval;
} consts[] = {
    {"PI", 3.14159265358979323846},    {"E", 2.71828182845904523536},
    {"GAMMA", 0.57721566490153286060}, {"DEG", 57.29577951308232087680},
    {"PHI", 1.61803398874989484820},
};

static struct { /* Built-ins */
  char *name;
  double (*func)();
} builtins[] = {
    {"sin", sin},   {"cos", cos},     {"atan", atan},
    {"log", Log},   {"log10", Log10}, {"exp", Exp},
    {"sqrt", Sqrt}, {"int", integer}, {"abs", fabs},
};

void init() {
  for (int i = 0; i < sizeof(consts) / sizeof(*consts); i++)
    cru_symbol_install(consts[i].name, VAR, (SymbolValue)consts[i].cval);
  for (int i = 0; i < sizeof(builtins) / sizeof(*builtins); i++) {
    cru_symbol_install(builtins[i].name, BLTIN, (SymbolValue)builtins->func);
  }
}

int main(int argc, char **argv) {
  init();
  (void)setjmp(begin);
  yyparse();

  return 0;
}
