#include <iostream>
#include <algorithm> //std::min
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 丑数
 * 思路
 * 遍历判断每一个整数是不是丑数的做法肯定不可取。
 * 显然反过来，在已有丑数的基础上乘2,3,5得到下一个丑数会更快，那么问题就变成怎么让生成的丑数是有序的
 * 答案当然是：取每次取乘2,3,5中最小的，显然同一个丑数肯定是乘以2最小，但这个数乘过2之后，就只能乘3,5了，
 * 而后面的丑数乘2和这个丑数乘以3,5比较谁小，那就不一定了。
 * 因此，需要三个变量分别标记已经乘过2,3,5的数
 */
class Solution
{
  public:
    int GetUglyNumber_Solution(int index)
    {
        if (index <= 0)
            return 0;
        vector<int> vnUgly(index);
        vnUgly[0] = 1; //第一个丑数是1
        size_t index2 = 0, index3 = 0, index5 = 0;
        for (size_t i = 1; i < vnUgly.size(); ++i)
        {
            vnUgly[i] = std::min(vnUgly[index2] * 2,
                                 std::min(vnUgly[index3] * 3, vnUgly[index5] * 5));
            if (vnUgly[i] == vnUgly[index2] * 2)
                ++index2;
            if (vnUgly[i] == vnUgly[index3] * 3)
                ++index3;
            if (vnUgly[i] == vnUgly[index5] * 5)
                ++index5;
        }
        return vnUgly[index - 1];
    }
};

int main()
{
    Solution s;
    cout << s.GetUglyNumber_Solution(7) << endl; //8
}