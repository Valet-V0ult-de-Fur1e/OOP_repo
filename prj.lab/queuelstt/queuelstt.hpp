#pragma once
#ifndef QUEUELSTT_QUEUELSTT_HPP
#define QUEUELSTT_QUEUELSTT_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>

template<class T>
class QueueLstT
{
public:
	QueueLstT() = default;
	QueueLstT(const QueueLstT& queue);
	QueueLstT(QueueLstT&& queue) noexcept;

	~QueueLstT();

	QueueLstT& operator=(const QueueLstT& queue);
	QueueLstT& operator=(QueueLstT&& queue) noexcept;

	void Push(const T& data);
	void Pop() noexcept;
	void Clear() noexcept;

	T& Back();
	const T& Back() const;

	T& Top();
	const T& Top() const;
	
	bool IsEmpty() const noexcept;

private:
	struct Node
	{
		T data_ = T(0);
		Node* next_ = nullptr;

		Node() = default;
		Node(const T& data) : data_(data), next_(nullptr) {}
	};

	Node* head_ = nullptr;
	Node* tail_ = nullptr;

	void CopyQueue(const QueueLstT& queue);
};

template<class T>
QueueLstT<T>::QueueLstT(const QueueLstT<T>& queue) {
  CopyQueue(queue);
}

template<class T>
QueueLstT<T>::QueueLstT(QueueLstT&& queue) noexcept {
  std::swap(head_, queue.head_);
  tail_ = queue.tail_;
}

template<class T>
QueueLstT<T>::~QueueLstT() {
  Clear();
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(const QueueLstT<T>& queue) {
  if (head_ == queue.head_) {
    return *(this);
  }
  else {
    if (queue.IsEmpty()) {
      Clear();
    }
    else if (IsEmpty()) {
      CopyQueue(queue);
    }
    else {
      head_->data_ = queue.head_->data_;
      Node* parent = queue.head_;
      Node* child = head_;
      while ((parent->next_ != nullptr) && (child->next_ != nullptr)) {
        child->data_ = parent->data_;
        child = child->next_;
        parent = parent->next_;
      }
      child->data_ = parent->data_;
      if ((parent->next_ != nullptr) && (child->next_ == nullptr)) {
        while (parent->next_ != nullptr) {
          child->next_ = new Node(parent->next_->data_);
          child = child->next_;
          parent = parent->next_;
        }
      }
      tail_ = child;
      if ((parent->next_ == nullptr) && (child->next_ != nullptr)) {
        Node* temp = child->next_;
        child->next_ = nullptr;
        while (child != nullptr) {
          child = temp->next_;
          delete temp;
          temp = child;
        }
      }
    }
    return *(this);
  }
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(QueueLstT<T>&& rhs) noexcept
{
    if (this != &rhs) {
        std::swap(head_, rhs.head_);
        std::swap(tail_, rhs.tail_);
    }
    return *this;
}

template<class T>
bool QueueLstT<T>::IsEmpty() const noexcept {
    return head_ == nullptr;
}

template<class T>
void QueueLstT<T>::Pop() noexcept {
    if (!IsEmpty()) {
        Node* deleted = head_;
        head_ = head_->next_;
        delete deleted;
    }
    else {
        throw std::logic_error("QueueLst - try delete top form empty queue.");
    }
}

template<class T>
void QueueLstT<T>::Push(const T& data) {
  if (IsEmpty()) {
    tail_ = new Node(data);
    head_ = tail_;
  }
  else {
    tail_->next_ = new Node(data);
    tail_ = tail_->next_;
  }
}

template<class T>
const T& QueueLstT<T>::Back() const {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get back form empty queue.");
    }
    return (tail_->data_);
}

template<class T>
T& QueueLstT<T>::Back() {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get back form empty queue.");
    }
    return tail_->data_;
}

template<class T>
const T& QueueLstT<T>::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get front form empty queue.");
    }
    return (head_->data_);
}

template<class T>
T& QueueLstT<T>::Top() {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get top front empty queue.");
    }
    return head_->data_;
}

template<class T>
void QueueLstT<T>::Clear() noexcept {
    while (!IsEmpty())
    {
        Pop();
    }
}

template<class T>
void QueueLstT<T>::CopyQueue(const QueueLstT<T>& queue) {
  if (!queue.IsEmpty()) {
    head_ = new Node(queue.head_->data_);
    tail_ = head_;
    Node* temp = queue.head_->next_;
    while (temp != nullptr) {
      tail_->next_ = new Node(temp->data_);
      tail_ = tail_->next_;
      temp = temp->next_;
    }
  }
  else {
    head_ = nullptr;
    tail_ = nullptr;
  }
}

#endif // !QUEUELSTT_QUEUELSTT_HPP