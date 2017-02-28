#include "gtest/gtest.h"
#include "vector.hpp"

class vector_operators_test :
    public ::testing::TestWithParam< ::testing::tuple<int, int> > {
 public:
  vector_operators_test() {
    vec_size = ::testing::get<0>(GetParam());
    vec_value = ::testing::get<1>(GetParam());
    lhs = new cppbench::containers::vector<int>(vec_size, vec_value);
    rhs = new cppbench::containers::vector<int>(vec_size, vec_value);
  }

  virtual ~vector_operators_test() {
    delete lhs;
    delete rhs;
    lhs = rhs = nullptr;
  }

  int vec_size;
  int vec_value;
  cppbench::containers::vector<int>* lhs;
  cppbench::containers::vector<int>* rhs;
};

TEST_P(vector_operators_test, vector_eq_test)
{
  EXPECT_TRUE(*lhs == *rhs);
}

TEST_P(vector_operators_test, vector_neq_test)
{
  rhs->push_back(3);
  EXPECT_TRUE(*lhs != *rhs);
}

TEST_P(vector_operators_test, vector_l_test)
{
  rhs->push_back(12);
  EXPECT_TRUE(*lhs < *rhs);
}

TEST_P(vector_operators_test, vector_le_test)
{
  EXPECT_TRUE(*lhs <= *rhs);
}

TEST_P(vector_operators_test, vector_g_test)
{
  lhs->push_back(12);
  EXPECT_TRUE(*lhs > *rhs);
}

TEST_P(vector_operators_test, vector_ge_test)
{
  EXPECT_TRUE(*lhs >= *rhs);
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_operators_test,
    ::testing::Combine(
         ::testing::Values(10),
         ::testing::Values(10)));
