#include <iostream>
#include <vector>
#include <stdexcept>
using std::cout;
using std::endl;
using std::vector;

/**
 * 树的子结构：判断树B是树A的子结构
 * 思路:
 * 树操作一般用递归方便，树A和树B都需要递归
 * 递归一：在树A递归判断A的每一个结点与树B的根节点是否相等，如果相等执行递归二
 * 递归二：结点相等
 *          两树同时递归判断左右子节点是否相等，返回两结果的逻辑与&&
 *          不相等返回false
 *        
 * 递归一的终止条件：A到达nullptr；
 * 递归二的终止条件：B到达nullptr返回true；B不为nullptr而A为nullptr返回false
 * 特例：树A或B有一个为空
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
    bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2)
    {
        if (!pRoot1 || !pRoot2) //终止条件与特例判断合在一起
            return false;
        bool result = false; //对A树每一次递归是一次独立的判断
        if (pRoot1->val == pRoot2->val)
            //注意逻辑与的特性：前半部分判断为假，则后半部分不会执行
            result = (JudgeSubNode(pRoot1->left, pRoot2->left) &&
                      JudgeSubNode(pRoot1->right, pRoot2->right));
        if (!result) //只要有一次判断出B是A的子结构，则不需要继续递归
            result = HasSubtree(pRoot1->left, pRoot2);
        if (!result)
            result = HasSubtree(pRoot1->right, pRoot2);
        return result;
    }

  private:
    bool JudgeSubNode(TreeNode *pTree1, TreeNode *pTree2)
    {
        if (!pTree2) //树B到nullptr
            return true;
        else if (!pTree1) //树B结点非空，但树A结点是空
            return false;
        //都非空则做比较
        if (pTree1->val == pTree2->val)
            //注意逻辑与的特性：前半部分判断为假，则后半部分不会执行
            return (JudgeSubNode(pTree1->left, pTree2->left) &&
                    JudgeSubNode(pTree1->right, pTree2->right));
        else
            return false;
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

void PostorderTraverse(TreeNode *pRoot)
{
    if (pRoot == NULL)
        return;
    PostorderTraverse(pRoot->left);
    PostorderTraverse(pRoot->right);
    cout << pRoot->val << " ";
}
void Test(int *preorder, int *inorder, int length, int *SubPreorder, int *SubInorder, int SubLength)
{
    Solution s;
    try
    {
        vector<int> vnPreorder(preorder, preorder + length);
        vector<int> vnInorder(inorder, inorder + length);
        TreeNode *pRoot = Construct(vnPreorder, vnInorder);
        PostorderTraverse(pRoot);
        cout << " 后序遍历" << endl;

        vector<int> vnSubPreorder(SubPreorder, SubPreorder + SubLength);
        vector<int> vnSubInorder(SubInorder, SubInorder + SubLength);
        TreeNode *pSubRoot = Construct(vnSubPreorder, vnSubInorder);
        PostorderTraverse(pSubRoot);
        cout << " 后序遍历" << endl;

        if (s.HasSubtree(pRoot, pSubRoot))
            cout << "是子结构" << endl;
        else
            cout << "不是子结构" << endl;
        cout << endl;
    }
    catch (std::exception &exception)
    {
        cout << exception.what() << endl;
    }
}
void Test1()
{
    /*                   6                8
                 /       \           / \
                8         8         9   2
              /   \
             9     2
                  / \
                 4   7 */
    const int Length = 7, SubLength = 3;
    int preorder[Length] = {6, 8, 9, 2, 4, 7, 8};
    int inorder[Length] = {9, 8, 4, 2, 7, 6, 8};
    int SubPreorder[SubLength] = {8, 9, 2};
    int SubInorder[SubLength] = {9, 8, 2};
    Test(preorder, inorder, Length, SubPreorder, SubInorder, SubLength);
}
void Test2()
{
    /*                   6                8
                 /       \           / \
                8         8         9   2
              /   \
             9     3
                  / \
                 4   7 */
    const int Length = 7, SubLength = 3;
    int preorder[Length] = {6, 8, 9, 3, 4, 7, 8};
    int inorder[Length] = {9, 8, 4, 3, 7, 6, 8};
    int SubPreorder[SubLength] = {8, 9, 2};
    int SubInorder[SubLength] = {9, 8, 2};
    Test(preorder, inorder, Length, SubPreorder, SubInorder, SubLength);
}
void Test3()
{
    //                6                  8
    //              /                   /
    //             8                   9
    //           /                    /
    //          9                    2
    //         /
    //        2
    //       /
    //      5
    const int Length = 5, SubLength = 3;
    int preorder[Length] = {6, 8, 9, 2, 5};
    int inorder[Length] = {5, 2, 9, 8, 6};
    int SubPreorder[SubLength] = {8, 9, 2};
    int SubInorder[SubLength] = {2, 9, 8};
    Test(preorder, inorder, Length, SubPreorder, SubInorder, SubLength);
}
void Test4()
{
    /*        8                   8
           \                   \ 
            8                   9
             \                   \
              9                   2
               \      
                2
                 \
                  5 */
    const int Length = 5, SubLength = 3;
    int preorder[Length] = {8, 8, 9, 2, 5};
    int inorder[Length] = {8, 8, 9, 2, 5};
    int SubPreorder[SubLength] = {8, 9, 2};
    int SubInorder[SubLength] = {8, 9, 2};
    Test(preorder, inorder, Length, SubPreorder, SubInorder, SubLength);
}
void Test5()
{
    /*            8                   8
               \                   \ 
                8                   9
                 \                 / \
                  9               3   2
                   \      
                    2
                     \
//                    5 */
    const int Length = 5, SubLength = 4;
    int preorder[Length] = {8, 8, 9, 2, 5};
    int inorder[Length] = {8, 8, 9, 2, 5};
    int SubPreorder[SubLength] = {8, 9, 3, 2};
    int SubInorder[SubLength] = {8, 3, 9, 2};
    Test(preorder, inorder, Length, SubPreorder, SubInorder, SubLength);
}
void Test6()
{
    Solution s;
    cout << s.HasSubtree(NULL, NULL) << endl;
}
int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
}
