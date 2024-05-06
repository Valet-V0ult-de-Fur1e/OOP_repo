#pragma once
#ifndef STACKARR_STACKARR_HPP
#define STACKARR_STACKARR_HPP

#include<complex/complex.hpp>
#include<cstddef>
#include<memory>

class StackArr
{
public:
  StackArr() = default;
  StackArr(const StackArr& stackarr);
  StackArr(StackArr&& stack) noexcept;
  
  ~StackArr() = default;

  StackArr& operator=(const StackArr& stackarr);
  StackArr& operator=(StackArr&& stack) noexcept;

  void Push(const Complex& cell);
  void Pop() noexcept;
  void Clear() noexcept;

  bool IsEmpty() const noexcept;
  Complex& Top() const;
  ptrdiff_t Size() const noexcept;
  ptrdiff_t Capacity() const noexcept;

private:
  ptrdiff_t size_ = 0;
  ptrdiff_t capacity_ = 0;
  std::unique_ptr<Complex[]> data_ = nullptr;
};

#endif // !STACKARR_STACKARR_HPP