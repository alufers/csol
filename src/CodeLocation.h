#ifndef CODE_LOCATION
#define CODE_LOCATION
#include "SourceFile.h"
#include <memory>

class CodeLocation {
public:
  std::shared_ptr<SourceFile> file;
  int line;
  int charOffset;
  int column;
  CodeLocation(std::shared_ptr<SourceFile> file, int line, int column, int charOffset);
};
#endif
