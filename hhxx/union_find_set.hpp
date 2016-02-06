// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_UNION_FIND_SET_HPP_
#define HHXX_UNION_FIND_SET_HPP_

#include <cstddef>
#include <unordered_map>
#include <utility>

namespace hhxx {

/// Disjoint sets data structure.
/// Elements and sets are referenced by keys of type `std::uintptr_t`.
/// In the initial state, each element `x` within `[0, UINTPTR_MAX]` is in a set
/// of its own referenced by the same key `x`.
class union_find_set {
  struct Node {
    Node(std::uintptr_t iparent)
        : parent(iparent), size(1) {
      // nop
    }
    std::uintptr_t parent;
    std::size_t size;
  };

public:
  /// Type of keys used to reference elements and sets.
  using key_type = std::uintptr_t;

  /// Returns the largest set containing `key`.
  key_type find(key_type key) {
    return find_pair_it(key)->first;
  }

  /// Merges the largest sets containing `a` and `b` respectively, and returns
  /// the resulting union set.
  key_type unite(key_type a, key_type b) {
    auto pair_it_a = find_pair_it(a);
    auto pair_it_b = find_pair_it(b);
    if (pair_it_a == pair_it_b) return pair_it_a->first;
    if (pair_it_a->second.size < pair_it_b->second.size) {
      swap(pair_it_a, pair_it_b);
    }
    pair_it_a->second.size += pair_it_b->second.size;
    pair_it_b->second.parent = pair_it_a->first;
    return pair_it_a->first;
  }

  /// Resets to initial state where each element is in a set of its own
  /// referenced by the same key.
  void reset() {
    parent_.clear();
  }

private:
  std::unordered_map<key_type, Node>::iterator find_pair_it(key_type key) {
    auto pr = parent_.emplace(key, key);
    if (pr.second) return pr.first;
    auto it = pr.first;
    while (it->first != it->second.parent) {
      it = parent_.find(it->second.parent);
    }
    if (it == pr.first) return it;
    const auto root = it->first;
    swap(it, pr.first);
    while (it->second.parent != root) {
      auto parent_key = std::exchange(it->second.parent, root);
      it = parent_.find(parent_key);
    }
    return pr.first;
  }

  std::unordered_map<key_type, Node> parent_;
};

} // namespace hhxx

#endif // HHXX_UNION_FIND_SET_HPP_
