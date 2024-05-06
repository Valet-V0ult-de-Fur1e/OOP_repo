#pragma once
#ifndef QUEUELST_QUEUELST_HPP
#define QUEUELST_QUEUELST_HPP

#include <cstddef>
#include <iostream>
#include "complex/complex.hpp"

class QueueLst
{
public:
	QueueLst() = default;
	QueueLst(const QueueLst& queue);
	QueueLst(QueueLst&& queue) noexcept;

	~QueueLst();

	QueueLst& operator=(const QueueLst& queue);
	QueueLst& operator=(QueueLst&& queue) noexcept;

	void Push(const Complex& data);
	void Pop() noexcept;
	void Clear() noexcept;

	Complex& Back();
	const Complex& Back() const;

	Complex& Top();
	const Complex& Top() const;
	
	bool IsEmpty() const noexcept;

private:
	struct Node
	{
		Complex data_ = Complex(0);
		Node* next_ = nullptr;

		Node() = default;
		Node(const Complex& data) : data_(data), next_(nullptr) {}
	};

	Node* head_ = nullptr;
	Node* tail_ = nullptr;

	void CopyQueue(const QueueLst& queue);
};


#endif // !QUEUELST_QUEUELST_HPP