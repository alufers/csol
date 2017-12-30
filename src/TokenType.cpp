#include "TokenType.h"

std::string TokenTypeUtils::getTokenTypeName(TokenType tt) {
  switch (tt) {
  case TokenType::T_LEFT_PAREN:
    return "T_LEFT_PAREN";
  case TokenType::T_RIGHT_PAREN:
    return "T_RIGHT_PAREN";
  case TokenType::T_LEFT_BRACE:
    return "T_LEFT_BRACE";
  case TokenType::T_RIGHT_BRACE:
    return "T_RIGHT_BRACE";
  case TokenType::T_COMMA:
    return "T_COMMA";
  case TokenType::T_DOT:
    return "T_DOT";
  case TokenType::T_MINUS:
    return "T_MINUS";
  case TokenType::T_PLUS:
    return "T_PLUS";
  case TokenType::T_SEMICOLON:
    return "T_SEMICOLON";
  case TokenType::T_SLASH:
    return "T_SLASH";
  case TokenType::T_STAR:
    return "T_STAR";
  case TokenType::T_STAR_STAR:
    return "T_STAR_STAR";
  case TokenType::T_PERCENT:
    return "T_PERCENT";
  case TokenType::T_BANG:
    return "T_BANG";
  case TokenType::T_BANG_EQUAL:
    return "T_BANG_EQUAL";
  case TokenType::T_EQUAL:
    return "T_EQUAL";
  case TokenType::T_EQUAL_EQUAL:
    return "T_EQUAL_EQUAL";
  case TokenType::T_GREATER:
    return "T_GREATER";
  case TokenType::T_GREATER_EQUAL:
    return "T_GREATER_EQUAL";
  case TokenType::T_LESS:
    return "T_LESS";
  case TokenType::T_LESS_EQUAL:
    return "T_LESS_EQUAL";
  case TokenType::T_PLUS_PLUS:
    return "T_PLUS_PLUS";
  case TokenType::T_PLUS_EQUAL:
    return "T_PLUS_EQUAL";
  case TokenType::T_MINUS_MINUS:
    return "T_MINUS_MINUS";
  case TokenType::T_MINUS_EQUAL:
    return "T_MINUS_EQUAL";
  case TokenType::T_IDENTIFIER:
    return "T_IDENTIFIER";
  case TokenType::T_STRING:
    return "T_STRING";
  case TokenType::T_NUMBER:
    return "T_NUMBER";
  case TokenType::T_AND:
    return "T_AND";
  case TokenType::T_CLASS:
    return "T_CLASS";
  case TokenType::T_ELSE:
    return "T_ELSE";
  case TokenType::T_FALSE:
    return "T_FALSE";
  case TokenType::T_FUN:
    return "T_FUN";
  case TokenType::T_FOR:
    return "T_FOR";
  case TokenType::T_IF:
    return "T_IF";
  case TokenType::T_NIL:
    return "T_NIL";
  case TokenType::T_OR:
    return "T_OR";
  case TokenType::T_PRINT:
    return "T_PRINT";
  case TokenType::T_RETURN:
    return "T_RETURN";
  case TokenType::T_BREAK:
    return "T_BREAK";
  case TokenType::T_SUPER:
    return "T_SUPER";
  case TokenType::T_THIS:
    return "T_THIS";
  case TokenType::T_TRUE:
    return "T_TRUE";
  case TokenType::T_MUT:
    return "T_MUT";
  case TokenType::T_WHILE:
    return "T_WHILE";
  case TokenType::T_EOF:
    return "T_EOF";
  }
}

TokenType TokenTypeUtils::stringToKeyword(const std::string &value) {

  if (value == "and") {
    return TokenType::T_AND;
  } else if (value == "class") {
    return TokenType::T_CLASS;
  } else if (value == "else") {
    return TokenType::T_ELSE;
  } else if (value == "false") {
    return TokenType::T_FALSE;
  } else if (value == "fun") {
    return TokenType::T_FUN;
  } else if (value == "for") {
    return TokenType::T_FOR;
  } else if (value == "if") {
    return TokenType::T_IF;
  } else if (value == "nil") {
    return TokenType::T_NIL;
  } else if (value == "or") {
    return TokenType::T_OR;
  } else if (value == "print") {
    return TokenType::T_PRINT;
  } else if (value == "return") {
    return TokenType::T_RETURN;
  } else if (value == "break") {
    return TokenType::T_BREAK;
  } else if (value == "super") {
    return TokenType::T_SUPER;
  } else if (value == "this") {
    return TokenType::T_THIS;
  } else if (value == "true") {
    return TokenType::T_TRUE;
  } else if (value == "mut") {
    return TokenType::T_MUT;
  } else if (value == "while") {
    return TokenType::T_WHILE;
  } else {
    return TokenType::T_IDENTIFIER;
  }
}

bool TokenTypeUtils::isKeyword(const TokenType &tt) {
  switch (tt) {
  case TokenType::T_AND:
  case TokenType::T_CLASS:
  case TokenType::T_ELSE:
  case TokenType::T_FALSE:
  case TokenType::T_FUN:
  case TokenType::T_FOR:
  case TokenType::T_IF:
  case TokenType::T_NIL:
  case TokenType::T_OR:
  case TokenType::T_PRINT:
  case TokenType::T_RETURN:
  case TokenType::T_BREAK:
  case TokenType::T_SUPER:
  case TokenType::T_THIS:
  case TokenType::T_TRUE:
  case TokenType::T_MUT:
  case TokenType::T_WHILE:
    return true;
  default:
    return false;
  }
}
