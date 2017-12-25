#include <iostream>
#include <string>
using std::string;
/**
 * 思路:
 * 遍历一遍都能想到,换种方法:
 * 每次n & n-1都会把n最右边的1变为0;重复该运算几次才使n为0就有几个1
 * 变形：(1)一条语句判断一个正整数是不是2的整数次方：if((n&(n-1))==0)
 *      (2)输入两个整数m和n，计算需要改变m的二进制表示中的多少位，才能得到n:
 *         思路：m^n，然后统计结果中有多少位是1
 */
class Solution
{
  public:
    int NumberOf1(int n)
    {
        int count = 0;
        while (n)
        {
            ++count;
            n &= (n - 1);
        }
        return count;
    }
};
/**
 * 题目：Excel2003中，用A表示第1列，B表示第2列……Z表示第26列，AA表示第27列，
 *      AB表示第28列……以此类推。写一个函数，输入用字母表示的列号编码，输出他是第几列
 * 思路：
 * 字母表示的26进制，进制高位在数组低位
 */
class Solution1
{
  public:
    long TwentySixSystem(string str)
    {
        if (str.empty())
            return -1;
        long lCol = 0;
        //注意：进制高位在数组低位，如AB，str[0]是A，str[1]是B
        for (size_t i = 0; i < str.size(); ++i) //从进制高位开始
            lCol = 26 * lCol + (str[i] - 'A' + 1);
        return lCol;
    }
};
int main(int argc, char *argv[])
{
    Solution s;
    std::cout << s.NumberOf1(1) << std::endl;          //正数,1
    std::cout << s.NumberOf1(0x7FFFFFFF) << std::endl; //正数,31
    std::cout << s.NumberOf1(0x80000000) << std::endl; //负数,1
    std::cout << s.NumberOf1(0xFFFFFFFF) << std::endl; //负数,32
    std::cout << s.NumberOf1(0) << std::endl;          //负数,32
    std::cout << int(0x7FFFFFFF) << std::endl;
    std::cout << int(0x80000000) << std::endl;
    std::cout << int(0xFFFFFFFF) << std::endl;
    std::cout << "---------------" << std::endl;

    Solution1 s1;
    std::cout << s1.TwentySixSystem("A") << std::endl;  //1
    std::cout << s1.TwentySixSystem("Z") << std::endl;  //26
    std::cout << s1.TwentySixSystem("AB") << std::endl; //28
    std::cout << s1.TwentySixSystem("") << std::endl;   //空
    return 0;
}