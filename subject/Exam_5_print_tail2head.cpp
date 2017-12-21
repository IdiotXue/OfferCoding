#include <iostream>
#include <vector>
#include <stack>
using std::stack;
using std::vector;

/**
 * 思路：入栈再出栈
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
    vector<int> printListFromTailToHead(ListNode *head)
    {
        if (head == nullptr)
            return vector<int>();
        ListNode *node = head;
        //保存指针，拷贝指针比拷贝对象快，本例是int体现不出来
        stack<ListNode *> iStack; 
        while (node)
        {
            iStack.push(node);
            node = node->next;
        }
        vector<int> vnTemp(iStack.size());
        for (size_t i = 0; i < vnTemp.size(); ++i)
        {
            vnTemp[i] = iStack.top()->val;
            iStack.pop();
        }
        return vnTemp;
    }
};
int main(int argc, char *argv[])
{
    ListNode *head = new ListNode(6);
    ListNode *node1 = new ListNode(20);
    ListNode *node2 = new ListNode(45);
    ListNode *node3 = new ListNode(4);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    Solution s;
    vector<int> vnTemp = s.printListFromTailToHead(head);
    for (const auto &x : vnTemp)
        std::cout << x << " ";
    std::cout << std::endl;
}