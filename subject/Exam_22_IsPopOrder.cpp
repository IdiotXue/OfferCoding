#include <iostream>
#include <stack>
#include <vector>
using std::cout;
using std::endl;
using std::stack;
using std::vector;

/**
 * 栈的压入和弹出序列
 * 思路：
 * 用一个栈模拟压入和弹出：
 *  循环入栈至所有元素都入栈
 *      每次判断栈顶元素是否等于弹出序列popV的当前元素
 *      如果是就循环弹出到不是为止
 * 最终栈为空说明压栈序列是对应的弹出序列，否则false
 * 特例：两个序列为空或长度不相等
 * 
 */
class Solution
{
  public:
    bool IsPopOrder(vector<int> pushV, vector<int> popV)
    {
        if (pushV.empty() || popV.empty() || pushV.size() != popV.size())
            return false;
        stack<int> nStack;
        int index = 0;
        for (auto val : pushV)
        {
            nStack.push(val);
            while (!nStack.empty() && nStack.top() == popV[index])
            {
                nStack.pop();
                ++index;
            }
        }
        if (nStack.empty())
            return true;
        return false;
    }
};
void Test(int ngPush[], int nLenPush, int ngPop[], int nLenPop)
{
    static int test = 0;
    cout << ++test << ": ";
    vector<int> vnPush(ngPush, ngPush + nLenPush);
    vector<int> vnPop(ngPop, ngPop + nLenPop);
    Solution s;
    cout << std::boolalpha << s.IsPopOrder(vnPush, vnPop) << endl;
}
void Test1()
{ //true
    const int nLen = 5;
    int push[nLen] = {1, 2, 3, 4, 5};
    int pop[nLen] = {4, 5, 3, 2, 1};
    Test(push, nLen, pop, nLen);
}
void Test2()
{ //true
    const int nLen = 5;
    int push[nLen] = {1, 2, 3, 4, 5};
    int pop[nLen] = {3, 5, 4, 2, 1};
    Test(push, nLen, pop, nLen);
}
void Test3()
{ //false
    const int nLen = 5;
    int push[nLen] = {1, 2, 3, 4, 5};
    int pop[nLen] = {4, 3, 5, 1, 2};
    Test(push, nLen, pop, nLen);
}
void Test4()
{ //false
    const int nLen = 5;
    int push[nLen] = {1, 2, 3, 4, 5};
    int pop[nLen] = {3, 5, 4, 1, 2};
    Test(push, nLen, pop, nLen);
}
void Test5()
{ //true
    const int nLen = 1;
    int push[nLen] = {1};
    int pop[nLen] = {1};
    Test(push, nLen, pop, nLen);
}
void Test6()
{ //false
    const int nLen = 1;
    int push[nLen] = {1};
    int pop[nLen] = {2};
    Test(push, nLen, pop, nLen);
}
void Test7()
{ //false
    const int nLen = 5;
    int push[nLen] = {1, 2, 3, 4, 5};
    int pop[nLen] = {4, 5, 3, 2, 1};
    Test(push, nLen, pop, nLen - 1);
}
void Test8()
{
    Test(NULL, 0, NULL, 0);
}
int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    return 0;
}