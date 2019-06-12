#include <iostream>
#include <vector>
#include "heap.h"
#include "item.h"


Heap::Heap(int type) {
  this->type = type;
  this->size = 0;
}

int Heap::get_left(int index) {return 2 * index + 1;}

int Heap::get_right(int index) {return 2 * index + 2;}

int Heap::get_parent(int index) {return (index - 1) / 2;}

int Heap::get_size() {return this->size;}

int Heap::get_type() {return this->type;}

std::vector<Item*> Heap::get_array() {return this->array;}

int Heap::is_empty() {return this->size == 0;}

void Heap::swap(int i, int j) {
  Item *tmp = this->array[i];
  this->array[i] = this->array[j];
  this->array[j] = tmp;
}

void Heap::insert(int key, int val) {
  if (this->get_size() < this->array.size()) 
    this->array[this->get_size()] = new Item(key, val);
  else 
    this->array.push_back(new Item(key, val)); 

  this->size += 1;
  int index = this->size - 1;

  if (this->get_type()) {
    while (index > 0 && this->array[this->get_parent(index)]->key < this->array[index]->key) {
      this->swap(index, this->get_parent(index));
      index = this->get_parent(index);
    }
  }
  else {
    while (index > 0 && this->array[this->get_parent(index)]->key > this->array[index]->key) {
      this->swap(index, this->get_parent(index));
      index = this->get_parent(index);
    }
  }
}

Item *Heap::extract() {
  int key = this->array[0]->key;
  int val = this->array[0]->val;

  this->array[0] = this->array[this->get_size() - 1];
  this->size -= 1;

  this->heapify(0);

  return new Item(key, val);
}

void Heap::heapify(int index) {
  int left = this->get_left(index);
  int right = this->get_right(index);

  if (this->get_type()) {
    int largest;
    if (left < this->get_size() and this->array[left]->key > this->array[index]->key)
      largest = left;
    else
      largest = index;

    if (right < this->get_size() && this->array[right]->key > this->array[largest]->key)
      largest = right;
   
    if (largest != index) {
      this->swap(index, largest);
      this->heapify(largest);
    }
  }
  else {
    int smallest;

    if (left < this->get_size() && this->array[left]->key < this->array[index]->key)
      smallest = left;
    else
      smallest = index;

    if (right < this->get_size() && this->array[right]->key < this->array[smallest]->key)
      smallest = right;

    if (smallest != index) {
      this->swap(index, smallest);
      this->heapify(smallest);
    }
  }
}
