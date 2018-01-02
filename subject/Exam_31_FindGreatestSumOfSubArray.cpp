#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
using std::cout;
using std::endl;
using std::numeric_limits;
using std::vector;

/**
 * 连续字数组的最大和
 * 思路
 * 用一个nCurrSum记录累加和，nMaxSum记录出现的最大值，当nCurrSum<0时，表示之前
 * 累加到此处是负数，与其继续加，不如舍弃重新开始，注意，此处的最大值可能是负数
 * 也可以用动态规划的分析方法：本质还是利用nCurrSum<0，还不如重新开始
 */
class Solution
{
  public:
    int FindGreatestSumOfSubArray(vector<int> array)
    {
        if(array.empty())
            throw std::invalid_argument("arry is empty");
        int nCurrSum = 0, nMaxSum = numeric_limits<int>::min(); //相当于0x8000000,
        for (auto val : array)
        {
            if (nCurrSum < 0)
                nCurrSum = val;
            else
                nCurrSum += val;
            if (nCurrSum > nMaxSum)
                nMaxSum = nCurrSum;
        }
        return nMaxSum;
    }
};

int main()
{
    Solution s;
    vector<int> vnTest{6, -3, -2, 7, -15, 1, 2, 2};
    cout << s.FindGreatestSumOfSubArray(vnTest) << endl;
}