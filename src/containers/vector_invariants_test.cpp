#include "gtest/gtest.h"
#include "vector.hpp"

class vector_invariants_test :
    public ::testing::TestWithParam< ::testing::tuple<int, int> > {
 public:
  vector_invariants_test() {
    vec_size = ::testing::get<0>(GetParam());
    vec_value = ::testing::get<1>(GetParam());
    vec = new cppbench::containers::vector<int>(vec_size, vec_value);
  }

  virtual ~vector_invariants_test() {
    delete vec;
    vec = nullptr;
  }

  int vec_size;
  int vec_value;
  cppbench::containers::vector<int>* vec;
};

TEST_P(vector_invariants_test, vector_explicit_ctor)
{
  for (typename cppbench::containers::vector<int>::size_type i = 0;
       i < vec_size; ++i) {
    EXPECT_EQ(vec_value, (*vec)[i]);
  }
}

TEST_P(vector_invariants_test, vector_begin_iter)
{
  EXPECT_EQ(vec_value, *vec->begin());
}

TEST_P(vector_invariants_test, vector_reverse_begin_iter)
{
  EXPECT_EQ(vec_value, *vec->rbegin());
  EXPECT_EQ(*(vec->end()-1), *vec->rbegin());
  EXPECT_EQ(vec->end(), vec->rbegin().base());
}

TEST_P(vector_invariants_test, vector_end_iter)
{
  EXPECT_EQ((vec->begin() + vec_size), vec->end());
}

TEST_P(vector_invariants_test, vector_reverse_end_iter)
{
  EXPECT_EQ((vec->rbegin() + vec_size), vec->rend());
  EXPECT_EQ(vec->begin(), vec->rend().base());
}

TEST_P(vector_invariants_test, vector_size)
{
  EXPECT_EQ(vec_size, vec->size());
}

TEST_P(vector_invariants_test, vector_front_ref)
{
  EXPECT_EQ(*vec->begin(), vec->front());
}

TEST_P(vector_invariants_test, vector_back_ref)
{
  EXPECT_EQ(*(vec->end() - 1), vec->back());
}

TEST_P(vector_invariants_test, vector_operator_subscript) {
  EXPECT_EQ(10, (*vec)[vec_size-1]);
}

TEST_P(vector_invariants_test, vector_operator_at) {
  EXPECT_EQ(10, vec->at(vec_size - 1));
  EXPECT_THROW(vec->at(vec_size), std::out_of_range);
}

TEST_P(vector_invariants_test, vector_empty) {
  EXPECT_FALSE(vec->empty());
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_invariants_test,
    ::testing::Combine(
         ::testing::Range(1, 10, 1),
         ::testing::Values(10)));
