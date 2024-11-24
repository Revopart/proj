template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::clearRecursive(node_type node) {
  if (node != nullptr) {
    clearRecursive(node->left_);
    clearRecursive(node->right_);
    allocator_.deallocate(node->data_, 1);
    delete node;
    node = nullptr;
  }
}
