import java.util.*;

public class MyPriorityQueue
{
	ArrayList<Integer> list;
	private int size;
	final boolean isMaxHeap;

	public MyPriorityQueue(boolean isMaxHeap)
	{
		list = new ArrayList<Integer>();
		this.size = 0;
		this.isMaxHeap = isMaxHeap;
	}

	private void heapify(int i)
	{
		int l = left(i);
		int r = right(i);

		if (isMaxHeap)
		{
			int largest = l < this.size && list.get(l) > list.get(i) ? l : i;
			largest = r < this.size && list.get(r) > list.get(largest) ? r : largest;
			if (largest != i)
			{
				exchange(i, largest);
				heapify(largest);
			}
		}
		else
		{
			int smallest = l < this.size && list.get(l) < list.get(i) ? l : i;
			smallest = r < this.size && list.get(r) < list.get(smallest) ? r : smallest;
			if (smallest != i)
			{
				exchange(i, smallest);
				heapify(smallest);
			}
		}
	}

	public Integer poll()
	{
		if (this.size == 0)
			return null;
		int val = list.get(0);
		list.set(0, list.get(this.size - 1));
		this.size--;
		heapify(0);	
		return val;				
	}

	public void add(int val)
	{
		if (this.size < list.size())
			list.set(this.size, val);
		else
			list.add(val);
		this.size++;		

		int i = this.size - 1;
		if (isMaxHeap)
			while (i > 0 && list.get(parent(i)) < list.get(i))
			{
				exchange(i, parent(i));
				i = parent(i);
			}
		else
			while (i > 0 && list.get(parent(i)) > list.get(i))
			{
				exchange(i, parent(i));
				i = parent(i);		
			}
	}

	public int size() {return this.size;}
	public boolean isEmpty() {return this.size == 0;}
	public Integer peek() {return this.size == 0 ? null : list.get(0);}

	private int parent(int i) {return (i - 1) / 2;}	
	private int left(int i) {return 2 * i + 1;}
	private int right(int i) {return 2 * i + 2;}

	private void exchange(int i, int j)
	{
		int save = list.get(i);
		list.set(i, list.get(j));
		list.set(j, save);
	}
	
	public boolean remove(int val)
	{
		int i = 0;
		boolean found = false;
		for (; i < this.size; i++)
			if (list.get(i) == val)
			{
				found = true;
				break;
			}

		if (found == true)
		{
			list.set(i, list.get(this.size - 1));
			heapify(i);
			if (isMaxHeap)
				while (list.get(i) > list.get(parent(i)))
				{
					exchange(i, parent(i));
					i = parent(i);
				}
			else
				while (list.get(i) < list.get(parent(i)))
				{
					exchange(i, parent(i));
					i = parent(i);
				}	
			size--;
		}
		return found;
	}
}
