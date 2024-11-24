
template <class Key, class T, class Compare, class Allocator>
RedBlackTree<Key, T, Compare, Allocator>::RedBlackTree()
    : root_(nullptr), length_(0), cmp_(Compare()), allocator_(Allocator()) {}

template <class Key, class T, class Compare, class Allocator>
RedBlackTree<Key, T, Compare, Allocator>::RedBlackTree(
    std::initializer_list<value_type> const &items)
    : root_(nullptr), length_(0), cmp_(Compare()), allocator_(Allocator()) {
  for (value_type item : items) {
    insert(item);
  }
}

template <class Key, class T, class Compare, class Allocator>
RedBlackTree<Key, T, Compare, Allocator>::RedBlackTree(RedBlackTree &other)
    : root_(nullptr), length_(0), cmp_(other.cmp_),
      allocator_(other.allocator_) {
  insert_range(other.begin(), other.end());
}

template <class Key, class T, class Compare, class Allocator>
RedBlackTree<Key, T, Compare, Allocator>::RedBlackTree(RedBlackTree &&other)
    : root_(std::exchange(other.root_, nullptr)),
      length_(std::exchange(other.length_, 0)), cmp_(std::move(other.cmp_)),
      allocator_(std::move(other.allocator_)) {}

template <class Key, class T, class Compare, class Allocator>
RedBlackTree<Key, T, Compare, Allocator>::~RedBlackTree() {
  clear();
}

template <class Key, class T, class Compare, class Allocator>
RedBlackTree<Key, T, Compare, Allocator> &
RedBlackTree<Key, T, Compare, Allocator>::operator=(RedBlackTree &&other) {
  if (this != &other) {
    clear();
    root_ = std::exchange(other.root_, nullptr);
    length_ = std::exchange(other.length_, 0);
    cmp_ = std::move(other.cmp_);
    allocator_ = std::move(other.allocator_);
  }
  return *this;
}

template <class Key, class T, class Compare, class Allocator>
RedBlackTree<Key, T, Compare, Allocator> &
RedBlackTree<Key, T, Compare, Allocator>::operator=(RedBlackTree &other) {
  if (this != &other) {
    clear();
    cmp_ = other.cmp_;
    allocator_ = other.allocator_;
    insert_range(other.begin(), other.end());
  }
  return *this;
}
