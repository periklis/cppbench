#include "gtest/gtest.h"
#include "vector.hpp"

class vector_mutate_test
    : public ::testing::TestWithParam< ::testing::tuple<int, int> > {

 public:
  vector_mutate_test() {
    vec_size = ::testing::get<0>(GetParam());
    vec_value = ::testing::get<1>(GetParam());
    vec = new cppbench::containers::vector<int>(vec_size, vec_value);
  }

  virtual ~vector_mutate_test() {
    delete vec;
    vec = nullptr;
  }

  int vec_size;
  int vec_value;
  cppbench::containers::vector<int>* vec;
};

TEST_P(vector_mutate_test, vector_push_back_lvalue) {
  const int val = 3;
  auto init_cap = vec->capacity();
  vec->push_back(val);

  EXPECT_EQ(vec_size + 1, vec->size());
  EXPECT_EQ(val, (*vec)[vec_size]);
  EXPECT_EQ(init_cap, vec->capacity());
}

TEST_P(vector_mutate_test, vector_push_back_extend_cap) {
  const int val = 3;
  auto init_cap = vec->capacity();

  for(int i = 0; i <= vec_size; ++i) {
    vec->push_back(val);
  }

  EXPECT_EQ(2 * init_cap, vec->capacity());
}

TEST_P(vector_mutate_test, vector_push_back_rvalue) {
  const int val = 3;
  auto init_cap = vec->capacity();
  vec->push_back(std::move(val));

  EXPECT_EQ(vec_size + 1, vec->size());
  EXPECT_EQ(val, (*vec)[vec_size]);
  EXPECT_EQ(init_cap, vec->capacity());
}

TEST_P(vector_mutate_test, vector_pop_back) {
  vec->pop_back();
  EXPECT_EQ(vec_size - 1, vec->size());
}

TEST_P(vector_mutate_test, vector_clear) {
  auto init_cap = vec->capacity();
  vec->clear();
  EXPECT_EQ(0, vec->size());
  EXPECT_EQ(init_cap, vec->capacity());
}

TEST_P(vector_mutate_test, vector_reserve) {
  auto init_cap = vec->capacity();
  auto new_cap = 2*init_cap;
  vec->reserve(new_cap);
  EXPECT_EQ(new_cap, vec->capacity());
}

TEST_P(vector_mutate_test, vector_reserve_above_max_size) {
  typedef typename cppbench::containers::vector<int>::size_type sizeT;
  EXPECT_THROW(vec->reserve(std::numeric_limits<sizeT>::max()+1), std::length_error);
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_mutate_test,
    ::testing::Combine(
         ::testing::Range(1, 10, 1),
         ::testing::Values(10)));


class vector_shrink_test
    : public ::testing::TestWithParam< ::testing::tuple<int,int> > {

 public:
  vector_shrink_test() {
    vec_size = ::testing::get<0>(GetParam());
    vec_value = ::testing::get<1>(GetParam());
    vec = new cppbench::containers::vector<int>(vec_size, vec_value);
  }

  virtual ~vector_shrink_test() {
    delete vec;
    vec = nullptr;
  }

  int vec_value;
  int vec_size;
  cppbench::containers::vector<int>* vec;
};

TEST_P(vector_shrink_test, vector_shrink_to_fit) {
  vec->shrink_to_fit();
  EXPECT_EQ(vec->size(), vec->capacity());
  EXPECT_EQ(vec_size, vec->size());
  EXPECT_EQ(vec_value, vec->back());
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_shrink_test,
    ::testing::Combine(
         ::testing::Range(10, 11, 1),
         ::testing::Values(10)));
