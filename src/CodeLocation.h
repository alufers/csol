#ifndef CODE_LOCATION
#define CODE_LOCATION
#include "SourceFile.h"
#include <memory>
#include <string>
#include <vector>
class CodeLocation {
public:
  std::shared_ptr<SourceFile> file;
  int line;
  int charOffset;
  int column;
  CodeLocation();
  CodeLocation(std::shared_ptr<SourceFile> file, int line, int column, int charOffset);
  void nextChar();
  void nextLine();
  std::vector<std::string> linesBefore(int before) const;
};
#endif
