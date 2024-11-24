template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::clear() {
  clearRecursive(root_);
  root_ = nullptr;
  length_ = 0;
}

template <class Key, class Compare, class Allocator>
std::pair<typename RedBlackTree<Key, Compare, Allocator>::iterator, bool>
RedBlackTree<Key, Compare, Allocator>::insert(key_type value) {
  node_type current = root_;
  node_type parent = nullptr;

  while (current != nullptr) {
    parent = current;
    if (value == *current->data_) {
      return std::make_pair(Iterator(this, current, PROCESS), false);
    }
    if (cmp_(value, *current->data_)) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  key_type *allocatedK = allocator_.allocate(1);
  allocator_.construct(allocatedK, value);

  node_type newNode = new Node(allocatedK);
  newNode->parent_ = parent;

  if (parent == nullptr) {
    root_ = newNode;
  } else if (cmp_(value, *parent->data_)) {
    parent->left_ = newNode;
  } else {
    parent->right_ = newNode;
  }

  balanceInsert(newNode);

  length_++;
  return std::make_pair(Iterator(this, newNode, PROCESS), true);
}

template <class Key, class Compare, class Allocator>
std::optional<typename RedBlackTree<Key, Compare, Allocator>::key_type>
RedBlackTree<Key, Compare, Allocator>::extract(key_type key) {
  node_type deletedNode = getNode(key);
  if (deletedNode == nullptr) {
    return std::nullopt;
  }
  key_type keyRes = *deletedNode->data_;
  if (deletedNode == root_ && length_ == 1) {
    allocator_.deallocate(root_->data_, 1);
    delete root_;
    root_ = nullptr;
    length_--;
    return keyRes;
  }
  bool isNotChild = false;
  bool isLeftNode = true;

  node_type child = nullptr;
  bool removedColor = deletedNode->color_;
  if (deletedNode->getChildrenCount() < 2) {
    child = deletedNode->getChildOrNull();
    isNotChild = deletedNode->isNotChild();
    if (isNotChild) {
      isLeftNode = deletedNode->isLeftNode();
    } else {
      isLeftNode = child->isLeftNode();
    }
    swapNode(deletedNode, child, isNotChild);
    allocator_.deallocate(deletedNode->data_, 1);
    delete deletedNode;
    deletedNode = nullptr;
  } else {
    node_type swappedRight = getRightSwappedNode(deletedNode->right_);
    *deletedNode->data_ = *swappedRight->data_;
    removedColor = swappedRight->color_;
    child = swappedRight->getChildOrNull();
    isNotChild = swappedRight->isNotChild();
    if (isNotChild) {
      isLeftNode = swappedRight->isLeftNode();
    } else {
      isLeftNode = child->isLeftNode();
    }
    swapNode(swappedRight, child, isNotChild);
    allocator_.deallocate(swappedRight->data_, 1);
    delete swappedRight;
    swappedRight = nullptr;
  }

  if (removedColor == BLACK) {
    balanceRemove(child, isLeftNode);
    if (isNotChild) {
      if (child->parent_->left_ == child) {
        child->parent_->left_ = nullptr;
      } else {
        child->parent_->right_ = nullptr;
      }
    }
  }
  if (isNotChild) {
    delete child;
    child = nullptr;
  }
  length_--;
  return keyRes;
}

template <class Key, class Compare, class Allocator>
std::optional<typename RedBlackTree<Key, Compare, Allocator>::key_type>
RedBlackTree<Key, Compare, Allocator>::extract(iterator position) {
  return extract(*position);
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::swap(RedBlackTree &other) {
  std::swap(allocator_, other.allocator_);
  std::swap(root_, other.root_);
  std::swap(cmp_, other.cmp_);
  std::swap(length_, other.length_);
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::size_type
RedBlackTree<Key, Compare, Allocator>::erase(iterator pos) {
  auto res = extract(pos);
  if (res.has_value()) {
    return 1;
  }
  return 0;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::size_type
RedBlackTree<Key, Compare, Allocator>::erase(key_type key) {
  auto res = extract(key);
  if (res.has_value()) {
    return 1;
  }
  return 0;
}

template <class Key, class Compare, class Allocator>
template <class InputIt>
void RedBlackTree<Key, Compare, Allocator>::insert(InputIt first,
                                                   InputIt last) {
  for (auto it = first; it != last; ++it) {
    insert(*it);
  }
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::insert(
    std::initializer_list<key_type> ilist) {
  for (auto elem : ilist) {
    insert(elem);
  }
}