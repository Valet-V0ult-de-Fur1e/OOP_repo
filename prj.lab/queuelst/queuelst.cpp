#include <complex/complex.hpp>
#include <queuelst/queuelst.hpp>
#include <stdexcept>

bool QueueLst::IsEmpty() const noexcept {
    return head_ == nullptr;
}

void QueueLst::Pop() noexcept {
    if (!IsEmpty()) {
        Node* deleted = head_;
        head_ = head_->next;
        delete deleted;
    }
    else {
        throw std::logic_error("QueueLst - try delete top form empty queue.");
    }
}

void QueueLst::Push(const Complex& val) {
    Node new_tail = *new Node(val, tail_);
    tail_->next = &new_tail;
    tail_ = &new_tail;
}

const Complex& QueueLst::Back() const {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get back form empty queue.");
    }
    return (tail_->val);
}

Complex& QueueLst::Back() {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get back form empty queue.");
    }
    return tail_->val;
}

const Complex& QueueLst::Front() const {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get front form empty queue.");
    }
    return (head_->val);
}

Complex& QueueLst::Front() {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get top front empty queue.");
    }
    return head_->val;
}

void QueueLst::Clear() noexcept {
    while (!IsEmpty())
    {
        Pop();
    }
}