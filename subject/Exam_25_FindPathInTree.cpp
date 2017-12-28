#include <iostream>
#include <vector>
#include <stdexcept>
using std::cout;
using std::endl;
using std::vector;

/**
 * 二叉树中和为某一值的路径
 * 思路：
 * 树的问题一看又是要递归，这次的递归需要传递路径到某一结点时的和
 * 到达叶结点是判断这个和是否等于给定值，因为要打印路径，所以还要
 * 保存路径上的结点；
 * 考虑效率问题：和只是一个值，可以传值；但路径结构得传引用，因为是一个结构，
 * 因此递归的结尾需pop掉结点
 * 终止条件：当然是遇到叶结点
 * 特例：输入结点为空
 */

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution
{
  public:
    vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
    {
        if (!root)
            return vector<vector<int>>();
        vector<vector<int>> output;
        vector<int> vnTempPath;
        int nSum = 0;
        FindPathRecur(root, output, vnTempPath, expectNumber, nSum);
        return output;
    }

  private:
    void FindPathRecur(TreeNode *pNode, vector<vector<int>> &output,
                       vector<int> &vnTempPath, int expectNumber, int nSum)
    {
        nSum += pNode->val; //传值，各递归之间不影响
        vnTempPath.push_back(pNode->val);
        if (!pNode->left && !pNode->right) //叶子结点
            if (nSum == expectNumber)
                output.push_back(vnTempPath);
        if (pNode->left)
            FindPathRecur(pNode->left, output, vnTempPath, expectNumber, nSum);
        if (pNode->right)
            FindPathRecur(pNode->right, output, vnTempPath, expectNumber, nSum);
        vnTempPath.pop_back(); //执行完这个递归，本结点要从路径中删除
    }
};

TreeNode *ConstructCore(vector<int> &preorder, vector<int> &inorder,
                        int nStartPre, int nEndPre,
                        int nStartIn, int nEndIn)
{
    TreeNode *pRoot = new TreeNode(preorder[nStartPre]);
    if (nStartPre == nEndPre)
    {
        if (nStartIn == nEndIn && preorder[nStartPre] == inorder[nStartIn])
            return pRoot;
        else
            throw std::runtime_error("can not build tree");
    }
    int nRootIn = nStartIn;
    while (nRootIn <= nEndIn && inorder[nRootIn] != pRoot->val)
        ++nRootIn;
    if (nRootIn > nEndIn)
        throw std::runtime_error("can not build tree");
    int nLeftSubTreeLength = nRootIn - nStartIn;
    int nLeftSubTreeEnd = nStartPre + nLeftSubTreeLength;
    if (nLeftSubTreeLength > 0)
        pRoot->left = ConstructCore(preorder, inorder,
                                    nStartPre + 1, nLeftSubTreeEnd, nStartIn, nRootIn - 1);
    if (nLeftSubTreeLength < nEndIn - nStartIn)
        pRoot->right = ConstructCore(preorder, inorder,
                                     nLeftSubTreeEnd + 1, nEndPre, nRootIn + 1, nEndIn);
    return pRoot;
}

TreeNode *Construct(vector<int> &preorder, vector<int> &inorder)
{
    if (preorder.empty() || inorder.empty())
        return NULL;
    return ConstructCore(preorder, inorder, 0,
                         preorder.size() - 1, 0, inorder.size() - 1);
}

void Test(int *preorder, int *inorder, int length, int nExpectValue)
{
    Solution s;
    vector<int> vnPreorder(preorder, preorder + length);
    vector<int> vnInorder(inorder, inorder + length);
    TreeNode *pRoot = Construct(vnPreorder, vnInorder);

    static int test = 0;
    cout << "Test-" << ++test << ":";
    vector<vector<int>> output = s.FindPath(pRoot, nExpectValue);
    for (auto &vnArray : output)
    {
        for (auto x : vnArray)
            cout << x << " ";
        cout << endl;
    }
    cout << endl;
}
void Test1()
{
    /*         10
        /      \
       5        12
      /\        
     4  7        */
    const int length = 5;
    int preorder[length] = {10, 5, 4, 7, 12};
    int inorder[length] = {4, 5, 7, 10, 12};
    Test(preorder, inorder, length, 22);
}
void Test2()
{
    /*     10
        /      \
       5        12
      /\        
     4  7        */
    const int length = 5;
    int preorder[length] = {10, 5, 4, 7, 12};
    int inorder[length] = {4, 5, 7, 10, 12};
    Test(preorder, inorder, length, 15);
}
void Test3()
{
    //            8
    //          7
    //        6
    //      5
    //    4
    const int Length = 5;
    int preorder[Length] = {8, 7, 6, 5, 4};
    int inorder[Length] = {4, 5, 6, 7, 8};
    Test(preorder, inorder, Length, 30);
}
void Test4()
{
    /*    1                   
       \                    
        2                      
         \                   
          3                   
           \      
            4        
             \
              5 */
    const int Length = 5;
    int preorder[Length] = {1, 2, 3, 4, 5};
    int inorder[Length] = {1, 2, 3, 4, 5};
    Test(preorder, inorder, Length, 15);
}
void Test5()
{
    /*    1                   
       \                    
        2                      
         \                   
          3                   
           \      
            4        
             \
              5 */
    const int Length = 5;
    int preorder[Length] = {1, 2, 3, 4, 5};
    int inorder[Length] = {1, 2, 3, 4, 5};
    Test(preorder, inorder, Length, 12);
}
void Test6()
{
    const int Length = 1;
    int preorder[Length] = {1};
    int inorder[Length] = {1};
    Test(preorder, inorder, Length, 1);
}
void Test7()
{
    const int Length = 0;
    Test(NULL, NULL, Length, 1);
}

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    return 0;
}