import java.util.*;

public class Trie
{
    public Trie()
    {
        root = new TrieNode();
    }
	
    public void insert(String key)
    {
        TrieNode node = this.root;

        for (int i = 0; i < key.length(); i++)
        {
            if (node.children[key.charAt(i)] == null)
                node.children[key.charAt(i)] = new TrieNode();
            node = node.children[key.charAt(i)];
        }

        node.count++;
    }

    public boolean containsKey(String key)
    {
        return this.count(key) > 0 ? true : false;
    }

    public int count(String key)
    {
        TrieNode node = this.root;

        for (int i = 0; i < key.length(); i++)
            if (node.children[key.charAt(i)] == null)
                return 0;
            else
                node = node.children[key.charAt(i)];

        return node.count;
    }

	public ArrayList<String> hasPrefix(String key)
	{
		ArrayList<String> list = new ArrayList<String>();
		TrieNode node = this.root;

		for (int i = 0; i < key.length(); i++)
			if (node.children[key.charAt(i)] == null)
				return list;
			else
				node = node.children[key.charAt(i)];

		ArrayDeque<TrieNode> queueNode = new ArrayDeque<TrieNode>();
		ArrayDeque<String> queueSuff  = new ArrayDeque<String>();
		queueNode.addLast(node);
		queueSuff.addLast(key);
		
		while (!queueNode.isEmpty())
		{
			node = queueNode.removeFirst();
			String s = queueSuff.removeFirst();

			if (node.count != 0)
				list.add(s);

			for (int i = 0; i < node.children.length; i++)
				if (node.children[i] != null)
				{
					queueNode.addLast(node.children[i]);
                    StringBuilder sb = new StringBuilder(s);
					queueSuff.addLast(sb.append((char) i).toString());
				}
		}

		return list;		
	}

    public ArrayList<String> getKeys()
    {
        return this.hasPrefix("");
    }

    TrieNode root;

    static class TrieNode
    {
        public TrieNode()
        {
            this.children = new TrieNode[128];
            this.count = 0;
        }

        TrieNode[] children;
        int count;
    }
}
