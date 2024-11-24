template <class Key, class T, class Compare, class Allocator>
std::pair<typename RedBlackTree<Key, T, Compare, Allocator>::node_type, bool>
RedBlackTree<Key, T, Compare, Allocator>::insert(value_type pair) {
  node_type current = root_;
  node_type parent = nullptr;

  while (current != nullptr) {
    parent = current;
    if (pair.first == current->data_->first) {
      return std::make_pair(current, false);
    }
    if (cmp_(pair.first, current->data_->first)) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  std::pair<const key_type, mapped_value> *allocatedKV = allocator_.allocate(1);
  allocator_.construct(allocatedKV, pair);

  node_type newNode = new Node(allocatedKV);
  newNode->parent_ = parent;

  if (parent == nullptr) {
    root_ = newNode;
  } else if (cmp_(pair.first, parent->data_->first)) {
    parent->left_ = newNode;
  } else {
    parent->right_ = newNode;
  }

  balanceInsert(newNode);

  length_++;
  return std::make_pair(newNode, true);
}

template <class Key, class T, class Compare, class Allocator>
std::pair<typename RedBlackTree<Key, T, Compare, Allocator>::node_type, bool>
RedBlackTree<Key, T, Compare, Allocator>::insert_or_assign(value_type pair) {
  std::pair<node_type, bool> result = insert(pair);
  if (!result.second) {
    result.first->data_->second = pair.second;
  }
  return result;
}

template <class Key, class T, class Compare, class Allocator>
template <class InputIt>
void RedBlackTree<Key, T, Compare, Allocator>::insert_range(InputIt first,
                                                            InputIt last) {
  for (auto it = first; it != last; ++it) {
    node_type node = it.getNode();
    insert(std::make_pair(node->data_->first, node->data_->second));
  }
}

template <class Key, class T, class Compare, class Allocator>
int RedBlackTree<Key, T, Compare, Allocator>::erase(key_type key) {
  std::optional<value_type> res = extract(key);
  if (res.has_value()) {
    return 1;
  }
  return 0;
}

template <class Key, class T, class Compare, class Allocator>
std::optional<typename RedBlackTree<Key, T, Compare, Allocator>::value_type>
RedBlackTree<Key, T, Compare, Allocator>::extract(key_type key) {
  node_type deletedNode = getNode(key);
  if (deletedNode == nullptr) {
    return std::nullopt;
  }
  key_type keyRes = deletedNode->data_->first;
  mapped_value valueRes = deletedNode->data_->second;
  if (deletedNode == root_ && length_ == 1) {
    allocator_.deallocate(root_->data_, 1);
    delete root_;
    root_ = nullptr;
    length_--;
    return std::make_pair(keyRes, valueRes);
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
    const_cast<Key &>(deletedNode->data_->first) = swappedRight->data_->first;
    deletedNode->data_->second = swappedRight->data_->second;
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
  return std::make_pair(keyRes, valueRes);
}

template <class Key, class T, class Compare, class Allocator>
void RedBlackTree<Key, T, Compare, Allocator>::clear() {
  clearRecursive(root_);
  root_ = nullptr;
  length_ = 0;
}