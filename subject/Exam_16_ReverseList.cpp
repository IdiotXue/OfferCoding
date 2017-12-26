#include <iostream>

/**
 * 反转链表
 * 思路:
 * 只是处理逻辑关系，唯一要确定的是需要多少个指针完成反转操作：
 * 反转操作：当前结点断掉与下一结点的连接，指向上一个结点，然后整体后移重复该过程
 * 因此，需要pAhead，pCurr，pBehind三个指针
 * 特例：空链表或只有一个结点的链表
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
    ListNode *ReverseList(ListNode *pHead)
    {
        if (pHead == nullptr)
            return nullptr;
        ListNode *pAhead = nullptr, *pCurr = pHead, *pBehind = pHead->next;
        while (pBehind)
        {
            pCurr->next = pAhead; //反转
            //整体后移
            pAhead = pCurr;
            pCurr = pBehind;
            pBehind = pBehind->next;
        }
        pCurr->next = pAhead; //还差一次反转操作，完成它
        return pCurr;
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
    std::cout << s.ReverseList(pHead) << std::endl; //head为空,输出nullptr就是输出0
    AddToTail(pHead, 0);
    PrintList(pHead);
    pHead = s.ReverseList(pHead); //只有一个结点
    PrintList(pHead);
    AddToTail(pHead, 2);
    AddToTail(pHead, 4);
    AddToTail(pHead, 6);
    PrintList(pHead);
    pHead = s.ReverseList(pHead); //正常反转
    PrintList(pHead);
}