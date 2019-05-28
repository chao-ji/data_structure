public class T
{
	public static void main(String[] args)
	{
		UndirectedGraph graph = new UndirectedGraph(8);
		graph.addEdge(0, 1);
		graph.addEdge(0, 3);
		graph.addEdge(0, 4);
		graph.addEdge(1, 6);
		graph.addEdge(2, 6);
		graph.addEdge(4, 7);
		graph.addEdge(5, 6);
		graph.addEdge(5, 7);

		System.out.println("Depth First Search traversal");
		System.out.println(graph.depthFirstSearch());
		System.out.println("Breadth First Search trversal");
		System.out.println(graph.breadthFirstSearch(graph.vertex.get(0)));
	}
}
