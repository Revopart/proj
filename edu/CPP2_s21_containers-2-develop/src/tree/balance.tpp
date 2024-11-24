template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::balanceInsert(node_type newNode) {
  node_type uncle = nullptr;
  while (getColor(newNode->parent_) == RED) {
    if (newNode->parent_->isLeftNode()) {
      uncle = newNode->parent_->parent_->right_;
      if (getColor(uncle) == RED) {
        newNode->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        newNode->parent_->parent_->color_ = RED;
        newNode = newNode->parent_->parent_;
      } else {
        if (newNode->isRightNode()) {
          newNode = newNode->parent_;
          leftRotate(newNode);
        }
        newNode->parent_->color_ = BLACK;
        newNode->parent_->parent_->color_ = RED;
        rightRotate(newNode->parent_->parent_);
      }
    } else {
      uncle = newNode->parent_->parent_->left_;
      if (getColor(uncle) == RED) {
        newNode->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        newNode->parent_->parent_->color_ = RED;
        newNode = newNode->parent_->parent_;
      } else {
        if (newNode->isLeftNode()) {
          newNode = newNode->parent_;
          rightRotate(newNode);
        }
        newNode->parent_->color_ = BLACK;
        newNode->parent_->parent_->color_ = RED;
        leftRotate(newNode->parent_->parent_);
      }
    }
  }

  root_->color_ = BLACK;
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::swapNode(node_type to,
                                                     node_type from,
                                                     bool isNull) {
  if (to == root_) {
    root_ = from;
  } else if (to->isLeftNode()) {
    if (isNull) {
      to->parent_->left_ = nullptr;
    } else {
      to->parent_->left_ = from;
    }
  } else {
    if (isNull) {
      to->parent_->right_ = nullptr;
    } else {
      to->parent_->right_ = from;
    }
  }
  from->parent_ = to->parent_;
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::rightRotate(node_type node) {
  node_type tmp = node->left_;
  node->left_ = tmp->right_;
  if (node->left_ != nullptr) {
    node->left_->parent_ = node;
  }
  tmp->parent_ = node->parent_;
  if (node == root_) {
    root_ = tmp;
  } else if (node->isRightNode()) {
    node->parent_->right_ = tmp;
  } else {
    node->parent_->left_ = tmp;
  }
  tmp->right_ = node;
  node->parent_ = tmp;
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::leftRotate(node_type node) {
  node_type tmp = node->right_;
  node->right_ = tmp->left_;
  if (node->right_ != nullptr) {
    node->right_->parent_ = node;
  }
  tmp->parent_ = node->parent_;
  if (node == root_) {
    root_ = tmp;
  } else if (node->isLeftNode()) {
    node->parent_->left_ = tmp;
  } else {
    node->parent_->right_ = tmp;
  }
  tmp->left_ = node;
  node->parent_ = tmp;
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::balanceRemove(node_type node,
                                                          bool isLeftNode) {
  while (node != root_ && node->isBlack()) {
    node_type brother = nullptr;
    if (isLeftNode) {
      brother = node->parent_->right_;
      if (getColor(brother) == RED) {
        brother->color_ = BLACK;
        node->parent_->color_ = RED;
        leftRotate(node->parent_);
        brother = node->parent_->right_;
      }

      if (getColor(brother->left_) == BLACK &&
          getColor(brother->right_) == BLACK) {
        brother->color_ = RED;
        node = node->parent_;
      } else {
        if (getColor(brother->right_) == BLACK) {
          brother->left_->color_ = BLACK;
          brother->color_ = RED;
          rightRotate(brother);
          brother = node->parent_->right_;
        }
        brother->color_ = brother->parent_->color_;
        brother->right_->color_ = BLACK;
        node->parent_->color_ = BLACK;
        leftRotate(brother->parent_);
        node = root_;
      }
    } else {
      brother = node->parent_->left_;
      if (getColor(brother) == RED) {
        brother->color_ = BLACK;
        node->parent_->color_ = RED;
        rightRotate(node->parent_);
        brother = node->parent_->left_;
      }
      if (getColor(brother->left_) == BLACK &&
          getColor(brother->right_) == BLACK) {
        brother->color_ = RED;
        node = node->parent_;
      } else {
        if (getColor(brother->left_) == BLACK) {
          brother->right_->color_ = BLACK;
          brother->color_ = RED;
          leftRotate(brother);
          brother = node->parent_->left_;
        }
        brother->color_ = brother->parent_->color_;
        brother->left_->color_ = BLACK;
        node->parent_->color_ = BLACK;
        rightRotate(brother->parent_);
        node = root_;
      }
    }
  }
  node->color_ = BLACK;
}

template <class Key, class Compare, class Allocator>
typename RedBlackTree<Key, Compare, Allocator>::node_type
RedBlackTree<Key, Compare, Allocator>::getRightSwappedNode(node_type node) {
  node_type current = node;
  while (current != nullptr) {
    int childrenCount = current->getChildrenCount();
    if (childrenCount == 0) {
      return current;
    }
    if (childrenCount == 2) {
      if (cmp_(*current->left_->data_, *current->data_)) {
        current = current->left_;
      } else {
        current = current->right_;
      }
    } else {
      if (current->right_ == nullptr) {
        if (cmp_(*current->left_->data_, *current->data_)) {
          current = current->left_;
        } else {
          return current;
        }
      } else {
        if (cmp_(*current->right_->data_, *current->data_)) {
          current = current->right_;
        } else {
          return current;
        }
      }
    }
  }

  return node;
}

template <class Key, class Compare, class Allocator>
bool RedBlackTree<Key, Compare, Allocator>::getColor(node_type node) {
  if (node == nullptr) {
    return BLACK;
  }
  return node->color_;
}