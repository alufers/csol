#include "CodeLocation.h"
CodeLocation::CodeLocation(std::shared_ptr<SourceFile> file, int line,
                           int column, int charOffset) {
  this->file = file;
  this->line = line;
  this->charOffset = charOffset;
  this->column = column;
}
