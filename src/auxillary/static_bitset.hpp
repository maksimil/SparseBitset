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

template <Index BLOCKS, class WordType> class StaticBitset {
private:
  std::array<WordType, BLOCKS> data = {};
  Index set_bits = 0;

public:
  static constexpr Index word_size = 8 * sizeof(WordType);
  static constexpr Index capacity = word_size * BLOCKS;

  StaticBitset() {}

  StaticBitset(Index _dimension) {}

  Index size() const { return this->set_bits; }

  bool get(Index index) const {
    assert(index >= 0 && index < capacity);
    Index block_index = index / word_size;
    Index inner_index = index % word_size;
    WordType setword = WordType(1) << inner_index;

    return (this->data[block_index] & setword) == setword;
  }

  void set(Index index) {
    assert(index >= 0 && index < capacity);
    Index block_index = index / word_size;
    Index inner_index = index % word_size;
    WordType setword = WordType(1) << inner_index;

    this->set_bits += (this->data[block_index] & setword) == 0;
    this->data[block_index] |= setword;
  }

  void unset(Index index) {
    assert(index >= 0 && index < word_size * BLOCKS);
    Index block_index = index / word_size;
    Index inner_index = index % word_size;
    WordType setword = WordType(1) << inner_index;

    this->set_bits -= (this->data[block_index] & setword) == setword;
    this->data[block_index] &= ~setword;
  }

  class Iterator {
  private:
    const StaticBitset<BLOCKS, WordType> &bitset;
    Index index;

    void move_to_next() {
      while (this->index < capacity && !this->bitset.get(this->index)) {
        this->index++;
      }
    }

  public:
    void move_end() { this->index = word_size * BLOCKS; }

    Iterator(const StaticBitset<BLOCKS, WordType> &bitset) : bitset(bitset) {
      this->index = 0;
      this->move_to_next();
    }

    const Index &operator*() const { return this->index; }

    Iterator &operator++() {
      this->index++;
      this->move_to_next();
      return *this;
    }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) {
      return lhs.index != rhs.index;
    }
  };

  using const_iterator = Iterator;

  const_iterator begin() const { return Iterator(*this); }

  const_iterator end() const {
    Iterator iter = Iterator(*this);
    iter.move_end();
    return iter;
  }

  std::ostream &print(std::ostream &out) const {
    out << "[ ";
    for (const WordType &b : this->data) {
      out << +b << " ";
    }
    out << "]:" << this->set_bits;
    return out;
  }
};

template <Index BLOCKS, class WordType>
std::ostream &operator<<(std::ostream &out,
                         const StaticBitset<BLOCKS, WordType> &v) {
  return v.print(out);
}
