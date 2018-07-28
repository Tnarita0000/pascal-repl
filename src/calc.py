from scanner import Token, CharacterCodes
# Token types
#
# EOF (end-of-file) token is used to indicate that
# there is no more input left for lexical analysis
INTEGER, EOF = 'INTEGER', 'EOF'

class Tokenizer(object):
  def __init__(self, type, value):
    # token type: INTEGER, Token.PLUS, or EOF
    self.type = type
    # token value: 0, 1, 2. 3, 4, 5, 6, 7, 8, 9, '+', or None
    self.value = value

  def __str__(self):
    """String representation of the class instance.

    Examples:
        Tokenizer(INTEGER, 3)
        Tokenizer(Token.PLUS '+')
    """
    return 'Tokenizer({type}, {value})'.format(
      type=self.type,
      value=repr(self.value)
    )

  def __repr__(self):
    return self.__str__()


class Interpreter(object):
  def __init__(self, text):
    # client string input, e.g. "3+5"
    self.text = text
    # self.pos is an index into self.text
    self.pos = 0
    # current token instance
    self.current_token = None
    self.current_char = self.text[self.pos]

  def error(self):
    raise Exception('Invalid syntax')

  def advance(self):
    self.pos += 1
    if self.pos > len(self.text) - 1:
      self.current_char = None
    else:
      self.current_char = self.text[self.pos]

  def skip_whitespace(self):
    while self.current_char is not None and self.current_char.isspace():
      self.advance()

  def integer(self):
    result = ''
    while self.current_char is not None and self.current_char.isdigit():
      result += self.current_char
      self.advance()
    return int(result)

  def get_next_token(self):
    """Lexical analyzer (also known as scanner or tokenizer)
    This method is responsible for breaking a sentence
    apart into tokens. One token at a time.
    """
    while self.current_char is not None:
      if self.current_char.isspace():
        self.skip_whitespace()
        continue
      if self.current_char.isdigit():
        return Tokenizer(INTEGER, self.integer())
      if self.current_char == '+':
        self.advance()
        return Tokenizer(Token.PLUS, '+')
      if self.current_char == '-':
        self.advance()
        return Tokenizer(Token.MINUS, '-')
      if self.current_char == '*':
        self.advance()
        return Tokenizer(Token.MULTIPLICATION, '*')
      if self.current_char == '/':
        self.advance()
        return Tokenizer(Token.DIVISION, '/')

      self.error()
    return Tokenizer(EOF, None)

  def eat(self, token_type):
    # compare the current token type with the passed token
    # type and if they match then "eat" the current token
    # and assign the next token to the self.current_token,
    # otherwise raise an exception.
    if self.current_token.type == token_type:
      self.current_token = self.get_next_token()
    else:
      self.error()

  def term(self):
    token = self.current_token
    self.eat(INTEGER)
    return token.value

  def expr(self, left = None):
    self.current_token = self.get_next_token()

    result = self.term()
    while self.current_token.type in (Token.PLUS, Token.MINUS, Token.MULTIPLICATION, Token.DIVISION):
      token = self.current_token
      if token.type == Token.PLUS:
        self.eat(Token.PLUS)
        result = result + self.term()
      elif token.type == Token.MINUS:
        self.eat(Token.MINUS)
        result = result - self.term()
      elif token.type == Token.MULTIPLICATION:
        self.eat(Token.MULTIPLICATION)
        result = result * self.term()
      elif token.type == Token.DIVISION:
        self.eat(Token.DIVISION)
        result = result / self.term()

    return result

def main():
  while True:
    try:
      text = input('\x1b[32mcalc> \x1b[37m')
    except EOFError:
      break
    if not text:
      continue
    interpreter = Interpreter(text)
    result = interpreter.expr()
    print(result)


if __name__ == '__main__':
    main()
