#ifndef SCANNER_H
#define SCANNER_H
#include "ErrorReporter.h"
#include "SourceFile.h"
#include "CodeLocation.h"
#include <memory>
#include <vector>
#include "Token.h"
#include "TokenType.h"
#include <mpark/variant.hpp>
#include <cctype>

class Scanner {
public:
  std::shared_ptr<ErrorReporter> errorReporter;
  std::shared_ptr<SourceFile> scannedFile;
  std::vector<Token> tokens;
  Scanner(std::shared_ptr<ErrorReporter> errorReporter, std::shared_ptr<SourceFile> fileToScan);
  void scan();

private:
  CodeLocation currentLocation;
  CodeLocation startLocation;
  void scanToken();
  void consumeNumberLiteral();
  inline bool isAlpha(char c);
  inline bool isNumeric(char c);
  inline bool isAlphaNumeric(char c);
  bool match(char expected);
  char advance();
  char peek();
  char peekNext();
  bool isAtEnd();
  std::string currentLexeme();
  void addToken(TokenType type, mpark::variant<double, std::string, bool> literalValue);
  void addToken(TokenType type);
};
#endif
