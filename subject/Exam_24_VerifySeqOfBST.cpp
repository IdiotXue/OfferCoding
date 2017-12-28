#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>
using std::cout;
using std::endl;
using std::queue;
using std::vector;

/**
 * 二叉搜索树的后序遍历序列
 * 思路：
 * 根在树后序遍历的最后一个位置，根据二叉搜索树的性质，应该要
 * 能把序列分成<root的前半部分和>root的后半部分（可以只有一部分）
 * 而且分出来后要递归判断两部分是否也满足这个性质
 * 终止条件：left+2>=right，只剩一个根和至多两个结点,肯定满足性质
 * 特例：（1）输入结点为空（2）输入一个结点
 */

class Solution
{
  public:
    bool VerifySquenceOfBST(vector<int> sequence)
    {
        if (sequence.empty())
            return false;
        return VerSeqRecursion(sequence, 0, sequence.size() - 1);
    }
    bool VerSeqRecursion(const vector<int> &seq, int left, int right)
    {
        //right必须是有符号int，否则当无左子树（测试用例3），终止条件判断不满足
        if (left + 2 >= right)
            return true;
        int nRoot = seq[right]; //后序遍历根是序列最后一个元素
        int index = left;
        while (seq[index] < nRoot) //前半部分小于root
            ++index;
        int nHalf = index - 1;     //小于root的前半部分的边界
        while (seq[index] > nRoot) //后半部分小于root
            ++index;
        if (index == right) // 成功分成两部分时，index应该到达根结点
            //逻辑与的性质：前半为false时，后半不执行
            return (VerSeqRecursion(seq, left, nHalf) &&
                    VerSeqRecursion(seq, nHalf + 1, right - 1));
        return false;
    }
};

void Test(const vector<int> &seq)
{
    Solution s;
    static int test = 0;
    cout << "Test-" << ++test << ":";
    cout << std::boolalpha << s.VerifySquenceOfBST(seq) << std::noboolalpha << endl;
}

int main()
{
    /*         10
            /      \
           6        14
          /\        /\
         4  8     12  16 */
    vector<int> seq1{4, 8, 6, 12, 16, 14, 10};
    Test(seq1);

    //            8
    //          7
    //        6
    //      5
    //    4
    vector<int> seq2{4, 5, 6, 7, 8};
    Test(seq2);
    /*1                   
       \                    
        2                      
         \                   
          3                   
           \      
            4        
             
              5 */
    vector<int> seq3{5, 4, 3, 2, 1};
    Test(seq3);

    vector<int> seq4{1};
    Test(seq4);

    /*    5
         / \
        4   7
           /
          6 */
    vector<int> seq5{4, 6, 7, 5};
    Test(seq5);

    vector<int> seq6{7, 4, 6, 5}; //false
    Test(seq6);

    vector<int> seq7{4, 6, 12, 8, 16, 14, 10};
    Test(seq7);
}