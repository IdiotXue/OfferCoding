#include <iostream>
#include <stdexcept>
#include <string>
using std::string;

/**
 * O(1)删除链表节点
 * 思路:
 * 不能通过遍历搜索待删除结点的前一个结点，因此，
 * 只能做一次拷贝，将待删除结点下一结点的值拷贝到该结点，并更新该结点的m_pNext,
 * 然后删除该结点的下一个结点
 * 特例:（1）删除尾结点，不得不遍历（2）只有一个结点，删除后pHead=nullptr
 *     （3）输入的结点为空
 */
struct ListNode
{
    int m_nValue;
    ListNode *m_pNext;
};

class Solution
{
  public:
    void DeleteNode(ListNode **pListHead, ListNode *pToBeDelete)
    {
        if (!pListHead || !pToBeDelete)
            return;
        if (!pToBeDelete->m_pNext) //待删除结点为尾结点
        {
            if (*pListHead == pToBeDelete) //链表中只有一个结点
            {
                delete pToBeDelete;
                pToBeDelete = nullptr;
                *pListHead = nullptr;
            }
            else //链表不只一个结点，需遍历
            {
                ListNode *pNode = *pListHead;
                while (pNode->m_pNext != pToBeDelete)
                    pNode = pNode->m_pNext;
                pNode->m_pNext = nullptr;
                delete pToBeDelete;
                pToBeDelete = nullptr;
            }
        }
        else //待删除结点不是尾结点
        {
            ListNode *pNode = pToBeDelete->m_pNext;
            pToBeDelete->m_nValue = pNode->m_nValue;
            pToBeDelete->m_pNext = pNode->m_pNext;
            delete pNode;
            pNode = nullptr;
        }
    }
};
ListNode *AddToTail(ListNode *&pHead, int value)
{
    ListNode *pNew = new ListNode();
    pNew->m_nValue = value;
    pNew->m_pNext = NULL;
    if (pHead == NULL)
        pHead = pNew;
    else
    {
        ListNode *pTempNode = pHead;
        while (pTempNode->m_pNext != NULL)
            pTempNode = pTempNode->m_pNext;
        pTempNode->m_pNext = pNew;
    }
    return pNew;
}
void PrintList(ListNode *&pHead)
{
    ListNode *pNode = pHead;
    while (pNode != NULL)
    {
        std::cout << pNode->m_nValue << ' ';
        pNode = pNode->m_pNext;
    }
    std::cout << std::endl;
}
void Test(ListNode *&pHead, ListNode *pToBeDeleted)
{
    Solution s;
    s.DeleteNode(&pHead, pToBeDeleted);
}
int main(int argc, char *argv[])
{
    ListNode *pHead = NULL;
    ListNode *pDelete1 = NULL;
    //Test1 pHead==NULL
    Test(pHead, pDelete1);
    ListNode *pDelete2 = AddToTail(pHead, 2);
    //Test2 pDelete==NULL
    Test(pHead, pDelete1);
    //Test3 删除尾结点
    PrintList(pHead);
    Test(pHead, pDelete2);
    PrintList(pHead);

    ListNode *pDeleteHead = AddToTail(pHead, 0);
    AddToTail(pHead, 2);
    AddToTail(pHead, 4);
    ListNode *pDeleteMiddle = AddToTail(pHead, 6);
    AddToTail(pHead, 8);
    AddToTail(pHead, 10);
    ListNode *pDeleteEnd = AddToTail(pHead, 12);

    //Test4
    PrintList(pHead);
    Test(pHead, pDeleteEnd);
    PrintList(pHead);
    //Test5
    PrintList(pHead);
    Test(pHead, pDeleteHead);
    PrintList(pHead);
    //Test6
    PrintList(pHead);
    Test(pHead, pDeleteMiddle);
    PrintList(pHead);
}