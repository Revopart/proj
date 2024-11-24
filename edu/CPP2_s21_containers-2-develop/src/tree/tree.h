#ifndef S21_CONTAINERS_REDBLACKTREE_H_
#define S21_CONTAINERS_REDBLACKTREE_H_

#include <cstddef>
#include <functional>
#include <optional>
#include <utility>

#define RED 1
#define BLACK 0
#define START 0
#define PROCESS 1
#define END 2

namespace s21 {
template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key>>
class RedBlackTree {
public:
  using key_type = Key;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using key_compare = Compare;
  using allocator_type = Allocator;
  using reference = key_type &;
  using const_reference = const key_type &;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;

  class Node {
    friend RedBlackTree;

  public:
    using node_type = Node *;

  private:
    key_type *data_;
    bool color_;
    node_type parent_;
    node_type left_;
    node_type right_;

  public:
    Node() : color_(BLACK){};
    Node(Key *val)
        : data_(val), color_(RED), parent_(nullptr), left_(nullptr),
          right_(nullptr){};
    key_type getKey();
    node_type getLeft();
    node_type getRight();
    node_type getParent();
    bool isBlack();
    bool isRed();
    bool isLeftNode();
    bool isRightNode();
    int getChildrenCount();
    node_type getChildOrNull();
    bool isNotChild();
  };

  using node_type = Node *;

  class Iterator {
  private:
    RedBlackTree<Key, Compare, Allocator> *tree_;
    node_type node_;
    int position_;
    bool is_reverse_;

  public:
    Iterator(RedBlackTree<Key, Compare, Allocator> *tree, node_type node,
             int position = START, bool isReverse = false)
        : tree_(tree), node_(node), position_(position),
          is_reverse_(isReverse) {}
    ~Iterator(){};
    Iterator(const Iterator &other) = default;
    Iterator &operator=(const Iterator &other) = default;
    bool operator==(const Iterator &other);
    bool operator!=(const Iterator &other);
    Iterator next();
    Iterator prev();
    Iterator operator++();
    Iterator operator--();
    key_type operator*();
    key_type *operator->();
    node_type getNode();
    void start();
    void end();
    Iterator first();
    Iterator last();
  };

  using piterator = Iterator *;
  using iterator = Iterator;
  using const_iterator = const Iterator;
  using reverse_iterator = iterator;
  using const_reverse_iterator = const_iterator;

private:
  node_type root_;
  size_type length_;
  key_compare cmp_;
  allocator_type allocator_;

  // Utils
  void clearRecursive(node_type node);

  // Balance tree
  void balanceInsert(node_type new_node);
  void leftRotate(node_type node);
  void rightRotate(node_type node);
  void swapNode(node_type to, node_type from, bool isNull);
  void balanceRemove(node_type node, bool isLeftNode);
  node_type getRightSwappedNode(node_type node);
  bool getColor(node_type node);

public:
  // CONSTRUCTORS
  RedBlackTree();
  RedBlackTree(Allocator allocator);
  RedBlackTree(std::initializer_list<key_type> const &items);
  // На самом деле если скопировать по итератору. Она идентичной не будет по
  // структуре. Для этого нужно делать специальный метод для копирования
  RedBlackTree(RedBlackTree &other);
  // Конструктор перемещение
  RedBlackTree(RedBlackTree &&other);
  // Деструктор
  ~RedBlackTree();
  // Оператор присваивания
  RedBlackTree &operator=(RedBlackTree &&other);
  // Оператор присваивания перемещения
  RedBlackTree &operator=(RedBlackTree &other);

  // PRINT
  std::string string();
  void output(node_type node, std::string prefix, bool isTail,
              std::string *str);
  std::string stringWithCallback(std::function<std::string(key_type)> callback,
                                 bool withColor = false);
  void outputWithCallback(node_type node, std::string prefix, bool isTail,
                          std::string *str,
                          std::function<std::string(key_type)> callback,
                          bool withColor = false);

  // CAPACITY
  bool empty();
  size_type size();
  size_type max_size();

  // ELEMENT ACCESS
  node_type getNode(key_type key);
  reference at(const_reference key);
  reference operator[](const_reference key);
  node_type getNode(key_type key, std::function<bool(node_type current)>);

  // ITERATOR
  node_type right();
  node_type left();
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();
  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator crbegin();
  const_reverse_iterator crend();

  // MODIFIER
  void clear();
  std::pair<iterator, bool> insert(key_type value);
  template <class InputIt> void insert(InputIt first, InputIt last);
  void insert(std::initializer_list<key_type> ilist);
  size_type erase(iterator pos);
  size_type erase(key_type key);
  void swap(RedBlackTree &other);
  std::optional<key_type> extract(iterator position);
  std::optional<key_type> extract(key_type key);

  // LOOKUP
  bool contains(const Key &key) const {
    node_type node = getNode(key);
    if (node == nullptr) {
      return false;
    }
    return true;
  }

  // OBSERVERS
  key_compare key_comp();
  allocator_type get_allocator();
};

#include "balance.tpp"
#include "capacity.tpp"
#include "constructor.tpp"
#include "element_access.tpp"
#include "iterator.tpp"
#include "modifier.tpp"
#include "node.tpp"
#include "observer.tpp"
#include "print.tpp"
#include "utils.tpp"
} // namespace s21

#endif