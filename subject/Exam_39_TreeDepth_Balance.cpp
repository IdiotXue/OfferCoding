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
        int depth = 0;
        return IsBalancedRecursion(pRoot, depth);
    }

  private:
    /**
     * 思路
     * 递归到叶结点，从下往上开始比较,需要有个depth一直保留深度
     */
    bool IsBalancedRecursion(TreeNode *pRoot, int &depth)
    {
        if (!pRoot)
        {
            depth = 0;
            return true;
        }
        int nLeft, nRight; //声明为局部变量，即让父节点获取子节点的深度即可
        if (IsBalancedRecursion(pRoot->left, nLeft) &&
            IsBalancedRecursion(pRoot->right, nRight))
        {
            int nDiff = nLeft > nRight ? nLeft - nRight : nRight - nLeft;
            if (nDiff <= 1)
            {
                depth = nLeft > nRight ? nLeft + 1 : nRight + 1;
                return true;
            }
        }
        return false;
    }
};

int main()
{
    // Solution s; //已通过牛客网测试用例
}