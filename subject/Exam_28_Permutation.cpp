#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm> //标准库的交换操作用std::move做，更快
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;
/**
 * 字符串的排列
 * 思路：
 * 以填n个位置的方式思考，第一个位置有n个可能，轮流在n个字符到这个位置，固定了第一个位置后，
 * 要填第二个位置，让剩下的字符轮流到这个位置，显然这是个递归问题
 */

class Solution
{
  public:
    vector<string> Permutation(string str)
    {
        if (str.empty())
            return vector<string>();
        set<string> setOutput; //牛客网的测试用例输入字符有可能重复，用set屏蔽重复
        GenPermutationStr(setOutput, str, 0);
        vector<string> output(setOutput.begin(), setOutput.end());
        return output;
    }

  private:
    void GenPermutationStr(set<string> &output, string str, size_t nPos)
    {
        if (nPos == str.size() - 1)
        {
            output.insert(str);
            return;
        }
        for (size_t i = nPos; i < str.size(); ++i)
        {
            std::swap(str[i], str[nPos]);
            GenPermutationStr(output, str, nPos + 1);
        }
    }
};

int main()
{
    Solution s;
    vector<string> vsTest = s.Permutation("abc");
    for (const auto &s : vsTest)
        cout << s << " ";
    cout << endl;
    vsTest = s.Permutation("aa");
    for (const auto &s : vsTest)
        cout << s << " ";
    cout << endl;
    return 0;
}