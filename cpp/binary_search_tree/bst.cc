#include "node.h"
#include "bst.h"

Node *BinarySearchTree::get_root() {return this->root;}

void BinarySearchTree::insert(int key, int val) {
  Node *node = this->root;
  Node *parent = nullptr;

  while (node != nullptr && key != node->key) {
    parent = node;
    if (key < node->key)
      node = node->get_left();
    else
      node = node->get_right();
  }


  if (node == nullptr) {
    if (parent == nullptr)
      this->root = new Node(key, val);
    else if (key < parent->key)
      parent->set_left(new Node(key, val));
    else
      parent->set_right(new Node(key, val));
  }
}


Node *BinarySearchTree::query(int key) {
  Node *node = this->root;

  while (node != nullptr && key != node->key) {
    if (key < node->key)
      node = node->get_left();
    else
      node = node->get_right();
  }

  return node;
}


void BinarySearchTree::remove(int key) {
  Node *node = this->root;
  Node *parent = nullptr;

  while (node != nullptr && key != node->key) {
    parent = node;
    if (key < node->key)
      node = node->get_left();
    else
      node = node->get_right();
  }

  if (node == nullptr)
    return ;

  if (node->get_left() == nullptr) {
    if (parent != nullptr) {
      if (node->key < parent->key)
        parent->set_left(node->get_right());
      else
        parent->set_right(node->get_right());
    }
    else
      this->root = node->get_right();
  }
  else if (node->get_right() == nullptr) {
    if (parent != nullptr) {
      if (node->key < parent->key)
        parent->set_left(node->get_left());
      else
        parent->set_right(node->get_left());
    }
    else
      this->root = node->get_left();
  }
  else {
    Node *next_node = node->get_right();
    while (next_node->get_left() != nullptr)
      next_node = next_node->get_left();

    node->key = next_node->key;

    if (node->get_right() == next_node)
      node->set_right(next_node->get_right());
    else {
      parent = node->get_right();
      while (parent->get_left() != next_node)
        parent = parent->get_left();
      parent->set_left(next_node->get_right());
    }
  }  
}
