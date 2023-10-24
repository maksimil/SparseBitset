#include "auxillary/static_bitset.hpp"
#include "impls/set_bitset.hpp"
#include "impls/unordered_set_bitset.hpp"
#include "testing.hpp"
#include <cstdint>

int main(int argc, const char *argv[]) {
  TEST_IMPLEMENTATION(UnorderedSetBitset);
  TEST_IMPLEMENTATION(SetBitset);
  // StaticBitset works quicker than timer starting and stopping
  // TEST_IMPLEMENTATION(StaticBitset<256 COMMA Word8>);
}
