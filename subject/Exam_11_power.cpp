#include <iostream>
#include <cmath>
#include <stdexcept>

/**
 * 思路:
 * 提高效率的解法：a^n
 *      若n为偶数，则a^n=a^(n/2)*a^(n/2)
 *      若n为偶数，则a^n=a^((n-1)/2)*a^((n-1)/2)*a
 * 主体计算过程用递归，终止条件是指数变为0或1；
 * 奇偶用&0x01判断，除以2用>>1,浮点型判断是否为0不能用==
 * 另外，需要考虑（1）指数是正或负数的情况（2）底数是否为0
 * 特例：底数为0时，指数为负抛出异常，指数为0返回1，指数为正返回0
 */
class Solution
{
  public:
    double Power(double base, int exponent)
    {
        //判断double类型是否为0不能用==，底数为0，指数不能为0
        if (base > -1e-8 && base < 1e-8 && exponent < 0)
            throw std::invalid_argument("0 can be denominator");
        double res;
        if (exponent < 0) //指数为负数
            res = 1.0 / PowerRecursion(base, std::abs(exponent));
        else
            res = PowerRecursion(base, exponent);
        return res;
    }
    double PowerRecursion(double base, unsigned int exponent)
    {
        if (exponent == 0)
            return 1.0;
        if (exponent == 1)
            return base;
        //整数除法向下取整，所以此处可以不判断奇偶
        double res = PowerRecursion(base, exponent >> 1);
        res *= res;
        if (exponent & 0x01) //判断奇偶性
            res *= base;
        return res;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    std::cout << s.Power(4, 3) << std::endl;   //指数为正奇数
    std::cout << s.Power(2, 4) << std::endl;   //指数为正偶数
    std::cout << s.Power(-2, -3) << std::endl; //底数为负数,指数为负数
    std::cout << s.Power(-2, 3) << std::endl;  //底数为负数，指数为正数
    std::cout << s.Power(2, 0) << std::endl;   //指数为0
    std::cout << s.Power(0, 3) << std::endl;   //底数为0，指数为3
    std::cout << s.Power(0, 0) << std::endl;   //底数为0，指数为0
    // std::cout << s.Power(0, -1) << std::endl;  //底数为0
    std::cout << s.Power(2, -2) << std::endl; //指数为负数

    std::cout << "-----除以2测试-----" << std::endl;
    std::cout << (8 >> 1) << std::endl;
    std::cout << ((-55) >> 1) << std::endl;
    std::cout << std::pow(0, -1) << std::endl;
    std::cout << std::pow(0, 3) << std::endl;
    std::cout << std::pow(0, 0) << std::endl;
    return 0;
}