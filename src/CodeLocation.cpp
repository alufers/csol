#include "CodeLocation.h"
CodeLocation::CodeLocation() {}
CodeLocation::CodeLocation(std::shared_ptr<SourceFile> file, int line,
                           int column, int charOffset) {
  this->file = file;
  this->line = line;
  this->charOffset = charOffset;
  this->column = column;
}

void CodeLocation::nextLine() {
  this->line++;
  this->column = 0;
}

void CodeLocation::nextChar() {
  this->charOffset++;
  this->column++;
}

std::vector<std::string> CodeLocation::linesBefore(int before) const {
  int lines = 0;
  int offset = 0;
  for (offset = 0; offset < this->file->contents.size(); offset++) {
    if (this->file->contents[offset] == '\n') {
      lines++;
      if (lines > this->line - before) {
        break;
      }
    }
  }
  offset++;
  std::vector<std::string> out;
  std::string currentLine;
  for (; offset < this->file->contents.size(); offset++) {
    currentLine += this->file->contents[offset];
    if (this->file->contents[offset] == '\n') {
      lines++;
      out.push_back(currentLine);
      currentLine.clear();
      if (lines > this->line + 1) {
        break;
      }
    }
  }

  return out;
}
