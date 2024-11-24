template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::node_type
RedBlackTree<Key, Compare, Allocator>::getNode(key_type key) {
  node_type current = root_;

  while (current != nullptr) {
    if (key == *current->data_) {
      return current;
    }
    if (cmp_(key, *current->data_)) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  return nullptr;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::node_type
RedBlackTree<Key, Compare, Allocator>::getNode(
    key_type key, std::function<bool(node_type current)> callback) {
  node_type current = root_;

  while (current != nullptr) {
    if (callback(current)) {
      return current;
    }
    if (cmp_(key, *current->data_)) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  return nullptr;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::reference
RedBlackTree<Key, Compare, Allocator>::at(const_reference key) {
  node_type node = getNode(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->data_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::reference
RedBlackTree<Key, Compare, Allocator>::operator[](const_reference key) {
  node_type node = getNode(key);
  if (node == nullptr) {
    key_type value = key_type();
    insert(value);
    return value;
  }
  return node->data_;
}