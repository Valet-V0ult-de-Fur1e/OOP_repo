#include <complex/complex.hpp>
#include <queue/queue.hpp>
#include <stdexcept>

bool Queue::IsEmpty() const noexcept {
    return head_ == nullptr;
}

void Queue::Pop() noexcept {
    if (!IsEmpty()) {
        Node* deleted = head_;
        head_ = head_->next;
        delete deleted;
    }
    else {
        throw std::logic_error("Queue - try delete top form empty queue.");
    }
}

void Queue::Push(const Complex& val) {
    Node new_tail = *new Node(val, tail_);
    tail_->next = &new_tail;
    tail_ = &new_tail;
}

const Complex& Queue::Back() const {
    if (IsEmpty()) {
        throw std::logic_error("Queue - try get back form empty queue.");
    }
    return (tail_->val);
}

Complex& Queue::Back() {
    if (IsEmpty()) {
        throw std::logic_error("Queue - try get back form empty queue.");
    }
    return tail_->val;
}

const Complex& Queue::Front() const {
    if (IsEmpty()) {
        throw std::logic_error("Queue - try get front form empty queue.");
    }
    return (head_->val);
}

Complex& Queue::Front() {
    if (IsEmpty()) {
        throw std::logic_error("Queue - try get top front empty queue.");
    }
    return head_->val;
}

void Queue::Clear() noexcept {
    while (!IsEmpty())
    {
        Pop();
    }
}