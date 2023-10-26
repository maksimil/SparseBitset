#include "auxillary/empty.hpp"
#include "auxillary/static_bitset.hpp"
#include "impls/partitioned_bitset.hpp"
#include "impls/set_bitset.hpp"
#include "impls/unordered_set_bitset.hpp"
#include "impls/vector_bitset.hpp"
#include "testing.hpp"
#include <cstdint>
#include <map>

int main(int argc, const char *argv[]) {
  TEST_IMPLEMENTATION(EmptyBitset);

  TEST_IMPLEMENTATION(UnorderedSetBitset);
  TEST_IMPLEMENTATION(PartitionedBitset<2 COMMA UnorderedSetBitset>);
  TEST_IMPLEMENTATION(PartitionedBitset<4 COMMA UnorderedSetBitset>);
  TEST_IMPLEMENTATION(PartitionedBitset<16 COMMA UnorderedSetBitset>);

  TEST_IMPLEMENTATION(SetBitset);
  TEST_IMPLEMENTATION(PartitionedBitset<2 COMMA SetBitset>);
  TEST_IMPLEMENTATION(PartitionedBitset<4 COMMA SetBitset>);
  TEST_IMPLEMENTATION(PartitionedBitset<16 COMMA SetBitset>);

  TEST_IMPLEMENTATION(VectorBitset);
}
