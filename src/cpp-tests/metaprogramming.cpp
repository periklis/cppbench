#include <iostream>

#include "metaprogramming.hpp"

void solve_warmup(){
  using namespace cppbench;

  std::cout << "First fibonacci numbers: "
            << fibonacci<0>::value << ", "
            << fibonacci<1>::value << ", "
            << fibonacci<2>::value << ", "
            << fibonacci<3>::value << ", "
            << fibonacci<4>::value << ", "
            << fibonacci<5>::value << ", "
            << fibonacci<6>::value << ", "
            << fibonacci<7>::value << ", "
            << fibonacci<8>::value
            << std::endl;

  int i = 1;
  pointer_of<int>::type ip = &i;

  std::cout << "Return address of pointer_of<int>::type : \t"
            << ip
            << std::endl;

  std::cout << "Return predicate result is_reference<int&>::type : \t"
            << is_reference<int&>::value
            << std::endl;
}

void solve_exercise_2_0 ()
{
  using namespace template_metagrogramming_book;
  std::cout << "add_const_ref<T> returns T const& : \t"
            << is_same<typename add_const_ref<int>::type, int const&>::value
            << std::endl;

  std::cout << "add_const_ref<T*> returns T const& : \t"
            << is_same<typename add_const_ref<int*>::type, int const&>::value
            << std::endl;

  std::cout << "add_const_ref<T&> returns T& : \t"
            << is_same<typename add_const_ref<int&>::type, int&>::value
            << std::endl;
}

void solve_exercise_2_1()
{
  using namespace template_metagrogramming_book;

  typedef replace_type<void*, void, int>::type t1;

  std::cout << "replace_type<void*, void, int>::type returns int* : \t"
            << is_same<t1, int*>::value
            << std::endl;

  typedef replace_type<int&, int, long>::type r1;
  typedef replace_type<int const&, int, long>::type r1c;
  typedef replace_type<const int&, int, long>::type cr1;

  std::cout << "replace_type<int&, int, long>::type returns long& : \t"
            << is_same<r1, long&>::value
            << std::endl;

  std::cout << "replace_type<int const&, int, long>::type returns long const& : \t"
            << is_same<r1c, long const&>::value
            << std::endl;

  std::cout << "replace_type<const int&, int, long>::type returns const long& : \t"
            << is_same<cr1, const long&>::value
            << std::endl;

  typedef replace_type<int (*)(), int, long>::type rtn1;
  typedef replace_type<void (*)(int), int, long>::type arg1;
  typedef replace_type<int (*)(int), int, long>::type fp1;

  std::cout << "replace_type<int (*)(), int, long>::type returns long (*)() : \t"
            << is_same<rtn1, long (*)()>::value
            << std::endl;

  std::cout << "replace_type<void (*)(void), int, long>::type returns void (*)(long) : \t"
            << is_same<arg1, void (*)(long)>::value
            << std::endl;

  std::cout << "replace_type<int (*)(int), int, long>::type returns long (*)(long) : \t"
            << is_same<fp1, long (*)(long)>::value
            << std::endl;
}

void solve_exercise_2_4 ()
{
  using namespace template_metagrogramming_book;

  std::cout << type_descriptor<int>() << std::endl;
  std::cout << type_descriptor<long>() << std::endl;
}

int main () {
  solve_warmup();
  solve_exercise_2_0();
  solve_exercise_2_1();
  solve_exercise_2_4();


  return 0;
}
