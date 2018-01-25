#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 构建乘积数组，不能用除法
 * 思路：
 * 把B每个元素的分为两部分做乘积操作，即每个元素以i为分界点，i之前按下标顺序从小到大乘出来，计算完这部分
 * i之后按下标从大到小，乘出来并与已算出来的i之前的部分相乘
 */
class Solution
{
  public:
    vector<int> multiply(const vector<int> &A)
    {
        if (A.size() < 2)
            return A;
        vector<int> B(A.size());
        B[0] = 1;
        for (size_t i = 1; i < A.size(); ++i) //i之前的部分
            B[i] = B[i - 1] * A[i - 1];
        long long tmp = 1;
        for (int i = A.size() - 2; i >= 0; --i)
        {
            tmp *= A[i + 1];
            B[i] *= tmp;
        }
        return std::move(B);
    }
};
int main()
{
    Solution s;
    vector<int> A{1, 2, 3};
    vector<int> B = s.multiply(A);
    for (auto x : B)
        cout << x << " ";
    cout << endl;
}