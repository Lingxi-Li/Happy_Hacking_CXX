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
  std::vector<std::intptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap(range.begin(), range.end());
  std::intptr_t key = 5;
  while (heap.size()) {
    EXPECT_EQ(--key, heap.top());
    EXPECT_EQ(key, heap.pop());
  }
}

TEST(range_push, basic) {
  using hhxx::mutable_heap;
  std::vector<std::intptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap;
  for (auto key : range) {
    heap.push(key);
  }
  std::intptr_t key = 5;
  while (heap.size()) {
    EXPECT_EQ(--key, heap.top());
    EXPECT_EQ(key, heap.pop());
  }
}

TEST(range_emplace, basic) {
  using hhxx::mutable_heap;
  std::vector<std::intptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap;
  for (auto key : range) {
    heap.emplace(key);
  }
  std::intptr_t key = 5;
  while (heap.size()) {
    EXPECT_EQ(--key, heap.top());
    EXPECT_EQ(key, heap.pop());
  }
}

TEST(range_clear, basic) {
  using hhxx::mutable_heap;
  std::vector<std::intptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap(range.begin(), range.end());
  EXPECT_EQ(5u, heap.size());
  heap.clear();
  EXPECT_EQ(0u, heap.size());
  EXPECT_TRUE(heap.empty());
}

TEST(range_reserve, basic) {
  using hhxx::mutable_heap;
  std::vector<std::intptr_t> range = {0, 1, 4, 2, 3};
  mutable_heap<> heap;
  for (auto key : range) {
    heap.emplace(key);
  }
  heap.reserve(100);
  std::intptr_t key = 5;
  while (heap.size()) {
    EXPECT_EQ(--key, heap.top());
    EXPECT_EQ(key, heap.pop());
  }
}
