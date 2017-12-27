#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 顺时针打印矩阵
 * 思路:
 * 从外向里一圈一圈的遍历顺时针打印即可，可以通过2个行标记up，down
 * 和2个列标记来left，right，记录遍历到了哪一圈
 * 每次++up，--down，++left，--right

 * 当up>down或left>right时停止
 * 需考虑几种情形：
 * （1）最后一圈只有一个元素（2）最后一圈是一行或一列
 * （3）最后一圈刚好是一圈（4）矩阵为空
 */
class Solution
{
  public:
    vector<int> printMatrix(vector<vector<int>> &matrix)
    {
        //矩阵为空，逻辑或判断前半部分为真则不执行后半部分
        if (matrix.empty() || matrix[0].empty())
            return vector<int>();
        int up = 0, down = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;
        vector<int> output;
        //先分配空间，使push_back时不因空间不足而重新分配浪费时间
        output.reserve((down + 1) * (right + 1));
        while (up <= down && left <= right)
        {
            for (int i = left; i <= right; ++i)
                output.push_back(matrix[up][i]);
            for (int i = up + 1; i <= down; ++i)
                output.push_back(matrix[i][right]);
            if (up != down) //考虑最后一圈是一行
                for (int i = right - 1; i >= left; --i)
                    output.push_back(matrix[down][i]);
            if (left != right) //考虑最后一圈是一列
                for (int i = down - 1; i > up; --i)
                    output.push_back(matrix[i][left]);
            ++up;
            --down;
            ++left;
            --right;
        }
        return output;
    }
};

void Test(int columns, int rows)
{
    if (columns < 1 || rows < 1)
        return;
    Solution s;
    vector<vector<int>> martix(rows, vector<int>(columns));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
            martix[i][j] = i * columns + j + 1;
    }
    vector<int> output = s.printMatrix(martix);
    for (auto x : output)
        cout << x << " ";
    cout << endl;
}
int main()
{
    /*
    1     */
    Test(1, 1);

    /*
    1    2
    3    4*/
    Test(2, 2);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16 */
    Test(4, 4);
	/*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    21   22   23   24   25
    */
    Test(5, 5);

    /*
    1
    2
    3
    4
    5
    */
    Test(1, 5);

    /*
    1    2
    3    4
    5    6
    7    8
    9    10
    */
    Test(2, 5);

    /*
    1    2    3
    4    5    6
    7    8    9
    10   11   12
    13   14   15
    */
    Test(3, 5);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    17   18   19   20
    */
    Test(4, 5);

    /*
    1    2    3    4    5
    */
    Test(5, 1);

    /*
    1    2    3    4    5
    6    7    8    9    10
    */
    Test(5, 2);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14    15
    */
    Test(5, 3);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    */
    Test(5, 4);
    return 0;
}
