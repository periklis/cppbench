#include <random>
#include <limits>

#include "class_types.hpp"

/*
  Move constructor
*/
cppbench::c_ident_type::c_ident_type(cppbench::c_ident_type&& t)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(
      std::numeric_limits<int>::min(),
      std::numeric_limits<int>::max());

  m_identity = dis(gen);
  m_name = t.m_name;

  t.m_identity = 0;
  m_name = "";
}

cppbench::c_ident_type
cppbench::c_ident_type::clone()
{
  return cppbench::c_ident_type {m_identity, m_name};
}


void run_c_identity_tests ()
{
  cppbench::c_ident_type t{3, "init name"};

  std::cout << "Initial ident type object: " << t << '\n';

  auto t1 = t.clone();

  std::cout << "Cloned ident type object" << t1 << '\n';
}


int main()
{
  run_c_identity_tests();
  std::cout << "Hello class types!" << std::endl;
}
