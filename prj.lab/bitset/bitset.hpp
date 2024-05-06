#pragma once
#ifndef BITSET_BITSET_HPP
#define BITSET_BITSET_HPP

#include <cstddef>
#include <iostream>
#include <vector>

class BitSet {
public:
	class BitAccessor {
	public:
		BitAccessor() = delete;
		BitAccessor(BitSet& bst, const std::int32_t idx) noexcept : bst_(bst), idx_(idx) {}
		~BitAccessor() = default;
		BitAccessor(const BitAccessor&) = delete;
		BitAccessor(BitAccessor&&) noexcept = default;
		BitAccessor& operator=(const BitAccessor&) = delete;
		BitAccessor& operator=(BitAccessor&&) noexcept = default;
		BitAccessor& operator=(const bool v) { bst_.Set(idx_, v); return *this; }
		[[nodiscard]] operator bool() const { return bst_.Get(idx_); }
	private:
		BitSet& bst_;
		const std::int32_t idx_ = -1;
	};
public:

	BitSet() = default;
	BitSet(const BitSet&) = default;
	BitSet(BitSet&& rhs) noexcept;
	BitSet(const std::int32_t);

	BitSet& operator=(const BitSet&) = default;
	BitSet& operator=(BitSet&&) = default;
	
	~BitSet() = default;

	[[nodiscard]] bool operator==(const BitSet& rhs) const noexcept;

  	[[nodiscard]] bool operator!=(const BitSet& rhs) const noexcept;
	
	int32_t GetSize() const noexcept;
	
	[[nodiscard]] bool Get(const int32_t idx) const;

	void Set(const int32_t index, const bool val);

	void Resize(const int32_t size);
	
	void Fill(const bool val);

	[[nodiscard]] BitSet& operator&=(const BitSet& rhs);

	[[nodiscard]] BitSet& operator|=(const BitSet& rhs);

	[[nodiscard]] BitSet& operator^=(const BitSet& rhs);

	[[nodiscard]] BitSet operator~();

	BitAccessor operator[](const int32_t idx) { return {*this, idx}; }

	// std::ostream& WriteTxt(std::ostream&)
	// std::ostream& WriteBinary(std::ostream&)
	// std::istream& ReadTxt(std::istream&)
	// std::istream& RaadBinary(std::istream&)

private:

	int32_t size_ = 0;

	std::vector<uint32_t> bits_;

};

// std::ostream& operaror<<(std::ostream&, const BitSet&);
// std::istream& operaror>>(std::istream&, BitSet&);
[[nodiscard]] BitSet operator&(const BitSet& lhs, const BitSet& rhs);
[[nodiscard]] BitSet operator|(const BitSet& lhs, const BitSet& rhs);
[[nodiscard]] BitSet operator^(const BitSet& lhs, const BitSet& rhs);

#endif // !BITSET_BITSET_HPP