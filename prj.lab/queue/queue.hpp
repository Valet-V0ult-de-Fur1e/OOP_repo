#pragma once
#ifndef QUEUE_QUEUE_HPP
#define QUEUE_QUEUE_HPP

#include <cstddef>
#include <iostream>
#include "complex/complex.hpp"

class Queue
{
public:
	Queue() = default;

	Queue(const Queue&) = default;

	~Queue() = default;

	[[nodiscard]] Queue& operator=(const Queue&) = default;

	bool IsEmpty() const noexcept;

	void Pop() noexcept;

	void Push(const Complex& val);

	[[nodiscard]] Complex& Front();

	[[nodiscard]] const Complex& Front() const;

	[[nodiscard]] Complex& Back();

	[[nodiscard]] const Complex& Back() const;

	void Clear() noexcept;
private:

	struct Node {
		Node(Complex const val_, Node* const next_) : val(val_), next(next_) {};
		Complex val;
		Node* next = nullptr;
	};

	Node* head_ = nullptr;
	Node* tail_ = nullptr;
};

#endif // !QUEUE_QUEUE_HPP