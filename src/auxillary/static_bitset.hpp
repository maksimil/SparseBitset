#pragma once

#include "../basic.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <ostream>

using Word8 = std::uint8_t;
using Word16 = std::uint16_t;
using Word32 = std::uint32_t;
using Word64 = std::uint64_t;
using WordSize = std::uintptr_t;

template <class WordType> class StaticBitset {
private:
  WordType data = {};

public:
  static constexpr Index capacity = 8 * sizeof(WordType);

  StaticBitset() {}

  bool get(Index index) const {
    assert(index >= 0 && index < capacity);
    WordType setword = WordType(1) << index;

    return (this->data & setword) == setword;
  }

  bool set(Index index) {
    assert(index >= 0 && index < capacity);
    WordType setword = WordType(1) << index;

    bool did_set = (this->data & setword) == 0;
    this->data |= setword;

    return did_set;
  }

  bool unset(Index index) {
    assert(index >= 0 && index < capacity);
    WordType setword = WordType(1) << index;

    bool did_unset = (this->data & setword) == setword;
    this->data &= ~setword;

    return did_unset;
  }

  Index move_to_next(Index from) const {
    while (from < capacity && !this->get(from)) {
      from++;
    }
    return from;
  }

  friend std::ostream &operator<<(std::ostream &out,
                                  const StaticBitset<WordType> &v) {
    out << "[ " << (+v.data) << " ]";
    return out;
  }
};
