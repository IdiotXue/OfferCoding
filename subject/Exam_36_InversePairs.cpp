#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 数组中的逆序对
 * 思路
 * 逆序对这个概念是排序算法中提出的，排序就是消除逆序，插入排序的复杂度是O(n^2)就是因为每次只消除一个逆序
 * 想要一个个消除逆序又要快，就是归并（分治）；
 * 关键的修改是：合并不是从头开始比较，而是从尾部开始，当前面数组的尾大于后面数组的尾时，马上就能计算出逆序数量
 */
class Solution
{
  public:
    int InversePairs(vector<int> data)
    {
        if (data.empty())
            return 0;
        vector<int> vnTemp(data.size());
        // return IPRecursion(data, vnTemp, 0, data.size() - 1);
        //牛客网的测试用例要求数值太大时对1000000007求余
        return IPRecursion(data, vnTemp, 0, data.size() - 1) % 1000000007; 
    }

  private:
    int IPRecursion(vector<int> &data, vector<int> &vnTemp, int left, int right)
    {
        if (left >= right) //终止条件
            return 0;
        int mid = (left + right) >> 1;
        //分
        // int nInverLeft = IPRecursion(data, vnTemp, left, mid);
        // int nInverRight = IPRecursion(data, vnTemp, mid + 1, right);
        int nInverLeft = IPRecursion(data, vnTemp, left, mid) % 1000000007;
        int nInverRight = IPRecursion(data, vnTemp, mid + 1, right) % 1000000007;
        //治
        int nLeftPos = mid, nRightPos = right, nTempPos = right, nInver = 0;
        while (nLeftPos >= left && nRightPos >= mid + 1)
        {
            if (data[nLeftPos] > data[nRightPos])
            {
                vnTemp[nTempPos--] = data[nLeftPos--];
                nInver += (nRightPos - mid); //逆序数计算
                if (nInver > 1000000007)
                    nInver %= 1000000007;
            }
            else //注意：相等时放右边，让左边继续与下一个右边比较
                vnTemp[nTempPos--] = data[nRightPos--];
        }
        while (nLeftPos >= left)
            vnTemp[nTempPos--] = data[nLeftPos--];
        while (nRightPos >= mid + 1)
            vnTemp[nTempPos--] = data[nRightPos--];
        for (int i = left; i <= right; ++i)
            data[i] = vnTemp[i];
        // return (nInverLeft + nInverRight + nInver);
        return (nInverLeft + nInverRight + nInver) % 1000000007;
    }
};

int main()
{
    Solution s;
    cout << s.InversePairs({7, 5, 6, 4}) << endl;
}