#include "String.hpp"

namespace cppexp {

  unsigned long CString::length() const
  {
    char* tmp = rep;
    unsigned long i = 0;
    while (*tmp++ != '\0') ++i;

    return i;
  }

  char* CString::at(unsigned long pos) const
  {
    if (pos > (len - 1))
      throw std::out_of_range("CString::at()");

    return &rep[pos];
  }

  CString CString::substr(unsigned long pos, unsigned long count) const
  {
    char* tmp = new char[count+1];

    for (unsigned long i = pos; rep[i] != rep[pos+count]; ++i)
      tmp[i-pos] = rep[i];

    tmp[count+1] = '\0';

    return {tmp, count};
  }

  CString& CString::operator=(const CString& s)
  {
    unsigned long nl = s.len + 1;
    char* buf = new char[nl];

    for (unsigned long i = 0; rep[i] != '\0'; ++i)
      buf[i] = rep[i];

    delete[] rep;
    rep = buf;
    len += s.len;

    return *this;
  }

  CString& CString::operator=(CString&& s)
  {
    char* tmp = rep;
    rep = s.rep;
    s.rep = tmp;

    len = s.len;
    s.len = 0;

    return *this;
  }

  CString& CString::operator+=(const CString& s)
  {
    unsigned long nl = len + s.len + 1;
    char* buf = new char[nl];

    for (unsigned long i = 0; rep[i] != '\0'; ++i)
      buf[i] = rep[i];

    for (unsigned long i = 0; s.rep[i] != '\0'; ++i)
      buf[i+len] = s.rep[i];

    delete[] rep;
    rep = buf;
    len += s.len;

    return *this;
  }

  /*
    Namespace helper functions
   */

  CString operator+(const CString& a, const CString& b)
  {
    CString c {a};
    return c+=b;
  }

  bool operator==(const CString& a, const CString& b)
  {
    const char* pb = b.c_str();
    const char* pa = a.c_str();

    for (; *pa != '\0'; ++pa, ++pb)
      if (*pa != *pb)
        return false;

    return true;
  }

  bool operator!=(const CString& a, const CString& b)
  {
    return !(a == b);
  }

  bool operator<(const CString& a, const CString& b)
  {
    const char* pb = b.c_str();
    const char* pa = a.c_str();

    for(; *pa != '\0'; ++pa, ++pb) {
      if (*pa > *pb)
        return false;
    }

    return true;
  }

  bool operator>(const CString& a, const CString& b)
  {
    return !(a < b);
  }

  bool operator<=(const CString& a, const CString& b)
  {
    return !(a > b);
  }

  bool operator>=(const CString& a, const CString& b)
  {
    return !(a < b);
  }

  std::ostream& operator<<(std::ostream& out, const CString& s)
  {
    // TODO Make my CString independent from std::string
    return out << std::string(s.c_str());
  }
}
