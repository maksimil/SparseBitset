#pragma once

#include "../basic.hpp"
#include <array>
#include <iostream>

template <Index PARTITIONS, class Bitset> class PartitionedBitset {
private:
  std::array<Bitset, PARTITIONS> partitions;

public:
  class Iterator {
  private:
    const PartitionedBitset<PARTITIONS, Bitset> &bitset;
    Index partition_index;
    typename Bitset::const_iterator partition_iterator;

    void move_to_valid() {
      while (!(this->partition_iterator !=
               this->bitset.partitions[this->partition_index].end())) {
        this->partition_index++;
        if (this->partition_index == PARTITIONS) {
          return;
        }
        this->partition_iterator =
            this->bitset.partitions[this->partition_index].begin();
      }
    }

  public:
    Iterator(const PartitionedBitset<PARTITIONS, Bitset> &bitset)
        : bitset(bitset) {
      this->partition_index = 0;
      this->partition_iterator = this->bitset.partitions[0].begin();
      this->move_to_valid();
    }

    void move_to_end() {
      this->partition_index = PARTITIONS;
      this->partition_iterator = this->bitset.partitions[PARTITIONS - 1].end();
    }

    Index operator*() const {
      return (*this->partition_iterator) * PARTITIONS + this->partition_index;
    }

    Iterator &operator++() {
      ++this->partition_iterator;
      this->move_to_valid();
      return *this;
    }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) {
      return lhs.partition_index != rhs.partition_index ||
             lhs.partition_iterator != rhs.partition_iterator;
    }
  };
  friend class Iterator;
  using const_iterator = Iterator;

  const_iterator begin() const { return Iterator(*this); }

  const_iterator end() const {
    const_iterator it = this->begin();
    it.move_to_end();
    return it;
  }

  PartitionedBitset(Index dimension) : partitions() {
    for (Index k = 0; k < PARTITIONS; k++) {
      this->partitions[k] = Bitset(dimension / PARTITIONS + 1);
    }
  }

  PartitionedBitset() : partitions() {}

  void set(Index index) {
    Index partition_index = index % PARTITIONS;
    Index inner_index = index / PARTITIONS;

    this->partitions[partition_index].set(inner_index);
  }

  void unset(Index index) {
    Index partition_index = index % PARTITIONS;
    Index inner_index = index / PARTITIONS;

    this->partitions[partition_index].unset(inner_index);
  }

  friend std::ostream &
  operator<<(std::ostream &out,
             const PartitionedBitset<PARTITIONS, Bitset> &v) {
    out << "[ ";
    for (const Index &e : v) {
      out << e << " ";
    }
    out << "]";
    return out;
  }
};
