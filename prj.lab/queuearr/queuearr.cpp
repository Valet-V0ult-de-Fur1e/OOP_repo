#include<queuearr/queuearr.hpp>

#include<stdexcept>

QueueArr::QueueArr(const QueueArr& queue) {
  reallocate(queue.capacity_, queue);
}

QueueArr::QueueArr(QueueArr&& queue) noexcept {
  std::swap(data_, queue.data_);
  capacity_ = queue.capacity_;
  size_ = queue.size_;
  head_ = queue.head_;
  tail_ = queue.tail_;
}

QueueArr& QueueArr::operator=(const QueueArr& queue) {
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

QueueArr& QueueArr::operator=(QueueArr&& queue) noexcept {
  if (this != &queue) {
    std::swap(data_, queue.data_);
    capacity_ = queue.capacity_;
    size_ = queue.size_;
    head_ = queue.head_;
    tail_ = queue.tail_;
  }

  return *this;
}

void QueueArr::Push(const Complex& data) {
  if (size_ == 0) {
    if (capacity_ == 0) {
      capacity_ = 1;
      data_ = std::make_unique<Complex[]>(capacity_);
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

void QueueArr::Pop() noexcept {
  if (!IsEmpty()) {
    head_ = data_.get() + (head_ - data_.get() + 1) % capacity_;
    --size_;
  }
}

void QueueArr::Clear() noexcept {
  size_ = 0;
}

Complex& QueueArr::Top() {
  if (IsEmpty()) {
    throw std::runtime_error("Queue is empty!");
  }
  return *head_;
}

const Complex& QueueArr::Top() const {
  if (IsEmpty()) {
    throw std::runtime_error("Queue is empty!");
  }
  return *head_;
}

bool QueueArr::IsEmpty() const noexcept {
  return (size_ == 0);
}

void QueueArr::reallocate(std::ptrdiff_t newCapacity, const QueueArr& source) {
  std::unique_ptr<Complex[]> newdata = std::make_unique<Complex[]>(newCapacity);
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

std::ptrdiff_t QueueArr::Count() const {
  return IsEmpty() ? 0 : (tail_ + size_ - head_) % size_ + 1;
}