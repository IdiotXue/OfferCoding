#include <iostream>
#include <cstring>
/**
 * 思路：
 * 遍历一次字符数组，看有多少空格，以此计算替换后字符串的长度，
 * 用两个指针，一个指向字符数组的尾部，一个指向替换后数组的尾部，
 * 两个指针同时移动完成拷贝和替换的工作，这样只需一次拷贝
 * 特例：(1)字符数组为空或length为0 (2)str容量不足
 * 若允许创建新字符串就没难度了
 */
class Solution
{
  public:
    void replaceSpace(char *str, int length)
    {
        if (str == nullptr || length <= 0)
            return;
        size_t numOfSpace = 0, i = 0;
        for (; str[i] != '\0'; ++i)
            if (str[i] == ' ')
                ++numOfSpace;
        int newStrLen = i + 2 * numOfSpace; //比实际长度少1，因为从0开始
        if (newStrLen + 1 > length)         //str容量不足
            return;
        int nOld = i, nNew = newStrLen;
        while (nNew > 0)
        {
            if (str[nOld] == ' ')
            {
                str[nNew--] = '0';
                str[nNew--] = '2';
                str[nNew--] = '%';
                --nOld;
            }
            else
                str[nNew--] = str[nOld--];
        }
    }
};
int main(int argc, char *argv[])
{
    char str[] = "We Are Happy"; //12个字符，不包括\0
    std::cout << str << std::endl;
    std::cout << strlen(str) << std::endl;
    Solution s;
    s.replaceSpace(str, 20);
    std::cout << str << std::endl;
}