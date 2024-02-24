# SparseBitSet

This repository contains code, tests and benchmarks for 
different implementations of sparse bitset --- a sparsely populated bitset
(a sparsely populated subset of natural numbers).
An example implementation using `std::set` can 
be found in `src/impls/set_bitset.hpp`.

All the other implementations are in `src/impls`.

The benchmarks include 
- Setting 100 elements
- Unsetting 50 elements
- Iterating through 100 elements
- An empty benchmark `EmptyBitset` which estimates
how much time does the timer itself take.

Implementations include
- An implementation using `std::set`
- An implementation using `std::unordered_set`
- An implementation using a regular static bitset
- An implementation using a vector of static bitsets
- Implementations which partition the set of values into several 
bitsets. For example `PartitionedBitset<2, SetBitset>` splits the values 
into two SetBitsets: one with even values and one with odd values.

## Run yourself

You can run the code yourself with

```sh
make config=release
./bin/Release/SparseBitset
```

`premake5` is used during development for makefile generation.
