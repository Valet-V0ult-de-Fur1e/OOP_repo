#include <complex/complex.hpp>
#include <stacklst/stacklst.hpp>

#include <stdexcept>

StackLst::StackLst(StackLst&& rhs) noexcept: head_(rhs.head_)
{
    rhs.head_ = nullptr;
}

StackLst& StackLst::operator=(StackLst&& rhs)
{
    if (this != &rhs) {
        std::swap(head_, rhs.head_);
    }
    return *this;
}

bool StackLst::IsEmpty() const noexcept {
    return head_ == nullptr;
}

void StackLst::Pop() noexcept {
    if (!IsEmpty()) {
        Node* old_head = head_;
        head_ = old_head->next;
        delete old_head;
    }
    else {
        throw std::logic_error("StackLst - try delete top form empty stack.");
    }
}

void StackLst::Push(const Complex& val) {
    head_ = new Node(val, head_);
}

const Complex& StackLst::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("StackLst - try get top form empty stack.");
    }
    return (head_->val);
}

Complex& StackLst::Top() {
    if (IsEmpty()) {
        throw std::logic_error("StackLst - try get top form empty stack.");
    }
    return head_->val;
}

void StackLst::Clear() noexcept {
    while (!IsEmpty())
    {
        Pop();
    }
}