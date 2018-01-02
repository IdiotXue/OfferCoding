#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
using std::cout;
using std::endl;
using std::numeric_limits;
using std::vector;

/**
 * 从1到n整数中1出现的次数
 * 思路
 * 找规律，书上讲得不清楚
 * 这篇文章的解释比较清晰：http://blog.csdn.net/yi_afly/article/details/52012593
 * 核心是，分析每一位从0-9时，1会出现的次数，这样就能通过 进位次数×1出现次数，直接计算，而不需要
 * 对每个数字数1的个数
 */
class Solution
{
  public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        if (n < 1)
            return 0;
        int count = 0; //累加各个位1的出现的次数
        int base = 1;  //从个位开始数
        int round = n;
        int digit;
        while (round > 0)
        {
            digit = round % 10; //取出每一位数字
            round /= 10;        //计算本位的进位次数
            count += round * base;
            if (digit > 1)
                count += base;
            else if (digit == 1)
                count += (n % base + 1);
            base *= 10;
        }
        return count;
    }
};

int main()
{
    Solution s;
    cout << s.NumberOf1Between1AndN_Solution(12) << endl;
    cout << s.NumberOf1Between1AndN_Solution(20) << endl;
}