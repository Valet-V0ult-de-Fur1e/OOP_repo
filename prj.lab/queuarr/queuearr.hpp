#pragma once
#ifndef QUEUE_QUEUE_HPP
#define QUEUE_QUEUE_HPP

#include <cstddef>
#include "complex/complex.hpp"

class QueueArr {
public:
	QueueArr() = default;

	QueueArr(const QueueArr&);

	QueueArr(QueueArr&& rhs) noexcept;

	~QueueArr();

	QueueArr& operator=(QueueArr&& rhs);

	[[nodiscard]] bool IsEmpty() const noexcept;

	void Pop() noexcept;

	void Push(const Complex& val);

	[[nodiscard]] Complex& Top();

	[[nodiscard]] const Complex& Top() const;

	void Clear() noexcept;

private:
	std::ptrdiff_t size_ = 0;  
	Complex* data_ = nullptr;  
	std::ptrdiff_t head_ = -1; 
	std::ptrdiff_t tail_ = -1; 
private:
	std::ptrdiff_t Count() const;
};

#endif // !QUEUE_QUEUE_HPP