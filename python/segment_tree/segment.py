import numpy as np


class Node(object):
  """Node of Segment Tree."""
  def __init__(self, start, end):
    """Constructor.
    
    Args:
      start: int scalar, the lower bound (inclusive) of the interval.
      end: int scalar, the upper bound (inclusive) of the inverval.
    """
    if start > end:
      raise ValueError('start (%d) must be <= end (%d)' % (start, end))

    self.start = start
    self.end = end
    self.val = None
    self.left = None
    self.right = None


class SegmentTree(object):
  """An array can be turned into a segment tree, which allows for efficient 
  range queries. Each node corresponds to an interval.

  The array is divided at the mid point into two subarrays, `left` and `right`,
  where the root corresponds to the original array and its left and right child
  corresponds to `left` and `right`, respectively. The left and right child have
  children themselves, which correspond to subarrays further divided from `left`
  and `right`. The leaf nodes correspond to each individual element in the 
  array. 
  """
  def __init__(self, start, end, reduce_mode='sum'):
    """Constructor.

    Args:
      start: int scalar, the lower bound (inclusive).
      end: int scalar, the upper bound (inclusive).
      reduce_mode: string scalar, type of reduction on the set of values 
        bounded between `start` and `end`.
    """
    self.root = Node(start, end)
    if reduce_mode not in ('sum', 'max', 'min'):
      raise ValueError('unsupported reduction mode: %s' % reduce_mode)

    self._reduce_mode = reduce_mode
    self._reduce_fn, self._init_fn = self._reduce_init_fn()

  def insert(self, node, key, val=None):
    """Insert a new value into node.

    Args:
      node: a Node instance.
      key: int scalar, the key into the array.
      val: int scalar, the value with index `key`.
    """
    if key < node.start or key > node.end:
      return

    if node.val is None:
      node.val = self._init_fn(val)
    else:
      node.val = self._reduce_fn(node.val, val) 

    if node.start == node.end:
      return

    mid = (node.end - node.start) // 2 + node.start
    
    if key <= mid:
      if node.left is None:
        node.left = Node(node.start, mid)
      self.insert(node.left, key, val)
    else:
      if node.right is None:
        node.right = Node(mid + 1, node.end)
      self.insert(node.right, key, val)

  def update(self, node, key, val):
    """Update element `key` with new value `val` within the subtree rooted at 
    `node`.

    Args:
      node: a Node instance.
      key: int scalar, the key into the array.
      val: int scalar, the new value to update the element `key` with.
    """
    if key < node.start or key > node.end:
      return

    # make sure `node`'s range is not empty
    assert node.val is not None

    if node.start == node.end:
      assert key == node.start
      node.val = val
      return

    mid = (node.end - node.start) // 2 + node.start
    if key <= mid:
      assert node.left
      self.update(node.left, key, val)
    else:
      assert node.right
      self.update(node.right, key, val)

    node.val = self._merge(node.left.val, node.right.val)


  def query(self, node, start, end):
    """Search the subtree rooted at `node` with query `[start, end]`.

    Args:
      node: a Node instance.
      start: int scalar, the lower bound (inclusive). Must be bounded within
        the range of `node`.
      end: int scalar, the upper bound (inclusive). Must be bounded within the
        range of `node`.

    Returns:
      val: the result of a reduction function on the subarray 
        `array[start: end + 1]`, e.g. sum, max or min.
    """
    val = None 

    if node is None or end < node.start or start > node.end or start > end:
      return val

    mid = (node.end - node.start) // 2 + node.start
 
    if start == node.start and end == node.end:
      val = node.val
    elif start <= mid and end <= mid:
      val = self.query(node.left, start, end)
    elif start >= mid + 1 and end >= mid + 1:
      val = self.query(node.right, start, end)
    else:
      val = self._merge(
          self.query(node.left, start, mid), 
          self.query(node.right, mid + 1, end))  
    return val      


  def _merge(self, left, right):
    """merge teh result of two subtrees."""
    if left is not None and right is not None:
      if self._reduce_mode == 'sum':
        return left + right
      elif self._reduce_mode == 'max':
        return max(left, right)
      elif self._reduce_mode == 'min':
        return min(left, right)
 
    elif left is not None and right is None:
      return left
    elif left is None and right is not None:
      return right
    
    return None

  def _reduce_init_fn(self):
    if self._reduce_mode == 'sum':
      reduce_fn = lambda x, y: x + y
      init_fn = lambda x: x
    elif self._reduce_mode == 'max':
      reduce_fn = lambda x, y: max(x, y)
      init_fn = lambda x: x
    elif self._reduce_mode == 'min':
      reduce_fn = lambda x, y: min(x, y)
      init_fn = lambda x: x
    return reduce_fn, init_fn


if __name__ == '__main__':
  n = np.random.randint(0, 100, size=())
  low, high = -100, 100
  a = list(np.random.randint(low, high, size=n))

  reduce_mode = 'max'
  reduce_fn = max

  st = SegmentTree(0, len(a) - 1, reduce_mode)
  for i, v in enumerate(a):
    st.insert(st.root, i, v)
 
  print('n', n)
  for i in range(n):
    for j in range(i, n):
      result = st.query(st.root, i, j)
      gt = reduce_fn(a[i:j + 1])
      if result != gt:
        print('wrong!')

  print('Original', a)
  if n >= 1:
    for _ in range(10):
      index = np.random.randint(0, n, size=())
      new_val = np.random.randint(low, high, size=())
      a[index] = int(new_val)
      st.update(st.root, index, new_val)
    print('Updated', a)
    for i in range(n):
      for j in range(i, n):
        result = st.query(st.root, i, j)
        gt = reduce_fn(a[i:j + 1])
        if result != gt:
          print('wrong!')

