#ifndef BST_H
#define BST_H

#include "node.h"

class BinarySearchTree {
  private:
    Node *root;
  public:
    void insert(int, int);    
    Node *query(int);
    void remove(int);
    Node *get_root();
};

#endif
