#include <iostream>
#include <vector>
#include <stdexcept>
using std::cout;
using std::endl;
using std::vector;

/**
 * 二叉树的镜像
 * 思路:
 * 递归到每个结点的是时候都交换其左右子结点即可
 * 终止条件：到达nullptr
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
    void Mirror(TreeNode *pRoot)
    {
        if (!pRoot)
            return;
        Mirror(pRoot->left);
        Mirror(pRoot->right);
        TreeNode *pNode = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = pNode;
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

void PreorderTraverse(TreeNode *pRoot)
{
    if (pRoot == NULL)
        return;
    cout << pRoot->val << ' ';
    PreorderTraverse(pRoot->left);
    PreorderTraverse(pRoot->right);
}
void InorderTraverse(TreeNode *pRoot) //中序遍历
{
    if (pRoot == NULL)
        return;
    InorderTraverse(pRoot->left);
    cout << pRoot->val << " ";
    InorderTraverse(pRoot->right);
}
void PostorderTraverse(TreeNode *pRoot)
{
    if (pRoot == NULL)
        return;
    PostorderTraverse(pRoot->left);
    PostorderTraverse(pRoot->right);
    cout << pRoot->val << " ";
}
void Test(int *preorder, int *inorder, int length)
{
    Solution s;
    try
    {
        vector<int> vnPreorder(preorder, preorder + length);
        vector<int> vnInorder(inorder, inorder + length);
        TreeNode *pRoot = Construct(vnPreorder, vnInorder);
        PostorderTraverse(pRoot);
        cout << " 树A后序遍历" << endl;
        InorderTraverse(pRoot);
        cout << " 树A中序遍历" << endl;

        s.Mirror(pRoot);
        PostorderTraverse(pRoot);
        cout << " 镜像后树A后序遍历" << endl;
        InorderTraverse(pRoot);
        cout << " 镜像后树A中序遍历" << endl;
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
    TreeNode *pRoot = new TreeNode(1);
    PostorderTraverse(pRoot);
    cout << " 树A后序遍历" << endl;
    Solution s;
    s.Mirror(pRoot);
    PostorderTraverse(pRoot);
    cout << " 树A后序遍历" << endl;
}
void Test5()
{
    Solution s;
    s.Mirror(NULL);
}
int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
}
