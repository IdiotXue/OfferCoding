#include <iostream>
#include <algorithm>
#include <stack>
using std::cout;
using std::endl;

/**
 * 两个链表的第一个公共结点
 * 思路
 * 两个单向链表，有公共结点，那么必定呈现Y字形，即从公共结点往后的结点是一样的
 * 那从尾部开始对比就好了，单向链表无法回溯，那就用栈
 * 好吧书上有更牛逼的做法，不需要辅助空间，计算出两个链表的长度m、n后，让长的
 * 链表先走m-n步，这样就能同时到达公共结点
 */
struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
  public:
    ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
    {
        ListNode *pNode = pHead1;
        size_t nLen1 = 0;
        while (pNode && (++nLen1))
            pNode = pNode->next;
        pNode = pHead2;
        size_t nLen2 = 0;
        while (pNode && (++nLen2))
            pNode = pNode->next;
        pNode = nullptr;
        int nDiff = nLen1 < nLen2 ? nLen2 - nLen1 : nLen1 - nLen2;
        ListNode *pNodeLong = pHead1;
        ListNode *pNodeShort = pHead2;
        if (nLen1 < nLen2)
            std::swap(pNodeLong, pNodeShort);
        for (int i = 0; i < nDiff; ++i) //先走nDiff步
            pNodeLong = pNodeLong->next;
        while (pNodeLong && pNodeShort && pNodeLong != pNodeShort)
        {
            pNodeLong = pNodeLong->next;
            pNodeShort = pNodeShort->next;
        }
        return pNodeLong; //返回空或者公共结点
    }
};

int main()
{
    // Solution s; //已通过牛客网测试用例
}