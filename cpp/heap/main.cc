#include <iostream>
#include <vector>
#include "heap.h"
#include "item.h"

int main(void) {
  Heap *heap = new Heap(MAX);

  int a[] = {3, 1, 4, 1, 5, 9, 2, 6};
  for (int i = 0; i < 8; i++)
    heap->insert(a[i], -1);

  Item *item;
  while (!heap->is_empty()) {
    item = heap->extract();
    std::cout << item->key << "\n";
  }
}
