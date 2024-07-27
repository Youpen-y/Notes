#include <iostream>
#include <vector>

using namespace std;

int lengthOfLIS(vector<int>& nums);

int main()
{
    vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> nums1{0, 1, 0, 3, 2, 3};
    vector<int> nums2{7, 7, 7, 7, 7, 7};
    vector<int> nums3{1, 3, 6, 7, 9, 4, 10, 5, 6};
    cout << "LIS is " << lengthOfLIS(nums) << endl;
    cout << "LIS is " << lengthOfLIS(nums1) << endl;
    cout << "LIS is " << lengthOfLIS(nums2) << endl;
    cout << "LIS is " << lengthOfLIS(nums3) << endl;
    return 0;
}

int lengthOfLIS(vector<int>& nums)
{
    int res = INT_MIN;
    int size = nums.size();

    vector<int> dp(size, 1);

    for(int i = 0; i < size; i++)
    {
	for(int j = 0; j < i; j++)
	{
	    if(nums[i] > nums[j])
	    {
		dp[i] = (dp[i] > dp[j]+1)?dp[i] : dp[j]+1;
	    }
	}
    }
    
    for(i = 0; i < size; i++)
    {
	res = res < dp[i] ? dp[i] : res;
    }
    return res;
}
