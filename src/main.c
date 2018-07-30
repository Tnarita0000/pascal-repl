#include <stdio.h>
#include <string.h>
#include "spi.h"
#include "lex.c"

void toplevel(void) {
  double val = expression();
  if (token == Semic) {
    printf("=> %.14g\n>>> ", val);
    fflush(stdout);
  } else {
    error("Invalid token.");
  }
}

int main(void) {
  printf(">>> ");
  fflush(stdout);
  nextch();
  while (true) {
    if (!setjmp(err)) {
      get_token();
      if (token == Eof) break;
      toplevel();
    } else {
      // clear input
      while (getch() != '\n') nextch();
      printf(">>> ");
      fflush(stdout);
    }
  }
  printf("bye\n");
  return 0;
}
