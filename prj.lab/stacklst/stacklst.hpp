#pragma once
#ifndef STACKLST_STACKLST_HPP
#define STACKLST_STACKLST_HPP

#include <cstddef>
#include <iostream>
#include "complex/complex.hpp"

class StackLst
{
public:
	[[nodiscard]] StackLst() = default;

	[[nodiscard]] StackLst(const StackLst&) = default;
	[[nodiscard]] StackLst(StackLst&& rhs) noexcept;

	~StackLst() = default;

	[[nodiscard]] StackLst& operator=(const StackLst&) = default;
	[[nodiscard]] StackLst& operator=(StackLst&& rhs);
	bool IsEmpty() const noexcept;

	void Pop() noexcept;

	void Push(const Complex& val);

	[[nodiscard]] Complex& Top();

	[[nodiscard]] const Complex& Top() const;

	void Clear() noexcept;
private:

	struct Node {
		Node(Complex const val_, Node* const next_) : val(val_), next(next_) {};
		Complex val;
		Node* next = nullptr;
	};

	Node* head_ = nullptr;
};

#endif // !STACKLST_STACKLST_HPP