#include <complex/complex.hpp>
#include <stacklst/stacklst.hpp>

#include <stdexcept>

StackLst::StackLst(const StackLst& stack) {
  CopyStack(stack);
}

StackLst::StackLst(StackLst&& stack) noexcept {
  std::swap(top_, stack.top_);
}

StackLst::~StackLst() {
  Clear();
}

StackLst& StackLst::operator=(const StackLst& stack) {
  if (top_ == stack.top_) {
    return *(this);
  }
  else {
    if (stack.IsEmpty()) {
      Clear();
    }
    else if (IsEmpty()) {
      CopyStack(stack);
    }
    else {
      Node* temp_child = top_;
      Node* temp_parent = stack.top_;
      temp_child->data_ = temp_parent->data_;
      while ((temp_child->next_ != nullptr) && (temp_parent->next_ != nullptr)) {
        temp_child->data_ = temp_parent->data_;
        temp_child = temp_child->next_;
        temp_parent = temp_parent->next_;
      }
      if ((temp_parent->next_ == nullptr) && (temp_child->next_ != nullptr)) {
        Node* temp = temp_child->next_;
        temp_child->next_ = nullptr;
        while (temp_child != nullptr) {
          temp_child = temp->next_;
          delete temp;
          temp = temp_child;
        }
      }
      if ((temp_parent->next_ != nullptr) && (temp_child->next_ == nullptr)) {
        while (temp_parent->next_ != nullptr) {
          temp_child->next_ = new Node(temp_parent->next_->data_);
          temp_child = temp_child->next_;
          temp_parent = temp_parent->next_;
        }
      }
    }
    return *(this);
  }
}

StackLst& StackLst::operator=(StackLst&& stack) noexcept {
  std::swap(top_, stack.top_);

  return *this;
}

void StackLst::Push(const Complex& data) {
  Node* temp = new Node(data);
  temp->next_ = top_;
  top_ = temp;
}

void StackLst::Pop() noexcept {
    if (!IsEmpty()) {
        Node* temp = top_;
        top_ = temp->next_;
        delete temp;
    }
    else {
            throw std::logic_error("StackLst - try delete top form empty stack.");
    }
}

void StackLst::Clear() noexcept {
    while (!IsEmpty())
    {
        Pop();
    }
}

Complex& StackLst::Top() const {
  if (IsEmpty()) {
    throw std::logic_error("StackLst - try get top form empty stack.");
  }
  else {
    return top_->data_;
  }
}

bool StackLst::IsEmpty() const noexcept {
  return (top_ == nullptr);
}

void StackLst::CopyStack(const StackLst& stack) {
  if (!stack.IsEmpty()) {
    top_ = new Node(stack.top_->data_);
    Node* temp_parent = stack.top_->next_;
    Node* temp_child = top_;
    while (temp_parent != nullptr) {
      temp_child->next_ = new Node(temp_parent->data_);
      temp_child = temp_child->next_;
      temp_parent = temp_parent->next_;
    }
  }
  else {
    top_ = nullptr;
  }
}