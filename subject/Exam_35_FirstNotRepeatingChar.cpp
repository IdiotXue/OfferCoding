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
 * 二叉树的深度&判断平衡二叉树
 * 思路
 * （1）深度：像之前计算路径和一样，递归到null就返回0，否则就+1再返回
 * （2）平衡二叉树：即任意结点的左右子树深度相差不超过1
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