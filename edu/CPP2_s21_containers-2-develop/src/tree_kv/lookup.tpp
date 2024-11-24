template <class Key, class T, class Compare, class Allocator>
bool RedBlackTree<Key, T, Compare, Allocator>::contains(key_type key) {
  node_type node = getNode(key);
  if (node == nullptr) {
    return false;
  }
  return true;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::iterator
RedBlackTree<Key, T, Compare, Allocator>::find(key_type key) {
  node_type node = getNode(key);
  return Iterator(this, node, PROCESS);
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::const_iterator
RedBlackTree<Key, T, Compare, Allocator>::find(key_type key) const {
  node_type node = getNode(key);
  return Iterator(this, node, PROCESS);
}