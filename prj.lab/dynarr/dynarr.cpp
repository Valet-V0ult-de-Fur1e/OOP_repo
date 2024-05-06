#include "dynarr.hpp"
#include <stddef.h>
#include <algorithm>

DynArr::DynArr(const DynArr& dynArray) {
	if (dynArray.size_ > 0) {
		Resize(dynArray.size_);
		std::copy(dynArray.dataPtr_.get(), dynArray.dataPtr_.get() + dynArray.size_, dataPtr_.get());
	}
	else {
		throw std::runtime_error("invalid size");
	}
}

DynArr::DynArr(DynArr&& dynarr) noexcept {
	std::swap(dataPtr_, dynarr.dataPtr_);
	std::swap(size_, dynarr.size_);
}

DynArr::DynArr(const std::ptrdiff_t size) {
	Resize(size);
}

std::ptrdiff_t DynArr::Size() const noexcept {
	return size_;
}

DynArr& DynArr::operator=(const DynArr& dynArray) {
	if (dataPtr_ == dynArray.dataPtr_) {
		return *this;
	}
	Resize(dynArray.size_);
	std::copy(dynArray.dataPtr_.get(), dynArray.dataPtr_.get() + dynArray.size_, dataPtr_.get());
	return *this;
}

DynArr& DynArr::operator=(DynArr&& dynarr) noexcept {
	if (this != &dynarr) {
		std::swap(dataPtr_, dynarr.dataPtr_);
		std::swap(size_, dynarr.size_);
	}
	return *this;
}


void DynArr::Resize(const std::ptrdiff_t size) {
	if (size <= 0) {
		throw std::runtime_error("invalid size");
	}
	else {
		std::unique_ptr<float[]> newDataPtr = std::make_unique<float[]>(size);
		std::fill(newDataPtr.get(), newDataPtr.get() + size, 0);
		if (dataPtr_!=nullptr) {
			std::copy(dataPtr_.get(), dataPtr_.get() + ((size < size_) ? size : size_), newDataPtr.get());
		}
		std::swap(dataPtr_, newDataPtr);
		size_ = size;
	}
}

float& DynArr::operator[](const std::ptrdiff_t index) {
	if (0 <= index && index < size_) {
		return dataPtr_[index];
	}
	throw std::runtime_error("out of range");
}

const float& DynArr::operator[](const std::ptrdiff_t index) const {
	if (0 <= index && index < size_) {
		return dataPtr_[index];
	}
	throw std::runtime_error("out of range");
}

std::ostream& DynArr::WriteTo(std::ostream& ostrm) const {
	for (int i = 0; i < size_ - 1; i++) {
		ostrm << (*this)[i] << " ";
	}
	ostrm << (*this)[size_ - 1];
	return ostrm;
}