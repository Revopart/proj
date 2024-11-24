template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::empty() {
  return length_ == 0;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::size_type
RedBlackTree<Key, Compare, Allocator>::size() {
  return length_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::size_type
RedBlackTree<Key, Compare, Allocator>::max_size() {
  return std::allocator_traits<Allocator>::max_size(allocator_);
}