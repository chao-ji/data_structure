import numpy as np
import networkx as nx

class Node(object):
  def __init__(self, key, val=None):
    self.key = key
    self.val = val
    self.neighbors = []

class Graph(object):
  """Simple undirected Graph.
  
  Each node has a unique `key` (integer) and optionally a `val` field. Each pair
  of nodes are connected by at most one edge (i.e. simple graph).
  """
  def __init__(self):
    self.nodes = {}
    self.edges = set()

  @property
  def num_nodes(self):
    return len(self.nodes)

  @property
  def num_edges(self):
    return len(self.edges)

  def add_edge(self, u, v):
    """Add an edge.

    Args:
      u: an instance of `Node` or a 2-tuple holding `key` and `val`. 
      v: an instance of `Node` or a 2-tuple holding `key` and `val`. 
    """
    if not isinstance(u, Node):
      u = Node(u[0], u[1])
    if not isinstance(v, Node):
      v = Node(v[0], v[1])

    edge = (u.key, v.key) if u.key < v.key else (v.key, u.key)
    if edge not in self.edges:
      self.edges.add(edge)
    else:
      raise ValueError('edge (%d, %d) exists!' % (edge[0], edge[1]))

    if u.key not in self.nodes:
      self.nodes[u.key] = u
    if v.key not in self.nodes:
      self.nodes[v.key] = v

    self.nodes[u.key].neighbors.append(v)
    self.nodes[v.key].neighbors.append(u)

  def bfs_nodes(self, source):
    """Generates node sequence in breadth first search starting for a source.

    Args:
      source: an instance of `Node` or an int scalar holding the key.

    Yields:
      a 2-tuple holding node key and node val.
    """
    source = self._get_node(source)

    queue = [source.key]
    visited = set(queue)

    while queue:
      key = queue.pop(0)
      node = self.nodes[key]

      yield node.key, node.val

      neighbors = node.neighbors
      for i in range(len(neighbors)):
        if neighbors[i].key not in visited:
          visited.add(neighbors[i].key)
          queue.append(neighbors[i].key)

  def dfs_nodes(self, source):
    """Generates node sequence in depth first search starting from a source.

    Args::
      source: an instance of `Node` or an int scalar holding the key.

    Yields:
      a 2-tuple holding node key and node val.
    """
    source = self._get_node(source)

    stack = [source.key]
    visited = set(stack)

    while stack:
      key = stack.pop()
      node = self.nodes[key]

      yield node.key, node.val

      neighbors = node.neighbors
      for i in range(len(neighbors)):
        if neighbors[i].key not in visited:
          visited.add(neighbors[i].key)
          stack.append(neighbors[i].key)

  def _get_node(self, node):
    """Returns a Node instance.

    Args:
      node: an instance of `Node`, or an int scalar holding the node's key.

    Returns:
      a Node instance.
    """
    if not isinstance(node, Node):
      if node not in self.nodes:
        raise ValueError('node with key %d does not exist.' % node)
      else:
        node = self.nodes[node]
    return node


if __name__ == '__main__':

  # Generate undirected graph with `num_nodes` nodes
  num_nodes = 16
  edges = []
  adj = np.random.randint(0, 2, size=(num_nodes, num_nodes))
  for i in range(num_nodes):
    for j in range(i, num_nodes):
      if adj[i, j] == 1:
        edges.append((i, j))

  # Pick a source
  source = int(np.random.randint(0, num_nodes, size=()))

  ########## This implementation
  g = Graph()
  for edge in edges:
    g.add_edge((edge[0], None), (edge[1], None))

  bfs_nodes = g.bfs_nodes(source)
  bfs_nodes = list(zip(*bfs_nodes))[0]

  dfs_nodes = g.dfs_nodes(source)
  dfs_nodes = list(zip(*dfs_nodes))[0]

  ########### networkx
  g = nx.Graph()
  g.add_edges_from(edges)

  bfs_nodes_nx = nx.traversal.bfs_edges(g, source)
  bfs_nodes_nx = (source,) + list(zip(*bfs_nodes_nx))[1]

  dfs_nodes_nx = nx.traversal.dfs_edges(g, source) 
  dfs_nodes_nx = (source,) + list(zip(*dfs_nodes_nx))[1]
