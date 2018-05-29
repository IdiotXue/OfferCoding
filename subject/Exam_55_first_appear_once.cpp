#include <iostream>
#include <limits>
#include <vector>
using std::cout;
using std::endl;

/**
 * 字符流中第一个不重复的字符
 * 思路：常规逻辑题
 * （1）主要在重要结点判断有无正负号、小数点、E（2）数字都是扫描略过
 */
class Solution
{
  public:
    Solution() : index(0), m_occurAddr(256, -1) {}
    //Insert one char from stringstream
    void Insert(char ch)
    {
        if (m_occurAddr[ch] == -1) //没出现过
            m_occurAddr[ch] = index;
        else if (m_occurAddr[ch] >= 0) //重复
            m_occurAddr[ch] = -2;
        ++index;
    }
    //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        int minAddr = std::numeric_limits<int>::max();
        char c = '#';
        for (size_t i = 0; i < m_occurAddr.size(); ++i)
        {
            if (m_occurAddr[i] >= 0 && m_occurAddr[i] < minAddr)
            {
                minAddr = m_occurAddr[i];
                c = static_cast<char>(i);
            }
        }
        return c;
    }

  private:
    int index;                    //字符流目前的位置
    std::vector<int> m_occurAddr; //字符出现的位置≥0，-1表示没出现过，-2表示重复
};
//输入：google，输出：l
int main()
{
    Solution s;
    char a;
    while (std::cin >> a)
        s.Insert(a);
    cout << s.FirstAppearingOnce() << endl;
}