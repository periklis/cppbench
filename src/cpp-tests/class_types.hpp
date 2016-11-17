// -*-c++-*-

#ifndef CLASS_TYPES_H_
#define CLASS_TYPES_H_
#include <iostream>

#include <string>

namespace cppbench {

/*
  Basic class for identity type
 */
class c_ident_type {
 public:
  explicit c_ident_type(int id)
      : m_identity(id) {}

  explicit c_ident_type(int id, const std::string& s)
      : m_identity(id), m_name(s) {}

  c_ident_type(const c_ident_type& t) = delete;
  c_ident_type(c_ident_type&& t);

  c_ident_type operator =(const c_ident_type& t) = delete;
  c_ident_type operator =(c_ident_type&& t) = delete;

  c_ident_type clone();

  int GetIdentity() const { return m_identity; }
  std::string GetName() const { return m_name; }
 private:
  int m_identity {};
  std::string m_name {};
};

std::ostream& operator<< (std::ostream& os, const c_ident_type& t)
{
  return os << "[" << t.GetIdentity() << ":" << t.GetName() << "]";
}

class c_value_type {


};


class c_base_type {


};

class c_traits_type {


};

}
#endif
