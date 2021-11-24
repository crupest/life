#pragma once

typedef union SymbolValue {
  double val;
  double (*ptr)();
} SymbolValue;

typedef struct Symbol {
  char *name;
  int type;
  SymbolValue value;
  struct Symbol *next;
} Symbol;

Symbol *cru_symbol_lookup(const char *name);
Symbol *cru_symbol_install(const char *name, int type, SymbolValue value);

double Pow(double x, double y);

int yylex();
int yyparse();
void yyerror(const char *s);

extern int lineno;
void execerror(const char *s, const char *t);
