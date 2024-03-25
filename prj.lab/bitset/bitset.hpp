#pragma once
#ifndef BITSET_BITSET_HPP
#define BITSET_BITSET_HPP

#include <cstddef>
#include <iostream>
#include <vector>

class BitSet {
public:

	BitSet() = default;
	BitSet(const BitSet&) = default;
	BitSet(BitSet&& rhs) noexcept;

	BitSet& operator=(const BitSet&) = default;
	BitSet& operator=(BitSet&& rhs);
	
	~BitSet() = default;
	
	int32_t GetSize() const noexcept;
	
	bool Get(const int32_t index);

	void Set(const int32_t index, const bool new_value);

	void Resize(const int32_t new_size);
	
	void Fill(const bool value);

private:

	int32_t size_ = 0;

	std::vector<bool> data_{};

};

[[nodiscard]] BitSet operator&(const BitSet& lhs, const BitSet& rhs);
[[nodiscard]] BitSet operator|(const BitSet& lhs, const BitSet& rhs);
[[nodiscard]] BitSet operator~(const BitSet& rhs);
[[nodiscard]] BitSet operator^(const BitSet& lhs, const BitSet& rhs);

#endif // !BITSET_BITSET_HPP