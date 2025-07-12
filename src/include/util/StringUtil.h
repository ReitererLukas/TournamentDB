#pragma once

#include <string>
#include <vector>

struct StringReader {
  static std::string extractWord(std::string& txt, size_t& position);
  static int extractInteger(std::string& txt, size_t& position);
  static bool waitForNextArgument(std::string& txt, size_t& position, char separator = ',');
};

struct StringUtil {
  static std::vector<std::string> splitString(std::string& cmd, std::string delimiter);
};