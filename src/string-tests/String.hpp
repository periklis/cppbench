// -*-c++-*-
#include <algorithm>
#include <stdexcept>

#ifndef STRING_H_
#define STRING_H_

namespace cppexp {

  class CString {
  public:
    CString(): rep{new char[1]}, len{0} { rep[0] = '\0'; }

    CString(const char* c, unsigned long l)
      : rep{new char[l]}, len{l}
    {
      for (unsigned long i = 0; c[i] != '\0'; ++i)
        rep[i] = c[i];
      rep[l] = '\0';
    }

    CString(const CString& s)
      : rep{new char[s.len]}, len{s.len}
    {
      for (unsigned long i = 0; s.rep[i] != '\0'; ++i)
        rep[i] = s.rep[i];
      rep[len]= '\0';
    }

    CString& operator=(const CString& s);

    CString(CString&& s)
      : CString()
    {
      char* tmp = rep;
      rep = s.rep;
      s.rep = tmp;
      len = s.len;
      s.len = 0;
    }

    CString& operator=(CString&& s);

    ~CString() { delete[] rep; }

    CString& operator+=(const CString& s);

    char* operator[](unsigned long i) { return &rep[i]; }

    const char* c_str() const { return rep; }
    unsigned long length() const;
    char* at(unsigned long pos) const;

    CString substr(unsigned long pos, unsigned long count) const;

  private:
    char* rep;
    unsigned long len;
  };

  CString operator+(const CString& a, const CString& b);
  bool operator==(const CString& a, const CString& b);
  bool operator!=(const CString& a, const CString& b);
  bool operator<(const CString& a, const CString& b);
  bool operator>(const CString& a, const CString& b);
  bool operator<=(const CString& a, const CString& b);
  bool operator>=(const CString& a, const CString& b);

  std::ostream& operator<<(std::ostream& out, const CString& s);
}

#endif
