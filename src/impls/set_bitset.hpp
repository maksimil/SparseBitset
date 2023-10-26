#pragma once

#include "../basic.hpp"
#include <set>

class SetBitset {
private:
  std::set<Index> data;

public:
  SetBitset(Index _dimension) {}
  SetBitset() {}

  void set(Index index) { this->data.insert(index); }
  void unset(Index index) { this->data.erase(index); }

  Index size() const { return this->data.size(); }

  using const_iterator = std::set<Index>::const_iterator;

  const_iterator begin() const { return this->data.begin(); }
  const_iterator end() const { return this->data.end(); }
};
