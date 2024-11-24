template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::key_compare
RedBlackTree<Key, Compare, Allocator>::key_comp() {
  return cmp_;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::allocator_type
RedBlackTree<Key, Compare, Allocator>::get_allocator() {
  return allocator_;
}