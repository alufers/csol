#ifndef SCANNER_H
#define SCANNER_H
#include "ErrorReporter.h"
#include "SourceFile.h"
#include <memory>
#include <vector>

class Scanner {
public:
  std::shared_ptr<ErrorReporter> errorReporter;
  std::shared_ptr<SourceFile> scannedFile;
  Scanner(std::shared_ptr<ErrorReporter> errorReporter);
  void scan(std::shared_ptr<SourceFile> fileToScan);

private:
    int line; // current line
    int column; // current column
    int charOffset; // current position
    int start; // start offset of the current lexeme
};
#endif
