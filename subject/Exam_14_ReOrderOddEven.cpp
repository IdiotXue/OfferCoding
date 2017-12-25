#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using std::vector;

/**
 * 调整数组顺序使奇数位于偶数前面
 * 思路:
 * 会改变相对位置的方法：两个指针分别同时从左右两边向中间移动，左边在偶数停，右边在奇数挺，然后交换
 * 不改变相对位置的方法：创建临时vector保存奇数，将原vector中的偶数从尾部开始放，腾出前半部分的空间，再奇数拷贝回来
 * 显然，效率上前者高，后者O(n)
 * 函数对象function可以让代码的可扩展性更好,改判断条件方便
 */

class Solution
{
  public:
    void reOrderArray(vector<int> &array) { ReOrder(array, Solution::IsOdd); }
    void reOrderArrayChaos(vector<int> &array) { ReOrderChaos(array, Solution::IsOdd); }
    void PrintVec(vector<int> &array)
    {
        for (auto x : array)
            std::cout << x << " ";
        std::cout << std::endl;
    }

  private:
    inline static bool IsOdd(int val) { return val & 0x01; }
    /**
     * 保证奇数和奇数，偶数和偶数之间的相对位置不变
     */
    void ReOrder(vector<int> &array, std::function<bool(int)> iJudge)
    {
        if (array.empty())
            return;
        vector<int> vnTemp(array.size());
        int nNumOfOdd = 0;
        for (auto x : array)
            if (iJudge(x))
                vnTemp[nNumOfOdd++] = x;
        int nIndex = array.size() - 1;
        for (int i = array.size() - 1; i >= 0; --i)
            if (!iJudge(array[i]))
                array[nIndex--] = array[i];
        for (int i = 0; i < nNumOfOdd; ++i)
            array[i] = vnTemp[i];
        return;
    }
    /**
     * 相对位置改变
     */
    void ReOrderChaos(vector<int> &array, std::function<bool(int)> iJudge)
    {
        if (array.empty())
            return;
        size_t left = 0, right = array.size() - 1;
        while (left < right)
        {
            while (left < right && iJudge(array[left]))
                ++left; //奇数继续右移，偶数停止
            while (left < right && !iJudge(array[right]))
                --right; //奇数继续左移，奇数停止
            if (left < right)
                std::swap(array[left], array[right]);
        }
        return;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    vector<int> input{1, 4, 6, 5, 8, 7, 2};
    s.PrintVec(input);
    s.reOrderArray(input);
    s.PrintVec(input);

    vector<int> input1{1, 4, 6, 5, 8, 7, 2};
    s.PrintVec(input1);
    s.reOrderArrayChaos(input1);
    s.PrintVec(input1);
}