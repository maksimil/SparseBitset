#pragma once

#include "../auxillary/static_bitset.hpp"
#include "../basic.hpp"
#include <cassert>
#include <cstdint>
#include <ostream>
#include <vector>

class VectorBitset {
private:
  using Segment = StaticBitset<WordSize>;
  std::vector<Segment> segments;
  Index set_bits = 0;

public:
  class Iterator {
  private:
    const VectorBitset &bitset;
    Index segment_index;
    Index inner_index;

    void move_to_next() {
      this->inner_index =
          this->bitset.segments[segment_index].move_to_next(this->inner_index);
      while (this->inner_index == Segment::capacity) {
        this->inner_index = 0;
        this->segment_index++;
        if (this->segment_index == this->bitset.segments.size()) {
          return;
        }
        this->inner_index = this->bitset.segments[segment_index].move_to_next(
            this->inner_index);
      }
    }

  public:
    Iterator(const VectorBitset &bitset) : bitset(bitset) {
      this->segment_index = 0;
      this->inner_index = 0;
      if (!bitset.segments.empty()) {
        this->move_to_next();
      }
    }

    void move_end() {
      this->inner_index = 0;
      this->segment_index = this->bitset.segments.size();
    }

    Index operator*() const {
      return this->inner_index + this->segment_index * Segment::capacity;
    }

    Iterator &operator++() {
      this->inner_index++;
      this->move_to_next();
      return *this;
    }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) {
      return lhs.segment_index != rhs.segment_index ||
             lhs.inner_index != rhs.inner_index;
    }
  };
  friend class Iterator;
  using const_iterator = Iterator;

  VectorBitset(Index dimension) : segments(dimension / Segment::capacity + 1) {}
  VectorBitset() : segments() {}

  const_iterator begin() const { return Iterator(*this); }

  const_iterator end() const {
    const_iterator it = this->begin();
    it.move_end();
    return it;
  }

  Index size() const { return this->set_bits; }

  bool empty() const { return this->set_bits == 0; }

  void set(Index index) {
    Index segment_index = index / Segment::capacity;
    Index inner_index = index % Segment::capacity;

    this->set_bits += this->segments[segment_index].set(inner_index);
  }

  void unset(Index index) {
    Index segment_index = index / Segment::capacity;
    Index inner_index = index % Segment::capacity;

    this->set_bits -= this->segments[segment_index].unset(inner_index);
  }

  friend std::ostream &operator<<(std::ostream &out, const VectorBitset &v) {
    out << "[ ";
    for (const Index &e : v) {
      out << e << " ";
    }
    out << "]";
    return out;
  }
};
