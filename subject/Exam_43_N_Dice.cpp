#include <iostream>
#include <vector>
#include <cmath>   //std::pow
#include <iomanip> //std::setprecision
using std::cout;
using std::endl;
using std::vector;

/**
 * n个骰子的点数
 * 思路：
 * 骰子点数的取值范围是[n,6n]，n个骰子的组合数有6^n,
 * 关键点：加一个骰子，就能让上一次点数为K-1，K-2，K-3，K-4，K-5，K-6，变为点数是K
 * 所以K的出现次数就是上一次这6个数出现次数的和，显然，用两个数组模拟反复加骰子的过程即可，
 * 为了让索引更快，数组的小标代表求和值s
 */
class Solution
{
  public:
    void PrintProbabilityNDice(int n)
    {
        if (n < 1)
            return;
        const int kinds = 6; //骰子有6种点数
        vector<vector<int>> res(2, vector<int>(kinds * n + 1));
        size_t flag = 0;                    //用于交替选择两个数组
        for (size_t i = 1; i <= kinds; ++i) //第一个骰子先赋值，1到6各出现一次
            res[flag][i] = 1;
        for (int i = 2; i <= n; ++i) //从第二个骰子开始
        {
            for (int k = i; k <= kinds * i; ++k) //i个骰子的取值范围是[i,6i]
            {
                res[1 - flag][k] = 0;
                for (int pre = k - 1; (pre >= (k - 6)) && pre > 0; --pre) //值K出现的次数是上一次K-1到K-6出现次数之和
                    res[1 - flag][k] += res[flag][pre];
            }
            flag = 1 - flag;
        }
        double total = std::pow(kinds, n);
        for (int i = n; i <= kinds * n; ++i)
            cout << i << ":" << res[flag][i] << ":"
                 << std::setprecision(3) << res[flag][i] / total << "  ";
        cout << endl;
    }
};

int main()
{
    Solution s;
    s.PrintProbabilityNDice(1);
    cout << endl;
    s.PrintProbabilityNDice(2);
    cout << endl;
    s.PrintProbabilityNDice(3);
}