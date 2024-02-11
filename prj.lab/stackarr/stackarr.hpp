#pragma once
#ifndef STACKARR_STACKARR_HPP
#define STACKARR_STACKARR_HPP

#include <cstddef>
#include <iostream>
#include "complex/complex.hpp"

class StackArr
{
public:
	StackArr() = default;
	StackArr(const StackArr& stackArray);
	~StackArr();
	
	StackArr& operator=(const StackArr& rhs);

	void Push(const Complex& newItem);
	void Pop();
	void Resize();
	
	bool IsEmpty();

	std::ptrdiff_t Size() const noexcept;
	
	const Complex Top();


private:
	std::ptrdiff_t size = 0;
	std::ptrdiff_t capacity = 0;
	Complex* dataPtr = nullptr;
};


#endif // !STACKARR_STACKARR_HPP