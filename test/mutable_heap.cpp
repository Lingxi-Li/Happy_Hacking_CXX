// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#include <hhxx/mutable_heap.hpp>

#include <cstddef>
#include <vector>

#include <gtest/gtest.h>

TEST(default_ctor, basic) {
  using hhxx::mutable_heap;
  mutable_heap<> heap;
  EXPECT_EQ(0u, heap.size());
  EXPECT_TRUE(heap.empty());
}

TEST(range_ctor_top_pop, basic) {
  using hhxx::mutable_heap;
  std::vector<std::uintptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap(range.begin(), range.end());
  std::uintptr_t key = 5;
  while (heap.size()) {
    EXPECT_EQ(--key, heap.top());
    EXPECT_EQ(key, heap.pop());
  }
}

TEST(push, basic) {
  using hhxx::mutable_heap;
  std::vector<std::uintptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap;
  for (auto key : range) {
    heap.push(key);
  }
  std::uintptr_t key = 5;
  while (heap.size()) {
    EXPECT_EQ(--key, heap.top());
    EXPECT_EQ(key, heap.pop());
  }
}

namespace mutable_heap_test_ns {

struct less {
  explicit less(std::vector<int>& ipri)
      : pri(ipri) {
    // nop
  }
  bool operator()(std::uintptr_t a, std::uintptr_t b) const {
    return pri[a] < pri[b];
  }
  std::vector<int>& pri;
};

} // namespace mutable_heap_test_ns

TEST(list_ctor_push, update) {
  using hhxx::mutable_heap;
  using mutable_heap_test_ns::less;
  std::vector<int> priorities = {0, 1, 2, 3, 4};
  mutable_heap<less> heap({0, 1, 2, 3, 4}, less(priorities));
  priorities.assign({4, 3, 2, 1, 0});
  for (auto key : {0, 1, 2, 3, 4}) {
    heap.push(key);
  }
  std::uintptr_t key = 0;
  while (heap.size()) {
    EXPECT_EQ(key, heap.top());
    EXPECT_EQ(key, heap.pop());
    ++key;
  }
}

TEST(emplace, basic) {
  using hhxx::mutable_heap;
  std::vector<std::uintptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap;
  for (auto key : range) {
    heap.emplace(key);
  }
  std::uintptr_t key = 5;
  while (heap.size()) {
    EXPECT_EQ(--key, heap.top());
    EXPECT_EQ(key, heap.pop());
  }
}

TEST(clear, basic) {
  using hhxx::mutable_heap;
  std::vector<std::uintptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap(range.begin(), range.end());
  EXPECT_EQ(5u, heap.size());
  heap.clear();
  EXPECT_EQ(0u, heap.size());
  EXPECT_TRUE(heap.empty());
}

TEST(reserve, basic) {
  using hhxx::mutable_heap;
  std::vector<std::uintptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap;
  for (auto key : range) {
    heap.emplace(key);
  }
  heap.reserve(100);
  std::uintptr_t key = 5;
  while (heap.size()) {
    EXPECT_EQ(--key, heap.top());
    EXPECT_EQ(key, heap.pop());
  }
}
