#ifndef QUEUEARRT_QUEUEARRT_HPP
#define QUEUEARRT_QUEUEARRT_HPP

#include<cstddef>
#include<memory>
#include<stdexcept>

template<class T>
class QueueArrT
{
public:
  QueueArrT() = default;
  QueueArrT(const QueueArrT& queue);
  QueueArrT(QueueArrT&& queue) noexcept;

  ~QueueArrT() = default;

  QueueArrT& operator=(const QueueArrT& queue);
  QueueArrT& operator=(QueueArrT&& queue) noexcept;

  void Push(const T& data);
  void Pop() noexcept;
  void Clear() noexcept;

  T& Top();
  const T& Top() const;
  bool IsEmpty() const noexcept;

private:
  void reallocate(std::ptrdiff_t size, const QueueArrT& source);
  std::ptrdiff_t Count() const;

  T* head_ = nullptr;
  T* tail_ = nullptr;

  std::unique_ptr<T[]> data_ = nullptr;
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
};

template<class T>
QueueArrT<T>::QueueArrT(const QueueArrT<T>& queue) {
  reallocate(queue.capacity_, queue);
}

template<class T>
QueueArrT<T>::QueueArrT(QueueArrT<T>&& queue) noexcept {
  std::swap(data_, queue.data_);
  capacity_ = queue.capacity_;
  size_ = queue.size_;
  head_ = queue.head_;
  tail_ = queue.tail_;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(const QueueArrT<T>& queue) {
  if (&queue == this) {
    return *this;
  }
  else {
    if (queue.size_ > capacity_) {
      reallocate(queue.capacity_, queue);
    }
    else {
      std::copy(queue.head_,
        (queue.tail_ > queue.head_) ? (queue.tail_ + 1) : (queue.data_.get() + queue.capacity_),
        data_.get());
      if (queue.tail_ < queue.head_) {
        std::copy(queue.data_.get(),
          queue.tail_ + 1,
          data_.get() + (queue.data_.get() + queue.capacity_ - queue.head_));
      }
      capacity_ = queue.capacity_;
      size_ = queue.size_;
      head_ = data_.get();
      tail_ = head_ + size_ - 1;
    }
  }

  return *this;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(QueueArrT<T>&& queue) noexcept {
  if (this != &queue) {
    std::swap(data_, queue.data_);
    capacity_ = queue.capacity_;
    size_ = queue.size_;
    head_ = queue.head_;
    tail_ = queue.tail_;
  }

  return *this;
}

template<class T>
void QueueArrT<T>::Push(const T& data) {
  if (size_ == 0) {
    if (capacity_ == 0) {
      capacity_ = 1;
      data_ = std::make_unique<T[]>(capacity_);
    }
    head_ = data_.get();
    tail_ = head_;
    *tail_ = data;
    size_ += 1;
  }
  else {
    if (size_ + 1 >= capacity_) {
      reallocate(capacity_ * 2, *this);
    }
    tail_ = data_.get() + (head_ + size_ - data_.get()) % capacity_;
    *tail_ = data;
    ++size_;
  }
}

template<class T>
void QueueArrT<T>::Pop() noexcept {
  if (!IsEmpty()) {
    head_ = data_.get() + (head_ - data_.get() + 1) % capacity_;
    --size_;
  }
}

template<class T>
void QueueArrT<T>::Clear() noexcept {
  size_ = 0;
}

template<class T>
T& QueueArrT<T>::Top() {
  if (IsEmpty()) {
    throw std::runtime_error("Queue is empty!");
  }
  return *head_;
}

template<class T>
const T& QueueArrT<T>::Top() const {
  if (IsEmpty()) {
    throw std::runtime_error("Queue is empty!");
  }
  return *head_;
}

template<class T>
bool QueueArrT<T>::IsEmpty() const noexcept {
  return (size_ == 0);
}

template<class T>
void QueueArrT<T>::reallocate(std::ptrdiff_t newCapacity, const QueueArrT& source) {
  std::unique_ptr<T[]> newdata = std::make_unique<T[]>(newCapacity);
  if (source.size_ != 0) {
    std::copy(source.head_,
      (source.tail_ > source.head_) ? (source.tail_ + 1) : (source.data_.get() + source.capacity_),
      newdata.get());
    if (source.tail_ < source.head_) {
      std::copy(source.data_.get(),
        source.tail_ + 1,
        newdata.get() + (source.data_.get() + source.capacity_ - source.head_));
    }
  }
  std::swap(data_, newdata);
  capacity_ = newCapacity;
  size_ = source.size_;
  head_ = data_.get();
  tail_ = head_ + size_ - 1;
}

template<class T>
std::ptrdiff_t QueueArrT<T>::Count() const {
  return IsEmpty() ? 0 : (tail_ + size_ - head_) % size_ + 1;
}
#endif // !QUEUEARRT_QUEUEARRT_HPP
