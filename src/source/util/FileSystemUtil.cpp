#include "FileSystemUtil.h"

bool FileSystemUtil::createDirectory(std::string path) {
  return fs::create_directories(path);
}

bool FileSystemUtil::createFile(std::string path) {
  std::ofstream file(path);
  if(file) {
    return true;
  }
  return false;
}