#include <iostream>
#include <stack>
#include <stdexcept>
using std::stack;

/**
 * 思路
 * 队列是先进先出，栈是先进后出
 * stack1专门负责入队，stack2专门负责出队
 * 出队时：若stack2为空，则先从stack1出栈至空，元素都向stack2入栈，
 *       再从stack2出栈，否则，直接从stack2出栈
 * 入队时：直接stack1入栈即可
 * 特例：两个栈都空还pop
 */
class Solution
{
  public:
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {
        if (stack2.empty())
        {
            if (stack1.empty())
                throw std::runtime_error("queue is always empty");
            while (!stack1.empty())
            {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int node = stack2.top();
        stack2.pop();
        return node;
    }

  private:
    stack<int> stack1;
    stack<int> stack2;
};
int main(int argc, char *argv[])
{
    Solution s;
    s.push(1);
    s.push(2);
    //元素从stack1到stack2
    std::cout << s.pop() << std::endl;
    s.push(3);
    s.push(4);
    //stack2还有元素
    std::cout << s.pop() << std::endl;
    //stack2为空，从stack1再拿元素    
    std::cout << s.pop() << std::endl;
    std::cout << s.pop() << std::endl;
    //两个stack都空
    std::cout << s.pop() << std::endl;
    return 0;
}