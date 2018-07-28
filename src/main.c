#include <stdio.h>
#include <string.h>

int main(int argc, char *args[]) {
  while (1) {
    printf(">>> ");

    char buff[1024];
    gets(buff);

    if (strlen(buff) >= 1024) {
      fprintf(stderr, "ERR: too many characters\n");
      exit(0);
    }
    printf("[%s]\n", buff);
  }
}
