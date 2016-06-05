#include "String.hpp"

#include <iostream>

cppexp::CString createString(const char* p, unsigned long s)
{
  return cppexp::CString {p, s};
}

int subroutine(int a, int b)
{
  int c = a + b;
  return c;
}

int main()
{
  unsigned long s = 6;
  const char* p = "String";
  std::cout << "------ Starting Tests ------\n";
  std::cout << "Tests moved to boost::test. Please run ./build/tests/run-tests!" << "\n";
  subroutine(1, 2);
  cppexp::CString str = createString(p, s);

  std::cout << "String content: " << str << "\n";
  std::cout << "------ End Tests -----------\n";
}
