// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_MUTABLE_HEAP_HPP_
#define HHXX_MUTABLE_HEAP_HPP_

#include <cassert>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

namespace hhxx {

/// Binary max-heap with mutable priorities. `Less` is the less-than comparator
/// type that compares the priorities of objects referenced by key type
/// `std::intptr_t`.
template <class Less = std::less<std::intptr_t>>
class mutable_heap {
public:
  using key_type = std::intptr_t;
  using pos_type = std::size_t;
  using map_type = std::unordered_map<key_type, pos_type>;
  using vec_type = std::vector<key_type>;

  /// Constructs a mutable heap using `less` as the less-than comparator.
  explicit mutable_heap(Less less = Less{})
      : less_(std::move(less)) {
    // nop
  }

  /// Constructs a mutable heap over the objects referenced by keys
  /// `[first, last)` using `less` as the less-than comparator.
  template <class ForwardIt>
  mutable_heap(ForwardIt first, ForwardIt last, Less less = Less{})
      : less_(std::move(less)),
        heap_(first, last) {
    std::make_heap(heap_.begin(), heap_.end(), less_);
    for (pos_type i = 0; i < heap_.size(); ++i) {
      key_pos_map_.emplace(heap_[i], i);
    }
  }

  /// Returns root of the heap.
  key_type top() const {
    assert(! empty());
    return heap_.front();
  }

  /// Takes and returns root of the heap.
  key_type pop() {
    assert(! empty());
    auto key = top();
    heap_.front() = heap_.back();
    auto& key_pos = key_pos_map_[heap_.front()] = 0;
    key_pos_map_.erase(key);
    heap_.pop_back();
    sift_down(heap_.begin(), heap_.end(), key_pos);
    return key;
  }

  /// Add the object referenced by `key` to the heap. If it's already in the
  /// heap, its position in the heap is updated if necessary.
  void push(key_type key) {
    auto pr = key_pos_map_.emplace(key, heap_.size());
    if (pr.second) {
      heap_.emplace_back(key);
      sift_up(heap_.begin(), heap_.end(), pr.first->second);
      return;
    }
    auto it = heap_.begin() + pr.first->second;
    if (sift_up(heap_.begin(), it + 1, pr.first->second)) return;
    sift_down(it, heap_.end(), pr.first->second);
    return;
  }

  /// Same as `push()`.
  void emplace(key_type key) {
    push(key);
  }

  /// Empties the heap.
  void clear() {
    heap_.clear();
    key_pos_map_.clear();
  }

  /// Returns the number of elements in the heap.
  auto size() const {
    return heap_.size();
  }

  /// Returns whether the heap is empty.
  bool empty() const {
    return heap_.empty();
  }

  /// Reserves storage for `cap` elements.
  void reserve(pos_type cap) {
    heap_.reserve(cap);
    key_pos_map_.reserve(cap);
  }

private:
  bool sift_up(vec_type::iterator first, vec_type::iterator last,
               pos_type& key_pos) {
    auto n = static_cast<pos_type>(last - first);
    if (n < 2) return false;
    auto parent = n / 2 - 1;
    if (! less_(first[parent], last[-1])) return false;
    auto key = std::exchange(last[-1], first[parent]);
    key_pos_map_[last[-1]] = static_cast<pos_type>(last - first - 1);
    while (true) {
      last = first + parent + 1;
      n = static_cast<pos_type>(last - first);
      if (n < 2) break;
      parent = n / 2 - 1;
      if (! less_(first[parent], key)) break;
      last[-1] = first[parent];
      key_pos_map_[last[-1]] = static_cast<pos_type>(last - first - 1);
    }
    last[-1] = key;
    key_pos = static_cast<pos_type>(last - first - 1);
    return true;
  }

  bool sift_down(vec_type::iterator first, vec_type::iterator last,
                 pos_type& key_pos) {
    auto first_pos = static_cast<pos_type>(first - heap_.begin());
    auto last_pos = static_cast<pos_type>(last - heap_.begin());
    auto child_pos = 2 * first_pos + 1;
    if (! (child_pos < last_pos)) return false;
    if (child_pos + 1 < last_pos
        && less_(heap_[child_pos], heap_[child_pos + 1])) {
      ++child_pos;
    }
    if (! less_(heap_[first_pos], heap_[child_pos])) return false;
    auto key = std::exchange(heap_[first_pos], heap_[child_pos]);
    key_pos_map_[heap_[first_pos]] = first_pos;
    while (true) {
      first_pos = child_pos;
      child_pos = first_pos * 2 + 1;
      if (! (child_pos < last_pos)) break;
      if (child_pos + 1 < last_pos
          && less_(heap_[child_pos], heap_[child_pos + 1])) {
        ++child_pos;
      }
      if (! less_(heap_[first_pos], heap_[child_pos])) break;
      heap_[first_pos] = heap_[child_pos];
      key_pos_map_[heap_[first_pos]] = first_pos;
    }
    heap_[first_pos] = key;
    key_pos = first_pos;
    return true;
  }

  Less less_;
  vec_type heap_;
  map_type key_pos_map_;
};

} // namespace hhxx

#endif // HHXX_MUTABLE_HEAP_HPP_
