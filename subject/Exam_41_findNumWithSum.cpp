#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
using std::cout;
using std::endl;
using std::vector;

/**
 * 和为s的两个数字，只输出乘积最小的
 * 思路：
 * 数组是递增排序，那么从两边开始，left+right>s，则right向左一位；<s则left向右一位
 * 
 * 和为S的连续正数序列
 * 思路：
 * 依然以一大一小两个变量来指定序列的范围，从1和2开始，<sum则++big，大于sum则--small，一直向前推进
 * 因为序列必须至少两个数字，所以终止条件可以是small >= (1+s)/2
 */
class Solution
{
  public:
    //和为s的两个数字，只输出乘积最小的
    vector<int> FindNumbersWithSum(vector<int> array, int sum)
    {
        if (array.empty())
            return vector<int>();
        size_t left = 0, right = array.size() - 1;
        int s;                                         //保存临时加和
        int product = std::numeric_limits<int>::max(); //保存积
        int small, big;                                //牛客网要求返回乘积最小的一对
        while (left < right)
        {
            s = array[left] + array[right];
            if (s < sum)
                ++left;
            else if (s > sum)
                --right;
            else
            {
                if (array[left] * array[right] < product)
                {
                    small = array[left];
                    big = array[right];
                    product = array[left] * array[right];
                }
                ++left;
            }
        }
        if (product == std::numeric_limits<int>::max())
            return vector<int>();
        vector<int> output(2);
        output[0] = small;
        output[1] = big;
        return std::move(output); //移动而非复制
    }
    //和为S的连续正数序列
    vector<vector<int>> FindContinuousSequence(int sum)
    {
        if (sum < 3)
            return vector<vector<int>>();
        int small = 1, big = 2;
        int nCurrSum = small + big;
        int end = (1 + sum) >> 1;
        vector<vector<int>> output;
        while (small < end)
        {
            if (nCurrSum < sum)
            {
                ++big;
                nCurrSum += big;
            }
            else if (nCurrSum > sum)
            {
                nCurrSum -= small;
                ++small;
            }
            else
            {
                vector<int> res(big - small + 1);
                for (size_t i = 0; i < res.size(); ++i)
                    res[i] = small + i;
                output.push_back(std::move(res)); //移动而非复制
                nCurrSum -= small;
                ++small;
            }
        }
        return std::move(output);
    }
};

int main()
{
    Solution s;
    auto res = s.FindNumbersWithSum({1, 2, 4, 7, 11, 15}, 15);
    for (auto x : res)
        cout << x << " ";
    cout << endl;

    auto output = s.FindContinuousSequence(15);
    for (const auto &arr : output)
    {
        for (auto val : arr)
            cout << val << " ";
        cout << endl;
    }
}