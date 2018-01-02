#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 数字在排序数组中出现的次数
 * 思路
 * 两次二分搜索先找到这个数的头和尾，相减即可
 */
struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
  public:
    int GetNumberOfK(vector<int> data, int k)
    {
        if (data.empty())
            return 0;
        int first = GetFirstK(data, k);
        if (first == -1)
            return 0;
        int last = GetLastK(data, k);
        return last - first + 1;
    }

  private:
    int GetFirstK(const vector<int> &data, int k)
    {
        int left = 0, right = data.size() - 1, mid;
        while (left <= right)
        {
            mid = (left + right) >> 1;
            if (k < data[mid])
                right = mid - 1;
            else if (k > data[mid])
                left = mid + 1;
            else if (mid == 0 || data[mid - 1] != k) //第一个k
                return mid;
            else
                right = mid - 1;
        }
        return -1; //找不到
    }
    int GetLastK(const vector<int> &data, int k)
    {
        int last = data.size() - 1;
        int left = 0, right = last, mid;
        while (left <= right)
        {
            mid = (left + right) >> 1;
            if (k < data[mid])
                right = mid - 1;
            else if (k > data[mid])
                left = mid + 1;
            else if (mid == last || data[mid + 1] != k) //最后一个k
                return mid;
            else
                left = mid + 1;
        }
        return -1; //找不到
    }
};

int main()
{
    Solution s;
    cout << s.GetNumberOfK({1, 1, 1, 2, 4, 6, 7}, 1) << endl;
    cout << s.GetNumberOfK({1, 2, 4, 6, 7, 8, 8, 8}, 8) << endl;
    cout << s.GetNumberOfK({1, 2, 4, 6, 7, 8, 8, 8}, 2) << endl;
    cout << s.GetNumberOfK({1, 2, 4, 6, 7, 8}, 0) << endl;
    cout << s.GetNumberOfK({1, 2, 4, 6, 7, 8}, 5) << endl;
    cout << s.GetNumberOfK({1, 2, 4, 5, 5, 5, 6, 7, 8}, 5) << endl;
}