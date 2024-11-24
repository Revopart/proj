template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::Iterator::operator==(
    const Iterator &other) {
  if (node_ == nullptr && other.node_ == nullptr) {
    if (position_ == other.position_) {
      return true;
    }
    return false;
  }
  if (node_ == nullptr || other.node_ == nullptr) {
    return false;
  }
  return node_->data_ == other.node_->data_;
}

template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::Iterator::operator!=(
    const Iterator &other) {
  if (node_ == nullptr && other.node_ == nullptr) {
    if (position_ != other.position_) {
      return true;
    }
    return false;
  }
  if (node_ == nullptr || other.node_ == nullptr) {
    return true;
  }
  return node_->data_ != other.node_->data_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::key_type
RedBlackTree<Key, Compare, Allocator>::Iterator::operator*() {
  return *node_->data_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::node_type
RedBlackTree<Key, Compare, Allocator>::Iterator::getNode() {
  return node_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::key_type *
RedBlackTree<Key, Compare, Allocator>::Iterator::operator->() {
  return &(node_->data_);
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::iterator
RedBlackTree<Key, Compare, Allocator>::begin() {
  return Iterator(this, left(), PROCESS);
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::iterator
RedBlackTree<Key, Compare, Allocator>::end() {
  iterator it(this, nullptr, START);
  it.end();
  return it;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::const_iterator
RedBlackTree<Key, Compare, Allocator>::cbegin() {
  return Iterator(this, left(), PROCESS);
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::const_iterator
RedBlackTree<Key, Compare, Allocator>::cend() {
  iterator it(this, nullptr, START);
  it.end();
  return it;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::node_type
RedBlackTree<Key, Compare, Allocator>::left() {
  if (length_ == 0) {
    return nullptr;
  }
  node_type current = root_;
  while (current->left_ != nullptr) {
    current = current->left_;
  }
  return current;
}
template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::node_type
RedBlackTree<Key, Compare, Allocator>::right() {
  if (length_ == 0) {
    return nullptr;
  }
  node_type current = root_;
  while (current->right_ != nullptr) {
    current = current->right_;
  }
  return current;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Iterator
RedBlackTree<Key, Compare, Allocator>::Iterator::next() {
  if (position_ == END) {
    return *this;
  }
  if (position_ == START) {
    if (tree_->size() == 0) {
      return *this;
    }
    node_ = tree_->left();
    position_ = PROCESS;
    return *this;
  }
  if (node_->right_ != nullptr) {
    node_ = node_->right_;
    while (node_->left_ != nullptr) {
      node_ = node_->left_;
    }
    return *this;
  }
  while (node_->parent_ != nullptr) {
    node_type tmp_node = node_;
    node_ = node_->parent_;
    if (tmp_node == node_->left_) {
      return *this;
    }
  }
  node_ = nullptr;
  position_ = END;
  return *this;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Iterator
RedBlackTree<Key, Compare, Allocator>::Iterator::prev() {
  if (position_ == START) {
    return *this;
  }
  if (position_ == END) {
    if (tree_->size() == 0) {
      return *this;
    }
    node_ = tree_->right();
    position_ = PROCESS;
    return *this;
  }
  if (node_->left_ != nullptr) {
    node_ = node_->left_;
    while (node_->right_ != nullptr) {
      node_ = node_->right_;
    }
    return *this;
  }
  while (node_->parent_ != nullptr) {
    node_type tmp_node = node_;
    node_ = node_->parent_;
    if (tmp_node == node_->right_) {
      return *this;
    }
  }

  node_ = nullptr;
  position_ = START;
  return *this;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Iterator
RedBlackTree<Key, Compare, Allocator>::Iterator::operator--() {
  if (!is_reverse_) {
    return prev();
  } else {
    return next();
  }
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Iterator
RedBlackTree<Key, Compare, Allocator>::Iterator::operator++() {
  if (!is_reverse_) {
    return next();
  } else {
    return prev();
  }
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::Iterator::start() {
  node_ = nullptr;
  position_ = START;
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::Iterator::end() {
  node_ = nullptr;
  position_ = END;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Iterator
RedBlackTree<Key, Compare, Allocator>::Iterator::first() {
  start();
  return ++(*this);
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Iterator
RedBlackTree<Key, Compare, Allocator>::Iterator::last() {
  end();
  return --(*this);
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::reverse_iterator
RedBlackTree<Key, Compare, Allocator>::rbegin() {
  return Iterator(this, right(), PROCESS, true);
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::reverse_iterator
RedBlackTree<Key, Compare, Allocator>::rend() {
  iterator it(this, nullptr, START, true);
  it.start();
  return it;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::const_reverse_iterator
RedBlackTree<Key, Compare, Allocator>::crbegin() {
  return Iterator(this, right(), PROCESS, true);
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::const_reverse_iterator
RedBlackTree<Key, Compare, Allocator>::crend() {
  iterator it(this, nullptr, START, true);
  it.start();
  return it;
}
