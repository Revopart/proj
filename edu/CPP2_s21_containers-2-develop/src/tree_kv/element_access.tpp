template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::mapped_value &
RedBlackTree<Key, T, Compare, Allocator>::operator[](key_type key) {
  node_type node = getNode(key);
  if (node == nullptr) {
    mapped_value value = mapped_value();
    auto res = insert(std::make_pair(key, value));
    return res.first->data_->second;
  }
  return node->data_->second;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::mapped_value &
RedBlackTree<Key, T, Compare, Allocator>::at(key_type key) {
  node_type node = getNode(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->data_->second;
}