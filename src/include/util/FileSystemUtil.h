#pragma once

#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

struct FileSystemUtil {

  static bool createDirectory(std::string path);
  static bool createFile(std::string path);
};