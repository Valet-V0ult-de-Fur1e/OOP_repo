#include <complex/complex.hpp>
#include <queuelst/queuelst.hpp>
#include <stdexcept>

QueueLst::QueueLst(const QueueLst& queue) {
  CopyQueue(queue);
}

QueueLst::QueueLst(QueueLst&& queue) noexcept {
  std::swap(head_, queue.head_);
  tail_ = queue.tail_;
}

QueueLst::~QueueLst() {
  Clear();
}

QueueLst& QueueLst::operator=(const QueueLst& queue) {
  if (head_ == queue.head_) {
    return *(this);
  }
  else {
    if (queue.IsEmpty()) {
      Clear();
    }
    else if (IsEmpty()) {
      CopyQueue(queue);
    }
    else {
      head_->data_ = queue.head_->data_;
      Node* parent = queue.head_;
      Node* child = head_;
      while ((parent->next_ != nullptr) && (child->next_ != nullptr)) {
        child->data_ = parent->data_;
        child = child->next_;
        parent = parent->next_;
      }
      child->data_ = parent->data_;
      if ((parent->next_ != nullptr) && (child->next_ == nullptr)) {
        while (parent->next_ != nullptr) {
          child->next_ = new Node(parent->next_->data_);
          child = child->next_;
          parent = parent->next_;
        }
      }
      tail_ = child;
      if ((parent->next_ == nullptr) && (child->next_ != nullptr)) {
        Node* temp = child->next_;
        child->next_ = nullptr;
        while (child != nullptr) {
          child = temp->next_;
          delete temp;
          temp = child;
        }
      }
    }
    return *(this);
  }
}

QueueLst& QueueLst::operator=(QueueLst&& rhs) noexcept
{
    if (this != &rhs) {
        std::swap(head_, rhs.head_);
        std::swap(tail_, rhs.tail_);
    }
    return *this;
}

bool QueueLst::IsEmpty() const noexcept {
    return head_ == nullptr;
}

void QueueLst::Pop() noexcept {
    if (!IsEmpty()) {
        Node* deleted = head_;
        head_ = head_->next_;
        delete deleted;
    }
    else {
        throw std::logic_error("QueueLst - try delete top form empty queue.");
    }
}

void QueueLst::Push(const Complex& data) {
  if (IsEmpty()) {
    tail_ = new Node(data);
    head_ = tail_;
  }
  else {
    tail_->next_ = new Node(data);
    tail_ = tail_->next_;
  }
}

const Complex& QueueLst::Back() const {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get back form empty queue.");
    }
    return (tail_->data_);
}

Complex& QueueLst::Back() {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get back form empty queue.");
    }
    return tail_->data_;
}

const Complex& QueueLst::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get front form empty queue.");
    }
    return (head_->data_);
}

Complex& QueueLst::Top() {
    if (IsEmpty()) {
        throw std::logic_error("QueueLst - try get top front empty queue.");
    }
    return head_->data_;
}

void QueueLst::Clear() noexcept {
    while (!IsEmpty())
    {
        Pop();
    }
}

void QueueLst::CopyQueue(const QueueLst& queue) {
  if (!queue.IsEmpty()) {
    head_ = new Node(queue.head_->data_);
    tail_ = head_;
    Node* temp = queue.head_->next_;
    while (temp != nullptr) {
      tail_->next_ = new Node(temp->data_);
      tail_ = tail_->next_;
      temp = temp->next_;
    }
  }
  else {
    head_ = nullptr;
    tail_ = nullptr;
  }
}