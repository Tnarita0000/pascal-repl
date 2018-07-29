#include <stdio.h>
#include <stdbool.h>
#include "spi.h"
const enum Symbol sym;

int pos    = 0;
int result = 0;

/* compare char byte code and integer */
bool is_integer(char c) {
  switch ((int)c) {
    case 48: /* '0' is 48 */
    case 49: /* '1' is 49 */
    case 50: /* '2' is 50 */
    case 51: /* '3' is 51 */
    case 52: /* '4' is 52 */
    case 53: /* '5' is 53 */
    case 54: /* '6' is 54 */
    case 55: /* '7' is 55 */
    case 56: /* '8' is 56 */
    case 57: /* '9' is 57 */
      return true;
    default:
      return false;
  }
}

int scan(char c) {
  if ( is_integer(c) ) {
    puts("INTEGER");
    return INTEGER;
  }

  switch (c) {
    case ' ':
      puts("SPACE");
      return 0;
    case '+':
      puts("PLUS");
      return OP_PLU;
    case '-':
      puts("MINUS");
      return OP_MIN;
    case '*':
      puts("MULTI");
      return OP_MUL;
    case '/':
      puts("DIVISION");
      return OP_DIV;
  }

  return 0;
}

int parse(char text[]) {
  puts(text);
  while (true) {
    if (text[pos] == 0) { break; };

    scan(text[pos]);

    pos++;
  }
  return result;
}
