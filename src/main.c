#include <stdio.h>
#include <string.h>
#include "lexer.c"

char *getsn(char *s, int n) {
  if (fgets(s, n, stdin) == NULL) return NULL;
  char *ln = strchr(s, '\n');
  if (ln) *ln = '\0';
  else while (1) {
    int c = getchar();
    if (c == '\n' || c == EOF) break;
  }
  return s;
}

int main(int argc, char **args) {
  while (1) {
    printf(">>> ");

    char buff[1024] = {};
    getsn(buff, 1024);

    if (strlen(buff) >= 1024) {
      fprintf(stderr, "ERR: too many characters\n");
      return 0;
    }
    parse(buff);
    printf("[%s]\n", buff);
  }
}
