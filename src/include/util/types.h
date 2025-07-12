#pragma once

#include <string>
#include <vector>

typedef unsigned long size_t;

namespace Datatype
{
  enum class Type {
    INT, INTASC, INTDESC,
    DOUBLE, DOUBLEASC, DOUBLEDESC,
    STRING, STRINGASC, STRINGDESC,
    INVALID 
  }; 

  [[maybe_unused]] static Type getTypeFromString(std::string type) {
    if(type == "INT") {
      return Type::INT;
    } else if(type == "INTASC") {
      return Type::INTASC;
    } else if(type == "INTDESC") {
      return Type::INTDESC;
    } else if(type == "DOUBLE") {
      return Type::DOUBLE;
    } else if(type == "DOUBLEASC") {
      return Type::DOUBLEASC;
    } else if(type == "DOUBLEDESC") {
      return Type::DOUBLEDESC;
    } else if(type == "STRING") {
      return Type::STRING;
    } else if(type == "STRINGASC") {
      return Type::STRINGASC;
    } else if(type == "STRINGDESC") {
      return Type::STRINGDESC;
    }
    return Type::INVALID;
  }

} // namespace Datatype


namespace Structure
{
  enum class Type {
    LIGA,
    INVALID
  };

  [[maybe_unused]] static Type getTypeFromString(std::string type) {
    if(type == "LIGA") {
      return Type::LIGA;
    }
    return Type::INVALID;
  }

} // namespace Structure


