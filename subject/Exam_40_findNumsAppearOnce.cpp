#include <iostream>
#include <vector>
#include <stdexcept>
using std::cout;
using std::endl;
using std::vector;

/**
 * 只出现一次的一个数字
 * （1） 一个数只出现一次，而其他都出现2次（用异或使两次出现的清零）
 * 只能用常数辅助空间，想到了只用一个变量做位运算，因为有两个的数其对应位上的1都出现了2次，
 * 而只有一个的，对应位的1出现了1次，这个可以用异或（符合交换律）n^0=n,n^n=0
 * 
 * 扩展：
 * （2） 一个数只出现一或两次，而其他都出现3次（三次出现清零）
 * 位运算只能是0,1所以只能记录出现1次，再出现进位清零，所以关键就是找一种能记录出现2次，再出现进位清零的方法
 * 方法一：最容易想到，也是最通用方法，用一个sizeof(int)大小的数组，每次累加data元素每一位，得到每一位1的个数
 *       然后取模3，这样就得到要求的数每一位应该是1还是0；
 * 方法二：完全用位运算（比方法一快），核心思想是两个计数器，如果data元素的某一位出现1一次，用once记录，下次循环
 *       如果再出现1，就进位到twice，即把twice的相应位置1，once置0；当发现twice和once的某一位同时为1时，说明该位
 *       1出现了3次，可以清零了；最后如果是求出现一次的返回once，出现两次的返回twice
 * 第二个方法的优点是快，但缺点是通用性差，方法一可以找出只出现非3的倍数次的数，而且如果其他数都出现4\5\6等等也只需要修改取模的数
 */

/**
 * 数组中只出现一次的两个数字
 * 思路
 * （3）只需借助（1）的方法，然后思考如何把两个数字分到两个子数组，很巧妙的方法：
 * 先做一次（1），得到的结果是要找的两个数字的异或，那么取出第一个为1的位，这个位必定是两个数字不同的位，根据这个位是0或1就能把原数组、
 * 分成两个分别包含两个数字的字数组。这题真难
 */
class Solution
{
  public:
    //（1）一个数只出现一次，而其他都出现2次
    int FindOnceOther2(const vector<int> &data)
    {
        if (data.empty())
            throw std::invalid_argument("array is empty");
        int res = 0;
        for (auto val : data)
            res ^= val;
        return res;
    }
    //（2）一个数只出现非3的倍数，而其他都出现3次，方法一
    int FindOnceOther3_Way1(const vector<int> &data)
    {
        if (data.empty())
            throw std::invalid_argument("array is empty");
        vector<char> count(sizeof(int), 0); //用于记录每一位1出现的次数
        //得到最终结果每一位1的个数
        for (auto val : data)
            for (size_t i = 0; i < count.size(); ++i)
                count[i] = (count[i] + (val >> i & 0x01)) % 3;
        int res = 0;
        for (size_t i = 0; i < count.size(); ++i)
            if (count[i])
                res |= 1u << i;
        return res;
    }
    //（2）一个数只出现非3的倍数，而其他都出现3次，方法二
    //  1010  twice：0000  once：1010
    //  1110  twice：1010  once：0100
    //  0110  twice：1110  once：0010
    int FindOnceOther3_Way2(const vector<int> &data)
    {
        if (data.empty())
            throw std::invalid_argument("array is empty");
        int twice = 0;    //已经出现过两次的位置为一
        int once = 0;     //出现了一次的位置为一，进位到twice时要清零
        int is_not_three; //出现3次要清零，用于保存不用清零的位置
        for (auto val : data)
        {
            twice |= once & val;            //某个位上次出现了1次1(once)，这次又出现1(val)，则出现了2次1
            once ^= val;                    //已经计入twice的，即1进位了的清零，原本是0，val中出现了1则置1
            is_not_three = ~(twice & once); //twice和once都置1的位说明出现了3次1，则类似于取模，这些位清零，取出不用清零的位
            twice &= is_not_three;
            once &= is_not_three;
        }
        return once; //出现一次返回once，出现两次返回twice
    }
    //（3）数组中只出现一次的两个数字,
    void FindNumsAppearOnce(vector<int> data, int &num1, int &num2)
    {
        if (data.empty())
            return;
        int res = 0;
        for (auto val : data)
            res ^= val;
        unsigned int nIndex = 0; //要找的两个数异或后第一个为1的位
        while (!(res & 0x01) && ((++nIndex) < 8 * sizeof(int)))
            res >>= 1;
        num1 = num2 = 0;
        for (auto val : data)
            if ((val >> nIndex) & 0x01)
                num1 ^= val;
            else
                num2 ^= val;
    }
};

int main()
{
    Solution s;
    cout << s.FindOnceOther2({23, 21, 12, 23, 12}) << endl; //21

    cout << s.FindOnceOther3_Way1({1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3}) << endl;       //1出现两次
    cout << s.FindOnceOther3_Way1({3, 2, 1, 3, 2, 1, 3, 2, 1, 4, 4, 4, 4}) << endl; //4出现四次

    cout << s.FindOnceOther3_Way2({1, 2, 2, 2, 3, 3, 3, 3, 3, 3}) << endl; //1出现两次

    int num1, num2;
    s.FindNumsAppearOnce({2, 3, 1, 2, 3, 4}, num1, num2);
    cout << num1 << " " << num2 << endl;
}