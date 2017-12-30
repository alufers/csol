#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H
#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <memory>
//#include "Scanner.h"

class Scanner;
class SourceFile {
public:
  std::string path;
  std::string contents;
  std::shared_ptr<Scanner> scanner;
  SourceFile(const std::string &path);
};
#endif
