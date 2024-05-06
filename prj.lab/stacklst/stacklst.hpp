#pragma once
#ifndef STACKLST_STACKLST_HPP
#define STACKLST_STACKLST_HPP

#include <cstddef>
#include <iostream>
#include "complex/complex.hpp"

class StackLst
{
public:
  StackLst() = default;
  StackLst(const StackLst& stack);
  StackLst(StackLst&& stack) noexcept;

  ~StackLst();

  StackLst& operator=(const StackLst& stack);
  StackLst& operator=(StackLst&& stack) noexcept;

  void Push(const Complex& data);
  void Pop() noexcept;
  void Clear() noexcept;

  Complex& Top() const;
  bool IsEmpty() const noexcept;

private:
  struct Node
  {
    Complex data_ = Complex(0);
    Node* next_ = nullptr;

    Node() = default;
    
    Node(const Complex& data) {
      data_ = data;
      next_ = nullptr;
    }
  };

  Node* top_ = nullptr;

  void CopyStack(const StackLst& stack);
};

#endif // !STACKLST_STACKLST_HPP