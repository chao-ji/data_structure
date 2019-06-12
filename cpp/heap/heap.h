#ifndef HEAP_H
#define HEAP_H

#include <vector> 
#include "item.h"

#define MAX 1
#define MIN 0

class Heap {
  private:
    int size;
    std::vector<Item*> array;
    int type;

    int get_left(int);
    int get_right(int);
    int get_parent(int);
    void swap(int, int);

  public:
    Heap(int);
    int get_size();
    int get_type();
    int is_empty();
    void insert(int, int);
    Item *extract();
    void heapify(int); 
    std::vector<Item*> get_array();
};

#endif
