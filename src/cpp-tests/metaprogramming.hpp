// -*-c++-*-

#ifndef METAPROGRAMMING_H_
#define METAPROGRAMMING_H_

namespace cppbench {

/**
 * Warm up excercises
 *
 */
template<unsigned int N>
struct fibonacci {
  enum { value = fibonacci<N-1>::value + fibonacci<N-2>::value};
};

template<>
struct fibonacci<1> {
  enum {value = 1};
};

template<>
struct fibonacci<0> {
  enum {value = 0};
};

struct true_type {
  static constexpr bool  value = true;
};
struct false_type {
  static constexpr bool value = false;
};

template<typename T>
struct pointer_of {
  typedef T* type;
};

template<typename T>
struct is_reference
    : false_type {
  typedef false_type type;
};

template<typename T>
struct is_reference<T&>
    : true_type {
  typedef true_type type;
};

template<typename T>
struct is_reference<T&&>
    : true_type {
  typedef true_type type;
};

}

namespace template_metagrogramming_book {

/*
 * Utilities
 *
 */
struct true_type {
  static constexpr bool  value = true;
};
struct false_type {
  static constexpr bool value = false;
};

template<typename T, typename U>
struct is_same : false_type {};

template<typename T>
struct is_same<T,T> : true_type {};


/*
 * Exercise 2.0
 *
 */
template<typename T>
struct add_const_ref {
  typedef T const& type;
};

template<typename T>
struct add_const_ref<T*> {
  typedef T const& type;
};

template<typename T>
struct add_const_ref<T&> {
  typedef T& type;
};


/*
 * Exercise 2.1
 *
 */
template<typename H, typename N, typename R>
struct replace_type {};

template<typename H, typename N>
struct replace_type<H, N, N> {
  typedef H type;
};

template<typename H, typename N, typename R>
struct replace_type<H const, N, R> {
  typedef R const type;
};

template<typename H, typename N, typename R>
struct replace_type<H*, N, R> {
  typedef R* type;
};

template<typename H, typename N, typename R>
struct replace_type<H const *, N, R> {
  typedef R const*  type;
};

template<typename H, typename N, typename R>
struct replace_type<H const * const, N, R> {
  typedef R const * const type;
};

template<typename H, typename N, typename R>
struct replace_type<H&, N, R> {
  typedef R& type;
};

template<typename H, typename N, typename R>
struct replace_type<H const&, N, R> {
  typedef R const& type;
};

template<typename H, typename N, typename R>
struct replace_type<H (*)(), N, R> {
  typedef R (*type)();
};

template<typename H, typename N, typename R>
struct replace_type<void (*)(H), N, R> {
  typedef void (*type)(R);
};

template<typename H, typename N, typename R>
struct replace_type<H (*)(H), N, R> {
  typedef R (*type)(R);
};


/*
 * Exercise 2.4
 *
 */
template<typename T>
struct type_descriptor {};

template<>
struct type_descriptor<int> {
  typedef int type;
  operator const char*() { return "int"; }
};

template<>
struct type_descriptor<long> {
  typedef long type;
  operator const char*() { return "long"; }
};

template<>
struct type_descriptor<char> {
  typedef char type;
};

}

#endif
