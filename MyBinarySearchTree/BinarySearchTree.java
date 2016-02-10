public class BinarySearchTree
{
	TreeNode root;
	public BinarySearchTree()
	{
		root = null;
	}

	public void insert(int key)
	{
		TreeNode parent = null;
		TreeNode node = root;
		while (node != null && key != node.val)
		{
			parent = node;
			node = key < node.val ? node.left : node.right;
		}

		if (node == null)
		{
			if (parent == null)
				root = new TreeNode(key);
			else if (key < parent.val)
				parent.left = new TreeNode(key);
			else
				parent.right = new TreeNode(key);
		}	
	}

	public TreeNode query(int key)
	{
		TreeNode node = root;
		while (node != null && key != node.val)
			node = key < node.val ? node.left : node.right;

		return node;
	}

	public void remove(int key)
	{
		TreeNode parent = null;
		TreeNode node = root;
		while (node != null && key != node.val)
		{
			parent = node;
			node = key < node.val ? node.left : node.right;
		}

		if (node == null)
			return;

		if (node.left == null)
		{
			if (parent != null)
			{
				if (node.val < parent.val)
					parent.left = node.right;
				else
					parent.right = node.right;
			}
			else
				root = node.right;
		}
		else if (node.right == null)
		{
			if (parent != null)
			{
				if (node.val < parent.val)
					parent.left = node.left;
				else
					parent.right = node.left;
			}
			else
				root = node.left;
		}
		else
		{
			TreeNode next = node.right;
			while (next.left != null)
				next = next.left;
			node.val = next.val;
			if (node.right == next)
				node.right = next.right;
			else
			{
				parent = node.right;
				while (parent.left != next)
					parent = parent.left;
				parent.left = next.right;
			}
		}
	} 

	static class TreeNode
	{
		int val;
		TreeNode left;
		TreeNode right;
		TreeNode(int x) {val = x;}
	}
}
