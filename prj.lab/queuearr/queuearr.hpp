#ifndef QUEUEARR_QUEUEARR_HPP
#define QUEUEARR_QUEUEARR_HPP

#include<complex/complex.hpp>
#include<cstddef>
#include<memory>

class QueueArr
{
public:
  QueueArr() = default;
  QueueArr(const QueueArr& queue);
  QueueArr(QueueArr&& queue) noexcept;

  ~QueueArr() = default;

  QueueArr& operator=(const QueueArr& queue);
  QueueArr& operator=(QueueArr&& queue) noexcept;

  void Push(const Complex& data);
  void Pop() noexcept;
  void Clear() noexcept;

  Complex& Top();
  const Complex& Top() const;
  bool IsEmpty() const noexcept;

private:
  void reallocate(std::ptrdiff_t size, const QueueArr& source);

  Complex* head_ = nullptr;
  Complex* tail_ = nullptr;

  std::unique_ptr<Complex[]> data_ = nullptr;
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
private:
  std::ptrdiff_t Count() const;
};

#endif // !QUEUEARR_QUEUEARR_HPP