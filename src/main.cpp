#include <iostream>
#include <vector>
#include <stdexcept>
using std::cout;
using std::endl;
using std::vector;

/**
 * 复杂链表的复制
 * 思路：
 * 基本思路：复制next主链上的结点，再复制random，但复制每个random都得从新建链表头开始寻找到该结点
 * 改进1：用map<RandomListNode*,RandomListNode*>使新旧链表的每个结点一一对应
 * 终止条件：当然是遇到叶结点
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
    RandomListNode *Clone(RandomListNode *pHead)
    {
    }
};

int main()
{

    return 0;
}