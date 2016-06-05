public class SegmentTree
{
	SegmentTreeNode root;

	public SegmentTree(int start, int end)
	{
		root = new SegmentTreeNode(start, end, 0);
	}

	public void insert(SegmentTreeNode node, int val)
	{
		if (val < node.start || val > node.end)
			return ;

		node.count++;
		if (node.start == node.end)
			return ;

		int mid = (node.start + node.end) / 2;
		if (node.end < 0 || node.start > 0)
			mid = (node.end - node.start) / 2 + node.start;

		if (val <= mid)
		{
			if (node.left == null)
				node.left = new SegmentTreeNode(node.start, mid, 0);
			this.insert(node.left, val);
		}
		else
		{
			if (node.right == null)
				node.right = new SegmentTreeNode(mid + 1, node.end, 0);
			this.insert(node.right, val);
		}
	}

	public int query(SegmentTreeNode node, int start, int end)
	{
		int count = 0;
		if (node == null || end < node.start || start > node.end)
			return count;

		int mid = (node.start + node.end) / 2;
		if (node.end < 0 || node.start > 0)
			mid = (node.end - node.start) / 2 + node.start;

		if (start == node.start && end == node.end)
			count = node.count;
		else if (start <= mid && end <= mid)
			count = query(node.left, start, end);
		else if (start >= mid + 1 && end >= mid + 1)
			count = query(node.right, start, end);
		else
			count = query(node.left, start, mid) + query(node.right, mid + 1, end);

		return count;
	}

	static class SegmentTreeNode
	{
		int start;
		int end;
		int count;
		SegmentTreeNode left;
		SegmentTreeNode right;

		public SegmentTreeNode(int start, int end, int count)
		{
			this.start = start;
			this.end = end;
			this.count = count;
		}
	}
}
