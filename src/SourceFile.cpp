#include "SourceFile.h"

SourceFile::SourceFile(const std::string &path) {
  std::ifstream file(path);
  this->contents = std::string((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
}
