#include <vector>
#include <iostream>
#include "node.h"
#include "bst.h"


void in_order(Node *root) {
  if (root == nullptr)
    return;

  in_order(root->get_left());
  std::cout << root->key << "\n";
  in_order(root->get_right());

}

int main(void) {

  int a[] = {8, 42, 38, 24, 46, 34, 19,  1, 21, 10, 26, 23, 15,  7, 41, 25, 43,
       31,  2, 18,  3,  4, 49, 27, 36,  6, 28, 12, 45, 20, 35, 39, 11, 37,
       22, 44, 16, 13,  5, 32, 30, 47, 14, 17, 33, 48,  0,  9, 29, 40};
  int i;

  BinarySearchTree *bst = new BinarySearchTree();

  for (i = 0; i < 50; i++) 
    bst->insert(a[i], -1);


  int b[] = {27, 17, 12, 18, 34,  4, 45, 33, 30, 20, 11, 13,  3, 17, 41, 41, 19,
       29, 25, 47};

  for (i = 0; i < 20; i++)
    bst->remove(b[i]);


  in_order(bst->get_root());
}
