#include "bitset.hpp"

BitSet::BitSet(BitSet&& rhs) noexcept : size_(rhs.size_), bits_(rhs.bits_) {
	rhs.size_ = 0;
	rhs.bits_.clear();
}

BitSet& BitSet::operator=(BitSet&& rhs) {
	if (this != &rhs) {
		size_ = rhs.size_;
		bits_ = rhs.bits_;
		rhs.size_ = 0;
		rhs.bits_.clear();
	}
	return *this;
}

int32_t BitSet::GetSize() const noexcept {
	return size_;
}

bool BitSet::Get(const int32_t index) const {
	if (index > GetSize() - 1) {
		throw std::runtime_error("invalid index");
	}
	return bits_[index];
}

void BitSet::Set(const int32_t index, const bool val) {
	if (index > GetSize() - 1) {
		throw std::runtime_error("invalid index");
	}
	bits_[index] = val;
}

void BitSet::Resize(const int32_t size) {
	size_ = size;
	bits_.resize(size_);
}

void BitSet::Fill(const bool value) {
	bits_.resize(size_, value);
}

BitSet operator&(const BitSet& lhs, const BitSet& rhs)
{
	BitSet out;
	if (lhs.GetSize() != rhs.GetSize()) {
		throw std::logic_error("invalid size");
	}
	int32_t out_size = lhs.GetSize();
	out.Resize(lhs.GetSize());
	for (int index = 0; index < lhs.GetSize(); ++index) {
		out.Set(index, lhs.Get(index) && rhs.Get(index));
	}
	return out;
}

BitSet operator|(const BitSet& lhs, const BitSet& rhs)
{
	BitSet out;
	if (lhs.GetSize() != rhs.GetSize()) {
		throw std::logic_error("invalid size");
	}
	int32_t out_size = lhs.GetSize();
	out.Resize(lhs.GetSize());
	for (int index = 0; index < lhs.GetSize(); ++index) {
		out.Set(index, lhs.Get(index) || rhs.Get(index));
	}
	return out;
}

BitSet operator~(const BitSet& rhs)
{
	BitSet out;
	int32_t out_size = rhs.GetSize();
	out.Resize(rhs.GetSize());
	for (int index = 0; index < rhs.GetSize(); ++index) {
		out.Set(index, !rhs.Get(index));
	}
	return out;
}

BitSet operator^(const BitSet& lhs, const BitSet& rhs)
{
	BitSet out;
	if (lhs.GetSize() != rhs.GetSize()) {
		throw std::logic_error("invalid size");
	}
	int32_t out_size = lhs.GetSize();
	out.Resize(lhs.GetSize());
	for (int index = 0; index < lhs.GetSize(); ++index) {
		out.Set(index, lhs.Get(index) ^ rhs.Get(index));
	}
	return out;
}

BitSet::BitAccessor BitSet::operator[](const std::int32_t index)
{
	return BitAccessor(*this, index);
}
