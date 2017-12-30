#include "Scanner.h"

Scanner::Scanner(std::shared_ptr<ErrorReporter> errorReporter,
                 std::shared_ptr<SourceFile> fileToScan) {
  this->errorReporter = errorReporter;
  this->startLocation = CodeLocation(fileToScan, 0, 0, 0);
  this->currentLocation = CodeLocation(fileToScan, 0, 0, 0);
  this->boundFile = fileToScan;
}

void Scanner::scan() {
  this->scannedFile = this->boundFile.lock();
  if(!this->scannedFile) {
    throw std::runtime_error("File to scan is deleted (could not lock weak_ptr).");
  }
  while (!this->isAtEnd()) {
    this->startLocation = this->currentLocation;
    this->scanToken();
    if (this->errorReporter->hadScanningError) {
      break;
    }
  }
  this->scannedFile = nullptr;
}

void Scanner::scanToken() {
  char c = this->advance();
  switch (c) {
  case '(':
    this->addToken(TokenType::T_LEFT_PAREN);
    break;
  case ')':
    this->addToken(TokenType::T_RIGHT_PAREN);
    break;
  case '{':
    this->addToken(TokenType::T_LEFT_BRACE);
    break;
  case '}':
    this->addToken(TokenType::T_RIGHT_BRACE);
    break;
  case ',':
    this->addToken(TokenType::T_COMMA);
    break;
  case '.':
    this->addToken(TokenType::T_DOT);
    break;
  case '-':
    if (this->match('-')) {
      this->addToken(TokenType::T_MINUS_MINUS);
    } else if (this->match('=')) {
      this->addToken(TokenType::T_MINUS_EQUAL);
    } else {
      this->addToken(TokenType::T_MINUS);
    }
    break;
  case '+':
    if (this->match('+')) {
      this->addToken(TokenType::T_PLUS_PLUS);
    } else if (this->match('=')) {
      this->addToken(TokenType::T_PLUS_EQUAL);
    } else {
      this->addToken(TokenType::T_PLUS);
    }
    break;
  case ';':
    this->addToken(TokenType::T_SEMICOLON);
    break;
  case '/':
    if (this->match('/')) { // match a single line comment
      while (this->peek() != '\n' && !this->isAtEnd()) { // consume comments
        this->advance();
      }
    } else {
      this->addToken(TokenType::T_SLASH);
    }
    break;
  case '*':
    this->addToken(this->match('*') ? TokenType::T_STAR_STAR
                                    : TokenType::T_STAR);
    break;
  case '%':
    this->addToken(TokenType::T_PERCENT);
    break;
  case '!':
    this->addToken(this->match('=') ? TokenType::T_BANG_EQUAL
                                    : TokenType::T_BANG);
    break;
  case '>':
    this->addToken(this->match('=') ? TokenType::T_GREATER_EQUAL
                                    : TokenType::T_GREATER);
    break;
  case '<':
    this->addToken(this->match('=') ? TokenType::T_LESS_EQUAL
                                    : TokenType::T_LESS);
    break;
  case '=':
    this->addToken(this->match('=') ? TokenType::T_EQUAL_EQUAL
                                    : TokenType::T_EQUAL);
    break;
  case '\n':
  case '\t':
  case '\r':
  case ' ':
    /// :(
    break;
  case '"':
    this->consumeStringLiteral();
    break;
  default:
    if (this->isNumeric(c)) {
      this->consumeNumberLiteral();
    } else if (this->isAlpha(c)) {
      this->consumeIdentifierOrKeyword();
    } else {
      this->errorReporter->reportScanningError(
          "Unexpected character " + std::string(1, c), this->currentLocation);
    }
  }
}

void Scanner::consumeNumberLiteral() {
  while (this->isNumeric(this->peek()) ||
         (this->peek() == '.' &&
          this->isNumeric(this->peekNext()))) { // check if there is a dot and a
                                                // number after it
    this->advance();
  }
  this->addToken(TokenType::T_NUMBER, std::stod(this->currentLexeme()));
}
void Scanner::consumeStringLiteral() {
  std::ostringstream literalStream;
  while (this->peek() != '"' && !this->isAtEnd()) {
    char c = this->advance();
    if (c == '\\') {          // match escape sequences
      if (this->match('"')) { //  \"
        literalStream << '"';
      } else if (this->match('\\')) { // \\  
        literalStream << '\\';
      } else if (this->match('n')) {  // new line
        literalStream << '\n';
      } else if (this->match('t')) { // tabulator
        literalStream << '\t';
      } else if (this->match('\n')) {
        // do nothing, escaped newline
      } else {
        this->errorReporter->reportScanningError("Illegal escape sequence \\" +
                                                     std::string(1, c),
                                                 this->currentLocation);
        return;
      }
    } else {
      literalStream << c;
    }
  }
  if (this->isAtEnd()) {
    this->errorReporter->reportScanningError("Unterminated string",
                                             this->startLocation);
    return;
  }
  this->advance(); // move past "
  addToken(TokenType::T_STRING, literalStream.str());
}
std::string Scanner::currentLexeme() {
  return this->scannedFile->contents.substr(this->startLocation.charOffset,
                                            this->currentLocation.charOffset -
                                                this->startLocation.charOffset);
}
void Scanner::consumeIdentifierOrKeyword() {
  while (this->isAlphaNumeric(peek()) && !this->isAtEnd()) {
    this->advance();
  }
  std::string value = this->currentLexeme();
  TokenType tt = TokenTypeUtils::stringToKeyword(value);
  if (tt == TokenType::T_IDENTIFIER) {
    this->addToken(TokenType::T_IDENTIFIER, value);
  } else {
    this->addToken(tt);
  }
}
void Scanner::addToken(TokenType type,
                       mpark::variant<double, std::string, bool> literalValue) {
  Token t;
  t.lexeme = this->currentLexeme();
  t.literalValue = literalValue;
  t.type = type;
  t.location = this->startLocation;
  this->tokens.push_back(t);
}
void Scanner::addToken(TokenType type) { this->addToken(type, false); }
bool Scanner::match(char expected) {
  if (isAtEnd())
    return false;
  if (this->scannedFile->contents[this->currentLocation.charOffset] != expected)
    return false;
  this->advance();
  return true;
}

char Scanner::advance() {
  this->currentLocation.nextChar();
  char c = this->scannedFile->contents[this->currentLocation.charOffset - 1];
  if (c == '\n') {
    this->currentLocation.nextLine();
  }
  return c;
}

char Scanner::peek() {
  if (isAtEnd())
    return '\0';
  return this->scannedFile->contents[this->currentLocation.charOffset];
}

char Scanner::peekNext() {
  if (this->currentLocation.charOffset + 1 >=
      this->scannedFile->contents.size())
    return '\0';
  return this->scannedFile->contents[this->currentLocation.charOffset + 1];
}

bool Scanner::isAtEnd() {
  return this->currentLocation.charOffset >= this->scannedFile->contents.size();
}

bool Scanner::isAlpha(char c) {
  return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}

bool Scanner::isNumeric(char c) {
  return std::isdigit(static_cast<unsigned char>(c));
}

bool Scanner::isAlphaNumeric(char c) {
  return std::isalnum(static_cast<unsigned char>(c));
}
