#ifndef SPI_H
#define SPI_H
enum Symbol {
  OP_PLU, /* + */
  OP_MIN, /* - */
  OP_MUL, /* * */
  OP_DIV, /* / */
  INTEGER,
  STRING,
  CHARACTER,
};

typedef struct {
  int sym;
  int value;
} Token;
#endif
