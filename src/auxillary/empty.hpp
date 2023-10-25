#pragma once

#include "../basic.hpp"

static Index dummy_ptr = 0;

class EmptyBitset {
public:
  EmptyBitset(Index _dimension) {}

  void set(Index index) {}
  void unset(Index index) {}

  Index size() const { return 0; }

  using const_iterator = Index *;
  const_iterator begin() const { return &dummy_ptr; }
  const_iterator end() const { return &dummy_ptr; }
};
