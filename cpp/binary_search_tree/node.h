#ifndef NODE_H
#define NODE_H

class Node {
  private:
    Node *left;
    Node *right;
  public:
    int key;
    int val;
    Node(int, int);
    void set_left(Node *);
    void set_right(Node *);
    Node *get_left();
    Node *get_right();
};

#endif
