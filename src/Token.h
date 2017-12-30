#ifndef TOKEN_H
#define TOKEN_H
#include "CodeLocation.h"
#include "TokenType.h"
#include <string>
#include <mpark/variant.hpp>

class CodeLocation;
class Token {
public:
  CodeLocation location;
  TokenType type;
  std::string lexeme;
  mpark::variant<double, std::string, bool> literalValue;
};
#endif
