#include "dynarr.hpp"
#include <stddef.h>
#include <algorithm>

DynArr::DynArr(const DynArr& dynArray) {
	if (dynArray.size > 0) {
		Resize(dynArray.capacity);
		std::copy(dynArray.dataPtr, dynArray.dataPtr + dynArray.capacity, dataPtr);
		Resize(dynArray.size);
	}
	else {
		throw std::runtime_error("invalid size");
	}
}

DynArr::DynArr(const std::ptrdiff_t size) {
	Resize(size);
}

std::ptrdiff_t DynArr::Size() const noexcept {
	return size;
}

void DynArr::Resize(const std::ptrdiff_t size) {
	if (size <= 0) {
		throw std::runtime_error("invalid size");
	}
	else {
		if (capacity >= size) {
			this->size = size;
		}
		else {
			float* newDataPtr = new float[size * 2];
			std::fill(newDataPtr, newDataPtr + size * 2, 0);
			if (dataPtr != nullptr) {
				std::copy(dataPtr, dataPtr + this->capacity, newDataPtr);
			}
			delete[] dataPtr;
			dataPtr = newDataPtr;
			this->capacity = size * 2;
			this->size = size;
		}
	}
}

float& DynArr::operator[](const std::ptrdiff_t index) {
	if (0 <= index && index < size) {
		return dataPtr[index];
	}
	throw std::runtime_error("out of range");
}

const float& DynArr::operator[](const std::ptrdiff_t index) const {
	if (0 <= index && index < size) {
		return dataPtr[index];
	}
	throw std::runtime_error("out of range");
}

std::ostream& DynArr::WriteTo(std::ostream& ostrm) const {
	for (int i = 0; i < size - 1; i++) {
		ostrm << (*this)[i] << " ";
	}
	ostrm << (*this)[size - 1];
	return ostrm;
}

DynArr::~DynArr() {
	delete[] dataPtr;
}