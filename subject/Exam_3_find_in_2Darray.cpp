#include <iostream>
#include <vector>
using std::vector;
/**
 * 思路：
 * 从右上开始搜，比元素y大则行+1（排除一行），小则列-1（排除一列）,
 * 直到等于为止，也可能找不到
 * 特例：传入数组为空
 */
class Solution
{
  public:
    bool Find(int target, vector<vector<int>> &array)
    {
        if (array.size() == 0)
            return false;
        vector<int>::size_type row = 0;
        int col = array[0].size() - 1;
        bool flag = false;
        while ((row < array.size()) && (col >= 0))
        {
            if (target < array[row][col])
                --col;
            else if (target > array[row][col])
                ++row;
            else
            {
                flag = true;
                break;
            }
        }
        return flag;
    }
};
int main(int argc, char *argv[])
{
    int target = 10;
    vector<vector<int>> array{
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}};
    Solution s;
    if (s.Find(target, array))
        std::cout << "can find" << std::endl;
    else
        std::cout << "can not find" << std::endl;
}