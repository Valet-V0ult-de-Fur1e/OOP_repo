#pragma once
#ifndef DYNARRT_DYNARRT_HPP
#define DYNARRT_DYNARRT_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include<algorithm>
#include<stdexcept>

template<class T>
class DynArrT
{
public:
	DynArrT() = default;
	DynArrT(const DynArrT& dynArray);
	DynArrT(DynArrT&& dynarr) noexcept;
	DynArrT(const std::ptrdiff_t size);

	DynArrT& operator=(const DynArrT& dynArray);
	DynArrT& operator=(DynArrT&& dynarr) noexcept;
	std::ptrdiff_t Size() const noexcept;

	void Resize(const std::ptrdiff_t size);

	[[nodiscard]] T& operator[](const std::ptrdiff_t index);
	[[nodiscard]] const T& operator[](const std::ptrdiff_t index) const;

	std::ostream& WriteTo(std::ostream& ostrm) const;

	~DynArrT() = default;

private:
	std::ptrdiff_t size_ = 0;
	std::unique_ptr<T[]> dataPtr_ = std::make_unique<T[]>(0);;
};

template<class T>
inline std::ostream& operator<<(std::ostream& ostrm, const DynArrT<T>& rhs) {
	return rhs.WriteTo(ostrm);
}

template<class T>
DynArrT<T>::DynArrT(const DynArrT<T>& dynArray) {
	if (dynArray.size_ > 0) {
		Resize(dynArray.size_);
		std::copy(dynArray.dataPtr_.get(), dynArray.dataPtr_.get() + dynArray.size_, dataPtr_.get());
	}
	else {
		throw std::runtime_error("invalid size");
	}
}

template<class T>
DynArrT<T>::DynArrT(DynArrT<T>&& dynarr) noexcept {
	std::swap(dataPtr_, dynarr.dataPtr_);
	std::swap(size_, dynarr.size_);
}

template<class T>
DynArrT<T>::DynArrT(const std::ptrdiff_t size) {
	Resize(size);
}

template<class T>
std::ptrdiff_t DynArrT<T>::Size() const noexcept {
	return size_;
}

template<class T>
DynArrT<T>& DynArrT<T>::operator=(const DynArrT<T>& dynArray) {
	if (dataPtr_ == dynArray.dataPtr_) {
		return *this;
	}
	Resize(dynArray.size_);
	std::copy(dynArray.dataPtr_.get(), dynArray.dataPtr_.get() + dynArray.size_, dataPtr_.get());
	return *this;
}

template<class T>
DynArrT<T>& DynArrT<T>::operator=(DynArrT<T>&& dynarr) noexcept {
	if (this != &dynarr) {
		std::swap(dataPtr_, dynarr.dataPtr_);
		std::swap(size_, dynarr.size_);
	}
	return *this;
}

template<class T>
void DynArrT<T>::Resize(const std::ptrdiff_t size) {
	if (size <= 0) {
		throw std::runtime_error("invalid size");
	}
	else {
		std::unique_ptr<T[]> newDataPtr = std::make_unique<T[]>(size);
		std::fill(newDataPtr.get(), newDataPtr.get() + size, 0);
		if (dataPtr_!=nullptr) {
			std::copy(dataPtr_.get(), dataPtr_.get() + ((size < size_) ? size : size_), newDataPtr.get());
		}
		std::swap(dataPtr_, newDataPtr);
		size_ = size;
	}
}

template<class T>
T& DynArrT<T>::operator[](const std::ptrdiff_t index) {
	if (0 <= index && index < size_) {
		return dataPtr_[index];
	}
	throw std::runtime_error("out of range");
}

template<class T>
const T& DynArrT<T>::operator[](const std::ptrdiff_t index) const {
	if (0 <= index && index < size_) {
		return dataPtr_[index];
	}
	throw std::runtime_error("out of range");
}

template<class T>
std::ostream& DynArrT<T>::WriteTo(std::ostream& ostrm) const {
	for (int i = 0; i < size_ - 1; i++) {
		ostrm << (*this)[i] << " ";
	}
	ostrm << (*this)[size_ - 1];
	return ostrm;
}

#endif // !DYNARRT_DYNARRT_HPP