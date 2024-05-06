#pragma once
#ifndef STACKARRT_STACKARRT_HPP
#define STACKARRT_STACKARRT_HPP

#include<cstddef>
#include<memory>
#include<algorithm>
#include<stdexcept>

template<class T>
class StackArrT
{
public:
  StackArrT() = default;
  StackArrT(const StackArrT& stackarr);
  StackArrT(StackArrT&& stack) noexcept;
  
  ~StackArrT() = default;

  StackArrT& operator=(const StackArrT& stackarr);
  StackArrT& operator=(StackArrT&& stack) noexcept;

  void Push(const T& cell);
  void Pop() noexcept;
  void Clear() noexcept;

  bool IsEmpty() const noexcept;
  T& Top() const;
  ptrdiff_t Size() const noexcept;
  ptrdiff_t Capacity() const noexcept;

private:
  ptrdiff_t size_ = 0;
  ptrdiff_t capacity_ = 0;
  std::unique_ptr<T[]> data_ = nullptr;
};

template<class T>
bool StackArrT<T>::IsEmpty() const noexcept {
  return (size_ == 0);
}

template<class T>
StackArrT<T>::StackArrT(const StackArrT<T>& stackarr) {
    size_ = stackarr.size_;
    capacity_ = stackarr.capacity_;
    data_ = std::make_unique<Complex[]>(capacity_);
    std::copy(stackarr.data_.get(), stackarr.data_.get() + size_, data_.get());
}

template<class T>
StackArrT<T>::StackArrT(StackArrT<T>&& array) noexcept {
    std::swap(data_, array.data_);
    size_ = array.size_;
    capacity_ = array.capacity_;
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(const StackArrT& stackarr) {
    if (data_ == stackarr.data_) {
        return *this;
    }
    else {
        if (capacity_ >= stackarr.size_) {
        size_ = stackarr.size_;
        std::copy(stackarr.data_.get(), stackarr.data_.get() + size_, data_.get());
        }
        else {
        size_ = stackarr.size_;
        capacity_ = stackarr.capacity_;
        data_ = std::make_unique<Complex[]>(capacity_);
        std::copy(stackarr.data_.get(), stackarr.data_.get() + size_, data_.get());
        }
        return *this;
    }
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(StackArrT&& array) noexcept {
    if (this != &array) {
        std::swap(data_, array.data_);
        size_ = array.size_;
        capacity_ = array.capacity_;
    }

    return *this;
}

template<class T>
void StackArrT<T>::Pop() {
    if (!IsEmpty()) {
        size_ -= 1;
    }
    else {
        throw std::logic_error("StackArr - try delete top form empty stack.");
    }
}

template<class T>
void StackArrT<T>::Push(const T& cell) {
    if (size_ >= capacity_) {
        if (capacity_ == 0) {
        capacity_ = 1;
        }
        else {
        capacity_ *= 2;
        }
        std::unique_ptr<T[]> ptr_temp = std::make_unique<T[]>(capacity_);
        std::copy(data_.get(), data_.get() + size_, ptr_temp.get());
        std::swap(data_, ptr_temp);
        *(data_.get() + size_) = cell;
    }
    else {
        *(data_.get() + size_) = cell;
    }
    ++size_;
}

template<class T>
T& StackArrT<T>::Top() const{
    if (IsEmpty()) {
        throw std::logic_error("StackArr - try get top form empty stack.");
    }
    return *(data_.get() + size_ - 1);
}

template<class T>
void StackArrT<T>::Clear() noexcept {
    size_ = 0;
}

template<class T>
ptrdiff_t StackArrT<T>::Capacity() const noexcept {
    return capacity_;
}

#endif // !STACKARRT_STACKARRT_HPP