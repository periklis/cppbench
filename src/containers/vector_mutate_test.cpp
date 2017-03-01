#include <random>
#include "gtest/gtest.h"
#include "vector.hpp"

class vector_mutate_test
    : public ::testing::TestWithParam< ::testing::tuple<int, int> > {

 public:
  vector_mutate_test() {
    vec_size = ::testing::get<0>(GetParam());
    vec_value = ::testing::get<1>(GetParam());
    vec = new cppbench::containers::vector<int>(vec_size, vec_value);
    // std::generate_n(vec->begin(), vec_size, std::rand);
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

TEST_P(vector_mutate_test, vector_insert_at_pos_copy_lvalue) {
  auto new_pos = vec_size > 2 ? 1 : 0;
  auto new_val = vec_value + 1;
  auto iter_new_val = vec->insert(new_pos, new_val);

  EXPECT_EQ(vec_size + 1, vec->size());
  EXPECT_EQ(new_val, (*vec)[new_pos]);
  EXPECT_EQ(new_val, *iter_new_val);
}

TEST_P(vector_mutate_test, vector_insert_at_pos_rvalue) {
  auto new_pos = vec_size > 2 ? 1 : 0;
  auto new_val = vec_value + 1;
  auto iter_new_val = vec->insert(new_pos, std::move(new_val));

  EXPECT_EQ(vec_size + 1, vec->size());
  EXPECT_EQ(new_val, (*vec)[new_pos]);
  EXPECT_EQ(new_val, *iter_new_val);
}

TEST_P(vector_mutate_test, vector_insert_n_times_at_pos_lvalue) {
  auto new_n = 3;
  auto new_start_pos = vec_size > 2 ? 1 : 0;
  auto new_end_pos = new_start_pos + new_n - 1;
  auto new_val = vec_value + 1;

  vec->insert(new_start_pos, new_n, std::move(new_val));

  EXPECT_EQ(vec_size + new_n, vec->size());
  EXPECT_PRED4([] (auto vec, auto start_pos, auto end_pos, auto new_val) {
      return std::all_of(
          (*vec)->begin() + start_pos,
          (*vec)->begin() + end_pos,
          [new_val] (auto elem) { return elem == new_val; });
    }, &vec, new_start_pos, new_end_pos,  new_val);
}

TEST_P(vector_mutate_test, vector_insert_by_iters) {
  auto list = {1,2,3,4};
  auto new_n = list.size();
  auto new_start_pos = vec_size > 2 ? 1 : 0;
  auto new_end_pos = new_start_pos + new_n;

  vec->insert(new_start_pos, list.begin(), list.end());

  EXPECT_EQ(vec_size + new_n, vec->size());
  EXPECT_PRED3([&list] (auto vec, auto start_pos, auto end_pos) {
      return std::equal((*vec)->begin() + start_pos, (*vec)->begin() + end_pos,
                        list.begin(), list.end());
    }, &vec, new_start_pos, new_end_pos);
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

TEST_P(vector_mutate_test, vector_resize_bigger_size) {
  auto new_size = vec_size + 1;
  vec->resize(new_size);

  EXPECT_EQ(new_size, vec->size());

  EXPECT_PRED3([] (auto vec, auto old_size, auto val) {
      return std::all_of(
          (*vec)->begin(),
          (*vec)->begin() + old_size,
          [val] (auto elem) { return elem == val; });
    }, &vec, vec_size, vec_value);

  EXPECT_EQ(0, (*vec)[vec_size]);
}

TEST_P(vector_mutate_test, vector_resize_lesser_size) {
  auto new_size = vec_size > 1 ? vec_size - 1 : 1;
  vec->resize(new_size);

  EXPECT_EQ(new_size, vec->size());

  EXPECT_PRED2([] (auto vec, auto val) {
      return std::all_of(
          (*vec)->begin(),
          (*vec)->end(),
          [val] (auto elem) { return elem == val; });
    }, &vec, vec_value);
}

TEST_P(vector_mutate_test, vector_shrink_to_fit) {
  vec->shrink_to_fit();
  EXPECT_EQ(vec->size(), vec->capacity());
  EXPECT_EQ(vec_size, vec->size());
}

INSTANTIATE_TEST_CASE_P(
    vector,
    vector_mutate_test,
    ::testing::Combine(
         ::testing::Range(1, 10, 1),
         ::testing::Values(10)));
