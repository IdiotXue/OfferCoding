#include <iostream>
#include <vector>
using std::vector;
/**
 * 思路
 * 斐波那契:（1）n=0时f(n)=0（2）n=1时f(n)=1（3）n>1时f(n)=f(n-1)+f(n-2)
 * 值  {0,1,1,2,3,5,8,13,21,34}
 * 下标{0,1,2,3,4,5,6, 7, 8, 9}
 * 从f(0)和f(1)开始加，每次求和后的值需保留到下一次
 * 特例：n=0或1，直接返回
 * 变形题目：青蛙跳台/变态青蛙跳台/小矩形覆盖大矩形
 */
class Solution
{
  public:
    int Fibonacci(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        int f1 = 0, f2 = 1, fn;
        while (--n)
        {
            fn = f2 + f1;
            f1 = f2;
            f2 = fn;
        }
        return fn;
    }
};
int main(int argc, char *argv[])
{
    Solution s;
    std::cout<<s.Fibonacci(3)<<std::endl;
    std::cout<<s.Fibonacci(8)<<std::endl;
    return 0;
}