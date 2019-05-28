class Node(object):
  def __init__(self, key, val=None):
    self.key = key
    self.val = val
    self.left = None
    self.right = None

class BinarySearchTree(object):

  def __init__(self):
    self.root = None


  def insert(self, key, val=None):
    # `parent` points to the parent of `node`, so we can assign `node`
    # as one of `parent`'s child (i.e. left or right) where `node` is
    # supposed to be inserted. 
    node, parent = self.root, None

    # Use `node.key` to help us navigate to the right place to insert
    while node is not None and key != node.key:
      parent = node
      if key < node.key:
        node = node.left
      else:
        node = node.right

    # if `node` is not None, it means there is already a node with key 
    # `key` in the tree, nothing to do

    # found the right place to insert `node`
    if node is None:
      if parent is None: # tree is empty 
        self.root = Node(key, val)
      elif key < parent.key:
        parent.left = Node(key, val)
      else:
        parent.right = Node(key, val)

  def query(self, key):
    node = self.root
    # Use `node.key` to help us navigate to the right place to insert
    while node is not None and key != node.key:
      if key < node.key:
        node = node.left
      else:
        node = node.right 
    return node

  def delete(self, key):
    node, parent = self.root, None

    # Use `node.key` to help us navigate to the right place to insert
    while node is not None and key != node.key:
      parent = node
      if key < node.key:
        node = node.left
      else:
        node = node.right

    # found the place where the node with `key` is supposed to be 
    
    # the node to be deleted doesn't exist, nothing to do
    if node is None:
      return

    # the node to be deleted has empty left tree, so assign `node.right`
    # as one of `parent`'s child node (if `parent` is not empty).
    if node.left is None: 
      if parent is not None:
        if node.key < parent.key: # `node` is `parent`'s left child
          parent.left = node.right
        else: # `node` is `parent`'s right child
          parent.right = node.right
      else: # `parent` is empty, so the tree is empty
        self.root = node.right

    # the node to be deleted has empty right tree, so assign `node.left`
    # as one of `parent`'s child node (if `parent` is not empty). 
    elif node.right is None:
      if parent is not None:
        if node.key < parent.key: # `node` is `parent`'s left child
          parent.left = node.left
        else: # `node` is `parent`'s right child
          parent.right = node.left
      else: # `parent` is empty, so the tree is empty
        self.root = node.left

    else: # the node to be deleted has non-empty left and right child
          # so first we need to find the successor of `node` (i.e. the next integer)

      # the successor of `node` is the leftmost node in `node`'s right subtree
      # and its left child should be empty
      next_node = node.right
      while next_node.left is not None:
        next_node = next_node.left
      
      # `node` gets `next_node`'s key
      node.key = next_node.key

      # then we need to delete `next_node`
      #
      # if `next_node` is `node`'s right child, since `next_node` doesn't have
      # a left child, we simply assign `node_next`'s right child as `node`'s right
      # child
      if node.right == next_node:
        node.right = next_node.right

      # there are some nodes between `node.right` and `next_node` along the "all-left"
      # path, we use a pointer `parent` and move it along the "all-left" path, until
      # its left child is `next_node`
      else:
        parent = node.right
        while parent.left != next_node:
          parent = parent.left
        parent.left = next_node.right
 
if __name__ == '__main__':
  a = [8, 3, 10, 1, 6, 14, 4, 7, 13]

  bst = BinarySearchTree()

  for i in range(len(a)):
    bst.insert(a[i])


  bst.delete(10)

  curr_level = [bst.root]
  next_level = []
  vals = []

  while curr_level:
    for node in curr_level:
      vals.append(node.key)
      if node.left:
        next_level.append(node.left)
      if node.right:
        next_level.append(node.right)
    print(vals)
    curr_level = next_level
    next_level = []
    vals = []
