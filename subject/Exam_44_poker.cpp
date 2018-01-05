#include <iostream>
#include <algorithm> //std::sort
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 扑克牌顺子
 * 思路：
 * 题意是把大小王当做0输入，可以对数组排序,然后遍历一遍记录0的个数和非0的相邻数字之间相差多少，
 * 超过一的部分减掉相应个数的0，当最终0的个数大于或等于0的时候是顺子
 * 特例：有非零的相等数字
 */
class Solution
{
  public:
    bool IsContinuous(vector<int> numbers)
    {
        if (numbers.size() < 5)
            return false;
        std::sort(numbers.begin(), numbers.end());
        int numOf0 = 0;
        int diff;
        for (size_t i = 0; i < numbers.size(); ++i)
        {
            if (numbers[i] == 0)
                ++numOf0;
            else if (i != 0 && numbers[i - 1] != 0)
            {
                diff = numbers[i] - numbers[i - 1];
                if (diff == 0) //有两个非零相等的数
                    return false;
                while ((diff--) > 1)
                    if ((--numOf0) < 0)
                        return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution s;
    cout << std::boolalpha << s.IsContinuous({0, 0, 1, 3, 4}) << endl;
    cout << std::boolalpha << s.IsContinuous({0, 0, 1, 4, 4}) << endl;
    cout << std::boolalpha << s.IsContinuous({1, 4, 5, 0, 0}) << endl;
    cout << std::boolalpha << s.IsContinuous({3, 1, 0, 0, 5}) << endl;
}