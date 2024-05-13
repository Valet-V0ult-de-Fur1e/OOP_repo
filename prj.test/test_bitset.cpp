#include <bitset/bitset.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("bitset init") {
	BitSet testBitset = BitSet();
}


TEST_CASE("bitset resize") {
	BitSet testBitset = BitSet();
}

TEST_CASE("bitset fill") {
	BitSet testBitset = BitSet();
}

TEST_CASE("bitset and") {
	BitSet firstBitset = BitSet();
	firstBitset.Resize(10);
	BitSet secondBitset = BitSet();
	secondBitset.Resize(10);
}

TEST_CASE("bitset or") {
	BitSet firstBitset = BitSet();
	firstBitset.Resize(10);
	BitSet secondBitset = BitSet();
	secondBitset.Resize(10);
}

TEST_CASE("bitset not") {
	BitSet testBitset = BitSet();
	testBitset.Resize(10);
}

TEST_CASE("bitset xor") {
	BitSet firstBitset = BitSet();
	firstBitset.Resize(10);
	BitSet secondBitset = BitSet();
	secondBitset.Resize(10);
}

TEST_CASE("bia init") {
	BitSet testBitset = BitSet();
	testBitset.Resize(10);
	testBitset.Set(0, 1);
	std::cout << bool(testBitset[0]);
	std::cout << bool(testBitset[1]);

}

TEST_CASE("bia change value") {
	BitSet testBitset = BitSet();
	testBitset.Resize(10);
	testBitset[0] = 1;
	std::cout << bool(testBitset[0]);
	testBitset[1] = 1;
	std::cout << bool(testBitset[1]);
}