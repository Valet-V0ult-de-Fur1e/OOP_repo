#pragma once
#ifndef STACKLST_STACKLST_HPP
#define STACKLST_STACKLST_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <class T>
class StackLstT
{
public:
	StackLstT() = default;
	StackLstT(const StackLstT& stack);
	StackLstT(StackLstT&& stack) noexcept;

	~StackLstT();

	StackLstT& operator=(const StackLstT& stack);
	StackLstT& operator=(StackLstT&& stack) noexcept;

	void Push(const T& data);
	void Pop() noexcept;
	void Clear() noexcept;

	T& Top() const;
	bool IsEmpty() const noexcept;

private:
	struct Node
	{
		T data_ = T(0);
		Node* next_ = nullptr;

		Node() = default;
		
		Node(const T& data) {
		data_ = data;
		next_ = nullptr;
		}
	};

	Node* top_ = nullptr;

	void CopyStack(const StackLstT& stack);
};

template <class T>
StackLstT<T>::StackLstT(const StackLstT<T>& stack) {
  CopyStack(stack);
}

template <class T>
StackLstT<T>::StackLstT(StackLstT<T>&& stack) noexcept {
  std::swap(top_, stack.top_);
}

template <class T>
StackLstT<T>::~StackLstT() {
  Clear();
}

template <class T>
StackLstT<T>& StackLstT<T>::operator=(const StackLstT<T>& stack) {
  if (top_ == stack.top_) {
    return *(this);
  }
  else {
    if (stack.IsEmpty()) {
      Clear();
    }
    else if (IsEmpty()) {
      CopyStack(stack);
    }
    else {
      Node* temp_child = top_;
      Node* temp_parent = stack.top_;
      temp_child->data_ = temp_parent->data_;
      while ((temp_child->next_ != nullptr) && (temp_parent->next_ != nullptr)) {
        temp_child->data_ = temp_parent->data_;
        temp_child = temp_child->next_;
        temp_parent = temp_parent->next_;
      }
      if ((temp_parent->next_ == nullptr) && (temp_child->next_ != nullptr)) {
        Node* temp = temp_child->next_;
        temp_child->next_ = nullptr;
        while (temp_child != nullptr) {
          temp_child = temp->next_;
          delete temp;
          temp = temp_child;
        }
      }
      if ((temp_parent->next_ != nullptr) && (temp_child->next_ == nullptr)) {
        while (temp_parent->next_ != nullptr) {
          temp_child->next_ = new Node(temp_parent->next_->data_);
          temp_child = temp_child->next_;
          temp_parent = temp_parent->next_;
        }
      }
    }
    return *(this);
  }
}

template <class T>
StackLstT<T>& StackLstT<T>::operator=(StackLstT<T>&& stack) noexcept {
  std::swap(top_, stack.top_);

  return *this;
}

template <class T>
void StackLstT<T>::Push(const T& data) {
  Node* temp = new Node(data);
  temp->next_ = top_;
  top_ = temp;
}

template <class T>
void StackLstT<T>::Pop() noexcept {
    if (!IsEmpty()) {
        Node* temp = top_;
        top_ = temp->next_;
        delete temp;
    }
    else {
            throw std::logic_error("StackLst - try delete top form empty stack.");
    }
}

template <class T>
void StackLstT<T>::Clear() noexcept {
    while (!IsEmpty())
    {
        Pop();
    }
}

template <class T>
T& StackLstT<T>::Top() const {
  if (IsEmpty()) {
    throw std::logic_error("StackLst - try get top form empty stack.");
  }
  else {
    return top_->data_;
  }
}

template <class T>
bool StackLstT<T>::IsEmpty() const noexcept {
  return (top_ == nullptr);
}

template <class T>
void StackLstT<T>::CopyStack(const StackLstT<T>& stack) {
  if (!stack.IsEmpty()) {
    top_ = new Node(stack.top_->data_);
    Node* temp_parent = stack.top_->next_;
    Node* temp_child = top_;
    while (temp_parent != nullptr) {
      temp_child->next_ = new Node(temp_parent->data_);
      temp_child = temp_child->next_;
      temp_parent = temp_parent->next_;
    }
  }
  else {
    top_ = nullptr;
  }
}

#endif // !STACKLST_STACKLST_HPP