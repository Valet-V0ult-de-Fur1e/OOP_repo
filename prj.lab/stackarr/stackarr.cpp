#include "stackarr.hpp"
#include <stddef.h>

StackArr::StackArr(const StackArr& stackArr) {
    std::copy(stackArr.dataPtr, stackArr.dataPtr, dataPtr);
}

StackArr::~StackArr() {
	delete[] dataPtr;
}

StackArr& StackArr::operator=(const StackArr& rhs){

}

void Push(const)

bool StackArr::IsEmpty() {
    return (size == 0) ? true : false;
}

std::ptrdiff_t StackArr::Size() const noexcept {
    return size;
}

const Complex StackArr::Top(){

}