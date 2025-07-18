#pragma once
#include "types.h"

template <typename T> struct Array {
  size_t length_;
  T* array_;

  Array(size_t length);
};


template<typename T>
Array<T>::Array(size_t length) : length_{length} {
  array_ = (T*)(((char*)&length_) + sizeof(length_));
}