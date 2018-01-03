#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

/**
 * 第一个只出现一次的数
 * 思路
 * 第一次遍历用hash表保存出现次数
 * 第二次遍历找出第一个只出现一次的数
 */

class Solution
{
  public:
    int FirstNotRepeatingChar(string str)
    {
        if (str.empty())
            return -1;
        unordered_map<char, int> mapCount;
        for (const auto &c : str)
            ++mapCount[c];
        for (size_t i = 0; i < str.size(); ++i)
            if (mapCount[str[i]] == 1)
                return int(i);
        return -1; //没有这样的字符返回-1
    }
};

int main()
{
    Solution s;
    cout << s.FirstNotRepeatingChar("adebeadc") << endl;
}