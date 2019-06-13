#include "node.h"

Node::Node(int key, int val) {
  this->key = key;
  this->val = val;
}

void Node::set_left(Node *left) {
  this->left = left;
}

void Node::set_right(Node *right) {
  this->right = right;
}

Node *Node::get_left() {
  return this->left;
}

Node *Node::get_right() {
  return this->right;
}
