#ifndef TOKEN_H
#define TOKEN_H
#include "CodeLocation.h"
#include "TokenType.h"
#include <string>

class Token {
public:
  CodeLocation location;
  TokenType type;
  std::string lexeme;

};
#endif
