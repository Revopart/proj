template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::key_type
RedBlackTree<Key, Compare, Allocator>::Node::getKey() {
  return *data_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Node *
RedBlackTree<Key, Compare, Allocator>::Node::getLeft() {
  return left_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Node *
RedBlackTree<Key, Compare, Allocator>::Node::getRight() {
  return right_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Node *
RedBlackTree<Key, Compare, Allocator>::Node::getParent() {
  return parent_;
}

template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::Node::isRed() {
  return color_ == RED;
}

template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::Node::isBlack() {
  return color_ == BLACK;
}

template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::Node::isLeftNode() {
  if (parent_ == nullptr) {
    return false;
  }
  return parent_->left_ == this;
}

template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::Node::isRightNode() {
  if (parent_ == nullptr) {
    return false;
  }
  return parent_->right_ == this;
}

template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::Node::isNotChild() {
  if (left_ == nullptr && right_ == nullptr) {
    return true;
  }
  return false;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::Node::node_type
RedBlackTree<Key, Compare, Allocator>::Node::getChildOrNull() {
  if (left_ != nullptr) {
    return left_;
  }
  if (right_ == nullptr) {
    return new Node();
  }
  return right_;
}

template <class Key, class Compare, class Allocator>
int RedBlackTree<Key, Compare, Allocator>::Node::getChildrenCount() {
  int result = 0;

  if (left_ != nullptr) {
    result++;
  }

  if (right_ != nullptr) {
    result++;
  }

  return result;
}