#include <iostream>
using std::cout;
using std::endl;

/**
 * 数组中的重复数字
 * 思路：
 * 直观的做法是Hash
 * 更高效的做法，大循环按顺序扫描，对比每个位置的下标是否与其元素相等，相等则下一个
 *                  小循环 不相等则对比该元素 与 以该元素为下标的元素是否相等，相等则找到了重复的数字
 *                      不想等则交换，即把该元素放到了正确的位置，重复小循环的过程
 */
class Solution
{
  public:
    bool duplicate(int numbers[], int length, int *duplication)
    {
        if (numbers == nullptr || length < 2)
            return false;
        for (int i = 0; i < length; ++i)
            if (numbers[i] < 0 || numbers[i] > length - 1) //得先判断，否则下面可能越界
                return false;
        for (int i = 0; i < length; ++i)
        {
            while (numbers[i] != i)
            {
                if (numbers[i] == numbers[numbers[i]])
                {
                    *duplication = numbers[i];
                    return true;
                }
                else
                    std::swap(numbers[i], numbers[numbers[i]]);
            }
        }
        return false;
    }
};
int main()
{
    Solution s;
    int ret;
    int numbers[] = {2, 3, 1, 0, 2, 5, 3};
    if (s.duplicate(numbers, 7, &ret))
        cout << ret << endl;
}