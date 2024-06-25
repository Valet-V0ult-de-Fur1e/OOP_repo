#pragma once
#ifndef QUEUELSTT_QUEUELSTT_HPP
#define QUEUELSTT_QUEUELSTT_HPP

#include <stdexcept>
#include <initializer_list>

template<class T>
class QueueLstT {
public:
    [[nodiscard]] QueueLstT() = default;
    [[nodiscard]] QueueLstT(const QueueLstT& copy_queuelst);
    [[nodiscard]] QueueLstT(QueueLstT&& copy_queuelst);
    [[nodiscard]] QueueLstT(const std::initializer_list<T>& init_list);
    QueueLstT& operator=(const QueueLstT& copy_queuelst) noexcept;
    QueueLstT& operator=(QueueLstT&& copy_queuelst) noexcept;
    ~QueueLstT();

    [[nodiscard]] bool IsEmpty() const noexcept;
    [[nodiscard]] T& Top()&;
    [[nodiscard]] const T& Top() const&;
    void Pop() noexcept;
    void Push(const T& n_elem);
    void Clear() noexcept;

private:
    struct Node {
        Node(const T& n_value);
        T value;
        Node* next_node = nullptr;
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
};


template<class T>
[[nodiscard]] QueueLstT<T>::QueueLstT(const QueueLstT& copy_queuelst) {
    Node* copy_head = copy_queuelst.head_;
    while (copy_head != nullptr) {
        Push(copy_head->value);
        copy_head = copy_head->next_node;
    }
    return;
}

template<class T>
[[nodiscard]] QueueLstT<T>::QueueLstT(QueueLstT&& copy_queuelst)
    : head_{ copy_queuelst.head_ },
    tail_{ copy_queuelst.tail_ } {
    copy_queuelst.head_ = nullptr;
    copy_queuelst.tail_ = nullptr;
}

template<class T>
[[nodiscard]] QueueLstT<T>::QueueLstT(const std::initializer_list<T>& init_list) {
    for (T i : init_list) {
        Push(i);
    }
    return;
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(const QueueLstT& copy_queuelst) noexcept {
    if (this == &copy_queuelst) {
        return *this;
    }

    Node* our_elem = head_;
    Node* our_elem_prev = nullptr;
    tail_ = nullptr;
    Node* their_elem = copy_queuelst.head_;

    while (our_elem != nullptr && their_elem != nullptr) {
        our_elem->value = their_elem->value;

        our_elem_prev = our_elem;
        our_elem = our_elem->next_node;

        their_elem = their_elem->next_node;
    }

    if (our_elem != nullptr && their_elem == nullptr) {
        if (our_elem_prev != nullptr) {
            our_elem_prev->next_node = nullptr;
            tail_ = our_elem_prev;
        }

        Node* to_delete = nullptr;
        while (our_elem != nullptr) {
            to_delete = our_elem;
            our_elem = our_elem->next_node;
            delete to_delete;
        }

        if (our_elem_prev == nullptr) {
            head_ = tail_ = nullptr;
        }
    }

    if (our_elem == nullptr && their_elem != nullptr) {
        if (our_elem_prev == nullptr) {
            head_ = new Node(their_elem->value);
            our_elem_prev = head_;
            their_elem = their_elem->next_node;
        }
        while (their_elem != nullptr) {
            Node* our_elem_new = new Node(their_elem->value);
            our_elem_prev->next_node = our_elem_new;
            our_elem_prev = our_elem_new;
            their_elem = their_elem->next_node;
        }

        tail_ = our_elem_prev;
        our_elem_prev->next_node = nullptr;
    }

    return *this;
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(QueueLstT&& copy_queuelst) noexcept {
    if (this == &copy_queuelst) {
        return *this;
    }

    std::swap(head_, copy_queuelst.head_);
    std::swap(tail_, copy_queuelst.tail_);
    return *this;
}

template<class T>
QueueLstT<T>::~QueueLstT() {
    if (head_ == nullptr) {
        return;
    }

    Node* to_delete = nullptr;
    while (head_ != nullptr) {
        to_delete = head_;
        head_ = head_->next_node;
        delete to_delete;
    }

    to_delete = nullptr;
    head_ = nullptr;
    return;
}

template<class T>
[[nodiscard]] bool QueueLstT<T>::IsEmpty() const noexcept {
    return head_ == nullptr;
}

template<class T>
[[nodiscard]] T& QueueLstT<T>::Top()& {
    if (IsEmpty()) {
        throw std::runtime_error("something bad happened");
    }
    return head_->value;
}

template<class T>
[[nodiscard]] const T& QueueLstT<T>::Top() const& {
    if (IsEmpty()) {
        throw std::runtime_error("something bad happened");
    }
    return head_->value;
}

template<class T>
void QueueLstT<T>::Pop() noexcept {
    if (IsEmpty()) {
        return;
    }

    Node* to_delete = head_;
    head_ = head_->next_node;
    if (head_ == nullptr) {
        tail_ = nullptr;
    }

    delete to_delete;
    return;
}

template<class T>
void QueueLstT<T>::Push(const T& n_elem) {
    Node* new_node = new Node(n_elem);

    if (tail_ != nullptr) {
        tail_->next_node = new_node;
    }
    tail_ = new_node;

    if (head_ == nullptr) {
        head_ = tail_;
    }
    return;
}

template<class T>
void QueueLstT<T>::Clear() noexcept {
    Node* to_delete = nullptr;
    while (head_ != nullptr) {
        to_delete = head_;
        head_ = head_->next_node;
        delete to_delete;
    }
    return;
}

template<class T>
QueueLstT<T>::Node::Node(const T& n_value) :
    value{ n_value }, next_node{ nullptr } {}



#endif // !QUEUELSTT_QUEUELSTT_HPP