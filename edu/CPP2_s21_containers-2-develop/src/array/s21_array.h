#ifndef S21_CONTAINERS_ARRAY_H_
#define S21_CONTAINERS_ARRAY_H_

#include <functional>
#include <memory>

#define START 0
#define PROCESS 1
#define END 2

namespace s21 {
template <class T, std::size_t N> class array {
public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;

  class Iterator {
    friend array;

  private:
    array *array_;
    size_type index_;
    int position_;
    bool isReverse_;

  public:
    Iterator()
        : array_(nullptr), index_(0), position_(START), isReverse_(false) {}
    Iterator(array *v, size_type index, int pos, bool isReverse = false)
        : array_(v), index_(index), position_(pos), isReverse_(isReverse){};
    ~Iterator() {
      array_ = nullptr;
      index_ = 0;
      position_ = START;
    };
    Iterator(const Iterator &other) = default;
    Iterator &operator=(const Iterator &other) = default;

    bool operator==(const Iterator &other) {
      if (position_ != other.position_) {
        return false;
      }
      return index_ == other.index_;
    }
    bool operator!=(const Iterator &other) {
      if (position_ != other.position_) {
        return true;
      }
      return index_ != other.index_;
    }

    Iterator &next() {
      if (position_ == END) {
        return *this;
      } else if (position_ == START) {
        index_ = 0;
        position_ = PROCESS;
        return *this;
      }
      index_++;
      if (index_ == array_->size()) {
        index_--;
        position_ = END;
      }
      return *this;
    }
    Iterator &prev() {
      if (position_ == START) {
        return *this;
      } else if (position_ == END) {
        index_ = array_->size() - 1;
        position_ = PROCESS;
        return *this;
      }
      if (index_ == 0) {
        position_ = START;
      } else {
        index_--;
      }
      return *this;
    }

    Iterator &operator++() {
      if (isReverse_) {
        return prev();
      }
      return next();
    };
    Iterator &operator--() {
      if (isReverse_) {
        return next();
      }
      return prev();
    }
    reference operator*() { return array_->data_[index_]; };
    T *operator->() { return *array_->data_[index_]; };
  };

  using iterator = Iterator;
  using const_iterator = const Iterator;
  using reverse_iterator = iterator;
  using const_reverse_iterator = const_iterator;

private:
  T data_[N];

public:
  array() {
    for (size_type i = 0; i < N; i++) {
      data_[i] = T();
    }
  }; // Конструктор по умолчанию
  array(const array &other) : array() { // Конструктор копирования
    std::copy(other.data_, other.data_ + N, data_);
  }
  array(array &&other) noexcept : array() { // Конструктор перемещения
    std::move(other.data_, other.data_ + N, data_);
  }
  ~array() = default; // Деструктор
  array &operator=(const array &other) { // Оператор присваивания копированием
    if (this != &other) {
      std::copy(other.data_, other.data_ + N, data_);
    }
    return *this;
  }
  array &
  operator=(array &&other) noexcept { // Оператор присваивания перемещением
    if (this != &other) {
      std::move(other.data_, other.data_ + N, data_);
    }
    return *this;
  }

  // Element access
  T &at(size_type index) {
    if (index >= N) {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }
  T &operator[](size_type index) { return data_[index]; }
  T &front() { return data_[0]; }
  T &back() { return data_[N - 1]; }
  T *data() { return data_; }

  // Iterator
  iterator begin() { return Iterator(this, 0, PROCESS); }
  const_iterator cbegin() const { return Iterator(this, 0, PROCESS); }
  iterator end() { return Iterator(this, N - 1, END); }
  const_iterator end() const { return Iterator(this, N - 1, END); }
  iterator rbegin() { return Iterator(this, N - 1, PROCESS, true); }
  const_iterator crbegin() const {
    return Iterator(this, N - 1, PROCESS, true);
  }
  iterator rend() { return Iterator(this, 0, START, true); }
  const_iterator crend() const { return Iterator(this, 0, START, true); }

  // Capacity
  bool empty() { return N == 0; }
  size_type size() { return N; }
  size_type max_size() { return N; }

  // Operations
  void fill(const value_type &value) { std::fill(data_, data_ + N, value); }
  void swap(array &other) { std::swap_ranges(data_, data_ + N, other.data_); }
};
} // namespace s21

#endif