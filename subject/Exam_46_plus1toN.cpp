#include <iostream>
#include <algorithm> //std::sort
#include <vector>
#include <functional>
using std::cout;
using std::endl;
using std::vector;

/**
 * 求1+2+3+...+n不用for,while,if,和乘除
 * 思路：
 * （1）构造函数法：最容易想到的是vector<A>把A构造n次,每次对其静态变量+1（循环）
 * （2）函数对象法：函数对象数组保存了两个函数，一个做加法操作，一个是递归的终止条件，1到N都可以转为true，而0是false，依靠这种1,0来切换调用哪个函数（递归）
 * （3）类模板递归特例化，这个真想不到；利用编译器类模板特例化时的一个特点：已提供特例化的版本，直接用我们提供的，而不由编译器生成
 */
class Solution
{
  public:
    int Sum_Solution(int n)
    {
        CTemp::Reset();
        vector<CTemp> vTemp(n);
        return CTemp::GetSum();
    }
    class CTemp
    {
      public:
        CTemp()
        {
            ++m_sN;
            m_sSum += m_sN;
        }
        static void Reset() { m_sN = m_sSum = 0; }
        static int GetSum() { return m_sSum; };

      private:
        static int m_sSum;
        static int m_sN;
    };

    static int Sum_Stop(int n)
    {
        return 0;
    }
    static int Sum_Solution2(int n)
    {
        static vector<std::function<int(int)>> func = {Sum_Stop, Sum_Solution2};
        return func[!!n](n - 1) + n;
    }
};
int Solution::CTemp::m_sSum = 0;
int Solution::CTemp::m_sN = 0;

/**
 * 方法3，类模板特例化，书上用enum是因为C++11之前不支持类内初始化,
 * 所以借助enum的特性，C++11开始支持
 */
template <int n>
struct Sum_Solution4
{
    int N = Sum_Solution4<n - 1>().N + n;
};
template <>
struct Sum_Solution4<1>
{
    int N = 1;
};

int main()
{
    Solution s;
    cout << s.Sum_Solution(5) << endl;
    cout << s.Sum_Solution(6) << endl;

    cout << s.Sum_Solution2(6) << endl;

    Sum_Solution4<6> a;
    cout << a.N << endl;
}