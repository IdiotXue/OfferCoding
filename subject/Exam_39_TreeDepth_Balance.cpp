#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 二叉树的深度&判断平衡二叉树
 * 思路
 * （1）深度：像之前计算路径和一样，递归到null就返回0，否则就+1再返回
 * （2）平衡二叉树：即任意结点的左右子树深度相差不超过1
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
    int TreeDepth(TreeNode *pRoot)
    {
        if (!pRoot)
            return 0;
        int nLeft = TreeDepth(pRoot->left);
        int nRight = TreeDepth(pRoot->right);
        return nLeft > nRight ? nLeft + 1 : nRight + 1;
    }
    bool IsBalanced_Solution(TreeNode *pRoot)
    {
        if (!pRoot)
            return true;
        int nLeft = TreeDepth(pRoot->left);
        int nRight = TreeDepth(pRoot->right);
        int nDiff = nLeft > nRight ? nLeft - nRight : nRight - nLeft;
        if (nDiff > 1)
            return false;
        return IsBalanced_Solution(pRoot->left) && IsBalanced_Solution(pRoot->right);
    }
};

int main()
{
    // Solution s; //已通过牛客网测试用例
}