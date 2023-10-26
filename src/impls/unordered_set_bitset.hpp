#pragma once

#include "../basic.hpp"
#include <unordered_set>

class UnorderedSetBitset {
private:
  std::unordered_set<Index> data;

public:
  UnorderedSetBitset(Index _dimension) {}
  UnorderedSetBitset() {}

  void set(Index index) { this->data.insert(index); }
  void unset(Index index) { this->data.erase(index); }

  Index size() const { return this->data.size(); }

  using const_iterator = std::unordered_set<Index>::const_iterator;

  const_iterator begin() const { return this->data.begin(); }
  const_iterator end() const { return this->data.end(); }

  bool operator==(const UnorderedSetBitset &lhs) const {
    return this->data == lhs.data;
  }
};
