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

int initcode();
int execute(Inst *p);

void init() {
  initcode();
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
  execute(prog);

  return 0;
}

#define NSTACK 256
static Datum stack[NSTACK]; /* the stack */
static Datum *stackp;       /* next free spot on stack */

#define NPROG 2000
Inst prog[NPROG]; /* the machine */
Inst *progp;      /* next free spot for code generation */
Inst *pc;         /* program counter during execution */

int initcode() /* initialize for code generation */
{
  stackp = stack;
  progp = prog;
  return 0;
}

int push(Datum d) /* push d onto stack */
{
  if (stackp >= &stack[NSTACK])
    execerror("stack overflow", (char *)0);
  *stackp++ = d;
  return 0;
}

Datum pop() /* pop and return top elem from stack */
{
  if (stackp <= stack)
    execerror("stack underflow", (char *)0);
  return *--stackp;
}

int constpush() /* push constant onto stack */
{
  Datum d;
  d.val = ((Symbol *)*pc++)->value.val;
  push(d);
  return 0;
}

int varpush() /* push variable onto stack */
{
  Datum d;
  d.sym = (Symbol *)(*pc++);
  push(d);
  return 0;
}

int bltin() /* evaluate built-in on top of stack */
{
  Datum d;
  d = pop();
  d.val = (*(double (*)())(*pc++))(d.val);
  push(d);
  return 0;
}

int eval() /* evaluate variable on stack */
{
  Datum d;
  d = pop();
  if (d.sym->type == UNDEF)
    execerror("undefined variable", d.sym->name);
  d.val = d.sym->value.val;
  push(d);
  return 0;
}

int add() /* add top two elems on stack */
{
  Datum d1, d2;
  d2 = pop();
  d1 = pop();
  d1.val += d2.val;
  push(d1);
  return 0;
}

int sub() /* subtract top of stack from next */
{
  Datum d1, d2;
  d2 = pop();
  d1 = pop();
  d1.val -= d2.val;
  push(d1);
  return 0;
}

int mul() {
  Datum d1, d2;
  d2 = pop();
  d1 = pop();
  d1.val *= d2.val;
  push(d1);
  return 0;
}

int mydiv() {
  Datum d1, d2;
  d2 = pop();
  if (d2.val == 0.0)
    execerror("division by zero", (char *)0);
  d1 = pop();
  d1.val /= d2.val;
  push(d1);
  return 0;
}

int negate() {
  Datum d;
  d = pop();
  d.val = -d.val;
  push(d);
  return 0;
}

int power() {
  Datum d1, d2;
  extern double Pow();
  d2 = pop();
  d1 = pop();
  d1.val = Pow(d1.val, d2.val);
  push(d1);
  return 0;
}

int assign() /* assign top value to next value */
{
  Datum d1, d2;
  d1 = pop();
  d2 = pop();
  if (d1.sym->type != VAR && d1.sym->type != UNDEF)
    execerror("assignment to non-variable", d1.sym->name);
  d1.sym->value.val = d2.val;
  d1.sym->type = VAR;
  push(d2);
  return 0;
}

int print() /* pop top value from stack, print it */
{
  Datum d;
  d = pop();
  printf("\t%.8g\n", d.val);
  return 0;
}

Inst *code(Inst f) /* install one instruction or operand */
{
  Inst *oprogp = progp;
  if (progp >= &prog[NPROG])
    execerror("program too big", (char *)0);
  *progp++ = f;
  return oprogp;
}

int execute(Inst *p) /* run the machine */
{
  for (pc = p; *pc != STOP;)
    (*(*pc++))();
  return 0;
}

int mypop() {
  pop();
  return 0;
}
