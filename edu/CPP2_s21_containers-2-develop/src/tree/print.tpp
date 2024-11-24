template <class Key, class Compare, class Allocator>
std::string RedBlackTree<Key, Compare, Allocator>::string() {
  std::string str = "";
  if (!empty()) {
    output(root_, "", true, &str);
  } else {
    str += "Empty tree!\n";
  }
  return str;
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::output(node_type node,
                                                   std::string prefix,
                                                   bool isTail,
                                                   std::string *str) {
  if (node->right_ != nullptr) {
    std::string newPrefix = prefix;
    if (isTail) {
      newPrefix += "│   ";
    } else {
      newPrefix += "    ";
    }
    output(node->right_, newPrefix, false, str);
  }
  *str += prefix;
  if (isTail) {
    *str += "└── ";
  } else {
    *str += "┌── ";
  }
  if (node->data_ != nullptr) {
    *str += "Color: " + std::string(node->color_ == BLACK ? "BLACK" : "RED") +
            ", Key: " + std::to_string(*node->data_) + "\n";
  } else {
    *str += "NULL\n";
  }
  if (node->left_ != nullptr) {
    std::string newPrefix = prefix;
    if (isTail) {
      newPrefix += "    ";
    } else {
      newPrefix += "│   ";
    }
    output(node->left_, newPrefix, true, str);
  }
}

template <class Key, class Compare, class Allocator>
std::string RedBlackTree<Key, Compare, Allocator>::stringWithCallback(
    std::function<std::string(key_type)> callback, bool withColor) {
  std::string str = "";
  if (!empty()) {
    outputWithCompare(root_, "", true, &str, callback, withColor);
  } else {
    str += "Empty tree!\n";
  }
  return str;
}

template <class Key, class Compare, class Allocator>
void RedBlackTree<Key, Compare, Allocator>::outputWithCallback(
    node_type node, std::string prefix, bool isTail, std::string *str,
    std::function<std::string(key_type)> callback, bool withColor) {
  if (node->right_ != nullptr) {
    std::string newPrefix = prefix;
    if (isTail) {
      newPrefix += "│   ";
    } else {
      newPrefix += "    ";
    }
    outputWithCompare(node->right_, newPrefix, false, str, callback, withColor);
  }
  *str += prefix;
  if (isTail) {
    *str += "└── ";
  } else {
    *str += "┌── ";
  }
  if (node->data_ != nullptr) {
    if (withColor) {
      *str += "Color: " + std::string(node->color_ == BLACK ? "BLACK" : "RED");
    }
    *str += callback(*node->data_) + "\n";
  } else {
    *str += "NULL\n";
  }
  if (node->left_ != nullptr) {
    std::string newPrefix = prefix;
    if (isTail) {
      newPrefix += "    ";
    } else {
      newPrefix += "│   ";
    }
    outputWithCompare(node->left_, newPrefix, true, str, callback, withColor);
  }
}