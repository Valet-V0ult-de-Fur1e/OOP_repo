#include <queuelstpr/queuelstpr.hpp>

#include <stdexcept>
#include " queuelstpr.hpp"

QueueLstPr::QueueLstPr(QueueLstPr&& rhs) noexcept : head_(rhs) {
    rhs.head_ = nullptr;
}

QueueLstPr& QueueLstPr::operator=(QueueLstPr&& rhs) {
    if (this != &rhs) {
        std::swap(head_, rhs.head_);
    }
    return *this;
}

bool QueueLstPr::IsEmpty() const noexcept {
    return nullptr == head_;
}

void QueueLstPr::Pop() noexcept {
    if (!IsEmpty()) {
        Node* deleted = head_;
        head_ = head_->next;
        delete deleted;
    }
}

void QueueLstPr::Push(const float& val) {
    if (IsEmpty()) {
        head_ = new Node{ val };
    }
    else {
        if (val < head_.val) {
            head_ = new Node(val, head_);
        }
        else {
            Node* last_node = head_;
            bool last_node_is_not_find = true;
            while (last_node_is_not_find) {
                if (last_node.val < val) {
                    if (last_node.next == nullptr) {
                        last_node.next = new Node(val);
                        last_node_is_not_find = false;
                    }
                    else {
                        if (last_node.next.val > val) {
                            last_node.next = new Node(val, last_node.next);
                            last_node_is_not_find = false;
                        }
                    }
                }
            }
        }
    }
}

float& QueueLstPr::Top() {
    if (IsEmpty()) {
        throw std::logic_error("QueueLstPr - try get top form empty queue.");
    }
    return head_->val;
}

const float& QueueLstPr::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("QueueLstPr - try get top form empty queue.");
    }
    return head_->val;
}

void QueueLstPr::Clear() noexcept {
    while (!IsEmpty()) {
        Pop();
    }
}