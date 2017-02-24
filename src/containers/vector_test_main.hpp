#include "gtest/gtest.h"

typedef ::testing::Types<
  bool,
  short int, int, long int, long long int,
  unsigned short int, unsigned int, unsigned long int, unsigned long long int,
  char, signed char, unsigned char, char16_t, char32_t, wchar_t,
  float, double, long double,
  std::string, std::wstring> VectorValueTypes;

typedef ::testing::Types<
  int*, long*, long long*, char*, float*, double*, long double*> VectorPointerTypes;
