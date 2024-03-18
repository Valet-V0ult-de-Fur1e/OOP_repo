#include <complex/complex.hpp>
#include <stackarr/stackarr.hpp>

#include <algorithm>
#include <stdexcept>

bool StackArr::IsEmpty() const noexcept {
    return 0 > i_top_;
}

StackArr::StackArr(StackArr&& rhs) noexcept : size_(rhs.size_), i_top_(rhs.i_top_), data_(rhs.data_) {
    rhs.size_ = 0;
    rhs.i_top_ = -1;
    rhs.data_ = nullptr;
}

StackArr& StackArr::operator=(StackArr&& rhs) {
    if (this != &rhs) {
        std::swap(size_, rhs.size_);
        std::swap(i_top_, rhs.i_top_);
        std::swap(data_, rhs.data_);
    }
    return *this;
}

void StackArr::Pop() {
    if (!IsEmpty()) {
        i_top_ -= 1;
    }
    else {
        throw std::logic_error("StackArr - try delete top form empty stack.");
    }
}

void StackArr::Push(const Complex& val) {
    if (nullptr == data_) {
        size_ = 8;
        data_ = new Complex[size_];
    }
    else if (size_ == i_top_ + 1) {
        auto buf = new Complex(size_ * 2);
        std::copy(data_, data_ + size_, buf);
        std::swap(data_, buf);
        delete[] buf;
        size_ *= 2;
    }
    data_[++i_top_] = val;
}

Complex& StackArr::Top() {
    if (i_top_ < 0) {
        throw std::logic_error("StackArr - try get top form empty stack.");
    }
    return data_[i_top_];
}

const Complex& StackArr::Top() const {
    if (i_top_ < 0) {
        throw std::logic_error("StackArr - try get top form empty stack.");
    }
    return data_[i_top_];
}

void StackArr::Clear() noexcept {
    i_top_ = -1;
}