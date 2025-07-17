#include "StringUtil.h"


std::string StringReader::extractWord(std::string& txt, size_t& position) {
  std::string word = "";

  bool word_finished = false;
  while(position < txt.length()) {
    char ch = txt.at(position);
    if(((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) && !word_finished) {
      word.push_back(ch);
    } else if (word.length() > 0 && !word_finished) {
      word_finished = true;
    } 
    
    if(word_finished && ch != ' ') {
      return word;
    }
    position++;
  }

  return word;
}

int StringReader::extractInteger(std::string& txt, size_t& position) {
  int integer = 0;

  bool word_found = false;
  bool word_finished = false;
  while(position < txt.length()) {
    char ch = txt.at(position);
    if((ch >= '0' && ch <= '9') && !word_finished) {
      word_found = true;
      integer = integer * 10 + (int)(ch - '0');
    } else if (word_found && !word_finished) {
      word_finished = true;
    } 
    
    if(word_finished && ch != ' ') {
      return integer;
    } else if(!word_found && ch != ' ') {
      return integer;
    }

    position++;
  }

  return integer;
}

bool StringReader::waitForNextArgument(std::string& txt, size_t& position, char separator) {
  bool separator_found = true;

  while(position < txt.length()) {
    char ch = txt.at(position);
    if(ch != ' ' && ch != separator) {
      return separator_found;
    } else if(ch == separator) {
      separator_found = true;
    }
    
    position++;
  }
  return false;
}

std::vector<std::string> StringUtil::splitString(std::string& cmd, std::string delimiter) {
  std::vector<std::string> tokens;
  size_t position = 0;
  while ((position = cmd.find(delimiter)) != std::string::npos) {
      std::string token = cmd.substr(0, position);
      if(token != "") {
        tokens.push_back(token);
      }
      cmd.erase(0, position + delimiter.length());
  }
  tokens.push_back(cmd);

  return tokens;
}