template <class Key, class T, class Compare, class Allocator>
bool RedBlackTree<Key, T, Compare, Allocator>::empty() {
  return length_ == 0;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::size_type
RedBlackTree<Key, T, Compare, Allocator>::size() {
  return length_;
}

template <class Key, class T, class Compare, class Allocator>
typename RedBlackTree<Key, T, Compare, Allocator>::size_type
RedBlackTree<Key, T, Compare, Allocator>::max_size() {
  return std::allocator_traits<Allocator>::max_size(allocator_);
}