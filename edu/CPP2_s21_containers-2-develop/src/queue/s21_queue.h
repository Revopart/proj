#ifndef S21_CONTAINERS_QUEUE_H_
#define S21_CONTAINERS_QUEUE_H_

#include "../list/s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T>> class queue {
public:
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;
  using value_type = typename Container::value_type;

private:
  Container container_;

public:
  queue() = default;
  explicit queue(const Container &cont) : container_(cont) {}
  explicit queue(Container &&cont) : container_(std::move(cont)) {}
  queue(const queue &other) : container_(other.container_) {}
  queue(queue &&other) noexcept : container_(std::move(other.container_)) {}
  ~queue() {}

  queue &operator=(const queue &other) {
    if (this != &other) {
      container_ = other.container_;
    }
    return *this;
  }

  queue &operator=(queue &&other) noexcept {
    if (this != &other) {
      container_ = std::move(other.container_);
    }
    return *this;
  }

  std::string string() { return container_.string(); }

  reference top() { return container_.front(); }

  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }

  void push(const value_type &value) { container_.push_back(value); }
  void push(value_type &&value) { container_.push_back(value); }
  void pop() { container_.pop_front(); }

  template <class R> void push_range(R &&rg) {
    for (auto it = rg.begin(); it != rg.end(); ++it) {
      push(*it);
    }
  }
  void swap(queue &Other) { std::swap(container_, Other.container_); }
};
} // namespace s21

#endif