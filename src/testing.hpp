#include "basic.hpp"
#include "impls/unordered_set_bitset.hpp"
#include "timer.hpp"
#include <iostream>
#include <random>
#include <vector>

#define SET_TRIES 1000
#define SETS_PER_TRY 100
#define RANDOM_POOL_SIZE 1000
#define DIMENSION 2000

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

using ComparisonImpl = UnorderedSetBitset;

template <class SparseBitset>
bool compare_implementation(const SparseBitset &bit_set,
                            const ComparisonImpl &compare_bit_set) {
  ComparisonImpl converted_bit_set(DIMENSION);
  for (const Index &e : bit_set) {
    converted_bit_set.set(e);
  }

  return compare_bit_set == converted_bit_set;
}

template <class SparseBitset> void test_set() {
  // Set INSERT_PER_TRY values
  std::cout << COLOR_GREEN << "Setting " << SETS_PER_TRY << " elements"
            << COLOR_UNSET << "\n";

  Benchmark insertion_benchmark;
  Index passed_tests = 0;

  for (Index try_count = 0; try_count < SET_TRIES; try_count++) {

    RandomPool pool(DIMENSION);

    // testing
    {
      SparseBitset bit_set(DIMENSION);
      ComparisonImpl comparison_bit_set(DIMENSION);
      for (Index k = 0; k < SETS_PER_TRY; k++) {
        bit_set.set(pool.get(k));
        comparison_bit_set.set(pool.get(k));
      }

      passed_tests += compare_implementation(bit_set, comparison_bit_set);
    }

    // benchmark
    {
      SparseBitset bit_set(DIMENSION);
      insertion_benchmark.start();
      for (Index k = 0; k < SETS_PER_TRY; k++) {
        bit_set.set(pool.get(k));
      }
      insertion_benchmark.end();
    }
  }

  std::cout << "Passed " << passed_tests << "/" << SET_TRIES << " tests\n";
  std::cout << "Average time: " << insertion_benchmark.average() << "mcs\n";
  std::cout << "Average time per element: "
            << (insertion_benchmark.average() / SETS_PER_TRY) << "mcs\n";
}

template <class SparseBitset> void test_implementation() {
  test_set<SparseBitset>();
}

#define TEST_IMPLEMENTATION(impl)                                              \
  std::cout << COLOR_BLUE << "TESTING " << #impl << COLOR_UNSET << "\n";       \
  test_implementation<impl>();                                                 \
  std::cout << "\n";
