#ifndef S21_CONTAINERS_VECTOR_H_
#define S21_CONTAINERS_VECTOR_H_

#include <functional>
#include <memory>

#define START 0
#define PROCESS 1
#define END 2
#define START_INIT_SIZE 2
#define BIG_DATA_EDGE 1000
#define RESIZE_EXP 2
#define BIG_DATA_RESIZE_EXP 4

namespace s21 {
template <class T, class Allocator = std::allocator<T>> class vector {
public:
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = typename Allocator::pointer;
  using const_pointer = typename Allocator::const_pointer;

  class Iterator {
    friend vector;

  private:
    vector *vector_;
    size_type index_;
    int position_;
    bool isReverse_;

  public:
    Iterator()
        : vector_(nullptr), index_(0), position_(START), isReverse_(false) {}
    Iterator(vector *v, size_type index, int pos, bool isReverse = false)
        : vector_(v), index_(index), position_(pos), isReverse_(isReverse){};
    ~Iterator() {
      vector_ = nullptr;
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
      if (index_ == vector_->size()) {
        index_--;
        position_ = END;
      }
      return *this;
    }
    Iterator &prev() {
      if (position_ == START) {
        return *this;
      } else if (position_ == END) {
        index_ = vector_->size() - 1;
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
    reference operator*() { return vector_->data_[index_]; };
    T *operator->() { return *vector_->data_[index_]; };
  };

  using iterator = Iterator;
  using const_iterator = const Iterator;
  using reverse_iterator = iterator;
  using const_reverse_iterator = const_iterator;

private:
  T *data_;
  size_type length_;
  size_type capacity_;
  allocator_type allocator_;

  bool isFull() {
    if (length_ == capacity_) {
      return true;
    }
    return false;
  }

  void resizeWithExp() {
    if (isFull()) {
      if (length_ >= BIG_DATA_EDGE) {
        resize(capacity_ * BIG_DATA_RESIZE_EXP);
      } else {
        resize(capacity_ * RESIZE_EXP);
      }
    }
  }

public:
  vector()
      : data_(nullptr), length_(0), capacity_(0), allocator_(Allocator()){};
  vector(size_type count, const T &value)
      : data_(nullptr), length_(0), capacity_(0), allocator_(Allocator()) {
    resize(count);
    for (size_type i = 0; i < count; ++i) {
      push_back(value);
    }
  };
  vector(size_type count)
      : data_(nullptr), length_(0), capacity_(0), allocator_(Allocator()) {
    resize(count);
  }
  vector(const vector &other)
      : data_(nullptr), length_(0), capacity_(0), allocator_(Allocator()) {
    clear();
    if (other.data_ != nullptr) {
      resize(other.capacity_);
      for (size_type i = 0; i < other.length_; ++i) {
        push_back(other.data_[i]);
      }
    }
  }
  vector(vector &&other)
      : data_(nullptr), length_(0), capacity_(0), allocator_(Allocator()) {
    clear();
    if (other.data_ != nullptr) {
      resize(other.capacity_);
      for (size_type i = 0; i < other.length_; ++i) {
        push_back(other.data_[i]);
      }
    }
    other.clear();
  }
  vector(std::initializer_list<T> init)
      : data_(nullptr), length_(0), capacity_(0), allocator_(Allocator()) {
    for (auto item : init) {
      push_back(item);
    }
  }
  ~vector() { clear(); }
  vector &operator=(const vector &other) {
    clear();
    if (other.data_ != nullptr) {
      resize(other.capacity_);
      for (size_type i = 0; i < other.length_; ++i) {
        push_back(other.data_[i]);
      }
    }
    return *this;
  }
  vector &operator=(vector &&other) {
    clear();
    if (other.data_ != nullptr) {
      resize(other.capacity_);
      for (size_type i = 0; i < other.length_; ++i) {
        push_back(other.data_[i]);
      }
    }
    other.clear();
    return *this;
  }
  vector &operator=(std::initializer_list<T> ilist) {
    clear();
    for (auto item : ilist) {
      push_back(item);
    }
    return *this;
  };

  // PRINT
  std::string string() {
    if (length_ == 0) {
      return "empty";
    }
    std::string str = "";

    for (auto it = this->begin(); it != this->end(); ++it) {
      if (str != "") {
        str += " ";
      }
      str += std::to_string(*it);
    }

    return str;
  }

  std::string
  stringWithCallback(std::function<std::string(value_type)> callback) {
    if (length_ == 0) {
      return "empty";
    }
    std::string str = "";

    for (auto it = this->begin(); it != this->end(); ++it) {
      if (str != "") {
        str += " ";
      }
      str += callback(*it);
    }

    return str;
  }

  // ELEMENT ACCESS
  T &at(size_type position) {
    if (position >= length_) {
      throw std::out_of_range("position out of range");
    }
    return data_[position];
  }
  T &operator[](size_type position) { return data_[position]; }
  value_type front() {
    if (empty()) {
      throw std::out_of_range("container empty");
    }
    return data_[0];
  }
  value_type back() {
    if (empty()) {
      throw std::out_of_range("container empty");
    }
    return data_[length_ - 1];
  }
  T *data() { return data_; }

  // Iterator
  iterator begin() { return Iterator(this, 0, PROCESS); }
  const_iterator cbegin() const { return Iterator(this, 0, PROCESS); }
  iterator end() { return Iterator(this, length_ - 1, END); }
  const_iterator end() const { return Iterator(this, length_ - 1, END); };
  iterator rbegin() { return Iterator(this, length_ - 1, PROCESS, true); }
  const_iterator crbegin() const {
    return Iterator(this, length_ - 1, PROCESS, true);
  }
  iterator rend() { return Iterator(this, 0, START, true); }
  const_iterator crend() const { return Iterator(this, 0, START, true); };

  // Modifier
  void clear() {
    if (data_ == nullptr) {
      return;
    }
    for (size_type i = 0; i < length_; ++i) {
      allocator_.destroy(data_ + i);
    }
    allocator_.deallocate(data_, capacity_);
    length_ = 0;
    capacity_ = 0;
    data_ = nullptr;
  }
  iterator insert(const_iterator pos, const T &value) {
    if (pos.position_ == END) {
      push_back(value);
      return Iterator(this, length_ - 1, END);
    }
    auto tmp = data_[pos.index_];
    data_[pos.index_] = value;
    for (auto i = pos.index_ + 1; i < length_; ++i) {
      auto tmpInner = data_[i];
      data_[i] = tmp;
      tmp = tmpInner;
    }
    push_back(tmp);
    return Iterator(this, pos.index_ + 1, PROCESS);
  }
  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      insert(pos, *it);
    }
    return pos;
  }
  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    iterator it = pos;
    for (auto el : ilist) {
      it = insert(pos, el);
    }
    return it;
  };
  template <class R> void insert_range(R &&rg) {
    for (auto it = rg.begin(); it != rg.end(); ++it) {
      push_back(*it);
    }
  }
  iterator erase(iterator pos) {
    auto prev = pos.index_;
    for (auto i = pos.index_ + 1; i < length_; i++) {
      data_[prev] = data_[i];
      prev = i;
    }
    length_--;
    return pos;
  }
  iterator erase(iterator first, iterator last) {
    for (auto i = first.index_; i < last.index_; i++) {
      erase(first);
    }
    return first;
  }
  void push_back(const T &value) {
    if (data_ == nullptr) {
      data_ = allocator_.allocate(START_INIT_SIZE);
      allocator_.construct(data_, value);
      length_++;
      capacity_ = START_INIT_SIZE;
      return;
    }
    resizeWithExp();
    allocator_.construct(data_ + length_, value);
    length_++;
  }
  template <class R> void append_range(R &&rg) {
    for (auto it = rg.begin(); it != rg.end(); ++it) {
      push_back(*it);
    }
  }

  void pop_back() { --length_; }
  void resize(size_type count) {
    if (count < length_) {
      return;
    }
    T *newData = allocator_.allocate(count);

    if (data_ != nullptr) {
      for (size_type i = 0; i < length_; ++i) {
        allocator_.construct(newData + i, std::move_if_noexcept(data_[i]));
      }

      for (size_type i = 0; i < length_; ++i) {
        allocator_.destroy(data_ + i);
      }
      allocator_.deallocate(data_, capacity_);
    }

    data_ = newData;
    capacity_ = count;
  }
  void clip() {
    if (length_ == 0) {
      clear();
    }
    resize(length_);
  }
  void swap(vector &other) {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(length_, other.length_);
  }

  // CAPACITY
  size_type cap() { return capacity_; }
  bool empty() { return length_ == 0; }
  size_type size() { return length_; }
  size_type max_size() {
    return std::allocator_traits<Allocator>::max_size(allocator_);
  }
};
} // namespace s21

#endif
