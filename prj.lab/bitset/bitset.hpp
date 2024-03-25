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
	
	bool Get(const int32_t index) const;

	void Set(const int32_t index, const bool new_value);

	void Resize(const int32_t new_size);
	
	void Fill(const bool value);

	class BiA {
	public:
		BiA(BitSet& b, int32_t i) : b_(b), i_(i) {};
		~BiA() = default;
		explicit operator bool();
		void operator=(const bool rhs);
		void operator= (BiA& rhs);
	private:
		BitSet& b_;
		int32_t i_;
	};

	BiA operator[](const std::int32_t index);

private:

	int32_t size_ = 0;

	std::vector<bool> data_{};

};

[[nodiscard]] BitSet operator&(const BitSet& lhs, const BitSet& rhs);
[[nodiscard]] BitSet operator|(const BitSet& lhs, const BitSet& rhs);
[[nodiscard]] BitSet operator~(const BitSet& rhs);
[[nodiscard]] BitSet operator^(const BitSet& lhs, const BitSet& rhs);

#endif // !BITSET_BITSET_HPP