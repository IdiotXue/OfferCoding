#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
using std::cout;
using std::endl;
using std::string;

/**
 * 把字符串转换成整数
 * 思路：
 * 做法很简单，无非是num= num*10+x-'0',重点在于特殊情形的考虑
 * 特例（1）空字符串（2）存在不是数字或正负号的字符（3）正负号不在首位或只有正负号
 * （4）数值溢出
 * 牛客网的测试用例没有考虑只有正负号和溢出
 */
class Solution
{
  public:
    int StrToInt(string str)
    {
        if (str.empty()) //空字符串
            throw std::invalid_argument("input is empty");
        long num = 0; //64位系统，long是8字节，int是4字节
        bool minus = false;
        for (size_t i = 0; i < str.size(); ++i)
            if ('0' <= str[i] && str[i] <= '9')
            {
                num = num * 10 + (str[i] - '0');
                if ((!minus && (num > std::numeric_limits<int>::max())) || (minus && (-num < std::numeric_limits<int>::min())))
                    throw std::range_error("value out of range");
            }

            else if (i == 0 && (str[i] == '+' || str[i] == '-'))
            {
                if (str.size() == 1)
                    throw std::invalid_argument("input error");
                if (str[i] == '-')
                    minus = true;
            }
            else
                throw std::invalid_argument("input error");
        if (minus)
            num = -num;
        return num;
    }
};
int main()
{
    Solution s;
    cout << s.StrToInt("1234") << endl;
    cout << s.StrToInt("-1234") << endl;
    try
    {
        cout << s.StrToInt("-12a34") << endl;
    }
    catch (std::exception &e)
    {
        cout << e.what() << endl;
    }

    try
    {
        cout << s.StrToInt("2147483648") << endl;
    }
    catch (std::exception &e)
    {
        cout << e.what() << endl;
    }

    cout << std::numeric_limits<int>::max() << endl;
    cout << std::numeric_limits<int>::min() << endl;
    cout << sizeof(long long) << endl;
    cout << sizeof(long) << endl;
    cout << sizeof(int) << endl;
}