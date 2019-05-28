import heapq
import numpy as np


class Heap(object):
  """
  """

  def __init__(self, is_max=False):
    self._array = []
    self._size = 0
    self._is_max = is_max

    self._left = lambda index: 2 * index + 1
    self._right = lambda index: 2 * index + 2
    self._parent = lambda index: (index - 1) // 2


  @property
  def size(self):
    return self._size

  @property
  def array(self):
    return self._array

  @property
  def is_max(self):
    return self._is_max

  @property
  def is_empty(self):
    return self.size == 0 

  @property
  def peek(self):
    return None if self.size == 0 else self.array[0]

  def heapify(self, index):
    """
    Assumes that the subtree rooted at `left(index)` and `right(index)` are both
    valid heaps (max or min).

    Args:
      index: int scalar
    """
    left = self._left(index)
    right = self._right(index)

    if self.is_max:
      # `largest` points to the index of `index`, `left(index)`, `right(index)`
      # with largest value 
      largest = (left if left < self.size and 
          self.array[left] > self.array[index] else index)
      largest = (right if right < self.size and 
          self.array[right] > self.array[largest] else largest)
      if largest != index:
        self._swap(index, largest)
        self.heapify(largest)

    else:
      # `smallest` points to the index of `index`, `left(index)`, `right(index)`
      # with smallest value
      smallest = (left if left < self.size and 
          self.array[left] < self.array[index] else index)
      smallest = (right if right < self.size and
          self.array[right] < self.array[smallest] else smallest)
      if smallest != index:
        self._swap(index, smallest)
        self.heapify(smallest)

  def extract(self):
    if self.is_empty:
      return None

    key, val = self.array[0]
    # replace element at index 0 with a possibly smaller element (at index -1)
    # and decrement `self._size`
    self.array[0] = self.array[self.size - 1]
    self._size -= 1
    # restore the heap property by heapifying 0
    self.heapify(0)
    return key, val

  def insert(self, key, val=None):
    """Insert a node.

    The node with key `key` is first inserted to the end of the heap, which 
    might violate the heap property. The inserted node is then floated up
    along the path to the root, until it reaches the right place to be inserted.
    In the mean time, `heapify` is called to maintain the heap property.
    
    Args:
      key: int scalar, key of node.
      val: (Optional) int scalar, value of node.
    """
    if self.size < len(self.array):
      self.array[self.size] = key, val
    else:
      self.array.append((key, val))
    self._size += 1

    index = self.size - 1
    if self.is_max:
      # the path from root to `index` (not including `index`) is decreasing,
      # move `array[index]` to the right place by floating it up in the path
      # like insertion sort.
      while index > 0 and self.array[self._parent(index)] < self.array[index]:
        self._swap(index, self._parent(index))
        index = self._parent(index)
    else:
      # the path from root to `index` (not including `index`) is increasing,
      # move `array[index]` to the right place by floating it up in the path
      # like insertion sort.
      while index > 0 and self.array[self._parent(index)] > self.array[index]:
        self._swap(index, self._parent(index))
        index = self._parent(index)

  def _swap(self, i, j):
    tmp = self.array[i]
    self.array[i] = self.array[j]
    self.array[j] = tmp


if __name__ == '__main__':
  data = list(np.random.randint(0, 20, size=100))
  ops = [('extract',) if np.random.rand() > 0.5 
      else ('insert', int(np.random.randint(0, 20, size=()))) 
          for i in range(100)]  

  # 1. this implementation 
  h = Heap()
  result_a = []

  for i in range(len(data)):
    h.insert(data[i])


  for op in ops:
    if op[0] == 'extract':
      if not h.is_empty:
        result_a.append(h.extract())
    elif op[0] == 'insert':
      h.insert(op[1])

  while not h.is_empty:
    result_a.append(h.extract())

  result_a = list(zip(*result_a))[0]
  # 2. python built-in heapq
  h = []
  result_b = []

  for i in range(len(data)):
    heapq.heappush(h, data[i])

  for op in ops:
    if op[0] == 'extract':
      if h:
        result_b.append(heapq.heappop(h))
    elif op[0] == 'insert':
      heapq.heappush(h, op[1])

  while h:
    result_b.append(heapq.heappop(h))
