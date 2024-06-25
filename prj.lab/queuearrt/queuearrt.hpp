#ifndef QUEUEARRT_QUEUEARRT_HPP
#define QUEUEARRT_QUEUEARRT_HPP
#include <stdexcept>
#include <initializer_list>
#include <memory>

template<class T>
class QueueArrT {
public:
    [[nodiscard]] QueueArrT() = default;
    [[nodiscard]] QueueArrT(const QueueArrT& copy_queuearr);
    [[nodiscard]] QueueArrT(QueueArrT&& copy_queuearr);
    [[nodiscard]] QueueArrT(const std::initializer_list<T>& init_list);
    QueueArrT& operator=(const QueueArrT& copy_queuearr) noexcept;
    QueueArrT& operator=(QueueArrT&& copy_queuearr) noexcept;
    ~QueueArrT();

    [[nodiscard]] bool IsEmpty() const noexcept;
    [[nodiscard]] T& Top()&;
    [[nodiscard]] const T& Top() const&;
    void Pop() noexcept;
    void Push(const T& n_elem);
    void Clear() noexcept;

private:
    std::unique_ptr<T[]> data_arr_ = nullptr;
    T* data_arr_end_ = nullptr;
    T* head_ = nullptr;
    T* tail_ = nullptr;

    void Enlarge() noexcept;
    void Enlarge(const size_t n_size) noexcept;

    void Enlarge_nocopy() noexcept;
    void Enlarge_nocopy(const size_t n_size) noexcept;
};

template<class T>
[[nodiscard]] QueueArrT<T>::QueueArrT(const QueueArrT& copy_queuearr) {
    if (copy_queuearr.IsEmpty()) {
        this->Clear();
        return;
    }

    Enlarge(copy_queuearr.data_arr_end_ - copy_queuearr.data_arr_.get());
    T* our = head_;
    T* theirs = copy_queuearr.head_;
    size_t counter = 0;

    while (theirs != copy_queuearr.tail_ + 1) {
        *our = *theirs;
        ++our;
        ++theirs;
        ++counter;
        if (theirs == copy_queuearr.data_arr_end_ && theirs != tail_ + 1) {
            theirs = copy_queuearr.data_arr_.get();
        }
    }
    tail_ = head_ + counter - 1;
}

template<class T>
[[nodiscard]] QueueArrT<T>::QueueArrT(QueueArrT&& copy_queuearr)
    : data_arr_{ copy_queuearr.data_arr_.release() },
    data_arr_end_{ copy_queuearr.data_arr_end_ },
    head_{ copy_queuearr.head_ },
    tail_{ copy_queuearr.tail_ } {
    copy_queuearr.data_arr_end_ = copy_queuearr.head_ = copy_queuearr.tail_ = nullptr;
}

template<class T>
[[nodiscard]] QueueArrT<T>::QueueArrT(const std::initializer_list<T>& init_list) {
    Enlarge(init_list.size());
    for (size_t i = 0; i < init_list.size(); ++i) {
        data_arr_[i] = init_list.begin()[i];
    }
    tail_ = head_ + init_list.size() - 1;
    return;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(const QueueArrT& copy_queuearr) noexcept {
    if (this == &copy_queuearr) {
        return *this;
    }

    if (copy_queuearr.IsEmpty()) {
        this->Clear();
        return *this;
    }

    if (copy_queuearr.data_arr_end_ - copy_queuearr.data_arr_.get() > data_arr_end_ - data_arr_.get()) {
        Enlarge_nocopy(copy_queuearr.data_arr_end_ - copy_queuearr.data_arr_.get());
    }

    T* our = head_;
    T* theirs = copy_queuearr.head_;
    size_t counter = 0;

    while (theirs != copy_queuearr.tail_ + 1) {
        *our = *theirs;
        ++our;
        ++theirs;
        ++counter;
        if (theirs == copy_queuearr.data_arr_end_ && theirs != tail_ + 1) {
            theirs = copy_queuearr.data_arr_.get();
        }
    }
    tail_ = head_ + counter - 1;
    return *this;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(QueueArrT&& copy_queuearr) noexcept {
    if (this == &copy_queuearr) {
        return *this;
    }

    std::swap(data_arr_, copy_queuearr.data_arr_);
    std::swap(data_arr_end_, copy_queuearr.data_arr_end_);
    std::swap(head_, copy_queuearr.head_);
    std::swap(tail_, copy_queuearr.tail_);
    return *this;
}

template<class T>
QueueArrT<T>::~QueueArrT() {
    head_ = tail_ = data_arr_end_ = nullptr;
    return;
}

template<class T>
[[nodiscard]] bool QueueArrT<T>::IsEmpty() const noexcept {
    return data_arr_ == nullptr || head_ - tail_ == 1;
}

template<class T>
[[nodiscard]] T& QueueArrT<T>::Top()& {
    if (IsEmpty()) {
        throw std::runtime_error("something bad happened");
    }
    return *head_;
}

template<class T>
[[nodiscard]] const T& QueueArrT<T>::Top() const& {
    if (IsEmpty()) {
        throw std::runtime_error("something bad happened");
    }
    return *head_;
}

template<class T>
void QueueArrT<T>::Pop() noexcept {
    if (IsEmpty()) {
        return;
    }

    ++head_;
    if (head_ == data_arr_end_) {
        head_ = data_arr_.get();
        tail_ = head_ - 1;
    }
    return;
}

template<class T>
void QueueArrT<T>::Push(const T& n_elem) {
    if (data_arr_ == nullptr) {
        Enlarge();
    }
    if (head_ == data_arr_.get() && tail_ == head_ - 1) {
        tail_ = head_;
        *tail_ = n_elem;
        return;
    }

    T* new_tail_ = tail_ + 1;

    if (new_tail_ == data_arr_end_) {
        if (head_ != data_arr_.get()) {
            new_tail_ = data_arr_.get();
        }
        else {
            Enlarge();
            new_tail_ = tail_ + 1;
        }
    }
    if (new_tail_ == head_) {
        Enlarge();
        new_tail_ = tail_ + 1;
    }

    *new_tail_ = n_elem;
    tail_ = new_tail_;
    return;
}

template<class T>
void QueueArrT<T>::Clear() noexcept {
    head_ = data_arr_.get();
    tail_ = head_ - 1;
    return;
}

template<class T>
void QueueArrT<T>::Enlarge() noexcept {
    Enlarge(data_arr_end_ - data_arr_.get());
    return;
}

template<class T>
void QueueArrT<T>::Enlarge(const size_t n_size) noexcept {
    size_t new_data_size_ = n_size + n_size / 2 + 1;
    std::unique_ptr<T[]> new_data_(new T[new_data_size_]);
    size_t new_data_elem_ = 0;

    while (head_ != tail_ + 1 && head_ != nullptr) {
        new_data_[new_data_elem_] = *head_;
        ++new_data_elem_;
        ++head_;
        if (head_ == data_arr_end_ && head_ != tail_ + 1) {
            head_ = data_arr_.get();
        }
    }

    data_arr_.reset(new_data_.release());
    data_arr_end_ = data_arr_.get() + new_data_size_;
    head_ = data_arr_.get();
    tail_ = head_ + new_data_elem_ - 1;
    return;
}

template<class T>
void QueueArrT<T>::Enlarge_nocopy() noexcept {
    Enlarge_nocopy(data_arr_end_ - data_arr_.get());
    return;
}

template<class T>
void QueueArrT<T>::Enlarge_nocopy(const size_t n_size) noexcept {
    size_t new_data_size_ = n_size + n_size / 2 + 1;

    data_arr_.reset(new T[new_data_size_]);
    data_arr_end_ = data_arr_.get() + new_data_size_;
    head_ = data_arr_.get();
    tail_ = head_ - 1;
    return;
}

#endif // !QUEUEARRT_QUEUEARRT_HPP
