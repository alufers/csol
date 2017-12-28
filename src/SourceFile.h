#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H
#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>

class SourceFile {
public:
  std::string path;
  std::string contents;
  SourceFile(const std::string &path);
};
#endif
