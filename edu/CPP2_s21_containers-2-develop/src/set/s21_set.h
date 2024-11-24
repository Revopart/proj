#ifndef S21_CONTAINERS_SET_H_
#define S21_CONTAINERS_SET_H_

#include "../tree_kv/tree.h"
#include <cstddef>
#include <functional>
#include <optional>
#include <utility>

namespace s21 {
template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, bool>>>
class set {
public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using key_compare = Compare;
  using allocator_type = Allocator;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;
  using node_type =
      typename RedBlackTree<Key, bool, Compare, Allocator>::node_type;

  class Iterator {
  private:
    typename RedBlackTree<Key, bool, Compare, Allocator>::iterator iter_;

  public:
    Iterator(typename RedBlackTree<Key, bool, Compare, Allocator>::iterator it)
        : iter_(it){};
    ~Iterator(){};
    Iterator(const Iterator &other) = default;
    Iterator &operator=(const Iterator &other) = default;

    bool operator==(const Iterator &other) { return iter_ == other.iter_; }
    bool operator!=(const Iterator &other) { return iter_ != other.iter_; }

    Iterator next() {
      iter_ = iter_.next();
      return *this;
    }

    Iterator prev() {
      iter_ = iter_.prev();
      return *this;
    }

    Iterator operator++() {
      iter_ = ++iter_;
      return *this;
    }
    Iterator operator--() { iter_ = --iter_; }
    node_type getNode() { return iter_.getNode(); }
    key_type operator*() {
      auto node = iter_.getNode();
      return node->getKey();
    }
    key_type *operator->() {
      auto node = iter_.getNode();
      return &(node->getKey());
    }

    void start() { iter_.start(); }
    void end() { iter_.end(); }
    Iterator first() {
      iter_ = iter_.first();
      return *this;
    }
    Iterator last() {
      iter_ = iter_.last();
      return *this;
    }
  };

  using piterator = Iterator *;
  using iterator = Iterator;
  using const_iterator = const Iterator;
  using reverse_iterator = iterator;
  using const_reverse_iterator = const_iterator;

private:
  RedBlackTree<Key, bool, Compare, Allocator> tree_;

public:
  set() { tree_ = RedBlackTree<Key, bool, Compare, Allocator>(); }
  set(std::initializer_list<value_type> const &items) {
    for (value_type item : items) {
      tree_.insert(std::make_pair(item, false));
    }
  }
  set(set &other) {
    tree_ = RedBlackTree<Key, bool, Compare, Allocator>(other.tree_);
  }
  set(set &&other) {
    tree_ = RedBlackTree<Key, bool, Compare, Allocator>(std::move(other.tree_));
  }
  set &operator=(set &&other) {
    tree_ = std::move(other.tree_);
    return *this;
  }
  // Оператор присваивания перемещения
  set &operator=(set &other) {
    tree_ = other.tree_;
    return *this;
  }

  // PRINT SET
  std::string string() { return tree_.string(); }

  // ITERATOR
  iterator begin() { return Iterator(tree_.begin()); }
  iterator end() { return Iterator(tree_.end()); }
  const_iterator cbegin() { return Iterator(tree_.begin()); }
  const_iterator cend() { return Iterator(tree_.end()); }
  reverse_iterator rbegin() { return Iterator(tree_.rbegin()); }
  reverse_iterator rend() { return Iterator(tree_.rend()); }
  const_reverse_iterator crbegin() { return Iterator(tree_.rbegin()); }
  const_reverse_iterator crend() { return Iterator(tree_.rbegin()); }

  // MODIFIER
  // Очистка контейнера
  void clear() { tree_.clear(); }

  // Вствка элемента
  std::pair<node_type, bool> insert(value_type value) {
    return tree_.insert(std::make_pair(value, false));
  }

  // Вставка элементов по итератору
  template <class InputIt> void insert_range(InputIt first, InputIt last) {
    tree_.insert_range(first, last);
  }

  // Удаление по ключу. возвращает кол-во удаленных элементов
  int erase(value_type value) { return tree_.erase(value); }

  // Удвление по ключу. Возвращает пару ключ значение при успешном удалений.
  // Если же элемента не существует возвращает std::nullopt
  std::optional<value_type> extract(value_type value) {
    auto res = tree_.extract(value);
    if (!res.has_value()) {
      return std::nullopt;
    }
    return std::optional(res.value().first);
  }

  // Обмен содержимым двух деревьев
  void swap(set &other) { tree_.swap(other.tree_); }

  // LOOKUP
  bool contains(value_type value) { return tree_.contains(value); }

  // CAPACITY
  bool empty() { return tree_.empty(); }
  size_type size() { return tree_.size(); }
  size_type max_size() { return tree_.max_size(); }

  // ELEMENT ACCESS
  value_type &at(value_type value) {
    node_type node = tree_.getNode(value);
    if (node == nullptr) {
      throw std::out_of_range("value not found in value");
    }
    return node->getKeyRef();
  }
  value_type &operator[](value_type value) {
    node_type node = tree_.getNode(value);
    if (node == nullptr) {
      value_type val = value_type();
      auto res = tree_.insert(std::make_pair(value, val));
      return res.first->getKeyRef();
    }
    return node->getKeyRef();
  }

  // OBSERVERS (getters and setters)
  // Возвращает функцию компаратор
  key_compare key_comp() { return tree_.key_comp(); }

  // Возвращает функцию компаратор. По сути идентичен key_comp нахера эта
  // функция нужна не ясно. Наверное этот метод нахер удалю. Не тестить
  key_compare value_comp() { return tree_.value_comp(); }

  // Возвращает аллокатор
  allocator_type get_allocator() { return tree_.get_allocator(); }
};
} // namespace s21

#endif