#ifndef S21_CONTAINERS_STACK_H_
#define S21_CONTAINERS_STACK_H_

#include "../list/s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T>> class stack {
public:
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;
  using value_type = typename Container::value_type;

private:
  Container container_;

public:
  stack() = default;
  explicit stack(const Container &cont) : container_(cont) {}
  explicit stack(Container &&cont) : container_(std::move(cont)) {}
  stack(const stack &other) : container_(other.container_) {}
  stack(stack &&other) noexcept : container_(std::move(other.container_)) {}
  ~stack() {}

  stack &operator=(const stack &other) {
    if (this != &other) {
      container_ = other.container_;
    }
    return *this;
  }

  stack &operator=(stack &&other) noexcept {
    if (this != &other) {
      container_ = std::move(other.container_);
    }
    return *this;
  }

  std::string string() { return container_.string(); }

  reference top() { return container_.back(); }

  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }

  void push(const value_type &value) { container_.push_back(value); }
  void push(value_type &&value) { container_.push_back(value); }
  void pop() { container_.pop_back(); }
  template <class R> void push_range(R &&rg) {
    for (auto it = rg.begin(); it != rg.end(); ++it) {
      push(*it);
    }
  }
  void swap(stack &Other) { std::swap(container_, Other.container_); }
};
} // namespace s21

#endif