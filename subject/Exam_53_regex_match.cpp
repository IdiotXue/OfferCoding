#include <iostream>
using std::cout;
using std::endl;

/**
 * 正则表达式匹配
 * 思路：
 * 所有字符匹配整个模式降低了难度
 * 字符串与模式逐字符匹配，遇到‘.’就是简单的判为相等，遇到‘*'比较麻烦，因为可以使前一个字符无效或重复多次
 * 因此，逐字符判断的过程中每次都需判断下一个字符是否为‘*'
 *      若不是‘*’：直接判断是否相等，等后移，不等返回false
 *      若是‘*’：需先判断本字符是否相等
 *          不相等则在模式中跳到'*'后一个字符，是否匹配就取决与后面，显然需要递归
 *          相等（就麻烦了）则需知道要重复几次，这需要直到后面的字符串是否匹配，显然这个地方需要递归
 *              如果后面的匹配，返回true
 *              如果后面不匹配，可以保持模式不变，字符串后移
 * 
 */
class Solution
{
  public:
    bool match(char *str, char *pattern)
    {
        if (str == nullptr || pattern == nullptr)
            return false;
        return MatchRecur(str, pattern);
    }

  private:
    bool MatchRecur(char *str, char *pattern)
    {
        if (*str == '\0' && *pattern == '\0') //终止条件
            return true;
        while (*pattern != '\0' && *(pattern + 1) != '*') //模式后一个字符不是’*‘，循环判断即可
        {
            if (*str == *pattern || (*pattern == '.' && *str != '\0')) //这样判断，str先完也能返回false
                ++str, ++pattern;
            else
                return false;
            if (*str == '\0' && *pattern == '\0') //同时到末端
                return true;
        }
        if (*pattern == '\0') //pattern完，但str没完才会到此处
            return false;
        //到此处：模式的后一个字符是'*'，str不确定
        if (*str == *pattern || (*pattern == '.' && *str != '\0')) //str先完，该判断为false
        {
            if (MatchRecur(str + 1, pattern + 2)) //A*只匹配一个A（当前数目的A）试试
                return true;
            if (MatchRecur(str + 1, pattern)) //A*匹配一个A（当前数目的A）行不通，那加一个A试试
                return true;
            return MatchRecur(str, pattern + 2); //A*匹配那么多个A都行不通，那我不要匹配这个A*了试试
            //上面只是为了方便注释，可以直接写成两个或 Match() || Match() || Match()
        }
        else //字符不相等，跳过'*'
            return MatchRecur(str, pattern + 2);
    }
};
int main()
{
    Solution s;
    char str[] = "aaa";
    char pattern1[] = "a.a";
    cout << std::boolalpha << s.match(str, pattern1) << endl;
    char pattern2[] = "ab*ac*a";
    cout << std::boolalpha << s.match(str, pattern2) << endl;
    char pattern3[] = "aa.a";
    cout << std::boolalpha << s.match(str, pattern3) << endl;
    char pattern4[] = "ab*a";
    cout << std::boolalpha << s.match(str, pattern4) << endl;
}