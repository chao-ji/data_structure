import java.util.*;

public class UndirectedGraph
{
	List<UndirectedGraphNode> vertex;

	UndirectedGraph(int size)
	{
		this.vertex = new ArrayList<UndirectedGraphNode>();
		for (int i = 0; i < size; i++)
			vertex.add(new UndirectedGraphNode(i));
	}

	public void addEdge(int u, int v)
	{
		vertex.get(u).neighbors.add(vertex.get(v));
		vertex.get(v).neighbors.add(vertex.get(u));
	}

	public void depthFirstSearchFromNode(UndirectedGraphNode root, boolean[] visited, List<Integer> dfs)
	{
		Deque<UndirectedGraphNode> stack = new ArrayDeque<UndirectedGraphNode>();
		visited[root.label] = true;
		stack.addLast(root);

		while (!stack.isEmpty())
		{
			UndirectedGraphNode node = stack.removeLast();
			dfs.add(node.label);
			for (int i = node.neighbors.size() - 1; i >= 0; i--)
				if (!visited[node.neighbors.get(i).label])
				{
					visited[node.neighbors.get(i).label] = true;
					stack.addLast(node.neighbors.get(i));
				}
		}
	}

	public List<Integer> depthFirstSearch()
	{
		boolean[] visited = new boolean[vertex.size()];
		List<Integer> dfs = new ArrayList<Integer>();
		for (int i = 0; i < vertex.size(); i++)
			if (!visited[vertex.get(i).label])
				depthFirstSearchFromNode(vertex.get(i), visited, dfs);
		return dfs;
	}

	public List<Integer> breadthFirstSearch(UndirectedGraphNode root)
	{
		Deque<UndirectedGraphNode> queue = new ArrayDeque<UndirectedGraphNode>();
		List<Integer> bfs = new ArrayList<Integer>();
		boolean[] visited = new boolean[vertex.size()];
		visited[root.label] = true;
		queue.addLast(root);
		
		while (!queue.isEmpty())
		{
			UndirectedGraphNode node = queue.removeFirst();
			bfs.add(node.label);
			for (int i = node.neighbors.size() - 1; i >= 0; i--)
				if (!visited[node.neighbors.get(i).label])
				{
					visited[node.neighbors.get(i).label] = true;
					queue.addLast(node.neighbors.get(i));
				}
		}
		return bfs;
	}

}
