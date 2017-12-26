#include <iostream>

/**
 * 合并两个排序的链表
 * 思路:
 * 已排序链表的合并，在两个链表上分别用一个指针同时移动比较即可，
 * 另外有第三个指针维持合并后链表的结构，且合并后的链表的头指针要保留用于返回
 * 特例：（1）某一链表为空（2）两个都为空
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
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
    {
        if (pHead1 == nullptr)
        {
            if (pHead2 == nullptr) //两个都为空
                return nullptr;
            else
                return pHead2; //只有pHead1是空，返回pHead2
        }
        else if (pHead2 == nullptr)
            return pHead1; //只有pHead2是空，返回pHead1
        //两个都不为空执行常规合并
        //1.先确定用于返回的头指针
        ListNode *pHead=nullptr;
        if (pHead1->val <= pHead2->val)
        {
            pHead = pHead1;
            pHead1 = pHead1->next;
        }
        else
        {
            pHead = pHead2;
            pHead1 = pHead2->next;
        }
        //2.执行合并
        ListNode *pNode = pHead;
        while (pHead1 && pHead2)
        {
            if (pHead1->val <= pHead2->val)
            {
                pNode->next = pHead1;
                pHead1 = pHead1->next;
            }
            else
            {
                pNode->next = pHead2;
                pHead2 = pHead2->next;
            }
            pNode = pNode->next;
        }
        //3.判断哪个链表还有结点,全都补到后面
        while (pHead1)
        {
            pNode->next = pHead1;
            pHead1 = pHead1->next;
            pNode = pNode->next;
        }
        while (pHead2)
        {
            pNode->next = pHead2;
            pHead2 = pHead2->next;
            pNode = pNode->next;
        }
        return pHead;
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
    ListNode *pHead1 = NULL;
    AddToTail(pHead1, 0);
    AddToTail(pHead1, 3);
    AddToTail(pHead1, 6);
    AddToTail(pHead1, 9);
    PrintList(pHead1);
    ListNode *pHead2 = NULL;
    AddToTail(pHead2, 1);
    AddToTail(pHead2, 2);
    AddToTail(pHead2, 7);
    AddToTail(pHead2, 8);
    PrintList(pHead2);

    ListNode *pHead = s.Merge(pHead1, pHead2);
    PrintList(pHead);
}