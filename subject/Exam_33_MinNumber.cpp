#include <iostream>
#include <algorithm> //std::sort
#include <vector>
#include <string> //std::to_string
using std::cout;
using std::endl;
using std::string;
using std::vector;

/**
 * 把数组排成最小的数
 * 思路
 * 数字ab<ba,则让a排在前面，否则让b排在前面,简单的说，让高位小的排在前面，显然基于这个规则对数组排序即可
 * 定义新的比较规则，以匿名函数传给sort排序就行了
 */
class Solution
{
  public:
    string PrintMinNumber(vector<int> numbers)
    {
        std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
            string A = std::to_string(a) + std::to_string(b);
            string B = std::to_string(b) + std::to_string(a);
            return A < B; //A比较小，则为a<b，a排在前面
        });
        string output("");
        for (auto x : numbers)
            output += std::to_string(x);
        return output;
    }
};

int main()
{
    Solution s;
    cout << s.PrintMinNumber({3,32,321}) << endl;

    //string的默认排序测试
    string a = "322", b = "324", c = "432";
    cout << std::boolalpha << (a < b) << endl;
    cout << std::boolalpha << (a < c) << endl;
}