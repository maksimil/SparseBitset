#include "basic.hpp"
#include "impls/set_bitset.hpp"
#include "impls/unordered_set_bitset.hpp"
#include "timer.hpp"
#include <bitset>
#include <iostream>
#include <random>
#include <vector>

#define SET_TRIES 1000
#define SETS_PER_TRY 100
#define RANDOM_POOL_SIZE 1000

static const char *COLOR_GREEN = "\x1b[32m";
static const char *COLOR_BLUE = "\x1b[34m";
static const char *COLOR_UNSET = "\x1b[0m";

class RandomPool {
private:
  std::vector<Index> data;

public:
  RandomPool(Index dimension) : data(RANDOM_POOL_SIZE) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<Index> distribution(0, dimension - 1);

    for (Index k = 0; k < RANDOM_POOL_SIZE; k++) {
      data[k] = distribution(engine);
    }
  }

  Index get(Index k) const { return this->data[k % RANDOM_POOL_SIZE]; }
};

template <class SparseBitset> void try_implementation() {
  // The universe has 2000 numbers
  Index dimension = 2000;

  // Set INSERT_PER_TRY values
  {
    std::cout << COLOR_GREEN << "Setting " << SETS_PER_TRY << " elements"
              << COLOR_UNSET << "\n";

    Benchmark insertion_benchmark;

    for (Index try_count = 0; try_count < SET_TRIES; try_count++) {
      SparseBitset bit_set(dimension);
      RandomPool pool(dimension);

      insertion_benchmark.start();
      for (Index k = 0; k < SETS_PER_TRY; k++) {
        bit_set.set(pool.get(k));
      }
      insertion_benchmark.end();
    }

    std::cout << "Average time: " << insertion_benchmark.average() << "mcs\n";
    std::cout << "Average time per element: "
              << (insertion_benchmark.average() / SETS_PER_TRY) << "mcs\n";
  }
}

#define TEST_IMPLEMENTATION(impl)                                              \
  std::cout << COLOR_BLUE << "TESTING " << #impl << COLOR_UNSET << "\n";       \
  try_implementation<impl>();                                                  \
  std::cout << "\n";

int main(int argc, const char *argv[]) {
  TEST_IMPLEMENTATION(UnorderedSetBitset);
  TEST_IMPLEMENTATION(SetBitset);
}
