#include<stackarr/stackarr.hpp>

#include<cstddef>
#include<algorithm>
#include<stdexcept>

bool StackArr::IsEmpty() const noexcept {
  return (size_ == 0);
}

StackArr::StackArr(const StackArr& stackarr) {
    size_ = stackarr.size_;
    capacity_ = stackarr.capacity_;
    data_ = std::make_unique<Complex[]>(capacity_);
    std::copy(stackarr.data_.get(), stackarr.data_.get() + size_, data_.get());
}

StackArr::StackArr(StackArr&& array) noexcept {
    std::swap(data_, array.data_);
    size_ = array.size_;
    capacity_ = array.capacity_;
}

StackArr& StackArr::operator=(const StackArr& stackarr) {
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

StackArr& StackArr::operator=(StackArr&& array) noexcept {
    if (this != &array) {
        std::swap(data_, array.data_);
        size_ = array.size_;
        capacity_ = array.capacity_;
    }

    return *this;
}

void StackArr::Pop() {
    if (!IsEmpty()) {
        size_ -= 1;
    }
    else {
        throw std::logic_error("StackArr - try delete top form empty stack.");
    }
}

void StackArr::Push(const Complex& cell) {
    if (size_ >= capacity_) {
        if (capacity_ == 0) {
        capacity_ = 1;
        }
        else {
        capacity_ *= 2;
        }
        std::unique_ptr<Complex[]> ptr_temp = std::make_unique<Complex[]>(capacity_);
        std::copy(data_.get(), data_.get() + size_, ptr_temp.get());
        std::swap(data_, ptr_temp);
        *(data_.get() + size_) = cell;
    }
    else {
        *(data_.get() + size_) = cell;
    }
    ++size_;
}

Complex& StackArr::Top() const{
    if (IsEmpty()) {
        throw std::logic_error("StackArr - try get top form empty stack.");
    }
    return *(data_.get() + size_ - 1);
}

void StackArr::Clear() noexcept {
    size_ = 0;
}

ptrdiff_t StackArr::Capacity() const noexcept {
    return capacity_;
}