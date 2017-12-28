#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>
using std::cout;
using std::endl;
using std::queue;
using std::vector;

/**
 * 从上往下打印二叉树
 * 思路：
 * 一层层遍历相当于广度优先搜索，用队列
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
    vector<int> PrintFromTopToBottom(TreeNode *root)
    {
        if (root == nullptr)
            return vector<int>();
        queue<TreeNode *> pQueue;
        pQueue.push(root);
        vector<int> output;
        TreeNode *pNode = nullptr;
        while (!pQueue.empty())
        {
            pNode = pQueue.front();
            output.push_back(pNode->val);
            if (pNode->left)
                pQueue.push(pNode->left);
            if (pNode->right)
                pQueue.push(pNode->right);
            pQueue.pop();
        }
        return output;
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

void Test(int *preorder, int *inorder, int length)
{
    Solution s;
    try
    {
        vector<int> vnPreorder(preorder, preorder + length);
        vector<int> vnInorder(inorder, inorder + length);
        TreeNode *pRoot = Construct(vnPreorder, vnInorder);

        vector<int> output = s.PrintFromTopToBottom(pRoot);
        for (auto val : output)
            cout << val << " ";
        cout << endl;
    }
    catch (std::exception &exception)
    {
        cout << exception.what() << endl;
    }
}
void Test1()
{
    // 测试完全二叉树：除了叶子节点，其他节点都有两个子节点
    //            8
    //        6      10
    //       5 7    9  11
    const int Length = 7;
    int preorder[Length] = {8, 6, 5, 7, 10, 9, 11};
    int inorder[Length] = {5, 6, 7, 8, 9, 10, 11};
    Test(preorder, inorder, Length);
}

void Test2()
{
    // 测试二叉树：出叶子结点之外，左右的结点都有且只有一个左子结点
    //            8
    //          7
    //        6
    //      5
    //    4
    const int Length = 5;
    int preorder[Length] = {8, 7, 6, 5, 4};
    int inorder[Length] = {4, 5, 6, 7, 8};
    Test(preorder, inorder, Length);
}
void Test3()
{
    // 树中结点只有右子结点，树B是树A的子结构
    /*   8                   
       \                    
        7                      
         \                   
          6                   
           \      
            5        
             \
              4 */
    const int Length = 5;
    int preorder[Length] = {8, 7, 6, 5, 4};
    int inorder[Length] = {8, 7, 6, 5, 4};
    Test(preorder, inorder, Length);
}
void Test4()
{
    const int Length = 1;
    int preorder[Length] = {1};
    int inorder[Length] = {1};
    Test(preorder, inorder, Length);
}
void Test5()
{
    Solution s;
    s.PrintFromTopToBottom(NULL);
}
int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    return 0;
}