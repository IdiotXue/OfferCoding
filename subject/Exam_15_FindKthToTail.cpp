#include <iostream>

/**
 * 链表中倒数第K个结点
 * 思路:
 * 快慢指针法，一个指针（快指针）先走k-1步，则快指针到尾结点时，慢指针刚好到倒数第k个结点
 * 特例：空链表，k为0，链表不足k个结点
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
    ListNode *FindKthToTail(ListNode *pListHead, unsigned int k)
    {
        if (!pListHead || k == 0)
            return nullptr;
        ListNode *pFastNode = pListHead, *pSlowNode = pListHead;
        //数先走的步数k-1步，且快指针最多到尾结点
        while ((--k) && (pFastNode->next))
            pFastNode = pFastNode->next;
        if (k) //若k此时大于0，说明链表不足k个结点
            return nullptr;
        while (pFastNode->next)
        {
            pFastNode = pFastNode->next;
            pSlowNode = pSlowNode->next;
        }
        return pSlowNode;
    }
};

ListNode *AddToTail(ListNode *&pHead, int value)
{
    ListNode *pNew = new ListNode(value);
    if (pHead == NULL)
        pHead = pNew;
    else
    {
        ListNode *pTempNode = pHead;
        while (pTempNode->next != NULL)
            pTempNode = pTempNode->next;
        pTempNode->next = pNew;
    }
    return pNew;
}
void PrintList(ListNode *&pHead)
{
    ListNode *pNode = pHead;
    while (pNode != NULL)
    {
        std::cout << pNode->val << ' ';
        pNode = pNode->next;
    }
    std::cout << std::endl;
}
int main(int argc, char *argv[])
{
    Solution s;
    ListNode *pHead = NULL;
    std::cout << s.FindKthToTail(pHead, 1) << std::endl; //head为空,输出nullptr就是输出0
    AddToTail(pHead, 0);
    std::cout << s.FindKthToTail(pHead, 0) << std::endl; //k为0
    AddToTail(pHead, 2);
    std::cout << s.FindKthToTail(pHead, 3) << std::endl; //不足k个结点
    AddToTail(pHead, 4);
    AddToTail(pHead, 6);
    PrintList(pHead);
    std::cout << s.FindKthToTail(pHead, 2)->val << std::endl; //输出4
}