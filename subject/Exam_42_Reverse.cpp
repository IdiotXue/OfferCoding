#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution
{
  public:
    /**
     * 翻转单词顺序
     * 思路
     * 先翻转整体再逐个单词翻转
     * 其实这个题直接用两个string临时变量从后往前复制str也挺方便
     */
    string ReverseSentence(string str)
    {
        if (str.empty())
            return "";
        int strLen = str.size();
        //1.翻转整体
        int left = 0, right = strLen - 1; //right必须是有符，防止unsigned时 0-1 不等于-1
        while (left < right)
            std::swap(str[left++], str[right--]); //内部是move而不是拷贝
        //2.逐个单词翻转
        left = 0;
        for (int i = 0; i < strLen; ++i)
            if (str[i] == ' ') //空格分隔单词
            {
                right = i - 1;
                while (left < right)
                    std::swap(str[left++], str[right--]);
                left = i + 1;
            }
            else if (i + 1 == strLen) //最后一个单词后没有空格
            {
                right = i;
                while (left < right)
                    std::swap(str[left++], str[right--]);
            }
        return std::move(str);
    }
    /**
     * 左旋转字符串
     * 思路：
     * 还是可以翻转，这次还更方便了只需要翻转两部分
     * ab|cdefg -> ba|gfedc -> cdefg|ab
     */
    string LeftRotateString(string str, int n)
    {
        int strLen = str.size();
        if (strLen == 0 || n <= 0 || n > strLen)
            return str;
        //1.逐个部分翻转
        int left = 0, mid = n - 1, right = strLen - 1;
        while (left < mid)
            std::swap(str[left++], str[mid--]);
        mid = n;
        while (mid < right)
            std::swap(str[mid++], str[right--]);
        //2.整体翻转
        left = 0, right = strLen - 1;
        while (left < right)
            std::swap(str[left++], str[right--]);
        return std::move(str);
    }
};

int main()
{
    Solution s;
    cout << s.ReverseSentence("I am a student.") << endl;
    cout << s.ReverseSentence("Wonderful") << endl;
    cout << s.LeftRotateString("abcdefg", 2) << endl;
}