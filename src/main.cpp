#include "auxillary/static_bitset.hpp"
#include "impls/set_bitset.hpp"
#include "impls/unordered_set_bitset.hpp"
#include "testing.hpp"
#include <cstdint>

int main(int argc, const char *argv[]) {
  TEST_IMPLEMENTATION(UnorderedSetBitset);
  TEST_IMPLEMENTATION(SetBitset);
  TEST_IMPLEMENTATION(StaticBitset<256 COMMA Word8>);
  TEST_IMPLEMENTATION(StaticBitset<128 COMMA Word16>);
  TEST_IMPLEMENTATION(StaticBitset<64 COMMA Word32>);
  TEST_IMPLEMENTATION(StaticBitset<32 COMMA Word64>);
}
