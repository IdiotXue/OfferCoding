#include <iostream>
#include <algorithm> //std::sort
#include <list>
using std::cout;
using std::endl;
using std::list;

/**
 * 圆圈中最后剩下的数
 * 思路：
 * （1）环形链表模拟过程就行了
 * （2）还有一个找规律的方法：首先明确一个性质，取模n（%n）就是余数取循环集0到n-1，刚好就是一圈的数字转回来
 *     取走第m-1个数后，接下来肯定是从m开始，则序列变成如下的左边;显然，正向隐射的公式是x'=(x-m)%n，那么方向映射
 *     就是x=(x'+m)%n，也就是说，只要已知n-1个数删m的时候剩下谁，就能通过这个公式隐射回去，终止条件显然是n=1时剩下0
 *     倒推回去n=2时，剩下x=(0+m)%n = (0+m)%2
 *  m -> 0
 *  m+1 -> 1
 *  m+2 -> 2
 *  ...
 *  n-1 -> n-1-m
 *  0 -> (0-m)%n = n-1+(-m)
 *  1 -> (1-m)%n = n-1 + (1-m) = n-m
 *  ...
 *  m-2 -> (m-2-m)%n = n-1-2 = n-3
 */
class Solution
{
  public:
    int LastRemaining_Solution(int n, int m)
    {
        if (n < 1 || m < 1)
            return -1;
        list<int> lnNum(n);
        int num = 0;
        for (auto &x : lnNum)
            x = num++;
        auto iter = lnNum.begin();
        while (lnNum.size() > 1)
        {
            for (int i = 1; i < m; ++i)
                if (++iter == lnNum.end())
                    iter = lnNum.begin();
            iter = lnNum.erase(iter);
            if (iter == lnNum.end())
                iter = lnNum.begin();
        }
        return lnNum.front();
    }
    int LastRemaining(int n, int m)
    {
        if (n < 1 || m < 1)
            return -1;
        int num = 0;
        for (int i = 2; i <= n; ++i)
            num = (num + m) % i;
        return num;
    }
};

int main()
{
    Solution s;
    cout << s.LastRemaining_Solution(5, 2) << endl; //0,1,2,3,4;{1,3,0,4,2}
    cout << s.LastRemaining_Solution(5, 3) << endl; //0,1,2,3,4;{2,0,4,1,3}
    cout << s.LastRemaining(5, 2) << endl; //0,1,2,3,4;{1,3,0,4,2}
    cout << s.LastRemaining(5, 3) << endl; //0,1,2,3,4;{2,0,4,1,3}
}