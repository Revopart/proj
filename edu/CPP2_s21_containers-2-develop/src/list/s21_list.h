#ifndef S21_CONTAINERS_LIST_H_
#define S21_CONTAINERS_LIST_H_

#define START 0
#define PROCESS 1
#define END 2

#include <memory>
#include <utility>

namespace s21 {
template <class T, class Allocator = std::allocator<T>> class list {
public:
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;

  class Node {
    friend list;

  private:
    value_type *value_;
    Node *prev_;
    Node *next_;

  public:
    Node(value_type *val) : value_(val), prev_(nullptr), next_(nullptr) {}

    value_type value() { return value_; }
    Node *next() { return next_; }
    Node *prev() { return prev_; }
  };

  class Iterator {
    friend list;

  private:
    list *list_;
    Node *current_;
    int position_;
    bool isReverse_;

  public:
    Iterator()
        : list_(nullptr), current_(nullptr), position_(START),
          isReverse_(false) {}
    Iterator(list *l, Node *current, int pos, bool isReverse = false)
        : list_(l), current_(current), position_(pos), isReverse_(isReverse){};
    ~Iterator() {
      list_ = nullptr;
      current_ = nullptr;
      position_ = START;
    };
    Iterator(const Iterator &other) = default;
    Iterator &operator=(const Iterator &other) = default;

    bool operator==(const Iterator &other) {
      if (position_ != other.position_) {
        return false;
      }
      return current_ == other.current_;
    }
    bool operator!=(const Iterator &other) {
      if (position_ != other.position_) {
        return true;
      }
      return current_ != other.current_;
    }

    Iterator &next() {
      if (position_ == END) {
        return *this;
      } else if (position_ == START) {
        current_ = list_->head_;
        position_ = PROCESS;
        return *this;
      }
      current_ = current_->next_;
      if (current_ == nullptr) {
        position_ = END;
      }
      return *this;
    }
    Iterator &prev() {
      if (position_ == START) {
        return *this;
      } else if (position_ == END) {
        current_ = list_->tail_;
        position_ = PROCESS;
        return *this;
      }
      current_ = current_->prev_;
      if (current_ == nullptr) {
        position_ = START;
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
    reference operator*() { return *current_->value_; };
    T *operator->() { return *(*current_->value_); }
  };

  using iterator = Iterator;
  using const_iterator = const Iterator;

private:
  Node *head_;
  Node *tail_;
  size_type length_;
  allocator_type allocator_;

public:
  // CONSTRUCTORS
  list()
      : head_(nullptr), tail_(nullptr), length_(0), allocator_(Allocator()){};
  list(int count, const T &value = T(), const Allocator &alloc = Allocator())
      : head_(nullptr), tail_(nullptr), length_(0), allocator_(alloc) {
    for (int i = 0; i < count; ++i) {
      push_back(value);
    }
  }
  template <class InputIt>
  list(InputIt first, InputIt last, allocator_type alloc = Allocator())
      : head_(nullptr), tail_(nullptr), length_(0), allocator_(alloc) {
    for (auto it = first; it != last; ++it) {
      push_back(*it);
    }
  }
  list(list &other, allocator_type alloc = Allocator())
      : head_(nullptr), tail_(nullptr), length_(0), allocator_(alloc) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
  }
  list(const list &other, allocator_type alloc = Allocator())
      : head_(nullptr), tail_(nullptr), length_(0), allocator_(alloc) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
  }
  list(list &&other)
      : head_(std::exchange(other.head_, nullptr)),
        tail_(std::exchange(other.tail_, nullptr)),
        length_(std::exchange(other.length_, 0)),
        allocator_(std::move(other.allocator_)) {}
  list(std::initializer_list<T> init, allocator_type alloc = Allocator())
      : head_(nullptr), tail_(nullptr), length_(0), allocator_(alloc) {
    for (auto val : init) {
      push_back(val);
    }
  }
  template <class R>
  list(R &&rg, const Allocator &alloc = Allocator())
      : head_(nullptr), tail_(nullptr), length_(0), allocator_(alloc) {
    for (auto it = std::begin(rg); it != std::end(rg); ++it) {
      push_back(*it);
    }
  }

  ~list() { clear(); };

  list &operator=(list &other) {
    if (this != &other) {
      clear();
      allocator_ = other.allocator_;
      for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
      }
    }
    return *this;
  }
  list &operator=(list &&other) {
    if (this != &other) {
      clear();
      head_ = std::exchange(other.head_, nullptr);
      tail_ = std::exchange(other.tail_, nullptr);
      length_ = std::exchange(other.length_, 0);
      allocator_ = std::move(other.allocator_);
    }
    return *this;
  }
  list &operator=(std::initializer_list<T> ilist) {
    clear();
    for (auto val : ilist) {
      push_back(val);
    }
    return *this;
  }

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

  // iterators
  iterator begin() { return Iterator(this, head_, PROCESS); }
  const_iterator cbegin() const { return Iterator(this, head_, PROCESS); }
  iterator end() { return Iterator(this, nullptr, END); }
  const_iterator end() const { return Iterator(this, nullptr, END); };
  iterator rbegin() { return Iterator(this, tail_, PROCESS, true); }
  const_iterator crbegin() const {
    return Iterator(this, tail_, PROCESS, true);
  }
  iterator rend() { return Iterator(this, nullptr, START, true); }
  const_iterator crend() const { return Iterator(this, nullptr, START, true); };

  // modifier - omit(resize)
  void clear() {
    Node *prev = nullptr;
    Node *curr = head_;
    while (curr != nullptr) {
      if (prev != nullptr) {
        allocator_.deallocate(prev->value_, 1);
        delete prev;
      }
      prev = curr;
      curr = curr->next_;
    }
    if (prev != nullptr) {
      allocator_.deallocate(prev->value_, 1);
      delete prev;
    }
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
  }

  iterator insert(const_iterator &pos, const_reference value) {
    if (pos.position_ == START || pos.current_ == head_) {
      push_front(value);
      return Iterator(this, head_, PROCESS);
    } else if (pos.position_ == END) {
      push_back(value);
      return Iterator(this, tail_, PROCESS);
    }
    for (auto it = begin(); it != end(); ++it) {
      if (it == pos) {
        value_type *newValue = allocator_.allocate(1);
        allocator_.construct(newValue, value);
        Node *newNode = new Node(newValue);
        newNode->prev_ = it.current_->prev_;
        newNode->next_ = it.current_;
        newNode->prev_->next_ = newNode;
        newNode->next_->prev_ = newNode;
        length_++;
        return Iterator(this, newNode, PROCESS);
      }
    }
    return Iterator();
  }

  iterator insert(const_iterator &pos, int count, const_reference value) {
    iterator iter = Iterator();
    for (int i = 0; i < count; i++) {
      iter = insert(pos, value);
    }
    return iter;
  }

  template <class InputIt>
  iterator insert(const_iterator &pos, InputIt first, InputIt last) {
    iterator iter = Iterator();
    for (auto it = first; it != last; ++it) {
      iter = insert(pos, *it);
    }
    return iter;
  }
  iterator insert(const_iterator &pos, std::initializer_list<T> ilist) {
    iterator iter = Iterator();
    for (auto val : ilist) {
      iter = insert(pos, val);
    }
    return iter;
  }

  template <class R> iterator insert_range(const_iterator &pos, R &&rg) {
    iterator iter = Iterator();
    for (auto it = rg.begin(); it != rg.end(); ++it) {
      iter = insert(pos, *it);
    }
    return iter;
  }

  iterator erase(iterator &pos) {
    if (pos.position_ == START || pos.position_ == END) {
      return pos;
    }

    if (pos.current_ == head_) {
      pop_front();
      return Iterator(this, head_, PROCESS);
    } else if (pos.current_ == tail_) {
      pop_back();
      return Iterator(this, nullptr, END);
    }
    auto prevNode = pos.current_->prev_;
    auto nextNode = pos.current_->next_;
    prevNode->next_ = nextNode;
    nextNode->prev_ = prevNode;
    allocator_.deallocate(pos.current_->value_, 1);
    delete pos.current_;
    length_--;
    return Iterator(this, nextNode, PROCESS);
  }

  iterator erase(const_iterator &pos) {
    if (pos.position_ == START || pos.position_ == END) {
      return pos;
    }
    if (pos.current_ == head_) {
      pop_front();
      return Iterator(this, head_, PROCESS);
    } else if (pos.current_ == tail_) {
      pop_back();
      return Iterator(this, nullptr, END);
    }
    auto prevNode = pos.current_->prev_;
    auto nextNode = pos.current_->next_;
    prevNode->next_ = nextNode;
    nextNode->prev_ = prevNode;
    allocator_.deallocate(pos.current_->value_, 1);
    delete pos.current_;
    length_--;
    return Iterator(this, nextNode, PROCESS);
  }
  iterator erase(iterator &first, iterator &last) {
    iterator iter = first;
    for (; iter != last;) {
      iter = erase(iter);
    }
    return iter;
  }
  iterator erase(const_iterator &first, const_iterator &last) {
    iterator iter = first;
    for (; iter != last;) {
      iter = erase(iter);
    }
    return iter;
  }

  void push_back(const_reference value) {
    value_type *newValue = allocator_.allocate(1);
    allocator_.construct(newValue, value);
    Node *newNode = new Node(newValue);
    if (length_ == 0) {
      tail_ = newNode;
      head_ = newNode;
    } else {
      newNode->prev_ = tail_;
      tail_->next_ = newNode;
      tail_ = newNode;
    }
    length_++;
  }

  template <typename R> void append_range(R &&rg) {
    for (auto it = rg.begin(); it != rg.end(); ++it) {
      push_back(*it);
    }
  }

  void pop_back() {
    if (length_ == 0) {
      return;
    }
    if (length_ == 1) {
      allocator_.deallocate(head_->value_, 1);
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      tail_ = tail_->prev_;
      allocator_.deallocate(tail_->next_->value_, 1);
      delete tail_->next_;
      tail_->next_ = nullptr;
    }
    length_--;
  }

  void push_front(const_reference value) {
    value_type *newValue = allocator_.allocate(1);
    allocator_.construct(newValue, value);
    Node *newNode = new Node(newValue);
    if (length_ == 0) {
      tail_ = newNode;
      head_ = newNode;
    } else {
      newNode->next_ = head_;
      head_->prev_ = newNode;
      head_ = newNode;
    }
    length_++;
  }

  template <typename R> void prepend_range(R &&rg) {
    for (auto it = rg.rbegin(); it != rg.rend(); ++it) {
      push_front(*it);
    }
  }

  void pop_front() {
    if (length_ == 0) {
      return;
    }
    if (length_ == 1) {
      allocator_.deallocate(head_->value_, 1);
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      head_ = head_->next_;
      allocator_.deallocate(head_->prev_->value_, 1);
      delete head_->prev_;
      head_->prev_ = nullptr;
    }
    length_--;
  }

  void swap(list &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(length_, other.length_);
    std::swap(allocator_, other.allocator_);
  }

  // element access
  value_type front() { return head_->value; }
  value_type back() { return tail_->value; }

  // operations
  void merge(list &other) {
    if (other.head_ == nullptr) {
      return;
    }
    if (head_ == nullptr) {
      head_ = other.head_;
      tail_ = other.tail_;
      length_ = other.length_;
      allocator_ = other.allocator_;
    } else {
      tail_->next_ = other.head_;
      other.head_ = tail_;
      tail_ = other.tail_;
      length_ += other.length_;
    }

    other.tail_ = nullptr;
    other.head_ = nullptr;
    other.length_ = 0;
  }

  void merge(list &&other) {
    if (other.head_ == nullptr) {
      return;
    }
    if (head_ == nullptr) {
      head_ = other.head_;
      tail_ = other.tail_;
      length_ = other.length_;
      allocator_ = other.allocator_;
    } else {
      tail_->next_ = other.head_;
      other.head_ = tail_;
      tail_ = other.tail_;
      length_ += other.length_;
    }

    other.tail_ = nullptr;
    other.head_ = nullptr;
    other.length_ = 0;
  }

  void reverse() {
    if (length_ == 0 || length_ == 1) {
      return;
    }
    iterator it = begin();
    iterator rit = rbegin();
    for (size_type i = 0; i < length_ / 2; i++) {
      auto tmp = it.current_->value_;
      it.current_->value_ = rit.current_->value_;
      rit.current_->value_ = tmp;
      ++it;
      ++rit;
    }
  }

  // capacity
  size_type size() { return length_; }
  bool empty() { return length_ == 0; }
  size_type max_size() {
    return std::allocator_traits<Allocator>::max_size(allocator_);
  }
};
} // namespace s21

#endif