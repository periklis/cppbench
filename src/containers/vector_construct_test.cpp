#include <iostream>
#include "gtest/gtest.h"
#include "vector.hpp"
#include "vector_test_main.hpp"

/*
  TESTS FOR DEFAULT CONSTRUCTION
*/
template<typename T>
class vector_default_construct_test
    : public ::testing::Test {

 public:
  vector_default_construct_test()
      : vec{new cppbench::containers::vector<T>()} {}

  ~vector_default_construct_test() {
    delete vec;
    vec = nullptr;
  }

  cppbench::containers::vector<T>* vec;
};

TYPED_TEST_CASE_P(vector_default_construct_test);

TYPED_TEST_P(vector_default_construct_test, vector_default_ctor) {
  EXPECT_EQ(0, this->vec->size());
  EXPECT_EQ(nullptr, this->vec->begin());
  EXPECT_EQ(nullptr, this->vec->end());
  EXPECT_TRUE(this->vec->begin() == this->vec->end());
  EXPECT_TRUE(this->vec->empty());
}

TYPED_TEST_P(vector_default_construct_test, vector_default_typedefs) {
  auto cond1 = std::is_same< typename cppbench::containers::vector<TypeParam>::value_type, TypeParam>::value;
  ASSERT_TRUE(cond1);

  auto cond2 = std::is_same<typename cppbench::containers::vector<TypeParam>::reference, TypeParam&>::value;
  ASSERT_TRUE(cond2);

  auto cond3 = std::is_same<typename cppbench::containers::vector<TypeParam>::const_reference, const TypeParam&>::value;
  ASSERT_TRUE(cond3);

  auto cond4 = std::is_same<typename cppbench::containers::vector<TypeParam>::iterator, TypeParam*>::value;
  ASSERT_TRUE(cond4);

  auto cond5 = std::is_same<typename cppbench::containers::vector<TypeParam>::const_iterator, const TypeParam*>::value;
  ASSERT_TRUE(cond5);
}

REGISTER_TYPED_TEST_CASE_P(
    vector_default_construct_test,
    vector_default_ctor,
    vector_default_typedefs);

INSTANTIATE_TYPED_TEST_CASE_P(vector_value_types, vector_default_construct_test, VectorValueTypes);
INSTANTIATE_TYPED_TEST_CASE_P(vector_pointer_types, vector_default_construct_test, VectorPointerTypes);

/*

  Tests for explicit vector(size_type n)

*/
class vector_construct_with_size_test
    : public ::testing::TestWithParam<int> {

 public:
  vector_construct_with_size_test() {
    vec_size = GetParam();
    vec = new cppbench::containers::vector<int>(vec_size);
  }

  ~vector_construct_with_size_test() {
    delete vec;
    vec = nullptr;
  }

  int vec_size;
  cppbench::containers::vector<int>* vec;
};

TEST_P(vector_construct_with_size_test, vector_size_ctor) {
  EXPECT_EQ(vec_size, vec->size());
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_construct_with_size_test,
    ::testing::Range(1, 10, 1));



/*

  Tests for vector(size_type n, value_type& v)

*/
class vector_construct_with_value_test
    : public ::testing::TestWithParam< ::testing::tuple<int, int> > {

 public:
  vector_construct_with_value_test() {
    vec_size = ::testing::get<0>(GetParam());
    vec_value = ::testing::get<1>(GetParam());
    vec = new cppbench::containers::vector<int>(vec_size, vec_value);
  }

  ~vector_construct_with_value_test() {
    delete vec;
    vec = nullptr;
  }

  int vec_size;
  int vec_value;
  cppbench::containers::vector<int>* vec;
};

TEST_P(vector_construct_with_value_test, size_and_def_val_ctor) {
  EXPECT_EQ(vec_size, vec->size());
  EXPECT_TRUE(vec->begin() != vec->end());
  EXPECT_PRED2([] (auto vec, auto val) {
      return std::all_of(
          (*vec)->begin(),
          (*vec)->end(),
          [val] (auto elem) { return elem == val; });
    }, &vec, vec_value);
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_construct_with_value_test,
    ::testing::Combine(
         ::testing::Range(1, 10, 1),
         ::testing::Values(10)));

/*
  TESTS FOR COPY CONSTRUCTION
 */

class vector_copy_construct_test
    : public vector_construct_with_value_test {
};

TEST_P(vector_copy_construct_test, vector_copy_ctor) {
  auto vec_copy(*vec);

  EXPECT_EQ(vec_size, vec_copy.size());
  EXPECT_EQ(vec_copy.size(), vec->size());
  EXPECT_NE(vec_copy.begin(), vec->begin());
  EXPECT_NE(vec_copy.end(), vec->end());
  EXPECT_PRED2([] (auto lhs, auto rhs) {
      return std::equal(lhs.begin(), lhs.end(), (*rhs)->begin());
    }, vec_copy, &vec);
}

TEST_P(vector_copy_construct_test, vector_copy_assigment) {
  auto vec_copy = *vec;

  EXPECT_EQ(vec_size, vec_copy.size());
  EXPECT_EQ(vec_copy.size(), vec->size());
  EXPECT_NE(vec_copy.begin(), vec->begin());
  EXPECT_NE(vec_copy.end(), vec->end());
  EXPECT_PRED2([] (auto lhs, auto rhs) {
      return std::equal(lhs.begin(), lhs.end(), (*rhs)->begin());
    }, vec_copy, &vec);
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_copy_construct_test,
    ::testing::Combine(
         ::testing::Range(1, 3, 1),
         ::testing::Values(10)));


/*
  TESTS FOR COPY CONSTRUCTION
 */

class vector_move_construct_test
    : public vector_construct_with_value_test {
};

TEST_P(vector_move_construct_test, vector_move_ctor) {
  auto vec_moved_to(std::move(*vec));

  EXPECT_EQ(vec_size, vec_moved_to.size());
  EXPECT_EQ(0, vec->size());
  EXPECT_NE(vec_moved_to.size(), vec->size());

  EXPECT_NE(vec_moved_to.begin(), vec->begin());
  EXPECT_NE(vec_moved_to.end(), vec->end());
  EXPECT_EQ(nullptr, vec->begin());
  EXPECT_EQ(nullptr, vec->end());

  EXPECT_PRED2([] (auto vec, auto val) {
      return std::all_of(
          vec.begin(),
          vec.end(),
          [val] (auto elem) { return elem == val; });
    }, vec_moved_to, vec_value);
}

TEST_P(vector_move_construct_test, vector_move_assigment) {
  auto vec_moved_to = std::move(*vec);

  EXPECT_EQ(vec_size, vec_moved_to.size());
  EXPECT_EQ(0, vec->size());
  EXPECT_NE(vec_moved_to.size(), vec->size());

  EXPECT_NE(vec_moved_to.begin(), vec->begin());
  EXPECT_NE(vec_moved_to.end(), vec->end());
  EXPECT_EQ(nullptr, vec->begin());
  EXPECT_EQ(nullptr, vec->end());

  EXPECT_PRED2([] (auto vec, auto val) {
      return std::all_of(
          vec.begin(),
          vec.end(),
          [val] (auto elem) { return elem == val; });
    }, vec_moved_to, vec_value);
}

TEST_P(vector_move_construct_test, vector_move_with_swap_by_adl) {
  using std::swap;

  cppbench::containers::vector<int> vc {3, vec_value};
  swap(vc, *vec);

  EXPECT_EQ(3, vec->size());
  EXPECT_EQ(vec_size, vc.size());

  EXPECT_PRED2([] (auto lhs, auto rhs) {
      return std::equal(lhs.begin(), lhs.end(), (*rhs)->begin());
    }, vc, &vec);
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_move_construct_test,
    ::testing::Combine(
         ::testing::Range(1, 3, 1),
         ::testing::Values(10)));
