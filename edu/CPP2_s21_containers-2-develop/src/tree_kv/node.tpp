template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::Node::node_type
RedBlackTree<Key, T, Compare, Allocator>::Node::getLeft() {
  return left_;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::Node::node_type
RedBlackTree<Key, T, Compare, Allocator>::Node::getRight() {
  return right_;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::Node::node_type
RedBlackTree<Key, T, Compare, Allocator>::Node::getParent() {
  return parent_;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::key_type
RedBlackTree<Key, T, Compare, Allocator>::Node::getKey() {
  return data_->first;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::key_type &
RedBlackTree<Key, T, Compare, Allocator>::Node::getKeyRef() {
  return const_cast<key_type &>(data_->first);
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::mapped_value
RedBlackTree<Key, T, Compare, Allocator>::Node::getValue() {
  return data_->second;
}

template <class Key, class T, class Compare, class Allocator>
int RedBlackTree<Key, T, Compare, Allocator>::Node::getChildrenCount() {
  int result = 0;

  if (left_ != nullptr) {
    result++;
  }

  if (right_ != nullptr) {
    result++;
  }

  return result;
}

template <class Key, class T, class Compare, class Allocator>
bool RedBlackTree<Key, T, Compare, Allocator>::Node::isBlack() {
  return color_ == BLACK;
}

template <class Key, class T, class Compare, class Allocator>
bool RedBlackTree<Key, T, Compare, Allocator>::Node::isRed() {
  return color_ == RED;
}

template <class Key, class T, class Compare, class Allocator>
bool RedBlackTree<Key, T, Compare, Allocator>::Node::isLeftNode() {
  if (parent_ == nullptr) {
    return false;
  }
  return parent_->left_ == this;
}

template <class Key, class T, class Compare, class Allocator>
bool RedBlackTree<Key, T, Compare, Allocator>::Node::isRightNode() {
  if (parent_ == nullptr) {
    return false;
  }
  return parent_->right_ == this;
}

template <class Key, class T, class Compare, class Allocator>
bool RedBlackTree<Key, T, Compare, Allocator>::Node::isNotChild() {
  if (left_ == nullptr && right_ == nullptr) {
    return true;
  }
  return false;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::Node::node_type
RedBlackTree<Key, T, Compare, Allocator>::Node::getChildOrNull() {
  if (left_ != nullptr) {
    return left_;
  }
  if (right_ == nullptr) {
    return new Node();
  }
  return right_;
}