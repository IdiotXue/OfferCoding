#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdio>
using std::string;
using std::vector;

/**
 * 思路：
 * 前序遍历是{根，左子树，右子树}；中序是{左子树，根，右子树}
 * 因此，按如下操作即可
 * （1）在前序中拿出根（第一个元素），用于在中序中分出左右子树
 * （2）根据中序得出的左右子树元素个数，在前序中分出左右子树
 * （3）在（1）（2）中得到左右子树的前序和中序遍历，是原问题的子集
 *     即：左右子树的根就是（1）中根的左右子结点
 * （4）递归构建左右子树，直到叶子结点为止
 * 特例：（1）前中序大小不同或大小为0（2）无法构成二叉树（3）部分无左子树或右子树
 */
//Definition for binary tree
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution
{
  public:
    TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin)
    {
        if (pre.size() != vin.size() || pre.empty())
            return nullptr;
        return RCBTRecursion(pre, vin, 0, pre.size() - 1, 0, vin.size() - 1);
    }

  private:
    TreeNode *RCBTRecursion(vector<int> &pre, vector<int> &vin,
                            size_t nPreLeft, size_t nPreRight,
                            size_t nVinLeft, size_t nVinRight)
    {
        //1. 前序的第一个元素是根
        TreeNode *node = new TreeNode(pre[nPreLeft]);
        //4. 终止条件：前序只剩一个元素，可能是叶子节点，也可能无法构成二叉树
        if (nPreLeft == nPreRight)
        {
            //到达叶子结点
            if (nVinLeft == nVinRight && pre[nPreLeft] == vin[nVinLeft])
                return node;
            else //无法构成二叉树
                throw std::runtime_error("cannot construct binary tree");
        }
        //2. 在中序里找到根并分出左右子树
        size_t nVinRootIndex = nVinLeft;
        //找出中序里根的位置
        while (nVinRootIndex <= nVinRight && vin[nVinRootIndex] != pre[nPreLeft])
            ++nVinRootIndex;
        if (nVinRootIndex > nVinRight) //中序里没找到根
            throw std::runtime_error("cannot find root in vin");
        size_t nleftTreeLen = nVinRootIndex - nVinLeft; //左子树长度
        //3. 在前序中分出左右子树，并递归构建左右子树
        if (nleftTreeLen > 0) //有左子树才能构建，否则下标错乱
            node->left = RCBTRecursion(pre, vin, nPreLeft + 1, nPreLeft + nleftTreeLen,
                                       nVinLeft, nVinRootIndex - 1);
        if (nVinRootIndex < nVinRight) //有右子树才能构建，否则下标错乱
            node->right = RCBTRecursion(pre, vin, nPreLeft + nleftTreeLen + 1, nPreRight,
                                        nVinRootIndex + 1, nVinRight);
        return node;
    }
};
void PreorderTraverse(TreeNode *pRoot) //前遍历
{
    if (pRoot == nullptr)
        return;
    std::cout << pRoot->val << " ";
    PreorderTraverse(pRoot->left);
    PreorderTraverse(pRoot->right);
}
void InorderTraverse(TreeNode *pRoot) //中序遍历
{
    if (pRoot == nullptr)
        return;
    InorderTraverse(pRoot->left);
    std::cout << pRoot->val << " ";
    InorderTraverse(pRoot->right);
}
void PostorderTraverse(TreeNode *pRoot) //后序遍历
{
    if (pRoot == nullptr)
        return;
    PostorderTraverse(pRoot->left);
    PostorderTraverse(pRoot->right);
    std::cout << pRoot->val << " ";
}
void Test(const string &testName, vector<int> &preorder, vector<int> &inorder) //测试函数主体
{
    std::cout << testName << std::endl;

    printf("The preorder sequence is: ");
    for (size_t i = 0; i < preorder.size(); ++i)
        printf("%d ", preorder[i]);
    printf("\n");

    printf("The inorder sequence is: ");
    for (size_t i = 0; i < inorder.size(); ++i)
        printf("%d ", inorder[i]);
    printf("\n");
    Solution s;
    try
    {
        TreeNode *root = s.reConstructBinaryTree(preorder, inorder);
        PreorderTraverse(root);
        std::cout << " 前序遍历" << std::endl;
        InorderTraverse(root);
        std::cout << " 中序遍历" << std::endl;
        PostorderTraverse(root);
        std::cout << " 后序遍历" << std::endl;
    }
    catch (std::exception &exception)
    {
        std::cout << exception.what() << std::endl;
    }
}
// 普通二叉树
/*           1
          /     \ 
         2       3
        /       / \ 
       4       5   6
        \         /
         7       8 */
void Test1()
{
    vector<int> preorder{1, 2, 4, 7, 3, 5, 6, 8};
    vector<int> inorder{4, 7, 2, 1, 5, 3, 8, 6};

    Test("Test1", preorder, inorder);
}
// 所有结点都没有右子结点
//            1
//           /
//          2
//         /
//        3
//       /
//      4
//     /
//    5
void Test2()
{
    vector<int> preorder{1, 2, 3, 4, 5};
    vector<int> inorder{5, 4, 3, 2, 1};

    Test("Test2", preorder, inorder);
}

// 所有结点都没有左子结点
/*         1
            \ 
             2
              \ 
               3
                \ 
                 4
                  \ 
                   5 */
void Test3()
{
    vector<int> preorder{1, 2, 3, 4, 5};
    vector<int> inorder{1, 2, 3, 4, 5};

    Test("Test3", preorder, inorder);
}

// 树中只有一个结点
void Test4()
{
    vector<int> preorder{1};
    vector<int> inorder{1};

    Test("Test4", preorder, inorder);
}

// 完全二叉树
/*           1
          /     \ 
         2       3
        / \     / \ 
       4   5   6   7 */
void Test5()
{
    vector<int> preorder{1, 2, 4, 5, 3, 6, 7};
    vector<int> inorder{4, 2, 5, 1, 6, 3, 7};

    Test("Test5", preorder, inorder);
}

// 输入空指针
void Test6()
{
    vector<int> a;
    vector<int> b;
    Test("Test6", a, b);
}

// 输入的两个序列不匹配
void Test7()
{
    vector<int> preorder{1, 2, 4, 5, 3, 6, 7};
    vector<int> inorder{4, 2, 8, 1, 6, 3, 7};

    Test("Test7: for unmatched input", preorder, inorder);
}

int main(int argc, char *argv[])
{
    // 测试用例：
    // 普通二叉树（完全、不完全二叉树）
    // 特殊二叉树（所有结点都没有右子结点的二叉树，所有结点都没有左子结点的二叉树，只有一个结点的二叉树）
    // 特殊输入测试（二叉树根结点指针为NULL，输入的前序遍历序列和中序遍历序列不匹配）
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}