#include <iostream>
#include <stdexcept>
#include <string>
using std::string;

/**
 * 打印1到最大的n位数
 * 思路:
 * 关键点是解决long long都会溢出的情况
 * 首选用字符串模拟加法，用最高位是否进位判断是否到最大
 * 注意：字符串的高位对应者十进制值的低位
 * 特例：输入负数或0
 */
class Solution
{
  public:
    void Print1ToMaxNbit(int nDigits)
    {
        if (nDigits <= 0)
            return;
        string str(nDigits, '0'); //初始化为全0
        while (StringPlusOne(str))
            std::cout << stoi(str) << " "; //转成int去掉无用的前置0
    }
    bool StringPlusOne(string &str)
    {
        int nDigits = str.size();                 //获取位数
        int nBitVal = str[nDigits - 1] - '0' + 1; //个位加1
        int nCarry;                               //存进位
        while (nDigits--)
        {
            nCarry = 0;        //每次进入循环时进位位都是0
            if (nBitVal == 10) //有进位
            {
                if (nDigits == 0) //最高位进位表示已经到达最大的n位数
                    return false;
                else
                {
                    nCarry = 1; //进一位
                    nBitVal -= 10;
                }
            }
            str[nDigits] = '0' + nBitVal; //更新本位的数字字符
            if (!nCarry)                  //没有进位可以结束循环
                break;
            //有进位则需要更新nBitVal为下一位的值，并加上进位
            nBitVal = str[nDigits - 1] - '0' + nCarry;
        }
        return true; //正常完成计算返回true
    }
};

int main(int argc, char *argv[])
{
    int n;
    Solution s;
    while (std::cin >> n)
    {
        s.Print1ToMaxNbit(n);
        std::cout << "End" << std::endl;
    }
    return 0;
}