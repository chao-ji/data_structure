public class CountInversion
{
  // Count the number of inversions using mergesort
	public static void main(String[] args)
	{
		int[] nums = {7,2,6,4,5,1,3,8};
		int count = countInversion(nums, 0, nums.length - 1);
		System.out.println(count);
	}

	static int countInversion(int[] nums, int low, int high)
	{
		if (low == high)
			return 0;

		int mid = (low + high) / 2;
		int lowerCount = countInversion(nums, low, mid);
		int upperCount = countInversion(nums, mid + 1, high);

		int[] lower = new int[mid + 2 - low];
		int[] upper = new int[high - mid + 1];
		lower[mid - low + 1] = Integer.MAX_VALUE;
		upper[high - mid] = Integer.MAX_VALUE;
		for (int i = low; i <= mid; i++)
			lower[i - low] = nums[i];
		for (int i = mid + 1; i <= high; i++)
			upper[i - mid - 1] = nums[i];

		int count = lowerCount + upperCount;
		int li = 0;
		int hi = 0;
		for (int i = low; i <= high; i++)
			if (lower[li] <= upper[hi])
			{
				nums[i] = lower[li];
				li++;
			}
			else
			{
				count += (mid - low - li + 1);  //all numbers after lower[li] in the lower[] array are greater than upper[hi]
				nums[i] = upper[hi];
				hi++;
			}
		
		return count;
	}
}
