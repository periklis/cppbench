#define BOOST_TEST_MODULE Test_CString
#include <boost/test/included/unit_test.hpp>
#include "String.hpp"

BOOST_AUTO_TEST_CASE(test_empty_cstring)
{
  cppexp::CString s {};
  BOOST_TEST(s.c_str() == "");
  BOOST_TEST(s.length() == 0);
}

BOOST_AUTO_TEST_CASE(test_cstring_from_c_string)
{
  const char* txt = "C-String to CString";
  cppexp::CString s {txt, 19};

  BOOST_TEST(s.c_str() == txt);
  BOOST_TEST(s.length() == 19);
}

BOOST_AUTO_TEST_CASE(test_cstring_subscripting)
{
  const char* txt = "C-String to CString";
  cppexp::CString s {txt, 19};

  BOOST_TEST(s[18] == "g");
  BOOST_TEST(s.at(18) == "g");
  BOOST_CHECK_THROW(s.at(19), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_cstring_copy_semantics)
{
  cppexp::CString s1 {"String", 6};
  cppexp::CString s2 {s1};

  BOOST_TEST(s1 == s2);

  cppexp::CString t1 {"1", 1};
  cppexp::CString t2 {"2", 1};

  s1 += t1;
  s2 += t2;

  BOOST_TEST(s1 != s2);
}

BOOST_AUTO_TEST_CASE(test_cstring_move_semantics)
{
  const char* txt = "String";
  cppexp::CString s1 {txt, 6};
  cppexp::CString s2 {std::move(s1)};

  BOOST_TEST(s2.c_str() == txt);
  BOOST_TEST(s1.c_str() == "");

  cppexp::CString s3 {txt, 6};
  cppexp::CString s4 = std::move(s3);

  BOOST_TEST(s4.c_str() == txt);
  BOOST_TEST(s3.c_str() == "");
}

BOOST_AUTO_TEST_CASE(test_cstring_comparison)
{
  cppexp::CString a {"AAAbbb", 6};
  cppexp::CString b {"BBBccc", 6};

  BOOST_TEST(a < b);
  BOOST_TEST(!(a > b));

  BOOST_TEST(a <= b);
  BOOST_TEST(!(a >= b));
}

BOOST_AUTO_TEST_CASE(test_cstring_concatenation)
{
  const char* txt = "AAAABBBB";
  cppexp::CString a {"AAAA", 4};
  cppexp::CString b {"BBBB", 4};

  cppexp::CString c = a + b;

  BOOST_TEST(c.c_str() == txt);
  BOOST_TEST(c.length() == 8);
}

BOOST_AUTO_TEST_CASE(test_cstring_substring)
{
  const char* txt = "stSt";
  cppexp::CString s {"TestString", 10};
  cppexp::CString sstr = s.substr(2, 4);

  BOOST_TEST(sstr.c_str() == txt);
  BOOST_TEST(sstr.length() == 4);
}
