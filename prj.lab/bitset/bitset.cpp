#include "bitset.hpp"

BitSet::BitSet(BitSet&& rhs) noexcept : size_(rhs.size_), data_(rhs.data_) {
	rhs.size_ = 0;
	rhs.data_.clear();
}

BitSet& BitSet::operator=(BitSet&& rhs) {
	if (this != &rhs) {
		size_ = rhs.size_;
		data_ = rhs.data_;
		rhs.size_ = 0;
		rhs.data_.clear();
	}
	return *this;
}

int32_t BitSet::GetSize() const noexcept {
	return size_;
}

bool BitSet::Get(const int32_t index) {
	if (index > GetSize() - 1) {
		throw std::runtime_error("invalid index");
	}
	return data_[index];
}

void BitSet::Set(const int32_t index, const bool new_value) {
	if (index > GetSize() - 1) {
		throw std::runtime_error("invalid index");
	}
	data_[index] = new_value;
}

void BitSet::Resize(const int32_t new_size) {
	size_ = new_size;
	data_.resize(size_);
}

void BitSet::Fill(const bool value) {
	data_.resize(size_, value);
}

BitSet operator&(const BitSet& lhs, const BitSet& rhs)
{
	BitSet out;
	if (lhs.GetSize() != rhs.GetSize()) {
		throw std::logic_error("invalid size");
	}
	int32_t out_size = lhs.GetSize();
	out.Resize(lhs.GetSize());
	for (int index = 0; index < lhs.GetSize())
	return out;
}

BitSet operator|(const BitSet& lhs, const BitSet& rhs)
{
	BitSet out;
	return out;
}

BitSet operator~(const BitSet& rhs)
{
	BitSet out;
	return out;
}

BitSet operator^(const BitSet& lhs, const BitSet& rhs)
{
	BitSet out;
	return out;
}
