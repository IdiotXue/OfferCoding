#include <iostream>
#include <vector>
#include <stdexcept>
#include <unordered_map>
using std::cout;
using std::endl;
using std::unordered_map;
using std::vector;

/**
 * 数组中出现次数超过一半的数字
 * 思路
 * 容易想到的当然是空间换时间，用一个map记录出现次数，同时记录最大出现次数和对应元素，看有没有超过一半
 * 但是有更巧妙不用这么多辅助空间的：如果数字出现的次数超过数组长度的一半，也就超过其他所有数字出现次数的总和
 * 用一个变量res记录出现次数最多的数，count记录出现次数，遇到res就count+=1，不是就count-=1
 * 如果存在大于一半的数，那肯定是最后一次把count设为1的数
 */
class Solution
{
  public:
    int MoreThanHalfNum_Solution(vector<int> numbers)
    {
        if (numbers.empty())
            throw std::invalid_argument("array is empty");
        int res;
        size_t count = 0;
        for (size_t i = 0; i < numbers.size(); ++i)
        {
            if (count == 0) //如果是重置，会在下一个判断把count设为1
                res = numbers[i];
            if (res == numbers[i])
                ++count;
            else
                --count;
        }
        //有可能留到最后的不是大于一半的数，而只是最后一个数，所以需要判断
        count = 0;
        for (size_t i = 0; i < numbers.size(); ++i)
            if (numbers[i] == res)
                ++count;
        if ((count << 1) <= numbers.size())
            return 0; //牛客网的测试用例，没有返回0
        return res;
    }
    int MoreThanHalfNum_Solution2(vector<int> numbers)
    {
        if (numbers.empty())
            throw std::invalid_argument("array is empty");
        unordered_map<int, size_t> mapNum; //记录出现次数
        size_t nMax = 0;                   //记录最大出现次数
        int nKey;                          //记录最大出现次数的key
        for (size_t i = 0; i < numbers.size(); ++i)
        {
            ++mapNum[numbers[i]];
            if (mapNum[numbers[i]] > nMax)
            {
                nMax = mapNum[numbers[i]];
                nKey = numbers[i];
            }
        }
        if ((nMax << 1) <= numbers.size())
            return 0;
        return nKey;
    }
};

int main()
{
    Solution s;
    vector<int> vnTest{1, 2, 3, 2, 2, 2, 5, 4, 2};
    cout << s.MoreThanHalfNum_Solution(vnTest) << endl;
    cout << s.MoreThanHalfNum_Solution2(vnTest) << endl;

    vnTest = {1, 2, 3, 2, 4, 2, 5, 2, 3};
    cout << s.MoreThanHalfNum_Solution(vnTest) << endl;
    cout << s.MoreThanHalfNum_Solution2(vnTest) << endl;

    vnTest = {2, 2, 2, 2, 2, 1, 3, 4, 5};
    cout << s.MoreThanHalfNum_Solution(vnTest) << endl;
    cout << s.MoreThanHalfNum_Solution2(vnTest) << endl;

    vnTest = {1, 3, 4, 5, 2, 2, 2, 2, 2};
    cout << s.MoreThanHalfNum_Solution(vnTest) << endl;
    cout << s.MoreThanHalfNum_Solution2(vnTest) << endl;

    vnTest = {1};
    cout << s.MoreThanHalfNum_Solution(vnTest) << endl;
    cout << s.MoreThanHalfNum_Solution2(vnTest) << endl;
}