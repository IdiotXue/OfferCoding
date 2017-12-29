#include <iostream>
#include <unordered_map> //hash作为key，比map更快
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

/**
 * 二叉搜索树与双向链表
 * 思路：
 * 二叉树搜索树中序遍历就是从小到大的，所以按这个顺序遍历.
 * 在中序遍历的递归中传递最新连接到哪一个结点pConn，pConn的右指向当前结点pCurr，
 * pCurr的左指向pConn，然后pConn=pCurr
 * 终止条件：遇到空结点
 * 特例：输出空结点
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
    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        if (pRootOfTree == nullptr)
            return nullptr;
        TreeNode *pConn = nullptr;
        ConvertBST(pRootOfTree, pConn);
        //此时pConn指向链表的最右，牛客网的测试用例要求返回的头指针在链表最左
        pConn = pRootOfTree; //少走几步
        while (pConn->left)
            pConn = pConn->left;
        return pConn;
    }

  private:
    void ConvertBST(TreeNode *pCurr, TreeNode *&pConn)
    {
        if (!pCurr)
            return;
        ConvertBST(pCurr->left, pConn);
        pCurr->left = pConn;
        if (pConn)
            pConn->right = pCurr;
        pConn = pCurr;
        ConvertBST(pCurr->right, pConn);
    }
};

int main()
{

    return 0;
}