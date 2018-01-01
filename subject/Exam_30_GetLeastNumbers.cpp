#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

/**
 * 最小的k个数
 * 思路
 * 最容易想到的是用一个大小为k的已排序数组，若元素x比数组中的max小，就pop掉max，push进x，显然最大的缺点在于插入时
 * 需要遍历数组找合适的插入位置，插入复杂度O(k)，删除O(1)，若数组不排序则插入与删除的复杂度相反。
 * 要插入和删除都是O(logk),可以用树(set)或者堆(priority_queue),只关心k个数的最大值，不需要排序信息，显然是用堆O(Nlogk)
 * 这种做法适用于海量数据
 * 特例：k<=0，input为空，input的大小比k小
 * 
 * 另一种做法：快排。快排的核心思想是选择一个pivot，把>pivot的放后面，<pivot的放前面，那么当pivot的下标是k-1时，前半部分
 * 就是最小的k个数；这种做法的时间复杂度是O(N),缺点是要改动原数组而且数据必须能全部装入内存
 */
class Solution
{
  public:
    //堆(优先队列)法
    vector<int> GetLeastNumbers_Solution(const vector<int> &input, int k)
    {
        if (k <= 0 || input.empty() || int(input.size()) < k)
            return vector<int>();
        priority_queue<int> nHeap(input.begin(), input.begin() + k); //默认最大堆
        for (size_t i = k; i < input.size(); ++i)
            if (input[i] < nHeap.top())
            {
                nHeap.pop();
                nHeap.push(input[i]);
            }
        vector<int> output(k);
        for (int i = k - 1; i >= 0; --i)
        {
            output[i] = nHeap.top();
            nHeap.pop();
        }
        return output;
    }

    //快排法
    vector<int> GetLeastNumbers_QS(vector<int> input, int k)
    {
        if (k <= 0 || input.empty() || int(input.size()) < k)
            return vector<int>();
        QuickSortCore(input, 0, input.size() - 1, k);
        vector<int> output(input.cbegin(), input.cbegin() + k);
        return output;
    }
    void QuickSortCore(vector<int> &arr, int left, int right, int k)
    {
        if (left >= right) //递归终止条件
            return;
        int pivot = median3(arr, left, right);
        //开始分割partition
        int i = left, j = right - 1;
        for (;;)
        {                            //不用担心i或j越界，因为边界已在median3中设好
            while (arr[++i] < pivot) //最多停在right-1
                ;
            while (arr[--j] > pivot) //最少停在left
                ;
            if (i < j)
                std::swap(arr[i], arr[j]);
            else
                break;
        }
        std::swap(arr[i], arr[right - 1]); //pivot放在正确的位置上
        if (k - 1 < i)                     //针对本题的修改，pivot在前半部分才做此递归
            QuickSortCore(arr, left, i - 1, k);
        if (k - 1 > i) //针对本题的修改，pivot在后半部分才做此递归
            QuickSortCore(arr, i + 1, right, k);
    }
    /**
     * 三数中值法选出pivot，且按顺序摆放这3个值，这种做法使得QuickSortCore中
     * 可以省掉边界判断
     */
    int median3(vector<int> &arr, int left, int right)
    {
        int mid = (left + right) >> 1;
        if (arr[right] < arr[mid])
            std::swap(arr[right], arr[mid]);
        //此时右边界固定为>pivot的数
        if (arr[right] < arr[left])
            std::swap(arr[right], arr[left]);
        //此时左边界固定为<pivot的数
        if (arr[mid] < arr[left])
            std::swap(arr[mid], arr[left]);
        //把pivot交换到右边界的前一个位置
        std::swap(arr[mid], arr[right - 1]);
        return arr[right - 1];
    }
};

int main()
{
    Solution s;
    vector<int> vnTest{4, 5, 1, 6, 2, 7, 3, 8};
    auto result = s.GetLeastNumbers_Solution(vnTest, 3);
    for (auto x : result)
        cout << x << " ";
    cout << endl;

    vnTest = {4, 5, 1, 6, 2, 7, 3, 8, 2};
    result = s.GetLeastNumbers_Solution(vnTest, 4);
    for (auto x : result)
        cout << x << " ";
    cout << endl;

    vnTest = {4, 5, 1, 6, 2, 7, 3, 8};
    result = s.GetLeastNumbers_QS(vnTest, 3);
    for (auto x : result)
        cout << x << " ";
    cout << endl;

    vnTest = {4, 5, 1, 6, 2, 7, 3, 8, 2};
    result = s.GetLeastNumbers_QS(vnTest, 4);
    for (auto x : result)
        cout << x << " ";
    cout << endl;
}