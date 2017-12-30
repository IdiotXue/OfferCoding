#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm> //标准库的交换操作用std::move做，更快
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;
/**
 * 字符串的排列
 * 思路：
 * 以填n个位置的方式思考，第一个位置有n个可能，轮流在n个字符到这个位置，固定了第一个位置后，
 * 要填第二个位置，让剩下的字符轮流到这个位置，显然这是个递归问题
 * 扩展：
 * （1）字符串的组合
 * （2）正方形的8个顶点
 * （3）8×8国际象棋里8个皇后
 *      
 */

class Solution
{
  public:
    /**
     * 排列
     */
    vector<string> Permutation(string str)
    {
        if (str.empty())
            return vector<string>();
        set<string> setOutput; //牛客网的测试用例输入字符有可能重复，用set屏蔽重复
        GenPermutationStr(setOutput, str, 0);
        vector<string> output(setOutput.begin(), setOutput.end());
        return output;
    }

    //排列
    void GenPermutationStr(set<string> &output, string str, size_t nPos)
    {
        if (nPos == str.size() - 1)
        {
            output.insert(str);
            return;
        }
        for (size_t i = nPos; i < str.size(); ++i)
        {
            std::swap(str[i], str[nPos]);
            GenPermutationStr(output, str, nPos + 1);
        }
    }

    /**
     * 组合
     * （1）字符串的组合：如三个字符能构成的长度为1或2或3的组合，肯定要有一个循环指定组合长度，
 *     在m个字符中分出第一个字符和后面部分，在剩余m-1个字符中再选一个，不够长度就递归往后选
 *     终止条件：字符数满足长度了
     */
    vector<string> Combination(const string &str)
    {
        if (str.empty())
            return vector<string>();
        vector<string> output;
        for (size_t nLen = 1; nLen <= str.size(); ++nLen)            //字符串长度
            for (size_t nPos = 0; nPos + nLen <= str.size(); ++nPos) //从nPos开始的字符都还没被选过
                GenCombinationStr(output, str, "", nPos, nLen);
        return output;
    }
    //组合
    void GenCombinationStr(vector<string> &output, const string &str,
                           string out, size_t nPos, size_t nLen)
    {
        out += str[nPos]; //分离出第一个
        if (out.size() == nLen)
        {
            output.push_back(out);
            return;
        }
        //在剩余m-1个字符中选一个，一个递归选一个，已经选过的后面也不用选了，所以pos一直增加
        for (size_t i = nPos + 1; i < str.size(); ++i)
            if (str.size() - nPos + out.size() >= nLen) //剩余字符数够长度要求才有必要递归
                GenCombinationStr(output, str, out, i, nLen);
    }
    /**
     * （2）正方形的8个定点
     * 正方形的8个顶点，一个数组8个数字，判断是否可能使得正方形上三组相对的面上的4个顶点的和都相等，这是个排列问题
     * 满足3个条件：（1）a1+a2+a3+a4=a5+a6+a7+a8，（2）a1+a3+a5+a7=a2+a4+a6+a8，（3）a1+a2+a5+a6=a3+a4+a7+a8
     * 找出8个数字所有的排列方式，然后判断是否满足这3个条件即可
     */
    template <typename T>
    bool PermutationSquare(const vector<T> &vTData)
    {
        if (vTData.size() != 8)
            return false;
        return PrintPermutationSquareRecursively(vTData, 0);
    }
    template <typename T>
    bool PrintPermutationSquareRecursively(vector<T> vTData, size_t nPos)
    {
        bool IsSatisfy = false;
        // static int count = 0; //静态变量记录满足条件的数量
        if (nPos == vTData.size() - 1)
        {
            if (vTData[0] + vTData[1] + vTData[2] + vTData[3] == vTData[4] + vTData[5] + vTData[6] + vTData[7] && vTData[0] + vTData[2] + vTData[4] + vTData[6] == vTData[1] + vTData[3] + vTData[5] + vTData[7] && vTData[0] + vTData[1] + vTData[4] + vTData[5] == vTData[2] + vTData[3] + vTData[6] + vTData[7])
            { //输出排列顺序
                // for (unsigned i = 0; i < vTData.size(); i++)
                //     cout << vTData[i] << ' ';
                // cout << endl;
                // cout << ++count << endl;
                return true;
            }
            else
                return false;
        }
        else
        {
            for (size_t i = nPos; i < vTData.size(); ++i)
            {
                std::swap(vTData[i], vTData[nPos]);
                IsSatisfy |= PrintPermutationSquareRecursively(vTData, nPos + 1);
                //如果不数有多少中情况，只判断真假可以在这里返回
                if (IsSatisfy) //有一个满足就能返回true,不用继续找了,
                    return IsSatisfy;
            }
        }
        return IsSatisfy; //到这里肯定是返回false了
    }
    /**
     * （3）8×8国际象棋里8个皇后
     * 思路：
     * 不能在同行同列，则可以用行做数组下标，存8个不同列号，即数字0-7，显然这是一个排列问题
     * 先得出这8个数字的所有排列，然后判断是否符合任意两个不在同一对角线这个条件fabs(i-j) == fabs(ColumnIndex[i]-ColumnIndex[j]),显然这是一个组合问题
     * 
     * 非递归部分：初始化长度为8的数组为0-7，
     * 排列的递归，模仿上题就行了
     * 组合的判断：判断8个数是否两两符合不在同一对角线是个组合问题，只是此处简化为组合位数为2，用两个循环就能搞定
     */

    int PermutationWayOfInternationalChess()
    {
        vector<int> vnColumnIndex{0, 1, 2, 3, 4, 5, 6, 7};
        int nNumofWay = 0;
        PermutationRecursively(vnColumnIndex, 0, nNumofWay);
        return nNumofWay;
    }
    void PermutationRecursively(vector<int> vnColumnIndex, unsigned nPos, int &nNumOfWay)
    {
        if (nPos == vnColumnIndex.size() - 1)
        {
            if (JudgeNotTheSameDiagonal(vnColumnIndex))
            {
                ++nNumOfWay;
                // for (unsigned i = 0; i < vnColumnIndex.size(); i++)
                //     cout << vnColumnIndex[i] << ' ';
                // cout << endl;
            }
        }
        else
            for (unsigned i = nPos; i < vnColumnIndex.size(); ++i)
            {
                std::swap(vnColumnIndex[i], vnColumnIndex[nPos]);
                PermutationRecursively(vnColumnIndex, nPos + 1, nNumOfWay);
            }
    }
    bool JudgeNotTheSameDiagonal(const vector<int> &vnColumnIndex)
    {
        if (vnColumnIndex.empty())
            return false;
        //组合只是长度为2，因此不需要递归，2个循环就行
        for (int i = 0; i < int(vnColumnIndex.size() - 1); ++i)
            for (int j = i + 1; j < int(vnColumnIndex.size()); ++j)
                if ((i - j) == (vnColumnIndex[i] - vnColumnIndex[j]) ||
                    (j - i) == (vnColumnIndex[i] - vnColumnIndex[j]))
                    return false;
        return true;
    }
};

int main()
{
    Solution s;
    //排列
    vector<string> vsTest = s.Permutation("abc");
    for (const auto &s : vsTest)
        cout << s << " ";
    cout << endl;
    vsTest = s.Permutation("aa");
    for (const auto &s : vsTest)
        cout << s << " ";
    cout << endl;

    //组合
    vsTest = s.Combination("abc");
    for (const auto &s : vsTest)
        cout << s << " ";
    cout << endl;

    //正方形8个顶点
    vector<int> vnTest{1, 2, 3, 4, 1, 2, 3, 4};
    cout << std::boolalpha << s.PermutationSquare(vnTest) << std::noboolalpha << endl;

    //8皇后问题
    cout << s.PermutationWayOfInternationalChess() << endl;
    return 0;
}