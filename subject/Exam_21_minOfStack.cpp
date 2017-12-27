#include <iostream>
#include <stack>
#include <functional>
#include <string>
#include <stdexcept>
using std::cout;
using std::endl;
using std::stack;
using std::string;

/**
 * 包含min函数的栈
 * 思路：
 * 第一个想法是维护一个堆和一个栈，细想发现pop操作时，堆只能删除堆顶，因此放弃。
 * 第二个想法针对这一点做改进就行，既然堆pop不方便，那就干脆再来一个辅助存最小值的栈，
 *         每次push的时候都存当前的最小值
 */
class Solution
{
  public:
    void push(int value)
    {
        m_nStack.push(value);
        if (m_nMinStack.empty())
        {
            m_nMinStack.push(value);
            return;
        }
        if (value < m_nMinStack.top()) //每次都存现阶段的最小值
            m_nMinStack.push(value);
        else
            m_nMinStack.push(m_nMinStack.top());
    }
    void pop()
    {
        if (m_nStack.empty())
            throw std::runtime_error("stack is empty");
        m_nStack.pop();
        m_nMinStack.pop();
    }
    int top()
    {
        if (m_nStack.empty())
            throw std::runtime_error("stack is empty");
        return m_nStack.top();
    }
    int min()
    {
        if (m_nStack.empty())
            throw std::runtime_error("stack is empty");
        return m_nMinStack.top();
    }

  private:
    stack<int> m_nStack;
    stack<int> m_nMinStack;
};
void Test(string TestName, Solution &iStack, int expected)
{
    cout << TestName << ":";
    if (iStack.min() == expected)
        cout << "Pass" << endl;
    else
        cout << "Fail" << endl;
}
int main()
{
    Solution iStack;

    iStack.push(3);
    Test("Test1", iStack, 3);

    iStack.push(4);
    Test("Test2", iStack, 3);

    iStack.push(2);
    Test("Test3", iStack, 2);

    iStack.push(3);
    Test("Test4", iStack, 2);

    iStack.pop();
    Test("Test5", iStack, 2);

    iStack.pop();
    Test("Test6", iStack, 3);

    iStack.pop();
    Test("Test7", iStack, 3);

    iStack.push(0);
    Test("Test8", iStack, 0);

    return 0;
}