#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE
#include <string>

enum class TokenType {
  T_LEFT_PAREN,
  T_RIGHT_PAREN,
  T_LEFT_BRACE,
  T_RIGHT_BRACE,
  T_COMMA,
  T_DOT,
  T_MINUS,
  T_PLUS,
  T_SEMICOLON,
  T_SLASH,
  T_STAR,
  T_STAR_STAR,
  T_PERCENT,
  T_BANG,
  T_BANG_EQUAL,
  T_EQUAL,
  T_EQUAL_EQUAL,
  T_GREATER,
  T_GREATER_EQUAL,
  T_LESS,
  T_LESS_EQUAL,
  T_PLUS_PLUS,
  T_MINUS_MINUS,

  // Literals.
  T_IDENTIFIER,
  T_STRING,
  T_NUMBER,

  // Keywords.
  T_AND,
  T_CLASS,
  T_ELSE,
  T_FALSE,
  T_FUN,
  T_FOR,
  T_IF,
  T_NIL,
  T_OR,
  T_PRINT,
  T_RETURN,
  T_BREAK,
  T_SUPER,
  T_THIS,
  T_TRUE,
  T_MUT,
  T_WHILE,

  T_EOF
};

class TokenTypeUtils {
    static std::string getTokenTypeName(TokenType tt);
};
#endif