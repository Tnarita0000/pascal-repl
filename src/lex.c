#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "spi.h"

#define SIZE 1024

int ch; // '+', '-', '*', '/'
int token;
double value;
jmp_buf err;

char *token_name[] = {
  "EOF",
  "Number",
  "+",
  "-",
  "*",
  "/",
  "(",
  ")",
  ";",
  "Others",
};

double expression(void);
double term(void);
double factor(void);

void error(char *mes) {
  fprintf(stderr, "%s, %s\n", mes, token_name[token]);
  longjmp(err, 1);
}

void nextch(void) {
  ch = getchar();
}

int getch(void) {
  return ch;
}

int get_fixnum(char *buff, int i) {
  while ( isdigit(getch()) ) {
    buff[i++] = getch();
    nextch();
  }
  return i;
}

double get_number(void) {
  char buff[SIZE + 1];
  char *err;
  int i = get_fixnum(buff, 0);

  /* if float number */
  if (getch() == '.') {
    buff[i++] = getch();
    nextch();
    i = get_fixnum(buff, i);
  }

  /* if exponent */
  if (getch() == 'e' || getch() == 'E') {
    buff[i++] = getch();
    nextch();
    if (getch() == '+' || getch() == '-') {
      buff[i++] = getch();
      nextch();
    }
    i = get_fixnum(buff, i);
  }

  buff[i] = '\0';
  double value = strtod(buff , &err);
  if (*err != '\0') error("get_number: not Number\n");
  
  return value;
}

void get_token(void) {
  while ( isspace(getch()) ) nextch();
  if ( isdigit(getch()) ) {
    token = Number;
    value = get_number();
  } else {
    switch( getch() ) {
      case '+':
        token = Add;
        nextch();
        break;
      case '-':
        token = Sub;
        nextch();
        break;
      case '*':
        token = Mul;
        nextch();
        break;
      case '/':
        token = Div;
        nextch();
        break;
      case '(':
        token = Lpar;
        nextch();
        break;
      case ')':
        token = Rpar;
        nextch();
        break;
      case ';':
        token = Semic;
        nextch();
        break;
      case EOF:
        token = Eof;
        break;
      default:
        token = Others;
    }
  }
}

double expression(void) {
  double val = term();
  while (true) {
    switch (token) {
      case Add:
        get_token();
        val += term();
        break;
      case Sub:
        get_token();
        val -= term();
        break;
      default:
        return val;
    }
  }
}

double term(void) {
  double val = factor();
  while (true) {
    switch (token) {
      case Mul:
        get_token();
        val *= factor();
        break;
      case Div:
        get_token();
        val /= factor();
        break;
      default:
        return val;
    }
  }
}

double factor(void) {
  switch (token) {
    case Lpar:
      get_token();
      double val = expression();
      if (token == Rpar)
        get_token();
      else
        error("')' expected");
      return val;
    case Number:
      get_token();
      return value;
    default:
      error("Unexpected token.");
      return RAND_MAX;
  }
}
