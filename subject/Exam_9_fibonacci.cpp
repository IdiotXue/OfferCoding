#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
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
    /**
     * 青蛙跳台思路：
     * 1个台阶：1种方法f(1)；2个台阶：2种方法f(2)
     * 3个台阶：若先上1个，则为f(2)种方法；若先上2个，则为f(1)种方法，即f(2)+f(1)
     * 4个台阶：若先上1个，则为f(3)种方法；若先上2个，则为f(2)种方法，即f(3)+f(2)
     * 显然：斐波那契问题
     */
    int jumpFloor(int number)
    {
        if (number < 1)
            throw std::runtime_error("invaild input");
        if (number == 1)
            return 1;
        if (number == 2)
            return 2;
        int f1 = 1, f2 = 2, fn;
        for (int i = 3; i <= number; ++i)
        {
            fn = f2 + f1;
            f1 = f2;
            f2 = fn;
        }
        return fn;
    }
    /**
     * 变态青蛙跳台思路：
     * 1个台阶：1种方法f(1)
     * 2个台阶：若先上一个台阶，则为f(1)中方法；也可以直接上2个台阶，即f(1)+1
     * 3个台阶：若先上1个，则为f(2)种方法；若先上2个，则为f(1)种方法；也可以上3个台阶，即即f(2)+f(1)+1
     * ...
     * n-1个台阶：f(n-2)+f(n-3)+...+f(1)+1
     * n个台阶：f(n-1)+f(n-1)...+f(1)+1
     * 错位向减得：f(n)-f(n-1)=f(n-1) => f(n)=2*f(n-1)=2^2*f(n-2)=...=2^(n-1)
     * 这应该是数学问题
     */
    int jumpFloorII(int number)
    {
        if (number < 1)
            throw std::runtime_error("invaild input");
        return pow(2.0, number - 1);
    }
    /**
     * 小矩形覆盖大矩形思路：
     * 若第一个矩形竖着放：则变为2*(n-1)的大矩形覆盖问题
     * 若第一个矩形横着放：其下方必定横放，则变为2*(n-2)的大矩形覆盖问题
     * 显然是斐波那契问题
     */
    int rectCover(int number)
    {
        if (number < 1) //根据题目要求调整
            return 0;
        if (number == 1)
            return 1;
        if (number == 2)
            return 2;
        int f1 = 1, f2 = 2, fn;
        for (int i = 3; i <= number; ++i)
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
    std::cout << s.Fibonacci(3) << std::endl;
    std::cout << s.Fibonacci(8) << std::endl;
    std::cout << s.jumpFloor(3) << std::endl;
    std::cout << s.jumpFloorII(3) << std::endl;
    std::cout << s.rectCover(3) << std::endl;
    return 0;
}