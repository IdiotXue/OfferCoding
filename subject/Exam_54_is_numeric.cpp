#include <iostream>
#include <string>
#include <cctype>
using std::cout;
using std::endl;
using std::string;

/**
 * 表示数值的字符串
 * 思路：常规逻辑题
 * （1）主要在重要结点判断有无正负号、小数点、E（2）数字都是扫描略过
 */
class Solution
{
  public:
    bool isNumeric(const string &str)
    {
        if (str.empty())
            return false;
        size_t index = 0;
        if (str[index] == '+' || str[index] == '-')
            ++index;
        if (index == str.size())
            return false;

        scanDigits(str, index);
        if (index == str.size()) //普通整数
            return true;
        else
        {
            if (str[index] == '.') //浮点数
            {
                ++index;
                scanDigits(str, index);
                if (index != str.size() && (str[index] == 'e' || str[index] == 'E'))
                    return isExponential(str, index);
                return index == str.size(); //普通浮点数 或 false
            }
            else if (str[index] == 'e' || str[index] == 'E')
                return isExponential(str, index);
            return false; //不是整数、不是浮点、也不是科学计数，那肯定false
        }
    }

  private:
    inline void scanDigits(const string &str, size_t &index)
    {
        while (index != str.size() && std::isdigit(str[index])) //扫描数字
            ++index;
    }
    bool isExponential(const string &str, size_t &index)
    {
        if (str[index] != 'e' && str[index] != 'E')
            return false;
        ++index;
        if (str[index] == '+' || str[index] == '-')
            ++index;
        if (index == str.size())
            return false;
        scanDigits(str, index);
        return index == str.size();
    }
};
int main()
{
    Solution s;
    cout << "+100: " << std::boolalpha << s.isNumeric("+100") << endl;
    cout << "5e2: " << std::boolalpha << s.isNumeric("5e2") << endl;
    cout << "3.1416: " << std::boolalpha << s.isNumeric("3.1416") << endl;
    cout << "-1E-16: " << std::boolalpha << s.isNumeric("-1E-16") << endl;

    cout << "12e: " << std::boolalpha << s.isNumeric("12e") << endl;
    cout << "1a3.14: " << std::boolalpha << s.isNumeric("1a3.14") << endl;
    cout << "1.2.3: " << std::boolalpha << s.isNumeric("1.2.3") << endl;
    cout << "12e+4.3: " << std::boolalpha << s.isNumeric("12e+4.3") << endl;
}