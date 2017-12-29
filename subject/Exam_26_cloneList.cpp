#include <iostream>
#include <unordered_map> //hash作为key，比map更快
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

/**
 * 复杂链表的复制
 * 思路：
 * 基本思路：复制next主链上的结点，再从头复制random，但复制每个random都得从新建链表头开始寻找到该结点 O(n^2)
 * 改进1：用map<RandomListNode*,RandomListNode*>使新旧链表的每个结点一一对应，这样复制random够快 O(n),需辅助空间
 * 改进2：好吧，书上的方法更牛逼，连辅助空间都不要：把新建结点插入到原结点后面，这样复制random直接指向下一结点即可，当然
 *       这样代码写起来复杂一点，要拆分链表
 * 特例：输入结点为空
 */

struct RandomListNode
{
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
class Solution
{
  public:
    //改进1的做法：空间换时间
    RandomListNode *Clone(RandomListNode *pHead)
    {
        if (!pHead)
            return nullptr;
        //1.头结点单独复制
        RandomListNode *pCloneHead = new RandomListNode(pHead->label);
        RandomListNode *pNode = pHead, *pCloneNode = pCloneHead;
        unordered_map<RandomListNode *, RandomListNode *> mapOld2New;
        mapOld2New[pHead] = pCloneHead;
        //2.复制主链
        while (pNode->next)
        {
            pCloneNode->next = new RandomListNode(pNode->next->label);
            pNode = pNode->next;
            pCloneNode = pCloneNode->next;
            mapOld2New[pNode] = pCloneNode;
        }
        pNode = pHead;
        pCloneNode = pCloneHead;
        //3.复制random
        while (pNode)
        {
            if (pNode->random)
                pCloneNode->random = mapOld2New[pNode->random];
            pNode = pNode->next;
            pCloneNode = pCloneNode->next;
        }
        return pCloneHead;
    }
    //改进2的做法：新建结点插入原结点的后面
    RandomListNode *Clone2(RandomListNode *pHead)
    {
        if (!pHead)
            return nullptr;
        //1.复制主链上的结点，新建结点插入原结点的后面
        RandomListNode *pNode = pHead, *pTemp = nullptr;
        while (pNode)
        {
            pTemp = pNode->next;
            pNode->next = new RandomListNode(pNode->label);
            pNode->next->next = pTemp;
            pNode = pTemp;
        }
        pNode = pHead;
        //2.复制random
        while (pNode)
        {
            if (pNode->random)
                pNode->next->random = pNode->random->next;
            pNode = pNode->next->next;
        }
        //3.拆分链表
        RandomListNode *pCloneHead = pHead->next, *pCloneNode = pCloneHead;
        pNode = pHead;
        while (pCloneNode->next)
        {
            pNode->next = pCloneNode->next;
            pCloneNode->next = pNode->next->next;
            pNode = pNode->next;
            pCloneNode = pCloneNode->next;
        }
        pNode->next = nullptr;
        return pCloneHead;
    }
};
void BuildNodes(RandomListNode *pNode, RandomListNode *pNext, RandomListNode *random)
{
    if (pNode)
    {
        pNode->next = pNext;
        pNode->random = random;
    }
}

void PrintList(RandomListNode *pHead)
{
    RandomListNode *pNode = pHead;
    while (pNode)
    {
        cout << "value of this node:" << pNode->label << endl;
        if (pNode->random)
            cout << "value of its random:" << pNode->random->label << endl;
        else
            cout << "the node has no random" << endl;
        cout << endl;
        pNode = pNode->next;
    }
}

void Test(const string &testName, RandomListNode *pHead)
{
    cout << testName << endl;

    cout << "origin list:" << endl;
    PrintList(pHead);

    Solution s;
    RandomListNode *pClonedHead = s.Clone2(pHead);

    cout << "new list:" << endl;
    PrintList(pClonedHead);
}

/*       -----------------
        \|/              |
 1-------2-------3-------4-------5
 |       |      /|\             /|\
 --------+--------               |
         ------------------------- */
void Test1()
{
    RandomListNode *pNode1 = new RandomListNode(1);
    RandomListNode *pNode2 = new RandomListNode(2);
    RandomListNode *pNode3 = new RandomListNode(3);
    RandomListNode *pNode4 = new RandomListNode(4);
    RandomListNode *pNode5 = new RandomListNode(5);

    BuildNodes(pNode1, pNode2, pNode3);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, NULL);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test1", pNode1);
}

/*       -----------------
        \|/              |
 1-------2-------3-------4-------5
        |       | /|\           /|\
        |       | --             |
        |------------------------| */
void Test2()
{
    RandomListNode *pNode1 = new RandomListNode(1);
    RandomListNode *pNode2 = new RandomListNode(2);
    RandomListNode *pNode3 = new RandomListNode(3);
    RandomListNode *pNode4 = new RandomListNode(4);
    RandomListNode *pNode5 = new RandomListNode(5);

    BuildNodes(pNode1, pNode2, NULL);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, pNode3);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test2", pNode1);
}

/*       -----------------
        \|/              |
 1-------2-------3-------4-------5
         |              /|\
         |               |
         |---------------| */
void Test3()
{
    RandomListNode *pNode1 = new RandomListNode(1);
    RandomListNode *pNode2 = new RandomListNode(2);
    RandomListNode *pNode3 = new RandomListNode(3);
    RandomListNode *pNode4 = new RandomListNode(4);
    RandomListNode *pNode5 = new RandomListNode(5);

    BuildNodes(pNode1, pNode2, NULL);
    BuildNodes(pNode2, pNode3, pNode4);
    BuildNodes(pNode3, pNode4, NULL);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test3", pNode1);
}

void Test4()
{
    RandomListNode *pNode1 = new RandomListNode(1);
    BuildNodes(pNode1, NULL, pNode1);

    Test("Test4", pNode1);
}

void Test5()
{
    Test("Test5", NULL);
}

int main()
{
    Test1();
    // Test2();
    // Test3();
    // Test4();
    // Test5();
    return 0;
}