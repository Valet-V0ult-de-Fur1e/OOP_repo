#include "stackarr.hpp"
#include <stddef.h>
#include "complex/complex.hpp"

StackArr::StackArr(const StackArr& stackArr) {
    std::copy(stackArr.dataPtr, stackArr.dataPtr, dataPtr);
}

StackArr::~StackArr() {
	delete[] dataPtr;
}

StackArr& StackArr::operator=(const StackArr& rhs) {
    return *this;
}

void StackArr::Resize() {
	if (capacity >= size) {
		this->size = size;
	}
	else {
		Complex* newDataPtr = new Complex[size * 2];
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

void StackArr::Push(const Complex& newItem){
	if (size >= capacity) {
		Resize();
	}
	size += 1;
	dataPtr[size] = newItem;
}

void StackArr::Pop() {
	if (size == 0) {
		throw std::runtime_error("Stack is empty");
	}
	size -= 1;
}

bool StackArr::IsEmpty() {
    return (size == 0) ? true : false;
}

std::ptrdiff_t StackArr::Size() const noexcept {
    return size;
}

const Complex StackArr::Top(){
    return dataPtr[size];
}