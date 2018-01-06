#include <iostream>
#include <algorithm> //std::sort
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 不用加减乘除做加法
 * 思路：
 * 加减乘除都不能用了，就只剩下位运算了吧，位运算的逐位二进制相加得到的结果转成十进制
 * 与十进制相加是一样的，所以往位运算上想就行了
 * 异或^可以得到不进位时的和res，与&后左移动<<一位可以得到需要进位加1数carray，此时
 * 再将res和carry异或又能得到不进位的和，但可能还有进位，因此反复做这个过程直到carry为0为止
 */
class Solution
{
  public:
    int Add(int num1, int num2)
    {
        int res;   //不进位时的和
        int carry; //需要进位加1的位
        do
        {
            res = num1 ^ num2;
            carry = (num1 & num2) << 1;
            num1 = res;
            num2 = carry;
        } while (num2);
        return res;
    }
};

int main()
{
    Solution s;
    cout << s.Add(5, 7) << endl;
    //注意负数在计算机是用补码表示的，即 -5:1011（1101的补码），-7:1001，最高位是符号位
    cout << s.Add(-5, -7) << endl; 
    

    char a = -5, b = -7;
    cout << (a >> 1) << endl;
    cout << (a << 1) << endl;
    cout << (a ^ b) << endl;
}