#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

/**
 * 把字符串转换成整数
 * 思路：
 * 
 */
class Solution
{
  public:
    int StrToInt(string str)
    {
        if (str.empty())
            return 0;
        int num = 0;
        bool minus = false;
        for (size_t i = 0; i < str.size(); ++i)
            if ('0' <= str[i] && str[i] <= '9')
                num = num * 10 + (str[i] - '0');
            else if (i == 0 && (str[i] == '+' || str[i] == '-'))
            {
                if (str[i] == '-')
                    minus = true;
            }
            else
                return 0;
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
    cout << s.StrToInt("-12a34") << endl;
}